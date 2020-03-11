#include "stdafx.h"
#include "ui_general.h"


ui_general::ui_general()
{
}


ui_general::~ui_general()
{
}

HRESULT ui_general::init()
{
	uiImageAdd("화면UI_timer", WINSIZEX - 230, 0, 230, 183, 0, true);
	uiImageAdd("화면UI_HpEnergyBar", WINSIZEX - 150, WINSIZEY - 200, 90, 180, 0, false);
	uiImageAdd("화면UI_HpBar_Front", WINSIZEX - 140, WINSIZEY - 160, 20, 132, 0, false);
	uiImageAdd("화면UI_EnergyBar_Front", WINSIZEX - 90, WINSIZEY - 160, 20, 132, 0, false);
	uiImageAdd("화면UI_MainInventory", 120, WINSIZEY - 150, 655, 90, 0, false);

	for (int i = 0; i < 12; i++)
	{
		_selectItemRc[i] = RectMake(136 + 52 * i, WINSIZEY - 150 + 22, 48, 48);
	}

	_isBottomInventory = true;
	_selectItem = UIMANAGER->getSelectItem();
	_infoItem = -1;

	return S_OK;
}

void ui_general::update()
{
	ui::update();
	keyboardInput();

	_state = PLAYERMANAGER->getPlayerState();


	//위치에 따라서 인벤토리창을 바꿔준다
	if (!CAMERAMANAGER->getIsBottomCamera() && _isBottomInventory == true)
	{
		_vUiImage[4].startY = 60;
		_vUiImage[4].rc = RectMake(120, 60, 655, 90);

		for (int i = 0; i < 12; i++)
		{
			_selectItemRc[i] = RectMake(136 + 52 * i, 60 + 22, 48, 48);
		}
		_isBottomInventory = false;
	}
	else if (CAMERAMANAGER->getIsBottomCamera() && _isBottomInventory == false)
	{
		_vUiImage[4].startY = WINSIZEY - 150;
		_vUiImage[4].rc = RectMake(120, WINSIZEY - 150, 655, 90);

		for (int i = 0; i < 12; i++)
		{
			_selectItemRc[i] = RectMake(136 + 52 * i, WINSIZEY - 150 + 22, 48, 48);
		}
		_isBottomInventory = true;
	}

	//인벤토리입력을 처리한다
	inventorySelect();

	//체력바를 조정한다
	_vUiImage[2].height = (double)_state.getPlayerHp() / _state.getPlayerMaxHp() * 132;
	_vUiImage[2].startY = _vUiImage[2].rc.bottom - _vUiImage[2].height;
	_vUiImage[3].height = (double)_state.getPlayerActingPower() / _state.getPlayerActingPowerMax() * 132;
	_vUiImage[3].startY = _vUiImage[3].rc.bottom - _vUiImage[3].height;
}

void ui_general::release()
{
	ui::release();
	UIMANAGER->setSelectItem(_selectItem);
}

void ui_general::render(HDC hdc)
{
	char strTemp[256];
	inventory invenTemp = INVENTORYMANAGER->getInventory();
	item itemTemp;
	gameTimeValue timeTemp = GAMETIMEMANAGER->getGameTime();

	timeBarChange(timeTemp.hour);

	ui::render(hdc);

	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	//색상//글씨체 선택
	SelectObject(hdc, hMediumFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	SetTextAlign(hdc, TA_RIGHT);

	sprintf(strTemp, "%s , %d", weekPrint(timeTemp.week).c_str(), timeTemp.date);
	TextOut(hdc, WINSIZEX - 50, 13, strTemp, strlen(strTemp));//요일

	if (timeTemp.min == 0)
	{
		if (timeTemp.hour > 12)
		{
			sprintf(strTemp, "%d:00, 오후", timeTemp.hour - 12);
		}
		else
		{
			sprintf(strTemp, "%d:00, 오전", timeTemp.hour);
		}
		TextOut(hdc, WINSIZEX - 30, 86, strTemp, strlen(strTemp));//시간
	}
	else
	{
		if (timeTemp.hour > 12)
		{
			sprintf(strTemp, "%d:%d, 오후", timeTemp.hour - 12, timeTemp.min);
		}
		else
		{
			sprintf(strTemp, "%d:%d, 오전", timeTemp.hour, timeTemp.min);
		}

		TextOut(hdc, WINSIZEX - 30, 86, strTemp, strlen(strTemp));//시간
	}

	SelectObject(hdc, hFont);
	TextOut(hdc, WINSIZEX - 23, 138, to_string(_state.getPlayerMoney()).c_str(), to_string(_state.getPlayerMoney()).size());//760,450// 돈

	//아이템 출력
	for (int i = 0; i < 12; i++)
	{
		itemTemp = invenTemp.getItem(i, 0);

		if (itemTemp.getItemCategory() == ITEMKIND_NULL || itemTemp.getItemImg() == nullptr)	continue;

		itemTemp.getItemImg()->frameRender(hdc, _selectItemRc[i].left, _selectItemRc[i].top, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);

		if (itemTemp.getItemNum() < 2)	continue;

		SelectObject(hdc, hMediumFont);
		SetTextColor(hdc, RGB(255, 255, 225));
		TextOut(hdc, _selectItemRc[i].left + 46, _selectItemRc[i].top + 25, to_string(itemTemp.getItemNum()).c_str(), to_string(itemTemp.getItemNum()).size());
	}

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	SetTextAlign(hdc, TA_LEFT);

	//아이템 정보 출력 필요시 출력
	if (_infoItem != -1)
	{
		itemTemp = invenTemp.getItem(_infoItem, 0);

		if (itemTemp.getItemCategory() != ITEMKIND_NULL || itemTemp.getItemImg() != nullptr)
		{
			if (_isBottomInventory == true)
			{
				itemTemp.informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y + 48 - 431);
			}
			else
			{
				itemTemp.informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y + 48);
			}
		}
	}

	//선택된 아이템박스
	IMAGEMANAGER->render("UI_선택박스", hdc, _selectItemRc[_selectItem].left, _selectItemRc[_selectItem].top);

	//체력바 , 행동력바 확인
	if (PtInRect(&_vUiImage[2].rc, m_ptMouse))
	{
		//배경모드
		SetBkMode(hdc, TRANSPARENT);
		//색상
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf(strTemp, "%d / %d", _state.getPlayerHp(), _state.getPlayerMaxHp());
		TextOut(hdc, m_ptMouse.x - 200, m_ptMouse.y - 30, strTemp, strlen(strTemp));

		SetTextColor(hdc, RGB(183, 89, 20));

	}
	else if (PtInRect(&_vUiImage[3].rc, m_ptMouse))
	{
		//배경모드
		SetBkMode(hdc, TRANSPARENT);
		//색상
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf(strTemp, "%d / %d", _state.getPlayerActingPower(), _state.getPlayerActingPowerMax());
		TextOut(hdc, m_ptMouse.x - 200, m_ptMouse.y - 30, strTemp, strlen(strTemp));

		SetTextColor(hdc, RGB(183, 89, 20));
	}
}

