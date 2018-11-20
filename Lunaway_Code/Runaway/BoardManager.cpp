#include "stdafx.h"
#include "BoardManager.h"

BoardManager::BoardManager() : phase(1)
{
	currentLine = 0;
}


BoardManager::~BoardManager()
{
}

void BoardManager::Update()
{
	if ((int)p->pos.z > (int)(pos.z + 16.0f)) {
		pos.z += 16.0f;
		for (int i = 0; i < 6; i++) {
			if(!boards[i][currentLine]->useModel)
				boards[i][currentLine]->useModel = true;
			if (boards[i][currentLine]->isBreak)
				boards[i][currentLine]->isBreak = false;
			if (boards[i][currentLine]->myCol)
				boards[i][currentLine]->myCol->Destroy();
			boards[i][currentLine]->pos.z += 40.0f * 16.0f;
		}

		currentLine++;
		if (currentLine >= 40)
			currentLine = 0;
	}
}

void BoardManager::PhaseChange(int phase)
{
	if (phase == 1) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 40; j++) {
				boards[i][j]->myModel = model1;
			}
		}
	}
	if (phase == 2) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 40; j++) {
				boards[i][j]->myModel = model2;
			}
		}
	}
	if (phase == 3) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 40; j++) {
				boards[i][j]->myModel = model3;
			}
		}
	}
}
