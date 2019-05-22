#include "PlayScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "Base\ccMacros.h"
#include "SceneManager.h"
#include "deprecated\CCDeprecated.h"
#include "Base\CCEventKeyboard.h"
#include "Base\PlatformUtils.h"
#include "Base\GameConstant.h"
#include "Base\SoundManager.h"
#include "Data\SolveMatrix.h"
#include "Data\Board.h"
#include "proj.win32\PauseGameDialog.h"

using namespace ui;
#define MAX_LIFE 3

PlayScene::PlayScene()
{
	scaleRate = 1;
}

PlayScene::~PlayScene()
{

}

Scene * PlayScene::createScene()
{
	auto scene = PlayScene::create();
	return scene;
}

bool PlayScene::init()
{
	if (!BaseScene::init()){
		return false;
	}

	this->initGui();
	this->addListener();

	return true;
}

void PlayScene::onClickHome(Ref* obj)
{
	CCLOG("onClickHome");
	SoundManager::playClickSound();
	this->onBackPress();
}

void PlayScene::onEnter()
{
	Scene::onEnter();
	this->initData();
	schedule(schedule_selector(PlayScene::updateProgressTimeBar), 0.5);
}

void PlayScene::initGui()
{
	auto layer = Layer::create();
	this->addChild(layer);

	Node* node = CSLoader::createNode("PlayScene.csb");
	layer->addChild(node);

	this->bgImage = (ui::Widget *)node->getChildByName("bgImage");
	this->itemPanel = (ui::Widget *) this->bgImage->getChildByName("panel_item");
	this->timeProgressBar = (ui::LoadingBar *) this->bgImage->getChildByName("bg_progress_time")->getChildByName("progress_time");
	this->initStatusPanel();
	initControlPanel();
}

void PlayScene::initControlPanel()
{
	float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
	
	Node *controlPanel = this->bgImage->getChildByName("panel_control");
	this->homeButton = (ui::Button *)controlPanel->getChildByName("btn_home");
	this->homeButton->setZoomScale(0.1f);
	this->homeButton->setPressedActionEnabled(true);
	this->homeButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onClickHome, this));

	ui::Button *pauseButton = (ui::Button *) controlPanel->getChildByName("btn_pause");
	pauseButton->setZoomScale(0.1f);
	pauseButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onPause, this));

	this->hintButton = (ui::Button *) controlPanel->getChildByName("btn_hint");
	this->hintButton->setZoomScale(0.1f);
	this->hintButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onHint, this));

	this->soundOnButton = (ui::Button *) controlPanel->getChildByName("btn_sound_on");
	this->soundOnButton->setZoomScale(0.1f);
	this->soundOnButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onSoundOn, this));

	this->soundOffButton = (ui::Button *) controlPanel->getChildByName("btn_sound_off");
	this->soundOffButton->setZoomScale(0.1f);
	this->soundOffButton->addClickEventListener(CC_CALLBACK_1(PlayScene::onSoundOff, this));

	this->hintNumLabel = (TextBMFont *)(controlPanel->getChildByName("ic_notification")->getChildByName("lb_num_hint"));
}

void PlayScene::onBackPress()
{

}

void PlayScene::initData()
{
	this->gameData = GameDataMgr::getInstance();
	this->board = new Board(8, 14, 28);
	this->board->initData();
	this->board->setGameData(this->gameData);
	this->board->addToBg(this->itemPanel);

	this->updateData();
}

void PlayScene::addListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->bgImage->getChildByName("panel_control"));
}

void PlayScene::initListNumber()
{
	int imageNum = 28;
	int height = 8;
	int width = 14;

	vector<int> countMatrix = SolveMatrix::createCardCountMatrix(width * height, imageNum);
	string str = "";
	for (int i = 0; i < imageNum; i++){
		str.append(" ").append(StringUtils::toString(countMatrix[i]));
	}
	log(str.c_str());

	str = "";
	cardMatrix = SolveMatrix::createMatrix(countMatrix, imageNum, height, width);
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			str.append(" ").append(StringUtils::toString(cardMatrix[i][j]));
		}
		str.append("\n");
	}
	log(str.c_str());
}

