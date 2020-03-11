#pragma once
#include "singletonBase.h"
#include "tileMap.h"
#include "scene.h"

class tileMapManager :public singletonBase<tileMapManager>
{
private:
	tileMap *_tileMap;
	image *_mapBuffer;
	image *_attributeMapBuffer;
	image *_minimapBuffer;
	image *_attributeMiniMapBuffer;

	vSampleTileMapString _vSampleTileMapString_terrian;											//바닥 샘플맵 이미지 키값을 가지고 잇는 벡터
																								//로드나 저장, 추가시 이것을 이용한다

	vSampleTileMapString _vSampleTileMapString_object;											//오브젝트 샘플맵 이미지 키값을 가지고 잇는 벡터

	int _minimapX, _minimapY;																	//미니맵 사이즈

	HANDLE file;																				//세이브, 로드을 위한 변수
	DWORD write;
	DWORD read;

public:
	tileMapManager();
	~tileMapManager();

	HRESULT init();
	HRESULT init(int x, int y);
	void render(HDC hdc);
	void allRender();
	void tileNumRender(int num);																//해당 배열층만 불러오는 렌더
	void attributeRender();																		//해당 배열층만 불러오는 렌더
	void reDrawMoveRender(HDC hdc);
	void reDrawRender(int startX, int startY, int endX, int endY);
	void reDrawTileMap_tileNpc(HDC hdc);
	void update();
	void release();

	//타일맵 관리
	//전체 타일맵을 재수정하고 사이즈를 조정합니다
	void tileMapSetting(int sizeX, int sizeY);

	POINT getTileMapSize() { return _tileMap->getTileMapSize(); };
	void setTileMapSize(POINT mapSize) { tileMapSetting(mapSize.x, mapSize.y); };

	void addTileMapIamge(char *imageName);														//타일맵에 이미지를 추가합니다
	void deleteTileMapImage() { _tileMap->deleteTileMapImage(); };								//타일맵에 이미지를 제거합니다

	tileMap getTileMap() { return *_tileMap; };
	void setTileMap(tileMap tilemap);
	void setTile(TagTile_TERRAIN tile, int x, int y, int num);									//타일맵에 타일을 수정합니다
	void setTile(TagTile_TERRAIN tile, int x, int y, POINT frameStart, POINT frameEnd, int num);//타일맵에 타일을 수정합니다
	void addObject(TagTile_Object *object);														//타일맵에 오브젝트룰 추가합니다
	void deleteObject(int num);																	//타일맵에 오브젝트를 제거합니다

	void initTileMap();																			//타일맵을 초기화합니다

	TILE_TERRAINKIND getTileMapAttribute(int x, int y) { return _tileMap->getKindTerrian(x, y); };				//속성들을 가져오거나 설정합니다
	void setTileMapAttribute(int x, int y, TILE_TERRAINKIND kind);
	bool getIsTerrain(int x, int y) { return _tileMap->getIsTerrain(x, y); };
	bool getIsObject(int x, int y) { return _tileMap->getIsObject(x, y); };

	//미니맵
	void minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY);		//미니맵랜더

	void setMinimapSize(POINT mapSize);

	int getMinimapX() { return _minimapX; };
	int	getMinimapY() { return _minimapY; };

	//타일맵을 블러오고 저장합니다
	void loadTileMapIamge(const char *fileName, INGAMESCENE_NAME sceneName);
	void saveTileMapIamge(char *fileName);

	//타일맵이 저장된 이미지들의 키값을 가진 벡터
	void addSampleTileMapAdd();
	string getNowSampleTileMapString_Terrian(int index) { return _vSampleTileMapString_terrian[index]; };
	string getNowSampleTileMapString_Object(int index) { return _vSampleTileMapString_object[index]; };
	int getSampleTileMapMaxIndex_Terrian() { return _vSampleTileMapString_terrian.size(); };
	int getSampleTileMapMaxIndex_Object() { return _vSampleTileMapString_object.size(); };

	void seasonImageSeting();
	string imageIndexString(int index);

	vSampleTileMapString getSampleTileMapString_terrian() { return _vSampleTileMapString_terrian; };
	vSampleTileMapString getSampleTileMapString_object() { return _vSampleTileMapString_object; };


	void setObjectHp(int i, int x) { _tileMap->setObjectHp(i,x); };
};

