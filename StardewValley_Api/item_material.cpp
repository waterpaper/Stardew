#include "stdafx.h"
#include "item_material.h"


item_material::item_material()
{
}


item_material::~item_material()
{
}

void item_material::init(int itemSection)
{
	_itemCategory = ITEMKIND_MATERIAL;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getMaterialItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_material");

	_itemImgFrame = POINT{ itemSection, 0 };
	setValue();
}

void item_material::setValue()
{
	if (_itemDivision == MATERIALKIND::MATERIALKIND_WOOD)	_buyValue = 40, _sellValue = 20;
	if (_itemDivision == MATERIALKIND::MATERIALKIND_BIGWOOD)	_buyValue = 80, _sellValue = 40;
	if (_itemDivision == MATERIALKIND::MATERIALKIND_FIBER)	_buyValue = 40, _sellValue = 20;
}
