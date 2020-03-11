#include "stdafx.h"
#include "tileMapManager.h"


tileMapManager::tileMapManager()
{
	_minimapX = TILE_MINIMAP_SIZEX;
	_minimapY = TILE_MINIMAP_SIZEY;
}


tileMapManager::~tileMapManager()
{
	release();
}

HRESULT tileMapManager::init()
{
	/*
	tileMapManager를 초기화 합니다
	tilemap의 사이즈 초기값은 32,32입니다(tileMap->init에서 초기화)

	이미지 추가를 통해 새 dc를 크기에 맞게 선언해주고
	patblt를 통해 흰색 이미지로 만들어 줍니다
	*/
	SAFE_DELETE(_tileMap);
	_tileMap = new tileMap;
	_tileMap->init();
	tileMapSetting(_tileMap->getTileMapSize().x, _tileMap->getTileMapSize().y);

	//타일맵 스트링백터 추가
	addSampleTileMapAdd();

	return S_OK;
}

HRESULT tileMapManager::init(int x, int y)
{
	/*
		tileMapManager를 초기화 합니다

		이미지 추가를 통해 새 dc를 크기에 맞게 선언해주고
		patblt를 통해 흰색 이미지로 만들어 줍니다
		*/
	SAFE_DELETE(_tileMap);
	_tileMap = new tileMap();

	tileMapSetting(x, y);

	return S_OK;
}

void tileMapManager::render(HDC hdc)
{
	/*
	현재 타일맵 매니저가 가지고 있는 타일맵을 출력합니다
	보이는 위치는 카메라 매니저에서 가지고 있는 위치를 사용합니다
	*/
	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	POINT maxTile = _tileMap->getTileMapSize();
	POINT sizeTemp;

	//사이즈 검사
	if (maxTile.x*TILE_SIZE_X <= WINSIZEX)
	{
		sizeTemp.x = maxTile.x * TILE_SIZE_X;
	}
	else
	{
		sizeTemp.x = WINSIZEX;
	}

	if (maxTile.y*TILE_SIZE_Y <= WINSIZEY)
	{
		sizeTemp.y = maxTile.y * TILE_SIZE_Y;
	}
	else
	{
		sizeTemp.y = WINSIZEY;
	}

	//글씨체 선택
	SelectObject(hdc, hSmallFont);

	BitBlt(hdc, cameraTemp.x, cameraTemp.y, cameraTemp.x + WINSIZEX, cameraTemp.y + WINSIZEY, _mapBuffer->getMemDC(), cameraTemp.x, cameraTemp.y, SRCCOPY);

	if (_isAttribute)
	{
		GdiTransparentBlt(hdc, cameraTemp.x, cameraTemp.y, sizeTemp.x, sizeTemp.y, _attributeMapBuffer->getMemDC(), cameraTemp.x, cameraTemp.y, sizeTemp.x, sizeTemp.y, RGB(255, 255, 255));			//제외할 칼라
		_attributeMapBuffer->render(_attributeMiniMapBuffer->getMemDC(), 0, 0, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);
		GdiTransparentBlt(_minimapBuffer->getMemDC(), 0, 0, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY, _attributeMiniMapBuffer->getMemDC(), 0, 0, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY, RGB(255, 255, 255));			//제외할 칼라
	}

	//타일맵 위치 그리기
	if (_isDebug)
	{
		_tileMap->debugRenderTileMap(hdc, cameraTemp.x, cameraTemp.y);
	}
}

void tileMapManager::allRender()
{
	/*
	전체맵을 다시 로딩하는 함수입니다
	*/
	tileNumRender(0);
}

