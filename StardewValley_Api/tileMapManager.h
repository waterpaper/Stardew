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

	vSampleTileMapString _vSampleTileMapString_terrian;											//�ٴ� ���ø� �̹��� Ű���� ������ �մ� ����
																								//�ε峪 ����, �߰��� �̰��� �̿��Ѵ�

	vSampleTileMapString _vSampleTileMapString_object;											//������Ʈ ���ø� �̹��� Ű���� ������ �մ� ����

	int _minimapX, _minimapY;																	//�̴ϸ� ������

	HANDLE file;																				//���̺�, �ε��� ���� ����
	DWORD write;
	DWORD read;

public:
	tileMapManager();
	~tileMapManager();

	HRESULT init();
	HRESULT init(int x, int y);
	void render(HDC hdc);
	void allRender();
	void tileNumRender(int num);																//�ش� �迭���� �ҷ����� ����
	void attributeRender();																		//�ش� �迭���� �ҷ����� ����
	void reDrawMoveRender(HDC hdc);
	void reDrawRender(int startX, int startY, int endX, int endY);
	void reDrawTileMap_tileNpc(HDC hdc);
	void update();
	void release();

	//Ÿ�ϸ� ����
	//��ü Ÿ�ϸ��� ������ϰ� ����� �����մϴ�
	void tileMapSetting(int sizeX, int sizeY);

	POINT getTileMapSize() { return _tileMap->getTileMapSize(); };
	void setTileMapSize(POINT mapSize) { tileMapSetting(mapSize.x, mapSize.y); };

	void addTileMapIamge(char *imageName);														//Ÿ�ϸʿ� �̹����� �߰��մϴ�
	void deleteTileMapImage() { _tileMap->deleteTileMapImage(); };								//Ÿ�ϸʿ� �̹����� �����մϴ�

	tileMap getTileMap() { return *_tileMap; };
	void setTileMap(tileMap tilemap);
	void setTile(TagTile_TERRAIN tile, int x, int y, int num);									//Ÿ�ϸʿ� Ÿ���� �����մϴ�
	void setTile(TagTile_TERRAIN tile, int x, int y, POINT frameStart, POINT frameEnd, int num);//Ÿ�ϸʿ� Ÿ���� �����մϴ�
	void addObject(TagTile_Object *object);														//Ÿ�ϸʿ� ������Ʈ�� �߰��մϴ�
	void deleteObject(int num);																	//Ÿ�ϸʿ� ������Ʈ�� �����մϴ�

	void initTileMap();																			//Ÿ�ϸ��� �ʱ�ȭ�մϴ�

	TILE_TERRAINKIND getTileMapAttribute(int x, int y) { return _tileMap->getKindTerrian(x, y); };				//�Ӽ����� �������ų� �����մϴ�
	void setTileMapAttribute(int x, int y, TILE_TERRAINKIND kind);
	bool getIsTerrain(int x, int y) { return _tileMap->getIsTerrain(x, y); };
	bool getIsObject(int x, int y) { return _tileMap->getIsObject(x, y); };

	//�̴ϸ�
	void minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY);		//�̴ϸʷ���

	void setMinimapSize(POINT mapSize);

	int getMinimapX() { return _minimapX; };
	int	getMinimapY() { return _minimapY; };

	//Ÿ�ϸ��� ������ �����մϴ�
	void loadTileMapIamge(const char *fileName, INGAMESCENE_NAME sceneName);
	void saveTileMapIamge(char *fileName);

	//Ÿ�ϸ��� ����� �̹������� Ű���� ���� ����
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

