/*Created by thaod*/
#include "GameDataMgr.h"
#include "base\GameConstant.h"

#define GAME_DATA_KEY "game_data"
#define HIGH_SCORE_KEY "game_score"

GameDataMgr *gameDataMgrInstance = NULL;

GameDataMgr::GameDataMgr()
{
	this->mode = 1;
	this->currentLevel = 1;
	this->score = 0;
	this->numLife = 3;
	this->numHint = 3;
	this->theme = 0;
	this->remainTime = 150;
	this->gameTime = 150;
	this->loadHighScore();
}

GameDataMgr::~GameDataMgr()
{

}

void GameDataMgr::resetData()
{
	this->currentLevel = 0;
}

void GameDataMgr::gameOver()
{

}


void GameDataMgr::setMode(int mode)
{
	this->mode = mode;
}


void GameDataMgr::setTheme(int theme)
{
	this->theme = theme;
}

std::string GameDataMgr::loadData()
{
	string gameDataStr = GameDataMgr::getCache(GAME_DATA_KEY + StringUtils::toString(this->mode), "");
	return gameDataStr;
}

void GameDataMgr::saveData(int mode, std::string dataStr)
{
	GameDataMgr::saveCache(GAME_DATA_KEY + StringUtils::toString(mode), dataStr);
}

void GameDataMgr::saveHighScore()
{
	GameDataMgr::saveCache(string(HIGH_SCORE_KEY) + StringUtils::toString(this->mode), 
		StringUtils::toString(this->score));
}

void GameDataMgr::updateHighScore(int score, int title)
{
	if (score > this->score){
		if (score > this->score){
			this->score = score;
		}

		this->saveHighScore();
	}
}

void GameDataMgr::loadHighScore()
{
	string highScoreStr = GameDataMgr::getCache(string(HIGH_SCORE_KEY) + StringUtils::toString(this->mode), StringUtils::toString(0));
	this->score = atoi(highScoreStr.c_str());
}

GameDataMgr * GameDataMgr::getInstance()
{
	if (gameDataMgrInstance == NULL){
		gameDataMgrInstance = new GameDataMgr();
	}

	return gameDataMgrInstance;
}


void GameDataMgr::saveCache(string key, string value)
{
	CCUserDefault::getInstance()->setStringForKey(key.c_str(), value);
	CCUserDefault::getInstance()->flush();
}

std::string GameDataMgr::getCache(string key, string defaultValue)
{
	string value = CCUserDefault::getInstance()->getStringForKey(key.c_str(), defaultValue);
	return value;
}

void GameDataMgr::addScore(int num)
{
	this->score += num;
}

