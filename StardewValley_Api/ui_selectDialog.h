#pragma once
#include "ui.h"
#include "animal.h"

enum UI_SELECTDIALOGKIND
{
	UI_SELECTDIALOGKIND_NULL,
	UI_SELECTDIALOGKIND_EATTINGITEM,
	UI_SELECTDIALOGKIND_INVENTORYEXPAND,
	UI_SELECTDIALOGKIND_ANIMALSELECT,
	UI_SELECTDIALOGKIND_NOTMONEY,
	UI_SELECTDIALOGKIND_END
};
enum UI_SELECTDIALOG_BUTTONKIND
{
	UI_SELECTDIALOG_BUTTONKIND_NULL,
	UI_SELECTDIALOG_BUTTONKIND_YES,
	UI_SELECTDIALOG_BUTTONKIND_NO,
	UI_SELECTDIALOG_BUTTONKIND_END
};

class ui_selectDialog:public ui
{
private:
	int _invenLevel;
	int _num, _possibleMoney,_animalMoney;
	item _itemTemp;
	UI_SELECTDIALOG_BUTTONKIND _buttonKind;
	UI_SELECTDIALOGKIND _kind;
	ANIMAL_KIND _animalKind;

	image *_selectBox;
	RECT _yesRect, _noRect;

public:
	ui_selectDialog();
	~ui_selectDialog();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	virtual int getKindNum();
};

