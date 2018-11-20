#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#include "stdafx.h"

#define RUNAWM WindowManager::GetInstance()

class WindowManager
{
	friend class GraphicManager;
	friend class MessageManager;
protected:
	BOOL mFullScreen;		//��üȭ�� ����
	HDC mDC;				//����̽� ���ؽ�Ʈ
	HGLRC mRC;				//GL ������ ���ؽ�Ʈ
	HWND mHWnd;				//������ �ڵ�
	HINSTANCE mHInstance;	//�ڵ� �ν��Ͻ�
	void DestroyGLWindow();		//�޸� ���� ���
	MSG mMsg;				//������ �޽��� (���η������� ���)
	
public:
	WindowManager();
	~WindowManager();
	HWND GetHWND() { return mHWnd; }
	HDC GetHDC() { return mDC; }

	BOOL WindowInit(BOOL isFullscreen = FALSE, const wchar_t *title = L"Runaway", int width=1024, int height=768, int bits = 16, bool showCursor=false, bool clipCursor=true);
	BOOL RegisterWIndow(HINSTANCE hInstance);

	int MainLoop();	//����Ŭ

	static WindowManager* GetInstance() 
	{
		static WindowManager instance;
		return &instance;
	}

	



};

#endif
