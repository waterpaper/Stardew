#pragma once
#include "tile_Info.h"

class tileMap
{
private:
	image *_tileMapImage;														//Ÿ�ϸʿ� �̹����� �����մϴ�.
	bool _isTileMapImage;														//Ÿ�ϸʿ� �̹����� ������ �ִ��� �Ǵ��մϴ�
	string _tileMapImagePath;

	bTileMap _tileMap;															//��ü Ÿ���� ������ �ִ� �������迭�̴�.(������������ ��ü Ÿ�ϸ��� �����Ѵ�.)
	vTileObject _tileObject;													//��ü ������Ʈ�� ������ �ִ� �����̴�(�� ������Ʈ�� ũ�Ⱑ Ÿ�Ϲٴڰ� �ٸ��� ��ü�� �÷��̾�� ��ȣ�ۿ��ϱ⶧���� ���� ����)
	viTileObject _iTileObject;													//������Ʈ ������ ���ͷ�����

	int _maxTileX, _maxTileY;													//��ü Ÿ�ϸ��� ���� ������ �����̴�.

	HBRUSH green, red, blue, white, oBrush;

public:
	tileMap();
	~tileMap();

	HRESULT init();
	void update();
	void release();

	void setTileMap(int tileSizeX, int tileSizeY);								//�� ��������� �迭�� �Ҵ�, �ʱ�ȭ�մϴ�
	void addTileMapIamge(char *imageName);										//Ÿ�ϸʿ� �̹����� �߰��մϴ�
	void deleteTileMapImage();													//Ÿ�ϸʿ� �̹����� �����մϴ�

	void setTile(TagTile_TERRAIN btileMap, int x, int y, int num);				//Ÿ���� ��ü�մϴ�
	void addObject(TagTile_Object *tileObject);									//������Ʈ�� �߰��մϴ�
	void deleteObject(HDC hdc, int num);										//������Ʈ�� �����մϴ�
	void clearObject();															//������Ʈ�� ��ü �����մϴ�

	bool getIsTerrain(int x, int y) { return _tileMap[y][x].isTerrain; };
	bool getIsObject(int x, int y) { return _tileMap[y][x].isObject; };
	bool getIsShader(int x, int y) { return _tileMap[y][x].isShader; };

	bool getIsImage() { return _isTileMapImage; };
	void setIsImage(bool isImage) { _isTileMapImage = isImage; };

	string getImagePath() { return _tileMapImagePath; };
	void setImagePath(string temp) { _tileMapImagePath = temp; };


	//render����
	void screenRenderTileMap(HDC hdc, int cameraX, int cameraY);				//Ÿ�ϸ��� ȭ�鸸ŭ�� �ٽ� �׷��ݴϴ�
	void reDrawTileMap(HDC hdc);												//Ÿ�ϸ��� �Ϻκ��� �ٽ� �׷��ݴϴ�(ĳ���� �̵��� ���)
	void reDrawTileMap_tile(HDC hdc, RECT rc);
	void reDrawTileMap(HDC hdc, int tileX, int tileY, int sizeX, int sizeY, bool isObject);	//Ÿ�ϸ��� �Ϻκ��� �ٽ� �׷��ݴϴ�(������ ���)
	void allRenderTileMap(HDC hdc, int num);									//Ÿ�ϸ� ��ü�� �ٽ� �׷��ݴϴ�
	void debugRenderTileMap(HDC hdc, int cameraX, int cameraY);					//Ÿ�� ��ȣ�� �׷��ݴϴ�
	void attributeRenderTileMap(HDC hdc);										//Ÿ�� �Ӽ��� �׷��ݴϴ�
	void attributeRenderTileMap(HDC hdc, int x, int y);							//Ÿ�� �Ӽ��� �׷��ݴϴ�

	void attributeRenderRectSelect(HDC hdc, TagTile_TERRAIN tile);				//�Ӽ��� �Ǵ��� ��Ʈ�� �Ӽ��� �´� ������ �׷��ݴϴ�

	POINT getTileMapSize() { return POINT{ _maxTileX,_maxTileY }; };			//Ÿ�ϸ� ������ ��ȯ
	bTileMap getTileMap() { return _tileMap; };
	TagTile_TERRAIN getTileMap(int x, int y) { return _tileMap[y][x]; };
	vTileObject getTileObject() { return _tileObject; };
	TagTile_Object *getTileObject(int num) { return _tileObject[num]; };

	TILE_TERRAINKIND kindSelectTerrain(int index, int frameX, int frameY);		//Ÿ���� ������ �������ִ� �Լ�
	void setKindTerrian(TILE_TERRAINKIND kind, int x, int y) { _tileMap[y][x].tile_terrainKind = kind; };
	TILE_TERRAINKIND getKindTerrian(int x, int y) { return _tileMap[y][x].tile_terrainKind; };

	void kindSelectObject(TagTile_Object *object, int index);					//������Ʈ�� ������ Ư���� �������ִ� �Լ�
	void setKindObject(TILE_OBJECTKIND kind, int num) { _tileObject[num]->tile_objectKind = kind; };
	TILE_OBJECTKIND getKindObject(int num) { return _tileObject[num]->tile_objectKind; };

	void setTileImage(int x, int y, int num, const char *keyName);
	void setObjectFrame(int num, int frameX, int frameY);

	void setObjectHp(int i, int x) { _tileObject[i]->hp = x; };
};

