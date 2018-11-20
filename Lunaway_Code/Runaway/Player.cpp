#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "SplitPlayer.h"
#include "MainScene.h"

#include "BoardManager.h"

Player::Player(Model* MyModel) : GameObject(MyModel), speed(30.0f), lrspeed(20.0f), hp(10), maxhp(10), mp(10), phase(1), killo(0), zDistance(50.0f), isSplit(true), shootDelay(0.2f), shootTimeCheck(0.0f), isGameOver(false), speedTImer(0.0f), damage(1), bestScore(0), isEnded(false), readyToEnd(false)
{
	layer = LPlayer;
	FILE* f;
	int sc=0;
	f = fopen("Resource/mk.sav", "r");
	if (f) {
		fscanf(f, "%d", &sc);
		printf("sc : %d\n", sc);
		fclose(f);
	}
	bestScore = sc;
}


Player::~Player()
{
}

void Player::Update()
{
	CM->rad = zDistance;
	CheckBase();
	MoveFBRun(1);
	if (!isGameOver) {
		if (RUNAMM->GetMyKeyState('A') > 0) {
			if (pos.x <= 6.0f * 16.0f - 12.0f)
				MoveLR(1);
		}
		if (RUNAMM->GetMyKeyState('D') > 0) {
			if (pos.x >= 0 - 4.0f)
				MoveLR(-1);
		}
	

	if (isSplit) {
		if (shootTimeCheck <= shootDelay)
			shootTimeCheck += RUNAMM->deltaTime;
		else if (RUNAMM->GetMyKeyState(VK_SPACE) > 0) {
			Shoot();
			shootTimeCheck = 0.0f;
		}
	}

	if (RUNAMM->GetMyKeyState('R') > 0 && isSplit&&mp >= 10) {
		mp -= 10;
		Split();
	}

	//페이즈 처리
	if (phase == 1 && killo>1000) {
		++phase;
		boardManager->PhaseChange(phase);
	}
	else if (phase == 2 && killo > 5000) {
		++phase;
		boardManager->PhaseChange(phase);
	}

	
		if (hpBar) {
			hpBar->scale.y = 40.0f*(float)hp*0.1f;
			hpBar->pos.z = pos.z;
		}
		if (mpBar) {
			mpBar->scale.y = 40.0f*(float)mp*0.1f;
			mpBar->pos.z = pos.z;
		}
		

		speedTImer += RUNAMM->deltaTime;
		if (speedTImer >= 4.0f) {
			speed += speed*0.03f;
			lrspeed += speed*0.015f;
			speedTImer = 0.0f;
		}
	}

	if (hp <= 0) {
		hp = 0;
		isGameOver = true;
		useModel = false;
		//게임 종료씬 띄우기
		UI* theGameOver;
		theGameOver = new UI("Resource/UI/GameOver/GameOver.png", 0, 0);
		CURRENTSCENE->PushBackUI(theGameOver);

		if (bestScore < killo) {
			FILE* f;
			f = fopen("Resource/mk.sav", "w");
			if (f) {
				fprintf(f, "%d", killo);
				fclose(f);
			}
		}
	}
	if (isGameOver) {
		static float checker;
		checker += RUNAMM->deltaTime;
		if (checker>=2.0f) {
			readyToEnd = true;
		}
		if (isEnded) {
			 
			checker = 0.0f;
			RUNASCENEM->ChangeScene(new MainScene());
		}
	}

	if (moon) {
		moon->pos.z = pos.z + 720.0f;
	}
	/*CM->pos.z = pos.z - zDistance;
	CM->pos.x = pos.x;*/
}

void Player::MoveFB(int wtg)
{
	pos.z += speed*wtg*RUNAMM->deltaTime;

}

void Player::MoveFBRun(int wtg)
{
	pos.z += speed*2.5f*wtg*RUNAMM->deltaTime;
}

void Player::MoveLR(int wtg)
{
	pos.x += lrspeed * wtg * RUNAMM->deltaTime;
}

void Player::Shoot()
{
	Bullet *a = new Bullet(bulletModel);
	a->SetPos(pos.x, pos.y, pos.z + 8.0f);
	CURRENTSCENE->PushBackGameObject(a);
	a->myCol = new Collider(a, 2.0f);
	CURRENTSCENE->PushBackCollider(a->myCol);
	a->speed = speed * 10.0f;
}

void Player::Split() {
	printf("split\n");
	SplitPlayer* splitP[2] = {
		new SplitPlayer(myModel,true),
		new SplitPlayer(myModel,false)
	};
	myCollider->enable = false;
	splitP[0]->SetPos(pos.x, pos.y, pos.z);
	splitP[1]->SetPos(pos.x, pos.y, pos.z);
	for (int i = 0; i < 2; i++) {
		splitP[i]->SetScale(0.2f, 0.2f, 0.2f);
		splitP[i]->p = this;
		CURRENTSCENE->PushBackGameObject(splitP[i]);
		splitP[i]->myCol = new Collider(splitP[i], 12 * 0.5f);
		CURRENTSCENE->PushBackCollider(splitP[i]->myCol);
	}
	useModel = false;
	isSplit = false;
}

void Player::OnCollision(GameObject * ano)
{
	if (isSplit) {

	}
}
