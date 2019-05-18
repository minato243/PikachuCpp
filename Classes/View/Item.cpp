#include "Item.h"

Item::Item()
{
	bg = Sprite::createWithSpriteFrameName("bg_item_1.png");
}

Item::~Item()
{
	icon->release();
	bg->release();
}

void Item::setSelected(bool isSelected)
{
	if(!isSelected) bg->setSpriteFrame("bg_item_1.png");
	else bg->setSpriteFrame("bg_item_3.png");
}

void Item::setVisible(bool isVisible)
{
	this->bg->setVisible(isVisible);
}

void Item::setIcon(int iconType)
{
	if (iconType == -1)
	{
		this->setVisible(false);
		return;
	}
	char text[100];
	sprintf(text, "item_classic/ic_%d.png", iconType +1);
	icon = Sprite::createWithSpriteFrameName(text);
	bg->removeAllChildren();
	bg->addChild(icon);
	icon->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
}

