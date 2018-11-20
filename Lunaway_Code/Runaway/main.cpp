#include "stdafx.h"
#include "Runaway.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "MainScene.h"
#include "GameScene.h"
int main() {
	//게임은 풀스크린으로 진행합니다.
	//자동으로 해상도를 정렬합니다.
	if (RUNAWM->WindowInit(TRUE, L"Runaway", 1920, 1080, 32, true, false)) {
		RUNAGLM->PrepareRender();
		RUNASCENEM->NewScene(new MainScene());
		return RUNAWM->MainLoop();
	}
	else
		return 0;
	//프로그램 종료시 처리는 RUNAMM->CloseMyWindow()
}
