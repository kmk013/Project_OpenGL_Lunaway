#include "stdafx.h"
#include "Planet.h"
#include "Item.h"
#include "Gem.h"
#include <time.h>
#include "Bullet.h"

Planet::Planet(Model* m) : GameObject(m), hp(3)
{
	layer = LCrush;
}


Planet::~Planet()
{
}

void Planet::Update()
{
	if (pos.z < p->pos.z - 60.0f) {
		Destroy();
		myCol->Destroy();
	}
	if (hp <= 0) {
		p->damage += 1;
		int num = rand() % 3;
		if (num == 0) {
			CreateItem(rand() % 99);
		}
		Destroy();
		myCol->Destroy();
	}
}

void Planet::OnCollision(GameObject* ano)
{
	if (ano->layer == LBullet) {		
		hp -= ((Bullet*)ano)->damage;
	}

	if (ano->layer == LPlayer) {
		if (&((Player*)ano)->hp)
			((Player*)ano)->hp -= 2;
		Destroy();
		myCol->Destroy();
	}
}

//아이템 생성 함수
void Planet::CreateItem(int randNum) {
	if (randNum >= 0 && randNum < 99) {
		Item *a;
		if (randNum >= 0 && randNum < 30) {
			a = new Item(im->itemModel[0]);
			a->itemLayer = LWind;
		}
		else if (randNum >= 30 && randNum < 60) {
			a = new Item(im->itemModel[1]);
			a->itemLayer = LAsteroid;
		}
		else if (randNum >= 60 && randNum < 90) {
			a = new Item(im->itemModel[2]);
			a->itemLayer = LStar;
		}
		else if (randNum >= 90 && randNum < 99) {
			a = new Item(im->itemModel[3]);
			a->itemLayer = LSun;
		}
		a->SetPos(pos.x, pos.y, pos.z);
		a->p = p;
		CURRENTSCENE->PushBackGameObject(a);
		a->myCol = new Collider(a, 17.0f);
		CURRENTSCENE->PushBackCollider(a->myCol);
	}
	else if (randNum >= 99) {
		int indexI = rand() % 3;
		int indexJ = rand() % 8;
		Gem *b = new Gem(im->gemModel[indexI][indexJ], indexI, indexJ);

		b->itemLayer = LGem;
		b->SetPos(pos.x, pos.y, pos.z);
		b->p = p;
		b->im = im;
		CURRENTSCENE->PushBackGameObject(b);
		if (indexI == 0) {
			b->myCol = new Collider(b, 19.0f, 1.0f);
		}
		else if (indexI == 1) {
			b->myCol = new Collider(b, 16.0f, 1.0f);
		}
		else if (indexI == 2) {
			b->myCol = new Collider(b, 16.0f, 1.0f);
		}
		CURRENTSCENE->PushBackCollider(b->myCol);
	}
}