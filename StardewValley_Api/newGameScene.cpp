#include "stdafx.h"
#include "newGameScene.h"


newGameScene::newGameScene()
{
}


newGameScene::~newGameScene()
{
	release();
}

HRESULT newGameScene::init()
{
	_newGame = new newGame();
	_newGame->init();

	_back = IMAGEMANAGER->findImage("타이틀배경");
	
	PLAYERMANAGER->setPlayerPosition(360.0,250.0);

	return S_OK;
}

void newGameScene::update()
{
	cloudAdd();
	cloudMove();
	_newGame->update();
}

void newGameScene::release()
{
	_newGame->release();
	SAFE_DELETE(_newGame);
	cloudVector.clear();
}

void newGameScene::render()
{
	_back->render(getMemDC(), 0, 0);

	for (int i = 0; i < cloudVector.size(); i++)
	{
		cloudVector[i]._img->render(getMemDC(), cloudVector[i]._rc.left, cloudVector[i]._rc.top);
	}

	_newGame->render(getMemDC());
	scene::render();
}

void newGameScene::cloudAdd()
{
	int rand = RND->getInt(1000);
	if (rand >= 980)
	{
		cloud cloudTemp;
		rand = RND->getInt(2);
		if (rand == 1)
		{
			cloudTemp._img = IMAGEMANAGER->findImage("타이틀구름1");
			cloudTemp._rc = RectMake(WINSIZEX, RND->getInt(WINSIZEY), 123 * 3, 54 * 3);
			cloudTemp._speed = RND->getInt(2);
		}
		else if (rand == 2)
		{
			cloudTemp._img = IMAGEMANAGER->findImage("타이틀구름2");
			cloudTemp._rc = RectMake(WINSIZEX, RND->getInt(WINSIZEY), 64 * 3, 36 * 3);
			cloudTemp._speed = RND->getInt(2);
		}

		cloudVector.push_back(cloudTemp);
	}
}

void newGameScene::cloudMove()
{
	for (int i = 0; i < cloudVector.size(); i++)
	{
		cloudVector[i]._rc.left -= cloudVector[i]._speed;
		cloudVector[i]._rc.right -= cloudVector[i]._speed;

		if (cloudVector[i]._rc.right <= 0)
		{
			cloudVector.erase(cloudVector.begin() + i);
			i--;
		}
	}
}
