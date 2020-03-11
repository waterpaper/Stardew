#pragma once
#include "npc.h"

class npc_leah:public npc
{
public:
	npc_leah();
	~npc_leah();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void addString();
};

