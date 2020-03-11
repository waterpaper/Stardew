#include "stdafx.h"
#include "ui_minimap.h"


ui_minimap::ui_minimap()
{
}


ui_minimap::~ui_minimap()
{
}

HRESULT ui_minimap::init()
{
	ui::init();

	uiImageAdd("메뉴창_미니맵", 150, 50, 700, 608, false);
	imageButtonAdd(nullptr, "", 192, 50, 54, 60, UIBUTTONKIND_INVENTORY, false);
	imageButtonAdd(nullptr, "", 246, 50, 54, 60, UIBUTTONKIND_FEELING, false);
	imageButtonAdd(nullptr, "", 300, 50, 54, 60, UIBUTTONKIND_MAP, false);
	imageButtonAdd(nullptr, "", 354, 50, 54, 60, UIBUTTONKIND_MAKING, false);
	imageButtonAdd(nullptr, "", 408, 50, 54, 60, UIBUTTONKIND_EXIT, false);
	imageButtonAdd("cancel버튼", "", 900, 50, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_cameraImg = IMAGEMANAGER->findImage("맵툴창_카메라");
	CAMERAMANAGER->setMinimapSize(POINT{ 600, 480 });
	return S_OK;
}

void ui_minimap::update()
{
	ui::update();

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
				else if (_vButton[i]._kind == UIBUTTONKIND_MAKING)
				{
					UIMANAGER->changeUi("UI_making");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_EXIT)
				{
					UIMANAGER->changeUi("UI_exit");
				}
				else if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
				{
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsMenu(false);
				}

				_sound.effSoundPlay("메뉴선택");
				break;
			}
		}
	}
}

void ui_minimap::release()
{
	ui::release();
}

void ui_minimap::render(HDC hdc)
{
	ui::render(hdc);
	CAMERAMANAGER->minimapRender(hdc,600, 480, 195, 140);
	POINT mapSize = TILEMAPMANAGER->getTileMapSize();
	POINT camera = CAMERAMANAGER->getCameraPos();

	int totalMapSizeX = mapSize.x *(TILE_SIZE_X);
	int totalMapSizeY = mapSize.y *(TILE_SIZE_Y);

	if (_cameraImg != nullptr)
	{
		//카메라
		if (totalMapSizeX < WINSIZEX && totalMapSizeY < WINSIZEY)
		{
			_cameraImg->render(hdc, 195, 140, 600, 480);
		}
		else if (totalMapSizeX < WINSIZEX)
		{
			_cameraImg->render(hdc, 195, 140 + camera.y / (totalMapSizeY / 480), 600, 480 * WINSIZEY / totalMapSizeY);
		}
		else if (totalMapSizeY < WINSIZEY)
		{
			_cameraImg->render(hdc, 195 + camera.x / (totalMapSizeX / 600), 140, 600 * WINSIZEX / totalMapSizeX, 480);
		}
		else
		{
			_cameraImg->render(hdc, 195 + camera.x / (totalMapSizeX / 600), 140 + camera.y / (totalMapSizeY / 480),
				600 * WINSIZEX / totalMapSizeX, 480 * WINSIZEY / totalMapSizeY);
		}
	}
}
