#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "GLShader.h"
#include "GLProgram.h"
#include "RUNAMath.h"
#include "PNGLoader.h"
#include "Model.h"
#include "ObjectManager.h"
#include "SceneManager.h"


#define RUNAGLM GraphicManager::GetInstance()
class GraphicManager
{
	friend class WindowManager;
private:
	HDC mDC;            //디바이스 컨텍스트
	HGLRC mRC;            //GL 렌더링 컨텍스트
public:
	GLsizei width;
	GLsizei height;

	HDC* GetHDCptr() { return &mDC; }
	HGLRC* GetHGLRCptr() { return &mRC; }

public:
	GraphicManager();
	~GraphicManager();

	static GraphicManager* GetInstance()
	{
		static GraphicManager instance;
		return &instance;
	}


	GLuint LoadBMP(const char* path);

public:
	BOOL GLInit33();
	void ViewInit(GLsizei w, GLsizei h);
	void GetGLVersion(int *major, int* minor);
	void PrepareRender();
	void SetData();

	//콜라이더 화면 출력용
	GLuint colVertexArrayID;

	void Render();   //화면을 새로 그림
	void DrawScene();
	void ReshapeView(GLsizei w, GLsizei h);
	void DestroyScene();

	//프로그램과 쉐이더
	GLProgram* mProgram;
	GLShader* mVertSh;         //정점 쉐이더
	GLShader* mTextureSh;      //텍스쳐 쉐이더

	GLProgram *mUIProgram;
	GLShader* mUITextureSh;
	GLShader* mUIVertSh;

	GLuint MatrixID;
	Mat4 mvp;

	GLuint textureUniformID;   //텍스쳐 쉐이더 유니폼 연결 아이디
	GLuint uiUniformID;         //UI 쉐이더 유니폼 연결 아이디
	GLuint uiScreenID;         //UI 스케일 변경시 이용할 아이디

	Model* testm;
};
