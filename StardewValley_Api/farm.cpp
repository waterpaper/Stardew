#include "stdafx.h"
#include "farm.h"


farm::farm()
{
}


farm::~farm()
{
}

HRESULT farm::init()
{
	vector<farmland> vtemp;
	farmland temp;
	object_crops objTemp;

	_farmLandNum = 0;

	_farmTile.setTileMap(100, 100);

	objTemp.img = nullptr;
	objTemp.kind = CROPSKIND::CROPSKIND_NULL;
	objTemp.period = 0;
	objTemp.max_Period = 0;
	objTemp.sellValue = 0;
	objTemp.frame = POINT{ 0,0 };
	objTemp.isHarvesting = false;
	temp.crops = objTemp;
	temp.height = 48;
	temp.width = 48;
	temp.frame = POINT{ 0,0 };
	temp.isHoeing = false;
	temp.isCrops = false;
	temp.isWatering = false;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			temp.x = j;
			temp.y = i;
			temp.rc = RectMake(j*(TILE_SIZE_X), i*(TILE_SIZE_Y), 48, 48);

			vtemp.push_back(temp);
		}
		_farmland.push_back(vtemp);
		vtemp.clear();
	}

	return S_OK;
}

void farm::update()
{

}

void farm::render(HDC hdc)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (_farmland[i][j].isHoeing || _farmland[i][j].img == nullptr)	continue;

			_farmland[i][j].img->frameRender(hdc, _farmland[i][j].rc.left, _farmland[i][j].rc.top);


			if (!_farmland[i][j].isCrops)	continue;

			_farmland[i][j].crops.img->frameRender(hdc, _farmland[i][j].rc.left, _farmland[i][j].rc.top - 48);
		}
	}
}

void farm::render(HDC hdc, int x, int y)
{
	if (!_farmland[y][x].isHoeing || _farmland[y][x].img == nullptr)	return;

	_farmland[y][x].img->frameRender(hdc, _farmland[y][x].rc.left, _farmland[y][x].rc.top, _farmland[y][x].frame.x, _farmland[y][x].frame.y);


	if (!_farmland[y][x].isCrops)	return;

	_farmland[y][x].crops.img->frameRender(hdc, _farmland[y][x].rc.left, _farmland[y][x].rc.top - 48, _farmland[y][x].crops.frame.x, _farmland[y][x].crops.frame.y);
}

void farm::release()
{
	_farmTile.release();
}

void farm::farmClear()
{
	_farmTile.setTileMap(100, 100);
	farmlandClear();
	_farmLandNum = 0;

}

void farm::farmlandClear()
{
	object_crops objTemp;

	for (int i = 0; i <100 ; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			objTemp.img = nullptr;
			objTemp.kind = CROPSKIND::CROPSKIND_NULL;
			objTemp.period = 0;
			objTemp.max_Period = 0;
			objTemp.sellValue = 0;
			objTemp.frame = POINT{ 0,0 };
			objTemp.isHarvesting = false;
			_farmland[i][j].crops = objTemp;
			_farmland[i][j].height = 48;
			_farmland[i][j].width = 48;
			_farmland[i][j].frame = POINT{ 0,0 };
			_farmland[i][j].isHoeing = false;
			_farmland[i][j].isCrops = false;
			_farmland[i][j].isWatering = false;
			_farmland[i][j].img = nullptr;
		}
	}
}

void farm::setTileMap(tileMap tilemap)
{
	/*
	농장의 데이터를 저장해둔다
	*/
	POINT size = tilemap.getTileMapSize();
	bTileMap bTilemap = tilemap.getTileMap();
	vTileObject vTileobj = tilemap.getTileObject();
	TagTile_TERRAIN tile;
	TagTile_Object *object;

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			tile.isObject = bTilemap[i][j].isObject;
			tile.isShader = bTilemap[i][j].isShader;
			tile.isTerrain = bTilemap[i][j].isTerrain;
			tile.tileNum = bTilemap[i][j].tileNum;
			for (int n = 0; n < 3; n++)
			{
				tile.imageIndex[n] = bTilemap[i][j].imageIndex[n];
				tile.tileFrame[n] = bTilemap[i][j].tileFrame[n];
				tile.tileTerrainImg[n] = bTilemap[i][j].tileTerrainImg[n];
				_farmTile.setTile(tile, j, i, n);
			}
			_farmTile.setKindTerrian(bTilemap[i][j].tile_terrainKind,j,i);
		}
	}
	_farmTile.clearObject();

	for (int i = 0; i < vTileobj.size(); i++)
	{
		object = new TagTile_Object;
		object->imageIndex = vTileobj[i]->imageIndex;
		object->objectFrame = vTileobj[i]->objectFrame;
		object->objectCollisionRc = vTileobj[i]->objectCollisionRc;
		object->objectPos = vTileobj[i]->objectPos;
		object->objectTotalRc = vTileobj[i]->objectTotalRc;
		object->sizeX = vTileobj[i]->sizeX;
		object->sizeY = vTileobj[i]->sizeY;
		object->tileObjectImg = vTileobj[i]->tileObjectImg;
		object->tile_objectKind = vTileobj[i]->tile_objectKind;

		_farmTile.addObject(object);
		object = nullptr;
	}
}

