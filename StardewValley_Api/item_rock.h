#pragma once
#include "item.h"

class item_rock:public item
{
public:
	item_rock();
	~item_rock();

	virtual void init(int itemSection);
	void setValue();
};

