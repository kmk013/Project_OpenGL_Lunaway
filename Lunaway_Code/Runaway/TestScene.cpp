#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
	sceneNumber = NGameScene;
	RUNAMM->deltaTime; //이거 델타타임변수

	testModel1 = new Model("Mingeu.obj", "Mingeu.png");
	
	testObject1 = new TestObject(testModel1);
	testObject1->SetPos(10.0f, 0.0f, 10.0f);

	testEmptyObject1 = new EmptyObject();
	
	//반드시 푸쉬백을 진행해야함!
	PushBackModel(testModel1);
	PushBackGameObject(testObject1);
	PushBackGameObject(testEmptyObject1);


	testModel2 = new Model("cube.obj", "test.png");
	testObject2 = new TestObject(testModel2);
	testObject2->SetPos(5.0f, 0.0f, 0.0f);
	testObject2->SetRot(1.0f, 1.0f, 0.0f);
	testObject2->SetScale(5.0f, 10.0f, 15.0f);

	PushBackModel(testModel2);
	PushBackGameObject(testObject2);


	/*for (int i = 0; i < 600; i++) {
		testObjArray[i] = new TestObject(testModel2);
		testObjArray[i]->SetPos((float)i*2, i*2, i*2);
		PushBackGameObject(testObjArray[i]);
	}*/
	
}


TestScene::~TestScene()
{
}
