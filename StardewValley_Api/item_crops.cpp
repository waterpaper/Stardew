#include "stdafx.h"
#include "item_crops.h"


item_crops::item_crops()
{
}


item_crops::~item_crops()
{
}

void item_crops::init(int itemSection)
{
	_itemCategory = ITEMKIND_CROPS;
	_itemDivision = itemSection;
	_itemSection = itemSection;

	itemString temp = ITEMMANAGER->getCropsItemString(_itemSection);

	_itemName = temp.itemName;
	_itemExplanation = temp.itemExplanation;
	_itemNum = 1;
	_itemImg = IMAGEMANAGER->findImage("æ∆¿Ã≈€_crops");

	_itemImgFrame = POINT{ itemSection%5, itemSection/5 };
	setValue();
}

void item_crops::setValue()
{
	if (_itemDivision == CROPSKIND::CROPSKIND_SPRING_PARSNIP)	_buyValue = 70, _sellValue = 35, _addHp = 11, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_SPRING_GREENBEAN)	_buyValue = 80, _sellValue = 40, _addHp = 11, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_SPRING_CAULIFLOWER)	_buyValue = 350, _sellValue = 175, _addHp = 33, _addActingPower = 75;
	if (_itemDivision == CROPSKIND::CROPSKIND_SPRING_POTATO)	_buyValue = 160, _sellValue = 80, _addHp = 11, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_SPRING_KALE)	_buyValue = 220, _sellValue = 110, _addHp = 22, _addActingPower = 50;
	if (_itemDivision == CROPSKIND::CROPSKIND_SUMMER_RADISH)	_buyValue = 180, _sellValue = 90, _addHp = 20, _addActingPower = 45;
	if (_itemDivision == CROPSKIND::CROPSKIND_SUMMER_MELON)	_buyValue = 500, _sellValue = 250, _addHp = 50, _addActingPower =113;
	if (_itemDivision == CROPSKIND::CROPSKIND_SUMMER_TOMATO)	_buyValue = 120, _sellValue = 60, _addHp = 9, _addActingPower = 20;
	if (_itemDivision == CROPSKIND::CROPSKIND_SUMMER_BLUEBERRY)	_buyValue = 100, _sellValue = 50, _addHp = 11, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_SUMMER_HOTPEPPER)	_buyValue = 80, _sellValue = 40, _addHp = 5, _addActingPower = 13;
	if (_itemDivision == CROPSKIND::CROPSKIND_FALL_EGGPLANT)	_buyValue = 120, _sellValue = 60, _addHp = 9, _addActingPower = 20;
	if (_itemDivision == CROPSKIND::CROPSKIND_FALL_PUMPKIN)	_buyValue = 640, _sellValue = 320, _addHp = 0, _addActingPower = 0;
	if (_itemDivision == CROPSKIND::CROPSKIND_FALL_CRANBERRY)	_buyValue = 150, _sellValue = 75, _addHp = 17, _addActingPower = 38;
	if (_itemDivision == CROPSKIND::CROPSKIND_FALL_BOKCHOY)	_buyValue = 160, _sellValue = 80, _addHp = 11, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_FALL_YAM)	_buyValue = 320, _sellValue = 160, _addHp = 20, _addActingPower = 45;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_CHERRY)	_buyValue = 100, _sellValue = 50, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_APRICOT)	_buyValue = 160, _sellValue = 80, _addHp = 10, _addActingPower = 25;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_ORANGE)	_buyValue = 280, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_PEACH)	_buyValue = 200, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_POMEGRANATE)	_buyValue = 200, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == CROPSKIND::CROPSKIND_TREE_APPLE)	_buyValue = 280, _sellValue = 100, _addHp = 13, _addActingPower = 5;
	if (_itemDivision == CROPSKIND::CROPSKIND_LAWN)	_buyValue = 80, _sellValue = 20, _addHp = 0, _addActingPower = 0;
}
