#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Player.h"

class Board :
	public GameObject
{
public:
	Board(Model* m);
	~Board();

	Player* p;
	Collider* myCol;

	void OnCollision(GameObject* ano);
};

