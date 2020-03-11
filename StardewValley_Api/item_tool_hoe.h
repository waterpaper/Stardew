#pragma once
#include "item.h"

enum HOEKIND
{
	HOEKIND_NULL = -1,
	HOEKIND_NORMAL = 5,
	HOEKIND_BRONZE,
	HOEKIND_SLIVER,
	HOEKIND_GOLD,
	HOEKIND_URANIUM,
	HOEKIND_END = 99
};

class item_tool_hoe:public item
{
public:
	item_tool_hoe();
	~item_tool_hoe();

	virtual void init(int itemSection);
};

