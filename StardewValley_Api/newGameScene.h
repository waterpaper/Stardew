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

	//�����߰�
	void cloudAdd();

	//���� ������
	void cloudMove();
};

