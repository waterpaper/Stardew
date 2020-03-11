#include "stdafx.h"
#include "item_rock.h"


item_rock::item_rock()
{
}


item_rock::~item_rock()
{
}

void item_rock::init(int itemSection)
{
	_itemCategory = ITEMKIND_ROCK;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getRockItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_rock");

	_itemImgFrame = POINT{ itemSection, 0 };
	setValue();
}

void item_rock::setValue()
{
	if (_itemDivision == ROCKKIND::ROCKKIND_STONE)	_buyValue = 20, _sellValue = 10;
	if (_itemDivision == ROCKKIND::ROCKKIND_XHAMSTER)	_buyValue = 60, _sellValue = 30;
}
