#include "stdafx.h"
#include "ui_selectDialog.h"


ui_selectDialog::ui_selectDialog()
{
}


ui_selectDialog::~ui_selectDialog()
{
}

HRESULT ui_selectDialog::init()
{
	UIMANAGER->setIsConversation(true);

	uiImageAdd("��ȭUI_����", 100, 450, 800, 228, false, false);
	imageButtonAdd("cancel��ư", "", 900, 400, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_num = UIMANAGER->getKindNum();
	_itemTemp = INVENTORYMANAGER->getItem(_num, 0);

	_invenLevel = INVENTORYMANAGER->getInventory().getInventoryLevel();

	_yesRect = RectMake(132, 546, 736, 48);
	_noRect = RectMake(132, 594, 736, 48);


	_kind = UIMANAGER->getSelectDialogKind();
	_buttonKind = UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_NULL;
	_selectBox = IMAGEMANAGER->findImage("UI_���ùڽ�2");
	_animalKind = UIMANAGER->getSelectAnimalKind();
	
	if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
	{
		_animalMoney = 800;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_DUCK)
	{
		_animalMoney = 4000;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
	{
		_animalMoney = 8000;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_COW)
	{
		_animalMoney = 1500;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_GOAT)
	{
		_animalMoney = 4000;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
	{
		_animalMoney = 8000;
	}
	else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_PIG)
	{
		_animalMoney = 16000;
	}
	else
	{
		_animalMoney = 0;
	}

	_sound.effSoundPlay("ĳ���ʹ�ȭ");

	return S_OK;
}

void ui_selectDialog::update()
{
	ui::update();
	if (PtInRect(&_yesRect, m_ptMouse))
	{
		_buttonKind = UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_YES;
	}
	else if (PtInRect(&_noRect, m_ptMouse))
	{
		_buttonKind = UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_NO;
	}
	else
	{
		_buttonKind = UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_NULL;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
				{
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsConversation(false);
				}
				_buttonKind = UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_NULL;

				break;
			}
		}

		//yesó��
		if (PtInRect(&_yesRect, m_ptMouse))
		{
			_sound.effSoundPlay("�޴�����");
			if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_EATTINGITEM)
			{
				INVENTORYMANAGER->eattingItem();
				UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND_NULL);
				UIMANAGER->setIsConversation(false);
				UIMANAGER->changeUi("UI_general");
				return;
			}
			else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_INVENTORYEXPAND)
			{
				if (_invenLevel == 1)
				{
					_possibleMoney = 4000;
				}
				else if(_invenLevel==2)
				{
					_possibleMoney = 10000;
				}

				if (PLAYERMANAGER->getPlayerMoney() < _possibleMoney)
				{
					_kind = UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NOTMONEY;
					UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND_NOTMONEY);
				}
				else
				{
					PLAYERMANAGER->setPlayerMoney(PLAYERMANAGER->getPlayerMoney()- _possibleMoney);
					INVENTORYMANAGER->inventoryUpgrade();
					UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NULL);
					UIMANAGER->setIsConversation(false);
					UIMANAGER->changeUi("UI_general");
				}
				return;
			}
			else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT)
			{
				//���� ���� ó��
				if (PLAYERMANAGER->getPlayerMoney() < _animalMoney)
				{
					_kind = UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NOTMONEY;
					UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND_NOTMONEY);
				}
				else
				{
					PLAYERMANAGER->setPlayerMoney(PLAYERMANAGER->getPlayerMoney() - _animalMoney);
					ANIMALMANAGER->addAnimal(_animalKind,1);
					UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NULL);
					UIMANAGER->setIsConversation(false);
					UIMANAGER->changeUi("UI_general");
				}
			}
			else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NOTMONEY)
			{
				UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND_NULL);
				UIMANAGER->setIsConversation(false);
				UIMANAGER->changeUi("UI_general");
				return;
			}
		}
		//noó��
		else if (PtInRect(&_noRect, m_ptMouse))
		{
			_sound.effSoundPlay("�޴�����");
			UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND_NULL);
			UIMANAGER->setIsConversation(false);
			UIMANAGER->changeUi("UI_general");
			return;
		}
	}
}

