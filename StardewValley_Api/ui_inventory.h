#pragma once
#include "ui.h"

class ui_inventory:public ui
{
private:
	playerState _state;
	playerAvatar _avatar;
	
	int _infoItemX, _infoItemY;
	int _selectItemX, _selectItemY;
	RECT _itemRc[3][12];
	bool _isItemSelect;

public:
	ui_inventory();
	~ui_inventory();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void selectItem();
	void selectItemMove();

	virtual int getKindNum();
};

