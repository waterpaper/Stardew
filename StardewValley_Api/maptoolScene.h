#pragma once
#include "scene.h"

class maptoolScene :public scene
{
private:
	maptool_main *_maptool;
	maptool_sub* _sub;

public:
	maptoolScene();
	~maptoolScene();

	HRESULT init();
	void update();
	void render();
	void release();
};

