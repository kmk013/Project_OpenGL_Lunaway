#pragma once
#include "Item.h"
#include "Model.h"
#include "ItemManager.h"

class Gem :
	public Item
{
public:
	Gem(Model* m, int indexI, int indexJ);
	~Gem();

	ItemManager* im;

	int indexI, indexJ;

	void Update();
	void OnCollision(GameObject* ano);
};

