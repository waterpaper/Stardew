#include "stdafx.h"
#include "inventoryManager.h"


inventoryManager::inventoryManager()
{
}


inventoryManager::~inventoryManager()
{
}

HRESULT inventoryManager::init()
{
	_inventory.init();
	return S_OK;
}

void inventoryManager::update()
{
}

void inventoryManager::render()
{
}

void inventoryManager::informationRenderItem(HDC hdc, int numX, int numY)
{
	_inventory.getItem(numX, numY).informationRender(hdc, m_ptMouse.x + 48, m_ptMouse.y + 48);
}

void inventoryManager::getItemRender(HDC hdc, item rItem)
{
	rItem.getItmeRender(hdc, 30, WINSIZEY - 100);
}

void inventoryManager::release()
{
	_inventory.release();
}

void inventoryManager::addItem(item items)
{
	int max = _inventory.getMaxSize();

	//같은 아이템이 존재하는지 확인

	for (int i = 0; i < max; i++)
	{
		if (items.getItemName().compare(_inventory.getItem(i%12, i / 12).getItemName()) == 0)
		{
			_inventory.addItemNum(i%12, i / 12);
			return;
		}
	}

	if (max <= _inventory.getNowSize())
	{
		//아이템이 꽉 차있으면 추가 x

		UIMANAGER->setFullInventory();
		return;
	}

	for (int i = 0; i < max; i++)
	{
		//아이템이 비어있는 곳에 추가
		if (_inventory.getItem(i % 12, i / 12).getItemCategory() == ITEMKIND_NULL)
		{
			_inventory.addItem(items, i%12, i / 12);

			break;
		}
		else
		{
			continue;
		}
	}
}

void inventoryManager::addItem(item items, int numX, int numY)
{
	_inventory.addItem(items, numX, numY);
}

void inventoryManager::eattingItem()
{
	int numX = UIMANAGER->getKindNum();
	item itemTemp = _inventory.getItem(numX, 0);

	playerState state = PLAYERMANAGER->getPlayerState();

	PLAYERMANAGER->setPlayerHp(state.getPlayerHp()+ itemTemp.getAddHp());
	PLAYERMANAGER->setPlayerActingPower(state.getPlayerActingPower() + itemTemp.getAddActingPower());

	deleteItem(numX,0);
}

void inventoryManager::deleteItem(int numX, int numY)
{
	if (_inventory.getItemNum(numX, numY) == 1)
	{
		_inventory.deleteItem(numX, numY);
	}
	else
	{
		_inventory.deleteItemNum(numX, numY);
	}
}

item inventoryManager::getItem(int numX, int numY)
{
	return _inventory.getItem(numX, numY);
}

bool inventoryManager::getIsInventoryFull()
{
	if (_inventory.getNowSize() >= _inventory.getMaxSize())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool inventoryManager::findItem(string name)
{
	int max = _inventory.getMaxSize();

	//같은 아이템이 존재하는지 확인

	for (int i = 0; i < max; i++)
	{
		if (name.compare(_inventory.getItem(i % 12, i / 12).getItemName()) == 0)
		{
			return true;
		}
	}
	return false;
}

void inventoryManager::gameStart()
{
	item *itemTemp;

	itemTemp = new item_tool_axe();
	itemTemp->init(AXEKIND_NORMAL);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);

	itemTemp = new item_tool_hoe();
	itemTemp->init(HOEKIND_NORMAL);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);

	itemTemp = new item_tool_pickaxe();
	itemTemp->init(PICKAXEKIND_NORMAL);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);

	itemTemp = new item_tool_scythe();
	itemTemp->init(SCYTHEKIND_NORMAL);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);

	itemTemp = new item_tool_wateringcan();
	itemTemp->init(WATERINGCANKIND_NORMAL);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);

	itemTemp = new item_seed();
	itemTemp->init(SEEDKIND_SPRING_CAULIFLOWER);
	addItem(*itemTemp);
	SAFE_DELETE(itemTemp);
}
