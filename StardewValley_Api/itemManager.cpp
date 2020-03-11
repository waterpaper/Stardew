#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	readString();
	return S_OK;
}

void itemManager::update()
{
	for (int i = 0; i < _vDropItem.size(); i++)
	{
		if (_vDropItem[i].isAvailableGet)	continue;

		if (_vDropItem[i].isUp)
		{
			_vDropItem[i].position.y -= _vDropItem[i].speed;
			_vDropItem[i].moveDistance -= _vDropItem[i].speed;
			_vDropItem[i].setDistance += _vDropItem[i].speed;
			_vDropItem[i].rc = RectMakeCenter(_vDropItem[i].position.x, _vDropItem[i].position.y, 48, 48);

			if (_vDropItem[i].moveDistance < 0)
			{
				_vDropItem[i].isUp = false;
				_vDropItem[i].isDown = true;
			}
		}
		else if (_vDropItem[i].isDown)
		{
			_vDropItem[i].position.y += _vDropItem[i].speed;
			_vDropItem[i].setDistance -= _vDropItem[i].speed;
			_vDropItem[i].rc = RectMakeCenter(_vDropItem[i].position.x, _vDropItem[i].position.y, 48, 48);

			if (_vDropItem[i].setDistance < 0)
			{
				_vDropItem[i].isDown = false;
				_vDropItem[i].isAvailableGet = true;
			}
		}
	}
}

void itemManager::render(HDC hdc)
{
	POINT frame;

	for (int i = 0; i < _vDropItem.size(); i++)
	{
		frame = _vDropItem[i].item->getItemImageFrame();
		_vDropItem[i].item->getItemImg()->frameRender(hdc, _vDropItem[i].rc.left, _vDropItem[i].rc.top, frame.x, frame.y);
	}
}

void itemManager::release()
{
	vector<dropItem> temp;

	for (int i = 0; i < _vDropItem.size(); i++)
	{
		SAFE_DELETE(_vDropItem[i].item);
	}
	_vDropItem.swap(temp);
	temp.clear();
}

void itemManager::deleteItem(int i)
{
	SAFE_DELETE(_vDropItem[i].item);
	_vDropItem.erase(_vDropItem.begin()+i);
}

void itemManager::materialWoodDrop(int x, int y, bool isTree)
{
	dropItem dropItems;
	item *items;
	int num = RND->getInt(9);

	items = new item_material();
	items->init(MATERIALKIND::MATERIALKIND_WOOD);

	dropItems.position.x = x;
	dropItems.position.y = y;
	dropItems.rc = RectMakeCenter(x, y, 48, 48);
	dropItems.isUp = true;
	dropItems.isDown = false;
	dropItems.isAvailableGet = false;
	dropItems.moveDistance = RND->getFromIntTo(24, 48);
	dropItems.speed = RND->getFromIntTo(1, 4);
	dropItems.setDistance = 0;
	dropItems.item = items;
	addDropItem(dropItems);
	items = nullptr;

	if (isTree)
	{
		if (num > 8)
		{
			items = new item_material();
			items->init(MATERIALKIND::MATERIALKIND_BIGWOOD);
			dropItems.position.y = y;
			num = RND->getInt(64);
			dropItems.position.x = (36 - num) + x;
			dropItems.rc = RectMakeCenter(x, y, 48, 48);
			dropItems.moveDistance = RND->getFromIntTo(24, 48);
			dropItems.speed = RND->getFromIntTo(1, 4);
			dropItems.item = items;
			addDropItem(dropItems);
			items = nullptr;
		}
	}
}

void itemManager::materialDrop(int x, int y)
{
	dropItem dropItems;
	item *items;

	items = new item_material();
	items->init(MATERIALKIND::MATERIALKIND_FIBER);

	dropItems.position.x = x;
	dropItems.position.y = y;
	dropItems.rc = RectMakeCenter(x, y, 48, 48);
	dropItems.isUp = true;
	dropItems.isDown = false;
	dropItems.isAvailableGet = false;
	dropItems.moveDistance = RND->getFromIntTo(24, 48);
	dropItems.speed = RND->getFromIntTo(1, 4);
	dropItems.setDistance = 0;
	dropItems.item = items;
	addDropItem(dropItems);
	items = nullptr;
}