void farm::setFarmLand(int x, int y, farmland farmlandTemp)
{
	object_crops objTemp;

	objTemp.img = IMAGEMANAGER->findImage("오브젝트_농작물");
	objTemp.kind = farmlandTemp.crops.kind;
	objTemp.period = farmlandTemp.crops.period;
	objTemp.max_Period = farmlandTemp.crops.max_Period;
	objTemp.sellValue = farmlandTemp.crops.sellValue;
	objTemp.frame = POINT{ farmlandTemp.crops.frame.x,farmlandTemp.crops.frame.y };
	objTemp.isHarvesting = farmlandTemp.crops.isHarvesting;
	_farmland[y][x].crops = objTemp;
	_farmland[y][x].height = 48;
	_farmland[y][x].width = 48;
	_farmland[y][x].frame = POINT{ farmlandTemp.frame.x,farmlandTemp.frame.y };
	_farmland[y][x].isHoeing = farmlandTemp.isHoeing;
	_farmland[y][x].isCrops = farmlandTemp.isCrops;
	_farmland[y][x].isWatering = false;
	_farmland[y][x].img = IMAGEMANAGER->findImage("타일_농지");

	_farmLandNum++;
}

void farm::growCrops()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (!_farmland[i][j].isHoeing)		continue;
			if (!_farmland[i][j].isWatering)		continue;

			_farmland[i][j].isWatering = false;
			_farmland[i][j].frame.x -= 4;

			if (!_farmland[i][j].isCrops)
			{
				TILEMAPMANAGER->reDrawRender(j, i, 1, 1);
				continue;
			}
			_farmland[i][j].crops.period += 1;
			if (_farmland[i][j].crops.max_Period <= _farmland[i][j].crops.period)
			{
				_farmland[i][j].crops.period = _farmland[i][j].crops.max_Period;
				_farmland[i][j].crops.frame.x = setCropsFrame(_farmland[i][j].crops.period, _farmland[i][j].crops.kind);
				_farmland[i][j].crops.isHarvesting = true;
			}
			else
			{
				_farmland[i][j].crops.frame.x = setCropsFrame(_farmland[i][j].crops.period, _farmland[i][j].crops.kind);
			}
			TILEMAPMANAGER->reDrawRender(j,i,1,1);
		}
	}
}

