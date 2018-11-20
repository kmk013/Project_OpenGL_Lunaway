#pragma once
#include "Scene.h"
#include "TestObject.h"
#include "EmptyObject.h"
class TestScene :
	public Scene
{
public:
	Model* testModel1;	
	Model* testModel2;
public:
	TestObject* testObject1;
	TestObject* testObject2;
	TestObject* testObjArray[600];
	EmptyObject* testEmptyObject1;

public:
	TestScene();
	~TestScene();
};

