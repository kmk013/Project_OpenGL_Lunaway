#pragma once
#include "Player.h"
#include "Model.h"
#include "Player.h"

class SplitPlayer : public Player
{
public:
	SplitPlayer(Model* m, bool isL);
	~SplitPlayer();

	Player *p;
	Collider* myCol;

	int isLeft;
	float currentDistance = 0.0f;
	float splitspeed = 30.0f;

	float shootDelay = 0.2f;
	float shootTimeCheck = 0.0f;

	float destroyTimeCheck = 0.0f;
	float destroyDelay = 3.0f;


	void MoveFB(int wtg);
	void MoveFBRun(int wtg);
	void MoveLR(int wtg);
	void Shoot();

	void Update();
	void OnCollision(GameObject* ano);

	void Combine();
	void SplitMove();
};