#pragma once
#include "item.h"

class item_crops:public item
{
public:
	item_crops();
	~item_crops();

	virtual void init(int itemSection);
	void setValue();
};

