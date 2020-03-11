#pragma once
#include "farm.h"
#include "singletonBase.h"

class farmManager:public singletonBase<farmManager>
{
private:
	farm _farm;
	bool _isFirst;

public:
	farmManager();
	~farmManager();

	HRESULT init();
	void update();
	void render(HDC hdc);
	void render(HDC hdc, int x, int y);
	void release();

	void farmClear() { _farm.farmClear(); };

	void setFarmMap(tileMap tilemap);
	void setFarmLand(int x, int y, farmland farmlandTemp) { _farm.setFarmLand(x,y, farmlandTemp); };
	tileMap getFarmMap() { return _farm.getTileMap(); };
	vFarmland getFarmLand() { return _farm.getFarmLand(); };

	void setHoeingField(int x, int y);
	void setWateringField(int x, int y);
	bool setSeedField(int x, int y, SEEDKIND kind);

	void growCrops();

	bool getIsFirst() { return _isFirst; };
	void setIsFirst(bool isBool) { _isFirst = isBool; };

	bool getHoeing(int x, int y) { return _farm.getHoeing(x,y); };
	bool getWatering(int x, int y) { return _farm.getWatering(x,y); };
	bool getCrops(int x, int y) { return _farm.getCrops(x,y); };
	void setHoeing(int x, int y, bool isBool) { _farm.setHoeing(x,y,isBool); };
	void setWatering(int x, int y, bool isBool) { _farm.setWatering(x, y, isBool); };
	void setCrops(int x, int y, bool isBool) { _farm.setCrops(x, y, isBool); };

	bool getIsHarvesting(int x, int y);
	void harvesting(int x, int y);
	int getHoeingFieldNum() { return _farm.getHoeingFieldNum(); };
};

