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
	uiImageAdd("ȭ��UI_timer", WINSIZEX - 230, 0, 230, 183, 0, true);
	uiImageAdd("ȭ��UI_HpEnergyBar", WINSIZEX - 150, WINSIZEY - 200, 90, 180, 0, false);
	uiImageAdd("ȭ��UI_HpBar_Front", WINSIZEX - 140, WINSIZEY - 160, 20, 132, 0, false);
	uiImageAdd("ȭ��UI_EnergyBar_Front", WINSIZEX - 90, WINSIZEY - 160, 20, 132, 0, false);
	uiImageAdd("ȭ��UI_MainInventory", 120, WINSIZEY - 150, 655, 90, 0, false);

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


	//��ġ�� ���� �κ��丮â�� �ٲ��ش�
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

	//�κ��丮�Է��� ó���Ѵ�
	inventorySelect();

	//ü�¹ٸ� �����Ѵ�
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

	//�����
	SetBkMode(hdc, TRANSPARENT);
	//����//�۾�ü ����
	SelectObject(hdc, hMediumFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	SetTextAlign(hdc, TA_RIGHT);

	sprintf(strTemp, "%s , %d", weekPrint(timeTemp.week).c_str(), timeTemp.date);
	TextOut(hdc, WINSIZEX - 50, 13, strTemp, strlen(strTemp));//����

	if (timeTemp.min == 0)
	{
		if (timeTemp.hour > 12)
		{
			sprintf(strTemp, "%d:00, ����", timeTemp.hour - 12);
		}
		else
		{
			sprintf(strTemp, "%d:00, ����", timeTemp.hour);
		}
		TextOut(hdc, WINSIZEX - 30, 86, strTemp, strlen(strTemp));//�ð�
	}
	else
	{
		if (timeTemp.hour > 12)
		{
			sprintf(strTemp, "%d:%d, ����", timeTemp.hour - 12, timeTemp.min);
		}
		else
		{
			sprintf(strTemp, "%d:%d, ����", timeTemp.hour, timeTemp.min);
		}

		TextOut(hdc, WINSIZEX - 30, 86, strTemp, strlen(strTemp));//�ð�
	}

	SelectObject(hdc, hFont);
	TextOut(hdc, WINSIZEX - 23, 138, to_string(_state.getPlayerMoney()).c_str(), to_string(_state.getPlayerMoney()).size());//760,450// ��

	//������ ���
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

	//������ ���� ��� �ʿ�� ���
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

	//���õ� �����۹ڽ�
	IMAGEMANAGER->render("UI_���ùڽ�", hdc, _selectItemRc[_selectItem].left, _selectItemRc[_selectItem].top);

	//ü�¹� , �ൿ�¹� Ȯ��
	if (PtInRect(&_vUiImage[2].rc, m_ptMouse))
	{
		//�����
		SetBkMode(hdc, TRANSPARENT);
		//����
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf(strTemp, "%d / %d", _state.getPlayerHp(), _state.getPlayerMaxHp());
		TextOut(hdc, m_ptMouse.x - 200, m_ptMouse.y - 30, strTemp, strlen(strTemp));

		SetTextColor(hdc, RGB(183, 89, 20));

	}
	else if (PtInRect(&_vUiImage[3].rc, m_ptMouse))
	{
		//�����
		SetBkMode(hdc, TRANSPARENT);
		//����
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

	//���õ� �������� �÷��̾� ���ۺ�ȭ�� �����Ѿ� �ϴ� ��� ó��
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
					_sound.effSoundPlay("�޴�����");
					_selectItem = i;
					
					//���õ� �������� �÷��̾� ���ۺ�ȭ�� �����Ѿ� �ϴ� ��� ó��
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
		str = "��";
	}
	else if (week == WEEK_TUESDAY)
	{
		str = "ȭ";
	}
	else if (week == WEEK_WEDNESDAY)
	{
		str = "��";
	}
	else if (week == WEEK_THURSDAY)
	{
		str = "��";
	}
	else if (week == WEEK_FRIDAY)
	{
		str = "��";
	}
	else if (week == WEEK_SATURDAY)
	{
		str = "��";
	}
	else if (week == WEEK_SUNDAY)
	{
		str = "��";
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
