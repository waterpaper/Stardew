#include "stdafx.h"
#include "animalManager.h"


animalManager::animalManager()
{
}


animalManager::~animalManager()
{
}

HRESULT animalManager::init()
{
	return S_OK;
}

void animalManager::update()
{
	INGAMESCENE_NAME temp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_BARN)
	{
		barnUpdate();
		animalMove();
	}
	else if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_COOP)
	{
		coopUpdate();
		animalMove();
	}
}

void animalManager::render(HDC hdc)
{
	INGAMESCENE_NAME temp =(INGAMESCENE_NAME) SCENEMANAGER->getIngameName();
	if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_BARN)
	{
		barnRender(hdc);
	}
	else if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_COOP)
	{
		coopRender(hdc);
	}
}

void animalManager::release()
{
	vector<animal> temp, temp2;

	_vCoopAnimal.swap(temp);
	temp.clear();
	_vBarnAnimal.swap(temp2);
	temp2.clear();
}

void animalManager::clearAnimal()
{
	release();
}

void animalManager::addAnimal(ANIMAL_KIND animalkind, int period)
{
	animal animalTemp;

	if (animalkind == ANIMAL_KIND::ANIMAL_KIND_CHICKEN|| animalkind == ANIMAL_KIND::ANIMAL_KIND_DUCK|| animalkind == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
	{
		animalTemp.init(animalkind, period);

		_vCoopAnimal.push_back(animalTemp);
	}
	else
	{
		animalTemp.init(animalkind, period);

		_vBarnAnimal.push_back(animalTemp);
	}
}

void animalManager::barnUpdate()
{
	for (int i = 0; i < _vBarnAnimal.size(); i++)
	{
		_vBarnAnimal[i].update();
	}
}

void animalManager::barnRender(HDC hdc)
{
	for (int i = 0; i < _vBarnAnimal.size(); i++)
	{
		_vBarnAnimal[i].render(hdc);
	}
}

void animalManager::coopUpdate()
{
	for (int i = 0; i < _vCoopAnimal.size(); i++)
	{
		_vCoopAnimal[i].update();
	}
}

void animalManager::coopRender(HDC hdc)
{
	for (int i = 0; i < _vCoopAnimal.size(); i++)
	{
		_vCoopAnimal[i].render(hdc);
	}
}

void animalManager::nextDay()
{
	for (int i = 0; i < _vBarnAnimal.size(); i++)
	{
		_vBarnAnimal[i].setLifePeriod(_vBarnAnimal[i].getLifePeriod()+1);
		_vBarnAnimal[i].setIsDayProduction(true);
	}
	for (int i = 0; i < _vCoopAnimal.size(); i++)
	{
		_vCoopAnimal[i].setLifePeriod(_vCoopAnimal[i].getLifePeriod() + 1);
		_vCoopAnimal[i].setIsDayProduction(true);
	}
}

void animalManager::barnGetItem(int num)
{
	item *itemTemp;
	ANIMAL_KIND kindTemp = _vBarnAnimal[num].getKind();

	if(kindTemp== ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_EGG);
		_sound.effSoundPlay("닭");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_COW)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_MILK);
		_sound.effSoundPlay("소");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_GOAT)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_GOATMILK);
		_sound.effSoundPlay("젖소");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_DUCK)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_DUCKEGG);
		_sound.effSoundPlay("오리");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_WOOL);
		_sound.effSoundPlay("양");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_PIG)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_TRUFFLE);
		_sound.effSoundPlay("돼지");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_RABBITFOOT);
		_sound.effSoundPlay("토끼");
	}
	else
	{
		return;
	}

	if (INVENTORYMANAGER->getIsInventoryFull())
	{
		if (INVENTORYMANAGER->findItem(itemTemp->getItemName()))
		{
			_vBarnAnimal[num].setIsDayProduction(false);
			UIMANAGER->addAddItemUi(*itemTemp);
			INVENTORYMANAGER->addItem(*itemTemp);
		}
		else
		{
			UIMANAGER->setFullInventory();
		}
	}
	else
	{
		UIMANAGER->addAddItemUi(*itemTemp);
		INVENTORYMANAGER->addItem(*itemTemp);
		_vBarnAnimal[num].setIsDayProduction(false);
	}

	itemTemp = nullptr;
}

