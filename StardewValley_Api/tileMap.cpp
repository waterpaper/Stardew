#include "stdafx.h"
#include "tileMap.h"


tileMap::tileMap()
{
	init();
}


tileMap::~tileMap()
{
}

HRESULT tileMap::init()
{
	//tileMap Ŭ������ �ʱ�ȭ�մϴ�

	_maxTileX = 32;
	_maxTileY = 32;

	_isTileMapImage = false;
	setTileMap(_maxTileX, _maxTileY);

	red = CreateSolidBrush(RGB(255, 0, 0));
	blue = CreateSolidBrush(RGB(0, 0, 255));
	green = CreateSolidBrush(RGB(0, 255, 0));
	white = CreateSolidBrush(RGB(255, 255, 255));

	return S_OK;
}

void tileMap::update()
{

}


void tileMap::release()
{
	if (SUBWIN->GetCTRL() != CTRL_LOAD)
	{
		_tileMapImage = nullptr;
		_isTileMapImage = false;
		_tileMapImagePath.clear();
	}

	if (_tileMap != nullptr)
	{
		/*
		�޸𸮸� �����մϴ�
		*/
		for (int i = 0; i < _maxTileY; i++)
		{
			free(_tileMap[i]);
		}
		free(_tileMap);

		/*
		�޸𸮸��� �ذ��ϱ� ���� ��Ҹ��� delete
		�� ���� capacity�� �ʱ�ȭ�Ѵ�
		*/
		for (_iTileObject = _tileObject.begin(); _iTileObject != _tileObject.end(); ++_iTileObject)
		{
			SAFE_DELETE(*_iTileObject);
		}
		_tileObject.clear();
		_tileObject.shrink_to_fit();
	}
}

