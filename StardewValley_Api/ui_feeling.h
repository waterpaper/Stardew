#pragma once
#include "ui.h"
#include "npc.h"

struct feelingList
{
	int npcVectorNum;
	int feelingNum;
};

class ui_feeling:public ui
{
private:
	vector<npc *> _vNpc;
	vector<feelingList> _vFeelingList;
	vector<feelingList>::iterator _viFeelingList;

	int _itemNum;

public:
	ui_feeling();
	~ui_feeling();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
};

