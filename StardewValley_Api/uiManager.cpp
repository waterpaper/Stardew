#include "stdafx.h"
#include "uiManager.h"


uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}

HRESULT uiManager::init()
{
	addUi("UI_general", new ui_general);
	addUi("UI_inventory", new ui_inventory);
	addUi("UI_feeling", new ui_feeling);
	addUi("UI_minimap", new ui_minimap);
	addUi("UI_making", new ui_making);
	addUi("UI_exit", new ui_exit);
	addUi("UI_shop", new ui_shop);
	addUi("UI_conversation", new ui_conversation);
	addUi("UI_selectDialog", new ui_selectDialog);
	addUi("UI_animalshop", new ui_animalshop);
	addUi("UI_save", new ui_save);


	changeUi("UI_general");
	_isConversation = false;

	_selectItem = 0;
	_selectDialogKind = UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_NULL;
	_isFullInventoryUi = false;
	_isNotMoneyInventoryUi = false;
	_time = 0;

	return S_OK;
}

void uiManager::release()
{
	if (_currentUi) _currentUi->release();
}

void uiManager::update()
{
	updateAddItemUi();

	if (_isFullInventoryUi || _isNotMoneyInventoryUi)
	{
		if (GetTickCount() - _time > 3000)
		{
			_isFullInventoryUi = false;
			_isNotMoneyInventoryUi = false;
			_time = 0;
		}
	}

	if (_currentUi) _currentUi->update();

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_isMenu = !_isMenu;
		if (_isMenu)
		{
			_sound.effSoundPlay("메뉴오픈");
			_menuTime = GetTickCount();
			changeUi("UI_inventory");
			_isShop = false;
		}
		else
		{
			_sound.effSoundPlay("메뉴닫기");
			GAMETIMEMANAGER->addMenuTime(GetTickCount() - _menuTime);
			changeUi("UI_general");
		}
	}
}

void uiManager::render(HDC hdc)
{
	if (!_isFullInventoryUi && !_isNotMoneyInventoryUi)
	{
		renderAddItemUi(hdc);
	}
	else if (_isFullInventoryUi)
	{
		IMAGEMANAGER->render("UI_인벤토리풀",hdc, 50, 620);
	}
	else if (_isNotMoneyInventoryUi)
	{
		IMAGEMANAGER->render("UI_돈없음", hdc ,50, 620);
	}

	if (_currentUi)_currentUi->render(hdc);
}

ui * uiManager::addUi(string sceneName, ui *ui)
{
	if (!ui) return nullptr;

	_mUiList.insert(make_pair(sceneName, ui));

	return nullptr;
}

HRESULT uiManager::changeUi(string sceneName)
{
	miUiList find = _mUiList.find(sceneName);

	//못찾으면 E_FAIL
	if (find == _mUiList.end())return E_FAIL;

	//바꾸려는 ui가 현재ui과 같아도 E_FAIL
	if (find->second == _currentUi)return E_FAIL;

	//여기까지 왔다는건 문제가 없다. 즉 ui를 초기화 하고 변경해라.
	if (SUCCEEDED(find->second->init()))
	{
		//혹시 기존에 ui가 있다면 릴리즈
		if (_currentUi)_currentUi->release();
		_currentUi = find->second;
		return S_OK;
	}
	return E_FAIL;
}

void uiManager::addAddItemUi(item item)
{
	addItemUi temp;
	temp.itemImg = item.getItemImg();
	temp.frameX = item.getItemImageFrame().x;
	temp.frameY = item.getItemImageFrame().y;
	temp.name = item.getItemName();

	temp.startTime = GetTickCount();
	for (int i = 0; i < _vAddItemUi.size(); i++)
	{
		if (_vAddItemUi[i].name.compare(temp.name) == 0)
		{
			_vAddItemUi[i].startTime = temp.startTime;
			return;
			break;
		}
	}
	_vAddItemUi.push_back(temp);
}

void uiManager::updateAddItemUi()
{
	int time = GetTickCount();

	for (int i = 0; i < _vAddItemUi.size(); i++)
	{
		if (time - _vAddItemUi[i].startTime > 3000)
		{
			_vAddItemUi.erase(_vAddItemUi.begin() + i);
			break;
		}
	}
}

void uiManager::renderAddItemUi(HDC hdc)
{
	int x, y;
	char strTemp[256];

	for (int i = 0; i < _vAddItemUi.size(); i++)
	{
		x = 50;
		y = 620 - (_vAddItemUi.size() - i) * 100;

		IMAGEMANAGER->render("UI_아이템입수", hdc, x, y);
		_vAddItemUi[i].itemImg->frameRender(hdc, x + 20, y + 20, _vAddItemUi[i].frameX, _vAddItemUi[i].frameY);

		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(183, 89, 20));

		sprintf(strTemp, "%s", _vAddItemUi[i].name.c_str());
		TextOut(hdc, x + 100, y + 32, strTemp, strlen(strTemp));					//아이템 이름
	}
}

int uiManager::getKindNum()
{
	if (_currentUi) return _currentUi->getKindNum();
}
