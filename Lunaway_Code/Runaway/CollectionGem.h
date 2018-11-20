#pragma once
#include "GameObject.h"
#include "UI.h"

class CollectionGem :
	public GameObject
{
public:
	UI* collector;
	UI* spriteGem[3][8];

	CollectionGem();
	~CollectionGem();
};

