#pragma once
#include "gameNode.h"
#include "sceneAll.h"

static image *_mouseIcon;

class mainGame : public gameNode
{
private:
	bool _isKeyExplanation;
	image *_keyExplanation;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

