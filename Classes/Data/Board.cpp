#include "Board.h"
#include "SolveMatrix.h"
#include "Base\GlobalVar.h"
#include "Base\DataStruct.h"
#include "Base\SoundManager.h"
#include "GameDataMgr.h"
#include "base\CCConsole.h"

int Board::ITEM_WIDTH = 62;
int Board::ITEM_HEIGHT = 62;

Board::Board(int _row, int _colum, int _numImage)
{
	this->row = _row;
	this->colum = _colum;
	this->numImage = _numImage;
	this->isDrawing = false;
	this->isHinting = false;
	this->hint1 = Pos{ 0, 0 };
	this->hint2 = Pos{ 0, 0 };
	this->drawNode = new DrawNode();
}

Board::~Board()
{
	this->itemMatrix.clear();
	this->cardMatrix.clear();
	
}

void Board::initData()
{
	vector<int> countMatrix = SolveMatrix::createCardCountMatrix(row * colum, numImage);
	cardMatrix = SolveMatrix::createMatrix(countMatrix, numImage, row, colum);
	
	for (int i = 0; i < row+2; i++){
		vector<Item *> itemList;
		for (int j = 0; j < colum +2; j++){
			Item* item = new Item();
			item->setIcon(this->cardMatrix[i][j]);
			itemList.push_back(item);
		}
		itemMatrix.push_back(itemList);
	}

	remainCount = row * colum;
}

void Board::setSelected(Vec2 pos)
{
	if (isDrawing) return;
	curPos = { 0, 0 };
	curPos.x = (int)pos.x / ITEM_WIDTH + 1;
	curPos.y = (int)pos.y / ITEM_HEIGHT + 1;
	if (curPos.x > colum || curPos.y > row || curPos.x < 0 || curPos.y < 0) return;
	this->isHinting = false;

	this->isSelected = !this->isSelected;
	log("setSelected %d %d", selectedPos.x, selectedPos.y);
	if (!this->isSelected){
		this->selectedPos = { curPos.x, curPos.y };
		this->itemMatrix[this->selectedPos.y][this->selectedPos.x]->setSelected(true);
	}
	else {
		this->itemMatrix[this->selectedPos.y][this->selectedPos.x]->setSelected(false);
		if (curPos.x == selectedPos.x && curPos.y == selectedPos.y){

		}
		else if(cardMatrix[curPos.y][curPos.x] != cardMatrix[selectedPos.y][selectedPos.x]){
			SoundManager::playWrongSound();
		}
		else {
			if (findPath(selectedPos, curPos)){
				SoundManager::playPairSound();
				hideHint();
				drawPath();
			}
			//int temp = cardMatrix[curPos.y][curPos.x];
			//cardMatrix[curPos.y][curPos.x] = -1;
			//cardMatrix[selectedPos.y][selectedPos.x] = -1;
			//rCount = MAX_INT;
			//t.clear();
			//r.clear();
			//directList.clear();
			////findRoute(curPos.x, curPos.y, 0);
			//cardMatrix[curPos.y][curPos.x] = temp;
			//cardMatrix[selectedPos.y][selectedPos.x] = temp;

			//if (rCount != MAX_INT){
			//	SoundManager::playPairSound();
			//	hideHint();
			//	drawPath();

			//	remainCount -= 2;
			//	if (!isLive()) {
			//		while (!isLive()) {
			//			permutation();
			//		}
			//	}
			//	// System.out.println("Ok");
			//	if (remainCount == 0) {
			//		// Am thanh het ban LEVEL.start();
			//		//tongDiem += clock.t / 10 * 10;
			//		//if (level < 8) {
			//			//SoundManager::playLevelSound();
			//			//level++;
			//			//newGame();
			//		//}
			//		//else {
			//			//GameDataMgr::getInstance()->youWin();
			//		//}
			//	}
			//}
			//else {
			//	SoundManager::playNoSound();
			//}
		}
	}
}

