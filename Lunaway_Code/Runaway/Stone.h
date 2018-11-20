#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Player.h"

class Stone :
	public GameObject
{
public:
	Stone(Model* m);
	~Stone();
	int hp;
	Collider* myCol;
	Player* p;

	void Update();
	void OnCollision(GameObject* ano);
};

