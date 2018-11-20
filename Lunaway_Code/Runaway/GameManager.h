#pragma once
#include "EmptyObject.h"
#include "Player.h"
#include "Model.h"
#include "BoardManager.h"
#include "ItemManager.h"

class GameManager :
	public EmptyObject
{
public:
	GameManager();
	~GameManager();

	BoardManager* boardManager;
	ItemManager* itemManager;
	Player* p;
	Model* planetModel[6];
	Model* stoneModel;
	Model* shootingStarModel;

	int playerDistance;
	int distanceDivide;
	int CreatePosition;

	float checkTimer;
	int checkpoint;

	void LateUpdate();

	void CreatePlanet(int randNum);
	void CreateStone();
	void CreateShootingStar();
	void CreatebreakBoard();
};

