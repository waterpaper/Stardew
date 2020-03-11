#pragma once
#include "ui.h"

class ui_animalshop:public ui
{
private:
	RECT _animalRc[3][3];


public:
	ui_animalshop();
	~ui_animalshop();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
};