std::string Board::toString()
{
	string str = "";
	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < colum + 2; j++) {
			str.append(" ").append(StringUtils::toString(cardMatrix[i][j]));
		}
		str.append("\n");
	}
	return str;
}

void Board::addToBg(Node *bg)
{
	this->bg = bg;
	Board::setItemSize(bg->getContentSize().width / colum, bg->getContentSize().height / row);
	for (int i = 0; i < row +2; i++){
		for (int j = 0; j < colum +2; j++){
			Item *item = this->itemMatrix[i][j];
			bg->addChild(item->bg);
			item->bg->setScale(ITEM_WIDTH/ item->bg->getContentSize().width);
			item->bg->setPosition(Vec2(ITEM_WIDTH *j - ITEM_WIDTH / 2, ITEM_HEIGHT *i - ITEM_HEIGHT/ 2));
		}
	}
}

void Board::setItemSize(const int width, const int height)
{
	Board::ITEM_WIDTH = width;
	Board::ITEM_HEIGHT = height;
}

bool Board::findRouter(int x1, int y1, int x2, int y2, int direct) {
	if (x2 < 0 || x2 > row + 1)
		return false;
	if (y2 < 0 || y2 > colum + 1)
		return false;
	if (cardMatrix[x2][y2] != -1)
		return false;
	Pos p = { x2, y2 };
	t.push_back(p);
	directList.push_back(direct);

	if (countTurn(directList) > 2){
		t.pop_back();
		directList.pop_back();
		return false;
	}
		
	cardMatrix[x2][y2] = -2;
	if (x2 == x1 && y2 == y1) {
		return true;
	}
	else {
		bool lg = (findRouter(x1, y1, x2, y2 - 1, LEFT)
			|| findRouter(x1, y1, x2, y2 + 1, RIGHT)
			|| findRouter(x1, y1, x2 + 1, y2, DOWN) 
			|| findRouter(x1, y1, x2 - 1, y2, UP));
		t.pop_back();
		directList.pop_back();
		cardMatrix[x2][y2] = -1;
		return lg;
	}
}

bool Board::findRoute(int x, int y, int direct) {
	if (x < 0 || x > colum+ 1)
		return false;
	if (y < 0 || y > row + 1)
		return false;
	if (cardMatrix[y][x] != -1)
		return false; // khong phai o trong, thoat (1)
	Pos p = { x, y };
	t.push_back(p);
	string str = "";
	for (int i = 0; i < t.size(); i++){
		str.append("(" + StringUtils::toString(t[i].x) + ", " + StringUtils::toString(t[i].y)+") ");
	}
	log(str.c_str());
	directList.push_back(direct); // ghi nhan la huong di den o [y,x]

	if (countTurn(directList) > 2){
		t.pop_back();
		directList.pop_back();
		return false;
	}
		
	bool b;
	cardMatrix[y][x] = -2; // danh dau o [y,x] da di qua
	if (x == selectedPos.x && y == selectedPos.y) 
	{
		// kiem tra xem duong di moi tim duoc co ngan hon duong di tim trong
		// cac lan truoc khong
		if (t.size() < rCount) {
			// neu ngan hon, ghi nho lai duong di nay
			rCount = t.size();
			r.clear();
			for (int i = 0; i < t.size(); i++) {
				Pos p = { t.at(i).x, t.at(i).y };
				r.push_back(p);
			}
		}
		return true;
	}
	else 
	{
		b = (findRoute(x - 1, y, LEFT))
		|| (findRoute(x + 1, y, RIGHT)) 
		|| (findRoute(x, y - 1, UP)) 
		|| (findRoute(x, y + 1, DOWN)) ;
	}

	t.pop_back();
	directList.pop_back();
	// danh dau lai la o [y,x] trong, co the di qua lai
	cardMatrix[y][x] = -1;
	return b;
}

int Board::countTurn(vector<int> d) {
	int count = 0;
	for (int i = 2; i < d.size(); i++)
	{
		if (d[i - 1] != d[i])
			count++; 
	}
	return count;
}

