#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Player.h"

class Item : public GameObject
{
public:
	
public:
	Collider* myCol;
	Player* p;
	ItemLayout itemLayer;

	Item(Model *m);
	~Item();

	void Update();
	void OnCollision(GameObject* ano);
};

