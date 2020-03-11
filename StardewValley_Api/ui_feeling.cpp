#include "stdafx.h"
#include "ui_feeling.h"


ui_feeling::ui_feeling()
{
}


ui_feeling::~ui_feeling()
{
}

HRESULT ui_feeling::init()
{
	int feelingNum;
	feelingList listTemp;

	uiImageAdd("메뉴창_호감도", 150, 50, 700, 608, false);
	imageButtonAdd(nullptr, "", 192, 50, 54, 60, UIBUTTONKIND_INVENTORY, false);
	imageButtonAdd(nullptr, "", 246, 50, 54, 60, UIBUTTONKIND_FEELING, false);
	imageButtonAdd(nullptr, "", 300, 50, 54, 60, UIBUTTONKIND_MAP, false);
	imageButtonAdd(nullptr, "", 354, 50, 54, 60, UIBUTTONKIND_MAKING, false);
	imageButtonAdd(nullptr, "", 408, 50, 54, 60, UIBUTTONKIND_EXIT, false);
	imageButtonAdd("cancel버튼", "", 900, 50, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_vNpc = NPCMANAGER->getNpcVector();
	_vFeelingList.reserve(_vNpc.size());

	for (int i = 0; i < _vNpc.size(); i++)
	{
		feelingNum = _vNpc[i]->getFeeling();

		listTemp.npcVectorNum = i;
		listTemp.feelingNum = feelingNum;

		if (_vFeelingList.size() == 0)
		{
			_vFeelingList.push_back(listTemp);
			continue;
		}
		for (int j = 0; j < _vFeelingList.size(); j++)
		{
			if (_vFeelingList[j].feelingNum < feelingNum)
			{
				_viFeelingList = _vFeelingList.begin() + j;
				_viFeelingList = _vFeelingList.insert(_viFeelingList, listTemp);

				break;
			}

			if (j == _vFeelingList.size() - 1)
			{
				_vFeelingList.push_back(listTemp);
				break;
			}
		}
	}

	return S_OK;
}

void ui_feeling::update()
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
				else if (_vButton[i]._kind == UIBUTTONKIND_MAKING)
				{
					UIMANAGER->changeUi("UI_making");
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

void ui_feeling::release()
{
	ui::release();
	_vFeelingList.clear();
}

void ui_feeling::render(HDC hdc)
{
	char strTemp[256];
	ui::render(hdc);
	int num;

	for (int i = 0; i < _vFeelingList.size(); i++)
	{
		_vNpc[_vFeelingList[i].npcVectorNum]->getCharacterFeelingImage()->render(hdc, 182, 154 + 104 * i);

			//배경모드
		SetBkMode(hdc, TRANSPARENT);
		sprintf(strTemp, "%s", _vNpc[_vFeelingList[i].npcVectorNum]->getName().c_str());
		TextOut(hdc, 256, 146 + 104 * i, strTemp, strlen(strTemp));

		num = _vNpc[_vFeelingList[i].npcVectorNum]->getFeeling();

		for (int j = 0; j < 10; j++)
		{
			if (num / 10 > j)
			{
				IMAGEMANAGER->render("UI_하트", hdc, 406 + 24 * j, 162 + 104 * i);
			}
			else
			{
				IMAGEMANAGER->render("UI_빈하트", hdc, 406 + 24 * j, 162 + 104 * i);
			}
		}

		sprintf(strTemp, "%d", num);
		TextOut(hdc, 742, 154 + 104 * i, strTemp, strlen(strTemp));

	}
}
