#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "stdafx.h"
#include "GameObject.h"
#include "Model.h"
#include "GraphicManager.h"
using namespace std;

#define RUNAOBJM ObjectManager::GetInstance()

class GameObject;

class ObjectManager
{
public:
	list<GameObject> gameObjects;

public:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}
};

#endif

