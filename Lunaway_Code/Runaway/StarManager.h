#pragma once
#include "GameObject.h"
#include "Player.h"
class StarManager :
	public GameObject
{
	float distance = 400.0f;
	float anglexz = 0.0f;
	float angley = 0.0f;
	float myTimer = 0.0f;
	int nextStar = 0;
public:
	int starcount = 20;
	GameObject* stars[20];
	Vec3 starPos[20];
	Player* p;
	StarManager();
	~StarManager();
	void SetRandomPos(int index);
	void Update();
	float Randomer(float min, float max);
};

