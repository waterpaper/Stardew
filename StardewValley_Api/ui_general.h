#pragma once
#include "ui.h"

class ui_general :public ui
{
private:
	playerState _state;
	RECT _selectItemRc[12];

	int _infoItem;
	int _selectItem;
	bool _isBottomInventory;

public:
	ui_general();
	~ui_general();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void keyboardInput();

	void inventorySelect();
	string weekPrint(int week);

	//���� ���õ� �������� ��ȣ�� ��ȯ�Ѵ�
	virtual int getKindNum() { return _selectItem; };
	void timeBarChange(int hour);
};

