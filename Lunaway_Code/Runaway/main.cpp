#include "stdafx.h"
#include "Runaway.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "MainScene.h"
#include "GameScene.h"
int main() {
	//������ Ǯ��ũ������ �����մϴ�.
	//�ڵ����� �ػ󵵸� �����մϴ�.
	if (RUNAWM->WindowInit(TRUE, L"Runaway", 1920, 1080, 32, true, false)) {
		RUNAGLM->PrepareRender();
		RUNASCENEM->NewScene(new MainScene());
		return RUNAWM->MainLoop();
	}
	else
		return 0;
	//���α׷� ����� ó���� RUNAMM->CloseMyWindow()
}