bool PlayScene::onTouchBegan(Touch* touch, cocos2d::Event* event)
{
	this->touchBeganPos = touch->getLocation();
	CCLOG("onTouchBegan (%f, %f)", this->touchBeganPos.x, this->touchBeganPos.y);
	return true;
}

void PlayScene::onTouchMoved(Touch* touch, cocos2d::Event* event)
{

}

void PlayScene::onTouchEnded(Touch* touch, cocos2d::Event* event)
{
	Vec2 pos = touch->getLocation();
	Vec2 pos2 = this->itemPanel->convertToNodeSpace(pos);
	CCLOG("onTouchEnded ( %f, %f), touchBegan (%f, %f)", pos.x, pos.y, this->touchBeganPos.x, this->touchBeganPos.y);
	this->board->setSelected(pos2);
}

void PlayScene::updateProgressTimeBar(float dt)
{
	gameData->remainTime -= dt;
	if (gameData->remainTime <= 0) {
		this->gameOver();
		return;
	}

	float percent = gameData->remainTime * 100 / gameData->gameTime;
	this->timeProgressBar->setPercent(percent);
}

void PlayScene::addKeyBoardListener()
{

}

void PlayScene::createNewGame()
{

}

void PlayScene::updateData()
{
	this->levelLabel->setString(StringUtils::toString(this->gameData->currentLevel));
	this->updateCurrentLife();
	this->updateScore();
	this->updateHint();
}

void PlayScene::loadData()
{

}

bool PlayScene::checkGameOver()
{
	return false;
}

void PlayScene::gameOver()
{

}

void PlayScene::onPause(Ref *obj)
{
	CCLOG("onPause");
	PauseGameDialog::getInstance()->startDialog(this);
}

void PlayScene::onSoundOn(Ref *obj)
{
	SoundManager::getInstance()->setMusicOn();
	this->updateVisibleSoundButton();
}

void PlayScene::onSoundOff(Ref *obj)
{
	SoundManager::getInstance()->setMusicOff();
	this->updateVisibleSoundButton();
}

void PlayScene::onHint(Ref *obj)
{
	this->board->hint();
}

void PlayScene::updateVisibleSoundButton()
{
	bool soundStatus = SoundManager::getInstance()->status;
	this->soundOnButton->setVisible(soundStatus == SOUND_OFF);
	this->soundOffButton->setVisible(soundStatus == SOUND_ON);
}

void PlayScene::updateCurrentLife()
{
	for (int i = 0; i < this->lilfeSpriteList.size(); i++){
		if (i < this->gameData->numLife){
			this->lilfeSpriteList.at(i)->setVisible(true);
		}
		else {
			this->lilfeSpriteList.at(i)->setVisible(false);
		}
	}
}

void PlayScene::initStatusPanel()
{
	Node *statusPanel = this->bgImage->getChildByName("panel_status");
	this->scoreLabel = dynamic_cast<ui::TextBMFont *>(statusPanel->getChildByName("lb_score"));
	this->levelLabel = dynamic_cast<TextBMFont *> (statusPanel->getChildByName("lb_level"));

	this->lilfeSpriteList.clear();
	for (int i = 0; i < MAX_LIFE; i++){
		char text[20];
		sprintf(text, "img_heart_%d", i + 1);
		Sprite *sprite = (Sprite *)(statusPanel->getChildByName(text));
		this->lilfeSpriteList.push_back(sprite);
		sprite->setVisible(true);
	}
}

void PlayScene::updateScore()
{
	this->scoreLabel->setString(StringUtils::toString(this->gameData->score));
}

void PlayScene::updateHint()
{
	this->hintNumLabel->setString(StringUtils::toString(this->gameData->numHint));
}


