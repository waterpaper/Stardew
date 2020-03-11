#pragma once
#include "npc.h"

class npc_marnie:public npc
{
public:
	npc_marnie();
	~npc_marnie();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void addString();
};

