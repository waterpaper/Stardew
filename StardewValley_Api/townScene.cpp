#include "stdafx.h"
#include "townScene.h"


townScene::townScene()
{
}


townScene::~townScene()
{
}

HRESULT townScene::init()
{
	POINT pTemp;
	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_TOWN;
	sceneLoading("map/town.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(1728, 1152, 96, 96);
	addMoveRc(456, 1344, 48, 96);

	addMoveRc(0, 878, 20, 240);
	return S_OK;
}

void townScene::update()
{
	scene::update();
	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();
	RECT playerRcTemp = playerStateTemp.getPlayerRc();

	switch (selectRc(POINT{ (long)playerStateTemp.getPlayerPositionX(), (long)playerStateTemp.getPlayerPositionY() }))
	{
	case TOWNSCENE_MOVE_SHOP:
		PLAYERMANAGER->setPlayerPosition(432, 1120);
		SCENEMANAGER->changeScene("shopScene");
		break;
	case TOWNSCENE_MOVE_ANIMALSHOP:
		PLAYERMANAGER->setPlayerPosition(816, 768);
		SCENEMANAGER->changeScene("animalShopScene");
		break;
	case TOWNSCENE_MOVE_NULL:
	default:
		break;
	}
	switch (collisionRc(playerRcTemp))
	{
	case TOWNSCENE_MOVE_HOMETOTOWN:
		PLAYERMANAGER->setPlayerPosition(1462, 768);
		SCENEMANAGER->changeScene("homeToTownRoadScene");
		break;
	case TOWNSCENE_MOVE_NULL:
	default:
		break;
	}
}

void townScene::release()
{
	scene::release();
}

void townScene::render()
{
	scene::render();
}