void tileMap::setTileMap(int tileSizeX, int tileSizeY)
{
	/*
	Ÿ�ϸ��� ������ �迭�� �ʱ�ȭ�մϴ�
	*/
	release();

	_maxTileX = tileSizeX;
	_maxTileY = tileSizeY;

	//�����迭
	_tileMap = (TagTile_TERRAIN**)malloc(sizeof(TagTile_TERRAIN*) * _maxTileY);
	for (int i = 0; i < _maxTileY; i++) {
		_tileMap[i] = (TagTile_TERRAIN*)malloc(sizeof(TagTile_TERRAIN) * _maxTileX);
	}

	//�ʱ�ȭ
	for (int i = 0; i < _maxTileY; i++)
	{
		for (int j = 0; j < _maxTileX; j++)
		{
			_tileMap[i][j].tileNum = 0;
			_tileMap[i][j].isTerrain = false;
			_tileMap[i][j].isObject = false;
			_tileMap[i][j].isShader = false;
			for (int n = 0; n < TILE_NUM_MAX; n++)
			{
				_tileMap[i][j].tileFrame[n] = POINT{ -1,-1 };
				_tileMap[i][j].tileTerrainImg[n] = nullptr;
				_tileMap[i][j].imageIndex[n] = -1;
			}
			_tileMap[i][j].tilePos = POINT{ j*TILE_SIZE_X,i*TILE_SIZE_Y };
			_tileMap[i][j].tile_terrainKind = TILE_TERRAINKIND_NULL;
			_tileMap[i][j].tileRc = RectMake(j*TILE_SIZE_X, i*TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
		}
	}
}

void tileMap::addTileMapIamge(char * imageName)
{
	_isTileMapImage = true;
	_tileMapImagePath = imageName;
	_tileMapImage = IMAGEMANAGER->findImage(_tileMapImagePath);
}

void tileMap::deleteTileMapImage()
{
	_isTileMapImage = false;
	_tileMapImage = nullptr;
}

void tileMap::setTile(TagTile_TERRAIN btileMap, int x, int y, int num)
{
	//Ÿ�ϸ��� Ÿ�� �����մϴ�
	if (_tileMap[y][x].tileNum < btileMap.tileNum || btileMap.tileNum == -1)
	{
		_tileMap[y][x].tileNum = btileMap.tileNum;
	}
	_tileMap[y][x].tileTerrainImg[num] = btileMap.tileTerrainImg[num];
	_tileMap[y][x].imageIndex[num] = btileMap.imageIndex[num];
	_tileMap[y][x].isTerrain = btileMap.isTerrain;
	_tileMap[y][x].isObject = btileMap.isObject;
	_tileMap[y][x].tileFrame[num] = btileMap.tileFrame[num];
	_tileMap[y][x].tile_terrainKind = kindSelectTerrain(btileMap.imageIndex[num], btileMap.tileFrame[num].x, btileMap.tileFrame[num].y);

}

void tileMap::addObject(TagTile_Object *tileObject)
{
	/*
	Ÿ�ϸʿ� ������Ʈ�� �߰��մϴ�
	*/
	RECT tempRc, collision;

	kindSelectObject(tileObject, tileObject->imageIndex);

	//��ü Ÿ�ϸ��� �Ѿ�� ���
	if (tileObject->objectPos.x + tileObject->sizeX > _maxTileX ||
		tileObject->objectPos.y + tileObject->sizeY > _maxTileY) return;

	//��ġ�� ������Ʈ�� �ִ� ���
	for (int i = 0; i < _tileObject.size(); i++)
	{
		collision = _tileObject[i]->objectTotalRc;

		if (IntersectRect(&tempRc, &collision, &tileObject->objectTotalRc))
		{
			return;
		}
	}

	_tileObject.push_back(tileObject);

	for (int i = tileObject->objectPos.y; i < tileObject->objectPos.y + tileObject->sizeY; i++)
	{
		for (int j = tileObject->objectPos.x; j < tileObject->objectPos.x + tileObject->sizeX; j++)
		{
			_tileMap[i][j].isShader = true;
		}
	}
	for (int i = tileObject->objectCollisionRc.top / (TILE_SIZE_Y); i < tileObject->objectCollisionRc.bottom / (TILE_SIZE_Y); i++)
	{
		for (int j = tileObject->objectCollisionRc.left / (TILE_SIZE_X); j < tileObject->objectCollisionRc.right / (TILE_SIZE_X); j++)
		{
			_tileMap[i][j].isObject = true;
		}
	}
}

void tileMap::deleteObject(HDC hdc, int num)
{
	/*
	Ÿ�ϸʿ� Ư�� ������Ʈ�� �����մϴ�
	*/
	int x = _tileObject[num]->objectPos.x;
	int y = _tileObject[num]->objectPos.y;
	int sizeX = _tileObject[num]->sizeX;
	int sizeY = _tileObject[num]->sizeY;

	for (int i = _tileObject[num]->objectPos.y; i < _tileObject[num]->objectPos.y + _tileObject[num]->sizeY; i++)
	{
		for (int j = _tileObject[num]->objectPos.x; j < _tileObject[num]->objectPos.x + _tileObject[num]->sizeX; j++)
		{
			_tileMap[i][j].isObject = false;
			_tileMap[i][j].isShader = false;
		}
	}

	SAFE_DELETE(*(_tileObject.begin() + num));
	_tileObject.erase(_tileObject.begin() + num);

	reDrawTileMap(hdc, x, y, sizeX, sizeY, true);

}

void tileMap::clearObject()
{
	for (_iTileObject = _tileObject.begin(); _iTileObject != _tileObject.end(); ++_iTileObject)
	{
		SAFE_DELETE(*_iTileObject);
	}
	_tileObject.clear();
	_tileObject.shrink_to_fit();
}

void tileMap::screenRenderTileMap(HDC hdc, int cameraX, int cameraY)
{
	/*
	tileMap�� ȭ�� ũ�⿡ �°� �׷��ݴϴ�
	*/

	//�ӽú���
	char str[256];
	int sizeTempX, sizeTempY;
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();

	/*
	Ÿ�ϸ��� ����� �����ҽ� ����� ���� �׷��ݴϴ�
	���� ������ ������ ���� ���� ��츦 ���� �˻��ϰ� �ش� ȭ�� ũ�⸸ŭ �׷��ݴϴ�
	(������ ������� ������ �ش� ������ ��ŭ�� render �ؾ��ϱ� ����)
	*/

	//������ �˻�
	if (_maxTileX*TILE_SIZE_X >= WINSIZEX)
	{
		sizeTempX = _maxTileX * TILE_SIZE_X;
	}
	else
	{
		sizeTempX = WINSIZEX;
	}

	if (_maxTileY*TILE_SIZE_Y >= WINSIZEY)
	{
		sizeTempY = _maxTileY * TILE_SIZE_Y;
	}
	else
	{
		sizeTempY = WINSIZEY;
	}

	//�̹��� ���
	if (_isTileMapImage)
	{
		_tileMapImage->render(hdc, cameraX, cameraY, 0, 0, sizeTempX, sizeTempY);
	}

	/*
	Ÿ�ϸ��� Terrain�� ȭ�� ũ�⿡ �°� render�մϴ�
	ȭ�� ���� ���ʿ� ��ġ�� Ÿ�ϰ� ������ ��ġ�� Ÿ�Ϻ��� ���� ������ +1��ŭ�� Ÿ�ϱ��� �˻�, �׷��ݴϴ�
	*/
	for (int i = cameraY / (TILE_SIZE_Y); i < _maxTileY; i++)
	{
		//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ���� Ÿ���� �Ѿ�� �����մϴ�(ȭ�� ���� �������϶� ����ó�� ���� for�� �ƴ� �Ʒ����� ó��)
		if ((cameraY + WINSIZEY) / (TILE_SIZE_Y) <= i)
			break;

		for (int j = cameraX / (TILE_SIZE_X); j < _maxTileX; j++)
		{
			//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ���� Ÿ���� �Ѿ�� �����մϴ�(ȭ�� ���� �������϶� ����ó�� ���� for�� �ƴ� �Ʒ����� ó��)
			if ((cameraX + WINSIZEX) / (TILE_SIZE_X) <= j)
				break;

			if (!_tileMap[i][j].isTerrain)
			{
				continue;
			}

			terrainTemp = _tileMap[i][j];

			for (int n = 0; n < _tileMap[i][j].tileNum; n++)
			{
				if (_tileMap[i][j].imageIndex[n] == -1) continue;

				_tileMap[i][j].tileTerrainImg[n]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[n].x, terrainTemp.tileFrame[n].y);
			}

			if (sceneTemp == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
			{
				if (farmLandTemp[i][j].isHoeing == true)
				{
					farmLandTemp[i][j].img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top, farmLandTemp[i][j].frame.x, farmLandTemp[i][j].frame.y);

					if (farmLandTemp[i][j].isCrops)
					{
						farmLandTemp[i][j].crops.img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top - 48, farmLandTemp[i][j].crops.frame.x, farmLandTemp[i][j].crops.frame.y);
					}
				}
			}
		}
	}

	/*
	Ÿ�ϸ��� Object�� render�մϴ�
	Ÿ�ϸ��� terrain���� �ٸ� ���Ϳ��� �����ϱ� ������ ���� �׷��ݴϴ�
	ȭ�� ũ�⿡ �´� �κи� �����ϱ� ���� ī�޶� �̿��� �˻��մϴ�
	*/
	for (int i = 0; i < _tileObject.size(); i++)
	{
		objectTemp = _tileObject[i];

		if (objectTemp->objectPos.x*TILE_SIZE_X < cameraX
			|| objectTemp->objectPos.x*TILE_SIZE_X + objectTemp->sizeX *TILE_SIZE_X > cameraX + sizeTempX)
		{
			continue;
		}
		else if (objectTemp->objectPos.y*TILE_SIZE_Y < cameraY
			|| objectTemp->objectPos.y*TILE_SIZE_Y + objectTemp->sizeY *TILE_SIZE_Y > cameraY + sizeTempY)
		{
			continue;
		}

		if (objectTemp->tileObjectImg->getIsFrame())
		{
			objectTemp->tileObjectImg->frameRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, objectTemp->objectFrame.x, objectTemp->objectFrame.y);
		}
		else
		{
			objectTemp->tileObjectImg->render(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, 0, 0, objectTemp->sizeX*(TILE_SIZE_X), objectTemp->sizeY*(TILE_SIZE_Y));
		}
	}

	SAFE_DELETE(objectTemp);
}

