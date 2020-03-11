#include "stdafx.h"
#include "homeToTownRoadScene.h"


homeToTownRoadScene::homeToTownRoadScene()
{
}


homeToTownRoadScene::~homeToTownRoadScene()
{
}

HRESULT homeToTownRoadScene::init()
{
	POINT pTemp;
	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_HOMETOTOWN;

	sceneLoading("map/homeToTown.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(0, 720, 20, 336);
	addMoveRc(1526, 720, 20, 336);

	return S_OK;
}

void homeToTownRoadScene::update()
{
	scene::update();

	RECT playerRcTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();

	switch (collisionRc(playerRcTemp))
	{
	case HOMETOTOWNROADSCENE_MOVE_FARM:
		PLAYERMANAGER->setPlayerPosition(4700, 864);
		SCENEMANAGER->changeScene("farmScene");
		_sound.soundOff();
		_sound.soundPlay("³óÀå");
		break;
	case HOMETOTOWNROADSCENE_MOVE_TOWN:
		PLAYERMANAGER->setPlayerPosition(64, 864);
		SCENEMANAGER->changeScene("townScene");
		_sound.soundOff();
		_sound.soundPlay("¸¶À»");
		break;
	case HOMETOTOWNROADSCENE_MOVE_NULL:
	default:
		break;
	}
}

void homeToTownRoadScene::release()
{
	scene::release();
}

void homeToTownRoadScene::render()
{
	scene::render();
}
