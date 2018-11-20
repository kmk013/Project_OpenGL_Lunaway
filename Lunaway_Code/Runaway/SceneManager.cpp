#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager() : _isChangeSceneCalled(false)
{

}


SceneManager::~SceneManager()
{
}

void SceneManager::NewScene(Scene * nextScene)
{
	currentScene = nextScene;
}

void SceneManager::ChangeScene(Scene * NextScene)
{
	_isChangeSceneCalled = true;
	nextScene = NextScene;	
}

void SceneManager::_sceneChange()
{
	DestroyCurrentScene();
	NewScene(nextScene);
	_isChangeSceneCalled = false;
}

void SceneManager::DestroyCurrentScene()
{
	delete currentScene;
}

