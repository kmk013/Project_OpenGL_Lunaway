#pragma once
#include "Scene.h"
#define RUNASCENEM SceneManager::GetInstance()
#define CURRENTSCENE RUNASCENEM->currentScene

class Scene;

class SceneManager
{
public:
	
private:
	
	Scene* nextScene;
public:
	Scene* currentScene;
public:
	SceneManager();
	~SceneManager();
	void NewScene(Scene* nextScene);
	void ChangeScene(Scene* nextScene);
	void DestroyCurrentScene();

public:
	bool _isChangeSceneCalled;
	void _sceneChange();
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}
};

