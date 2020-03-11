#pragma once
#include "item.h"

class item_seed:public item
{
private:

public:
	item_seed();
	~item_seed();

	virtual void init(int itemSection);
	void setValue();
};

