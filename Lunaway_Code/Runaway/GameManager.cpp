#include "stdafx.h"
#include "GameManager.h"
#include "Planet.h"
#include "Stone.h"
#include "ShootingStar.h"
#include <time.h>

GameManager::GameManager() : checkTimer(0.0f),checkpoint(0)
{
	srand((unsigned)time(NULL));
	playerDistance = 0;
	distanceDivide = 100;
}

GameManager::~GameManager()
{
}

void GameManager::LateUpdate() {
	checkTimer += RUNAMM->deltaTime;
	if (checkTimer>=8.0f) {
		checkpoint++;
		checkTimer = 0.0f;
	}
	playerDistance = (int)p->pos.z;
	CreatePosition = boardManager->currentLine + 38;
	if (CreatePosition >= 39)
		CreatePosition -= 39;

	//青己, 家青己, 蜡己, 墩赴 辨 磊悼 积己 窃荐
	if (distanceDivide <= playerDistance) {
		int num = rand() % 100;
		if (num >= 0 && num < 35) {         //青己
			CreatePlanet(rand() % 6);
		}		
		else if (num >= 35 && num < 70) {   //蜡己
			CreateShootingStar();
		}
		else if (num >= 70 && num < 80) {   //家青己
			CreateStone();
		}
		else {                              //墩赴 辨
			CreatebreakBoard();
		}
		distanceDivide += 100;
	}
}

void GameManager::CreatePlanet(int randNum) {
	printf("青己 积己\n");
	Planet *a = new Planet(planetModel[randNum]);
	int boardX = rand() % 6;
	a->SetPos(boardManager->boards[boardX][CreatePosition]->pos.x, 5.0f, boardManager->boards[boardX][CreatePosition]->pos.z);
	a->im = itemManager;
	a->p = p;
	a->hp += checkpoint;
	CURRENTSCENE->PushBackGameObject(a);
	a->myCol = new Collider(a, 12.0f);
	a->myCol->myGameObject = a;
	CURRENTSCENE->PushBackCollider(a->myCol);
}

void GameManager::CreateStone() {
	printf("家青己 积己\n");
	Stone *a = new Stone(stoneModel);
	a->SetPos(boardManager->boards[3][CreatePosition]->pos.x, 5.0f, boardManager->boards[2][CreatePosition]->pos.z);
	a->hp += checkpoint*3;
	a->p = p;
	CURRENTSCENE->PushBackGameObject(a);
	a->myCol = new Collider(a, 96.0f, 48.0f);
	a->myCol->myGameObject = a;
	CURRENTSCENE->PushBackCollider(a->myCol);
}

void GameManager::CreateShootingStar() {
	printf("蜡己 积己\n");
	int boardX = rand() % 6;
	ShootingStar *a = new ShootingStar(shootingStarModel);
	a->SetPos(boardManager->boards[boardX][CreatePosition]->pos.x, 5.0f, boardManager->boards[boardX][CreatePosition]->pos.z);
	a->p = p;
	a->speed = p->speed;
	CURRENTSCENE->PushBackGameObject(a);
	a->myCol = new Collider(a, 12.0f, 35.0f);
	a->myCol->myGameObject = a;
	CURRENTSCENE->PushBackCollider(a->myCol);
}

void GameManager::CreatebreakBoard() {
	printf("墩赴 辨 积己\n");
	int boardX = rand() % 6;
	boardManager->boards[boardX][CreatePosition]->useModel = false;
	boardManager->boards[boardX][CreatePosition]->isBreak = true;
	boardManager->boards[boardX][CreatePosition]->myCol = new Collider(boardManager->boards[boardX][CreatePosition], 12.0f);
	CURRENTSCENE->PushBackCollider(boardManager->boards[boardX][CreatePosition]->myCol);
}