#include "stdafx.h"
#include "cameraManger.h"


cameraManger::cameraManger()
{
}


cameraManger::~cameraManger()
{
}

HRESULT cameraManger::init()
{
	_camera.x = 0;
	_camera.y = 0;

	_totalBuffer = IMAGEMANAGER->addImage("totalBuffer", 32 * TILE_SIZE_X, 32 * TILE_SIZE_Y);
	
	_isBottomCamera = true;

	return S_OK;
}

void cameraManger::render(HDC hdc, bool isMapTool, vector<RECT> moveRect)
{
	PatBlt(_totalBuffer->getMemDC(), _camera.x, _camera.y, _camera.x + WINSIZEX, _camera.y + WINSIZEY, WHITENESS);

	if (isMapTool)
	{
		TILEMAPMANAGER->render(_totalBuffer->getMemDC());
	}
	else
	{
		TILEMAPMANAGER->render(_totalBuffer->getMemDC());

		if (_isDebug)
		{
			for (int i = 0; i < moveRect.size(); i++)
			{
				Rectangle(_totalBuffer->getMemDC(), moveRect[i].left, moveRect[i].top, moveRect[i].right, moveRect[i].bottom);
			}
		}

		EFFECTMANAGER->render(_totalBuffer->getMemDC());
		ITEMMANAGER->render(_totalBuffer->getMemDC());
		ANIMALMANAGER->render(_totalBuffer->getMemDC());
		NPCMANAGER->render(_totalBuffer->getMemDC());
		PLAYERMANAGER->render(_totalBuffer->getMemDC());
		NPCMANAGER->reRender(_totalBuffer->getMemDC(),PLAYERMANAGER->getPlayerState().getPlayerCollisionRc());
		TILEMAPMANAGER->reDrawTileMap_tileNpc(_totalBuffer->getMemDC());
		TILEMAPMANAGER->reDrawMoveRender(_totalBuffer->getMemDC());
		
	}

	BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, _totalBuffer->getMemDC(), _camera.x, _camera.y, SRCCOPY);
}

void cameraManger::release()
{

}

void cameraManger::cameraMove(int positionX, int positionY)
{
	/*
	ī�޶� ��ġ�� �̵����ִ� �Լ��Դϴ�
	ī�޶�� �����¿� ���ʿ����� �̵����� �����Ƿ� ����ó���� ���� ī�޶� ������Ű��
	��������� ���� ĳ������ġ�� ���� �̵��ϰ� �����մϴ�
	*/
	POINT mapSizeTemp;																						//���� �� ������

	mapSizeTemp = TILEMAPMANAGER->getTileMapSize();


	if (WINSIZEX / 2 > positionX || WINSIZEX > mapSizeTemp.x*TILE_SIZE_X)
	{
		//���� ���Ͻ� (�Ǵ� ���� ȭ�麸�� ������)
		_camera.x = 0;
	}
	else
	{
		_camera.x = positionX - WINSIZEX / 2;

		//������ ���Ͻ�
		if (_camera.x > mapSizeTemp.x*(TILE_SIZE_X)-WINSIZEX)
		{
			_camera.x = mapSizeTemp.x * (TILE_SIZE_X)-WINSIZEX;
		}
	}

	if ((WINSIZEY) / 2 > positionY || WINSIZEY > mapSizeTemp.y*TILE_SIZE_Y)
	{
		//���� ���Ͻ� (�Ǵ� ���� ȭ�麸�� ������)
		_camera.y = 0;
		_isBottomCamera = true;
	}
	else
	{
		_camera.y = positionY - WINSIZEY / 2;

		//�Ʒ��� ���Ͻ�
		if (_camera.y > mapSizeTemp.y *(TILE_SIZE_Y)-WINSIZEY)
		{
			_camera.y = mapSizeTemp.y * (TILE_SIZE_Y)-WINSIZEY;
			_isBottomCamera = false;
		}
		else
		{
			_isBottomCamera = true;
		}
	}
}

void cameraManger::cameraAllTileRender(HDC hdc, int mapSizeX, int mapSizeY)
{
	IMAGEMANAGER->deleteImage("totalBuffer");
	_totalBuffer = IMAGEMANAGER->addImage("totalBuffer", mapSizeX*TILE_SIZE_X, mapSizeY*TILE_SIZE_Y);

	_camera.x = 0;
	_camera.y = 0;

	BitBlt(_totalBuffer->getMemDC(), 0, 0, mapSizeX*TILE_SIZE_X, mapSizeY*TILE_SIZE_Y, hdc, 0, 0, SRCCOPY);
}

void cameraManger::minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY)
{
	/*
	�̴ϸʹ��ۿ� �׷��� �̴ϸ��� render�մϴ�
	*/

	_totalMinimapBuffer->render(hdc, posX, posY, 0, 0, minimapSizeX, minimapSizeY);
}

void cameraManger::setMinimapSize(POINT mapSize)
{
	//�̴ϸ��� ����� �ٲٰ� �ٽ� �׷��ݴϴ�
	IMAGEMANAGER->deleteImage("totalMinimapBuffer");
	_totalMinimapBuffer = IMAGEMANAGER->addImage("totalMinimapBuffer", mapSize.x, mapSize.y);
	image *_mapBuffer = IMAGEMANAGER->findImage("mapBuffer");

	int _minimapX = mapSize.x;
	int _minimapY = mapSize.y;

	POINT tileSizeTemp = TILEMAPMANAGER->getTileMapSize();

	_mapBuffer->render(_totalBuffer->getMemDC(),0,0);
	EFFECTMANAGER->render(_totalBuffer->getMemDC());
	ITEMMANAGER->render(_totalBuffer->getMemDC());
	ANIMALMANAGER->render(_totalBuffer->getMemDC());
	NPCMANAGER->render(_totalBuffer->getMemDC());
	PLAYERMANAGER->render(_totalBuffer->getMemDC());
	TILEMAPMANAGER->reDrawMoveRender(_totalBuffer->getMemDC());

	_totalMinimapBuffer->minimapRender(_totalMinimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _totalBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));

	_mapBuffer = nullptr;
}


