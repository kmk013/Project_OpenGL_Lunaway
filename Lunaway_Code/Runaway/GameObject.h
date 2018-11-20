#pragma once
#include "stdafx.h"
#include "GraphicManager.h"
class GameObject
{
public:
	enum ObjectLayer {
		LOther,
		LPlayer,
		LBullet,
		LCrush,
		LItem,
		LFloor,
	};
	enum ItemLayout {
		LWind,
		LAsteroid,
		LSun,
		LGem,
		LStar,
	};
private:
	bool isEnabled;
public:
	Vec3 pos;
	Vec3 rot;
	Vec3 scale;
	Model* myModel;
	ObjectLayer layer;
	bool useModel;
	bool isDestroyed;
	bool isBreak = false;
	
	GameObject();
	GameObject(Model* MyModel);
	virtual ~GameObject();
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRot(float x, float y, float z);
	void MawaruX();
	void MawaruY();
	void MawaruZ();
	void CheckBase();
	virtual void Update();
	virtual void LateUpdate() {};
	virtual void OnCollision(GameObject* ano) {};
	void Destroy();
	virtual void OnDestroy() {}
};