void ui_general::keyboardInput()
{
	if(KEYMANAGER->isOnceKeyDown('1'))
	{ 
		_selectItem = 0;
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_selectItem = 1;
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_selectItem = 2;
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_selectItem = 3;
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_selectItem = 4;
	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_selectItem = 5;
	}
	else if (KEYMANAGER->isOnceKeyDown('7'))
	{
		_selectItem = 6;
	}
	else if (KEYMANAGER->isOnceKeyDown('8'))
	{
		_selectItem = 7;
	}
	else if (KEYMANAGER->isOnceKeyDown('9'))
	{
		_selectItem = 8;
	}
	else if (KEYMANAGER->isOnceKeyDown('0'))
	{
		_selectItem = 9;
	}
	else
	{
		return;
	}

	//선택된 아이템이 플레이어 동작변화를 일으켜야 하는 경우 처리
	if (INVENTORYMANAGER->getItem(_selectItem, 0).getItemCategory() == ITEMKIND_NULL ||
		INVENTORYMANAGER->getItem(_selectItem, 0).getItemCategory() == ITEMKIND_EQUIPMENT ||
		INVENTORYMANAGER->getItem(_selectItem, 0).getItemCategory() == ITEMKIND_TOOL)
	{
		PLAYERMANAGER->setPlayerAvatarMoveSetting();
	}
	else
	{
		PLAYERMANAGER->setPlayerAvatarTakeMoveSetting();
	}
}

void ui_general::inventorySelect()
{
	if (PtInRect(&_vUiImage[4].rc, m_ptMouse))
	{
		for (int i = 0; i < 12; i++)
		{
			if (PtInRect(&_selectItemRc[i], m_ptMouse))
			{
				_infoItem = i;

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_sound.effSoundPlay("메뉴선택");
					_selectItem = i;
					
					//선택된 아이템이 플레이어 동작변화를 일으켜야 하는 경우 처리
					if (INVENTORYMANAGER->getItem(i, 0).getItemCategory() == ITEMKIND_NULL ||
						INVENTORYMANAGER->getItem(i, 0).getItemCategory() == ITEMKIND_EQUIPMENT ||
						INVENTORYMANAGER->getItem(i, 0).getItemCategory() == ITEMKIND_TOOL)
					{
						PLAYERMANAGER->setPlayerAvatarMoveSetting();
					}
					else
					{
						PLAYERMANAGER->setPlayerAvatarTakeMoveSetting();
					}
				}
				break;
			}
		}
	}
	else
	{
		_infoItem = -1;
	}
}

string ui_general::weekPrint(int week)
{
	string str;

	if (week == WEEK_MONDAY)
	{
		str = "월";
	}
	else if (week == WEEK_TUESDAY)
	{
		str = "화";
	}
	else if (week == WEEK_WEDNESDAY)
	{
		str = "수";
	}
	else if (week == WEEK_THURSDAY)
	{
		str = "목";
	}
	else if (week == WEEK_FRIDAY)
	{
		str = "금";
	}
	else if (week == WEEK_SATURDAY)
	{
		str = "토";
	}
	else if (week == WEEK_SUNDAY)
	{
		str = "일";
	}

	return str;
}

void ui_general::timeBarChange(int hour)
{
	if (6 <= hour && hour < 8)
	{
		_vUiImage[0].uiImg->setFrameX(0);
	}
	else if (8 <= hour && hour < 10)
	{
		_vUiImage[0].uiImg->setFrameX(1);
	}
	else if (10 <= hour && hour < 12)
	{
		_vUiImage[0].uiImg->setFrameX(2);
	}
	else if (12 <= hour && hour < 14)
	{
		_vUiImage[0].uiImg->setFrameX(3);
	}
	else if (14 <= hour && hour < 16)
	{
		_vUiImage[0].uiImg->setFrameX(4);
	}
	else if (16 <= hour && hour < 18)
	{
		_vUiImage[0].uiImg->setFrameX(5);
	}
	else if (18 <= hour && hour < 20)
	{
		_vUiImage[0].uiImg->setFrameX(6);
	}
	else if (20 <= hour && hour < 22)
	{
		_vUiImage[0].uiImg->setFrameX(7);
	}
	else
	{
		_vUiImage[0].uiImg->setFrameX(8);
	}
}
