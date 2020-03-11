#include "stdafx.h"
#include "item_tool_scythe.h"


item_tool_scythe::item_tool_scythe()
{
}


item_tool_scythe::~item_tool_scythe()
{
}

void item_tool_scythe::init(int itemSection)
{
	_itemCategory = ITEMKIND_TOOL;
	_itemDivision = TOOLKIND_SCYTHE;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getToolItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_tool");
	_itemImgFrame = POINT{ itemSection % 5, 4 };
}
