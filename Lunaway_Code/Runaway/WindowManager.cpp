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
	//초기화 과정
	//1. 윈도우 등록
	//2. 윈도우 스타일 지정
	//3. 윈도우 생성
	//4. OpenGL 디바이스 컨텍스트 할당


	//1.윈도우 등록

	//레지스터윈도우 실행, 문제있다면 FALSE반환
	if (!WindowManager::RegisterWIndow(mHInstance))
		return FALSE;

	GLuint PixelFormat;	//장치에 맞는 픽셀 포맷값 찾아서 할당할 변수
	DWORD dwExStyle;	//윈도우 확장 스타일
	DWORD dwStyle;		//윈도우 스타일
	RECT ClientRect;	//화면 사각형
	int wx, wy;
	ClientRect.left = (long)0;
	ClientRect.right = (long)width;
	ClientRect.top = (long)0;
	ClientRect.bottom = (long)height;
	mFullScreen = isFullscreen;



	if (mFullScreen) {
		//전체화면이라면

		wx = wy = 0L;
		ClientRect.right = glw = GetSystemMetrics(SM_CXSCREEN);
		ClientRect.bottom = glh = GetSystemMetrics(SM_CYSCREEN);
		dwStyle = WS_SYSMENU | WS_POPUP;
		dwExStyle = WS_EX_TOPMOST;
	}
	else {
		//창모드라면

		//GetSystemMetrics 화면 크기 받아옴
		wx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		wy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		ClientRect.right = width;
		ClientRect.bottom = height;
		dwStyle = WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION;
		dwExStyle = NULL;
	}
	//화면 등록
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
		NULL);	//여분의 데이터값.
	if (!mHWnd)
	{
		MessageBox(NULL, TEXT("윈도우 생성을 실패하였습니다."), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);

		return FALSE;
	}

	//픽셀포맷정보
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(pfd),			//크기
		1,						//버전
		PFD_DRAW_TO_WINDOW |	//윈도우 지원
		PFD_SUPPORT_OPENGL |	//오픈GL 지원
		PFD_DOUBLEBUFFER,		//더블버퍼링 지원
		PFD_TYPE_RGBA,			//RGBA 포맷 지원
		bits,					//색깔 비트수
		0,0,0,0,0,0,0,0,		//컬러 비트 무시, 알바 버퍼 없음, 시프트 비트 무시			
		0,						//누적 버퍼 없음
		0,0,0,0,				//누적 비트 무시
		32,						//32Bit 깊이 버퍼
		0,						//스텐실 버퍼 없음
		0,						//보조 버퍼 없음
		PFD_MAIN_PLANE,			//메인 드로우 레이어
		0,						//예약됨
		0,0,0					//레이어 마스크 무시
	};

	// 디바이스 컨텍스트가 있는가, 없으면 if문 실행
	if (!(mDC = GetDC(mHWnd)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL 디바이스 컨텍스트를 생성할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// 장치에 맞는 픽셀 형식이 있는가, 최상의 포맷을 찾고 없으면 if문실행
	if (!(PixelFormat = ChoosePixelFormat(mDC, &pfd)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("장치에 맞는 픽셀형식을 찾지 못했습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// 픽셀 포맷을 설정할 수 있는가, 가져온 포맷을 설정함
	if (!SetPixelFormat(mDC, PixelFormat, &pfd))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("픽셀형식을 설정할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// 렌더링 컨텍스트에 접근할 수 있는가
	//mDC에 적합한 새로운 오픈GL 렌더링 컨텍스트 생성
	//윈도우.h 함수임
	HGLRC tmpRC;
	if (!(tmpRC = wglCreateContext(mDC)))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL 렌더링 컨텍스트를 생성할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	// GL의 렌더링 컨텍스트를 만드는 함수 wglMakeCurrent
	// 이 함수가 호출된 후 부턴 오픈GL 호출은 내 DC의 장치에서 사용함
	// 렌더링 컨텍스트를 사용할 수 있는가
	// 위에서의 CS_OWNDC 속성 때문에 오픈GL이 사용함
	// CS_OWNDC가 있어야 윈도우에 DC를 완전히 할당할 수 있음 -> 그래야 GL API 제대로 사용가능
	if (!wglMakeCurrent(mDC, tmpRC))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("GL 렌더링 컨텍스트를 사용할 수 없습니다"), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//3.0 이상 OpenGL 사용
	InitGLAPI();		//GL API를 불러옴 (라이브러리가 없기에 직접 불러와야함, GLEW로 대체가능, 들어가면 노가다의 흔적을 볼 수 있어요 ㅠㅠ)

	//버전 확인하기
	int major, minor;
	RUNAGLM->GetGLVersion(&major, &minor);
	if (major < 3 || (major == 3 && minor < 2))
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("OpenGL 3.0이상을 지원하지 않는 컴퓨터입니다."), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	printf("GLVersion Major : %d, Minor : %d\n", major, minor);
	//렌더링 콘텍스트 생성시 전해줄 것들
	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,major,
		WGL_CONTEXT_MINOR_VERSION_ARB,minor,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	wglDeleteContext(tmpRC);

	//함수포인터 가져와서 쓰는거임
	if (wglCreateContextAttribsARB != NULL)
	{
		//렌더링 콘텍스트 생성
		mRC = wglCreateContextAttribsARB(mDC, 0, attribs);
	}

	wglMakeCurrent(NULL, NULL);
	if (!mRC)
	{
		DestroyGLWindow();
		MessageBox(NULL, TEXT("OpenGL 3.0 RC가 생성되지 않았습니다."), TEXT("오류"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//그래픽매니저에 할당
	RUNAGLM->mDC = mDC;
	RUNAGLM->mRC = mRC;

	//GL 렌더 초기화
	RUNAMM->OnSize(0, MAKELPARAM(glw, glh));

	//윈도우 설정	
	ShowWindow(mHWnd, SW_SHOW);	//윈도우 띄움
	SetForegroundWindow(mHWnd);	//윈도우 최상위로 보냄
	SetFocus(mHWnd);			//키보드를 이 윈도우가 사용하게 함


	ShowCursor(showCursor);
	CM->showCursor = showCursor;

	//마우스 화면안에 가두기
	if (mFullScreen || clipCursor) {
		CM->clipCursor = true;
		CM->ClipMouseInWindow();
	}

	//렌더 준비과정


	return TRUE;
}

BOOL WindowManager::RegisterWIndow(HINSTANCE hInstance)
{
	int count = 0;
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.cbWndExtra = 0;		//여분의 데이터 저장 가능
	wnd.cbClsExtra = 0;
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wnd.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = MessageManager::WndProc;
	wnd.lpszClassName = L"Runaway";
	wnd.hbrBackground = NULL;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	//윈도우의 수직, 수평값이 바뀌면 다시 그려줌 | 계속 사용하는 윈도우 DC
	if (!::RegisterClassEx(&wnd)) {
		return FALSE;
	}
	return TRUE;
}

int WindowManager::MainLoop()
{
	while (1)
	{
		//PeekMessage는 메세지가 들어와 있는지만을 검사 후 바로 리턴
		//시간을 끌지 않음
		if (PeekMessage(&mMsg, NULL, 0U, 0U, PM_REMOVE))
		{
			//메시지가 있다면
			if (mMsg.message == WM_QUIT)
			{
				//메시지가 WM_QUIT이라면 종료
				break;
			}
			else
			{
				//아니면 기본루프 진행
				TranslateMessage(&mMsg);	//메시지를 가공함
				DispatchMessage(&mMsg);		//메시지를 WndProc으로 전달 (MessageMangaer::WndProc)
			}
		}

		if (RUNASCENEM->_isChangeSceneCalled)
			RUNASCENEM->_sceneChange();

		//메시지가 없다면 렌더링 진행
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

