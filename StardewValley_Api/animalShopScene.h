#pragma once
#include "scene.h"

enum ANIMALSHOPSCENE_MOVE
{
	ANIMALSHOPSCENE_MOVE_NULL = -1,
	ANIMALSHOPSCENE_MOVE_TOWN,
	ANIMALSHOPSCENE_MOVE_ANIMALSHOP,
	ANIMALSHOPSCENE_MOVE_END
};

class animalShopScene:public scene
{
public:
	animalShopScene();
	~animalShopScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

