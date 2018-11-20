#include "stdafx.h"
#include "DistanceText.h"

DistanceText::DistanceText()
{
}

DistanceText::~DistanceText()
{
}

void DistanceText::Update() {
	for (int i = 0; i < 6; i++) {
		text[i]->isEnable=false;
	}
	Create();

}

void DistanceText::Create() {
	for (int i = 0; i < 6; i++) {

		text[i] = number[i][(p->killo / (int)pow(10, i)) % 10];
		text[i]->isEnable = true;
	}

}