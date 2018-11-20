#include "stdafx.h"
#include "Gem.h"


Gem::Gem(Model* m, int indexI, int indexJ) : Item(m)
{
	this->indexI = indexI;
	this->indexJ = indexJ;
}


Gem::~Gem()
{
}

void Gem::Update() {
	if (pos.z < p->pos.z - 60.0f) {
		Destroy();
		myCol->Destroy();
	}
}

void Gem::OnCollision(GameObject* ano) {
	if (ano->layer == LPlayer) {
		im->getGem[indexI][indexJ] = true;
		FILE* f;
		f = fopen("Resource/gem.sav", "w");
		if (f) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 8; j++) {
					fprintf(f, "%d", im->getGem[i][j]);
				}
			}
			fclose(f);
		}
		Destroy();
		myCol->Destroy();
	}
}