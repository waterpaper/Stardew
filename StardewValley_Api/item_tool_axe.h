#pragma once
#include "item.h"

enum AXEKIND
{
	AXEKIND_NULL = -1,
	AXEKIND_NORMAL,
	AXEKIND_BRONZE,
	AXEKIND_SLIVER,
	AXEKIND_GOLD,
	AXEKIND_URANIUM,
	AXEKIND_END=99
};

class item_tool_axe:public item
{
public:
	item_tool_axe();
	~item_tool_axe();

	virtual void init(int itemSection);

};

