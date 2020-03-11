#pragma once
#include "npc.h"
class npc_pierre:public npc
{
public:
	npc_pierre();
	~npc_pierre();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void addString();
};

