#pragma once
#include "npc.h"

class npc_emily:public npc
{
public:
	npc_emily();
	~npc_emily();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void addString();
};

