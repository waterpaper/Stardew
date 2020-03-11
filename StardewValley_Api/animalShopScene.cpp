#include "stdafx.h"
#include "animalShopScene.h"


animalShopScene::animalShopScene()
{
}


animalShopScene::~animalShopScene()
{
}

HRESULT animalShopScene::init()
{
	POINT pTemp;
	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();
	_ingameName = INGAMESCENE_NAME_ANIMALSHOP;

	sceneLoading("map/animalShop.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(816, 854, 96, 20);
	addMoveRc(696, 432, 240, 48);
	return S_OK;
}

void animalShopScene::update()
{
	scene::update();

	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();
	RECT playerRcTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();

	switch (selectRc(POINT{ (long)playerStateTemp.getPlayerPositionX(), (long)playerStateTemp.getPlayerPositionY() }))
	{
	case ANIMALSHOPSCENE_MOVE_ANIMALSHOP:
		UIMANAGER->setIsShop(true);
		UIMANAGER->changeUi("UI_animalshop");
		break;
	case ANIMALSHOPSCENE_MOVE_NULL:
	default:
		break;
	}

	switch (collisionRc(playerRcTemp))
	{
	case ANIMALSHOPSCENE_MOVE_TOWN:
		PLAYERMANAGER->setPlayerPosition(456, 1392);
		SCENEMANAGER->changeScene("townScene");
		break;
	case ANIMALSHOPSCENE_MOVE_NULL:
	default:
		break;
	}
}

void animalShopScene::release()
{
	scene::release();
}

void animalShopScene::render()
{
	scene::render();
}
