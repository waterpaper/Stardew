#pragma once

//크기(이미지 3배 확대)
#define TILE_SIZE_X 16 * 3
#define TILE_SIZE_Y 16 * 3

//초기좌표
#define INIT_X 0
#define INIT_Y 0

//타일 갯수
#define TILE_NUM_MAX 3
#define TILE_COUNT_X 20
#define TILE_COUNT_Y 20

//샘플 타일 이미지
#define TILE_SAMPLE_COUNT_X 12
#define TILE_SAMPLE_COUNT_Y 12
#define TILE_SAMPLE_TOTALIMAGE_SIZEX 300
#define TILE_SAMPLE_TOTALIMAGE_SIZEY 300

//미니맵사이즈
#define TILE_MINIMAP_SIZEX 300
#define TILE_MINIMAP_SIZEY 200

enum TILE_TERRAINKIND
{
	TILE_TERRAINKIND_NULL,
	TILE_TERRAINKIND_SOIL,
	TILE_TERRAINKIND_GRASS,
	TILE_TERRAINKIND_NORMAL,
	TILE_TERRAINKIND_FARMLAND,
	TILE_TERRAINKIND_WATER,
	TILE_TERRAINKIND_WALL,
	TILE_TERRAINKIND_NOTMOVE,
	TILE_TERRAINKIND_END
};

enum TILE_OBJECTKIND
{
	TILE_OBJECTKIND_NULL,
	TILE_OBJECTKIND_GRASS,
	TILE_OBJECTKIND_WEED,
	TILE_OBJECTKIND_ROCK, 
	TILE_OBJECTKIND_WOOD,
	TILE_OBJECTKIND_TREE,
	TILE_OBJECTKIND_PRODUCE,
	TILE_OBJECTKIND_INTERIOR,
	TILE_OBJECTKIND_END
};

struct TagTile_TERRAIN
{
	int tileNum;								//타일의 갯수를 의미한다
	image *tileTerrainImg[TILE_NUM_MAX];		//타일이 속한 이미지를 나타낸다
	int imageIndex[TILE_NUM_MAX];				//어떤 이미지에 위치하는지 나타낸다(세이브, 로드시 사용)
	POINT tileFrame[TILE_NUM_MAX];				//이미지에 어느 위치에 존재하는지 나타낸다

	POINT tilePos;								//타일맵에서 타일의 위치를 정의한다.
	RECT tileRc;								//타일맵의 렉트를 정의한다

	bool isTerrain, isObject, isShader;			//타일에 바닥이 존재하는지 오브젝트가 존재하는지에 대한 여부를 결정합니다
												//오브젝트는 따로 관리하나 플레이어 이동검출시 검사를 위해 위치의 타일에 오브젝트가 존재하는지 여부를 저장합니다
												//그러므로 오브젝트 추가, 제거시 terrain의 수정이 필요합니다


	TILE_TERRAINKIND tile_terrainKind;			//타일 바닥의 종류를 정의한다
};

struct TagTile_Object
{
	image *tileObjectImg;						//타일오브젝트가 속한 이미지를 나타낸다
	int imageIndex;								//어떤 이미지에 위치하는지 나타낸다(세이브, 로드시 사용)

	int hp;

	POINT objectFrame;							//타일오브젝트의 프레임을 나타낸다
	POINT objectPos;							//타일오브젝트의 위치를 정의한다.
	int sizeX, sizeY;							//타일오브젝트의 크기를 나타낸다
	RECT objectTotalRc;							//타일오브젝트의 전체렉트를 나타낸다.
	RECT objectCollisionRc;						//타일오브젝트의 충돌처리렉트를 나타낸다.

	TILE_OBJECTKIND tile_objectKind;			//타일오브젝트의 종류를 정의한다.

};

//저장 형태 정의
typedef TagTile_TERRAIN **bTileMap;
typedef vector<TagTile_Object *> vTileObject;
typedef vector<TagTile_Object *>::iterator viTileObject;

typedef vector<string> vSampleTileMapString;