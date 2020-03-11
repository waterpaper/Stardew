#pragma once
#include "scene.h"

enum FARMSCENE_MOVE
{
	FARMSCENE_MOVE_NULL = -1,
	FARMSCENE_MOVE_HOME,
	FARMSCENE_MOVE_COOP,
	FARMSCENE_MOVE_BARN,
	FARMSCENE_MOVE_HOMETOTOWNROAD,
	FARMSCENE_MOVE_END
};

class farmScene:public scene
{
public:
	farmScene();
	~farmScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

