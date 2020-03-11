#pragma once
#include "item.h"

enum PICKAXEKIND
{
	PICKAXEKIND_NULL = -1,
	PICKAXEKIND_NORMAL = 10,
	PICKAXEKIND_BRONZE,
	PICKAXEKIND_SLIVER,
	PICKAXEKIND_GOLD,
	PICKAXEKIND_URANIUM,
	PICKAXEKIND_END = 99
};

class item_tool_pickaxe:public item
{
public:
	item_tool_pickaxe();
	~item_tool_pickaxe();

	virtual void init(int itemSection);
};

