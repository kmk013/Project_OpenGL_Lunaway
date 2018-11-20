#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++)
			getGem[i][j] = false;
}


ItemManager::~ItemManager()
{
}
