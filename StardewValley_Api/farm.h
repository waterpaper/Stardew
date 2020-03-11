#pragma once
#include "tileMap.h"

struct object_crops
{
	image *img;
	POINT frame;

	CROPSKIND kind;
	int sellValue;
	
	int period;
	int max_Period;

	bool isHarvesting;
};

struct farmland
{
	int x, y, width, height;
	RECT rc;
	image *img;
	POINT frame;

	bool isHoeing;
	bool isCrops;
	bool isWatering;

	object_crops crops;
};
typedef vector< vector<farmland>> vFarmland;

class farm
{
	/*
	������ ���¸� �����ϴ� Ŭ���� �Դϴ�
	Ÿ�ϸʰ� ������ ũ�⿡ ������ ����� ������� ����մϴ�
	���� ����ũ�⸸ŭ�� �������͸� �����
	���� �����ϰ� ����ҽ� 1:1�� �����Ǵ� ���Ϳ� ����, ����մϴ�
	*/

private:
	tileMap _farmTile;
	vFarmland _farmland;

	int _farmLandNum;
	int _maxTileX, _maxTileY;

public:
	farm();
	~farm();

	HRESULT init();
	void update();
	void render(HDC hdc);
	void render(HDC hdc, int x, int y);
	void release();

	void farmClear();
	void farmlandClear();

	tileMap getTileMap() { return _farmTile; };
	vFarmland getFarmLand() { return _farmland; };
	void setTileMap(tileMap tilemap);
	void setFarmLand(int x, int y,farmland farmlandTemp);
	void growCrops();
	int setCropsFrame(int period, CROPSKIND kind);
	int getHoeingFieldNum() { return _farmLandNum; };


	void setHoeingField(int x, int y);
	void setHoeingFieldFrame(int x, int y, int stack);
	void setWateringField(int x, int y);
	void setSeedField(int x, int y, SEEDKIND kind);

	bool getHoeing(int x, int y) { return _farmland[y][x].isHoeing; };
	bool getWatering(int x, int y) { return _farmland[y][x].isWatering; };
	bool getCrops(int x, int y) { return _farmland[y][x].isCrops; };
	bool getIsHarvesting(int x, int y) { 
		if (!_farmland[y][x].isHoeing)	return false;
		if (!_farmland[y][x].isCrops)	return false;
		return _farmland[y][x].crops.isHarvesting;
	};

	void setHoeing(int x, int y, bool isBool) { _farmland[y][x].isHoeing = isBool; };
	void setWatering(int x, int y, bool isBool) { _farmland[y][x].isWatering = isBool; };
	void setCrops(int x, int y, bool isBool) { _farmland[y][x].isCrops = isBool; };

	void harvesting(int x, int y);
};

