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
	this->isSelected = !this->isSelected;
	Pos curPos = {0, 0};
	curPos.x = (int)pos.x / ITEM_WIDTH + 1;
	curPos.y = (int)pos.y / ITEM_HEIGHT + 1;

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
			int temp = cardMatrix[curPos.y][curPos.x];
			cardMatrix[curPos.y][curPos.x] = -1;
			cardMatrix[selectedPos.y][selectedPos.x] = -1;
			rCount = MAX_INT;
			t.clear();
			r.clear();
			directList.clear();
			findRoute(curPos.x, curPos.y, 0);
			cardMatrix[curPos.y][curPos.x] = temp;
			cardMatrix[selectedPos.y][selectedPos.x] = temp;

			if (rCount != MAX_INT){
				SoundManager::playPairSound();
				GameDataMgr::getInstance()->addScore(40);

				int x1 = selectedPos.x, y1 = selectedPos.y, x2 = curPos.x, y2 = curPos.y;
				cardMatrix[y1][x1] = -1;
				cardMatrix[y2][x2] = -1;
				itemMatrix[y1][x1]->setVisible(false);
				itemMatrix[y2][x2]->setVisible(false);
				// System.out.println("y1 " + y1 + ", x1 = " + x1);
				move(x1, y1, x2, y2);
				drawPath();

				remainCount -= 2;
				if (!isLive()) {
					while (!isLive()) {
						permutation();
					}
				}
				// System.out.println("Ok");
				if (remainCount == 0) {
					// Am thanh het ban LEVEL.start();
					//tongDiem += clock.t / 10 * 10;
					//if (level < 8) {
						//SoundManager::playLevelSound();
						//level++;
						//newGame();
					//}
					//else {
						//GameDataMgr::getInstance()->youWin();
					//}
				}
			}
			else {
				SoundManager::playNoSound();
			}
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

			this->drawNode = DrawNode::create();
			//drawNode->drawPoly(path, 4, false, Color4F::RED);
			//drawNode->drawCircle(Vec2(400, 240), 100, 360, 2, true, Color4F::RED);
			auto draw = DrawNode::create(); 
			draw->drawLine(Point(0, 0), Point(800, 480), Color4F::RED); 
			bg->addChild(draw);
			bg->addChild(drawNode,1000);
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

	if (countTurn(directList) > 2)
		return false;
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

void Board::findRoute(int x, int y, int direct) {
	if (x < 0 || x > colum+ 1)
		return;
	if (y < 0 || y > row + 1)
		return; 
	if (cardMatrix[y][x] != -1)
		return; // khong phai o trong, thoat (1)
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
		return;
	}
		

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
	}
	else 
	{
		findRoute(x - 1, y, LEFT);
		findRoute(x + 1, y, RIGHT);
		findRoute(x, y - 1, UP);
		findRoute(x, y + 1, DOWN);
	}

	t.pop_back();
	directList.pop_back();
	// danh dau lai la o [y,x] trong, co the di qua lai
	cardMatrix[y][x] = -1;
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

void Board::move(int x1, int y1, int x2, int y2)
{

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
	Vec2 path[4];
	path[0] = Vec2(0, 0);
	path[1] = Vec2(800, 480);
	path[2] = Vec2(480, 800);
	path[3] = Vec2(0, 800);

	this->drawNode = DrawNode::create();
	drawNode->drawPoly(path, 4, false, Color4F::RED);
	//drawNode->drawCircle(Vec2(400, 240), 100, 360, 2, true, Color4F::RED);
	bg->addChild(drawNode);
}

void Board::hidePath()
{

}
