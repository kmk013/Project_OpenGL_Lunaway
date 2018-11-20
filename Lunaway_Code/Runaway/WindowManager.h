#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#include "stdafx.h"

#define RUNAWM WindowManager::GetInstance()

class WindowManager
{
	friend class GraphicManager;
	friend class MessageManager;
protected:
	BOOL mFullScreen;		//전체화면 여부
	HDC mDC;				//디바이스 컨텍스트
	HGLRC mRC;				//GL 렌더링 컨텍스트
	HWND mHWnd;				//윈도우 핸들
	HINSTANCE mHInstance;	//핸들 인스턴스
	void DestroyGLWindow();		//메모리 해제 담당
	MSG mMsg;				//윈도우 메시지 (메인루프에서 사용)
	
public:
	WindowManager();
	~WindowManager();
	HWND GetHWND() { return mHWnd; }
	HDC GetHDC() { return mDC; }

	BOOL WindowInit(BOOL isFullscreen = FALSE, const wchar_t *title = L"Runaway", int width=1024, int height=768, int bits = 16, bool showCursor=false, bool clipCursor=true);
	BOOL RegisterWIndow(HINSTANCE hInstance);

	int MainLoop();	//사이클

	static WindowManager* GetInstance() 
	{
		static WindowManager instance;
		return &instance;
	}

	



};

#endif
