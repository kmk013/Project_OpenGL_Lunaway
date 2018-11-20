#pragma once
#include "stdafx.h"
#include "RUNAMath.h"
#include "GameObject.h"

class GameObject;

class Collider
{
public:
	Vec2 lt;
	Vec2 rb;

	Vec2 dist;
	bool enable = true;
	bool checked = false;
	bool isDestroyed;
	GameObject* myGameObject;
public:
	Collider(GameObject* myGO, float length);
	Collider(GameObject* myGO, float width, float height);
	Collider(GameObject* myGO, float length, float distX, float distZ);	//중앙으로부터 콜라이더 거리
	~Collider();
	bool CheckCollision(Collider* ano);
	void Destroy();
};