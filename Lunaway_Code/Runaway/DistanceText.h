#pragma once
#include "GameObject.h"
#include "Player.h"
#include "UI.h"

class DistanceText :
	public GameObject
{
public:
	UI* text[6];
	UI* number[6][10];
	Player* p;

	DistanceText();
	~DistanceText();

	void Update();
	void Create();
};

