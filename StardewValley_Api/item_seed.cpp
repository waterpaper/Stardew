#include "stdafx.h"
#include "item_seed.h"


item_seed::item_seed()
{
}


item_seed::~item_seed()
{
}

void item_seed::init(int itemSection)
{
	_itemCategory = ITEMKIND_SEED;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getSeedItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_seed");
	
	if (itemSection < 16)
	{
		_itemImgFrame = POINT{ itemSection % 5,  itemSection / 5 };
	}
	else
	{
		_itemImgFrame = POINT{ itemSection % 16,  4 };
	}

	setValue();
}

void item_seed::setValue()
{
	if (_itemDivision == SEEDKIND_SPRING_PARSNIP)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_SPRING_GREENBEAN)	_buyValue = 60;
	if (_itemDivision == SEEDKIND_SPRING_CAULIFLOWER)	_buyValue = 80;
	if (_itemDivision == SEEDKIND_SPRING_POTATO)	_buyValue = 50;
	if (_itemDivision == SEEDKIND_SPRING_KALE)	_buyValue = 70;
	if (_itemDivision == SEEDKIND_SUMMER_RADISH)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_SUMMER_MELON)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_SUMMER_TOMATO)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_SUMMER_BLUEBERRY)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_SUMMER_HOTPEPPER)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_FALL_EGGPLANT)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_FALL_PUMPKIN)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_FALL_CRANBERRY)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_FALL_BOKCHOY)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_FALL_YAM)	_buyValue = 20;
	if (_itemDivision == SEEDKIND_TREE_CHERRY)	_buyValue = 3400;
	if (_itemDivision == SEEDKIND_TREE_APRICOT)	_buyValue = 4000;
	if (_itemDivision == SEEDKIND_TREE_ORANGE)	_buyValue = 4000;
	if (_itemDivision == SEEDKIND_TREE_PEACH)	_buyValue = 6000;
	if (_itemDivision == SEEDKIND_TREE_POMEGRANATE)	_buyValue = 6000;
	if (_itemDivision == SEEDKIND_TREE_APPLE)	_buyValue = 4000;
	if (_itemDivision == SEEDKIND_LAWN)	_buyValue = 100;

	_sellValue = _buyValue / 2;
}
