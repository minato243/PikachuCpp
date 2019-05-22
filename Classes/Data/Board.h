#ifndef Board_h__
#define Board_h__

#include "cocos2d.h"
#include <string>
#include "View\Item.h"
#include "Base\DataStruct.h"
#include "GameDataMgr.h"

#define MODE_CLASSIC	0
#define MODE_MORDEN		1

USING_NS_CC;
using namespace std;

class Board{
public:
	Board(int row, int colum, int numImage);
	~Board();

	static int ITEM_WIDTH;
	static int ITEM_HEIGHT;

	int row;
	int colum;
	int numImage;

	vector<vector<Item *>> itemMatrix;
	vector <vector<int>> cardMatrix;
	vector<Pos> t;
	vector<Pos> r;
	vector<int> directList;
	int rCount;
	int remainCount;

	bool isSelected;
	bool isDrawing;
	Pos selectedPos;
	Pos curPos;
	bool isHinting;
	Pos hint1, hint2;

	DrawNode *drawNode;
	Node *bg;

	GameDataMgr *gameData;

	void initData();
	void setGameData(GameDataMgr *gameData);
	void addToBg(Node *bg);
	void setSelected(Vec2 pos);
	string toString();

	bool findRouter(int x1, int y1, int x2, int y2, int direct);
	bool findRoute(int x, int y, int direct);
	int countTurn(vector<int> d);
	bool findPath(Pos p1, Pos p2);
	bool findPath(Pos p1, Pos p2, int turn);
	bool canConnect(Pos p1, Pos p2);

	void move(Pos p1, Pos p2);
	void moveUp(Pos p1, Pos p2);
	void moveDown(Pos p1, Pos p2);
	void moveLeft(Pos p1, Pos p2);
	void moveRight(Pos p1, Pos p2);
	void moveUpAndDown(Pos p1, Pos p2);
	void moveLeftAndRight(Pos p1, Pos p2);
	void moveToCenterFromTopBottom(Pos p1, Pos p2);
	void moveToCenterFromLeftRight(Pos p1, Pos p2);

	void moveUpFromBottom(Pos p);
	void moveDownFromTop(Pos p);
	void moveLeftFromRight(Pos p);
	void moveRightFromLeft(Pos p);

	void moveDownFromCenter(Pos p);
	void moveUpFromCenter(Pos p);
	void moveLeftFromCenter(Pos p);
	void moveRightFromCenter(Pos p);
	void moveLeftToCenter(Pos p);
	void moveRightToCenter(Pos p);
	void moveTopToCenter(Pos p);
	void moveBottomToCenter(Pos p);

	void updateItem(Pos p);
	bool isLive();
	void permutation();

	void drawPath();
	void hidePath(float dt);
	void updateMatrix();
	void hint();
	void hideHint();

	static void setItemSize(const int width, const int height);
	static Vec2 fromPosToBg(Pos p);
};
#endif
