#include "stdafx.h"
#include "item_tool_wateringcan.h"


item_tool_wateringcan::item_tool_wateringcan()
{
}


item_tool_wateringcan::~item_tool_wateringcan()
{
}

void item_tool_wateringcan::init(int itemSection)
{
	_itemCategory = ITEMKIND_TOOL;
	_itemDivision = TOOLKIND_WATERINGCAN;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getToolItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_tool");
	_itemImgFrame = POINT{ itemSection % 5, 3 };
}

