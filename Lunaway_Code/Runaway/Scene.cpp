#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"


Scene::Scene()
{
}


Scene::~Scene()
{
	for (auto &i : gameObjectList)
		delete i;
	for (auto &i : modelList)
		delete i;
	for (auto &i : uiList)
		delete i;
	for (auto&i : colliderList)
		delete i;
}

void Scene::Collide()
{
	int count = 0;
	for (auto &i : colliderList)
		i->checked = false;
	for (auto &i : colliderList) {
		for (auto &j : colliderList) {
			if (!j->checked&&i != j&&i->enable&&j->enable)
			{
				if (i->myGameObject&&j->myGameObject) {
					if (i->CheckCollision(j))
					{
						i->
							myGameObject->
							OnCollision(
								j->
								myGameObject
							);
						j->myGameObject->OnCollision(i->myGameObject);
					}
				}
			}
		}
		i->checked = true;
	}
}

void Scene::Update()
{
	for (auto &i : gameObjectList)
		i->Update();
	for (auto &i : uiList)
		i->Update();
}

void Scene::LateUpdate() {
	for (auto &i : gameObjectList)
		i->LateUpdate();
	for (auto &i : uiList)
		i->LateUpdate();
}

void Scene::PushBackGameObject(GameObject* g)
{
	gameObjectList.push_back(g);
}

void Scene::PushBackModel(Model* m)
{
	modelList.push_back(m);
}

void Scene::PushBackUI(UI * u)
{
	uiList.push_back(u);
}

void Scene::PushBackCollider(Collider * c)
{
	colliderList.push_back(c);
}

void Scene::FindAndDeleteObjects()
{
	for (auto i = gameObjectList.begin(); i != gameObjectList.end(); ++i)
	{
		if ((*i)->isDestroyed)
		{
			(*i)->OnDestroy();
			delete *i;
			(*i) = NULL;
			i = gameObjectList.erase(i);
			if (i == gameObjectList.end())
				break;
		}
	}

	for (auto i = uiList.begin(); i != uiList.end(); ++i)
	{
		if ((*i)->isDestroyed)
		{
			(*i)->OnDestroy();
			delete *i;
			(*i) = NULL;

			i = uiList.erase(i);
			if (i == uiList.end())
				break;
		}
	}

	for (auto i = colliderList.begin(); i != colliderList.end(); ++i)
	{
		if ((*i)->isDestroyed)
		{
			delete *i;
			(*i) = NULL;

			i = colliderList.erase(i);
			if (i == colliderList.end())
				break;
		}
	}
}