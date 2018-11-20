#include "stdafx.h"
#include "Board.h"

Board::Board(Model* m) : GameObject(m)
{
	
}

Board::~Board()
{
}

void Board::OnCollision(GameObject* ano) {
	if (ano->layer == LPlayer) {
		p->nowBoard = this;
	}
	if (isBreak) {
		if (ano->layer == LPlayer) {
			if (&((Player*)ano)->hp)
				((Player*)ano)->hp -= 10;
		}
	}
}