#ifndef SoundManager_h__
#define SoundManager_h__

#define SOUND_ON true
#define SOUND_OFF false

#include <string>
#include "cocos2d.h"

using namespace std;

class SoundManager{
public:
	SoundManager();
	~SoundManager();
	
	bool status;

	int playSound(std::string soundPath);
	void stopSound(int tag);
	void stopAllSound();
	void playMusic(std::string musicPath);
	void stopMusic();
	void setMusicOn();
	void setMusicOff();

	static SoundManager *getInstance();
	static void playClickSound();
	static void playMoveSound();
	static void pauseMusic();
	static void resumeMusic();
	static void playPairSound();
	static void playLevelSound();
	static void playNoSound();
	static void playWrongSound();
};
#endif