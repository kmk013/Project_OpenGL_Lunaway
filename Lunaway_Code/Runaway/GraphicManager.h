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
	HDC mDC;            //����̽� ���ؽ�Ʈ
	HGLRC mRC;            //GL ������ ���ؽ�Ʈ
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

	//�ݶ��̴� ȭ�� ��¿�
	GLuint colVertexArrayID;

	void Render();   //ȭ���� ���� �׸�
	void DrawScene();
	void ReshapeView(GLsizei w, GLsizei h);
	void DestroyScene();

	//���α׷��� ���̴�
	GLProgram* mProgram;
	GLShader* mVertSh;         //���� ���̴�
	GLShader* mTextureSh;      //�ؽ��� ���̴�

	GLProgram *mUIProgram;
	GLShader* mUITextureSh;
	GLShader* mUIVertSh;

	GLuint MatrixID;
	Mat4 mvp;

	GLuint textureUniformID;   //�ؽ��� ���̴� ������ ���� ���̵�
	GLuint uiUniformID;         //UI ���̴� ������ ���� ���̵�
	GLuint uiScreenID;         //UI ������ ����� �̿��� ���̵�

	Model* testm;
};
