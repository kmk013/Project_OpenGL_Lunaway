#include "stdafx.h"
#include "Stone.h"
#include "Bullet.h"


Stone::Stone(Model* m) : GameObject(m), hp(10)
{
	layer = LCrush;
}


Stone::~Stone()
{
}

void Stone::Update() {
	if (pos.z < p->pos.z - 60.0f) {
		Destroy();
		myCol->Destroy();
	}
	if (hp <= 0) {
		p->speed += 1.0f;
		p->damage += 3.0f;
		Destroy();
		myCol->Destroy();
	}
}

void Stone::OnCollision(GameObject* ano) {
	if (ano->layer == LPlayer) {
		if (&((Player*)ano)->hp)
			((Player*)ano)->hp -= 3;
		Destroy();
		myCol->Destroy();
	}
	if (ano->layer == LBullet) {
		hp -= ((Bullet*)ano)->damage;
	}
}