#pragma once
#include "scene.h"

enum HOMETOTOWNROADSCENE_MOVE
{
	HOMETOTOWNROADSCENE_MOVE_NULL = -1,
	HOMETOTOWNROADSCENE_MOVE_FARM,
	HOMETOTOWNROADSCENE_MOVE_TOWN,
	HOMETOTOWNROADSCENE_MOVE_END
};

class homeToTownRoadScene:public scene
{
public:
	homeToTownRoadScene();
	~homeToTownRoadScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

