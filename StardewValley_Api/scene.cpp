#include "stdafx.h"
#include "scene.h"


scene::scene()
{
}


scene::~scene()
{
	release();
}

HRESULT scene::init()
{
	_ingameName = INGAMESCENE_NAME_NULL;

	_blackScreen = IMAGEMANAGER->findImage("화면_블랙스크린");
	_blackAlpha = 255;

	_mouseFrameX = 0;
	_mouseFrameY = 0;

	_sound.effSoundOff();

	return S_OK;
}

void scene::update()
{
	imageButtonPoint();

	if (_sceneName == SCENE_NAME_INGAME_SCENE)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F10))
		{
			_isAttribute = !_isAttribute;
			if (_isAttribute)
			{
				TILEMAPMANAGER->attributeRender();
			}
		}

		setMouseFrame();
		GAMETIMEMANAGER->update();
		PLAYERMANAGER->update();
		NPCMANAGER->update();
		EFFECTMANAGER->update();
		ITEMMANAGER->update();
	}
}

void scene::release()
{
	imageButtonClear();
	clearMoveRc();

	if (_sceneName == SCENE_NAME_INGAME_SCENE)
	{
		ITEMMANAGER->release();
	}
}

void scene::render()
{
	imageButtonRender();

	if (_sceneName == SCENE_NAME_INGAME_SCENE)
	{
		CAMERAMANAGER->render(getMemDC(), false, _moveRcVector);
		UIMANAGER->render(getMemDC());

		if (_blackAlpha > 0)
		{
			_blackScreen->alphaRender(getMemDC(), 0, 0, (BYTE)_blackAlpha);
			_blackAlpha -= 4;
		}
		else
		{
			_blackScreen = nullptr;
		}
	}
	else if (_sceneName == SCENE_NAME_MAPTOOL_SCENE)
	{
		CAMERAMANAGER->render(getMemDC(), true, _moveRcVector);

		if (_blackAlpha > 0)
		{
			_blackScreen->alphaRender(getMemDC(), 0, 0, (BYTE)_blackAlpha);
			_blackAlpha -= 4;
		}
		else
		{
			_blackScreen = nullptr;
		}
	}

	else
	{
		if (_blackAlpha > 0)
		{
			_blackScreen->alphaRender(getMemDC(), 0, 0, (BYTE)_blackAlpha);
			_blackAlpha -= 2;
		}
		else
		{
			_blackScreen = nullptr;
		}
	}
}

void scene::imageButtonRender()
{
	/*
	이미지 버튼을 그려줍니다
	프레임이미지(마우스 올렷을시 달라지는 이미지)가 존재하는 버튼과 아닌 버튼을 구별해 그려줍니다.
	*/
	for (int i = 0; i < button.size(); i++)
	{
		if (button[i]._isFrame)
		{
			if (button[i]._ischeck)
			{
				button[i]._img->frameRender(getMemDC(), button[i]._rc.left, button[i]._rc.top, button[i]._currentX, 0);
			}
			else
			{
				button[i]._img->frameRender(getMemDC(), button[i]._rc.left, button[i]._rc.top, 0, 0);
			}
		}
		else
		{
			button[i]._img->render(getMemDC(), button[i]._rc.left, button[i]._rc.top);
		}

		//배경모드
		SetBkMode(getMemDC(), TRANSPARENT);
		//색상
		SetTextColor(getMemDC(), RGB(0, 0, 0));

		TextOut(getMemDC(), 0, 0, button[i]._text.c_str(), button[i]._text.size());
	}
}

void scene::imageButtonPoint()
{
	/*
	현재 마우스가 어떤 버튼위에 있는지 판단합니다
	*/
	for (int i = 0; i < button.size(); i++)
	{
		if (!button[i]._isFrame) continue;

		if (PtInRect(&button[i]._rc, m_ptMouse))
		{
			button[i]._ischeck = true;
			button[i]._currentX = 1;
		}
		else
		{
			button[i]._ischeck = false;
			button[i]._currentX = 0;
		}
	}
}

void scene::imageButtonAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame)
{
	imageButton buttonTemp;

	buttonTemp._img = IMAGEMANAGER->findImage(imageName);
	buttonTemp._text = text;
	buttonTemp._rc = RectMake(x, y, width, height);
	buttonTemp._kind = kind;
	buttonTemp._isFrame = frame;
	buttonTemp._ischeck = false;
	buttonTemp._currentX = 0;

	button.push_back(buttonTemp);
}

void scene::imageButtonClear()
{
	button.clear();
}

void scene::sceneLoading(const char * fileName, INGAMESCENE_NAME sceneName)
{
	TILEMAPMANAGER->loadTileMapIamge(fileName, sceneName);
}

void scene::addMoveRc(int x, int y, int width, int height)
{
	//이동 렉트를 추가합니다
	_moveRcVector.push_back(RectMakeCenter(x, y, width, height));
}

int scene::collisionRc(RECT rc)
{
	//이동 렉트와 플레이어의 위치가 겹쳣는지 판단합니다

	RECT temp;

	for (int i = 0; i < _moveRcVector.size(); i++)
	{
		if (IntersectRect(&temp, &_moveRcVector[i], &rc))
		{
			return i;
		}
	}

	return -1;
}

int scene::selectRc(POINT point)
{
	POINT cameraTemp;
	int rectPointTempX, rectPointTempY;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		cameraTemp = CAMERAMANAGER->getCameraPos();

		for (int i = 0; i < _moveRcVector.size(); i++)
		{
			if (PtInRect(&_moveRcVector[i], POINT{ m_ptMouse.x + cameraTemp.x,m_ptMouse.y + cameraTemp.y }))
			{
				rectPointTempX = _moveRcVector[i].left + (_moveRcVector[i].right - _moveRcVector[i].left) / 2;
				rectPointTempY = _moveRcVector[i].top + (_moveRcVector[i].bottom - _moveRcVector[i].top) / 2;

				if (getDistance(point.x, point.y, rectPointTempX, rectPointTempY) < 70.0)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

void scene::clearMoveRc()
{
	vector<RECT> vecterTemp;
	_moveRcVector.swap(vecterTemp);
	vecterTemp.clear();
}

void scene::setScenePosition(int x, int y)
{
	PLAYERMANAGER->setPlayerPosition(x, y);
	CAMERAMANAGER->cameraMove(x, y);
}

void scene::setMouseFrame()
{
	POINT cameraTemp;

	if (_sceneName == SCENE_NAME_INGAME_SCENE)
	{
		cameraTemp = CAMERAMANAGER->getCameraPos();
		cameraTemp.x += m_ptMouse.x;
		cameraTemp.y += m_ptMouse.y;

		if (_ingameName==INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
		{
			if (FARMMANAGER->getIsHarvesting(cameraTemp.x / (TILE_SIZE_X), cameraTemp.y / (TILE_SIZE_Y)))
			{
				_mouseFrameX = 2;
				return;
			}
		}
		else if (_ingameName == INGAMESCENE_NAME::INGAMESCENE_NAME_SHOP|| _ingameName == INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN)
		{

		}

		_mouseFrameX = 0;
	}
}

