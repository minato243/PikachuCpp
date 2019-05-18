#include "SelectThemeScene.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "ui\UIButton.h"
#include "Data\GameDataMgr.h"
#include "SceneManager.h"
#include "Base\GameConstant.h"

#define TAG_SELECT_THEME 100
#define NUM_THEME	3


SelectThemeScene::SelectThemeScene()
{
	this->selectSpriteList = new vector<Sprite*>();
}

SelectThemeScene::~SelectThemeScene()
{
	this->selectSpriteList->clear();
	delete this->selectSpriteList;
}


Scene * SelectThemeScene::createScene()
{
	auto scene = SelectThemeScene::create();
	return scene;
}

bool SelectThemeScene::init(){
	if (!BaseScene::init()){
		return false;
	}

	this->initGui();
	this->initData();
	//this->addListener();
	return true;
}

void SelectThemeScene::initGui()
{
	Node* node = CSLoader::createNode("SelectThemeScene.csb");
	this->addChild(node);

	Node *bgImage = node->getChildByName("bgImage");

	ui::Button *doneButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_done"));
	float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
	doneButton->setZoomScale(0.1f * scaleX);
	doneButton->setPressedActionEnabled(true);
	doneButton->addClickEventListener(CC_CALLBACK_1(SelectThemeScene::onClickDone, this));
	
	for (int i = 0; i < NUM_THEME; i++){
		char text[100];
		sprintf(text, "btn_animal_%d", i);
		ui::Button *button = static_cast<ui::Button*>(bgImage->getChildByName(text));
		button->setZoomScale(0.1f * scaleX);
		button->setPressedActionEnabled(true);
		button->addClickEventListener(CC_CALLBACK_1(SelectThemeScene::onSelectTheme, this));
		button->setTag(TAG_SELECT_THEME + i);
	}

	ui::Button *exitButton = static_cast<ui::Button*>(bgImage->getChildByName("btn_back"));
	exitButton->setZoomScale(0.1f * scaleX);
	exitButton->setPressedActionEnabled(true);
	exitButton->addClickEventListener(CC_CALLBACK_1(SelectThemeScene::onClickExit, this));

	for (int i = 0; i < NUM_THEME + 1; i++){
		char text[100];
		sprintf(text, "img_check_animal_%d", i);
		Sprite *sprite = (Sprite *) bgImage->getChildByName(text);
		this->selectSpriteList->push_back(sprite);
	}
}

void SelectThemeScene::initData()
{
	gameData = GameDataMgr::getInstance();
	this->updateData();
}

void SelectThemeScene::updateData()
{
	for (short i = 0; i < NUM_THEME; i++){
		this->selectSpriteList->at(i)->setVisible(i == gameData->theme);
	}
}

void SelectThemeScene::onSelectTheme(Ref *obj)
{
	int tag = ((ui::Button *)obj)->getTag();
	gameData->setTheme(tag - TAG_SELECT_THEME);
	this->updateData();
}

void SelectThemeScene::onClickExit(Ref *obj)
{
	this->onBackPress();
}

void SelectThemeScene::onClickDone(Ref *obj)
{
	SceneManager::getInstance()->changeScene(PLAY_SCENE);
}

void SelectThemeScene::onBackPress()
{
	SceneManager::getInstance()->changeScene(MENU_SCENE);
}


