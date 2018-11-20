#include "stdafx.h"
#include "ShootingStar.h"


ShootingStar::ShootingStar(Model* m) : GameObject(m)
{
	layer = LCrush;
}


ShootingStar::~ShootingStar()
{
}

void ShootingStar::Update() {
	pos.z -= 0.5f;
	//rot.z값 변경을 해봤지만 모델 중심축이 약간 문제있음
	//rot.z += 0.1f;

	if (pos.z < p->pos.z - 60.0f) {
		Destroy();
		myCol->Destroy();
	}
}

void ShootingStar::OnCollision(GameObject* ano) {
	if (ano->layer == LPlayer) {
		if (&((Player*)ano)->hp)
			((Player*)ano)->hp -= 4;
		Destroy();
		myCol->Destroy();
	}
}