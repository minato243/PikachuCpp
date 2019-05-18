#ifndef Board_h__
#define Board_h__

#include "cocos2d.h"
#include <string>
#include "View\Item.h"
#include "Base\DataStruct.h"

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
	Pos selectedPos;

	DrawNode *drawNode;
	Node *bg;

	void initData();
	void addToBg(Node *bg);
	void setSelected(Vec2 pos);
	string toString();

	bool findRouter(int x1, int y1, int x2, int y2, int direct);
	void findRoute(int x, int y, int direct);
	int countTurn(vector<int> d);

	void move(int x1, int y1, int x2, int y2);
	bool isLive();
	void permutation();

	static void setItemSize(const int width, const int height);
	void drawPath();
	void hidePath();
};
#endif