void tileMap::reDrawTileMap(HDC hdc)
{
	/*
	�̵��� ���� �Ϻκи� �ٽñ׷��ִ� �Լ��Դϴ�
	Ÿ�� ����� ��ü���� ����� �Ѵ��� �˻��ϰ� �׷��ݴϴ�
	*/

	RECT rectTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();

	int startX, startY, endX, endY;
	startX = rectTemp.left / (TILE_SIZE_X);
	endX = rectTemp.right / (TILE_SIZE_X);
	startY = rectTemp.top / (TILE_SIZE_Y);
	endY = rectTemp.bottom / (TILE_SIZE_Y);

	//�ӽú���
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;


	//�ش� ��ġ�� terrain�� �ٽ� �׷��ݴϴ�
	for (int i = startY; i < endY+2; i++)
	{
		if (_maxTileY <= i)
			break;

		for (int j = startX; j < endX+1; j++)
		{
			if (_maxTileX <= j)
				break;

			terrainTemp = _tileMap[i][j];

			if (terrainTemp.tileTerrainImg == nullptr || !terrainTemp.isTerrain) break;

			if (i == endY)
			{
				if (!(_tileMap[i][j].imageIndex[1] == -1))
				_tileMap[i][j].tileTerrainImg[1]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[1].x, terrainTemp.tileFrame[1].y);
			}

			
			if (_tileMap[i][j].imageIndex[2] == -1) continue;
			_tileMap[i][j].tileTerrainImg[2]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[2].x, terrainTemp.tileFrame[2].y);
	

			if (sceneTemp == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
			{
				if (farmLandTemp[i][j].isHoeing == true)
				{
					farmLandTemp[i][j].img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top, farmLandTemp[i][j].frame.x, farmLandTemp[i][j].frame.y);

					if (farmLandTemp[i][j].isCrops)
					{
						farmLandTemp[i][j].crops.img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top - 48, farmLandTemp[i][j].crops.frame.x, farmLandTemp[i][j].crops.frame.y);
					}
				}
			}
		}
	}

	//�ش� ��ġ�� object�� �ٽ� �׷��ݴϴ�
	for (int i = 0; i < _tileObject.size(); i++)
	{
		objectTemp = _tileObject[i];

		if (objectTemp->objectPos.x > startX
			|| objectTemp->objectPos.x + objectTemp->sizeX < endX)
		{
			continue;
		}
		else if (objectTemp->objectPos.y > startY
			|| objectTemp->objectPos.y + objectTemp->sizeY < endY)
		{
			continue;
		}

		reDrawTileMap(hdc, objectTemp->objectPos.x, objectTemp->objectPos.y, objectTemp->sizeX, objectTemp->sizeY, false);
		PLAYERMANAGER->render(hdc);

		if (objectTemp->tileObjectImg->getIsFrame())
		{
			objectTemp->tileObjectImg->alphaFrameRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, objectTemp->objectFrame.x, objectTemp->objectFrame.y,(BYTE)100);
		}
		else
		{
			objectTemp->tileObjectImg->alphaRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, 0, 0, objectTemp->sizeX*(TILE_SIZE_X), objectTemp->sizeY*(TILE_SIZE_Y), (BYTE)100);
		}
	}
}

