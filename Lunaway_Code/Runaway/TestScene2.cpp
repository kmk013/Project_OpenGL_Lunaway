#include "stdafx.h"
#include "TestScene2.h"


TestScene2::TestScene2()
{	
	testModel2 = new Model("cube.obj", "test.png");
	testObject2 = new TestObject(testModel2);
	testObject2->SetPos(0.0f, 0.0f, 0.0f);

	PushBackModel(testModel2);
	PushBackGameObject(testObject2);
	//UI
	testUI = new UI("test.png", 100, 100);
	PushBackUI(testUI);

}


TestScene2::~TestScene2()
{
}
