#include "stdafx.h"
#include "SpeedText.h"


SpeedText::SpeedText()
{
}


SpeedText::~SpeedText()
{
	
}

void SpeedText::Update() {
	for (int i = 0; i < 3; i++) {
		text[i]->isEnable = false;
	}
	Create();
}

void SpeedText::Create() {
	for (int i = 0; i < 3; i++) {

		text[i] = number[i][((int)p->speed / (int)pow(10, i)) % 10];
		text[i]->isEnable = true;
	}
}