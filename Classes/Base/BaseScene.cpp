#include "BaseScene.h"

bool BaseScene::init()
{
	if (!Scene::init()){
		return false;
	}

	this->addKeyBoardListener();
	return true;
}

void BaseScene::addKeyBoardListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(BaseScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		this->onBackPress();
	}
}

void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d released", keyCode);
}

void BaseScene::onBackPress()
{

}

