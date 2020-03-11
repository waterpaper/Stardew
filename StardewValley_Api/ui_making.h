#pragma once
#include "ui.h"
class ui_making:public ui
{
public:
	ui_making();
	~ui_making();
	
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
};

