#include "stdafx.h"
#include "Camera.h"
#include "MessageManager.h"
#include "Player.h"

Camera::Camera() : clipCursor(false), isPerspective(false), cmRot(0.0f, 0.0f) {
	pos.x = 4.0f;
	pos.y = 25.0f;
	pos.z = -3.0f;
	rot.x = 12.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	look.x = 0.0f;
	look.y = -0.5f;
	look.z = 1.0f;

	rad = 40.0f;
	seta = 1.25f;
	ph = 4.71f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (player) {
		if (RUNAMM->GetMyKeyState(VK_UP) > 0) {
			seta -= RUNAMM->deltaTime*3.14f;
			if (seta < 1.1f) {
				seta = 1.1f;
			}
			look.y = -tan(4.71f - seta);
		}
		if (RUNAMM->GetMyKeyState(VK_DOWN) > 0) {
			seta += RUNAMM->deltaTime*3.14f;
			if (seta > 1.57f) {
				seta = 1.57f;
			}
			look.y = -tan(4.71f - seta);
		}
		if (RUNAMM->GetMyKeyState(VK_RIGHT) > 0) {
			ph -= RUNAMM->deltaTime*3.14f;
			look.x = sin(4.71f - ph);
			look.z = cos(4.71f - ph);
		}
		if (RUNAMM->GetMyKeyState(VK_LEFT) > 0) {
			ph += RUNAMM->deltaTime*3.14f;
			look.x = sin(4.71f - ph);
			look.z = cos(4.71f - ph);
		}
		if (RUNAMM->GetMyKeyState('T') > 0) {
			GameSceneInit();
		}
		LunaCamera();
	}
}

void Camera::LateUpdate()
{

}

void Camera::CameraRefresh()
{
	//printf("lx : %.4f, ly : %.4f, lz : %.4f\n", look.x, look.y, look.z);
	static int count = 0;
	/*if(isPerspective)*/
	Projection = Perspective(45.0f, widthdividedheight, 0.1f, 1000.0f);
	/*else
	Projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);*/
	View = LookAt(Vec3(pos.x, pos.y, pos.z), Vec3(pos.x + look.x, pos.y + look.y, pos.z + look.z), Vec3(0.0f, 1.0f, 0.0f));
	/*Mat4 Model = Mat4(1.0f);
	RUNAGLM->mvp = (View * Model)*Projection;*/
}

void Camera::LunaCamera()
{
	if (player) {
		pos.x = player->pos.x + rad*sin(seta)*cos(ph);
		pos.y = player->pos.y + rad*cos(seta);
		pos.z = player->pos.z + rad*sin(seta)*sin(ph);
	}
}

void Camera::GameSceneInit()
{
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z;
	look.x = 0.0f;
	look.y = -0.5f;
	look.z = 1.0f;
	rad = 40.0f;
	seta = 1.28f;
	ph = -1.57f;
	look.x = sin(4.71f - ph);
	look.z = cos(4.71f - ph);
	look.y = -tan(4.71f - seta);
}

void Camera::MainSceneInit()
{
	pos.x = 4.0f;
	pos.y = 25.0f;
	pos.z = -3.0f;
	rot.x = 12.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;
	look.x = 0.0f;
	look.y = -0.5f;
	look.z = 1.0f;

	rad = 40.0f;
	seta = 1.25f;
	ph = 4.71f;
}


void Camera::FPSCameraRotX(int mouseX)
{
	float xp = (float)(mouseX - oldMouseX)*rotSpeed;

	rot.x += xp;

	look.x = sin(rot.x);
	look.z = -cos(rot.x);

	oldMouseX = mouseX;
}

void Camera::FPSCameraRotY(int mouseY)
{
	float yp = (float)(mouseY - oldMouseY)*rotSpeed;

	rot.y += yp;

	if (rot.y > 0.6f) {
		rot.y -= yp;
	}
	if (rot.y < 0.0f) {
		rot.y -= yp;
	}
	look.y = -tan(rot.y);

	oldMouseY = mouseY;
}

void Camera::FPSCameraRot(int mouseX, int mouseY)
{
	float xp = (float)(mouseX - oldMouseX)*rotSpeed;
	float yp = (float)(mouseY - oldMouseY)*rotSpeed;

	rot.x += xp;
	rot.y += yp;

	look.x = sin(rot.x);
	look.z = -cos(rot.x);

	if (rot.y > piHalf) {
		rot.y -= yp;
	}
	if (rot.y < -piHalf) {
		rot.y -= yp;
	}
	look.y = -tan(rot.y);

	oldMouseX = mouseX;
	oldMouseY = mouseY;
	//printf("pos + look == %f %f %f\n", pos.x + look.x, pos.y + look.y, pos.z + look.z);
	//printf("lx : %.4f, ly : %.4f, lz : %.4f\n",look.x,look.y,look.z);
}

void Camera::CalculAngleLR(int isRight)
{
	rot.x += rotSpeed*isRight;
	look.x = sin(rot.x);
	look.z = -cos(rot.x);
}

void Camera::CalculAngleUD(int isUp)
{
	rot.y += rotSpeed*isUp;
	//얼마 이상으로 못올라가게
	if (rot.y > piHalf) {
		rot.y -= rotSpeed;
	}
	if (rot.y < -piHalf) {
		rot.y += rotSpeed;
	}
	//printf("%f\n", rot.y);
	look.y = -tan(rot.y);
}

void Camera::CalculMoveFB(int direction)
{
	/*pos.x = pos.x + direction*(look.x)*movSpeed;
	pos.z = pos.z + direction*(look.z)*movSpeed;*/

	//printf("pos == %f %f %f\n", pos.x, pos.y, pos.z);
}

void Camera::CalculMoveLR(int direction)
{
	/*pos.x = pos.x + direction*(look.z)*movSpeed;
	pos.z = pos.z + direction*(-look.x)*movSpeed;*/
	//printf("%f %f %f\n", pos.x, pos.y, pos.z);
}

void Camera::ClipMouseInWindow()
{
	if (!clipCursor)
		return;
	RECT a;
	GetWindowRect(RUNAWM->GetHWND(), &a);
	printf("\n%d %d %d %d\n", a.top, a.bottom, a.left, a.right);
	ClipCursor(&a);
	SetCursor(NULL);
	ShowCursor(showCursor);
}

void Camera::CameraInit()
{
	look.x = sin(rot.x);
	look.z = -cos(rot.x);
	//얼마 이상으로 못올라가게
	if (rot.y > piHalf) {
		rot.y -= rotSpeed;
	}
	if (rot.y < -piHalf) {
		rot.y += rotSpeed;
	}
	CameraRefresh();
}