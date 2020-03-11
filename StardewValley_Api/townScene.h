#pragma once
#include "scene.h"

enum TOWNSCENE_MOVE
{
	TOWNSCENE_MOVE_NULL = -1,
	TOWNSCENE_MOVE_SHOP,
	TOWNSCENE_MOVE_ANIMALSHOP,
	TOWNSCENE_MOVE_HOMETOTOWN,
	TOWNSCENE_MOVE_END
};

class townScene:public scene
{
public:
	townScene();
	~townScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

