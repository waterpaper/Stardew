#include "stdafx.h"
#include "item_tool_axe.h"


item_tool_axe::item_tool_axe()
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

item_tool_axe::~item_tool_axe()
{
}

void item_tool_axe::init(int itemSection)
{
	_itemCategory = ITEMKIND_TOOL;
	_itemDivision = TOOLKIND_AXE;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getToolItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_tool");
	_itemImgFrame = POINT{ itemSection % 5, 0 };

}

