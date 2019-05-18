#ifndef SceneManager_h__
#define SceneManager_h__

#include "cocos2d.h"

USING_NS_CC;

class SceneManager{
public:
	Scene *currentScene;

	SceneManager();
	~SceneManager();

	void changeScene(int sceneId);

	static SceneManager *getInstance();
	static void deystroyInstance();
};

#endif