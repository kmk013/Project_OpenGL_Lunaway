#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(Model *m) : GameObject(m), damage(1)
{
	this->layer = LBullet;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	myTime += RUNAMM->deltaTime;
	if (myTime > lifeTime) {
		Destroy();
		myCol->Destroy();
	}
	pos.z += speed*RUNAMM->deltaTime;
}

void Bullet::OnCollision(GameObject * ano)
{
	if (ano->layer==LCrush) {
		Destroy();
		myCol->Destroy();
	}
}