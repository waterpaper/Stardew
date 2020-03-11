#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

void inventory::init()
{
	vector<item *> vTemp;
	item *iTemp;

	_inventoryLevel=1;
	_maxSize=12;
	_inventoryNum=0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			iTemp = new item();

			vTemp.push_back(iTemp);
			
			iTemp = nullptr;
		}
		_vInventory.push_back(vTemp);
		vTemp.clear();
	}
}

void inventory::release()
{
	if (_vInventory.size()!=0)
	{
		/*
		메모리릭을 해결하기 위해 요소마다 delete
		그 이후 capacity를 초기화한다
		*/
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				SAFE_DELETE(_vInventory[i][j]);
			}
		}
		_vInventory.clear();
		_vInventory.shrink_to_fit();
	}
}

void inventory::addItem(item items, int x, int y)
{
	_vInventory[y][x]->setItemCategory(items.getItemCategory());
	_vInventory[y][x]->setItemDivision(items.getItemDivision());
	_vInventory[y][x]->setItemSection(items.getItemSection());
	_vInventory[y][x]->setItemName(items.getItemName());
	_vInventory[y][x]->setItemExplanation(items.getItemExplanation());
	_vInventory[y][x]->setItemNum(items.getItemNum());
	_vInventory[y][x]->setItemImg(items.getItemImg());
	_vInventory[y][x]->setItemImageFrame(items.getItemImageFrame());
	_vInventory[y][x]->setAddHp(items.getAddHp());
	_vInventory[y][x]->setAddActingPower(items.getAddActingPower());
	_vInventory[y][x]->setSellValue(items.getSellValue());
	_vInventory[y][x]->setBuyValue(items.getBuyValue());

	_inventoryNum++;
}

void inventory::deleteItem(int x, int y)
{
	_vInventory[y][x]->setItemCategory(ITEMKIND_NULL);
	_vInventory[y][x]->setItemDivision(-1);
	_vInventory[y][x]->setItemSection(-1);
	_vInventory[y][x]->setItemName("");
	_vInventory[y][x]->setItemExplanation("");
	_vInventory[y][x]->setItemNum(-1);
	_vInventory[y][x]->setItemImg(nullptr);
	_vInventory[y][x]->setItemImageFrame(POINT{ 0,0});
	_vInventory[y][x]->setAddHp(0);
	_vInventory[y][x]->setAddActingPower(0);
	_vInventory[y][x]->setSellValue(0);
	_vInventory[y][x]->setBuyValue(0);

	_inventoryNum--;
}
