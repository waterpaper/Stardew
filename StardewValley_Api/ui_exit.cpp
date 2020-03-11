#include "stdafx.h"
#include "ui_exit.h"


ui_exit::ui_exit()
{
}


ui_exit::~ui_exit()
{
}

HRESULT ui_exit::init()
{
	_barFront = IMAGEMANAGER->findImage("컨트롤바Front");
	_barBack = IMAGEMANAGER->findImage("컨트롤바Back");
	_controlButton = IMAGEMANAGER->findImage("컨트롤버튼");

	uiImageAdd("메뉴창_나가기", 150, 50, 700, 608, false);
	imageButtonAdd(nullptr, "", 192, 50, 54, 60, UIBUTTONKIND_INVENTORY, false);
	imageButtonAdd(nullptr, "", 246, 50, 54, 60, UIBUTTONKIND_FEELING, false);
	imageButtonAdd(nullptr, "", 300, 50, 54, 60, UIBUTTONKIND_MAP, false);
	imageButtonAdd(nullptr, "", 354, 50, 54, 60, UIBUTTONKIND_MAKING, false);
	imageButtonAdd(nullptr, "", 408, 50, 54, 60, UIBUTTONKIND_EXIT, false);
	imageButtonAdd("cancel버튼", "", 900, 50, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);
	imageButtonAdd("메뉴창_나가기메뉴_타이틀", "", 370, 250, 280, 104, UIBUTTONKIND_EXITKIND_TITLE, true);
	imageButtonAdd("메뉴창_나가기메뉴_나가기", "", 400, 380, 212, 104, UIBUTTONKIND_EXITKIND_EXIT, true);

	_backgroundVolumeSize = _sound.getBgmVolume() * 100;
	_effectVolumeSize = _sound.getEffVolume() * 100;

	_frontBackGroundVolume = RectMake(350, 550, _backgroundVolumeSize*2, 16);
	_backBackGroundVolume = RectMake(340, 550, 220, 16);
	_frontEffectVolume = RectMake(350, 600, _effectVolumeSize *2, 16);
	_backEffectVolume = RectMake(340, 600, 220, 16);

	_backGroundControlButton = RectMake(_backgroundVolumeSize * 2+350 - 8, 550 - 2, 16, 20);
	_effectControlButton = RectMake(350+ _effectVolumeSize * 2 - 8, 600 - 2, 16, 20);

	return S_OK;
}

void ui_exit::update()
{
	ui::update();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_backBackGroundVolume, m_ptMouse))
		{
			barControlButtonMove(UIBUTTONKIND_EXITKIND_BACKGROUND, m_ptMouse.x - 350);
		}
		else if (PtInRect(&_backEffectVolume, m_ptMouse))
		{
			barControlButtonMove(UIBUTTONKIND_EXITKIND_EFFECT, m_ptMouse.x - 350);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				if (_vButton[i]._kind == UIBUTTONKIND_INVENTORY)
				{
					UIMANAGER->changeUi("UI_inventory");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_FEELING)
				{
					UIMANAGER->changeUi("UI_feeling");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_MAP)
				{
					UIMANAGER->changeUi("UI_minimap");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_MAKING)
				{
					UIMANAGER->changeUi("UI_making");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
				{
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsMenu(false);
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_EXITKIND_TITLE)
				{
					UIMANAGER->setIsMenu(false);
					UIMANAGER->changeUi("UI_general");
					PLAYERMANAGER->init();
					GAMETIMEMANAGER->init();
					INVENTORYMANAGER->clearInventory();
					ANIMALMANAGER->clearAnimal();
					NPCMANAGER->npcClear();
					FARMMANAGER->farmClear();
					FARMMANAGER->setIsFirst(true);
					SCENEMANAGER->changeScene("titleScene");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_EXITKIND_EXIT)
				{
					DestroyWindow(m_hWnd);
				}

				_sound.effSoundPlay("메뉴선택");
				break;
			}
		}
	}
}

void ui_exit::release()
{
	ui::release();
}

void ui_exit::render(HDC hdc)
{
	char strTemp[256];
	ui::render(hdc);
	
	sprintf(strTemp,"%d", _backgroundVolumeSize);
	TextOut(hdc,600,540, strTemp,strlen(strTemp));
	sprintf(strTemp, "%d", _effectVolumeSize);
	TextOut(hdc, 600, 590, strTemp, strlen(strTemp));

	TextOut(hdc, 200, 540, "음량 : ", strlen("음량 : "));
	TextOut(hdc, 200, 590, "효과음 : ", strlen("효과음 : "));
	_barBack->render(hdc, _backBackGroundVolume.left+10, _backBackGroundVolume.top, _backBackGroundVolume.right - _backBackGroundVolume.left-20, _backBackGroundVolume.bottom - _backBackGroundVolume.top);
	_barFront->render(hdc, _frontBackGroundVolume.left, _frontBackGroundVolume.top, _frontBackGroundVolume.right- _frontBackGroundVolume.left, _frontBackGroundVolume.bottom- _frontBackGroundVolume.top);
	_controlButton->render(hdc, _backGroundControlButton.left, _backGroundControlButton.top);

	_barBack->render(hdc, _backEffectVolume.left+10, _backEffectVolume.top, _backEffectVolume.right - _backEffectVolume.left-20, _backEffectVolume.bottom - _backEffectVolume.top);
	_barFront->render(hdc, _frontEffectVolume.left, _frontEffectVolume.top, _frontEffectVolume.right - _frontEffectVolume.left, _frontEffectVolume.bottom- _frontEffectVolume.top);
	_controlButton->render(hdc, _effectControlButton.left, _effectControlButton.top);
}

void ui_exit::barControlButtonMove(UIBUTTONKIND_EXITKIND kind, int num)
{
	if (kind == UIBUTTONKIND_EXITKIND_BACKGROUND)
	{
		_backgroundVolumeSize = num / 2;
		if (_backgroundVolumeSize < 0)
		{
			_backgroundVolumeSize = 0;
		}
		else if (_backgroundVolumeSize > 100)
		{
			_backgroundVolumeSize = 100;
		}
		_sound.setBgmVolume(_backgroundVolumeSize / 100.0);
		_frontBackGroundVolume = RectMake(350, 550, _backgroundVolumeSize*2, 16);
		_backGroundControlButton = RectMake(350 + _backgroundVolumeSize*2 - 8, 550 - 2, 16, 20);
	}
	if (kind == UIBUTTONKIND_EXITKIND_EFFECT)
	{
		_effectVolumeSize = num / 2;
		if (_effectVolumeSize < 0)
		{
			_effectVolumeSize = 0;
		}
		else if (_effectVolumeSize > 100)
		{
			_effectVolumeSize = 100;
		}
		_sound.setEffVolume(_effectVolumeSize / 100.0);
		_frontEffectVolume = RectMake(350, 600, _effectVolumeSize*2, 16);
		_effectControlButton = RectMake(350 + _effectVolumeSize*2 - 8, 600 - 2, 16, 20);
	}
}
