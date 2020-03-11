#pragma once
#include "item.h"

class shop
{
private:
	vector<item *> vShopItem;

public:
	shop();
	~shop();

	HRESULT init();
	void seasonItemAdd();

	void deleteItem(int num) { vShopItem.erase(vShopItem.begin() + num); };
	void clearItem();

	int getItemMaxNum() { return vShopItem.size(); };
	item getItem(int num) { return *vShopItem[num]; };
	vector<item *> getShopItemList() { return vShopItem; };



};

