#include "stdafx.h"
#include "item_tool_pickaxe.h"


item_tool_pickaxe::item_tool_pickaxe()
{
}


item_tool_pickaxe::~item_tool_pickaxe()
{
}

void item_tool_pickaxe::init(int itemSection)
{
	_itemCategory = ITEMKIND_TOOL;
	_itemDivision = TOOLKIND_PICKAXE;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getToolItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_tool");
	_itemImgFrame = POINT{ itemSection % 5, 2 };
}