void animalManager::coopGetItem(int num)
{
	item *itemTemp;
	ANIMAL_KIND kindTemp = _vCoopAnimal[num].getKind();

	if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_EGG);
		_sound.effSoundPlay("닭");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_COW)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_MILK);
		_sound.effSoundPlay("소");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_GOAT)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_GOATMILK);
		_sound.effSoundPlay("젖소");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_DUCK)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_DUCKEGG);
		_sound.effSoundPlay("오리");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_WOOL);
		_sound.effSoundPlay("양");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_PIG)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_TRUFFLE);
		_sound.effSoundPlay("돼지");
	}
	else if (kindTemp == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
	{
		itemTemp = new item_animalitem();
		itemTemp->init(ANIMALITEMKIND::ANIMALITEMKIND_RABBITFOOT);
		_sound.effSoundPlay("토끼");
	}
	else
	{
		return;
	}

	if (INVENTORYMANAGER->getIsInventoryFull())
	{
		if (INVENTORYMANAGER->findItem(itemTemp->getItemName()))
		{
			_vCoopAnimal[num].setIsDayProduction(false);
			INVENTORYMANAGER->addItem(*itemTemp);
			UIMANAGER->addAddItemUi(*itemTemp);
		}
		else
		{
			UIMANAGER->setFullInventory();
		}
	}
	else
	{
		INVENTORYMANAGER->addItem(*itemTemp);
		_vCoopAnimal[num].setIsDayProduction(false);
		UIMANAGER->addAddItemUi(*itemTemp);
	}

	itemTemp = nullptr;
}

