#pragma once
#include "GameObject.h"
#include "Player.h"
#include "UI.h"

class SpeedText :
	public GameObject
{
public:
	UI* text[3];
	UI* number[3][10];
	Player *p;

	SpeedText();
	~SpeedText();

	void Update();
	void Create();
};

