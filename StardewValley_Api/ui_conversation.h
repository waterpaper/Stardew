#pragma once
#include "ui.h"
#include "npc.h"

class ui_conversation:public ui
{
private:
	int num;
	npc _nowNpc;
	RECT _conversationStringRect;


public:
	ui_conversation();
	~ui_conversation();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	virtual int getKindNum();
};

