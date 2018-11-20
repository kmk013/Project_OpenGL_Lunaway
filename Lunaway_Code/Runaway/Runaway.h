#ifndef _RUNAWAY_H_
#define _RUNAWAY_H_

#include "stdafx.h"
#include"WindowManager.h"
#include"MessageManager.h"
#include"GraphicManager.h"
#include"SceneManager.h"

//int main으로 시작
#pragma comment(linker, "/ENTRY:mainCRTStartup")

//디버그이면 콘솔창 표시
#ifdef _DEBUG
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#endif