void itemManager::rockDrop(int x, int y)
{
	dropItem dropItems;
	item *items;
	int num = RND->getInt(9);

	items = new item_rock();
	items->init(ROCKKIND::ROCKKIND_STONE);

	dropItems.position.x = x;
	dropItems.position.y = y;
	dropItems.rc = RectMakeCenter(x, y, 48, 48);
	dropItems.isUp = true;
	dropItems.isDown = false;
	dropItems.isAvailableGet = false;
	dropItems.moveDistance = RND->getFromIntTo(24, 48);
	dropItems.speed = RND->getFromIntTo(1, 4);
	dropItems.setDistance = 0;
	dropItems.item = items;
	addDropItem(dropItems);
	items = nullptr;

	if (num > 6)
	{
		items = new item_rock();
		items->init(ROCKKIND::ROCKKIND_XHAMSTER);
		dropItems.position.y = y;
		num = RND->getInt(64);
		dropItems.position.x = (36 - num) + x;
		dropItems.rc = RectMakeCenter(x, y, 48, 48);
		dropItems.moveDistance = RND->getFromIntTo(24, 48);
		dropItems.speed = RND->getFromIntTo(1, 4);
		dropItems.item = items;
		addDropItem(dropItems);
		items = nullptr;
	}
}

void itemManager::dropItemClear()
{
	vector<dropItem> temp;
	_vDropItem.swap(temp);
	temp.clear();
}

void itemManager::collisionItem(RECT rc)
{
	if (_vDropItem.size() == 0)	return;

	RECT rcTemp;
	POINT temp = CAMERAMANAGER->getCameraPos();

	for (int i = 0; i < _vDropItem.size(); i++)
	{
		if (!_vDropItem[i].isAvailableGet)	continue;

		if (_vDropItem[i].rc.right< temp.x || _vDropItem[i].rc.left>temp.x + WINSIZEX ||
			_vDropItem[i].rc.top < temp.y || _vDropItem[i].rc.bottom > temp.y + WINSIZEY) continue;
		
		if (IntersectRect(&rcTemp, &rc, &_vDropItem[i].rc))
		{
			if (INVENTORYMANAGER->getIsInventoryFull())
			{
				if (INVENTORYMANAGER->findItem(_vDropItem[i].item->getItemName()))
				{
					UIMANAGER->addAddItemUi(*_vDropItem[i].item);
					INVENTORYMANAGER->addItem(*_vDropItem[i].item);
					deleteItem(i);
				}
				else
				{
					UIMANAGER->setFullInventory();
				}
			}
			else
			{
				UIMANAGER->addAddItemUi(*_vDropItem[i].item);
				INVENTORYMANAGER->addItem(*_vDropItem[i].item);
				deleteItem(i);
			}

			break;
		}
		
	}
}

void itemManager::itemStringClear()
{
	vector<itemString> temp;

	_vEquipmentItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vToolItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vCropsItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vSeedItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vFoodItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vCraftalbleItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
	_vRockItemString.swap(temp);
	temp.clear();
	temp.shrink_to_fit();
}

void itemManager::readString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	itemString stringTmep;

	sprintf(dirTemp, "string/tool.txt");
	ifstream inFile(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vToolItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/seed.txt");

	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vSeedItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/food.txt");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vFoodItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/crops.txt");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vCropsItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/animalitem.txt");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vAnimalItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/material.txt");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vMaterialItemString.push_back(stringTmep);
	}

	inFile.close();

	sprintf(dirTemp, "string/rock.txt");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemName = strTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep.itemExplanation = strTemp;

		_vRockItemString.push_back(stringTmep);
	}

	inFile.close();
}
