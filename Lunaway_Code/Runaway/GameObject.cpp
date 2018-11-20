#include "stdafx.h"
#include "GameObject.h"
#include "SceneManager.h"

GameObject::GameObject() : useModel(false), myModel(NULL), pos(0.0f, 0.0f, 0.0f), rot(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), isDestroyed(false), layer(LOther)
{
	//모델없는 생성자
	printf("모델없는 오브젝트 생성됨\n");
}

GameObject::GameObject(Model* MyModel) : useModel(true), myModel(MyModel), pos(0.0f, 0.0f, 0.0f), rot(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), isDestroyed(false), layer(LOther)
{
	//모델 있는 생성자
	//printf("게임오브젝트생성됨\n");
}


GameObject::~GameObject()
{
}

void GameObject::SetPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void GameObject::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void GameObject::SetRot(float x, float y, float z)
{
	rot.x = x;
	rot.y = y;
	rot.z = z;
}

void GameObject::MawaruX()
{
	static float a = 0.0f;
	a += 0.01f;
	rot.x = a;
}

void GameObject::MawaruY()
{
	static float a = 0.0f;
	a += 0.01f;
	rot.y = a;
}

void GameObject::MawaruZ()
{
	static float a = 0.0f;
	a += 0.01f;
	rot.z = a;
}

void GameObject::CheckBase()
{
	if (RUNAMM->GetMyKeyState('X') > 0)
		MawaruX();
	if (RUNAMM->GetMyKeyState('Y') > 0)
		MawaruY();
	if (RUNAMM->GetMyKeyState('Z') > 0)
		MawaruZ();
	if (RUNAMM->GetMyKeyState('C') > 0) {
		SetRot(0.0f, 0.0f, 0.0f);
	}
}

void GameObject::Update()
{
	//CheckBase();
}

void GameObject::Destroy()
{
	isDestroyed = true;
}
