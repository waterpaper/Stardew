#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true, false);
	SCENEMANAGER->addScene("loadingScene", new loadingScene);
	SCENEMANAGER->addScene("titleScene", new titleScene);
	SCENEMANAGER->addScene("newGameScene", new newGameScene);

	SCENEMANAGER->addScene("maptoolScene", new maptoolScene);
	SCENEMANAGER->addScene("maptoolSub", new maptool_sub);

	SCENEMANAGER->addScene("homeScene", new homeScene);
	SCENEMANAGER->addScene("farmScene", new farmScene);
	SCENEMANAGER->addScene("homeToTownRoadScene", new homeToTownRoadScene);
	SCENEMANAGER->addScene("townScene", new townScene);
	SCENEMANAGER->addScene("shopScene", new shopScene);
	SCENEMANAGER->addScene("animalShopScene", new animalShopScene);
	SCENEMANAGER->addScene("coopScene", new coopScene);
	SCENEMANAGER->addScene("barnScene", new barnScene);
	SCENEMANAGER->addScene("loadGameScene", new loadGameScene);

	_mouseIcon = IMAGEMANAGER->addFrameImage("마우스", "images/ui/Ui_cursor.bmp", 128 * 3, 16 * 3, 8, 1, true, RGB(255, 0, 255));
	SetCursor(NULL);
	ShowCursor(FALSE);

	IMAGEMANAGER->addImage("화면_블랙스크린", "images/ui/Ui_blackScreen.bmp", 1024, 768, true, RGB(255, 0, 255));

	OldFont = (HFONT)SelectObject(getMemDC(), hFont);

	////현재씬
	SCENEMANAGER->changeScene("loadingScene");

	IMAGEMANAGER->addImage("UI_키설명화면", "images/ui/Ui_keyExplanation.bmp", 800, 558, true, RGB(255, 0, 255));
	_keyExplanation = IMAGEMANAGER->findImage("UI_키설명화면");
	_isKeyExplanation = false;

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SCENEMANAGER->release();
	UIMANAGER->release();
}

void mainGame::update()
{
	gameNode::update();

	if (!_isKeyExplanation)
	{
		UIMANAGER->update();
		_sound.update();
		if (!UIMANAGER->getIsMenu() && !UIMANAGER->getIsShop() && !UIMANAGER->getIsConversation())
		{
			SCENEMANAGER->update();
			ANIMATIONMANAGER->update();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F3))
		{
			_isDebug = !_isDebug;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			_isSound = !_isSound;
			_sound.soundOff();
			_sound.effSoundOff();
		}
	}
	//키 설명을 하는 창을 띄우는 여부
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_isKeyExplanation = !_isKeyExplanation;
	}
	

}

void mainGame::render()
{
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//====================================================

	SelectObject(getMemDC(), hFont);
	SCENEMANAGER->render();

	SelectObject(getMemDC(), OldFont);
	TIMEMANAGER->render(getMemDC());

	if (!SUBWIN->GetIsActive())
	{
		_mouseIcon->frameRender(getMemDC(), m_ptMouse.x, m_ptMouse.y, _mouseFrameX, _mouseFrameY);
	}

	if (_isKeyExplanation)
	{
		_keyExplanation->render(getMemDC(),100,50);
	}
	//=====================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

