#include "stdafx.h"
#include "newGame.h"


newGame::newGame()
{
}


newGame::~newGame()
{
}

HRESULT newGame::init()
{
	_hairNum = PLAYERMANAGER->getPlayerHairNum() + 1;
	_shirtsNum = PLAYERMANAGER->getPlayerShirtsNum() + 1;

	_hairR = PLAYERMANAGER->getPlayerHairColor().r, _hairG = PLAYERMANAGER->getPlayerHairColor().g, _hairB = PLAYERMANAGER->getPlayerHairColor().b;
	_pantsR = PLAYERMANAGER->getPlayerPantsColor().r, _pantsG = PLAYERMANAGER->getPlayerPantsColor().g, _pantsB = PLAYERMANAGER->getPlayerPantsColor().b;

	_selectCharacterInfo = IMAGEMANAGER->findImage("새로운시작Ui");
	_barFront = IMAGEMANAGER->findImage("컨트롤바Front");
	_barBack = IMAGEMANAGER->findImage("컨트롤바Back");
	_controlButton = IMAGEMANAGER->findImage("컨트롤버튼");
	_okayButton = IMAGEMANAGER->findImage("okay버튼");
	_cancelButton = IMAGEMANAGER->findImage("cancel버튼");
	
	_hairRControlRect = RectMake(BAR_STARTX - 8, BAR_HAIRR_Y - 8, 16, 20);
	_hairGControlRect = RectMake(BAR_STARTX - 8, BAR_HAIRG_Y - 8, 16, 20);
	_hairBControlRect = RectMake(BAR_STARTX - 8, BAR_HAIRB_Y - 8, 16, 20);
	_pantsRControlRect = RectMake(BAR_STARTX - 8, BAR_PANTSR_Y - 8, 16, 20);
	_pantsGControlRect = RectMake(BAR_STARTX - 8, BAR_PANTSG_Y - 8, 16, 20);
	_pantsBControlRect = RectMake(BAR_STARTX - 8, BAR_PANTSB_Y - 8, 16, 20);

	_frontHair = RectMake(403, 443, 44, 41);
	_backHair = RectMake(272, 443, 44, 41);
	_frontShirts = RectMake(403, 580, 44, 41);
	_backShirts = RectMake(272, 580, 44, 41);

	_nowButtonKind = BAR_BUTTON_KIND_NULL;

	_nameRect = RectMake(575, 145, 187, 46);
	_farmNameRect = RectMake(575, 208, 187, 46);

	_isName = false, _isFarmName = false;

	_okayButtonRect = RectMake(840, 164, 64, 64);
	_cancelButtonRect = RectMake(900, 100, 26 * 3, 12 * 3);

	return S_OK;
}

void newGame::update()
{
	barControlButtonMove();
	selectButton();
	enteredName();
}

void newGame::release()
{

}

