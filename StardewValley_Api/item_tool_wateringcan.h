#pragma once
#include "item.h"

enum WATERINGCANKIND
{
	WATERINGCANKIND_NULL = -1,
	WATERINGCANKIND_NORMAL = 15,
	WATERINGCANKIND_BRONZE,
	WATERINGCANKIND_SLIVER,
	WATERINGCANKIND_GOLD,
	WATERINGCANKIND_URANIUM,
	WATERINGCANKIND_END = 99
};

class item_tool_wateringcan:public item
{
public:
	item_tool_wateringcan();
	~item_tool_wateringcan();

	virtual void init(int itemSection);
};

