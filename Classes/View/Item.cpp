#include "Item.h"

Item::Item()
{
	bg = Sprite::createWithSpriteFrameName("bg_item_2.png");
}

Item::~Item()
{
	icon->release();
	bg->release();
}

void Item::setSelected(bool isSelected)
{
	this->hideHint();
	if(!isSelected) bg->setSpriteFrame("bg_item_2.png");
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

	this->setVisible(true);
	char text[100];
	sprintf(text, "item_classic/ic_%d.png", iconType +1);
	icon = Sprite::createWithSpriteFrameName(text);
	bg->removeAllChildren();
	bg->addChild(icon);
	icon->setPosition(Vec2(bg->getContentSize().width/2, bg->getContentSize().height/2));
}

void Item::showHint()
{
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(2);
	animFrames.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_item_3.png"));
	animFrames.pushBack(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bg_item_2.png"));
	Animation *animation = Animation::createWithSpriteFrames(animFrames, 0.25f, 100);
	Animate *animate = Animate::create(animation);
	bg->runAction(RepeatForever::create(animate));
}

void Item::hideHint()
{
	bg->stopAllActions();
	bg->setSpriteFrame("bg_item_2.png");
}

