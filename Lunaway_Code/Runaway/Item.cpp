#include "stdafx.h"
#include "Item.h"


Item::Item(Model* m) : GameObject(m)
{
	layer = LItem;
}


Item::~Item()
{
}

void Item::Update() {
	if (pos.z < p->pos.z - 60.0f) {
		Destroy();
		myCol->Destroy();
	}
}

void Item::OnCollision(GameObject* ano) {
	//¾ÆÀÌÅÛ È¹µæ
	if (ano->layer == LPlayer) {
		if (this->itemLayer == LWind) {
			p->speed += 4.0f;
			p->lrspeed += 2.0f;
		} else if (this->itemLayer == LAsteroid) {
			//°ø°Ý·Â Áõ°¡
			p->damage += 2;
		} else if (this->itemLayer == LStar) {
			p->hp += 5;
		} else if (this->itemLayer == LSun) {
			p->speed += 4.0f;
			p->lrspeed += 2.0f;
			p->damage += 2;
			p->hp += 3;
		}
		Destroy();
		myCol->Destroy();
	}
}