void tileMapManager::tileNumRender(int num)
{
	/*
	해당하는 타일 층만 그려주는 함수입니다.
	보이는 위치는 카메라 매니저에서 가지고 있는 위치를 사용합니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	PatBlt(_mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y), WHITENESS);

	_tileMap->allRenderTileMap(_mapBuffer->getMemDC(), num);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::attributeRender()
{
	/*
	전체 속성맵을 업데이트하는 함수입니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	_tileMap->attributeRenderTileMap(_attributeMapBuffer->getMemDC());
}

void tileMapManager::reDrawMoveRender(HDC hdc)
{
	_tileMap->reDrawTileMap(hdc);
}

void tileMapManager::reDrawRender(int startX, int startY, int endX, int endY)
{
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	_tileMap->reDrawTileMap(_mapBuffer->getMemDC(), startX, startY, endX, endY, true);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::reDrawTileMap_tileNpc(HDC hdc)
{
	vector<npc *> vNpc = NPCMANAGER->getNpcVector();
	INGAMESCENE_NAME scene = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();

	for (int i = 0; i < vNpc.size(); i++)
	{
		if (vNpc[i]->getIngameScene() == scene)
		{
			_tileMap->reDrawTileMap_tile(hdc, vNpc[i]->getRc());
		}
	}
}


void tileMapManager::update()
{

}

void tileMapManager::release()
{
	_tileMap->release();
}

void tileMapManager::tileMapSetting(int tileSizeX, int tileSizeY)
{
	/*
	타일맵을 다시 세팅해 주는 함수입니다
	새 dc를 만들어 세팅하며 타일맵 사이즈 또한 변경합니다
	변경이 끝나면 그려진 초기 타일맵을 맵에 그려주어
	미니맵을 그려줄때 사용합니다
	*/
	IMAGEMANAGER->deleteImage("mapBuffer");
	_mapBuffer = IMAGEMANAGER->addImage("mapBuffer", tileSizeX*(TILE_SIZE_X), tileSizeY*(TILE_SIZE_Y));

	IMAGEMANAGER->deleteImage("attributeMapBuffer");
	_attributeMapBuffer = IMAGEMANAGER->addImage("attributeMapBuffer", tileSizeX*(TILE_SIZE_X), tileSizeY*(TILE_SIZE_Y));

	IMAGEMANAGER->deleteImage("minimapBuffer");
	_minimapBuffer = IMAGEMANAGER->addImage("minimapBuffer", TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);

	IMAGEMANAGER->deleteImage("attributeMinimapBuffer");
	_attributeMiniMapBuffer = IMAGEMANAGER->addImage("attributeMinimapBuffer", TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);

	PatBlt(_mapBuffer->getMemDC(), 0, 0, tileSizeX*(TILE_SIZE_X), tileSizeY*(TILE_SIZE_Y), WHITENESS);
	PatBlt(_attributeMapBuffer->getMemDC(), 0, 0, tileSizeX*(TILE_SIZE_X), tileSizeY*(TILE_SIZE_Y), WHITENESS);

	_tileMap->setTileMap(tileSizeX, tileSizeY);
	_tileMap->allRenderTileMap(_mapBuffer->getMemDC(), 0);

	CAMERAMANAGER->cameraAllTileRender(_mapBuffer->getMemDC(), tileSizeX, tileSizeY);

	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeX*(TILE_SIZE_X), tileSizeY*(TILE_SIZE_Y));
}

