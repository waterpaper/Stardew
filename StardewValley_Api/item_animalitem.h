#pragma once
#include "item.h"

class item_animalitem:public item
{
public:
	item_animalitem();
	~item_animalitem();

	virtual void init(int itemSection);
	void setValue();
};