void tileMap::reDrawTileMap_tile(HDC hdc, RECT rc)
{
	//�ӽú���
	TagTile_TERRAIN terrainTemp;

	int startX, startY, endX, endY;
	startX = rc.left / (TILE_SIZE_X);
	endX = rc.right / (TILE_SIZE_X);
	startY = rc.top / (TILE_SIZE_Y);
	endY = rc.bottom / (TILE_SIZE_Y);

	//�ش� ��ġ�� terrain�� �ٽ� �׷��ݴϴ�
	for (int i = startY; i < endY + 2; i++)
	{
		if (_maxTileY <= i)
			break;

		for (int j = startX; j < endX + 1; j++)
		{
			if (_maxTileX <= j)
				break;

			terrainTemp = _tileMap[i][j];

			if (terrainTemp.tileTerrainImg == nullptr || !terrainTemp.isTerrain) break;

			if (i == endY)
			{
				if (!(_tileMap[i][j].imageIndex[1] == -1))
					_tileMap[i][j].tileTerrainImg[1]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[1].x, terrainTemp.tileFrame[1].y);
			}


			if (_tileMap[i][j].imageIndex[2] == -1) continue;
			_tileMap[i][j].tileTerrainImg[2]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[2].x, terrainTemp.tileFrame[2].y);
		}
	}
}

