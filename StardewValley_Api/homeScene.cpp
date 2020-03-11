#include "stdafx.h"
#include "homeScene.h"


homeScene::homeScene()
{
}


homeScene::~homeScene()
{
}

HRESULT homeScene::init()
{
	POINT pTemp;

	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_HOME;

	sceneLoading("map/house.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(408,950,144,20);
	addMoveRc(720, 768, 48, 48);

	return S_OK;
}

void homeScene::update()
{
	scene::update();

	RECT playerRcTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();

	switch (collisionRc(playerRcTemp))
	{
	case HOMESCENE_MOVE_FARM:
		PLAYERMANAGER->setPlayerPosition(4176,720);
		SCENEMANAGER->changeScene("farmScene");
		break;
	case HOMESCENE_MOVE_SAVE:
		PLAYERMANAGER->setPlayerPosition(656, 768);
		UIMANAGER->changeUi("UI_save");
		break;
	case HOMESCENE_MOVE_NULL:
	default:
		break;
	}
}

void homeScene::release()
{
	scene::release();
}

void homeScene::render()
{
	scene::render();
}
