#include "MenuScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "ui\UIButton.h"
#include "SceneManager.h"
#include "Base\GameConstant.h"
#include "Base\PlatformUtils.h"
#include "Base\SoundManager.h"
#include "Data\GameDataMgr.h"

Scene * MenuScene::createScene()
{
	auto scene = Scene::create();
	Layer* layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto sprite = Sprite::create("bg_play.png");
	//sprite->setPosition(0, 0);

	//this->addChild(sprite, 0);

	this->loadResource();

	Node* node = CSLoader::createNode("MenuScene.csb");
	this->addChild(node);

	Node *bgImage = node->getChildByName("bgImage");

	ui::Button *playButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_play"));
	float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
	playButton->setZoomScale(0.1f * scaleX);
	playButton->setPressedActionEnabled(true);
	playButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onPlay, this));

	ui::Button *rateButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_rate"));
	rateButton->setZoomScale(0.1f * scaleX);
	rateButton->setPressedActionEnabled(true);
	rateButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onRate, this));

	ui::Button *highScoreButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_high_score"));
	highScoreButton->setZoomScale(0.1f * scaleX);
	highScoreButton->setPressedActionEnabled(true);
	highScoreButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onClassicMode, this));

	ui::Button *exitButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_high_score"));
	highScoreButton->setZoomScale(0.1f * scaleX);
	highScoreButton->setPressedActionEnabled(true);
	highScoreButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onClickExit, this));

	PlatformUtils::getInstance()->signInGoogle();

	PlatformUtils::getInstance()->initBanner();
	PlatformUtils::getInstance()->showBanner();
	
	this->addKeyBoardListener();

	return true;
}

void MenuScene::loadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("item.plist");
}

void MenuScene::onRate(Ref *obj)
{
	SoundManager::playClickSound();
	PlatformUtils::getInstance()->rateApp();
}

void MenuScene::onHighScore(Ref *obj)
{
	SoundManager::playClickSound();
	PlatformUtils::getInstance()->showHighScore();
}

void MenuScene::onPlay(Ref *obj)
{
	SoundManager::playClickSound();
	GameDataMgr::getInstance()->setMode(MODE_MORDEN);
	SceneManager::getInstance()->changeScene(SELECT_THEME_SCENE);
}

void MenuScene::onClickExit(Ref *obj)
{

}

void MenuScene::onClassicMode(Ref *obj)
{
	SoundManager::playClickSound();
	GameDataMgr::getInstance()->setMode(MODE_MORDEN);
	SceneManager::getInstance()->changeScene(SELECT_THEME_SCENE);
}


void MenuScene::addKeyBoardListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK) {
		this->onBackPress();
	}
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d released", keyCode);

}

void MenuScene::onBackPress()
{
	CCDirector::getInstance()->end();
}

