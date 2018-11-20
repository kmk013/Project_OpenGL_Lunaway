#pragma once
#include "stdafx.h"
#include "MessageManager.h"
#include "RUNAMath.h"

class Player;

#define CM Camera::GetInstance()

class Camera
{
private:

	float pi2 = RUNA_PI*2.0f;
	float piHalf = RUNA_PI*0.5f;
public:
	Vec3 pos;
	Vec3 rot;
	Vec3 look;

	int cameraNear = 1;      //ī�޶� �ּҰŸ�
	int cameraFar = 1000;   //ī�޶� �ִ�Ÿ�   gluperspective�� �̿�

	bool clipCursor = false;
	bool showCursor = false;

	int screenWidth = 0;
	int screenHeight = 0;

	float myrateW;
	float myrateH;
	float widthdividedheight;


	Camera();
	~Camera();
	void Update();
	void LateUpdate();

	static Camera* GetInstance() {
		static Camera instance;
		return &instance;
	}

	void CameraRefresh();
	void CameraInit();

	void ClipMouseInWindow();

public:
	Mat4 Projection;
	Mat4 View;
	bool isPerspective;

public:
	//�� ���Ӹ��� ���� ������ �Լ�
	int currentX = 0;
	int currentY = 0;
	int oldMouseX = 0;
	int oldMouseY = 0;
	float rotSpeed = 0.015f;
	float movSpeed = 0.1f;
	int screenValue = 0;

	int movePoint = 100; //���콺 ������ ����

	Vec2 cmRot;
	Player* player;
	float rad, seta, ph;


	void LunaCamera();
	void GameSceneInit();
	void MainSceneInit();
	void FPSCameraMove() {};
	void FPSCameraRotX(int mouseX);
	void FPSCameraRotY(int mouseY);
	void FPSCameraRot(int mouseX, int mouseY);

	void CalculAngleLR(int isRight);
	void CalculAngleUD(int isUp);
	void CalculMoveFB(int direction);
	void CalculMoveLR(int direction);
};
