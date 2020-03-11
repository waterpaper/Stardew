#include "stdafx.h"
#include "item_food.h"


item_food::item_food()
{
}


item_food::~item_food()
{
}

void item_food::init(int itemSection)
{
	_itemCategory = ITEMKIND_FOOD;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getFoodItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_food");

	_itemImgFrame = POINT{ itemSection, 0 };
	setValue();
}

void item_food::setValue()
{
	if (_itemDivision == FOODKIND_SUGAR)	_buyValue = 100, _sellValue = 50, _addHp=10, _addActingPower=25;
	if (_itemDivision == FOODKIND_FLOUR)	_buyValue = 100, _sellValue = 50, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == FOODKIND_RICE)	_buyValue = 200, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == FOODKIND_OIL)	_buyValue = 200, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == FOODKIND_VINEGAR)	_buyValue = 200, _sellValue = 100, _addHp = 13, _addActingPower = 5;

}
