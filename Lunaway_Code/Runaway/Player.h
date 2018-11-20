#pragma once
#include "GameObject.h"

class BoardManager;

class Player :
	public GameObject
{
public:
	Model* bulletModel;
	GameObject* nowBoard;

	GameObject* hpBar;
	GameObject* mpBar;
	GameObject* moon;
	BoardManager* boardManager;
public:
	Player(Model* MyModel);
	~Player();

	void Update();

	int killo;
	int phase;
	bool isGameOver;

	float speedTImer;
	float speed = 30.0f;
	float lrspeed = 20.0f;
	int hp = 10;
	int maxhp = 10;
	int mp = 10;
	int damage;
	float zDistance = 50.0f;
	int bestScore;
	bool readyToEnd = false;
	bool isEnded = false;
	bool isSplit = true;

	//ÃÑ¾Ë µô·¹ÀÌ °ü·Ã
	float shootDelay = 0.2f;
	float shootTimeCheck = 0.0f;

	void MoveFB(int wtg);
	void MoveFBRun(int wtg);
	void MoveLR(int wtg);
	void Shoot();
	void Split();

	Collider* myCollider;
	void OnCollision(GameObject* ano);
};

