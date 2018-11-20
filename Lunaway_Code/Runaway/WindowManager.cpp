#include "stdafx.h"
#include "WindowManager.h"
#include "MessageManager.h"
#include "GraphicManager.h"
#include "SceneManager.h"
#include <stdio.h>

void WindowManager::DestroyGLWindow()
{
}

WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

BOOL WindowManager::WindowInit(BOOL isFullscreen, const wchar_t * title, int width, int height, int bits, bool showCursor, bool clipCursor)
{
	int counti = 0;
	int glw = width;
	int glh = height;
	int count = 0;
	//�ʱ�ȭ ����
	//1. ������ ���
	//2. ������ ��Ÿ�� ����
	//3. ������ ����
	//4. OpenGL ����̽� ���ؽ�Ʈ �Ҵ�


	//1.������ ���

	//�������������� ����, �����ִٸ� FALSE��ȯ
	if (!WindowManager::RegisterWIndow(mHInstance))
		return FALSE;

	GLuint PixelFormat;	//��ġ�� �´� �ȼ� ���˰� ã�Ƽ� �Ҵ��� ����
	DWORD dwExStyle;	//������ Ȯ�� ��Ÿ��
	DWORD dwStyle;		//������ ��Ÿ��
	RECT ClientRect;	//ȭ�� �簢��
	int wx, wy;
	ClientRect.left = (long)0;
	ClientRect.right = (long)width;
	ClientRect.top = (long)0;
	ClientRect.bottom = (long)height;
	mFullScreen = isFullscreen;



	if (mFullScreen) {
		//��üȭ���̶��

		wx = wy = 0L;
		ClientRect.right = glw = GetSystemMetrics(SM_CXSCREEN);
		ClientRect.bottom = glh = GetSystemMetrics(SM_CYSCREEN);
		dwStyle = WS_SYSMENU | WS_POPUP;
		dwExStyle = WS_EX_TOPMOST;
	}
	else {
		//â�����

		//GetSystemMetrics ȭ�� ũ�� �޾ƿ�
		wx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		wy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		ClientRect.right = width;
		ClientRect.bottom = height;
		dwStyle = WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;
		dwExStyle = NULL;
	}
	//ȭ�� ���
	AdjustWindowRectEx(&ClientRect, dwStyle, false, dwExStyle);
	mHWnd = CreateWindowEx(
		dwExStyle,
		L"Runaway",
		title,
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0,
		ClientRect.right - ClientRect.left,
		ClientRect.bottom - ClientRect.top,
		(HWND)NULL,
		(HMENU)NULL,
		mHInstance,
		NULL);	//������ �����Ͱ�.
	if (!mHWnd)
	{
		MessageBox(NULL, TEXT("������ ������ �����Ͽ����ϴ�."), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);

		return FALSE;
	}

	//�ȼ���������
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(pfd),			//ũ��
		1,						//����
		PFD_DRAW_TO_WINDOW |	//������ ����
		PFD_SUPPORT_OPENGL |	//����GL ����
		PFD_DOUBLEBUFFER,		//������۸� ����
		PFD_TYPE_RGBA,			//RGBA ���� ����
		bits,					//���� ��Ʈ��
		0,0,0,0,0,0,0,0,		//�÷� ��Ʈ ����, �˹� ���� ����, ����Ʈ ��Ʈ ����			
		0,						//���� ���� ����
		0,0,0,0,				//���� ��Ʈ ����
		32,						//32Bit ���� ����
		0,						//���ٽ� ���� ����
		0,						//���� ���� ����
		PFD_MAIN_PLANE,			//���� ��ο� ���̾�
		0,						//�����
		0,0,0					//���̾� ����ũ ����
	};

	// ����̽� ���ؽ�Ʈ�� �ִ°�, ������ if�� ����
	if (!(mDC = GetDC(mHWnd)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL ����̽� ���ؽ�Ʈ�� ������ �� �����ϴ�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// ��ġ�� �´� �ȼ� ������ �ִ°�, �ֻ��� ������ ã�� ������ if������
	if (!(PixelFormat = ChoosePixelFormat(mDC, &pfd)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("��ġ�� �´� �ȼ������� ã�� ���߽��ϴ�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// �ȼ� ������ ������ �� �ִ°�, ������ ������ ������
	if (!SetPixelFormat(mDC, PixelFormat, &pfd))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("�ȼ������� ������ �� �����ϴ�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// ������ ���ؽ�Ʈ�� ������ �� �ִ°�
	//mDC�� ������ ���ο� ����GL ������ ���ؽ�Ʈ ����
	//������.h �Լ���
	HGLRC tmpRC;
	if (!(tmpRC = wglCreateContext(mDC)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL ������ ���ؽ�Ʈ�� ������ �� �����ϴ�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// GL�� ������ ���ؽ�Ʈ�� ����� �Լ� wglMakeCurrent
	// �� �Լ��� ȣ��� �� ���� ����GL ȣ���� �� DC�� ��ġ���� �����
	// ������ ���ؽ�Ʈ�� ����� �� �ִ°�
	// �������� CS_OWNDC �Ӽ� ������ ����GL�� �����
	// CS_OWNDC�� �־�� �����쿡 DC�� ������ �Ҵ��� �� ���� -> �׷��� GL API ����� ��밡��
	if (!wglMakeCurrent(mDC, tmpRC))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL ������ ���ؽ�Ʈ�� ����� �� �����ϴ�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//3.0 �̻� OpenGL ���
	InitGLAPI();		//GL API�� �ҷ��� (���̺귯���� ���⿡ ���� �ҷ��;���, GLEW�� ��ü����, ���� �밡���� ������ �� �� �־�� �Ф�)

	//���� Ȯ���ϱ�
	int major, minor;
	RUNAGLM->GetGLVersion(&major, &minor);
	if (major < 3 || (major == 3 && minor < 2))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("OpenGL 3.0�̻��� �������� �ʴ� ��ǻ���Դϴ�."), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	printf("GLVersion Major : %d, Minor : %d\n", major, minor);
	//������ ���ؽ�Ʈ ������ ������ �͵�
	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,major,
		WGL_CONTEXT_MINOR_VERSION_ARB,minor,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	wglDeleteContext(tmpRC);

	//�Լ������� �����ͼ� ���°���
	if (wglCreateContextAttribsARB != NULL)
	{
		//������ ���ؽ�Ʈ ����
		mRC = wglCreateContextAttribsARB(mDC, 0, attribs);
	}

	wglMakeCurrent(NULL, NULL);
	if (!mRC)
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("OpenGL 3.0 RC�� �������� �ʾҽ��ϴ�."), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//�׷��ȸŴ����� �Ҵ�
	RUNAGLM->mDC = mDC;
	RUNAGLM->mRC = mRC;

	//GL ���� �ʱ�ȭ
	RUNAMM->OnSize(0, MAKELPARAM(glw, glh));

	//������ ����	
	ShowWindow(mHWnd, SW_SHOW);	//������ ���
	SetForegroundWindow(mHWnd);	//������ �ֻ����� ����
	SetFocus(mHWnd);			//Ű���带 �� �����찡 ����ϰ� ��


	ShowCursor(showCursor);
	CM->showCursor = showCursor;

	//���콺 ȭ��ȿ� ���α�
	if (mFullScreen || clipCursor) {
		CM->clipCursor = true;
		CM->ClipMouseInWindow();
	}

	//���� �غ����


	return TRUE;
}

BOOL WindowManager::RegisterWIndow(HINSTANCE hInstance)
{
	int count = 0;
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.cbWndExtra = 0;		//������ ������ ���� ����
	wnd.cbClsExtra = 0;
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wnd.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = MessageManager::WndProc;
	wnd.lpszClassName = L"Runaway";
	wnd.hbrBackground = NULL;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//�������� ����, ������ �ٲ�� �ٽ� �׷��� | ��� ����ϴ� ������ DC
	if (!::RegisterClassEx(&wnd)) {
		return FALSE;
	}
	return TRUE;
}

int WindowManager::MainLoop()
{
	while (1)
	{
		//PeekMessage�� �޼����� ���� �ִ������� �˻� �� �ٷ� ����
		//�ð��� ���� ����
		if (PeekMessage(&mMsg, NULL, 0U, 0U, PM_REMOVE))
		{
			//�޽����� �ִٸ�
			if (mMsg.message == WM_QUIT)
			{
				//�޽����� WM_QUIT�̶�� ����
				break;
			}
			else
			{
				//�ƴϸ� �⺻���� ����
				TranslateMessage(&mMsg);	//�޽����� ������
				DispatchMessage(&mMsg);		//�޽����� WndProc���� ���� (MessageMangaer::WndProc)
			}
		}

		if (RUNASCENEM->_isChangeSceneCalled)
			RUNASCENEM->_sceneChange();

		//�޽����� ���ٸ� ������ ����
		RUNAMM->UpdateKeyState();	
		RUNAMM->UpdateFPS();
		RUNASCENEM->currentScene->Collide();
		RUNASCENEM->currentScene->Update();
		RUNASCENEM->currentScene->FindAndDeleteObjects();
		CM->Update();
		RUNAGLM->Render();
		RUNASCENEM->currentScene->LateUpdate();
		CM->LateUpdate();
		SwapBuffers(mDC);

	}
	return mMsg.message;
}

