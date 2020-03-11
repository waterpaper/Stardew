#include "stdafx.h"
#include "barnScene.h"


barnScene::barnScene()
{
}


barnScene::~barnScene()
{
}

HRESULT barnScene::init()
{
	POINT pTemp;

	_sceneName = SCENE_NAME_INGAME_SCENE;
	scene::init();

	_ingameName = INGAMESCENE_NAME_BARN;

	sceneLoading("map/barn.map",_ingameName);
	SCENEMANAGER->setIngameName(_ingameName);
	pTemp = TILEMAPMANAGER->getTileMapSize();
	_currentMapX = pTemp.x;
	_currentMapY = pTemp.y;

	CAMERAMANAGER->cameraMove(PLAYERMANAGER->getPlayerState().getPlayerPositionX(), PLAYERMANAGER->getPlayerState().getPlayerPositionY());

	addMoveRc(408, 1046, 144, 20);

	return S_OK;
}

void barnScene::update()
{
	scene::update();

	playerState playerStateTemp = PLAYERMANAGER->getPlayerState();
	ANIMALMANAGER->update();
	switch (collisionRc(playerStateTemp.getPlayerRc()))
	{
	case BARNSCENE_MOVE_FARM:
		PLAYERMANAGER->setPlayerPosition(1944, 816);
		SCENEMANAGER->changeScene("farmScene");
		break;
	case BARNSCENE_MOVE_NULL:
	default:
		break;
	}
}

void barnScene::release()
{
	scene::release();
}

void barnScene::render()
{
	scene::render();
}
