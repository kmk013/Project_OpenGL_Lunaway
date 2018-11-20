#include "stdafx.h"
#include "TestObject.h"
#include "TestScene2.h"

TestObject::TestObject(Model* MyModel) : GameObject(MyModel)
{
}


TestObject::~TestObject()
{
}

void TestObject::Update()
{
	if (RUNAMM->GetMyKeyState(VK_UP) > 0)
		rot.y += 0.004f;
	if (RUNAMM->GetMyKeyState(VK_DOWN) > 0)
		rot.y -= 0.004f;
	if (RUNAMM->GetMyKeyState(VK_LEFT) > 0)
		rot.x += 0.004f;
	if (RUNAMM->GetMyKeyState(VK_RIGHT) > 0)
		rot.x -= 0.004f;
}