int farm::setCropsFrame(int period, CROPSKIND kind)
{
	if (kind == CROPSKIND::CROPSKIND_SPRING_PARSNIP)
	{
		if (period != 4)
		{
			return period + 1;
		}
		else
		{
			return 5;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SPRING_GREENBEAN)
	{
		if (period != 10)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SPRING_CAULIFLOWER)
	{
		if (period != 12)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SPRING_POTATO)
	{
		if (period != 6)
		{
			if (period > 5)
			{
				return 5;
			}
			return period;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SPRING_KALE)
	{
		if (period != 6)
		{
			if (period > 4)
			{
				return 4;
			}
			return period - 1;
		}
		else
		{
			return 5;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SUMMER_RADISH)
	{
		if (period != 6)
		{
			if (period > 5)
			{
				return 5;
			}
			return period;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SUMMER_MELON)
	{
		if (period != 12)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SUMMER_TOMATO)
	{
		if (period != 11)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SUMMER_BLUEBERRY)
	{
		if (period != 13)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_SUMMER_HOTPEPPER)
	{
		if (period != 5)
		{
			if (period > 5)
			{
				return 5;
			}
			return period;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_FALL_EGGPLANT)
	{
		if (period != 5)
		{
			if (period > 5)
			{
				return 5;
			}
			return period;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_FALL_PUMPKIN)
	{
		if (period != 13)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_FALL_CRANBERRY)
	{
		if (period != 7)
		{
			if (period > 5)
			{
				return 5;
			}
			return period - 1;
		}
		else
		{
			return 6;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_FALL_BOKCHOY)
	{
		if (period != 4)
		{
			if (period > 4)
			{
				return 4;
			}
			return period;
		}
		else
		{
			return 5;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_FALL_YAM)
	{
		if (period != 10)
		{
			if (period > 4)
			{
				return 4;
			}
			return period - 1;
		}
		else
		{
			return 5;
		}
	}
	else if (kind == CROPSKIND::CROPSKIND_TREE_CHERRY|| kind == CROPSKIND::CROPSKIND_TREE_APRICOT|| kind == CROPSKIND::CROPSKIND_TREE_ORANGE
	|| kind == CROPSKIND::CROPSKIND_TREE_PEACH|| kind == CROPSKIND::CROPSKIND_TREE_POMEGRANATE|| kind == CROPSKIND::CROPSKIND_TREE_APPLE)
	{
		if (period <7)
		{
			return 0;
		}
		else if (period < 14)
		{
			return 1;
		}
		else if (period < 21)
		{
			return 2;
		}
		else if (period < 28)
		{
			return 3;
		}

		return 4;
	}
	else if (kind == CROPSKIND::CROPSKIND_LAWN)
	{
	}
}

void farm::setHoeingField(int x, int y)
{
	_farmland[y][x].isHoeing = true;
	_farmland[y][x].img = IMAGEMANAGER->findImage("타일_농지");
	setHoeingFieldFrame(x, y, 0);
	EFFECTMANAGER->play("이펙트_호미질", _farmland[y][x].rc.left+24, _farmland[y][x].rc.top+24);

	_farmLandNum += 1;

	_sound.effSoundPlay("");
}

void farm::setHoeingFieldFrame(int x, int y, int stack)
{
	/*
	농지의 모양을 정해준다
	주변 타일의 모양을 보고 정하게 된다
	*/
	if (stack > 1)	return;

	//4방향 다 없을시
	if (!_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		_farmland[y][x].frame = POINT{ 0, 0 };
	}
	//1개만 존재시
	else if (_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//위만 존재시
		_farmland[y][x].frame = POINT{ 0, 3 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y - 1, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//아래만 존재시
		_farmland[y][x].frame = POINT{ 0, 1 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//왼쪽만 존재시
		_farmland[y][x].frame = POINT{ 3, 3 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 1, 3 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	//여기부터는 2개 존재시 입니다
	else if (_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//위,왼쪽만 존재시
		_farmland[y][x].frame = POINT{ 3, 2 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}
	else if (_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//위, 오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 1, 2 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	else if (_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//위, 아래만 존재시
		_farmland[y][x].frame = POINT{ 0, 2 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x, y + 1, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//아래, 왼쪽만 존재시
		_farmland[y][x].frame = POINT{ 3, 0 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//아래 ,오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 1, 0 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//왼쪽 ,오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 2, 3 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x - 1, y, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	//여기서부터는 3개방향이 존재시 입니다
	else if (_farmland[y - 1][x].isHoeing && !_farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//위,왼쪽, 오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 2, 2 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	else if (!_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//아래, 왼쪽, 오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 2, 0 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}
	else if (_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && !_farmland[y][x + 1].isHoeing)
	{
		//위, 아래, 왼쪽만 존재시
		_farmland[y][x].frame = POINT{ 3, 1 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}
	else if (_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && !_farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		//위, 아래 ,오른쪽만 존재시
		_farmland[y][x].frame = POINT{ 1, 1 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
		}
	}
	//4방향이 다 존재할 경우입니다
	else if (_farmland[y - 1][x].isHoeing && _farmland[y + 1][x].isHoeing && _farmland[y][x - 1].isHoeing && _farmland[y][x + 1].isHoeing)
	{
		_farmland[y][x].frame = POINT{ 2, 1 };
		if (stack < 1)
		{
			setHoeingFieldFrame(x, y + 1, stack + 1);
			setHoeingFieldFrame(x, y - 1, stack + 1);
			setHoeingFieldFrame(x + 1, y, stack + 1);
			setHoeingFieldFrame(x - 1, y, stack + 1);
		}
	}

	if (_farmland[y][x].isWatering)
	{
		_farmland[y][x].frame.x += 4;
	}

	TILEMAPMANAGER->reDrawRender(x, y, 1, 1);
}

void farm::setWateringField(int x, int y)
{
	_farmland[y][x].isWatering = true;
	_farmland[y][x].frame.x += 4;

	TILEMAPMANAGER->reDrawRender(x, y-1, 1, 3);
	EFFECTMANAGER->play("이펙트_물", _farmland[y][x].rc.left + 24, _farmland[y][x].rc.top + 24);
}


void farm::setSeedField(int x, int y, SEEDKIND kind)
{
	object_crops temp;
	temp.img = IMAGEMANAGER->findImage("오브젝트_농작물");
	temp.kind = (CROPSKIND)kind;
	temp.isHarvesting = false;

	if (temp.kind == CROPSKIND::CROPSKIND_SPRING_PARSNIP)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 4;
		temp.sellValue = 35;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SPRING_GREENBEAN)
	{
		temp.frame = POINT{ 0,1 };
		temp.period = 1;
		temp.max_Period = 10;
		temp.sellValue = 40;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SPRING_CAULIFLOWER)
	{
		temp.frame = POINT{ 0,2 };
		temp.period = 1;
		temp.max_Period = 12;
		temp.sellValue = 175;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SPRING_POTATO)
	{
		temp.frame = POINT{ 0,3 };
		temp.period = 1;
		temp.max_Period = 6;
		temp.sellValue = 80;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SPRING_KALE)
	{
		temp.frame = POINT{ 0,4 };
		temp.period = 1;
		temp.max_Period = 6;
		temp.sellValue = 110;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SUMMER_RADISH)
	{
		temp.frame = POINT{ 0,5 };
		temp.period = 1;
		temp.max_Period = 6;
		temp.sellValue = 90;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SUMMER_MELON)
	{
		temp.frame = POINT{ 0,6 };
		temp.period = 1;
		temp.max_Period = 12;
		temp.sellValue = 250;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SUMMER_TOMATO)
	{
		temp.frame = POINT{ 0,7 };
		temp.period = 1;
		temp.max_Period = 11;
		temp.sellValue = 60;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SUMMER_BLUEBERRY)
	{
		temp.frame = POINT{ 0,8 };
		temp.period = 1;
		temp.max_Period = 13;
		temp.sellValue = 50;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_SUMMER_HOTPEPPER)
	{
		temp.frame = POINT{ 0,9 };
		temp.period = 1;
		temp.max_Period = 5;
		temp.sellValue = 40;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_FALL_EGGPLANT)
	{
		temp.frame = POINT{ 0,10 };
		temp.period = 1;
		temp.max_Period = 5;
		temp.sellValue = 60;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_FALL_PUMPKIN)
	{
		temp.frame = POINT{ 0,11 };
		temp.period = 1;
		temp.max_Period = 13;
		temp.sellValue = 320;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_FALL_CRANBERRY)
	{
		temp.frame = POINT{ 0,12 };
		temp.period = 1;
		temp.max_Period = 7;
		temp.sellValue = 75;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_FALL_BOKCHOY)
	{
		temp.frame = POINT{ 0,13 };
		temp.period = 1;
		temp.max_Period = 4;
		temp.sellValue = 80;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_FALL_YAM)
	{
		temp.frame = POINT{ 0,14 };
		temp.period = 1;
		temp.max_Period = 10;
		temp.sellValue = 160;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_CHERRY)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 28;
		temp.sellValue = 50;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_APRICOT)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 28;
		temp.sellValue = 80;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_ORANGE)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 28;
		temp.sellValue = 100;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_PEACH)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 28;
		temp.sellValue = 140;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_POMEGRANATE)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 10;
		temp.sellValue = 100;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_TREE_APPLE)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 28;
		temp.sellValue = 140;
	}
	else if (temp.kind == CROPSKIND::CROPSKIND_LAWN)
	{
		temp.frame = POINT{ 0,0 };
		temp.period = 1;
		temp.max_Period = 1;
		temp.sellValue = 20;
	}

	_farmland[y][x].crops = temp;
	_farmland[y][x].isCrops = true;
}

void farm::harvesting(int x, int y)
{
	item *itemTemp;

	if (_farmland[y][x].isCrops &&_farmland[y][x].crops.isHarvesting)
	{
		if (!INVENTORYMANAGER->getIsInventoryFull())
		{
			itemTemp = new item_crops();
			itemTemp->init(_farmland[y][x].crops.kind);

			INVENTORYMANAGER->addItem(*itemTemp);
			UIMANAGER->addAddItemUi(*itemTemp);
			
			delete(itemTemp);
			itemTemp = nullptr;

			_farmland[y][x].isCrops = false;
			_farmland[y][x].crops.frame = POINT{0,0};
			_farmland[y][x].crops.img = nullptr;
			_farmland[y][x].crops.isHarvesting = false;
			_farmland[y][x].crops.kind = CROPSKIND::CROPSKIND_NULL;
			_farmland[y][x].crops.max_Period = 0;
			_farmland[y][x].crops.period = 0;
			_farmland[y][x].crops.sellValue = 0;

			TILEMAPMANAGER->reDrawRender(x,y-1,1,3);
			EFFECTMANAGER->play("이펙트_수확", _farmland[y][x].rc.left+24, _farmland[y][x].rc.top + 24-48);
		}
		else
		{
			//가득참 문구
		}
	}
}