void newGame::render(HDC hdc)
{
	char str[256];

	_selectCharacterInfo->render(hdc, 200, 100);

	//배경모드
	SetBkMode(hdc, TRANSPARENT);
	//색상
	SetTextColor(hdc, RGB(0, 0, 0));

	//종류 커스터마이징 출력
	sprintf_s(str, "%d", _hairNum);
	TextOut(hdc, 350, 460, str, strlen(str));

	sprintf_s(str, "%d", _shirtsNum);
	TextOut(hdc, 350, 600, str, strlen(str));


	//색 커스터마이징 출력
	sprintf_s(str, "R          %d", _hairR);
	TextOut(hdc, WINSIZEX / 2 + 70, 380, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_HAIRR_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_HAIRR_Y, _hairR, _barFront->getHeight());
	_controlButton->render(hdc, _hairRControlRect.left, _hairRControlRect.top);

	sprintf_s(str, "G          %d", _hairG);
	TextOut(hdc, WINSIZEX / 2 + 70, 430, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_HAIRG_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_HAIRG_Y, _hairG, _barFront->getHeight());
	_controlButton->render(hdc, _hairGControlRect.left, _hairGControlRect.top);

	sprintf_s(str, "B          %d", _hairB);
	TextOut(hdc, WINSIZEX / 2 + 70, 480, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_HAIRB_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_HAIRB_Y, _hairB, _barFront->getHeight());
	_controlButton->render(hdc, _hairBControlRect.left, _hairBControlRect.top);

	sprintf_s(str, "R          %d", _pantsR);
	TextOut(hdc, WINSIZEX / 2 + 70, 550, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_PANTSR_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_PANTSR_Y, _pantsR, _barFront->getHeight());
	_controlButton->render(hdc, _pantsRControlRect.left, _pantsRControlRect.top);

	sprintf_s(str, "G          %d", _pantsG);
	TextOut(hdc, WINSIZEX / 2 + 70, 600, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_PANTSG_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_PANTSG_Y, _pantsG, _barFront->getHeight());
	_controlButton->render(hdc, _pantsGControlRect.left, _pantsGControlRect.top);

	sprintf_s(str, "B          %d", _pantsB);
	TextOut(hdc, WINSIZEX / 2 + 70, 650, str, strlen(str));
	_barBack->render(hdc, BAR_STARTX, BAR_PANTSB_Y);
	_barFront->render(hdc, BAR_STARTX, BAR_PANTSB_Y, _pantsB, _barFront->getHeight());
	_controlButton->render(hdc, _pantsBControlRect.left, _pantsBControlRect.top);


	//글씨출력
	SetTextAlign(hdc, TA_RIGHT);
	TextOut(hdc, 750, 145, _playerName.c_str(), strlen(_playerName.c_str()));
	TextOut(hdc, 750, 208, _farmName.c_str(), strlen(_farmName.c_str()));
	SetTextAlign(hdc, TA_LEFT);

	//확인버튼
	_okayButton->render(hdc, _okayButtonRect.left, _okayButtonRect.top);


	//취소버튼
	_cancelButton->frameRender(hdc, _cancelButtonRect.left, _cancelButtonRect.top);

	PLAYERMANAGER->render(hdc);
}

int newGame::barLocationX(int num)
{
	return BAR_STARTX + num;
}

void newGame::barControlButton(BAR_BUTTON_KIND kind, int num)
{
	if (num < 0 || num > 255) return;

	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_HAIR_R)
	{
		_hairRControlRect = RectMake(BAR_STARTX + num - 8, BAR_HAIRR_Y - 8, 16, 20);
		_hairR = num;
	}
	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_HAIR_G)
	{
		_hairGControlRect = RectMake(BAR_STARTX + num - 8, BAR_HAIRG_Y - 8, 16, 20);
		_hairG = num;
	}
	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_HAIR_B)
	{
		_hairBControlRect = RectMake(BAR_STARTX + num - 8, BAR_HAIRB_Y - 8, 16, 20);
		_hairB = num;
	}
	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_PANTS_R)
	{
		_pantsRControlRect = RectMake(BAR_STARTX + num - 8, BAR_PANTSR_Y - 8, 16, 20);
		_pantsR = num;
	}
	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_PANTS_G)
	{
		_pantsGControlRect = RectMake(BAR_STARTX + num - 8, BAR_PANTSG_Y - 8, 16, 20);
		_pantsG = num;
	}
	if (kind == BAR_BUTTON_KIND::BAR_BUTTON_KIND_PANTS_B)
	{
		_pantsBControlRect = RectMake(BAR_STARTX + num - 8, BAR_PANTSB_Y - 8, 16, 20);
		_pantsB = num;
	}
}

