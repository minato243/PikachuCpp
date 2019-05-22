#ifndef Item_h__
#define Item_h__

#include "cocos2d.h"

#define MODE_CLASSIC	0
#define MODE_MORDEN		1

USING_NS_CC;
using namespace std;

class Item{
public:
	Item();
	~Item();

	Sprite* bg;
	Sprite* icon;
	bool isSelected;

	void setSelected(bool isSelected);
	void setVisible(bool isVisible);
	void setIcon(int iconType);
	void showHint();
	void hideHint();
};
#endif