void tileMap::reDrawTileMap(HDC hdc, int tileX, int tileY, int sizeX, int sizeY, bool isObject)
{
	/*
	���� �Ϻκи� �ٽñ׷��ִ� �Լ��Դϴ�
	Ÿ�� ����� ��ü���� ����� �Ѵ��� �˻��ϰ� �׷��ݴϴ�
	*/

	//�ӽú���
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	PatBlt(hdc, tileX*(TILE_SIZE_X), tileY*(TILE_SIZE_Y), sizeX*(TILE_SIZE_X), sizeY*(TILE_SIZE_Y), WHITENESS);

	//�ش� ��ġ�� terrain�� �ٽ� �׷��ݴϴ�
	for (int i = tileY; i < tileY + sizeY; i++)
	{
		if (_maxTileY <= i)
			break;

		for (int j = tileX; j < tileX + sizeX; j++)
		{
			if (_maxTileX <= j)
				break;

			terrainTemp = _tileMap[i][j];

			if (terrainTemp.tileTerrainImg == nullptr || !terrainTemp.isTerrain) break;

			for (int n = 0; n < _tileMap[i][j].tileNum; n++)
			{
				if (_tileMap[i][j].imageIndex[n] == -1) continue;

				_tileMap[i][j].tileTerrainImg[n]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[n].x, terrainTemp.tileFrame[n].y);
			}

			FARMMANAGER->render(hdc, j, i);
		}
	}

	if (isObject)
	{
		//�ش� ��ġ�� object�� �ٽ� �׷��ݴϴ�
		for (int i = 0; i < _tileObject.size(); i++)
		{
			objectTemp = _tileObject[i];

			if (objectTemp->objectPos.x < tileX
				|| objectTemp->objectPos.x + objectTemp->sizeX > _maxTileX)
			{
				continue;
			}
			else if (objectTemp->objectPos.y < tileY
				|| objectTemp->objectPos.y + objectTemp->sizeY > _maxTileY)
			{
				continue;
			}

			if (objectTemp->tileObjectImg->getIsFrame())
			{
				objectTemp->tileObjectImg->frameRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, objectTemp->objectFrame.x, objectTemp->objectFrame.y);
			}
			else
			{
				objectTemp->tileObjectImg->render(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, 0, 0, objectTemp->sizeX*(TILE_SIZE_X), objectTemp->sizeY*(TILE_SIZE_Y));
			}
		}
	}
}

