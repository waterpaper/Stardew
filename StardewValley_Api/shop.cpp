#include "stdafx.h"
#include "shop.h"


shop::shop()
{

}


shop::~shop()
{
	clearItem();
}

HRESULT shop::init()
{
	seasonItemAdd();

	return S_OK;
}

void shop::seasonItemAdd()
{
	clearItem();

	SEASON seasons = GAMETIMEMANAGER->getSeason();
	item *itemTemp;

	if (seasons == SEASON_SPRING)
	{
		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SPRING_PARSNIP);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SPRING_GREENBEAN);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SPRING_CAULIFLOWER);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SPRING_POTATO);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SPRING_KALE);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;
	}
	else if (seasons == SEASON_SUMMER)
	{
		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SUMMER_RADISH);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SUMMER_MELON);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SUMMER_TOMATO);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SUMMER_BLUEBERRY);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_SUMMER_HOTPEPPER);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;
	}
	else if (seasons == SEASON_FALL)
	{
		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_FALL_EGGPLANT);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_FALL_PUMPKIN);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_FALL_CRANBERRY);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_FALL_BOKCHOY);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;

		itemTemp = new item_seed;
		itemTemp->init(SEEDKIND_FALL_YAM);
		vShopItem.push_back(itemTemp);
		itemTemp = nullptr;
	}

	itemTemp = new item_food;
	itemTemp->init(FOODKIND_SUGAR);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_food;
	itemTemp->init(FOODKIND_FLOUR);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_food;
	itemTemp->init(FOODKIND_RICE);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_food;
	itemTemp->init(FOODKIND_OIL);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_food;
	itemTemp->init(FOODKIND_VINEGAR);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_CHERRY);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_APRICOT);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_ORANGE);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_PEACH);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_POMEGRANATE);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;

	itemTemp = new item_seed;
	itemTemp->init(SEEDKIND_TREE_APPLE);
	vShopItem.push_back(itemTemp);
	itemTemp = nullptr;
}

void shop::clearItem()
{
	if (vShopItem.size() != 0)
	{
		/*
		메모리릭을 해결하기 위해 요소마다 delete
		그 이후 capacity를 초기화한다
		*/
		for (int i = 0; i < vShopItem.size(); i++)
		{
			SAFE_DELETE(vShopItem[i]);
		}
		vShopItem.clear();
		vShopItem.shrink_to_fit();
	}
}