void tileMapManager::addTileMapIamge(char * imageName)
{
	/*
	타일맵에 이미지를 추가합니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	if (strlen(imageName) == 0)
	{
		return;
	}
	_tileMap->addTileMapIamge(imageName);
	_tileMap->allRenderTileMap(_mapBuffer->getMemDC(), 0);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::setTileMap(tileMap tilemap)
{
	POINT size = tilemap.getTileMapSize();
	bTileMap bTilemap = tilemap.getTileMap();
	vTileObject vTileobj = tilemap.getTileObject();
	TagTile_TERRAIN tile;
	TagTile_Object *object;

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			tile.isObject = bTilemap[i][j].isObject;
			tile.isShader = bTilemap[i][j].isShader;
			tile.isTerrain = bTilemap[i][j].isTerrain;
			tile.tileNum = bTilemap[i][j].tileNum;
			for (int n = 0; n < 3; n++)
			{
				tile.imageIndex[n] = bTilemap[i][j].imageIndex[n];
				tile.tileFrame[n] = bTilemap[i][j].tileFrame[n];
				tile.tileTerrainImg[n] = bTilemap[i][j].tileTerrainImg[n];
				_tileMap->setTile(tile, j, i, n);
			}
			_tileMap->setKindTerrian(bTilemap[i][j].tile_terrainKind,j,i);
		}
	}

	for (int i = 0; i < vTileobj.size(); i++)
	{
		object = new TagTile_Object;
		object->imageIndex = vTileobj[i]->imageIndex;
		object->objectFrame = vTileobj[i]->objectFrame;
		object->objectCollisionRc = vTileobj[i]->objectCollisionRc;
		object->objectPos = vTileobj[i]->objectPos;
		object->objectTotalRc = vTileobj[i]->objectTotalRc;
		object->sizeX = vTileobj[i]->sizeX;
		object->sizeY = vTileobj[i]->sizeY;
		object->tileObjectImg = vTileobj[i]->tileObjectImg;
		object->tile_objectKind = vTileobj[i]->tile_objectKind;

		_tileMap->addObject(object);
		object = nullptr;
	}
}

void tileMapManager::setTile(TagTile_TERRAIN tile, int x, int y, int num)
{
	/*
	타일맵에 타일을 수정합니다
	그 이후 dc에 수정된 부분과 미니맵을 다시그려줍니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	_tileMap->setTile(tile, x, y, num);
	_tileMap->reDrawTileMap(_mapBuffer->getMemDC(), x, y, 1, 1, true);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
	_tileMap->attributeRenderRectSelect(_attributeMapBuffer->getMemDC(), tile);


	if (_isAttribute)
	{
		_attributeMapBuffer->render(_attributeMiniMapBuffer->getMemDC(), 0, 0, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);
	}
}

void tileMapManager::setTile(TagTile_TERRAIN tile, int x, int y, POINT frameStart, POINT frameEnd, int num)
{
	/*
	타일맵에 타일을 수정합니다
	그 이후 dc에 수정된 부분과 미니맵을 다시그려줍니다
	*/

	POINT tileSizeTemp = _tileMap->getTileMapSize();

	for (int i = frameStart.y; i <= frameEnd.y; i++)
	{
		if (y + i - frameStart.y >= tileSizeTemp.y) break;
		for (int j = frameStart.x; j <= frameEnd.x; j++)
		{
			if (x + j - frameStart.x >= tileSizeTemp.x) break;

			tile.tileFrame[num] = POINT{ j,i };
			tile.isTerrain = true;

			if (_tileMap->getIsObject(j + x - frameStart.x, i + y - frameStart.y))
			{
				tile.isObject = true;
			}
			else
			{
				tile.isObject = false;
			}

			_tileMap->setTile(tile, x + j - frameStart.x, y + i - frameStart.y, num);
		}
	}
	_tileMap->reDrawTileMap(_mapBuffer->getMemDC(), x, y, frameEnd.x - frameStart.x + 1, frameEnd.y - frameStart.y + 1, true);

	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::addObject(TagTile_Object * object)
{
	/*
	타일맵에 오브젝트룰 추가합니다
	그 이후 dc에 수정된 부분과 미니맵을 다시그려줍니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	_tileMap->addObject(object);
	_tileMap->reDrawTileMap(_mapBuffer->getMemDC(), object->objectPos.x, object->objectPos.y, object->sizeX, object->sizeY, true);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::deleteObject(int num)
{
	/*
	타일맵에 오브젝트룰 제거합니다
	그 이후 dc에 수정된 부분과 미니맵을 다시그려줍니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();
	TagTile_Object *object = _tileMap->getTileObject(num);

	if (object->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_WOOD)
	{
		EFFECTMANAGER->play("이펙트_호미질", object->objectTotalRc.left + object->sizeX * 48 / 2, object->objectTotalRc.top + object->sizeY * 48 / 2);
		ITEMMANAGER->materialWoodDrop(object->objectTotalRc.left + object->sizeX * 48 / 2, object->objectTotalRc.top + object->sizeY * 48 / 2, false);
	}
	else if (object->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_GRASS)
	{
		EFFECTMANAGER->play("이펙트_풀제거", object->objectTotalRc.left+object->sizeX*48/2, object->objectTotalRc.top+object->sizeY * 48 / 2);
		ITEMMANAGER->materialDrop(object->objectTotalRc.left + object->sizeX * 48 / 2, object->objectTotalRc.top + object->sizeY * 48 / 2);
	}
	else if (object->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_ROCK)
	{
		EFFECTMANAGER->play("이펙트_돌제거", object->objectTotalRc.left + object->sizeX * 48 / 2, object->objectTotalRc.top + object->sizeY * 48 / 2);
		ITEMMANAGER->rockDrop(object->objectTotalRc.left + object->sizeX * 48 / 2, object->objectTotalRc.top + object->sizeY * 48 / 2);
	}
	else if (object->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
	{
		EFFECTMANAGER->play("이펙트_나무1쓰러짐", object->objectTotalRc.left + 144, object->objectTotalRc.top + 216);
		_sound.effSoundPlay("나무쓰러짐");
	}

	_tileMap->deleteObject(_mapBuffer->getMemDC(), num);
	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));

	object = nullptr;
}

void tileMapManager::initTileMap()
{
	tileMapSetting(_tileMap->getTileMapSize().x, _tileMap->getTileMapSize().y);
}

void tileMapManager::setTileMapAttribute(int x, int y, TILE_TERRAINKIND kind)
{
	/*
	타일의 속성을 재설정하고 맵을 다시 그려줍니다
	*/
	POINT tileSizeTemp = _tileMap->getTileMapSize();

	if (tileSizeTemp.x <= x || tileSizeTemp.y <= y)	return;

	if (_tileMap->getIsTerrain(x, y))
	{
		_tileMap->setKindTerrian(kind, x, y);
		_tileMap->attributeRenderRectSelect(_attributeMapBuffer->getMemDC(), _tileMap->getTileMap(x, y));

		if (_isAttribute)
		{
			_attributeMapBuffer->render(_attributeMiniMapBuffer->getMemDC(), 0, 0, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);
		}
	}
}

void tileMapManager::minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY)
{
	/*
	미니맵버퍼에 그려진 미니맵을 render합니다
	*/

	_minimapBuffer->render(hdc, posX, posY, 0, 0, minimapSizeX, minimapSizeY);
}

