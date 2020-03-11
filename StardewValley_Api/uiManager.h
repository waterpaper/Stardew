#pragma once
#include "singletonBase.h"
#include "ui.h"
#include "all_Ui.h"

struct addItemUi
{
	image *itemImg;
	int frameX;
	int frameY;
	string name;
	int startTime;
};

class uiManager : public singletonBase<uiManager>
{
private:
	typedef map<string, ui*> mUiList;
	typedef map<string, ui*>::iterator miUiList;

private:
	//���� ui
	ui* _currentUi;
	//ui ���
	mUiList _mUiList;
	image *_uiImage;
	int _selectItem;
	UI_SELECTDIALOGKIND _selectDialogKind;
	ANIMAL_KIND _selectAnimalKind;

	vector<addItemUi> _vAddItemUi;

	bool _isMenu;
	bool _isShop;
	bool _isConversation;
	long _menuTime;

	bool _isFullInventoryUi;
	bool _isNotMoneyInventoryUi;
	int _time;

public:
	uiManager();
	~uiManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//���߰��ϱ�
	ui* addUi(string sceneName, ui* ui);

	//������(���������)
	HRESULT changeUi(string sceneName);

	bool getIsMenu() { return _isMenu; };
	void setIsMenu(bool menu) { _isMenu = menu; };

	bool getIsShop() { return _isShop; };
	void setIsShop(bool shop) { _isShop = shop; };

	bool getIsConversation() { return _isConversation; };
	void setIsConversation(bool conversation) { _isConversation = conversation; };

	int getSelectItem() { return _selectItem; };
	void setSelectItem(int num) { _selectItem = num; };

	UI_SELECTDIALOGKIND getSelectDialogKind() { return _selectDialogKind; };
	void setSelectDialogKind(UI_SELECTDIALOGKIND selectDialogKind) { _selectDialogKind = selectDialogKind; };

	ANIMAL_KIND getSelectAnimalKind() { return _selectAnimalKind; };
	void setSelectAnimalkind(ANIMAL_KIND kind) { _selectAnimalKind= kind; };

	void addAddItemUi(item item);
	void updateAddItemUi();
	void renderAddItemUi(HDC hdc);
	
	void setFullInventory() { _vAddItemUi.clear(),_time = GetTickCount(), _isFullInventoryUi = true; };
	void setNotMoney() { _vAddItemUi.clear(),_time = GetTickCount(), _isNotMoneyInventoryUi = true; }

	//���� ���õ� �������� ��ȣ�� ��ȯ�Ѵ�
	virtual int getKindNum();
};

