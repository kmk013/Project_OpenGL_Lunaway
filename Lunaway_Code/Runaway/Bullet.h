#pragma once
#include "GameObject.h"
class Bullet :
	public GameObject
{
public:
	Collider* myCol;
	float speed=30.0f;
	float lifeTime = 3.0f;
	float myTime = 0.0f;
	int damage;
public:
	Bullet(Model *m);
	~Bullet();
	void Update();
	void OnCollision(GameObject* ano);
};