void tileMapManager::setMinimapSize(POINT mapSize)
{
	//미니맵의 사이즈를 바꾸고 다시 그려줍니다
	IMAGEMANAGER->deleteImage("minimapBuffer");
	_minimapBuffer = IMAGEMANAGER->addImage("minimapBuffer", mapSize.x, mapSize.y);

	_minimapX = mapSize.x;
	_minimapY = mapSize.y;

	POINT tileSizeTemp = _tileMap->getTileMapSize();

	_minimapBuffer->minimapRender(_minimapBuffer->getMemDC(), 0, 0, _minimapX, _minimapY, _mapBuffer->getMemDC(), 0, 0, tileSizeTemp.x*(TILE_SIZE_X), tileSizeTemp.y*(TILE_SIZE_Y));
}

void tileMapManager::loadTileMapIamge(const char *fileName, INGAMESCENE_NAME sceneName)
{
	/*
	타일맵을 로드한다
	*/
	int imageTemp = 0, objectNum = 0;
	char str[1000];
	char *pathTemp = {};
	POINT tileSizeTemp;								//현재 타일맵 사이즈
	ifstream inFile(fileName);
	TagTile_TERRAIN tileTerrainTemp;
	TagTile_Object *tileObjectTemp;
	TILE_TERRAINKIND temp;

	if (sceneName == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM&&!FARMMANAGER->getIsFirst())
	{
		//타일맵 초기화
		tileMapSetting(100, 100);
		setTileMap(FARMMANAGER->getFarmMap());
	}
	else
	{
		ZeroMemory(str, sizeof(str));
		inFile.getline(str, 1000);
		sscanf_s(str, "isTileImage : %d\r\n", &imageTemp);
		_tileMap->setIsImage(imageTemp);

		if (imageTemp)
		{
			ZeroMemory(str, sizeof(str));
			inFile.getline(str, 1000);
			strtok(str, ":");
			pathTemp = strtok(NULL, ":");

			sscanf_s(str, "imagePath :%s\r\n", &pathTemp);
			_tileMap->addTileMapIamge(pathTemp);
		}

		ZeroMemory(str, sizeof(str));
		inFile.getline(str, 1000);
		sscanf_s(str, "x : %d, y : %d\r\n", &tileSizeTemp.x, &tileSizeTemp.y);

		//타일맵 초기화
		tileMapSetting(tileSizeTemp.x, tileSizeTemp.y);

		for (int i = 0; i < tileSizeTemp.y; i++)
		{
			for (int j = 0; j < tileSizeTemp.x; j++)
			{
				ZeroMemory(str, sizeof(str));
				inFile.getline(str, 1000);

				sscanf_s(str, "%d ,%d, %d, %d, imageframe : %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
					&tileTerrainTemp.isTerrain,
					&tileTerrainTemp.isObject,
					&tileTerrainTemp.tileNum,
					&temp,

					&tileTerrainTemp.imageIndex[0],
					&tileTerrainTemp.tileFrame[0].x,
					&tileTerrainTemp.tileFrame[0].y,
					&tileTerrainTemp.imageIndex[1],
					&tileTerrainTemp.tileFrame[1].x,
					&tileTerrainTemp.tileFrame[1].y,
					&tileTerrainTemp.imageIndex[2],
					&tileTerrainTemp.tileFrame[2].x,
					&tileTerrainTemp.tileFrame[2].y
				);

				if (tileTerrainTemp.imageIndex[0] > -1)
				{
					tileTerrainTemp.tileTerrainImg[0] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[0]]);
				}
				if (tileTerrainTemp.imageIndex[1] > -1)
				{
					tileTerrainTemp.tileTerrainImg[1] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[1]]);
				}
				if (tileTerrainTemp.imageIndex[2] > -1)
				{
					tileTerrainTemp.tileTerrainImg[2] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[2]]);
				}

				_tileMap->setTile(tileTerrainTemp, j, i, 0);
				_tileMap->setTile(tileTerrainTemp, j, i, 1);
				_tileMap->setTile(tileTerrainTemp, j, i, 2);

				_tileMap->setKindTerrian(temp, j, i);
			}
		}

		ZeroMemory(str, sizeof(str));
		inFile.getline(str, 1000);
		sscanf_s(str, "tileMap_object_num : %d\r\n", &objectNum);


		for (int i = 0; i < objectNum; i++)
		{
			tileObjectTemp = new TagTile_Object;

			ZeroMemory(str, sizeof(str));
			inFile.getline(str, 1000);

			sscanf_s(str, "%d ,%d, %d, %d, %d, %d, %d\r\n",
				&(tileObjectTemp->imageIndex),
				&(tileObjectTemp->objectPos.x),
				&(tileObjectTemp->objectPos.y),
				&(tileObjectTemp->objectFrame.x),
				&(tileObjectTemp->objectFrame.y),
				&(tileObjectTemp->sizeX),
				&(tileObjectTemp->sizeY)
			);

			tileObjectTemp->tileObjectImg = IMAGEMANAGER->findImage(_vSampleTileMapString_object[tileObjectTemp->imageIndex]);

			_tileMap->addObject(tileObjectTemp);
			tileObjectTemp = nullptr;
		}

		inFile.close();

		if (sceneName == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM&&FARMMANAGER->getIsFirst())
		{
			FARMMANAGER->setFarmMap(*_tileMap);
			FARMMANAGER->setIsFirst(false);
		}
	}

	seasonImageSeting();
	TILEMAPMANAGER->allRender();

}

