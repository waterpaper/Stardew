#pragma once
#include "scene.h"

enum BARNSCENE_MOVE
{
	BARNSCENE_MOVE_NULL = -1,
	BARNSCENE_MOVE_FARM,
	BARNSCENE_MOVE_END
};

class barnScene:public scene
{

public:
	barnScene();
	~barnScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

