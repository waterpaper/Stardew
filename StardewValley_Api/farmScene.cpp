#include "stdafx.h"
#include "farmScene.h"


farmScene::farmScene()
{
}


farmScene::~farmScene()
{
}

HRESULT farmScene::init()
{
	POINT pTemp;

	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_FARM;
	SCENEMANAGER->setIngameName(_ingameName);

	sceneLoading("map/farm.map", _ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(4152, 624, 48, 96);
	addMoveRc(2856, 672, 48, 96);
	addMoveRc(1944, 720, 48, 96);
	addMoveRc(4790, 880, 20, 336);
	return S_OK;
}

void farmScene::update()
{
	scene::update();

	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();

	switch (selectRc(POINT{ (long)playerStateTemp.getPlayerPositionX(), (long)playerStateTemp.getPlayerPositionY() }))
	{
	case FARMSCENE_MOVE_HOME:
		PLAYERMANAGER->setPlayerPosition(456, 864);
		FARMMANAGER->setFarmMap(TILEMAPMANAGER->getTileMap());
		SCENEMANAGER->changeScene("homeScene");
		break;
	case FARMSCENE_MOVE_COOP:
		PLAYERMANAGER->setPlayerPosition(384, 768);
		FARMMANAGER->setFarmMap(TILEMAPMANAGER->getTileMap());
		SCENEMANAGER->changeScene("coopScene");
		break;
	case FARMSCENE_MOVE_BARN:
		PLAYERMANAGER->setPlayerPosition(408, 960);
		FARMMANAGER->setFarmMap(TILEMAPMANAGER->getTileMap());
		SCENEMANAGER->changeScene("barnScene");
		break;
	case FARMSCENE_MOVE_NULL:
	default:
		break;
	}

	switch (collisionRc(playerStateTemp.getPlayerRc()))
	{
	case FARMSCENE_MOVE_HOMETOTOWNROAD:
		PLAYERMANAGER->setPlayerPosition(68, 720);
		FARMMANAGER->setFarmMap(TILEMAPMANAGER->getTileMap());
		SCENEMANAGER->changeScene("homeToTownRoadScene");
		break;
	case FARMSCENE_MOVE_NULL:
	default:
		break;
	}
}

void farmScene::release()
{
	scene::release();
}

void farmScene::render()
{
	scene::render();
}
