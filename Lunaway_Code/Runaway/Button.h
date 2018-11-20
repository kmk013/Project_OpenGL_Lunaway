#pragma once
#include "UI.h"
#include "CollectionGem.h"

class Button :
	public UI
{
public:
	enum Buttons {
		noneb,
		startb,
		collectionb,
		rankb,
		howtoplayb,
		exitb
	};
	Buttons myCase;
	bool useButton;
	bool toNext;
	bool collectionV;
	UI* collector;
	CollectionGem* cg;
public:
	Button(const char* pngPath, int x, int y, Buttons MyCase,float scaleX=1.0f, float scaleY=1.0f);
	~Button();
	void Update();
	bool CollisionCheck();
	void MakeCollection();
};

