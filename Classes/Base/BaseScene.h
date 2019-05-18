#ifndef BaseScene_h__
#define BaseScene_h__

#include "cocos2d.h"
#include "platform\CCPlatformMacros.h"

USING_NS_CC;

class BaseScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(BaseScene);
	virtual bool init();
	void addKeyBoardListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onBackPress();
protected:
private:
};

#endif