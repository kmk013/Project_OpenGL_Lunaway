#include "stdafx.h"
#include "MainScene.h"


MainScene::MainScene()
{
	SetCursorPos(212, 400);
	CM->player = NULL;

	sceneNumber = NMainScene;
	//mainLogo = new Button("gg.png", 100, 100);
	//스케일 변경 예시
	//backGround = new UI("Resource/UI/MainScene/MainScene_BG.png", 0, 0);
	CM->myrateW = CM->screenWidth / 1920.0f;
	CM->myrateH = CM->screenHeight / 1080.0f;
	title = new UI("Resource/UI/MainScene/Title.png", 120, 710, 1.0f, 1.0f);
	gameStartButton = new Button("Resource/UI/MainScene/GameStart.png", 120, 410, Button::startb,0.8f,0.8f);
	exitButton = new Button("Resource/UI/MainScene/Exit.png", 120, 50, Button::exitb, 0.8f, 0.8f);
	PushBackUI(title);
	PushBackUI(gameStartButton);
	PushBackUI(exitButton);

	myCollectionButton = new Button("Resource/UI/MainScene/Collection.png", 120, 185, Button::collectionb);
	PushBackUI(myCollectionButton);

	collectionGem = new CollectionGem();

	collectionGem->collector = new UI("Resource/UI/Collection/BackGround.png", 96, 54, 0.9f, 0.9f);
	collectionGem->collector->isEnable = false;

	PushBackUI(collectionGem->collector);

	collectionGem->spriteGem[0][0] = new UI("Resource/UI/Collection/Gems/Item_Gem1_1.2d.png", 145, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][0]->isEnable = false;
	collectionGem->spriteGem[0][1] = new UI("Resource/UI/Collection/Gems/Item_Gem1_2.2d.png", 351, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][1]->isEnable = false;
	collectionGem->spriteGem[0][2] = new UI("Resource/UI/Collection/Gems/Item_Gem1_3.2d.png", 558, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][2]->isEnable = false;
	collectionGem->spriteGem[0][3] = new UI("Resource/UI/Collection/Gems/Item_Gem1_4.2d.png", 765, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][3]->isEnable = false;
	collectionGem->spriteGem[0][4] = new UI("Resource/UI/Collection/Gems/Item_Gem1_5.2d.png", 972, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][4]->isEnable = false;
	collectionGem->spriteGem[0][5] = new UI("Resource/UI/Collection/Gems/Item_Gem1_6.2d.png", 1179, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][5]->isEnable = false;
	collectionGem->spriteGem[0][6] = new UI("Resource/UI/Collection/Gems/Item_Gem1_7.2d.png", 1386, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][6]->isEnable = false;
	collectionGem->spriteGem[0][7] = new UI("Resource/UI/Collection/Gems/Item_Gem1_8.2d.png", 1594, 185, 0.6f, 0.6f);
	collectionGem->spriteGem[0][7]->isEnable = false;

	collectionGem->spriteGem[1][0] = new UI("Resource/UI/Collection/Gems/Item_Gem2_1.2d.png", 160, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][0]->isEnable = false;
	collectionGem->spriteGem[1][1] = new UI("Resource/UI/Collection/Gems/Item_Gem2_2.2d.png", 366, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][1]->isEnable = false;
	collectionGem->spriteGem[1][2] = new UI("Resource/UI/Collection/Gems/Item_Gem2_3.2d.png", 573, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][2]->isEnable = false;
	collectionGem->spriteGem[1][3] = new UI("Resource/UI/Collection/Gems/Item_Gem2_4.2d.png", 780, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][3]->isEnable = false;
	collectionGem->spriteGem[1][4] = new UI("Resource/UI/Collection/Gems/Item_Gem2_5.2d.png", 987, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][4]->isEnable = false;
	collectionGem->spriteGem[1][5] = new UI("Resource/UI/Collection/Gems/Item_Gem2_6.2d.png", 1194, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][5]->isEnable = false;
	collectionGem->spriteGem[1][6] = new UI("Resource/UI/Collection/Gems/Item_Gem2_7.2d.png", 1401, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][6]->isEnable = false;
	collectionGem->spriteGem[1][7] = new UI("Resource/UI/Collection/Gems/Item_Gem2_8.2d.png", 1609, 400, 0.6f, 0.6f);
	collectionGem->spriteGem[1][7]->isEnable = false;

	collectionGem->spriteGem[2][0] = new UI("Resource/UI/Collection/Gems/Item_Gem3_1.2d.png", 160, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][0]->isEnable = false;
	collectionGem->spriteGem[2][1] = new UI("Resource/UI/Collection/Gems/Item_Gem3_2.2d.png", 366, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][1]->isEnable = false;
	collectionGem->spriteGem[2][2] = new UI("Resource/UI/Collection/Gems/Item_Gem3_3.2d.png", 573, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][2]->isEnable = false;
	collectionGem->spriteGem[2][3] = new UI("Resource/UI/Collection/Gems/Item_Gem3_4.2d.png", 780, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][3]->isEnable = false;
	collectionGem->spriteGem[2][4] = new UI("Resource/UI/Collection/Gems/Item_Gem3_5.2d.png", 987, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][4]->isEnable = false;
	collectionGem->spriteGem[2][5] = new UI("Resource/UI/Collection/Gems/Item_Gem3_6.2d.png", 1194, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][5]->isEnable = false;
	collectionGem->spriteGem[2][6] = new UI("Resource/UI/Collection/Gems/Item_Gem3_7.2d.png", 1401, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][6]->isEnable = false;
	collectionGem->spriteGem[2][7] = new UI("Resource/UI/Collection/Gems/Item_Gem3_8.2d.png", 1609, 611, 0.6f, 0.6f);
	collectionGem->spriteGem[2][7]->isEnable = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			PushBackUI(collectionGem->spriteGem[i][j]);
		}
	}
	PushBackGameObject(collectionGem);

	myCollectionButton->cg = collectionGem;
	

	
	
	

	whiteStar = new Model("Resource/Model/WhiteCube/Star.obj", "Resource/Model/WhiteCube/Star.png");
	bgStars = new StarManager();
	bgStars->p = NULL;
	PushBackGameObject(bgStars);
	for (int j = 0; j < bgStars->starcount; j++) {
		bgStars->stars[j] = new GameObject(whiteStar);
		bgStars->SetRandomPos(j);
		PushBackGameObject(bgStars->stars[j]);
	}
	bgStars2 = new StarManager();
	bgStars2->p = NULL;
	PushBackGameObject(bgStars2);
	for (int j = 0; j < bgStars2->starcount; j++) {
		bgStars2->stars[j] = new GameObject(whiteStar);
		bgStars2->SetRandomPos(j);
		PushBackGameObject(bgStars2->stars[j]);
	}

	plm = new Model("Resource/Model/Character/Character.obj", "Resource/Model/Character/Character.png");
	pl = new GameObject(plm);
	pl->SetPos(26.0f, 15.0f, 50.0f);
	pl->SetRot(0.0f,3.14f, 0.0f);
	PushBackGameObject(pl);
	PushBackModel(plm);

	moom = new Model("Resource/Model/Moon/Moon.obj", "Resource/Model/Moon/Moon.png");
	moo = new GameObject(moom);
	moo->SetPos(-130.0f, 15.0f, -250.0f);
	moo->SetScale(5.0f, 5.0f, 2.0f);
	moo->SetRot(0.0f, 3.14f, 0.0f);
	PushBackGameObject(moo);
	PushBackModel(moom);

	CM->MainSceneInit();

}


MainScene::~MainScene()
{

}