void ui_selectDialog::release()
{
	ui::release();
}

void ui_selectDialog::render(HDC hdc)
{
	char strTemp[512];

	ui::render(hdc);

	if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_EATTINGITEM)
	{
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));
		sprintf(strTemp, "%s�� �Խ��ϱ�?", _itemTemp.getItemName().c_str());
		TextOut(hdc, 148, 482, strTemp, strlen(strTemp));

		sprintf(strTemp, "��");
		TextOut(hdc, _yesRect.left + 16, _yesRect.top + 8, strTemp, strlen(strTemp));
		sprintf(strTemp, "�ƴϿ�");
		TextOut(hdc, _noRect.left + 16, _noRect.top + 8, strTemp, strlen(strTemp));
	}
	else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_INVENTORYEXPAND)
	{
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));

		if (_invenLevel == 1)
		{
			sprintf(strTemp, "���� ���׷��̵� -- 24ĭ");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));

			sprintf(strTemp, "�����ϱ�(4000 ���)");
			TextOut(hdc, _yesRect.left + 16, _yesRect.top + 8, strTemp, strlen(strTemp));
			sprintf(strTemp, "���߿� �����մϴ�");
			TextOut(hdc, _noRect.left + 16, _noRect.top + 8, strTemp, strlen(strTemp));
		}
		else if (_invenLevel == 2)
		{
			sprintf(strTemp, "���� ���׷��̵� -- 36ĭ");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));

			sprintf(strTemp, "�����ϱ�(10000���)");
			TextOut(hdc, _yesRect.left + 16, _yesRect.top + 8, strTemp, strlen(strTemp));
			sprintf(strTemp, "���߿� �����մϴ�");
			TextOut(hdc, _noRect.left + 16, _noRect.top + 8, strTemp, strlen(strTemp));
		}
	}
	else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_ANIMALSELECT)
	{
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));


		if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
		{
			sprintf(strTemp, "���� �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_DUCK)
		{
			sprintf(strTemp, "������ �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
		{
			sprintf(strTemp, "�䳢�� �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_COW)
		{
			sprintf(strTemp, "�Ҹ� �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_GOAT)
		{
			sprintf(strTemp, "���Ҹ� �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
		{
			sprintf(strTemp, "���� �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}
		else if (_animalKind == ANIMAL_KIND::ANIMAL_KIND_PIG)
		{
			sprintf(strTemp, "������ �����մϴ�");
			TextOut(hdc, 148, 482, strTemp, strlen(strTemp));
		}

		sprintf(strTemp, "�����ϱ�(%d ���)", _animalMoney);
		TextOut(hdc, _yesRect.left + 16, _yesRect.top + 8, strTemp, strlen(strTemp));
		sprintf(strTemp, "���߿� �����մϴ�");
		TextOut(hdc, _noRect.left + 16, _noRect.top + 8, strTemp, strlen(strTemp));

	}
	else if (_kind == UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NOTMONEY)
	{
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));

		sprintf(strTemp, "���� ���ڶ��ϴ�");
		TextOut(hdc, 148, 482, strTemp, strlen(strTemp));

		sprintf(strTemp, "��");
		TextOut(hdc, _yesRect.left + 16, _yesRect.top + 8, strTemp, strlen(strTemp));
		sprintf(strTemp, "���߿� �����մϴ�");
		TextOut(hdc, _noRect.left + 16, _noRect.top + 8, strTemp, strlen(strTemp));

	}


	//���콺�� ��ó�� ������ �ڽ��� �׷��ش�
	if (_buttonKind == UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_YES)
	{
		_selectBox->render(hdc, _yesRect.left, _yesRect.top, _yesRect.right- _yesRect.left, _yesRect.bottom- _yesRect.top);
	}
	else if (_buttonKind == UI_SELECTDIALOG_BUTTONKIND::UI_SELECTDIALOG_BUTTONKIND_NO)
	{
		_selectBox->render(hdc, _noRect.left, _noRect.top, _noRect.right - _noRect.left, _noRect.bottom - _noRect.top);
	}
}

int ui_selectDialog::getKindNum()
{
	return UIMANAGER->getSelectItem();
}
