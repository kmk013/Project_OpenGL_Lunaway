#pragma once
#include "GraphicManager.h"
#include "Model.h"
#include "UI.h"
#include "SceneManager.h"
#include "Collider.h"

//Scene : 장면
//장면의 모든 것을 관리하는 객체

class GameObject;
class Collider;

class Scene
{
public:
	enum SceneNumber {
		NMainScene,
		NGameScene
	};
public:
	SceneNumber sceneNumber;
public : 
	list<GameObject*> gameObjectList;
	list<Model*> modelList;
	list<UI*> uiList;
	list<Collider*> colliderList;
	

public:
	Scene();
	virtual ~Scene();
	void Collide();
	void Update();
	void LateUpdate();
	void PushBackGameObject(GameObject* g);
	void PushBackModel(Model* m);
	void PushBackUI(UI* u);
	void PushBackCollider(Collider* c);
	void FindAndDeleteObjects();
};