void tileMap::allRenderTileMap(HDC hdc, int num)
{
	/*
	tileMap�� ��ü �׷��ݴϴ�(�̴ϸʰ� Ÿ���� ���⸦ ����)
	*/

	//�ӽú���
	char str[256];
	int sizeTempX, sizeTempY;
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();
	/*
	Ÿ�ϸ��� ����� �����ҽ� ����� ���� �׷��ݴϴ�
	���� ������ ������ ���� ���� ��츦 ���� �˻��ϰ� �ش� ȭ�� ũ�⸸ŭ �׷��ݴϴ�
	(������ ������� ������ �ش� ������ ��ŭ�� render �ؾ��ϱ� ����)
	*/

	//������ �˻�
	if (_maxTileX*TILE_SIZE_X >= WINSIZEX)
	{
		sizeTempX = _maxTileX * TILE_SIZE_X;
	}
	else
	{
		sizeTempX = WINSIZEX;
	}

	if (_maxTileY*TILE_SIZE_Y >= WINSIZEY)
	{
		sizeTempY = _maxTileY * TILE_SIZE_Y;
	}
	else
	{
		sizeTempY = WINSIZEY;
	}

	//�̹��� ���
	if (_isTileMapImage)
	{
		_tileMapImage->render(hdc, 0, 0);
	}

	/*
	Ÿ�ϸ��� Terrain�� ũ�⿡ �°� render�մϴ�
	*/
	for (int i = 0; i < _maxTileY; i++)
	{
		for (int j = 0; j < _maxTileX; j++)
		{
			if (!_tileMap[i][j].isTerrain)	continue;

			terrainTemp = _tileMap[i][j];

			if (num == 0)
			{
				for (int n = 0; n < _tileMap[i][j].tileNum; n++)
				{
					if (_tileMap[i][j].imageIndex[n] == -1) continue;

					_tileMap[i][j].tileTerrainImg[n]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[n].x, terrainTemp.tileFrame[n].y);

				}
			}
			else if (num == 1 || num == 2 || num == 3)
			{
				if (_tileMap[i][j].imageIndex[num - 1] == -1) continue;

				_tileMap[i][j].tileTerrainImg[num - 1]->frameRender(hdc, terrainTemp.tilePos.x, terrainTemp.tilePos.y, terrainTemp.tileFrame[num - 1].x, terrainTemp.tileFrame[num - 1].y);

			}

			if (sceneTemp == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
			{
				if (farmLandTemp[i][j].isHoeing == true)
				{
					farmLandTemp[i][j].img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top, farmLandTemp[i][j].frame.x, farmLandTemp[i][j].frame.y);

					if (farmLandTemp[i][j].isCrops)
					{
						farmLandTemp[i][j].crops.img->frameRender(hdc, farmLandTemp[i][j].rc.left, farmLandTemp[i][j].rc.top - 48, farmLandTemp[i][j].crops.frame.x, farmLandTemp[i][j].crops.frame.y);
					}
				}
			}
		}
	}
	if (num != 1 && num != 2 && num != 3)
	{
		/*
		Ÿ�ϸ��� Object�� render�մϴ�
		Ÿ�ϸ��� terrain���� �ٸ� ���Ϳ��� �����ϱ� ������ ���� �׷��ݴϴ�
		ȭ�� ũ�⿡ �´� �κи� �����ϱ� ���� ī�޶� �̿��� �˻��մϴ�
		*/
		for (int i = 0; i < _tileObject.size(); i++)
		{
			objectTemp = _tileObject[i];

			if (objectTemp->tileObjectImg->getIsFrame())
			{
				objectTemp->tileObjectImg->frameRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, objectTemp->objectFrame.x, objectTemp->objectFrame.y);
			}
			else
			{
				objectTemp->tileObjectImg->render(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, 0, 0, objectTemp->sizeX*(TILE_SIZE_X), objectTemp->sizeY*(TILE_SIZE_Y));
			}
		}
	}

	objectTemp = nullptr;
}

void tileMap::debugRenderTileMap(HDC hdc, int cameraX, int cameraY)
{
	/*
	����� ����Ͻ� Ÿ�� ��ȣ�� ��Ʈ�� �׷��ִ� �Լ��Դϴ�
	Ÿ�ϸ��� ȭ�� ũ�⿡ �°� render�մϴ�
	ȭ�� ���� ���ʿ� ��ġ�� Ÿ�ϰ� ������ ��ġ�� Ÿ�Ϻ��� ���� ������ +1��ŭ�� Ÿ�ϱ��� �˻�, �׷��ݴϴ�
	*/

	//�ӽú���
	char str[256];
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	if (_isDebug)
	{
		for (int i = cameraY / (TILE_SIZE_Y); i < _maxTileY; i++)
		{
			//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ���� Ÿ���� �Ѿ�� �����մϴ�(ȭ�� ���� �������϶� ����ó�� ���� for�� �ƴ� �Ʒ����� ó��)
			if ((cameraY + WINSIZEY) / (TILE_SIZE_Y)+1 < i)
				break;

			for (int j = cameraX / (TILE_SIZE_X); j < _maxTileX; j++)
			{
				//ȭ�鿡 ������ Ÿ�ϸ� �׷��ֱ� ���� Ÿ���� �Ѿ�� �����մϴ�(ȭ�� ���� �������϶� ����ó�� ���� for�� �ƴ� �Ʒ����� ó��)
				if ((cameraX + WINSIZEX) / (TILE_SIZE_X)+1 < j)
					break;

				terrainTemp = _tileMap[i][j];

				//�����
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(0, 0, 0));

				//�簢���� ��ǥ�� ����մϴ�
				LineMake(hdc, terrainTemp.tileRc.left, terrainTemp.tileRc.top, terrainTemp.tileRc.right, terrainTemp.tileRc.top);
				LineMake(hdc, terrainTemp.tileRc.left, terrainTemp.tileRc.top, terrainTemp.tileRc.left, terrainTemp.tileRc.bottom);
				LineMake(hdc, terrainTemp.tileRc.right, terrainTemp.tileRc.top, terrainTemp.tileRc.right, terrainTemp.tileRc.bottom);
				LineMake(hdc, terrainTemp.tileRc.left, terrainTemp.tileRc.bottom, terrainTemp.tileRc.right, terrainTemp.tileRc.bottom);
				sprintf_s(str, "(%d,%d)", j, i);
				TextOut(hdc, _tileMap[i][j].tileRc.left + 3, _tileMap[i][j].tileRc.top + 5, str, strlen(str));

			}
		}

		if (!_isAttribute)
		{
			for (int i = 0; i < _tileObject.size(); i++)
			{
				objectTemp = _tileObject[i];

				Rectangle(hdc, objectTemp->objectCollisionRc.left, objectTemp->objectCollisionRc.top, objectTemp->objectCollisionRc.right, objectTemp->objectCollisionRc.bottom);
				
				if (objectTemp->tileObjectImg->getIsFrame())
				{
					objectTemp->tileObjectImg->frameRender(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, objectTemp->objectFrame.x, objectTemp->objectFrame.y);
				}
				else
				{
					objectTemp->tileObjectImg->render(hdc, objectTemp->objectTotalRc.left, objectTemp->objectTotalRc.top, 0, 0, objectTemp->sizeX*(TILE_SIZE_X), objectTemp->sizeY*(TILE_SIZE_Y));
				}
			}
		}
	}

}

