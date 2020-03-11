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
	농장의 상태를 저장하는 클래스 입니다
	타일맵과 동일한 크기에 농장을 만들어 저장시켜 사용합니다
	또한 농장크기만큼의 농지벡터를 만들어
	땅을 개간하고 사용할시 1:1로 대응되는 벡터에 저장, 사용합니다
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

