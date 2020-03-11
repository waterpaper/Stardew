#pragma once

//ũ��(�̹��� 3�� Ȯ��)
#define TILE_SIZE_X 16 * 3
#define TILE_SIZE_Y 16 * 3

//�ʱ���ǥ
#define INIT_X 0
#define INIT_Y 0

//Ÿ�� ����
#define TILE_NUM_MAX 3
#define TILE_COUNT_X 20
#define TILE_COUNT_Y 20

//���� Ÿ�� �̹���
#define TILE_SAMPLE_COUNT_X 12
#define TILE_SAMPLE_COUNT_Y 12
#define TILE_SAMPLE_TOTALIMAGE_SIZEX 300
#define TILE_SAMPLE_TOTALIMAGE_SIZEY 300

//�̴ϸʻ�����
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
	int tileNum;								//Ÿ���� ������ �ǹ��Ѵ�
	image *tileTerrainImg[TILE_NUM_MAX];		//Ÿ���� ���� �̹����� ��Ÿ����
	int imageIndex[TILE_NUM_MAX];				//� �̹����� ��ġ�ϴ��� ��Ÿ����(���̺�, �ε�� ���)
	POINT tileFrame[TILE_NUM_MAX];				//�̹����� ��� ��ġ�� �����ϴ��� ��Ÿ����

	POINT tilePos;								//Ÿ�ϸʿ��� Ÿ���� ��ġ�� �����Ѵ�.
	RECT tileRc;								//Ÿ�ϸ��� ��Ʈ�� �����Ѵ�

	bool isTerrain, isObject, isShader;			//Ÿ�Ͽ� �ٴ��� �����ϴ��� ������Ʈ�� �����ϴ����� ���� ���θ� �����մϴ�
												//������Ʈ�� ���� �����ϳ� �÷��̾� �̵������ �˻縦 ���� ��ġ�� Ÿ�Ͽ� ������Ʈ�� �����ϴ��� ���θ� �����մϴ�
												//�׷��Ƿ� ������Ʈ �߰�, ���Ž� terrain�� ������ �ʿ��մϴ�


	TILE_TERRAINKIND tile_terrainKind;			//Ÿ�� �ٴ��� ������ �����Ѵ�
};

struct TagTile_Object
{
	image *tileObjectImg;						//Ÿ�Ͽ�����Ʈ�� ���� �̹����� ��Ÿ����
	int imageIndex;								//� �̹����� ��ġ�ϴ��� ��Ÿ����(���̺�, �ε�� ���)

	int hp;

	POINT objectFrame;							//Ÿ�Ͽ�����Ʈ�� �������� ��Ÿ����
	POINT objectPos;							//Ÿ�Ͽ�����Ʈ�� ��ġ�� �����Ѵ�.
	int sizeX, sizeY;							//Ÿ�Ͽ�����Ʈ�� ũ�⸦ ��Ÿ����
	RECT objectTotalRc;							//Ÿ�Ͽ�����Ʈ�� ��ü��Ʈ�� ��Ÿ����.
	RECT objectCollisionRc;						//Ÿ�Ͽ�����Ʈ�� �浹ó����Ʈ�� ��Ÿ����.

	TILE_OBJECTKIND tile_objectKind;			//Ÿ�Ͽ�����Ʈ�� ������ �����Ѵ�.

};

//���� ���� ����
typedef TagTile_TERRAIN **bTileMap;
typedef vector<TagTile_Object *> vTileObject;
typedef vector<TagTile_Object *>::iterator viTileObject;

typedef vector<string> vSampleTileMapString;