void tileMap::attributeRenderTileMap(HDC hdc)
{
	/*
	�Ӽ� ����Ͻ� Ÿ�� ��ȣ�� �Ӽ�Ÿ���� �׷��ִ� �Լ��Դϴ�
	Ÿ�ϸ��� �� ũ�⿡ �°� render�մϴ�
	*/

	//�ӽú���
	char str[256];
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	int sizeTempX, sizeTempY;

	//������ �˻�
	if (_maxTileX*TILE_SIZE_X >= WINSIZEX)
	{
		sizeTempX = _maxTileX * TILE_SIZE_X;
	}
	else
	{
		sizeTempX = WINSIZEX;
	}

	if (_maxTileY*TILE_SIZE_Y >= WINSIZEY)
	{
		sizeTempY = _maxTileY * TILE_SIZE_Y;
	}
	else
	{
		sizeTempY = WINSIZEY;
	}

	for (int i = 0; i < _maxTileY; i++)
	{
		for (int j = 0; j < _maxTileX; j++)
		{
			if (!_tileMap[i][j].isTerrain && !_tileMap[i][j].isObject)	continue;

			terrainTemp = _tileMap[i][j];
			attributeRenderRectSelect(hdc, terrainTemp);
		}
	}
}

void tileMap::attributeRenderTileMap(HDC hdc, int x, int y)
{
	TagTile_TERRAIN terrainTemp;

	if (!_tileMap[y][x].isTerrain && !_tileMap[y][x].isObject)	return;

	terrainTemp = _tileMap[y][x];
	attributeRenderRectSelect(hdc, terrainTemp);
}

void tileMap::attributeRenderRectSelect(HDC hdc, TagTile_TERRAIN tile)
{
	if (tile.isObject)
	{
		oBrush = (HBRUSH)SelectObject(hdc, blue);
		Rectangle(hdc, tile.tileRc.left, tile.tileRc.top, tile.tileRc.right, tile.tileRc.bottom);
		SelectObject(hdc, oBrush);
	}
	else if (tile.tile_terrainKind == TILE_TERRAINKIND_SOIL)
	{
		oBrush = (HBRUSH)SelectObject(hdc, green);
		Rectangle(hdc, tile.tileRc.left, tile.tileRc.top, tile.tileRc.right, tile.tileRc.bottom);
		SelectObject(hdc, oBrush);
	}
	else if (tile.tile_terrainKind == TILE_TERRAINKIND_NOTMOVE || tile.tile_terrainKind == TILE_TERRAINKIND_WALL)
	{
		oBrush = (HBRUSH)SelectObject(hdc, red);
		Rectangle(hdc, tile.tileRc.left, tile.tileRc.top, tile.tileRc.right, tile.tileRc.bottom);
		SelectObject(hdc, oBrush);
	}
	else if (tile.tile_terrainKind == TILE_TERRAINKIND_NULL)
	{
		PatBlt(hdc, tile.tilePos.x, tile.tilePos.y, tile.tileRc.right - tile.tileRc.left, tile.tileRc.bottom - tile.tileRc.top, WHITENESS);
	}
	else
	{
		oBrush = (HBRUSH)SelectObject(hdc, white);
		Rectangle(hdc, tile.tileRc.left, tile.tileRc.top, tile.tileRc.right, tile.tileRc.bottom);
		SelectObject(hdc, oBrush);
	}
}

