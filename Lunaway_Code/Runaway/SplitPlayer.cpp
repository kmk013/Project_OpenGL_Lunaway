#include "stdafx.h"
#include "SplitPlayer.h"
#include "Bullet.h"

SplitPlayer::SplitPlayer(Model* m, bool isL) : Player(m)
{
	layer = LPlayer;
	if (isL)
		isLeft = 1;
	else
		isLeft = -1;
}


SplitPlayer::~SplitPlayer()
{
}

void SplitPlayer::Update() {

	if (RUNAMM->GetMyKeyState('A') > 0) {
		if (pos.x <= 6.0f * 16.0f + isLeft*16.0f - 12.0f)
			MoveLR(1);
	}
	if (RUNAMM->GetMyKeyState('D') > 0) {
		if (pos.x >= isLeft*16.0f - 4.0f)
			MoveLR(-1);
	}

	if (shootTimeCheck <= shootDelay)
		shootTimeCheck += RUNAMM->deltaTime;
	else if (RUNAMM->GetMyKeyState(VK_SPACE) > 0) {
		Shoot();
		shootTimeCheck = 0.0f;
	}

	if (destroyTimeCheck <= destroyDelay) {
		destroyTimeCheck += RUNAMM->deltaTime;
		SplitMove();
	}
	else {
		Combine();
	}
}

void SplitPlayer::MoveFB(int wtg)
{
	pos.z += speed*wtg*RUNAMM->deltaTime;

}

void SplitPlayer::MoveFBRun(int wtg)
{
	pos.z += speed*2.5f*wtg*RUNAMM->deltaTime;
}

void SplitPlayer::MoveLR(int wtg)
{
	pos.x += lrspeed * wtg * RUNAMM->deltaTime;
}

void SplitPlayer::Shoot()
{
	Bullet *a = new Bullet(p->bulletModel);
	a->SetPos(pos.x, pos.y, pos.z + 8.0f);
	CURRENTSCENE->PushBackGameObject(a);
	a->myCol = new Collider(a, 2.0f);
	CURRENTSCENE->PushBackCollider(a->myCol);
	a->speed = speed * 10.0f;
}

void SplitPlayer::OnCollision(GameObject* ano) {
	//거의 Player클래스랑 비슷하게 하면 됨
}

void SplitPlayer::Combine()
{
	if (currentDistance > 0.0f) {
		float m = RUNAMM->deltaTime*splitspeed;
		currentDistance -= m;
		pos.x -= isLeft*m;
	}
	else {
		p->useModel = true;
		p->isSplit = true;
		p->myCollider->enable = true;
		Destroy();
		myCol->Destroy();
	}
	pos.z = p->pos.z;
}

void SplitPlayer::SplitMove()
{
	if (currentDistance < 16.0f) {
		float m = RUNAMM->deltaTime*splitspeed;
		currentDistance += m;
		pos.x += isLeft*m;
		if (currentDistance >= 16.0f)
			pos.x = p->pos.x + 16.0f*isLeft;
	}
	pos.z = p->pos.z;
}