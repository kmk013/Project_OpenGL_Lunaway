#pragma once
#include "Scene.h"
#include "Button.h"
#include "EmptyObject.h"
#include "StarManager.h"
#include "CollectionGem.h"

class MainScene :
	public Scene
{
	Button* mainLogo;
	Button* gameStartButton;
	Button* myCollectionButton;
	Button* rankButton;
	Button* howToPlayButton;
	Button* exitButton;
	UI* title;

	StarManager* bgStars;
	StarManager* bgStars2;
	Model* whiteStar;

	CollectionGem* collectionGem;

	Model* plm;
	Model* moom;
	GameObject* pl;
	GameObject* moo;
public:
	MainScene();
	~MainScene();
};

