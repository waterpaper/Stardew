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
	인벤토리에서 아이템 근처로 마우스 이동시 해당 아이템 정보를 출력합니다
	*/
	RECT rcTemp = RectMake(x + 20, y + 160, 250, 210);
	RECT rcTemp2 = RectMake(x + 70, y + 310, 250, 100);
	char strTemp[256];

	if (_itemImg == nullptr) return;

	IMAGEMANAGER->render("UI_아이템정보", hdc, x, y);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(51, 31, 10));

	sprintf(strTemp, "%s", _itemName.c_str());
	TextOut(hdc, x + 24, y + 24, strTemp, strlen(strTemp));					//아이템 이름

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
	TextOut(hdc, x + 24, y + 84, strTemp, strlen(strTemp));					//아이템 종류


	SetTextColor(hdc, RGB(51, 31, 10));

	sprintf(strTemp, "%s", _itemExplanation.c_str());
	DrawText(hdc, strTemp, strlen(strTemp), &rcTemp, DT_LEFT | DT_WORDBREAK);	//아이템설명

	if (_addHp > 0)
	{
		IMAGEMANAGER->render("UI_아이템정보_행동력", hdc, x + 15, y + 310);
		IMAGEMANAGER->render("UI_아이템정보_체력", hdc, x + 15, y + 360);

		sprintf(strTemp, "기력 + %d\n체력 + %d", _addHp, _addActingPower);
		DrawText(hdc, strTemp, strlen(strTemp), &rcTemp2, DT_LEFT | DT_WORDBREAK);	//아이템설명
	}

	SetTextColor(hdc, RGB(183, 89, 20));
}

void item::getItmeRender(HDC hdc, int x, int y)
{
	/*
	아이템을 흭득햇을시 출력하는 함수입니다
	*/

	char strTemp[256];

	if (_itemImg == nullptr) return;

	IMAGEMANAGER->render("UI_아이템입수", hdc, x, y);
	_itemImg->render(hdc, x + 20, y + 20);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));

	sprintf(strTemp, "%s", _itemName.c_str());
	TextOut(hdc, x + 100, y + 32, strTemp, strlen(strTemp));					//아이템 이름
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
		strTemp = "장비";
	}
	if (_itemCategory == ITEMKIND_TOOL)
	{
		strTemp = "도구";
	}
	if (_itemCategory == ITEMKIND_CROPS)
	{
		strTemp = "농작물";
	}
	if (_itemCategory == ITEMKIND_SEED)
	{
		strTemp = "씨앗";
	}
	if (_itemCategory == ITEMKIND_FOOD)
	{
		strTemp = "음식";
	}
	if (_itemCategory == ITEMKIND_CRAFTABLE)
	{
		strTemp = "제작품";
	}
	if (_itemCategory == ITEMKIND_ROCK)
	{
		strTemp = "광석";
	}
	if (_itemCategory == ITEMKIND_ANIMALITEM)
	{
		strTemp = "동물생산물";
	}
	if (_itemCategory == ITEMKIND_MATERIAL)
	{
		strTemp = "재료";
	}
	return strTemp;
}

