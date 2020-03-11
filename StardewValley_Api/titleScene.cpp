#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	_sceneName = SCENE_NAME_START_SCENE;

	scene::init();

	_sceneRenderCameraX = 0, _sceneRenderCameraY = WINSIZEY;

	_back = IMAGEMANAGER->findImage("타이틀배경");
	_img1 = IMAGEMANAGER->findImage("타이틀이미지1"), _img2 = IMAGEMANAGER->findImage("타이틀이미지2"), _img3 = IMAGEMANAGER->findImage("타이틀이미지3");
	_bird = IMAGEMANAGER->findImage("타이틀새");
	_title = IMAGEMANAGER->findImage("타이틀");

	_backRc = RectMake(0, -WINSIZEY, WINSIZEX, WINSIZEY);
	_img1Rc = RectMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY / 2);
	_img2Rc = RectMake(0, WINSIZEY / 2 - 100, WINSIZEX, WINSIZEY / 2);
	_img3Rc = RectMake(0, WINSIZEY / 2, WINSIZEX, WINSIZEY / 2);
	_birdRc = RectMake(WINSIZEX/2, WINSIZEY / 2 + 100, 104*3, 18*3);
	_titleRc = RectMake(WINSIZEX/2-398, -WINSIZEY+100, 398*2, 187*2);

	ANIMATIONMANAGER->addDefAnimation("birdAni", "타이틀새", 5, false, true);
	_birdAni = ANIMATIONMANAGER->findAnimation("birdAni");
	_birdAni->start();

	_startCount = GetTickCount();
	_buttonNum = 0;
	_isMove = true;
	_isSelectMenuCreate = false;

	_sound.soundOff();
	_sound.soundPlay("시작화면");

	return S_OK;
}

void titleScene::update()
{
	scene::update();

	cloudAdd();
	enteredKey();
	cloudMove();
	imageMove();
	crateSelectMenuButton();
}

void titleScene::release()
{
	scene::release();
}

void titleScene::render()
{
	_back->render(getMemDC(), _backRc.left, _backRc.top);

	for (int i = 0; i < cloudVector.size(); i++)
	{
		cloudVector[i]._img->render(getMemDC(), cloudVector[i]._rc.left, cloudVector[i]._rc.top);
	}

	if (_isMove)
	{
		_img2->render(getMemDC(), _img2Rc.left, _img2Rc.top);
		_img3->render(getMemDC(), _img3Rc.left, _img3Rc.top);
		_img1->render(getMemDC(), _img1Rc.left, _img1Rc.top);
		_bird->aniRender(getMemDC(), _birdRc.left, _birdRc.top, _birdAni);
	}

	_title->render(getMemDC(), _titleRc.left, _titleRc.top);

	scene::render();
}

void titleScene::cloudAdd()
{
	int rand = RND->getInt(1000);
	if (rand >= 980)
	{
		cloud cloudTemp;
		rand = RND->getInt(2);
		if (rand == 1)
		{
			cloudTemp._img = IMAGEMANAGER->findImage("타이틀구름1");
			cloudTemp._rc = RectMake(WINSIZEX,RND->getInt(WINSIZEY), 123 * 3, 54 * 3);
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

void titleScene::cloudMove()
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

	if (_isMove)
	{
		for (int i = 0; i < cloudVector.size(); i++)
		{
			cloudVector[i]._rc.top += 1;
			cloudVector[i]._rc.bottom += 1;
		}
	}
}

void titleScene::selectButton()
{
	for (int i = 0; i < button.size(); i++)
	{
		if (PtInRect(&button[i]._rc, m_ptMouse))
		{
			if (button[i]._kind == TITLESCENE_BUTTON_STARTGAMESCENE)
			{
				SCENEMANAGER->changeScene("newGameScene");
			}
			else if (button[i]._kind == TITLESCENE_BUTTON_LOADGAMESCENE)
			{
				SCENEMANAGER->changeScene("loadGameScene");
			}
			else if (button[i]._kind == TITLESCENE_BUTTON_MAPTOOLSCENE)
			{
				SCENEMANAGER->changeScene("maptoolScene");
			}
			else if (button[i]._kind == TITLESCENE_BUTTON_QUIT)
			{
				DestroyWindow(m_hWnd);
			}

			_sound.effSoundPlay("메뉴선택");
		}
	}
}

void titleScene::enteredKey()
{
	//키 입력
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isMove = false;
		_isSelectMenuCreate = true;

		_startCount = GetTickCount();

		_titleRc.top = 100;
		_backRc.top = 0;
		_img1Rc.top += WINSIZEY;
		_img2Rc.top += WINSIZEY;
		_img3Rc.top += WINSIZEY;
		_birdRc.top += WINSIZEY;
	}

	//마우스 입력
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		selectButton();
	}
}

void titleScene::imageMove()
{
	if (_isMove)
	{
		_birdRc.left -= 1;

		if (GetTickCount() - _startCount > 3000)
		{
			_titleRc.top += 1;
			_backRc.top += 1;
			_img1Rc.top += 3;
			_img2Rc.top += 1;
			_img3Rc.top += 2;
			_birdRc.top += 2;

			if (_backRc.top >= -2)
			{
				_isMove = false;
				_isSelectMenuCreate = true;
				_startCount = GetTickCount();
			}
		}

		if (_birdRc.top >= WINSIZEY)
		{
			_birdAni->stop();
		}
	}
}

void titleScene::crateSelectMenuButton()
{
	if (_isSelectMenuCreate)
	{
		if (GetTickCount() - _startCount > 700)
		{
			if (_buttonNum == 0)
			{
				imageButtonAdd("타이틀시작", "", 150, WINSIZEY - 250, 74 * 2, 58 * 2, TITLESCENE_BUTTON_STARTGAMESCENE, true);
			}
			else if (_buttonNum == 1)
			{
				imageButtonAdd("타이틀로드", "", 350, WINSIZEY - 250, 74 * 2, 58 * 2, TITLESCENE_BUTTON_LOADGAMESCENE, true);
			}
			else if (_buttonNum == 2)
			{
				imageButtonAdd("타이틀맵툴", "", 550, WINSIZEY - 250, 74 * 2, 58 * 2, TITLESCENE_BUTTON_MAPTOOLSCENE, true);
			}
			else if (_buttonNum == 3)
			{
				imageButtonAdd("타이틀나가기", "", 750, WINSIZEY - 250, 74 * 2, 58 * 2, TITLESCENE_BUTTON_QUIT, true);
			}
			else
			{
				_isSelectMenuCreate = false;
			}
			_startCount = GetTickCount();
			_buttonNum++;
		}
	}
}
