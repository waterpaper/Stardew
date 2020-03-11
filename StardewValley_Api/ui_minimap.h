#pragma once
#include "ui.h"

class ui_minimap:public ui
{
private:
	image *_cameraImg;

public:
	ui_minimap();
	~ui_minimap();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
};

