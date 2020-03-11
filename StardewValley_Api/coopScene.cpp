#include "stdafx.h"
#include "coopScene.h"


coopScene::coopScene()
{
}


coopScene::~coopScene()
{
}

HRESULT coopScene::init()
{
	POINT pTemp;

	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_COOP;

	sceneLoading("map/coop.map", _ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(384, 854, 94, 20);

	return S_OK;
}

void coopScene::update()
{
	scene::update();

	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();
	ANIMALMANAGER->update();
	switch (collisionRc(playerStateTemp.getPlayerRc()))
	{
	case COOPSCENE_MOVE_FARM:
		PLAYERMANAGER->setPlayerPosition(2856, 720);
		SCENEMANAGER->changeScene("farmScene");
		break;
	case COOPSCENE_MOVE_NULL:
	default:
		break;
	}
}

void coopScene::release()
{
	scene::release();
}

void coopScene::render()
{
	scene::render();
}
