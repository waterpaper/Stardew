#pragma once
#include "singletonBase.h"
#include "inventory.h"

class inventoryManager:public singletonBase<inventoryManager>
{
private:
	inventory _inventory;
	
public:
	inventoryManager();
	~inventoryManager();

	HRESULT init();
	void update();
	void render();
	void informationRenderItem(HDC hdc, int numX, int numY);
	void getItemRender(HDC hdc, item rItem);
	void release();

	void addItem(item items);
	void addItem(item items, int numX, int numY);
	void eattingItem();
	void deleteItem(int numX, int numY);
	void clearInventory() { _inventory.release();  _inventory.init(); };

	void inventoryUpgrade() { _inventory.setInventoryLevel(_inventory.getInventoryLevel() + 1); };
	item getItem(int numX, int numY);
	inventory getInventory() { return _inventory; };
	int getInventoryMaxSize() { return _inventory.getMaxSize(); };
	bool getIsInventoryFull();
	bool findItem(string name);

	void addInventoryNum(int num) { _inventory.addInventoryNum(num); };
	
	void gameStart();
};

