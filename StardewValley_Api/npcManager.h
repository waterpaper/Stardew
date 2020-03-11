#pragma once
#include "singletonBase.h"
#include "npc.h"
#include "allNpc.h"

class npcManager :public singletonBase<npcManager>
{
private:
	vector<npc *> vNpc;
	NPC_KIND nowNpcKind;
	bool isPresent;

public:
	npcManager();
	~npcManager();

	HRESULT init();
	void update();
	void render(HDC hdc);
	void reRender(HDC hdc, RECT rect);
	void release();

	void npcClear();

	void aniAdd();

	vector<npc *> getNpcVector() { return vNpc; };
	npc getNowNpc() { return *vNpc[(int)nowNpcKind]; };
	bool getIsPresent() { return isPresent; };
	void setIsPresent(bool isBool) { isPresent = isBool; };

	void setPositionX(int num, int x) { vNpc[num]->setPositionX(x); };
	void setPositionY(int num, int y) { vNpc[num]->setPositionX(y); };
	void setPosition(int num, int x, int y) { vNpc[num]->setPosition(x, y); };

	int setFrameX(int num, int frameX) { vNpc[num]->setFrameX(frameX); };
	int setFrameY(int num, int frameY) { vNpc[num]->setFrameY(frameY); };
	POINT setFrame(int num, POINT frame) { vNpc[num]->setFrame(frame); };

	void setName(int num, string name) { vNpc[num]->setName(name); };
	void addConversation(int num, string conversation) { vNpc[num]->addConversation(conversation); };
	void setFeeling(int num, int feeling) { vNpc[num]->setFeeling(feeling); };

	void setDirection(int num, NPC_DIRECTION direction) { vNpc[num]->setDirection(direction); };
	void setAction(int num, NPC_ACTION action) { vNpc[num]->setAction(action); };

	void playerConversation(POINT point);
	bool playerPresent(POINT point);

	bool getRectCollision(RECT rc, INGAMESCENE_NAME ingameName);
	bool getvNpcCollision(RECT rc);
	bool playerCollision(RECT rc);
	bool objectCollision(RECT rc);
};

