#pragma once
#include "scene.h"

enum NPC_KIND
{
	NPC_KIND_NULL=-1,
	NPC_KIND_ABIGAIL,
	NPC_KIND_EMILY,
	NPC_KIND_LEAH,
	NPC_KIND_MARNIE,
	NPC_KIND_PIERRE,
	NPC_KIND_END
};
enum NPC_DIRECTION
{
	NPC_DIRECTION_NULL = -1,
	NPC_DIRECTION_DOWN,
	NPC_DIRECTION_RIGHT,
	NPC_DIRECTION_UP,
	NPC_DIRECTION_LEFT,
	NPC_DIRECTION_END
};
enum NPC_ACTION
{
	NPC_ACTION_NULL,
	NPC_ACTION_IDLE,
	NPC_ACTION_MOVE,
	NPC_ACTION_END
};
class npc
{
protected:
	POINT _position;
	RECT _rc;
	RECT _collisionRc;
	string _name;
	NPC_KIND _kind;
	vector<string> _vConversation;
	NPC_DIRECTION _direction;
	NPC_ACTION _action;
	INGAMESCENE_NAME _locationScene;
	int _moveTime;
	int _idleTime;
	int _settingTime;
	int _speed;

	int _feeling;
	POINT _characterFrame;

	image *_characterImg;
	image *_portraitImg;
	image *_feelingImg;
	image *_shadow;

	animation *_aniCharacterImg;

	HBRUSH blue, oBrush;

public:
	npc();
	~npc();

	virtual HRESULT init();
	virtual void update();
	virtual void render(HDC hdc, int sceneName);
	virtual void release();

	void actionUpdate(NPC_ACTION action, NPC_DIRECTION direction);
	void move();

	int getPositionX() { return _position.x; };
	int getPosotionY() { return _position.y; };
	POINT getPosition() { return _position; };
	int getFrameX() { return _characterFrame.x; };
	int getFrameY() { return _characterFrame.y; };
	POINT getFrame() { return _characterFrame; };

	RECT getRc() { return _rc; }
	RECT getCollisionRc() { return _collisionRc; }
	string getName() { return _name; };
	string getConversation(int num) { return _vConversation[num]; };
	int getFeeling() { return _feeling; };
	NPC_DIRECTION getDirection() { return _direction; };
	NPC_ACTION getAction() { return _action; };
	INGAMESCENE_NAME getIngameScene() {return _locationScene;};
	

	image *getCharacterImage() { return _characterImg; };
	image *getCharacterPortrait() { return _portraitImg; };
	image *getCharacterFeelingImage() { return _feelingImg; };
	animation *getAnimation() { return _aniCharacterImg; };

	void setPositionX(int x) { _position.x = x, _rc = RectMakeCenter(_position.x, _position.y, 48, 96); };
	void setPositionY(int y) { _position.y = y, _rc = RectMakeCenter(_position.x, _position.y, 48, 96); };
	void setPosition(int x, int y) { _position.x = x, _position.y = y,_rc = RectMakeCenter(_position.x, _position.y, 48, 96); };

	int setFrameX(int frameX) { _characterFrame.x = frameX; };
	int setFrameY(int frameY) { _characterFrame.y = frameY; };
	POINT setFrame(POINT frame) { _characterFrame = frame; };

	void setRc(RECT rc) { _rc = rc; };
	void setCollisionRc(RECT rc) { _collisionRc = rc; };
	void setName(string name) { _name = name; };
	void addConversation(string conversation) { _vConversation.push_back(conversation); };
	void setFeeling(int feeling) { _feeling = feeling; };

	void setDirection(NPC_DIRECTION direction) { _direction = direction; };
	void setAction(NPC_ACTION action) { _action = action; };

	void setAnimaiton(const char* key);
};

