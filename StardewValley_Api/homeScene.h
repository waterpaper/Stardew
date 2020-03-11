#pragma once
#include "scene.h"

enum HOMESCENE_MOVE
{
	HOMESCENE_MOVE_NULL = -1,
	HOMESCENE_MOVE_FARM,
	HOMESCENE_MOVE_SAVE,
	HOMESCENE_MOVE_END
};

class homeScene:public scene
{
private:

public:
	homeScene();
	~homeScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