void animalManager::animalMove()
{
	/*
	애니멀들의 다음 위치를 검사해 이동이 가능하면 이동시키고 아니면 움직이지 않게 한다

	*/
	INGAMESCENE_NAME temp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	RECT nextRc;

	if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_BARN)
	{
		for (int i = 0; i < _vBarnAnimal.size();i++)
		{
			if (_vBarnAnimal[i].getActing() == ANIMAL_ACTING::ANIMAL_ACTING_MOVE)
			{
				if (_vBarnAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_DOWN)
				{
					nextRc = RectMakeCenter(_vBarnAnimal[i].getPositionX(), _vBarnAnimal[i].getPositionY()+ _vBarnAnimal[i].getSpeed(), _vBarnAnimal[i].getWidth(), _vBarnAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vBarnAnimal[i].setPositionY(_vBarnAnimal[i].getPositionY() + _vBarnAnimal[i].getSpeed());
					}
				}
				else if(_vBarnAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_RIGHT)
				{
					nextRc = RectMakeCenter(_vBarnAnimal[i].getPositionX() + _vBarnAnimal[i].getSpeed(), _vBarnAnimal[i].getPositionY(), _vBarnAnimal[i].getWidth(), _vBarnAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vBarnAnimal[i].setPositionX(_vBarnAnimal[i].getPositionX() + _vBarnAnimal[i].getSpeed());
					}
				}
				else if (_vBarnAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_UP)
				{
					nextRc = RectMakeCenter(_vBarnAnimal[i].getPositionX(), _vBarnAnimal[i].getPositionY() - _vBarnAnimal[i].getSpeed(), _vBarnAnimal[i].getWidth(), _vBarnAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vBarnAnimal[i].setPositionY(_vBarnAnimal[i].getPositionY() - _vBarnAnimal[i].getSpeed());
					}
				}
				else if (_vBarnAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_LEFT)
				{
					nextRc = RectMakeCenter(_vBarnAnimal[i].getPositionX() - _vBarnAnimal[i].getSpeed(), _vBarnAnimal[i].getPositionY(), _vBarnAnimal[i].getWidth(), _vBarnAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vBarnAnimal[i].setPositionX(_vBarnAnimal[i].getPositionX() - _vBarnAnimal[i].getSpeed());
					}
				}
			}
		}
	}
	else if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_COOP)
	{
		for (int i = 0; i < _vCoopAnimal.size(); i++)
		{
			if (_vCoopAnimal[i].getActing() == ANIMAL_ACTING::ANIMAL_ACTING_MOVE)
			{
				if (_vCoopAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_DOWN)
				{
					nextRc = RectMakeCenter(_vCoopAnimal[i].getPositionX(), _vCoopAnimal[i].getPositionY() + _vCoopAnimal[i].getSpeed(), _vCoopAnimal[i].getWidth(), _vCoopAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vCoopAnimal[i].setPositionY(_vCoopAnimal[i].getPositionY() + _vCoopAnimal[i].getSpeed());
					}
				}
				else if (_vCoopAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_RIGHT)
				{
					nextRc = RectMakeCenter(_vCoopAnimal[i].getPositionX() + _vCoopAnimal[i].getSpeed(), _vCoopAnimal[i].getPositionY(), _vCoopAnimal[i].getWidth(), _vCoopAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vCoopAnimal[i].setPositionX(_vCoopAnimal[i].getPositionX() + _vCoopAnimal[i].getSpeed());
					}
				}
				else if (_vCoopAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_UP)
				{
					nextRc = RectMakeCenter(_vCoopAnimal[i].getPositionX(), _vCoopAnimal[i].getPositionY() - _vCoopAnimal[i].getSpeed(), _vCoopAnimal[i].getWidth(), _vCoopAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vCoopAnimal[i].setPositionY(_vCoopAnimal[i].getPositionY() - _vCoopAnimal[i].getSpeed());
					}
				}
				else if (_vCoopAnimal[i].getDirction() == ANIMAL_DIRECTION::ANIMAL_DIRECTION_LEFT)
				{
					nextRc = RectMakeCenter(_vCoopAnimal[i].getPositionX() - _vCoopAnimal[i].getSpeed(), _vCoopAnimal[i].getPositionY(), _vCoopAnimal[i].getWidth(), _vCoopAnimal[i].getHeight());

					if (!nextMoveCollision(nextRc,i))
					{
						_vCoopAnimal[i].setPositionX(_vCoopAnimal[i].getPositionX() - _vCoopAnimal[i].getSpeed());
					}
				}
			}
		}
	}
}

