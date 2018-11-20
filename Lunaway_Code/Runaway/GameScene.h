#pragma once
#include "Scene.h"
#include "Player.h"
#include "BoardManager.h"
#include "StarManager.h"
#include "GameManager.h"
#include "ItemManager.h"
#include "DistanceText.h"
#include "SpeedText.h"
#include "BestScoreText.h"

class GameScene :
	public Scene
{
public:
	Model* boardModel;
	Model* boardModel2;
	Model* boardModel3;
	Model* characterM;
	Model* whiteStar;
public:
	StarManager* bgStars;
	Player* character;
	GameManager* gameManager;
	ItemManager* itemManager;
	BoardManager* boardManager;
	DistanceText* distanceText;
	SpeedText* speedText;
	BestScoreText* bsText;
	UI* backGround;

	//테스트오브젝트
	Model* testPlanetModel;

	Model* barsm[2];
	GameObject* bars[2];
	Model* moonM;
	GameObject* moon;

public:
	GameScene();
	~GameScene();
};

