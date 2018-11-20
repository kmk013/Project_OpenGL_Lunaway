#include "stdafx.h"
#include "Button.h"
#include "Camera.h"
#include "MessageManager.h"
#include "TestScene.h"
#include "SceneManager.h"
#include "GameScene.h"


Button::Button(const char* pngPath, int x, int y, Buttons MyCase, float scaleX, float scaleY) : UI(pngPath, x, y, scaleX, scaleY), useButton(true), myCase(MyCase), toNext(false), collectionV(false)
{

}


Button::~Button()
{
}

void Button::Update()
{
	//printf("%d\t%d\n", RUNAMM->mouseX, CM->screenHeight - RUNAMM->mouseY);
	//if (myCase == startb) {
	//	printf("%f\t%f\t%f\t%f\n", pos.x, pos.x + textureWidth * scale.x, pos.y, pos.y + textureHeight * scale.y);
	//}
	if (toNext) {
		RUNASCENEM->ChangeScene(new GameScene());
	}
	if (RUNAMM->mouseLClicked && CollisionCheck()) {
		if (myCase == startb) {
			UI* tmp = new UI("Resource/UI/MainScene/Loading.png", 1328, 103);
			toNext = true;
			CURRENTSCENE->PushBackUI(tmp);
		}
		else if (myCase == collectionb && !collectionV) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 8; j++) {
					cg->spriteGem[i][j]->isEnable = false;
				}
			}
			MakeCollection();
		}
		else if (myCase == exitb) {
			RUNAMM->CloseMyWindow();
		}
	}
	if (myCase == collectionb) {
		if (collectionV&&RUNAMM->GetMyKeyState(VK_ESCAPE)) {
			collectionV = false;
			cg->collector->isEnable = false;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 8; j++) {
					cg->spriteGem[i][j]->isEnable = false;
				}
			}
		}


	}
}

bool Button::CollisionCheck()
{
	float my = CM->screenHeight - RUNAMM->mouseY;
	float mx = RUNAMM->mouseX;
	float pl = pos.x;
	float pr = pos.x + textureWidth*scale.x;
	float pt = pos.y + textureHeight*scale.y;
	float pb = pos.y;
	if ((int)my >= pb&&my <= pt && (int)mx >= pl&&mx <= pr) {
		return true;
	}
	return false;
}

void Button::MakeCollection()
{
	cg->collector->isEnable = true;
	collectionV = true;
	FILE* f;
	char b;
	int cnt = 0;
	f = fopen("Resource/gem.sav", "r");
	if (f) {
		while ((b = fgetc(f)) != EOF) {
			if (b == '1') {
				cg->spriteGem[cnt / 8][cnt % 8]->isEnable = true;
			}
			cnt++;
		}
		fclose(f);
	}
	printf("»ý¼º");
}


