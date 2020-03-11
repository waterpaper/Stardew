#pragma once
#include "npc.h"

class npc_abigail:public npc
{
public:
	npc_abigail();
	~npc_abigail();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void addString();
};

