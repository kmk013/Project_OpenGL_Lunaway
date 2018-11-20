#pragma once
#include "GameObject.h"
#include "Model.h"
#include "ItemManager.h"
#include "Player.h"

class Planet :
	public GameObject
{
public:
	Player* p;
	ItemManager* im;
	Collider* myCol;
	int hp;
public:
	Planet(Model* m);
	~Planet();

	void Update();
	void OnCollision(GameObject* ano);

	void CreateItem(int randNum);
};

