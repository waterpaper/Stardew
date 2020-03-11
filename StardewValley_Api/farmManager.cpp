#include "stdafx.h"
#include "farmManager.h"


farmManager::farmManager()
{
}


farmManager::~farmManager()
{
}

HRESULT farmManager::init()
{
	_isFirst = true;
	_farm.init();

	return S_OK;
}

void farmManager::update()
{
}

void farmManager::render(HDC hdc)
{
	_farm.render(hdc);
}

void farmManager::render(HDC hdc, int x, int y)
{
	_farm.render(hdc, x, y);
}

void farmManager::release()
{
	_farm.release();
}

void farmManager::setFarmMap(tileMap tilemap)
{
	_farm.setTileMap(tilemap);
}

void farmManager::setHoeingField(int x, int y)
{
	/*
	호미질 한 땅의 프레임을 결정해줍니다
	주변의 땅을 비교한 후 모양을 결정합니다
	*/

	_farm.setHoeingField(x, y);
}

void farmManager::setWateringField(int x, int y)
{
	_farm.setWateringField(x, y);
}

bool farmManager::setSeedField(int x, int y, SEEDKIND kind)
{
	if (_farm.getHoeing(x, y) && !_farm.getCrops(x, y))
	{
		_farm.setSeedField(x, y, kind);
		TILEMAPMANAGER->reDrawRender(x,y,1,1);

		return true;
	}

	return false;
}

void farmManager::growCrops()
{
	_farm.growCrops();
}

bool farmManager::getIsHarvesting(int x, int y)
{
	return _farm.getIsHarvesting(x,y);
}

void farmManager::harvesting(int x, int y)
{
	_farm.harvesting(x,y);
}
