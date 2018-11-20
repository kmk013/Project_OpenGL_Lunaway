#pragma once
#include "GameObject.h"
class BestScoreText :
	public GameObject
{
public:
	UI* text[6];
	UI* number[6][10];
	Player* p;
	BestScoreText();
	~BestScoreText();
};

