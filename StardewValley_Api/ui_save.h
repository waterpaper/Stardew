#pragma once
#include "ui.h"
#include "gameSave.h"

enum UI_SAVEDIALOG_BUTTONKIND
{
	UI_SAVEDIALOG_BUTTONKIND_NULL,
	UI_SAVEDIALOG_BUTTONKIND_1,
	UI_SAVEDIALOG_BUTTONKIND_2,
	UI_SAVEDIALOG_BUTTONKIND_3,
	UI_SAVEDIALOG_BUTTONKIND_END
};
class ui_save:public ui
{
private:
	RECT _saveRc[3];
	image *_selectBox;
	UI_SAVEDIALOG_BUTTONKIND _buttonKind;
	gameSave _save;

	int _selectTime;
	bool _isSave;

public:
	ui_save();
	~ui_save();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
};

