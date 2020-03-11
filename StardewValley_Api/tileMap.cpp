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
	//tileMap 클래스를 초기화합니다

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
		메모리를 해제합니다
		*/
		for (int i = 0; i < _maxTileY; i++)
		{
			free(_tileMap[i]);
		}
		free(_tileMap);

		/*
		메모리릭을 해결하기 위해 요소마다 delete
		그 이후 capacity를 초기화한다
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
	타일맵을 이차원 배열로 초기화합니다
	*/
	release();

	_maxTileX = tileSizeX;
	_maxTileY = tileSizeY;

	//동적배열
	_tileMap = (TagTile_TERRAIN**)malloc(sizeof(TagTile_TERRAIN*) * _maxTileY);
	for (int i = 0; i < _maxTileY; i++) {
		_tileMap[i] = (TagTile_TERRAIN*)malloc(sizeof(TagTile_TERRAIN) * _maxTileX);
	}

	//초기화
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
	//타일맵의 타일 수정합니다
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
	타일맵에 오브젝트를 추가합니다
	*/
	RECT tempRc, collision;

	kindSelectObject(tileObject, tileObject->imageIndex);

	//전체 타일맵을 넘어가는 경우
	if (tileObject->objectPos.x + tileObject->sizeX > _maxTileX ||
		tileObject->objectPos.y + tileObject->sizeY > _maxTileY) return;

	//겹치는 오브젝트가 있는 경우
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
	타일맵에 특정 오브젝트를 삭제합니다
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
	tileMap을 화면 크기에 맞게 그려줍니다
	*/

	//임시변수
	char str[256];
	int sizeTempX, sizeTempY;
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();

	/*
	타일맵의 배경이 존재할시 배경을 먼저 그려줍니다
	현재 윈도우 사이즈 보다 작은 경우를 먼저 검사하고 해당 화면 크기만큼 그려줍니다
	(윈도우 사이즈보다 작으면 해당 사이즈 만큼만 render 해야하기 때문)
	*/

	//사이즈 검사
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

	//이미지 출력
	if (_isTileMapImage)
	{
		_tileMapImage->render(hdc, cameraX, cameraY, 0, 0, sizeTempX, sizeTempY);
	}

	/*
	타일맵의 Terrain을 화면 크기에 맞게 render합니다
	화면 가장 왼쪽에 위치한 타일과 맨위에 위치한 타일부터 가장 오른쪽 +1만큼의 타일까지 검사, 그려줍니다
	*/
	for (int i = cameraY / (TILE_SIZE_Y); i < _maxTileY; i++)
	{
		//화면에 나오는 타일만 그려주기 위해 타일이 넘어가면 종료합니다(화면 제일 마지막일때 예외처리 위해 for가 아닌 아래에서 처리)
		if ((cameraY + WINSIZEY) / (TILE_SIZE_Y) <= i)
			break;

		for (int j = cameraX / (TILE_SIZE_X); j < _maxTileX; j++)
		{
			//화면에 나오는 타일만 그려주기 위해 타일이 넘어가면 종료합니다(화면 제일 마지막일때 예외처리 위해 for가 아닌 아래에서 처리)
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
	타일맵의 Object를 render합니다
	타일맵의 terrain과는 다른 벡터에서 관리하기 때문에 따로 그려줍니다
	화면 크기에 맞는 부분만 랜더하기 위해 카메라를 이용해 검사합니다
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
	이동시 맵의 일부분만 다시그려주는 함수입니다
	타일 사이즈가 전체맵의 사이즈를 넘는지 검사하고 그려줍니다
	*/

	RECT rectTemp = PLAYERMANAGER->getPlayerState().getPlayerRc();
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();

	int startX, startY, endX, endY;
	startX = rectTemp.left / (TILE_SIZE_X);
	endX = rectTemp.right / (TILE_SIZE_X);
	startY = rectTemp.top / (TILE_SIZE_Y);
	endY = rectTemp.bottom / (TILE_SIZE_Y);

	//임시변수
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;


	//해당 위치에 terrain을 다시 그려줍니다
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

	//해당 위치에 object를 다시 그려줍니다
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
	//임시변수
	TagTile_TERRAIN terrainTemp;

	int startX, startY, endX, endY;
	startX = rc.left / (TILE_SIZE_X);
	endX = rc.right / (TILE_SIZE_X);
	startY = rc.top / (TILE_SIZE_Y);
	endY = rc.bottom / (TILE_SIZE_Y);

	//해당 위치에 terrain을 다시 그려줍니다
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
	맵의 일부분만 다시그려주는 함수입니다
	타일 사이즈가 전체맵의 사이즈를 넘는지 검사하고 그려줍니다
	*/

	//임시변수
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	PatBlt(hdc, tileX*(TILE_SIZE_X), tileY*(TILE_SIZE_Y), sizeX*(TILE_SIZE_X), sizeY*(TILE_SIZE_Y), WHITENESS);

	//해당 위치에 terrain을 다시 그려줍니다
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
		//해당 위치에 object를 다시 그려줍니다
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
	tileMap을 전체 그려줍니다(미니맵과 타일층 보기를 위함)
	*/

	//임시변수
	char str[256];
	int sizeTempX, sizeTempY;
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;
	INGAMESCENE_NAME sceneTemp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();
	/*
	타일맵의 배경이 존재할시 배경을 먼저 그려줍니다
	현재 윈도우 사이즈 보다 작은 경우를 먼저 검사하고 해당 화면 크기만큼 그려줍니다
	(윈도우 사이즈보다 작으면 해당 사이즈 만큼만 render 해야하기 때문)
	*/

	//사이즈 검사
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

	//이미지 출력
	if (_isTileMapImage)
	{
		_tileMapImage->render(hdc, 0, 0);
	}

	/*
	타일맵의 Terrain을 크기에 맞게 render합니다
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
		타일맵의 Object를 render합니다
		타일맵의 terrain과는 다른 벡터에서 관리하기 때문에 따로 그려줍니다
		화면 크기에 맞는 부분만 랜더하기 위해 카메라를 이용해 검사합니다
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
	디버그 모드일시 타일 번호와 렉트를 그려주는 함수입니다
	타일맵을 화면 크기에 맞게 render합니다
	화면 가장 왼쪽에 위치한 타일과 맨위에 위치한 타일부터 가장 오른쪽 +1만큼의 타일까지 검사, 그려줍니다
	*/

	//임시변수
	char str[256];
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	if (_isDebug)
	{
		for (int i = cameraY / (TILE_SIZE_Y); i < _maxTileY; i++)
		{
			//화면에 나오는 타일만 그려주기 위해 타일이 넘어가면 종료합니다(화면 제일 마지막일때 예외처리 위해 for가 아닌 아래에서 처리)
			if ((cameraY + WINSIZEY) / (TILE_SIZE_Y)+1 < i)
				break;

			for (int j = cameraX / (TILE_SIZE_X); j < _maxTileX; j++)
			{
				//화면에 나오는 타일만 그려주기 위해 타일이 넘어가면 종료합니다(화면 제일 마지막일때 예외처리 위해 for가 아닌 아래에서 처리)
				if ((cameraX + WINSIZEX) / (TILE_SIZE_X)+1 < j)
					break;

				terrainTemp = _tileMap[i][j];

				//배경모드
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(0, 0, 0));

				//사각형과 좌표를 출력합니다
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
	속성 모드일시 타일 번호와 속성타일을 그려주는 함수입니다
	타일맵을 맵 크기에 맞게 render합니다
	*/

	//임시변수
	char str[256];
	TagTile_TERRAIN terrainTemp;
	TagTile_Object *objectTemp = nullptr;

	int sizeTempX, sizeTempY;

	//사이즈 검사
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
	오브젝트의 속성값을 지정합니다
	여기서 정의되지 않은 오브젝트는 그려지지 않습니다(크기가 없기때문)
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

