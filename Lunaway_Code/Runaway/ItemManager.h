#pragma once
#include "EmptyObject.h"
#include "Model.h"

class ItemManager :
	public EmptyObject
{
public:
	Model* itemModel[4];
	Model* gemModel[3][8];

	bool getGem[3][8];
public:
	ItemManager();
	~ItemManager();
};

