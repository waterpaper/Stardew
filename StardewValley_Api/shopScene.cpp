#include "stdafx.h"
#include "shopScene.h"


shopScene::shopScene()
{
}


shopScene::~shopScene()
{
}

HRESULT shopScene::init()
{
	POINT pTemp;
	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();
	_ingameName = INGAMESCENE_NAME_SHOP;

	sceneLoading("map/shop.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());
	_inventoryNum = INVENTORYMANAGER->getInventory().getInventoryLevel();

	if (_inventoryNum == 1)
	{
		_bag = IMAGEMANAGER->findImage("상점UI_가방1");
	}
	else if (_inventoryNum = 2)
	{
		_bag = IMAGEMANAGER->findImage("상점UI_가방2");
	}
	else
	{
		_bag = nullptr;
	}

	addMoveRc(432, 1190, 96, 20);
	addMoveRc(336, 432, 96, 96);
	addMoveRc(504, 432, 48, 96);

	return S_OK;
}

void shopScene::update()
{
	scene::update();
	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();
	RECT playerRcTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();

	if (_inventoryNum != INVENTORYMANAGER->getInventory().getInventoryLevel())
	{
 		_inventoryNum = INVENTORYMANAGER->getInventory().getInventoryLevel();

		if (_inventoryNum == 1)
		{
			_bag = IMAGEMANAGER->findImage("상점UI_가방1");
		}
		else if (_inventoryNum == 2)
		{
			_bag = IMAGEMANAGER->findImage("상점UI_가방2");
		}
		else
		{
			_bag = nullptr;

		}
	}

	switch (selectRc(POINT{ (long)playerStateTemp.getPlayerPositionX(), (long)playerStateTemp.getPlayerPositionY() }))
	{
	case SHOPSCENE_MOVE_SHOP:
		UIMANAGER->setIsShop(true);
		UIMANAGER->changeUi("UI_shop");
		break;
	case SHOPSCENE_MOVE_BAG:
		if (_inventoryNum == 1 || _inventoryNum == 2)
		{
			UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_INVENTORYEXPAND);
			UIMANAGER->changeUi("UI_selectDialog");
		}
		break;
	case SHOPSCENE_MOVE_NULL:
	default:
		break;
	}
	switch (collisionRc(playerRcTemp))
	{
	case SHOPSCENE_MOVE_TOWN:
		PLAYERMANAGER->setPlayerPosition(1728, 1248);
		SCENEMANAGER->changeScene("townScene");
		break;
	case SHOPSCENE_MOVE_NULL:
	default:
		break;
	}
}

void shopScene::release()
{
	scene::release();
}

void shopScene::render()
{
	image *imgTemp = IMAGEMANAGER->findImage("totalBuffer");
	POINT camera = CAMERAMANAGER->getCameraPos();

	scene::render();

	if (!UIMANAGER->getIsConversation() && !UIMANAGER->getIsShop() && !UIMANAGER->getIsMenu())
	{
		if (_bag != nullptr)
		{
			_bag->render(imgTemp->getMemDC(), 480, 386);
			BitBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, imgTemp->getMemDC(), camera.x, camera.y, SRCCOPY);
			UIMANAGER->render(getMemDC());
		}
	}
}
