#ifndef GameDataMgr_h__
#define GameDataMgr_h__

#include "cocos2d.h"
#include <string>
#include "Base\DataStruct.h"

#define MODE_CLASSIC	0
#define MODE_MORDEN		1

USING_NS_CC;
using namespace std;

class GameDataMgr{
public:
	GameDataMgr();
	~GameDataMgr();

	int mode;
	int currentLevel;
	int score;
	short numHint;
	short numLife;
	short theme;
	float remainTime;
	float gameTime;

	GameStatus status;

	void resetData();
	void gameOver();
	std::string loadData();
	void saveData(int mode, std::string dataStr);
	void saveHighScore();
	void updateHighScore(int score, int title);
	void loadHighScore();
	void setMode(int mode);
	void setTheme(int theme);
	void collect();
	void addScore(int num);

	static std::string getCache(std::string key, std::string defaultValue);
	static void saveCache(std::string key, std::string value);
	static GameDataMgr *getInstance();
	void useHint();
};
#endif