void tileMapManager::saveTileMapIamge(char * fileName)
{
	char str[1000];										//문자열을 저장, 읽어올 변수

	POINT tileSizeTemp = _tileMap->getTileMapSize();	//현재 타일맵 사이즈
	bTileMap tileMapTemp = _tileMap->getTileMap();
	vTileObject tileObjectTemp = _tileMap->getTileObject();

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "isTileImage : %d\r\n", _tileMap->getIsImage());
	WriteFile(file, str, strlen(str), &write, NULL);

	if (_tileMap->getIsImage())
	{
		ZeroMemory(str, sizeof(str));
		sprintf_s(str, "imagePath :%s\r\n", _tileMap->getImagePath().c_str());
		WriteFile(file, str, strlen(str), &write, NULL);
	}

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "x : %d, y : %d\r\n", tileSizeTemp.x, tileSizeTemp.y);
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < tileSizeTemp.y; i++)
	{
		for (int j = 0; j < tileSizeTemp.x; j++)
		{
			ZeroMemory(str, sizeof(str));
			sprintf_s(str, "%d ,%d, %d, %d, imageframe : %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
				tileMapTemp[i][j].isTerrain,
				tileMapTemp[i][j].isObject,
				tileMapTemp[i][j].tileNum,
				tileMapTemp[i][j].tile_terrainKind,

				tileMapTemp[i][j].imageIndex[0],
				tileMapTemp[i][j].tileFrame[0].x,
				tileMapTemp[i][j].tileFrame[0].y,
				tileMapTemp[i][j].imageIndex[1],
				tileMapTemp[i][j].tileFrame[1].x,
				tileMapTemp[i][j].tileFrame[1].y,
				tileMapTemp[i][j].imageIndex[2],
				tileMapTemp[i][j].tileFrame[2].x,
				tileMapTemp[i][j].tileFrame[2].y
			);

			WriteFile(file, str, strlen(str), &write, NULL);
		}
	}

	ZeroMemory(str, sizeof(str));
	sprintf_s(str, "tileMap_object_num : %d\r\n", tileObjectTemp.size());
	WriteFile(file, str, strlen(str), &write, NULL);

	for (int i = 0; i < tileObjectTemp.size(); i++)
	{
		ZeroMemory(str, sizeof(str));

		sprintf_s(str, "%d ,%d, %d, %d, %d, %d, %d\r\n",
			tileObjectTemp[i]->imageIndex,
			tileObjectTemp[i]->objectPos.x,
			tileObjectTemp[i]->objectPos.y,
			tileObjectTemp[i]->objectFrame.x,
			tileObjectTemp[i]->objectFrame.y,
			tileObjectTemp[i]->sizeX,
			tileObjectTemp[i]->sizeY
		);

		WriteFile(file, str, strlen(str), &write, NULL);
	}

	CloseHandle(file);
}

