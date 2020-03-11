#pragma once
#include "ui.h"
#include "shop.h"

enum UI_SHOPBUTTONKIND
{
UI_SHOPBUTTONKIND_NULL,
UI_SHOPBUTTONKIND_UP,
UI_SHOPBUTTONKIND_DOWN,
UI_SHOPBUTTONKIND_WHEELBUTTON,
UI_SHOPBUTTONKIND_EXIT,
UI_SHOPBUTTONKIND_END
};


class ui_shop:public ui
{
private:
	shop *_shop;							//상점을 선언합니다

	int _itemNum;							//선택된 아이템 넘버를 나타냅니다
	int _itemBottomNum;						//제일 아래에 위치한 아이템 번호를 나타냅니다
	int _itemMaxNum;						//아이템 최대갯수을 나타냅니다

	RECT _itemInvenRc[3][12];				//인벤창에 위치한 렉트를 나타냅니다
	RECT _itemShopRc[4];					//샵에 위치한 렉트를 나타냅니다


	int _infoItemX, _infoItemY, _infoShopItem;			//선택된 아이템을 보여주기 위한 임시 변수입니다

public:
	ui_shop();
	~ui_shop();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void selectItem();					//어떤 아이템에 마우스가 올라가있는지 판별하는 함수입니다
	void wheelButtonMove();
};

