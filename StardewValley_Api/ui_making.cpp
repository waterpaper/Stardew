#include "stdafx.h"
#include "ui_making.h"


ui_making::ui_making()
{
}


ui_making::~ui_making()
{
}

HRESULT ui_making::init()
{
	ui::init();

	uiImageAdd("메뉴창_제작", 150, 50, 700, 608, false);
	imageButtonAdd(nullptr, "", 192, 50, 54, 60, UIBUTTONKIND_INVENTORY, false);
	imageButtonAdd(nullptr, "", 246, 50, 54, 60, UIBUTTONKIND_FEELING, false);
	imageButtonAdd(nullptr, "", 300, 50, 54, 60, UIBUTTONKIND_MAP, false);
	imageButtonAdd(nullptr, "", 354, 50, 54, 60, UIBUTTONKIND_MAKING, false);
	imageButtonAdd(nullptr, "", 408, 50, 54, 60, UIBUTTONKIND_EXIT, false);
	imageButtonAdd("cancel버튼", "", 900, 50, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	return S_OK;
}

void ui_making::update()
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
				else if (_vButton[i]._kind == UIBUTTONKIND_MAP)
				{
					UIMANAGER->changeUi("UI_minimap");
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

void ui_making::release()
{
	ui::release();
}

void ui_making::render(HDC hdc)
{
	ui::render(hdc);
}