void Board::move(Pos p1, Pos p2)
{
	int moveType = this->gameData->currentLevel % 9;

	switch (moveType)
	{
	case 1:
		moveUp(p1, p2);
		break;
	case 2: 
		moveDown(p1, p2);
		break;
	case 3:
		moveLeft(p1, p2);
		break;
	case 4:
		moveRight(p1, p2);
		break;
	case 5:
		moveUpAndDown(p1, p2);
		break;
	case 6:
		moveLeftAndRight(p1, p2);
		break;
	case 7:
		moveToCenterFromTopBottom(p1, p2);
		break;
	case 8:
		moveToCenterFromLeftRight(p1, p2);
		break;
	default:
		break;
	}
}

bool Board::isLive()
{
	return true;
}

void Board::permutation()
{

}

void Board::drawPath()
{
	isDrawing = true;
	const int n = r.size();
	Vec2 *path = new Vec2[n];
	string str="";
	for (int i = 0; i < n; i++){
		Vec2 vec = fromPosToBg(r.at(i));
		path[i] = vec;
		str.append("{").append(StringUtils::toString(vec.x)).append(",")
			.append(StringUtils::toString(vec.y)).append("}");
	}
	
	//CCLOG(str.c_str());
	this->drawNode = DrawNode::create(3);
	drawNode->drawPoly(path, n, false, Color4F::RED);
	//drawNode->drawCircle(Vec2(400, 240), 100, 360, 2, true, Color4F::RED);
	bg->addChild(drawNode);

	bg->runAction(Sequence::create(CCDelayTime::create(0.25f), CallFunc::create([this] {
		this->drawNode->removeFromParent();
		this->drawNode = NULL;
		updateMatrix();
		isDrawing = false;
	}), NULL
	));
}

void Board::hidePath(float dt)
{
	this->drawNode->removeFromParent();
	this->drawNode = NULL;

	updateMatrix();
}

cocos2d::Vec2 Board::fromPosToBg(Pos p)
{
	Vec2 v = { 0, 0 };
	v.x = (p.x - 1) * ITEM_WIDTH + ITEM_WIDTH / 2;
	v.y = (p.y - 1) * ITEM_HEIGHT + ITEM_HEIGHT / 2;

	return v;
}

void Board::setGameData(GameDataMgr *gameData)
{
	this->gameData = gameData;
}

void Board::moveUp(Pos p1, Pos p2)
{
	if (p2.y > p1.y) {
		moveUpFromBottom(p1);
		moveUpFromBottom(p2);		
	}
	else {
		moveUpFromBottom(p2);
		moveUpFromBottom(p1);	
	}
}

void Board::moveDown(Pos p1, Pos p2)
{
	if (p1.y > p2.y) {
		moveDownFromTop(p1);
		moveDownFromTop(p2);
	}
	else {
		moveDownFromTop(p2);
		moveDownFromTop(p1);
	}
}

void Board::moveLeft(Pos p1, Pos p2)
{
	if (p1.x > p2.x) {
		moveLeftFromRight(p1);
		moveLeftFromRight(p2);
	}
	else {
		moveLeftFromRight(p2);
		moveLeftFromRight(p1);
	}

//	log(this->toString().c_str());
}

void Board::moveRight(Pos p1, Pos p2)
{
	if (p1.x < p2.x) {
		moveRightFromLeft(p1);
		moveRightFromLeft(p2);
	}
	else {
		moveRightFromLeft(p2);
		moveRightFromLeft(p1);
	}
}