TILE_TERRAINKIND tileMap::kindSelectTerrain(int index, int frameX, int frameY)
{
	if (index == 0)
	{
		if ((frameX == 3 && frameY == 0)|| (frameX == 1 && frameY == 1)|| (frameX == 3 && frameY == 1)|| (frameX == 6 && frameY == 2)|| (frameX == 7 && frameY == 2)
			|| (frameX == 1 && frameY == 3) || (frameX == 2 && frameY == 3)|| (frameX == 6 && frameY == 3))
		{
			return TILE_TERRAINKIND_SOIL;
		}

		return TILE_TERRAINKIND_GRASS;
	}
	if (index == 1)
	{
		return TILE_TERRAINKIND_NOTMOVE;
	}

	return TILE_TERRAINKIND_NORMAL;
}

void tileMap::kindSelectObject(TagTile_Object *object, int index)
{
	/*
	������Ʈ�� �Ӽ����� �����մϴ�
	���⼭ ���ǵ��� ���� ������Ʈ�� �׷����� �ʽ��ϴ�(ũ�Ⱑ ���⶧��)
	*/
	if (index == 0)
	{
		object->tile_objectKind = TILE_OBJECTKIND_GRASS;
		object->sizeX = object->tileObjectImg->getWidth() / (TILE_SIZE_X);
		object->sizeY = object->tileObjectImg->getHeight() / (TILE_SIZE_Y);
		object->objectTotalRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
		object->objectCollisionRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
	}
	if (index == 1)
	{
		object->tile_objectKind = TILE_OBJECTKIND_ROCK;
		object->sizeX = object->tileObjectImg->getWidth() / (TILE_SIZE_X);
		object->sizeY = object->tileObjectImg->getHeight() / (TILE_SIZE_Y);
		object->objectTotalRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
		object->objectCollisionRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
	}
	if (index == 2)
	{
		object->tile_objectKind = TILE_OBJECTKIND_WOOD;
		object->sizeX = object->tileObjectImg->getWidth() / (TILE_SIZE_X);
		object->sizeY = object->tileObjectImg->getHeight() / (TILE_SIZE_Y);
		object->objectTotalRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
		object->objectCollisionRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
	}
	if (index == 3 || index == 4 || index == 5)
	{
		object->tile_objectKind = TILE_OBJECTKIND_TREE;
		object->sizeX = object->tileObjectImg->getFrameWidth() / (TILE_SIZE_X);
		object->sizeY = object->tileObjectImg->getFrameHeight() / (TILE_SIZE_Y);
		object->objectTotalRc = RectMake(object->objectPos.x*(TILE_SIZE_X), object->objectPos.y*(TILE_SIZE_Y), object->sizeX*(TILE_SIZE_X), object->sizeY*(TILE_SIZE_Y));
		object->objectCollisionRc = RectMake(object->objectPos.x*(TILE_SIZE_X)+ 16 * 3, object->objectPos.y*(TILE_SIZE_Y)+ 64 * 3, 16 * 3, 32 * 3);
		object->hp = 7;
	}

}

void tileMap::setTileImage(int x, int y, int num, const char * keyName)
{
	_tileMap[y][x].tileTerrainImg[num] = IMAGEMANAGER->findImage(keyName);
}

void tileMap::setObjectFrame(int num, int frameX, int frameY)
{
	_tileObject[num]->objectFrame = POINT{frameX, frameY};
}

