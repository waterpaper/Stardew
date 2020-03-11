#pragma once
#include "item.h"

class item_material:public item
{
public:
	item_material();
	~item_material();

	virtual void init(int itemSection);
	void setValue();
};

