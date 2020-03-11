#pragma once
#include "item.h"

class item_food:public item
{
public:
	item_food();
	~item_food();

	virtual void init(int itemSection);
	void setValue();
};

