#pragma once
#pragma comment(lib, "winmm.lib")
#include "stdafx.h"
#include"WindowManager.h"
#include"GraphicManager.h"


using namespace std;
#define RUNAMM MessageManager::GetInstance()
enum {
	KeyUp = -1,
	KeyNone = 0,
	KeyPress = 1,
	KeyDown = 2
};

class MessageManager
{
	friend class WindowManager;
	
public:
	int mouseX=0;
	int mouseY=0;
public:
	//키입력 처리
	bool lkey[256], rkey[256];
	bool mouseLClicked=false;
	bool mouseRClicked=false;
	void UpdateKeyState();
	int GetMyKeyState(int vk);
	int GetMyMouseState(int mouseLR);

public:
	//시간 처리
	float deltaTime;
	void UpdateFPS();

public:	
	typedef void (MessageManager::*MessageFuncPtr)(WPARAM, LPARAM);
	typedef struct _MessageMap {
		UINT iMsg;
		MessageFuncPtr fp;
	}MessageMap;

	static MessageManager* GetInstance() {
		static MessageManager instance;
		return &instance;
	}

	
	void CloseMyWindow();

private:	
	static MessageMap messageMap[];
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	//콜백 테스트
	void OnCreate(WPARAM wParam, LPARAM lParam) {
		
	}
	void OnSize(WPARAM wParam, LPARAM lParam);
	void OnClose(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void OnSysCommand(WPARAM wParam, LPARAM lParam);
	void OnCommand(WPARAM wParam, LPARAM lParam) {}
	void OnKeyUp(WPARAM wParam, LPARAM lParam) {}
	void OnMouseMove(WPARAM wParam, LPARAM lParam);
	void OnMouseLeave(WPARAM wParam, LPARAM lParam);
	void OnLButtonDown(WPARAM wParam, LPARAM lParam);
	void OnLButtonUp(WPARAM wParam, LPARAM lParam);
	void OnRButtonDown(WPARAM wParam, LPARAM lParam);
	void OnRButtonUp(WPARAM wParam, LPARAM lParam);
	void OnChar(WPARAM wParam, LPARAM lParam) {}
	void OnSetFocus(WPARAM wParam, LPARAM lParam);
};

