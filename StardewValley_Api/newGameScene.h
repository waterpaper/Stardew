#pragma once
#include "scene.h"
#include "newGame.h"

class newGameScene : public scene
{
private:
	newGame *_newGame;
	image *_back;

	vector<cloud> cloudVector;


public:
	newGameScene();
	~newGameScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	//구름추가
	void cloudAdd();

	//구름 움직임
	void cloudMove();
};

