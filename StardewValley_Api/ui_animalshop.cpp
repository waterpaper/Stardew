#include "stdafx.h"
#include "ui_animalshop.h"


ui_animalshop::ui_animalshop()
{
}


ui_animalshop::~ui_animalshop()
{
}

HRESULT ui_animalshop::init()
{
	uiImageAdd("상점UI_동물상점창", 250, 150, 500, 420, false);
	imageButtonAdd("cancel버튼", "", 250+432, 150+48, 35, 25, UI_SHOPBUTTONKIND_EXIT, true);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_animalRc[i][j] = RectMake(250 + 32 + 128 * j, 150 + 112 + 96 * i, 112, 96);
		}
	}

	return S_OK;
}

void ui_animalshop::update()
{
	ui::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				if (_vButton[i]._kind == UI_SHOPBUTTONKIND_EXIT)
				{
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsMenu(false);
					UIMANAGER->setIsShop(false);
					_sound.effSoundPlay("메뉴선택");
				}
				break;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (PtInRect(&_animalRc[i][j], m_ptMouse))
				{
					if (i == 0 && j == 0)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_CHICKEN);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 0 && j == 1)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_COW);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 0 && j == 2)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_GOAT);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 1 && j == 0)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_DUCK);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 1 && j == 1)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_SHEEP);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 1 && j == 2)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_RABBIT);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					if (i == 2 && j == 0)
					{
						UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT);
						UIMANAGER->setSelectAnimalkind(ANIMAL_KIND::ANIMAL_KIND_PIG);
						UIMANAGER->setIsMenu(false);
						UIMANAGER->setIsShop(false);
						_sound.effSoundPlay("메뉴선택");
						UIMANAGER->changeUi("UI_selectDialog");
					}
					return;
				}
			}
		}
	}
}

void ui_animalshop::release()
{
	ui::release();
}

void ui_animalshop::render(HDC hdc)
{
	ui::render(hdc);
}
