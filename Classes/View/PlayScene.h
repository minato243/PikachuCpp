#ifndef PlayScene_h__
#define PlayScene_h__

#include "cocos2d.h"
#include "2d\CCLabelBMFont.h"
#include "ui\UIButton.h"
#include "deprecated\CCDeprecated.h"
#include "2d\CCLabel.h"
#include "ui\UITextBMFont.h"
#include "math\Vec2.h"
#include "Base\BaseScene.h"
#include "Item.h"
#include "Data\Board.h"
#include "ui\UILoadingBar.h"
#include "Data\GameDataMgr.h"

using namespace std;
using namespace ui;
USING_NS_CC;

class PlayScene : public BaseScene{
public:
	PlayScene();
	~PlayScene();

	ui::Widget *bgImage;
	ui::TextBMFont *scoreLabel;
	TextBMFont *levelLabel;
	vector<Sprite *> lilfeSpriteList;
	ui::Button *homeButton, *soundOnButton, *soundOffButton, *pauseButton, *hintButton;
	TextBMFont *hintNumLabel;
	ui::Widget *itemPanel;
	ui::LoadingBar *timeProgressBar;

	Board *board;
	GameDataMgr *gameData;

	vector<vector<Item *>> itemMatrix;
	vector <vector<int>> cardMatrix;
	Vec2 touchBeganPos;

	string savedData;

	
	float scaleRate;

	static Scene *createScene();
	CREATE_FUNC(PlayScene);
	virtual bool init();
	void initGui();
	void initStatusPanel();
	void initControlPanel();
	void initListNumber();
	void initData();
	void addListener();
	void addKeyBoardListener();
	void createNewGame();
	
	
	void updateData();
	void loadData();
	void updateCurrentLife();
	void updateScore();
	void updateHint();

	string getSpriteFrameNameForNumber(int number);
	bool checkGameOver();
	void gameOver();

	virtual void onEnter();
	void onClickHome(Ref *obj);
	void onPause(Ref *obj);
	void onSoundOn(Ref *obj);
	void onSoundOff(Ref *obj);
	void onHint(Ref *obj);
	bool onTouchBegan(Touch* touch, cocos2d::Event* event);
	void onTouchMoved(Touch* touch, cocos2d::Event* event);
	void onTouchEnded(Touch* touch, cocos2d::Event* event);
	void onBackPress();

	void updateProgressTimeBar(float dt);
	void updateVisibleSoundButton();
};
#endif