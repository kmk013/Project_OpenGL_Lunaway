#pragma once
#include "EmptyObject.h"
#include "Board.h"
#include "Player.h"

class BoardManager : public EmptyObject
{
public:
	int currentLine;
public:
	BoardManager();
	~BoardManager();

	Board* boards[6][40];
	Board* nowBoard;
	Model* model1;
	Model* model2;
	Model* model3;
	Player* p;
	int phase;

	void Update();
	void PhaseChange(int phase);
};

