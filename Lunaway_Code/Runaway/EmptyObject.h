#pragma once
#include "GameObject.h"
class EmptyObject :
	public GameObject
{
public:
	EmptyObject();
	~EmptyObject();
	void Update();
	int k = 0;
};

