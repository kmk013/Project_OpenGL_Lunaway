#pragma once
#include "Scene.h"
#include "TestObject.h"
#include "UI.h"
class TestScene2 :
	public Scene
{
public:
	Model* testModel2;

public:
	TestObject* testObject2;
	UI* testUI;
public:
	TestScene2();
	~TestScene2();
};