bool animalManager::nextMoveCollision(RECT rc, int num)
{
	/*
	애니멀들의 다음 렉트를 받아서
	충돌여부를 확인한다 (충돌시 true)
	num은 벡터상 현재 번호
	*/
	INGAMESCENE_NAME temp = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	bTileMap tileMap = TILEMAPMANAGER->getTileMap().getTileMap();
	POINT tileSize = TILEMAPMANAGER->getTileMapSize();

	POINT leftTop = POINT{ rc.left/(TILE_SIZE_X),rc.top / (TILE_SIZE_Y) };
	POINT leftBottom = POINT{ rc.left / (TILE_SIZE_X),rc.bottom / (TILE_SIZE_Y) };
	POINT rightTop = POINT{ rc.right / (TILE_SIZE_X),rc.top / (TILE_SIZE_Y) };
	POINT rightBottom = POINT{ rc.right / (TILE_SIZE_X),rc.bottom / (TILE_SIZE_Y) };

	if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_BARN)
	{
		if (rc.left<0 || rc.right>=tileSize.x*TILE_SIZE_X || rc.top < 0 || rc.bottom>=tileSize.y*TILE_SIZE_Y)	return true;
		if (barnRectCollision(rc, num))	return true;
		if (tileMap[leftTop.y][leftTop.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[leftBottom.y][leftBottom.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[rightTop.y][rightTop.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[rightBottom.y][rightBottom.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE) return true;

	}
	else if (temp == INGAMESCENE_NAME::INGAMESCENE_NAME_COOP)
	{
		if (rc.left<0 || rc.right>=tileSize.x*TILE_SIZE_X || rc.top < 0 || rc.bottom>=tileSize.y*TILE_SIZE_Y)	return true;
		if (coopRectCollision(rc, num))	return true;
		if (tileMap[leftTop.y][leftTop.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[leftBottom.y][leftBottom.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[rightTop.y][rightTop.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE ||
			tileMap[rightBottom.y][rightBottom.x].tile_terrainKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE)	return true;
	}

	return false;
}

int animalManager::selectCoopAnimalNum()
{
	/*
	닭장안에서 선택된 애니멀이 있는지 확인하고 그 동물이 오늘 생산물을 생산하지 않앗으면 애니멀벡터의 번호를 반환한다
	아닐시에는 -1을 반환한다
	*/
	POINT playerPosition = POINT{ (LONG)PLAYERMANAGER->getPlayerState().getPlayerPositionX(), (LONG)PLAYERMANAGER->getPlayerState().getPlayerPositionY() };

	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	POINT pointTemp = POINT{m_ptMouse.x+cameraTemp.x, m_ptMouse.y + cameraTemp.y };

	for (int i = 0; i < _vCoopAnimal.size(); i++)
	{
		if (PtInRect(&_vCoopAnimal[i].getRc(), pointTemp))
		{
			if (_vCoopAnimal[i].getIsDayProduction())
			{
				if (!_vCoopAnimal[i].getIsBaby())
				{
					if (getDistance(playerPosition.x, playerPosition.y, _vCoopAnimal[i].getRc().left + (_vCoopAnimal[i].getRc().right - _vCoopAnimal[i].getRc().left) / 2,
						_vCoopAnimal[i].getRc().top + (_vCoopAnimal[i].getRc().bottom - _vCoopAnimal[i].getRc().top) / 2) < 74.0)
					{
						return i;
					}
					else
					{
						return -1;
					}
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}

	return -1;
}

int animalManager::selectBarnAnimalNum()
{
	/*
	축사안에서 선택된 애니멀이 있는지 확인하고 그 동물이 오늘 생산물을 생산하지 않앗으면 애니멀벡터의 번호를 반환한다
	아닐시에는 -1을 반환한다
	*/
	POINT playerPosition = POINT{ (LONG)PLAYERMANAGER->getPlayerState().getPlayerPositionX(), (LONG)PLAYERMANAGER->getPlayerState().getPlayerPositionY() };
	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	POINT pointTemp = POINT{ m_ptMouse.x + cameraTemp.x, m_ptMouse.y + cameraTemp.y };

	for (int i = 0; i < _vBarnAnimal.size(); i++)
	{
		if (PtInRect(&_vBarnAnimal[i].getRc(), pointTemp))
		{
			if (_vBarnAnimal[i].getIsDayProduction())
			{
				if (!_vBarnAnimal[i].getIsBaby())
				{
					if (getDistance(playerPosition.x, playerPosition.y, _vBarnAnimal[i].getRc().left + (_vBarnAnimal[i].getRc().right - _vBarnAnimal[i].getRc().left) / 2,
						_vBarnAnimal[i].getRc().top + (_vBarnAnimal[i].getRc().bottom - _vBarnAnimal[i].getRc().top) / 2) < 74.0)
					{
						return i;
					}
					else
					{
						return -1;
					}
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}
	return -1;
}

bool animalManager::coopRectCollision(RECT rc, int num)
{
	/*
	닭장안에서 각 충돌여부를 확인한다
	i는 무시한다
	*/
	RECT rcTemp;

	for (int i = 0; i < _vCoopAnimal.size(); i++)
	{
		if (i == num) continue;
		if (IntersectRect(&rcTemp, &_vCoopAnimal[i].getRc(), &rc))
		{
			return true;
		}
	}
	return false;
}

bool animalManager::barnRectCollision(RECT rc, int num)
{
	/*
	축사안에서 각 충돌여부를 확인한다
	*/
	RECT rcTemp;

	for (int i = 0; i < _vBarnAnimal.size(); i++)
	{
		if (i == num) continue;

		if (IntersectRect(&rcTemp, &_vBarnAnimal[i].getRc(), &rc))
		{
			return true;
		}
	}
	return false;
}
