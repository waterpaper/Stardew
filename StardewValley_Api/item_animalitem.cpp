#include "stdafx.h"
#include "item_animalitem.h"


item_animalitem::item_animalitem()
{
}


item_animalitem::~item_animalitem()
{
}

void item_animalitem::init(int itemSection)
{
	_itemCategory = ITEMKIND_ANIMALITEM;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getAnimalItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_animalitem");

	_itemImgFrame = POINT{ itemSection, 0 };
	setValue();
}

void item_animalitem::setValue()
{
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_EGG)	_buyValue = 80, _sellValue = 40, _addHp = 13, _addActingPower = 25;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_MILK)	_buyValue = 200, _sellValue = 100, _addHp = 20, _addActingPower = 45;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_GOATMILK)	_buyValue = 360, _sellValue = 180, _addHp = 33, _addActingPower = 75;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_DUCKEGG)	_buyValue = 150, _sellValue = 75, _addHp = 25, _addActingPower = 50;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_WOOL)	_buyValue = 540, _sellValue = 270, _addHp = 0, _addActingPower = 0;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_TRUFFLE)	_buyValue = 1000, _sellValue = 500, _addHp = 40, _addActingPower = 90;
	if (_itemDivision == ANIMALITEMKIND::ANIMALITEMKIND_RABBITFOOT)	_buyValue = 900, _sellValue = 450, _addHp = 0, _addActingPower = 0;
}
