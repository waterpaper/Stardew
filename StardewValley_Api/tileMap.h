#pragma once
#include "tile_Info.h"

class tileMap
{
private:
	image *_tileMapImage;														//타일맵에 이미지를 정의합니다.
	bool _isTileMapImage;														//타일맵에 이미지를 가지고 있는지 판단합니다
	string _tileMapImagePath;

	bTileMap _tileMap;															//전체 타일을 가지고 있는 이차원배열이다.(동적선언으로 전체 타일맵을 정의한다.)
	vTileObject _tileObject;													//전체 오브젝트를 가지고 있는 백터이다(한 오브젝트는 크기가 타일바닥과 다르나 전체가 플레이어와 상호작용하기때문에 따로 관리)
	viTileObject _iTileObject;													//오브젝트 벡터의 이터레이터

	int _maxTileX, _maxTileY;													//전체 타일맵의 수를 저장한 변수이다.

	HBRUSH green, red, blue, white, oBrush;

public:
	tileMap();
	~tileMap();

	HRESULT init();
	void update();
	void release();

	void setTileMap(int tileSizeX, int tileSizeY);								//맵 사이즈에따라 배열을 할당, 초기화합니다
	void addTileMapIamge(char *imageName);										//타일맵에 이미지를 추가합니다
	void deleteTileMapImage();													//타일맵에 이미지를 제거합니다

	void setTile(TagTile_TERRAIN btileMap, int x, int y, int num);				//타일을 교체합니다
	void addObject(TagTile_Object *tileObject);									//오브젝트를 추가합니다
	void deleteObject(HDC hdc, int num);										//오브젝트를 제거합니다
	void clearObject();															//오브젝트를 전체 삭제합니다

	bool getIsTerrain(int x, int y) { return _tileMap[y][x].isTerrain; };
	bool getIsObject(int x, int y) { return _tileMap[y][x].isObject; };
	bool getIsShader(int x, int y) { return _tileMap[y][x].isShader; };

	bool getIsImage() { return _isTileMapImage; };
	void setIsImage(bool isImage) { _isTileMapImage = isImage; };

	string getImagePath() { return _tileMapImagePath; };
	void setImagePath(string temp) { _tileMapImagePath = temp; };


	//render종류
	void screenRenderTileMap(HDC hdc, int cameraX, int cameraY);				//타일맵을 화면만큼만 다시 그려줍니다
	void reDrawTileMap(HDC hdc);												//타일맵의 일부분을 다시 그려줍니다(캐릭터 이동시 사용)
	void reDrawTileMap_tile(HDC hdc, RECT rc);
	void reDrawTileMap(HDC hdc, int tileX, int tileY, int sizeX, int sizeY, bool isObject);	//타일맵의 일부분을 다시 그려줍니다(수정시 사용)
	void allRenderTileMap(HDC hdc, int num);									//타일맵 전체를 다시 그려줍니다
	void debugRenderTileMap(HDC hdc, int cameraX, int cameraY);					//타일 번호를 그려줍니다
	void attributeRenderTileMap(HDC hdc);										//타일 속성를 그려줍니다
	void attributeRenderTileMap(HDC hdc, int x, int y);							//타일 속성를 그려줍니다

	void attributeRenderRectSelect(HDC hdc, TagTile_TERRAIN tile);				//속성을 판단해 렉트에 속성에 맞는 색상을 그려줍니다

	POINT getTileMapSize() { return POINT{ _maxTileX,_maxTileY }; };			//타일맵 사이즈 반환
	bTileMap getTileMap() { return _tileMap; };
	TagTile_TERRAIN getTileMap(int x, int y) { return _tileMap[y][x]; };
	vTileObject getTileObject() { return _tileObject; };
	TagTile_Object *getTileObject(int num) { return _tileObject[num]; };

	TILE_TERRAINKIND kindSelectTerrain(int index, int frameX, int frameY);		//타일의 종류를 지정해주는 함수
	void setKindTerrian(TILE_TERRAINKIND kind, int x, int y) { _tileMap[y][x].tile_terrainKind = kind; };
	TILE_TERRAINKIND getKindTerrian(int x, int y) { return _tileMap[y][x].tile_terrainKind; };

	void kindSelectObject(TagTile_Object *object, int index);					//오브젝트의 종류와 특성을 지정해주는 함수
	void setKindObject(TILE_OBJECTKIND kind, int num) { _tileObject[num]->tile_objectKind = kind; };
	TILE_OBJECTKIND getKindObject(int num) { return _tileObject[num]->tile_objectKind; };

	void setTileImage(int x, int y, int num, const char *keyName);
	void setObjectFrame(int num, int frameX, int frameY);

	void setObjectHp(int i, int x) { _tileObject[i]->hp = x; };
};

