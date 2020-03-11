#pragma once
#include "scene.h"

enum COOPSCENE_MOVE
{
	COOPSCENE_MOVE_NULL = -1,
	COOPSCENE_MOVE_FARM,
	COOPSCENE_MOVE_END
};


class coopScene:public scene
{
public:
	coopScene();
	~coopScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

