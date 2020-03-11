#include "stdafx.h"
#include "item_tool_hoe.h"


item_tool_hoe::item_tool_hoe()
{
	_itemCategory = (ITEMKIND)0;
	_itemDivision = 0;
	_itemSection = 0;

	_itemName = "";
	_itemExplanation = "";
	_itemNum = 0;
	_itemImg = nullptr;

	_sellValue = 0;
	_buyValue = 0;
}


item_tool_hoe::~item_tool_hoe()
{
}

void item_tool_hoe::init(int itemSection)
{
	_itemCategory = ITEMKIND_TOOL;
	_itemDivision = TOOLKIND_HOE;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getToolItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_tool");
	_itemImgFrame = POINT{ itemSection%5, 1 };
}