void Board::moveUpAndDown(Pos p1, Pos p2)
{
	if ((p1.x == p2.x) && (p1.y > row / 2)
		&& (p2.y > row / 2)) {
		if (p1.y > p2.y) {
			moveDownFromCenter(p2);
			moveDownFromCenter(p1);
		}
		else {
			moveDownFromCenter(p1);
			moveDownFromCenter(p2);
		}
	}
	else if ((p1.x == p2.x) && (p1.y <= row / 2)
		&& (p2.y <= row / 2)) {
		if (p1.y < p2.y) {
			moveUpFromCenter(p2);
			moveUpFromCenter(p1);
		}
		else {
			moveUpFromCenter(p1);
			moveUpFromCenter(p2);
		}
	}
	else {
		if (p1.y > row / 2) {
			moveDownFromCenter(p1);
		}
		else
			moveUpFromCenter(p1);
		if (p2.y > row / 2)
			moveDownFromCenter(p2);
		else
			moveUpFromCenter(p2);
	}
}

void Board::moveLeftAndRight(Pos p1, Pos p2)
{
	if ((p1.y == p2.y) && (p1.x > colum / 2)
		&& (p2.x > colum / 2)) {
		if (p1.x < p2.x) {
			moveRightFromCenter(p1);
			moveRightFromCenter(p2);
		}
		else {
			moveRightFromCenter(p2);
			moveRightFromCenter(p1);
		}
	}
	else if ((p1.y == p2.y) && (p1.x <= colum / 2)
		&& (p2.x <= colum / 2)) {
		if (p1.x < p2.x) {
			moveLeftFromCenter(p2);
			moveLeftFromCenter(p1);
		}
		else {
			moveLeftFromCenter(p1);
			moveLeftFromCenter(p2);
		}
	}
	else {
		if (p1.x > colum / 2)
			moveRightFromCenter(p1);
		else
			moveLeftFromCenter(p1);
		if (p2.x > colum / 2)
			moveRightFromCenter(p2);
		else
			moveLeftFromCenter(p2);
	}
	
}

void Board::moveToCenterFromTopBottom(Pos p1, Pos p2)
{
	if ((p1.x == p2.x) && (p1.y > row / 2)
		&& (p2.y > row / 2)) {
		if (p1.y > p2.y) {
			moveBottomToCenter(p1);
			moveBottomToCenter(p2);
		}
		else {
			moveBottomToCenter(p2);
			moveBottomToCenter(p1);
		}
	}
	else if ((p1.x == p2.x) && (p1.y <= row / 2)
		&& (p2.y <= row / 2)) {
		if (p1.y > p2.y) {
			moveTopToCenter(p2);
			moveTopToCenter(p1);
		}
		else {
			moveTopToCenter(p1);
			moveTopToCenter(p2);
		}
	}
	else {
		if (p1.y > row / 2)
			moveBottomToCenter(p1);
		else
			moveTopToCenter(p1);
		if (p2.y > row / 2)
			moveBottomToCenter(p2);
		else
			moveTopToCenter(p2);
	}
	
}

void Board::moveToCenterFromLeftRight(Pos p1, Pos p2)
{
	if ((p1.y == p2.y) && (p1.x > colum / 2)
		&& (p2.x > colum / 2)) {
		if (p1.x > p2.x) {
			moveRightToCenter(p1);
			moveRightToCenter(p2);
		}
		else {
			moveRightToCenter(p2);
			moveRightToCenter(p1);
		}
	}
	else if ((p1.y == p2.y) && (p1.x <= colum / 2)
		&& (p2.x <= colum / 2)) {
		if (p1.x > p2.x) {
			moveLeftToCenter(p2);
			moveLeftToCenter(p1);
		}
		else {
			moveLeftToCenter(p1);
			moveLeftToCenter(p2);
		}
	}

	else {
		if (p1.x > colum / 2)
			moveRightToCenter(p1);
		else
			moveLeftToCenter(p1);
		if (p2.x > colum / 2)
			moveRightToCenter(p2);
		else
			moveLeftToCenter(p2);
		;
	}
	
}
void Board::moveUpFromBottom(Pos p)
{
	for (int i = p.y; i >= 1; i--){
		cardMatrix[i][p.x] = cardMatrix[i - 1][p.x];
		Pos tmp; tmp.y = i; tmp.x = p.x;
		this->updateItem(tmp);
	}
}

