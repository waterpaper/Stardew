#pragma once
#include "item.h"

typedef vector< vector<item *> > vInventory;
typedef vector< vector<item *> >::iterator viInventory;

class inventory
{
private:
	int _inventoryLevel;
	int _maxSize;
	int _inventoryNum;
	vInventory _vInventory;
	viInventory _viInventory;


public:
	inventory();
	~inventory();

	void init();
	void release();

	int getInventoryLevel() { return _inventoryLevel; };
	int getMaxSize() { return _maxSize; };
	int getNowSize() { return _inventoryNum; };

	void addItem(item items, int x, int y);
	void addItemNum(int x, int y) { _vInventory[y][x]->setItemNum(_vInventory[y][x]->getItemNum() + 1); };
	void deleteItemNum(int x, int y) { _vInventory[y][x]->setItemNum(_vInventory[y][x]->getItemNum() - 1); };

	void deleteItem(int x, int y);

	int getItemNum(int x, int y) { return _vInventory[y][x]->getItemNum(); };
	item getItem(int x, int y) { return *_vInventory[y][x]; }
	vInventory getInventory() { return _vInventory; };

	void addInventoryNum(int num) { _inventoryNum += num; };


	bool isInventoryFull() 
	{
		if (_vInventory.size() >= _maxSize)
		{
			return true;
		}
		else
			return false;
	}

	void setInventoryLevel(int level)
	{ 
		_inventoryLevel = level;
		if (level == 1)
		{
			_maxSize = 12;
		}
		else if (level == 2)
		{
			_maxSize = 24;
		}
		else if (level == 3)
		{
			_maxSize = 36;
		}
	};
};