void newGame::barControlButtonMove()
{
	/*
	커스터마이징 버튼을 처리합니다
	왼쪽 버튼으로 값을 조절하며
	버튼을 떼게 되면 값이 적용되어 플레이어에 보이게 됩니다(시간 걸림)
	*/

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_hairRControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_HAIR_R)
		{
			barControlButton(BAR_BUTTON_KIND_HAIR_R, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_HAIR_R;
		}
		else if (PtInRect(&_hairGControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_HAIR_G)
		{
			barControlButton(BAR_BUTTON_KIND_HAIR_G, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_HAIR_G;
		}
		else if (PtInRect(&_hairBControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_HAIR_B)
		{
			barControlButton(BAR_BUTTON_KIND_HAIR_B, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_HAIR_B;
		}
		else if (PtInRect(&_pantsRControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_PANTS_R)
		{
			barControlButton(BAR_BUTTON_KIND_PANTS_R, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_PANTS_R;
		}
		else if (PtInRect(&_pantsGControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_PANTS_G)
		{
			barControlButton(BAR_BUTTON_KIND_PANTS_G, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_PANTS_G;
		}
		else if (PtInRect(&_pantsBControlRect, m_ptMouse) || _nowButtonKind == BAR_BUTTON_KIND_PANTS_B)
		{
			barControlButton(BAR_BUTTON_KIND_PANTS_B, m_ptMouse.x - BAR_STARTX);
			_nowButtonKind = BAR_BUTTON_KIND_PANTS_B;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_nowButtonKind == BAR_BUTTON_KIND_HAIR_R || _nowButtonKind == BAR_BUTTON_KIND_HAIR_G || _nowButtonKind == BAR_BUTTON_KIND_HAIR_B)
		{
			PLAYERMANAGER->setPlayerHairColor(color{ _hairR, _hairG, _hairB });
		}
		else if (_nowButtonKind == BAR_BUTTON_KIND_PANTS_R || _nowButtonKind == BAR_BUTTON_KIND_PANTS_G | _nowButtonKind == BAR_BUTTON_KIND_PANTS_B)
		{
			PLAYERMANAGER->setPlayerPantsColor(color{ _pantsR, _pantsG, _pantsB });
		}

		_nowButtonKind = BAR_BUTTON_KIND_NULL;
	}
}

void newGame::selectButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_backHair, m_ptMouse))
		{
			if (_hairNum == 1) return;

			_hairNum--;
			PLAYERMANAGER->setPlayerHairNum(_hairNum - 1);

			_sound.effSoundPlay("메뉴선택");
		}
		if (PtInRect(&_frontHair, m_ptMouse))
		{
			if (_hairNum == 32) return;

			_hairNum++;
			PLAYERMANAGER->setPlayerHairNum(_hairNum - 1);

			_sound.effSoundPlay("메뉴선택");
		}
		if (PtInRect(&_backShirts, m_ptMouse))
		{
			if (_shirtsNum == 1) return;

			_shirtsNum--;
			PLAYERMANAGER->setPlayerShirtsNum(_shirtsNum - 1);

			_sound.effSoundPlay("메뉴선택");
		}
		if (PtInRect(&_frontShirts, m_ptMouse))
		{
			if (_shirtsNum == 112) return;

			_shirtsNum++;
			PLAYERMANAGER->setPlayerShirtsNum(_shirtsNum - 1);

			_sound.effSoundPlay("메뉴선택");
		}

		//게임 스타트
		if (PtInRect(&_okayButtonRect, m_ptMouse))
		{
			gameStart();

			_sound.effSoundPlay("메뉴선택");
		}

		//돌아가기
		if (PtInRect(&_cancelButtonRect, m_ptMouse))
		{
			SCENEMANAGER->changeScene("titleScene");
			UIMANAGER->setIsMenu(false);

			_sound.effSoundPlay("메뉴선택");
		}

		//글씨 처리
		if (PtInRect(&_nameRect, m_ptMouse))
		{
			_isName = true;
			_isFarmName = false;
			INPUTMANAGER->stopKeyBoard();
			INPUTMANAGER->startKeyBoard();
		}
		else if (PtInRect(&_farmNameRect, m_ptMouse))
		{
			_isFarmName = true;
			_isName = false;
			INPUTMANAGER->stopKeyBoard();
			INPUTMANAGER->startKeyBoard();
		}
		else
		{
			_isFarmName = false;
			_isName = false;
			INPUTMANAGER->stopKeyBoard();
		}
	}
}

void newGame::enteredName()
{
	if (_isName)
	{
		_playerName = INPUTMANAGER->getKeyBoard();
	}
	else if (_isFarmName)
	{
		_farmName = INPUTMANAGER->getKeyBoard();
	}
}

void newGame::gameStart()
{
	PLAYERMANAGER->setPlayerName(_playerName);
	PLAYERMANAGER->setPlayerFarmName(_farmName);
	PLAYERMANAGER->setPlayerPosition(480, 480);
	CAMERAMANAGER->setCameraPos(POINT{ 0,0 });

	if (INVENTORYMANAGER->getInventory().getNowSize() == 0)
	{
		INVENTORYMANAGER->gameStart();
	}
	_sound.soundOff();
	_sound.soundPlay("농장");

	SCENEMANAGER->changeScene("homeScene");
}

