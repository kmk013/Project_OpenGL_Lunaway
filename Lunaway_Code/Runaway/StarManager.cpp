#include "stdafx.h"
#include "StarManager.h"
#include "MessageManager.h"


StarManager::StarManager() : distance(400.0f)
{
}


StarManager::~StarManager()
{
}

void StarManager::SetRandomPos(int index)
{
	float tx, ty, tz;
	float rx, rz;	//구면좌표계 x축 각도, z축 각도

	//구면좌표계
	rx = Randomer(-6.28f, 6.28f);
	rz = Randomer(-3.14f, 3.14f);	

	//구면좌표계 -> 직교좌표계
	tx = sin(rz)*cos(rx);
	ty = sin(rz)*sin(rx);
	tz = cos(rz);

	starPos[index].x = tx*distance;
	starPos[index].y = ty*distance;
	starPos[index].z = tz*distance;
}

void StarManager::Update()
{
	myTimer += RUNAMM->deltaTime;
	if (myTimer >= 10.0f) {
		myTimer -= 10.0f;
		SetRandomPos(nextStar++);
		if (nextStar >= starcount)
			nextStar = 0;
	}
	if (p) {
		for (int i = 0; i < starcount; ++i) {
			stars[i]->SetPos(starPos[i].x + p->pos.x, starPos[i].y, starPos[i].z + p->pos.z);
		}
	}
	else {
		for (int i = 0; i < starcount; ++i) {
			stars[i]->SetPos(starPos[i].x, starPos[i].y, starPos[i].z);
		}
	}
	
}

float StarManager::Randomer(float min, float max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(min, max);

	return range(rnd);
}
