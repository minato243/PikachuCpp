
#ifndef SelectThemeScene_h__
#define SelectThemeScene_h__

#include "cocos2d.h"
#include "platform\CCPlatformMacros.h"
#include "Base\BaseScene.h"
#include <vector>
#include "Data\GameDataMgr.h"

USING_NS_CC;
using namespace std;

class SelectThemeScene : BaseScene
{
public:
	SelectThemeScene();
	~SelectThemeScene();

	vector<Sprite*> *selectSpriteList;
	GameDataMgr *gameData;

	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(SelectThemeScene);
	
	void initGui();
	void initData();
	void updateData();

	void onSelectTheme(Ref *obj);
	void onClickExit(Ref *obj);
	void onClickDone(Ref *obj);
	virtual void onBackPress();
protected:
private:
};

#endif