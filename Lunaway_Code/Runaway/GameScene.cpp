#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Bullet.h"

GameScene::GameScene()
{
	sceneNumber = NGameScene;
	boardModel = new Model("Resource/Model/Floor/Floor.obj", "Resource/Model/Floor/Floor.png");
	boardModel2 = new Model("Resource/Model/Floor/Floor_Yellow_1.obj", "Resource/Model/Floor/Floor.png");
	boardModel3 = new Model("Resource/Model/Floor/Floor_Yellow_2.obj", "Resource/Model/Floor/Floor_Yellow_2.png");

	characterM = new Model("Resource/Model/Character/Character.obj", "Resource/Model/Character/Character.png");
	PushBackModel(boardModel);
	PushBackModel(boardModel2);
	PushBackModel(boardModel3);
	PushBackModel(characterM);

	backGround = new UI("Resource/UI/Texts.png", 0, 0);
	PushBackUI(backGround);

	//플레이어 생성
	character = new Player(characterM);
	character->SetScale(0.5f, 0.5f, 0.5f);
	character->pos.y += 10.0f;
	character->bulletModel = new Model("Resource/Model/Bullet/Bullet.obj", "Resource/Model/Bullet/Bullet.png");
	character->myCollider = new Collider(character, 12.0f);
	PushBackModel(character->bulletModel);
	PushBackGameObject(character);
	PushBackCollider(character->myCollider);

	CM->player = character;
	CM->GameSceneInit();

	//BoardManager 및 Board들 생성
	boardManager = new BoardManager();
	boardManager->p = character;
	boardManager->model1 = boardModel;
	boardManager->model2 = boardModel2;
	boardManager->model3 = boardModel3;
	character->boardManager = boardManager;
	int tmp = 16;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 40; j++) {
			boardManager->boards[i][j] = new Board(boardModel);
			boardManager->boards[i][j]->SetPos((float)i*tmp, 0.0f, (float)(j - 6)*tmp);
			boardManager->boards[i][j]->p = character;
			boardManager->boards[i][j]->isBreak = false;
			PushBackGameObject(boardManager->boards[i][j]);
			boardManager->boards[i][j]->myCol = NULL;
		}
	}
	PushBackGameObject(boardManager);

	//게임 매니저 생성
	gameManager = new GameManager();
	gameManager->p = character;
	gameManager->boardManager = boardManager;

	gameManager->planetModel[0] = new Model("Resource/Model/Planet/Planet_Gray.obj", "Resource/Model/Planet/Planet_Gray.png");
	gameManager->planetModel[1] = new Model("Resource/Model/Planet/Planet_Green.obj", "Resource/Model/Planet/Planet_Green.png");
	gameManager->planetModel[2] = new Model("Resource/Model/Planet/Planet_Orange.obj", "Resource/Model/Planet/Planet_Orange.png");
	gameManager->planetModel[3] = new Model("Resource/Model/Planet/Planet_Purple.obj", "Resource/Model/Planet/Planet_Purple.png");
	gameManager->planetModel[4] = new Model("Resource/Model/Planet/Planet_Red.obj", "Resource/Model/Planet/Planet_Red.png");
	gameManager->planetModel[5] = new Model("Resource/Model/Planet/Planet_Sky.obj", "Resource/Model/Planet/Planet_Sky.png");
	for (int i = 0; i < 6; i++)
		PushBackModel(gameManager->planetModel[i]);

	gameManager->stoneModel = new Model("Resource/Model/Stones/Stones.obj", "Resource/Model/Stones/Stones.png");
	gameManager->shootingStarModel = new Model("Resource/Model/ShootingStar/ShootingStar.obj", "Resource/Model/ShootingStar/ShootingStar.png");
	PushBackModel(gameManager->stoneModel);
	PushBackModel(gameManager->shootingStarModel);

	//아이템 매니저 생성
	itemManager = new ItemManager();

	itemManager->itemModel[0] = new Model("Resource/Model/Item/Item_Wind.obj", "Resource/Model/Item/Item_Wind.png");
	itemManager->itemModel[1] = new Model("Resource/Model/Item/Item_Asteroid.obj", "Resource/Model/Item/Item_Asteroid.png");
	itemManager->itemModel[2] = new Model("Resource/Model/Item/Item_Star.obj", "Resource/Model/Item/Item_Star.png");
	itemManager->itemModel[3] = new Model("Resource/Model/Item/Item_Sun.obj", "Resource/Model/Item/Item_Sun.png");
	for (int i = 0; i < 4; i++)
		PushBackModel(itemManager->itemModel[i]);

	itemManager->gemModel[0][0] = new Model("Resource/Model/Item/Gem1/Item_Gem1_1.obj", "Resource/Model/Item/Gem1/Item_Gem1_1.png");
	itemManager->gemModel[0][1] = new Model("Resource/Model/Item/Gem1/Item_Gem1_2.obj", "Resource/Model/Item/Gem1/Item_Gem1_2.png");
	itemManager->gemModel[0][2] = new Model("Resource/Model/Item/Gem1/Item_Gem1_3.obj", "Resource/Model/Item/Gem1/Item_Gem1_3.png");
	itemManager->gemModel[0][3] = new Model("Resource/Model/Item/Gem1/Item_Gem1_4.obj", "Resource/Model/Item/Gem1/Item_Gem1_4.png");
	itemManager->gemModel[0][4] = new Model("Resource/Model/Item/Gem1/Item_Gem1_5.obj", "Resource/Model/Item/Gem1/Item_Gem1_5.png");
	itemManager->gemModel[0][5] = new Model("Resource/Model/Item/Gem1/Item_Gem1_6.obj", "Resource/Model/Item/Gem1/Item_Gem1_6.png");
	itemManager->gemModel[0][6] = new Model("Resource/Model/Item/Gem1/Item_Gem1_7.obj", "Resource/Model/Item/Gem1/Item_Gem1_7.png");
	itemManager->gemModel[0][7] = new Model("Resource/Model/Item/Gem1/Item_Gem1_8.obj", "Resource/Model/Item/Gem1/Item_Gem1_8.png");

	itemManager->gemModel[1][0] = new Model("Resource/Model/Item/Gem2/Item_Gem2_1.obj", "Resource/Model/Item/Gem2/Item_Gem2_1.png");
	itemManager->gemModel[1][1] = new Model("Resource/Model/Item/Gem2/Item_Gem2_2.obj", "Resource/Model/Item/Gem2/Item_Gem2_2.png");
	itemManager->gemModel[1][2] = new Model("Resource/Model/Item/Gem2/Item_Gem2_3.obj", "Resource/Model/Item/Gem2/Item_Gem2_3.png");
	itemManager->gemModel[1][3] = new Model("Resource/Model/Item/Gem2/Item_Gem2_4.obj", "Resource/Model/Item/Gem2/Item_Gem2_4.png");
	itemManager->gemModel[1][4] = new Model("Resource/Model/Item/Gem2/Item_Gem2_5.obj", "Resource/Model/Item/Gem2/Item_Gem2_5.png");
	itemManager->gemModel[1][5] = new Model("Resource/Model/Item/Gem2/Item_Gem2_6.obj", "Resource/Model/Item/Gem2/Item_Gem2_6.png");
	itemManager->gemModel[1][6] = new Model("Resource/Model/Item/Gem2/Item_Gem2_7.obj", "Resource/Model/Item/Gem2/Item_Gem2_7.png");
	itemManager->gemModel[1][7] = new Model("Resource/Model/Item/Gem2/Item_Gem2_8.obj", "Resource/Model/Item/Gem2/Item_Gem2_8.png");

	itemManager->gemModel[2][0] = new Model("Resource/Model/Item/Gem3/Item_Gem3_1.obj", "Resource/Model/Item/Gem3/Item_Gem3_1.png");
	itemManager->gemModel[2][1] = new Model("Resource/Model/Item/Gem3/Item_Gem3_2.obj", "Resource/Model/Item/Gem3/Item_Gem3_2.png");
	itemManager->gemModel[2][2] = new Model("Resource/Model/Item/Gem3/Item_Gem3_3.obj", "Resource/Model/Item/Gem3/Item_Gem3_3.png");
	itemManager->gemModel[2][3] = new Model("Resource/Model/Item/Gem3/Item_Gem3_4.obj", "Resource/Model/Item/Gem3/Item_Gem3_4.png");
	itemManager->gemModel[2][4] = new Model("Resource/Model/Item/Gem3/Item_Gem3_5.obj", "Resource/Model/Item/Gem3/Item_Gem3_5.png");
	itemManager->gemModel[2][5] = new Model("Resource/Model/Item/Gem3/Item_Gem3_6.obj", "Resource/Model/Item/Gem3/Item_Gem3_6.png");
	itemManager->gemModel[2][6] = new Model("Resource/Model/Item/Gem3/Item_Gem3_7.obj", "Resource/Model/Item/Gem3/Item_Gem3_7.png");
	itemManager->gemModel[2][7] = new Model("Resource/Model/Item/Gem3/Item_Gem3_8.obj", "Resource/Model/Item/Gem3/Item_Gem3_8.png");
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 8; j++)
			PushBackModel(itemManager->gemModel[i][j]);
	PushBackGameObject(itemManager);

	gameManager->itemManager = itemManager;
	PushBackGameObject(gameManager);

	FILE* f;
	char b;
	int cnt = 0;
	f = fopen("Resource/gem.sav", "r");
	if (f) {
		while ((b = fgetc(f)) != EOF) {
			if (b == '1') {
				itemManager->getGem[cnt / 8][cnt % 8] = true;
			}
			cnt++;
		}
		fclose(f);
	}
	

	distanceText = new DistanceText();
	distanceText->p = character;
	for (int i = 0; i < 6; i++) {
		distanceText->number[i][0] = new UI("Resource/UI/Number/0.png", 1060 - i * 60, 976); distanceText->number[i][0]->isEnable = false;
		distanceText->number[i][1] = new UI("Resource/UI/Number/1.png", 1060 - i * 60, 976); distanceText->number[i][1]->isEnable = false;
		distanceText->number[i][2] = new UI("Resource/UI/Number/2.png", 1060 - i * 60, 976); distanceText->number[i][2]->isEnable = false;
		distanceText->number[i][3] = new UI("Resource/UI/Number/3.png", 1060 - i * 60, 976); distanceText->number[i][3]->isEnable = false;
		distanceText->number[i][4] = new UI("Resource/UI/Number/4.png", 1060 - i * 60, 976); distanceText->number[i][4]->isEnable = false;
		distanceText->number[i][5] = new UI("Resource/UI/Number/5.png", 1060 - i * 60, 976); distanceText->number[i][5]->isEnable = false;
		distanceText->number[i][6] = new UI("Resource/UI/Number/6.png", 1060 - i * 60, 976); distanceText->number[i][6]->isEnable = false;
		distanceText->number[i][7] = new UI("Resource/UI/Number/7.png", 1060 - i * 60, 976); distanceText->number[i][7]->isEnable = false;
		distanceText->number[i][8] = new UI("Resource/UI/Number/8.png", 1060 - i * 60, 976); distanceText->number[i][8]->isEnable = false;
		distanceText->number[i][9] = new UI("Resource/UI/Number/9.png", 1060 - i * 60, 976); distanceText->number[i][9]->isEnable = false;
		for (int j = 0; j < 10; j++)
			PushBackUI(distanceText->number[i][j]);
	}
	for (int i = 0; i < 6; i++) {
		distanceText->text[i] = distanceText->number[i][(distanceText->p->killo / (int)pow(10, i)) % 10];
		distanceText->text[i]->isEnable = true;
	}
	PushBackGameObject(distanceText);

	speedText = new SpeedText();
	speedText->p = character;
	for (int i = 0; i < 3; i++) {
		speedText->number[i][0] = new UI("Resource/UI/Number/0.png", 1630 - i * 60, 826); speedText->number[i][0]->isEnable = false;
		speedText->number[i][1] = new UI("Resource/UI/Number/1.png", 1630 - i * 60, 826); speedText->number[i][1]->isEnable = false;
		speedText->number[i][2] = new UI("Resource/UI/Number/2.png", 1630 - i * 60, 826); speedText->number[i][2]->isEnable = false;
		speedText->number[i][3] = new UI("Resource/UI/Number/3.png", 1630 - i * 60, 826); speedText->number[i][3]->isEnable = false;
		speedText->number[i][4] = new UI("Resource/UI/Number/4.png", 1630 - i * 60, 826); speedText->number[i][4]->isEnable = false;
		speedText->number[i][5] = new UI("Resource/UI/Number/5.png", 1630 - i * 60, 826); speedText->number[i][5]->isEnable = false;
		speedText->number[i][6] = new UI("Resource/UI/Number/6.png", 1630 - i * 60, 826); speedText->number[i][6]->isEnable = false;
		speedText->number[i][7] = new UI("Resource/UI/Number/7.png", 1630 - i * 60, 826); speedText->number[i][7]->isEnable = false;
		speedText->number[i][8] = new UI("Resource/UI/Number/8.png", 1630 - i * 60, 826); speedText->number[i][8]->isEnable = false;
		speedText->number[i][9] = new UI("Resource/UI/Number/9.png", 1630 - i * 60, 826); speedText->number[i][9]->isEnable = false;
		for (int j = 0; j < 10; j++)
			PushBackUI(speedText->number[i][j]);
	}
	for (int i = 0; i < 3; i++) {
		speedText->text[i] = speedText->number[i][((int)character ->speed / (int)pow(10, i)) % 10];
		speedText->text[i]->isEnable = true;
	}
	PushBackGameObject(speedText);

	bsText = new BestScoreText();
	bsText->p = character;
	for (int i = 0; i < 6; i++) {
		bsText->number[i][0] = new UI("Resource/UI/Number/0.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][0]->isEnable = false;
		bsText->number[i][1] = new UI("Resource/UI/Number/1.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][1]->isEnable = false;
		bsText->number[i][2] = new UI("Resource/UI/Number/2.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][2]->isEnable = false;
		bsText->number[i][3] = new UI("Resource/UI/Number/3.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][3]->isEnable = false;
		bsText->number[i][4] = new UI("Resource/UI/Number/4.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][4]->isEnable = false;
		bsText->number[i][5] = new UI("Resource/UI/Number/5.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][5]->isEnable = false;
		bsText->number[i][6] = new UI("Resource/UI/Number/6.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][6]->isEnable = false;
		bsText->number[i][7] = new UI("Resource/UI/Number/7.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][7]->isEnable = false;
		bsText->number[i][8] = new UI("Resource/UI/Number/8.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][8]->isEnable = false;
		bsText->number[i][9] = new UI("Resource/UI/Number/9.png", 1120 - i * 30, 940, 0.5f, 0.5f); bsText->number[i][9]->isEnable = false;
		for (int j = 0; j < 10; j++)
			PushBackUI(bsText->number[i][j]);
	}
	for (int i = 0; i < 6; i++) {
		bsText->text[i] = bsText->number[i][((int)character->bestScore / (int)pow(10, i)) % 10];
		bsText->text[i]->isEnable = true;
	}
	PushBackGameObject(bsText);

	//별
	whiteStar = new Model("Resource/Model/WhiteCube/Star.obj", "Resource/Model/WhiteCube/Star.png");
	bgStars = new StarManager();
	bgStars->p = character;
	PushBackGameObject(bgStars);
	for (int j = 0; j < bgStars->starcount; j++) {
		bgStars->stars[j] = new GameObject(whiteStar);
		bgStars->SetRandomPos(j);
		PushBackGameObject(bgStars->stars[j]);
	}


	//체력, mp바
	barsm[0] = new Model("Resource/Model/Bar/HpBar.obj", "Resource/Model/Bar/HpBar.png");
	bars[0] = new GameObject(barsm[0]);
	bars[0]->SetPos(96.0f, 8.0f, 0.0f);
	bars[0]->SetScale(4.0f, 40.0f, 4.0f);
	bars[0]->SetRot(1.57f, 0.0f, 0.0f);
	PushBackGameObject(bars[0]);
	barsm[1] = new Model("Resource/Model/Bar/MpBar.obj", "Resource/Model/Bar/MpBar.png");
	bars[1] = new GameObject(barsm[1]);
	bars[1]->SetPos(-16.0f,8.0f, 0.0f);
	bars[1]->SetScale(4.0f, 40.0f, 4.0f); 
	bars[1]->SetRot(1.57f, 0.0f, 0.0f);
	PushBackGameObject(bars[1]);
	character->hpBar = bars[0];
	character->mpBar = bars[1];

	moonM = new Model("Resource/Model/Moon/Moon.obj", "Resource/Model/Moon/Moon.png");
	moon = new GameObject(moonM);
	moon->SetPos(40.0f, 0.0f, 720.0f);
	moon->SetScale(2.0f, 2.0f, 2.0f);
	//moon->SetRot(0.0f, 3.14f, 0.0f);
	PushBackGameObject(moon);
	PushBackModel(moonM);
	character->moon = moon;

	CM->GameSceneInit();
}

GameScene::~GameScene()
{
}
