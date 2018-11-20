#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Player.h"

class ShootingStar :
	public GameObject
{
public:
	ShootingStar(Model* m);
	~ShootingStar();

	Collider* myCol;
	Player* p;

	float speed;

	void Update();
	void OnCollision(GameObject* ano);
};

