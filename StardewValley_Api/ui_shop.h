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
	shop *_shop;							//������ �����մϴ�

	int _itemNum;							//���õ� ������ �ѹ��� ��Ÿ���ϴ�
	int _itemBottomNum;						//���� �Ʒ��� ��ġ�� ������ ��ȣ�� ��Ÿ���ϴ�
	int _itemMaxNum;						//������ �ִ밹���� ��Ÿ���ϴ�

	RECT _itemInvenRc[3][12];				//�κ�â�� ��ġ�� ��Ʈ�� ��Ÿ���ϴ�
	RECT _itemShopRc[4];					//���� ��ġ�� ��Ʈ�� ��Ÿ���ϴ�


	int _infoItemX, _infoItemY, _infoShopItem;			//���õ� �������� �����ֱ� ���� �ӽ� �����Դϴ�

public:
	ui_shop();
	~ui_shop();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void selectItem();					//� �����ۿ� ���콺�� �ö��ִ��� �Ǻ��ϴ� �Լ��Դϴ�
	void wheelButtonMove();
};

