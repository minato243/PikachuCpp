#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include "platform\CCPlatformMacros.h"

USING_NS_CC;
using namespace CocosDenshion;


SoundManager::SoundManager()
{
	this->status = SOUND_ON;
}

SoundManager::~SoundManager()
{

}

int SoundManager::playSound(string soundPath){
	if (this->status == false) return 0;
	int tag = SimpleAudioEngine::getInstance()->playEffect(soundPath.c_str(), false);
	return tag;
}

void SoundManager::stopSound(int tag){
	   SimpleAudioEngine::getInstance()->stopEffect(tag);
}

void SoundManager::stopAllSound(){
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundManager::playMusic(string musicPath){
	if (this->status == SOUND_OFF) return;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(musicPath.c_str());
}

void SoundManager::stopMusic(){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundManager::setMusicOn(){
	this->status = SOUND_ON;
	//SoundManager.playBackgroundMusic();
}

void SoundManager::setMusicOff(){
	this->status = SOUND_OFF;
	this->stopMusic();
}

SoundManager *soundMgrInstance = NULL;

SoundManager *SoundManager::getInstance(){	
	if (soundMgrInstance == NULL){
		soundMgrInstance = new SoundManager();
	}
	return soundMgrInstance;
}

void SoundManager::playClickSound(){
	CCLOG("playClickSound");
	SoundManager::getInstance()->playSound("sound/click1.mp3");
}

void SoundManager::playMoveSound(){
	CCLOG("playMoveSound");
	soundMgrInstance->playSound("sound/win.mp3");
};

void SoundManager::pauseMusic(){
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
};

void SoundManager::resumeMusic(){
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
};

void SoundManager::playPairSound()
{
	log("playPairSound");
}

void SoundManager::playLevelSound()
{
	log("playLevelSound");
}

void SoundManager::playNoSound()
{
	log("playNoSound");
}

void SoundManager::playWrongSound()
{
	log("play wrong sound");
}

