#include "stdafx.h"
#include "ui_shop.h"


ui_shop::ui_shop()
{
}


ui_shop::~ui_shop()
{
	release();
}

HRESULT ui_shop::init()
{
	uiImageAdd("상점UI_상점창", 70, 80, 893, 595, false);
	imageButtonAdd(nullptr, "", 940, 90, 25, 25, UI_SHOPBUTTONKIND_UP, false);
	imageButtonAdd(nullptr, "", 940, 425, 25, 25, UI_SHOPBUTTONKIND_DOWN, false);
	imageButtonAdd("상점UI_상점창휠버튼", "", 945, 120, 13, 22, UI_SHOPBUTTONKIND_WHEELBUTTON, false);
	imageButtonAdd("cancel버튼", "", 910, 70, 35, 25, UI_SHOPBUTTONKIND_EXIT, true);

	_shop = new shop();
	_shop->init();

	_itemBottomNum = 4;
	_itemMaxNum = _shop->getItemMaxNum();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			_itemInvenRc[i][j] = RectMake(292 + 52 * j, 484 + 64 * i, 48, 48);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_itemShopRc[i] = RectMake(292, 96 + 86 * i, 624, 80);
	}

	_infoItemX = -1;
	_infoItemY = -1;
	_infoShopItem = -1;

	return S_OK;
}

void ui_shop::update()
{
	ui::update();

	selectItem();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				_sound.effSoundPlay("메뉴선택");
				if (_vButton[i]._kind == UI_SHOPBUTTONKIND_UP)
				{
					if (_itemBottomNum <= 4) break;

					_itemBottomNum--;
					wheelButtonMove();
				}
				else if (_vButton[i]._kind == UI_SHOPBUTTONKIND_DOWN)
				{
					if (_itemMaxNum <= _itemBottomNum) break;

					_itemBottomNum++;
					wheelButtonMove();
				}
				else if (_vButton[i]._kind == UI_SHOPBUTTONKIND_WHEELBUTTON)
				{

				}
				else if (_vButton[i]._kind == UI_SHOPBUTTONKIND_EXIT)
				{
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsMenu(false);
					UIMANAGER->setIsShop(false);
				}
				break;
			}
		}
	}
}

void ui_shop::release()
{
	ui::release();

	_shop->clearItem();
	SAFE_DELETE(_shop);
}

void ui_shop::render(HDC hdc)
{
	ui::render(hdc);

	char strTemp[256];
	inventory invenTemp = INVENTORYMANAGER->getInventory();
	item itemTemp;
	int inventoryMaxSize = INVENTORYMANAGER->getInventoryMaxSize();
	int money = PLAYERMANAGER->getPlayerMoney();

	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(183, 89, 20));


	//아이템 출력
	//shop
	for (int i = 0; i < 4; i++)
	{
		if (i >= _itemMaxNum)	break;

		itemTemp = _shop->getItem(i + _itemBottomNum - 4);
		itemTemp.getItemImg()->frameRender(hdc, _itemShopRc[i].left + 8, _itemShopRc[i].top + 20, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);

		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));

		SetTextAlign(hdc, TA_LEFT);
		TextOut(hdc, _itemShopRc[i].left + 100, _itemShopRc[i].top + 22, itemTemp.getItemName().c_str(), strlen(itemTemp.getItemName().c_str()));

		SetTextAlign(hdc, TA_RIGHT);
		TextOut(hdc, _itemShopRc[i].left + 592, _itemShopRc[i].top + 28, to_string(itemTemp.getBuyValue()).c_str(), to_string(itemTemp.getBuyValue()).size());//760,450// 돈
	}

	//인벤토리
	SelectObject(hdc, hMediumFont);
	SetTextColor(hdc, RGB(255, 255, 225));

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			itemTemp = invenTemp.getItem(j, i);

			if (itemTemp.getItemCategory() == ITEMKIND_NULL || itemTemp.getItemImg() == nullptr)	continue;

			itemTemp.getItemImg()->frameRender(hdc, _itemInvenRc[i][j].left, _itemInvenRc[i][j].top, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);
			
			if (itemTemp.getItemNum() < 2)	continue;

			TextOut(hdc, _itemInvenRc[i][j].left + 46, _itemInvenRc[i][j].top +25, to_string(itemTemp.getItemNum()).c_str(), to_string(itemTemp.getItemNum()).size());
		}
	}

	//돈 출력
	//글씨체 선택
	SelectObject(hdc, hMediumFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	TextOut(hdc, 220, 532, to_string(money).c_str(), to_string(money).size());//760,450// 돈
	SetTextAlign(hdc, TA_LEFT);

	//아이템 정보 출력 필요시 출력
	if (_infoItemX != -1 || _infoShopItem != -1)
	{
		if (_infoShopItem != -1)
		{
			itemTemp = _shop->getItem(_infoShopItem);

			if (itemTemp.getItemCategory() != ITEMKIND_NULL || itemTemp.getItemImg() != nullptr)
			{
				itemTemp.informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y);
			}
		}
		else if (_infoItemX != -1)
		{
			itemTemp = invenTemp.getItem(_infoItemX, _infoItemY);

			if (itemTemp.getItemCategory() != ITEMKIND_NULL || itemTemp.getItemImg() != nullptr)
			{
				itemTemp.informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y + 48 - 431);
			}
		}
	}


}

