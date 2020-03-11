#include "stdafx.h"
#include "ui_save.h"


ui_save::ui_save()
{

}


ui_save::~ui_save()
{

}

HRESULT ui_save::init()
{
	UIMANAGER->setIsConversation(true);

	uiImageAdd("대화UI_선택", 100, 450, 800, 228, false, false);
	imageButtonAdd("cancel버튼", "", 900, 400, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_saveRc[0] = RectMake(132, 546, 201, 96);
	_saveRc[1] = RectMake(333, 546, 201, 96);
	_saveRc[2] = RectMake(534, 546, 201, 96);

	_selectBox = IMAGEMANAGER->findImage("UI_선택박스2");
	_isSave = false;
	_selectTime = 0;

	return S_OK;
}

void ui_save::update()
{
	ui::update();
	
	if (_isSave&&GetTickCount() - _selectTime > 1000)
	{
		GAMETIMEMANAGER->nextDay();
		UIMANAGER->setIsConversation(false);
		UIMANAGER->changeUi("UI_general");
		return;
	}

	if (PtInRect(&_saveRc[0], m_ptMouse))
	{
		_buttonKind = UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_1;
	}
	else if (PtInRect(&_saveRc[1], m_ptMouse))
	{
		_buttonKind = UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_2;
	}
	else if (PtInRect(&_saveRc[2], m_ptMouse))
	{
		_buttonKind = UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_3;
	}
	else
	{
		_buttonKind = UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_NULL;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
				{
					UIMANAGER->setIsConversation(false);
					UIMANAGER->changeUi("UI_general");
				}
			}
		}
		if (PtInRect(&_saveRc[0], m_ptMouse))
		{
			_save.nowGameSave(1);
			_selectTime = GetTickCount();
			_isSave = true;
		}
		else if (PtInRect(&_saveRc[1], m_ptMouse))
		{
			_save.nowGameSave(2);
			_selectTime = GetTickCount();
			_isSave = true;
		}
		else if (PtInRect(&_saveRc[2], m_ptMouse))
		{
			_save.nowGameSave(3);
			_selectTime = GetTickCount();
			_isSave = true;
		}
	}
}

void ui_save::release()
{
	ui::release();
}

void ui_save::render(HDC hdc)
{
	char strTemp[512];
	
	if (_isSave)
	{
		IMAGEMANAGER->render("UI_로딩화면", hdc, 0, 0);
		return;
	}

	ui::render(hdc);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	sprintf(strTemp, "잠을 자시겠습니까?");
	TextOut(hdc, 148, 482, strTemp, strlen(strTemp));

	sprintf(strTemp, "1번");
	DrawText(hdc, strTemp, strlen(strTemp), &_saveRc[0], DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	sprintf(strTemp, "2번");
	DrawText(hdc, strTemp, strlen(strTemp), &_saveRc[1], DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	sprintf(strTemp, "3번");
	DrawText(hdc, strTemp, strlen(strTemp), &_saveRc[2], DT_CENTER | DT_VCENTER | DT_WORDBREAK);


	//마우스가 근처에 있을시 박스를 그려준다
	if (_buttonKind == UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_1)
	{
		_selectBox->render(hdc, _saveRc[0].left, _saveRc[0].top, _saveRc[0].right - _saveRc[0].left, _saveRc[0].bottom - _saveRc[0].top);
	}
	else if (_buttonKind == UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_2)
	{
		_selectBox->render(hdc, _saveRc[1].left, _saveRc[1].top, _saveRc[1].right - _saveRc[1].left, _saveRc[1].bottom - _saveRc[1].top);
	}
	else if (_buttonKind == UI_SAVEDIALOG_BUTTONKIND::UI_SAVEDIALOG_BUTTONKIND_3)
	{
		_selectBox->render(hdc, _saveRc[2].left, _saveRc[2].top, _saveRc[2].right - _saveRc[2].left, _saveRc[2].bottom - _saveRc[2].top);
	}
}