void Board::moveDownFromTop(Pos p)
{
	for (int i = p.y; i <= row; i++){
		cardMatrix[i][p.x] = cardMatrix[i + 1][p.x];
		Pos tmp; tmp.y = i; tmp.x = p.x;
		this->updateItem(tmp);
	}
}


void Board::moveLeftFromRight(Pos p)
{
	for (int j = p.x; j <= colum; j++){
		cardMatrix[p.y][j] = cardMatrix[p.y][j + 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
}

void Board::moveRightFromLeft(Pos p)
{
	for (int j = p.x; j >= 1; j--){
		cardMatrix[p.y][j] = cardMatrix[p.y][j - 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
}



void Board::moveDownFromCenter(Pos p)
{
	int i;
	for (i = p.y; i > row / 2 + 1; i--) {
		cardMatrix[i][p.x] = cardMatrix[i - 1][p.x];
		Pos tmp; tmp.x = p.x; tmp.y = i;
		this->updateItem(tmp);
	}

	cardMatrix[i][p.x] = -1;
	Pos tmp; tmp.x = p.x; tmp.y = i;
	this->updateItem(tmp);
}

void Board::moveUpFromCenter(Pos p)
{
	int i;
	for (i = p.y; i < row / 2; i++) {
		cardMatrix[i][p.x] = cardMatrix[i + 1][p.x];
		Pos tmp; tmp.x = p.x; tmp.y = i;
		this->updateItem(tmp);
	}
	cardMatrix[i][p.x] = -1;
	Pos tmp; tmp.x = p.x; tmp.y = i;
	this->updateItem(tmp);
}

void Board::moveLeftFromCenter(Pos p)
{
	log("moveLeftFromCenter %d %d",p.x, p.y);
	int j;
	for (j = p.x; j < colum / 2; j++) {
		cardMatrix[p.y][j] = cardMatrix[p.y][j + 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
	cardMatrix[p.y][j] = -1;
	Pos tmp; tmp.y = p.y; tmp.x = j;
	this->updateItem(tmp);
}


void Board::moveRightFromCenter(Pos p)
{
	log("moveRightFromCenter %d %d", p.x, p.y);
	int j;
	for (j = p.x; j > colum / 2 + 1; j--) {
		cardMatrix[p.y][j] = cardMatrix[p.y][j - 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
	cardMatrix[p.y][j] = -1;
	Pos tmp; tmp.y = p.y; tmp.x = j;
	this->updateItem(tmp);
}


void Board::moveLeftToCenter(Pos p)
{
	int j;
	for (j = p.x; j > 0; j--) {
		cardMatrix[p.y][j] = cardMatrix[p.y][j - 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
	cardMatrix[p.y][j] = -1;
	Pos tmp; tmp.y = p.y; tmp.x = j;
	this->updateItem(tmp);
}

void Board::moveRightToCenter(Pos p)
{
	int j;
	for (j = p.x; j < colum + 1; j++) {
		cardMatrix[p.y][j] = cardMatrix[p.y][j + 1];
		Pos tmp; tmp.y = p.y; tmp.x = j;
		this->updateItem(tmp);
	}
	cardMatrix[p.y][j] = -1;
	Pos tmp; tmp.y = p.y; tmp.x = j;
	this->updateItem(tmp);
}

void Board::moveTopToCenter(Pos p)
{
	int i;
	for (i = p.y; i > 0; i--) {
		cardMatrix[i][p.x] = cardMatrix[i - 1][p.x];
		Pos tmp; tmp.x = p.x; tmp.y = i;
		this->updateItem(tmp);
	}
	cardMatrix[i][p.x] = -1;
	Pos tmp; tmp.x = p.x; tmp.y = i;
	this->updateItem(tmp);
}

void Board::moveBottomToCenter(Pos p)
{
	int i;
	for (i = p.y; i < row; i++) {
		cardMatrix[i][p.x] = cardMatrix[i + 1][p.x];
		Pos tmp; tmp.x = p.x; tmp.y = i;
		this->updateItem(tmp);
	}
	cardMatrix[i][p.x] = -1;
	Pos tmp; tmp.x = p.x; tmp.y = i;
	this->updateItem(tmp);
}

void Board::updateItem(Pos p)
{
	int iconType = this->cardMatrix[p.y][p.x];
	this->itemMatrix[p.y][p.x]->setIcon(iconType);
}

void Board::updateMatrix()
{
	int x1 = selectedPos.x, y1 = selectedPos.y, x2 = curPos.x, y2 = curPos.y;
	cardMatrix[y1][x1] = -1;
	cardMatrix[y2][x2] = -1;

	this->move(this->selectedPos, this->curPos);
	this->gameData->collect();
}

void Board::hint()
{
	if (this->isHinting) return;
	if (this->gameData->numHint <= 0) {
		SoundManager::playWrongSound();
		return;
	}

	for (int i = 1; i <= row + 1; i++) {
		for (int j = 1; j <= colum + 1; j++) {
			if (cardMatrix[i][j] != -1) {
				for (int i2 = 1; i2 < row + 1; i2++) {
					for (int j2 = 1; j2 < colum + 1; j2++) {
						if ((cardMatrix[i][j] == cardMatrix[i2][j2])
							&& (i2 != i || j2 != j)) {
							int temp = cardMatrix[i][j];
							cardMatrix[i][j] = cardMatrix[i2][j2] = -1;
							rCount = MAX_INT;
							t.clear();
							directList.clear();
							boolean lg = findRouter(i, j, i2, j2,NONE);
							cardMatrix[i][j] = cardMatrix[i2][j2] = temp;
							if (lg) {
								this->hint1.x = j; this->hint1.y = i;
								this->hint2.x = j2; this->hint2.y = i2;
								this->itemMatrix[hint1.y][hint1.x]->showHint();
								this->itemMatrix[hint2.y][hint2.x]->showHint();
								this->isHinting = true;
								gameData->useHint();
								log("hint (%d %d) (%d %d)", hint1.x, hint1.y, hint2.x, hint2.y);
								return;
							}
						}
					}
				}
			}
		}
	}
}

void Board::hideHint()
{
	this->itemMatrix[hint1.y][hint1.x]->hideHint();
	this->itemMatrix[hint2.y][hint2.x]->hideHint();
}

bool Board::findPath(Pos p1, Pos p2)
{
	r.clear();
	if (findPath(p1, p2, 0)) return true;
	if (findPath(p1, p2, 1)) return true;
	if (findPath(p1, p2, 2)) return true;
	return false;
}

bool Board::findPath(Pos p1, Pos p2, int turn)
{
	if (turn == 0){
		if (canConnect(p1, p2)){
			r.push_back(p1);
			r.push_back(p2);
			return true;
		}
		return false;
	}
	else if (turn == 1){
		Pos tmp;
		tmp.x = p1.x;
		tmp.y = p2.y;
		if (cardMatrix[tmp.y][tmp.x] == -1 && canConnect(p1, tmp) && canConnect(tmp, p2)) {
			r.push_back(p1);
			r.push_back(tmp);
			r.push_back(p2);
			return true;
		}

		Pos tmp2; tmp2.x = p2.x; tmp2.y = p1.y;
		if (cardMatrix[tmp.y][tmp.x] == -1 && canConnect(p1, tmp2) && canConnect(tmp2, p2)) {
			r.push_back(p1);
			r.push_back(tmp2);
			r.push_back(p2);
			return true;
		}
		return false;
	}
	else if (turn == 2){
		Pos tmp1; tmp1.x = p1.x; 
		Pos tmp2; tmp2.x = p2.x;
		int maxY = max(row+2 -p1.y, p1.y);
		bool goUp = true;
		bool goDown = true;
		for (int i = 1; i <= maxY; i++){
			if (p1.y - i >= 0 && goDown){
				tmp1.y = p1.y - i;
				tmp2.y = tmp1.y;
				if (cardMatrix[tmp1.y][tmp1.x] == -1){
					if (cardMatrix[tmp2.y][tmp2.x] == -1 && canConnect(p1, tmp1) && canConnect(tmp1, tmp2) && canConnect(tmp2, p2)) {
						r.push_back(p1);
						r.push_back(tmp1);
						r.push_back(tmp2);
						r.push_back(p2);
						log("(%d %d) (%d %d) (%d %d) (%d %d)", p1.x, p1.y, tmp1.x, tmp1.y, tmp2.x, tmp2.y, p2.x, p2.y);
						return true;
					}
					
				}
				else {
					goDown = false;
				}

			}

			if (p1.y + i < row +2 && goUp){
				tmp1.y = p1.y + i;
				tmp2.y = tmp1.y;
				if (cardMatrix[tmp1.y][tmp1.x] == -1){
					if (cardMatrix[tmp2.y][tmp2.x] == -1 && canConnect(p1, tmp1) && canConnect(tmp1, tmp2) && canConnect(tmp2, p2)) {
						r.push_back(p1);
						r.push_back(tmp1);
						r.push_back(tmp2);
						r.push_back(p2);
						log("(%d %d) (%d %d) (%d %d) (%d %d)", p1.x, p1.y, tmp1.x, tmp1.y, tmp2.x, tmp2.y, p2.x, p2.y);
						return true;
					}
				}
				else {
					goUp = false;
				}
			}
		}

		tmp1.y = p1.y;
		tmp2.y = p2.y;
		int maxX = max(colum +2 - p1.x, p1.x);
		goUp = true;
		goDown = true;
		for (int j = 1; j <= maxX; j++){
			if (p1.x - j >= 0 && goDown){
				tmp1.x = p1.x - j;
				tmp2.x = tmp1.x;
				if (cardMatrix[tmp1.y][tmp1.x] == -1){
					if (cardMatrix[tmp2.y][tmp2.x] == -1 && canConnect(tmp1, tmp2) && canConnect(tmp2, p2)) {
						r.push_back(p1);
						r.push_back(tmp1);
						r.push_back(tmp2);
						r.push_back(p2);
						log("(%d %d) (%d %d) (%d %d) (%d %d)", p1.x, p1.y, tmp1.x, tmp1.y, tmp2.x, tmp2.y, p2.x, p2.y);
						return true;
					}
				}
				else {
					goDown = false;
				}
			}

			if (p1.x + j < colum + 2 && goUp){
				tmp1.x = p1.x + j;
				tmp2.x = tmp1.x;
				if (cardMatrix[tmp1.y][tmp1.x] == -1){
					if (canConnect(p1, tmp1) && canConnect(tmp1, tmp2) && canConnect(tmp2, p2)) {
						r.push_back(p1);
						r.push_back(tmp1);
						r.push_back(tmp2);
						r.push_back(p2);
						log("(%d %d) (%d %d) (%d %d) (%d %d)", p1.x, p1.y, tmp1.x, tmp1.y, tmp2.x, tmp2.y, p2.x, p2.y);
						return true;
					}
				}
				else{
					goUp = false;
				}
			}
		}

		return false;
	}
}

bool Board::canConnect(Pos p1, Pos p2)
{
	if (p1.x == p2.x){
		int beginY = p1.y < p2.y ? p1.y : p2.y;
		int endY = p1.y < p2.y ? p2.y : p1.y;
		for (int i = beginY + 1; i < endY;i ++){
			if (cardMatrix[i][p1.x] != -1){
				return false;
			}
		}
		return true;
	}
	else if (p1.y == p2.y){
		int beginX = p1.x < p2.x ? p1.x : p2.x;
		int endX = p1.x < p2.x ? p2.x : p1.x;
		for (int j = beginX + 1; j < endX; j++){
			if (cardMatrix[p1.y][j] != -1){
				return false;
			}
		}
		return true;
	}
	else return false;
}
