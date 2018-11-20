#pragma once
#include "stdafx.h"
#include "RUNAMath.h"

//UI의 위치는 변경될 일이 없다고 가정하고 구현함
class UI
{
public:
	Vec2 pos;
	Vec3 scale;

public:
	GLuint vertexArrayID;
	GLuint textureID;
	GLuint vertexBuffer;
	GLuint uvBuffer;

	vector<Vec2> v;   //버텍스 배열
	vector<Vec2> u;   //UV 배열

public:
	int textureWidth;
	int textureHeight;
public:
	UI(const char * pngPath, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f);
	UI(UI* texture, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f);
	virtual ~UI();
	bool LoadUI(const char* path);
	virtual void Update();
	virtual void LateUpdate();

	bool isEnable;
	bool textureShared;

	bool isDestroyed;
	bool isPopp;
	void Destroy();
	void PopOut();
	virtual void OnDestroy() {}

	GLuint LoadPNG(const char* path);
};
