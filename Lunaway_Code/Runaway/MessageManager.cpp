#include "stdafx.h"
#include "MessageManager.h"
#include "WindowManager.h"
#include "GraphicManager.h"
#include "MainScene.h"
#include "GameScene.h"
#include "Camera.h"

MessageManager::MessageMap MessageManager::messageMap[] = {
	//이곳에 콜백함수를 추가
	//{메시지명, &함수명}
	{WM_CREATE, &OnCreate},
	{WM_SIZE, &OnSize },
	{WM_CLOSE, &OnClose },
	{WM_KEYDOWN, &OnKeyDown },
	{WM_KEYUP, &OnKeyUp },
	{WM_MOUSEMOVE, &OnMouseMove },
	{WM_LBUTTONDOWN, &OnLButtonDown },
	{WM_LBUTTONUP, &OnLButtonUp },
	{WM_RBUTTONDOWN, &OnRButtonDown },
	{WM_RBUTTONUP, &OnRButtonUp },
	{WM_CHAR, &OnChar },
	{WM_COMMAND, &OnCommand },
	{WM_SYSCOMMAND, &OnSysCommand },
	{WM_MOUSELEAVE, &OnMouseLeave},
	{WM_SETFOCUS,&OnSetFocus},
	{0,NULL}
};

void MessageManager::UpdateKeyState()
{
	for (int i = 0; i < 256; i++)
	{
		lkey[i] = rkey[i];
		rkey[i] = GetAsyncKeyState(i) & 0x8000;
	}
	
}

int MessageManager::GetMyKeyState(int vk)
{
	if (lkey[vk] && rkey[vk]) return 2; //아까도 눌렀었고 지금도 눌러져있을 때
	if (!lkey[vk] && rkey[vk]) return 1; //아까는 아니지만 지금은 눌려있을때
	if (lkey[vk] && !rkey[vk]) return -1; //누르다 땠을때
	return 0;
}

int MessageManager::GetMyMouseState(int mouseLR)
{
	return 0;
}

void MessageManager::UpdateFPS()
{

	static DWORD frameCount = 0;            //프레임 카운트수
	static float timeElapsed = 0.0f;            //흐른 시간
	static DWORD lastTime = timeGetTime();   //마지막 시간(temp변수)

	DWORD curTime = timeGetTime();      //현재 시간
	deltaTime = (curTime - lastTime)*0.001f;

	timeElapsed += deltaTime;

	frameCount++;

	if (timeElapsed >= 1.0f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		float fps = (float)frameCount / timeElapsed;
		printf("fps : %f\n", fps);     //FPS출력 하는 소스

		if (CURRENTSCENE->sceneNumber == Scene::NGameScene) {
			if (((GameScene*)CURRENTSCENE)->character) {
				Player* p = ((GameScene*)CURRENTSCENE)->character;
				p->killo += (int)((float)p->speed*0.2778f);
				//printf("페이즈 : %d, hp : %d, mp : %d, 공격력 : %d, 거리 : %d, 속도 : %.2f, 게임오버? %d\n", p->phase, p->hp, p->mp,p->damage ,p->killo, p->speed, p->isGameOver);
				if (p->mp < 10)
					p->mp += 1;
			}
		}


		frameCount = 0;
		timeElapsed = 0.0f;
	}

	lastTime = curTime;
}

void MessageManager::CloseMyWindow()
{
	RUNAGLM->DestroyScene();
	SendMessage(RUNAWM->mHWnd, WM_CLOSE, 0, 0);
}

LRESULT MessageManager::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	while (messageMap[i].iMsg != 0)
	{
		//메시지의 형태 조사 후 같다면 실행
		if (iMessage == messageMap[i].iMsg)
		{
			(RUNAMM->*(messageMap[i].fp))(wParam, lParam);
		}
		++i;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void MessageManager::OnSize(WPARAM wParam, LPARAM lParam)
{
	//사이즈가 변경되었을 때마다 사용
	GLsizei width = LOWORD(lParam);
	GLsizei height = HIWORD(lParam);
	CM->screenHeight = height;
	CM->screenWidth = width;
	CM->widthdividedheight =(float)width/height;
	printf("%d, %d 화면크기 변경됨\n", height, width);
	//RUNAGLM->ViewInit(width, height);	//3.0 이전
	RUNAGLM->ReshapeView(width, height);
}

void MessageManager::OnClose(WPARAM wParam, LPARAM lParam)
{
	RUNAWM->DestroyGLWindow();
	PostQuitMessage(0);
}

void MessageManager::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	//getasynckeystate로 대체

	if (wParam == VK_ESCAPE)
	{
		if (RUNASCENEM->currentScene->sceneNumber == 1)
			RUNASCENEM->ChangeScene(new MainScene());
	}
	if (CURRENTSCENE->sceneNumber == Scene::NGameScene) {
		if (((GameScene*)CURRENTSCENE)->character) {
			if (((GameScene*)CURRENTSCENE)->character->readyToEnd) {
				((GameScene*)CURRENTSCENE)->character->isEnded = true;
			}
		}
	}
}

void MessageManager::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)				// Check System Calls
	{
	case SC_SCREENSAVE:		// Screensaver Trying To Start?
	case SC_MONITORPOWER:	// Monitor Trying To Enter Powersave?
		return;				// Prevent From Happening
	}
}

void MessageManager::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
	if (RUNASCENEM->currentScene->sceneNumber == Scene::NMainScene) {
		CM->FPSCameraRot(mouseX, mouseY);
		//printf("%.2f, %.2f,%.2f\n", CM->rot.x, CM->rot.y, CM->rot.z);
	}
}

void MessageManager::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{

}

void MessageManager::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	mouseLClicked = true;
}

void MessageManager::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	mouseLClicked = false;
}

void MessageManager::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	mouseRClicked = true;
}

void MessageManager::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	mouseRClicked = false;
}

void MessageManager::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
	CM->ClipMouseInWindow();
}
