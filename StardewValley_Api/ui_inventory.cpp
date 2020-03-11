#include "stdafx.h"
#include "ui_inventory.h"


ui_inventory::ui_inventory()
{
}


ui_inventory::~ui_inventory()
{
}

HRESULT ui_inventory::init()
{
	int inventoryNum = INVENTORYMANAGER->getInventory().getInventoryLevel();

	if (inventoryNum == 1)
	{
		uiImageAdd("메뉴창_인벤토리1", 150, 50, 700, 608, false);
	}
	else if (inventoryNum ==2)
	{
		uiImageAdd("메뉴창_인벤토리2", 150, 50, 700, 608, false);
	}
	else if (inventoryNum == 3)
	{
		uiImageAdd("메뉴창_인벤토리3", 150, 50, 700, 608, false);
	}
	else
	{
		uiImageAdd("메뉴창_인벤토리1", 150, 50, 700, 608, false);
	}
	imageButtonAdd(nullptr, "", 192, 50, 54, 60, UIBUTTONKIND_INVENTORY, false);
	imageButtonAdd(nullptr, "", 246, 50, 54, 60, UIBUTTONKIND_FEELING, false);
	imageButtonAdd(nullptr, "", 300, 50, 54, 60, UIBUTTONKIND_MAP, false);
	imageButtonAdd(nullptr, "", 354, 50, 54, 60, UIBUTTONKIND_MAKING, false);
	imageButtonAdd(nullptr, "", 408, 50, 54, 60, UIBUTTONKIND_EXIT, false);
	imageButtonAdd("cancel버튼", "", 900, 50, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_state = PLAYERMANAGER->getPlayerState();
	_avatar = PLAYERMANAGER->getPlayerAvatar();

	_state.setPlayerPosition(320, 460);
	_state.setPlayerDirection(PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN);
	_state.setPlayerActiveStateNow(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			_itemRc[i][j] = RectMake(188 + 52 * j, 154 + 72 * i, 48, 48);
		}
	}

	_infoItemX = -1;
	_infoItemY = -1;
	_selectItemX = -1;
	_selectItemY = -1;

	_isItemSelect = false;

	return S_OK;
}

void ui_inventory::update()
{
	ui::update();

	if (!_isItemSelect)
	{
		selectItem();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < _vButton.size(); i++)
			{
				if (PtInRect(&_vButton[i]._rc, m_ptMouse))
				{
					if (_vButton[i]._kind == UIBUTTONKIND_FEELING)
					{
						UIMANAGER->changeUi("UI_feeling");
					}
					else if (_vButton[i]._kind == UIBUTTONKIND_MAKING)
					{
						UIMANAGER->changeUi("UI_making");
					}
					else if (_vButton[i]._kind == UIBUTTONKIND_MAP)
					{
						UIMANAGER->changeUi("UI_minimap");
					}
					else if (_vButton[i]._kind == UIBUTTONKIND_EXIT)
					{
						UIMANAGER->changeUi("UI_exit");
					}
					else if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
					{
						UIMANAGER->changeUi("UI_general");
						UIMANAGER->setIsMenu(false);
					}

					_sound.effSoundPlay("메뉴선택");
					return;
				}
			}
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_sound.effSoundPlay("메뉴선택");
			selectItemMove();
		}
	}
}

void ui_inventory::release()
{
	ui::release();

}

void ui_inventory::render(HDC hdc)
{
	char strTemp[256];
	inventory invenTemp = INVENTORYMANAGER->getInventory();
	item itemTemp;
	int inventoryMaxSize = INVENTORYMANAGER->getInventoryMaxSize();

	ui::render(hdc);

	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	//색상//글씨체 선택
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	SetTextAlign(hdc, TA_CENTER);


	sprintf(strTemp, "%s 농장", _state.getPlayerFarmName().c_str());
	TextOut(hdc, 600, 400, strTemp, strlen(strTemp));//700,400//농장이름

	sprintf(strTemp, "이름 : %s", _state.getPlayerName().c_str());
	TextOut(hdc, 600, 470, strTemp, strlen(strTemp));//이름

	sprintf(strTemp, "현재 소지금 : %s", to_string(_state.getPlayerMoney()).c_str());
	TextOut(hdc, 600, 540, strTemp, strlen(strTemp));//760,450// 돈

	SetTextAlign(hdc, TA_LEFT);


	//캐릭터 출력
	_avatar.render(hdc, _state);


	//아이템 출력
	SelectObject(hdc, hMediumFont);
	SetTextColor(hdc, RGB(255, 255, 225));
	SetTextAlign(hdc, TA_RIGHT);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			itemTemp = invenTemp.getItem(j, i);

			if (itemTemp.getItemCategory() == ITEMKIND_NULL || itemTemp.getItemImg() == nullptr)	continue;

			//선택된 아이템인 경우
			if (_isItemSelect&&_selectItemX == j && _selectItemY == i)
			{
				itemTemp.getItemImg()->frameRender(hdc, m_ptMouse.x+24, m_ptMouse.y, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);
				continue;
			}

			itemTemp.getItemImg()->frameRender(hdc, _itemRc[i][j].left, _itemRc[i][j].top, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);

			if (itemTemp.getItemNum() < 2)	continue;

			TextOut(hdc, _itemRc[i][j].left + 46, _itemRc[i][j].top + 25, to_string(itemTemp.getItemNum()).c_str(), to_string(itemTemp.getItemNum()).size());
		}
	}
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	SetTextAlign(hdc, TA_LEFT);

	//아이템 정보 출력 필요시 출력
	if (_infoItemX != -1)
	{
		itemTemp = invenTemp.getItem(_infoItemX, _infoItemY);

		if (itemTemp.getItemCategory() != ITEMKIND_NULL || itemTemp.getItemImg() != nullptr)
		{
			itemTemp.informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y + 48);
		}
	}
}

void ui_inventory::selectItem()
{
	if (PtInRect(&_vUiImage[0].rc, m_ptMouse))
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (PtInRect(&_itemRc[i][j], m_ptMouse))
				{
					_infoItemX = j;
					_infoItemY = i;

					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_sound.effSoundPlay("메뉴선택");
						//아이템 선택시
						_isItemSelect = true;
						_infoItemX = -1;
						_infoItemY = -1;
						_selectItemX = j;
						_selectItemY = i;
					}
					return;
				}
			}
		}
	}
	else
	{
		_infoItemX = -1;
		_infoItemY = -1;
	}
}

void ui_inventory::selectItemMove()
{
	item selectItem, sourItem;

	if (PtInRect(&_vUiImage[0].rc, m_ptMouse))
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (PtInRect(&_itemRc[i][j], m_ptMouse))
				{
					if (i * 12 + j >= INVENTORYMANAGER->getInventoryMaxSize())
					{
						_selectItemX = -1;
						_selectItemY = -1;
						_isItemSelect = false;
						return;
					}
					sourItem = INVENTORYMANAGER->getItem(j,i);
					selectItem = INVENTORYMANAGER->getItem(_selectItemX, _selectItemY);

					INVENTORYMANAGER->addInventoryNum(-2);
					INVENTORYMANAGER->addItem(sourItem, _selectItemX, _selectItemY);
					INVENTORYMANAGER->addItem(selectItem, j, i);

					_selectItemX = -1;
					_selectItemY = -1;
					_isItemSelect = false;

					return;
				}

			}
		}
	}
	_isItemSelect = false;
}

int ui_inventory::getKindNum()
{
	return UIMANAGER->getSelectItem();
}