void tileMapManager::addSampleTileMapAdd()
{
	if (_vSampleTileMapString_terrian.size() == 0)
	{
		//타일맵 이미지 네임 추가
		_vSampleTileMapString_terrian.push_back("타일_기본1_봄");
		_vSampleTileMapString_terrian.push_back("타일_기본2_봄");
		_vSampleTileMapString_terrian.push_back("타일_타운1_봄");
		_vSampleTileMapString_terrian.push_back("타일_타운2_봄");
		_vSampleTileMapString_terrian.push_back("타일_타운3_봄");
		_vSampleTileMapString_terrian.push_back("타일_집1");
		_vSampleTileMapString_terrian.push_back("타일_집2");
		_vSampleTileMapString_terrian.push_back("타일_기본3_봄");
		_vSampleTileMapString_terrian.push_back("타일_샵1");
		_vSampleTileMapString_terrian.push_back("타일_샵2");
		_vSampleTileMapString_terrian.push_back("타일_샵3");
		_vSampleTileMapString_terrian.push_back("타일_농장1");

		//오브젝트 이미지 네임 추가
		_vSampleTileMapString_object.push_back("오브젝트_풀");
		_vSampleTileMapString_object.push_back("오브젝트_돌");
		_vSampleTileMapString_object.push_back("오브젝트_나무조각");
		_vSampleTileMapString_object.push_back("오브젝트_나무1");
		_vSampleTileMapString_object.push_back("오브젝트_나무2");
		_vSampleTileMapString_object.push_back("오브젝트_나무3");
	}
}

void tileMapManager::seasonImageSeting()
{
	bTileMap tilemapTemp = _tileMap->getTileMap();
	POINT size = _tileMap->getTileMapSize();
	string strTemp1, strTemp2;
	SEASON seasonTemp = GAMETIMEMANAGER->getSeason();
	vTileObject tileObjectTemp = _tileMap->getTileObject();

	if (seasonTemp == SEASON::SEASON_SPRING)
	{
		strTemp2 = "봄";
	}
	else if (seasonTemp == SEASON::SEASON_SUMMER)
	{
		strTemp2 = "여름";
	}
	else if (seasonTemp == SEASON::SEASON_FALL)
	{
		strTemp2 = "가을";
	}
	else if (seasonTemp == SEASON::SEASON_WINTER)
	{
		strTemp2 = "겨울";
	}

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			for (int n = 0; n < 3; n++)
			{
				strTemp1 = imageIndexString(tilemapTemp[i][j].imageIndex[n]);

				if (strTemp1.compare("0") == 0)	continue;
				_tileMap->setTileImage(j, i, n, (strTemp1 + strTemp2).c_str());
			}

		}
	}

	for (int i = 0; i < tileObjectTemp.size(); i++)
	{
		if (tileObjectTemp[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
		{
			_tileMap->setObjectFrame(i, (int)seasonTemp - 1, 0);
		}
	}

}

string tileMapManager::imageIndexString(int index)
{
	if (index == 0)
	{
		return "타일_기본1_";
	}
	else if (index == 1)
	{
		return "타일_기본2_";
	}
	else if (index == 2)
	{
		return "타일_타운1_";
	}
	else if (index == 3)
	{
		return "타일_타운2_";
	}
	else if (index == 4)
	{
		return "타일_타운3_";
	}
	else if (index == 7)
	{
		return "타일_기본3_";
	}
	else
		return "0";
}
