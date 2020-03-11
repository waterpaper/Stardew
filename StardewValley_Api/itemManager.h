#pragma once
#include "singletonBase.h"
#include "item.h"
#include "all_Item.h"

struct dropItem
{
	item *item;
	POINT position;
	RECT rc;
	int setDistance;
	int moveDistance;
	int speed;
	bool isUp;
	bool isDown;
	bool isAvailableGet;
};

struct itemString
{
	string itemName;
	string itemExplanation;
};

class itemManager:public singletonBase<itemManager>
{
private:
	vector<dropItem> _vDropItem;
	vector<itemString> _vEquipmentItemString;
	vector<itemString> _vToolItemString;
	vector<itemString> _vCropsItemString;
	vector<itemString> _vSeedItemString;
	vector<itemString> _vFoodItemString;
	vector<itemString> _vAnimalItemString;
	vector<itemString> _vCraftalbleItemString;
	vector<itemString> _vRockItemString;
	vector<itemString> _vMaterialItemString;

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();

	void deleteItem(int i);

	void materialWoodDrop(int x, int y, bool isTree);
	void materialDrop(int x, int y);
	void rockDrop(int x, int y);

	void addDropItem(dropItem item) { _vDropItem.push_back(item); };
	void dropItemClear();

	void collisionItem(RECT rc);

	void itemStringClear();
	void readString();

	itemString getEquipmentItemString(int num) { return _vEquipmentItemString[num]; };
	itemString getToolItemString(int num) { return _vToolItemString[num]; };
	itemString getCropsItemString(int num) { return _vCropsItemString[num]; };
	itemString getSeedItemString(int num) { return _vSeedItemString[num]; };
	itemString getFoodItemString(int num) { return _vFoodItemString[num]; };
	itemString getAnimalItemString(int num) { return _vAnimalItemString[num]; };
	itemString getCraftableItemString(int num) { return _vCraftalbleItemString[num]; };
	itemString getRockItemString(int num) { return _vRockItemString[num]; };
	itemString getMaterialItemString(int num) { return _vMaterialItemString[num]; };
};