void ui_shop::selectItem()
{
	item itemTemp;

	if (PtInRect(&_vUiImage[0].rc, m_ptMouse))
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_itemShopRc[i], m_ptMouse))
			{
				_infoItemX = -1;
				_infoItemY = -1;
				_infoShopItem = i + _itemBottomNum - 4;

				if (_infoShopItem >= _itemMaxNum)
				{
					_infoShopItem = -1;
					return;
				}

				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					_sound.effSoundPlay("메뉴선택");
					
					int money = PLAYERMANAGER->getPlayerMoney();
					//아이템 선택시 구매합니다
					itemTemp = _shop->getItem(_infoShopItem);
					if (itemTemp.getBuyValue() <= money)
					{
						if (!INVENTORYMANAGER->getIsInventoryFull())
						{
							INVENTORYMANAGER->addItem(itemTemp);
							PLAYERMANAGER->setPlayerMoney(money - itemTemp.getBuyValue());
						}
						else
						{
							if(INVENTORYMANAGER->findItem(itemTemp.getItemName()))
							{
								INVENTORYMANAGER->addItem(itemTemp);
								PLAYERMANAGER->setPlayerMoney(money - itemTemp.getBuyValue());
							}
							else
							{
								UIMANAGER->setFullInventory();
							}
						}
					}
					else if(itemTemp.getBuyValue() > money)
					{
						UIMANAGER->setNotMoney();
					}
				}
				return;
			}
		}

		//인벤토리 클릭시
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (PtInRect(&_itemInvenRc[i][j], m_ptMouse))
				{
					_infoItemX = j;
					_infoItemY = i;
					_infoShopItem = -1;

					if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
					{
						itemTemp = INVENTORYMANAGER->getItem(j, i);

						if (!(itemTemp.getItemCategory() == ITEMKIND_NULL || itemTemp.getItemCategory() == ITEMKIND_TOOL))
						{
							//아이템 선택시 판매합니다
							INVENTORYMANAGER->deleteItem(j, i);
							PLAYERMANAGER->setPlayerMoney(PLAYERMANAGER->getPlayerMoney() + itemTemp.getSellValue());
						}
					}

					return;
				}
			}
			if (i == 2)
			{
				_infoItemX = -1;
				_infoItemY = -1;
				_infoShopItem = -1;
			}
		}
	}
	else
	{
		_infoItemX = -1;
		_infoItemY = -1;
		_infoShopItem = -1;
	}
}

void ui_shop::wheelButtonMove()
{
	int wheelY = 280 / (_itemMaxNum - 4)*(_itemBottomNum - 4);

	if (_itemBottomNum == _itemMaxNum)
	{
		_vButton[2]._rc = RectMake(945, 400, 13, 22);
	}
	else if (_itemBottomNum == 4)
	{
		_vButton[2]._rc = RectMake(945, 120, 13, 22);
	}
	else
	{
		_vButton[2]._rc = RectMake(945, 120 + wheelY, 13, 22);
	}
}
