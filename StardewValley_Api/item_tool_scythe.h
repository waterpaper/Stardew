#pragma once
#include "item.h"

enum SCYTHEKIND
{
	SCYTHEKIND_NULL = -1,
	SCYTHEKIND_NORMAL=20,
	SCYTHEKIND_END = 99
};

class item_tool_scythe:public item
{
public:
	item_tool_scythe();
	~item_tool_scythe();

	virtual void init(int itemSection);
};

