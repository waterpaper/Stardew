#include "stdafx.h"
#include "item.h"


item::item() :
	_itemCategory(ITEMKIND_NULL),
	_itemDivision(-1),
	_itemSection(-1),

	_itemName(""),
	_itemExplanation(""),
	_itemNum(-1),
	_itemImg(nullptr),
	_itemImgFrame(POINT{ -1,-1 }),
	_sellValue(-1),
	_buyValue(-1)
{
}


item::~item()
{
}


void item::render(HDC hdc, int x, int y)
{
	if (_itemImg == nullptr) return;

	_itemImg->render(hdc, x, y);
}

void item::informationRender(HDC hdc, int x, int y)
{
	/*
	�κ��丮���� ������ ��ó�� ���콺 �̵��� �ش� ������ ������ ����մϴ�
	*/
	RECT rcTemp = RectMake(x + 20, y + 160, 250, 210);
	RECT rcTemp2 = RectMake(x + 70, y + 310, 250, 100);
	char strTemp[256];

	if (_itemImg == nullptr) return;

	IMAGEMANAGER->render("UI_����������", hdc, x, y);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(51, 31, 10));

	sprintf(strTemp, "%s", _itemName.c_str());
	TextOut(hdc, x + 24, y + 24, strTemp, strlen(strTemp));					//������ �̸�

	if (_itemCategory == ITEMKIND_EQUIPMENT || _itemCategory == ITEMKIND_TOOL || _itemCategory == ITEMKIND_NULL)
	{
		SetTextColor(hdc, RGB(133, 133, 133));
	}
	else if (_itemCategory == ITEMKIND_CROPS|| _itemCategory == ITEMKIND_MATERIAL)
	{
		SetTextColor(hdc, RGB(74, 137, 28));
	}
	else if (_itemCategory == ITEMKIND_SEED)
	{
		SetTextColor(hdc, RGB(165, 42, 42));
	}
	else if (_itemCategory == ITEMKIND_FOOD)
	{
		SetTextColor(hdc, RGB(220, 60, 0));
	}
	else if (_itemCategory == ITEMKIND_ROCK)
	{
		SetTextColor(hdc, RGB(110, 0, 90));
	}
	else if (_itemCategory == ITEMKIND_ANIMALITEM)
	{
		SetTextColor(hdc, RGB(220, 60, 0));
	}

	sprintf(strTemp, "%s", itemCategoryPrint(_itemDivision).c_str());
	TextOut(hdc, x + 24, y + 84, strTemp, strlen(strTemp));					//������ ����


	SetTextColor(hdc, RGB(51, 31, 10));

	sprintf(strTemp, "%s", _itemExplanation.c_str());
	DrawText(hdc, strTemp, strlen(strTemp), &rcTemp, DT_LEFT | DT_WORDBREAK);	//�����ۼ���

	if (_addHp > 0)
	{
		IMAGEMANAGER->render("UI_����������_�ൿ��", hdc, x + 15, y + 310);
		IMAGEMANAGER->render("UI_����������_ü��", hdc, x + 15, y + 360);

		sprintf(strTemp, "��� + %d\nü�� + %d", _addHp, _addActingPower);
		DrawText(hdc, strTemp, strlen(strTemp), &rcTemp2, DT_LEFT | DT_WORDBREAK);	//�����ۼ���
	}

	SetTextColor(hdc, RGB(183, 89, 20));
}

void item::getItmeRender(HDC hdc, int x, int y)
{
	/*
	�������� ŉ�������� ����ϴ� �Լ��Դϴ�
	*/

	char strTemp[256];

	if (_itemImg == nullptr) return;

	IMAGEMANAGER->render("UI_�������Լ�", hdc, x, y);
	_itemImg->render(hdc, x + 20, y + 20);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));

	sprintf(strTemp, "%s", _itemName.c_str());
	TextOut(hdc, x + 100, y + 32, strTemp, strlen(strTemp));					//������ �̸�
}

string item::itemCategoryPrint(int itemDivision)
{
	string strTemp;

	if (_itemCategory == ITEMKIND_NULL)
	{
		strTemp = "";
	}
	if (_itemCategory == ITEMKIND_EQUIPMENT)
	{
		strTemp = "���";
	}
	if (_itemCategory == ITEMKIND_TOOL)
	{
		strTemp = "����";
	}
	if (_itemCategory == ITEMKIND_CROPS)
	{
		strTemp = "���۹�";
	}
	if (_itemCategory == ITEMKIND_SEED)
	{
		strTemp = "����";
	}
	if (_itemCategory == ITEMKIND_FOOD)
	{
		strTemp = "����";
	}
	if (_itemCategory == ITEMKIND_CRAFTABLE)
	{
		strTemp = "����ǰ";
	}
	if (_itemCategory == ITEMKIND_ROCK)
	{
		strTemp = "����";
	}
	if (_itemCategory == ITEMKIND_ANIMALITEM)
	{
		strTemp = "�������깰";
	}
	if (_itemCategory == ITEMKIND_MATERIAL)
	{
		strTemp = "���";
	}
	return strTemp;
}

