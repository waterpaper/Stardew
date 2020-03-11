#include "stdafx.h"
#include "playerEquipment.h"


playerEquipment::playerEquipment()
{
	aniAdd();
}


playerEquipment::~playerEquipment()
{
}

bool playerEquipment::isAvailable(PLAYER_ACTIVE_STATE state, int x, int y)
{
	vTileObject objectTemp;

	if (state==PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE&&SCENEMANAGER->getIngameName()==INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
	{
		if (!TILEMAPMANAGER->getIsObject(x, y))
		{
			if (TILEMAPMANAGER->getTileMap().getKindTerrian(x, y) == TILE_TERRAINKIND::TILE_TERRAINKIND_SOIL)
			{
				if (!FARMMANAGER->getHoeing(x,y))
				{
					return true;
				}
			}
		}
	}

	if (state==PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING && SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
	{
		if (!TILEMAPMANAGER->getIsObject(x, y))
		{
			if (TILEMAPMANAGER->getTileMap().getKindTerrian(x, y) == TILE_TERRAINKIND::TILE_TERRAINKIND_SOIL)
			{
				if (FARMMANAGER->getHoeing(x, y)&&!FARMMANAGER->getWatering(x, y))
				{
					return true;
				}
			}
		}
	}

	if (state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE && SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
	{
		if (TILEMAPMANAGER->getIsObject(x, y))
		{
			objectTemp=TILEMAPMANAGER->getTileMap().getTileObject();
			for (int i = 0; i < objectTemp.size(); i++)
			{
				if (objectTemp[i]->objectPos.x <= x && objectTemp[i]->objectPos.x + objectTemp[i]->sizeX > x&&
					objectTemp[i]->objectPos.y <= y && objectTemp[i]->objectPos.y + objectTemp[i]->sizeY > y)
				{
					if (objectTemp[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_WOOD)
					{
						TILEMAPMANAGER->deleteObject(i);
						_sound.effSoundPlay("나무깨기");
						return true;
					}
					else if (objectTemp[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
					{
						_sound.effSoundPlay("나무깨기");
						if (objectTemp[i]->hp > 0)
						{
							TILEMAPMANAGER->setObjectHp(i,objectTemp[i]->hp-1);
							return false;
						}
						else
						{
							TILEMAPMANAGER->deleteObject(i);
							return true;
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
	}

	if (state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE && SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
	{
		if (TILEMAPMANAGER->getIsObject(x, y))
		{
			objectTemp = TILEMAPMANAGER->getTileMap().getTileObject();
			for (int i = 0; i < objectTemp.size(); i++)
			{
				if (objectTemp[i]->objectPos.x<= x&& objectTemp[i]->objectPos.x+ objectTemp[i]->sizeX > x&&
					objectTemp[i]->objectPos.y <= y && objectTemp[i]->objectPos.y + objectTemp[i]->sizeY > y)
				{
					if (objectTemp[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_ROCK)
					{
						TILEMAPMANAGER->deleteObject(i);
						_sound.effSoundPlay("돌캐기");
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}

	if (state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE && SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_FARM)
	{
		if (TILEMAPMANAGER->getIsObject(x, y))
		{
			objectTemp = TILEMAPMANAGER->getTileMap().getTileObject();
			for (int i = 0; i < objectTemp.size(); i++)
			{
				if (objectTemp[i]->objectPos.x <= x && objectTemp[i]->objectPos.x + objectTemp[i]->sizeX > x&&
					objectTemp[i]->objectPos.y <= y && objectTemp[i]->objectPos.y + objectTemp[i]->sizeY > y)
				{
					if (objectTemp[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_GRASS)
					{
						TILEMAPMANAGER->deleteObject(i);
						_sound.effSoundPlay("풀베기");
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}

	return false;
}

void playerEquipment::init()
{
	_equipmentImage = IMAGEMANAGER->findImage("tool_axe");
	_equipmentAni = ANIMATIONMANAGER->findAnimation("tool_axe_Down");
}

void playerEquipment::update(playerState state)
{
	if (equipAniIsPlay()) return;																//애니메이션이 진행중일때에는 다시 시작하지 않기 위해서 리턴한다

	if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE || state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_NULL ||
		state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE || state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE ||
		state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE)	return;

	string strTemp;

	if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK)
	{
		strTemp = "tool_attack";
	}
	else if(state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE)
	{
		strTemp = "tool_scythe";
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE)
	{
		strTemp = "tool_axe";
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE)
	{
		strTemp = "tool_pickaxe";
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE)
	{
		strTemp = "tool_hoe";
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
	{
		strTemp = "tool_wateringcan";
	}

	_equipmentImage = IMAGEMANAGER->findImage(strTemp);

	if (state.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		strTemp += "_Down";
	}
	else if (state.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		strTemp += "_Right";
	}
	else if (state.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		strTemp += "_Left";
	}
	else if (state.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		strTemp += "_Up";
	}

	_equipmentAni=ANIMATIONMANAGER->findAnimation(strTemp);
	_equipmentAni->start();

}

void playerEquipment::render(HDC hdc, playerState state)
{
	int x = state.getPlayerPositionX() - state.getPlayerWitdh() / 2;
	int y = state.getPlayerPositionY() - state.getPlayerHeight() / 2;

	if (state.getPlayerActiveStateNow()==PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE)
	{
		equipment_axeRender(hdc, x, y, state.getPlayerDirection());
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE)
	{
		equipment_pickaxeRender(hdc, x, y, state.getPlayerDirection());
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE)
	{
		equipment_hoeRender(hdc, x, y, state.getPlayerDirection());
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
	{
		equipment_wateringcanRender(hdc, x, y, state.getPlayerDirection());
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE)
	{
		equipment_scytheRender(hdc, x, y, state.getPlayerDirection());
	}
	else if (state.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK)
	{
		equipment_attackRender(hdc, x, y, state.getPlayerDirection());
	}
}

void playerEquipment::aniAdd()
{
	//움직임
	ANIMATIONMANAGER->addAnimation("tool_axe_Down", "tool_axe", 0 * 5, 0 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_hoe_Down", "tool_hoe", 0 * 5, 0 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_pickaxe_Down", "tool_pickaxe", 0 * 5, 0 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_wateringcan_Down", "tool_wateringcan", 0 * 3, 0 * 3 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("tool_scythe_Down", "tool_scythe", 0 * 6, 0 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("tool_axe_Right", "tool_axe", 1 * 5, 1 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_hoe_Right", "tool_hoe", 1 * 5, 1 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_pickaxe_Right", "tool_pickaxe", 1 * 5, 1 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_wateringcan_Right", "tool_wateringcan", 1 * 3, 1 * 3 + 2,5, false, false);
	ANIMATIONMANAGER->addAnimation("tool_scythe_Right", "tool_scythe", 1 * 6, 1 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("tool_axe_Left", "tool_axe", 2 * 5, 2 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_hoe_Left", "tool_hoe", 2 * 5, 2 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_pickaxe_Left", "tool_pickaxe", 2 * 5, 2 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_wateringcan_Left", "tool_wateringcan", 2 * 3, 2 * 3 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("tool_scythe_Left", "tool_scythe", 2 * 6, 2 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("tool_axe_Up", "tool_axe", 3 * 5, 3 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_hoe_Up", "tool_hoe", 3 * 5, 3 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_pickaxe_Up", "tool_pickaxe", 3 * 5, 3 * 5 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("tool_wateringcan_Up", "tool_wateringcan", 3 * 3, 3 * 3 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("tool_scythe_Up", "tool_scythe", 3 * 6, 3 * 6 + 5, 20, false, false);
}

bool playerEquipment::equipAniIsPlay()
{
	if (_equipmentAni->isPlay())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void playerEquipment::equipAniStop()
{
	if (_equipmentAni!=nullptr&&_equipmentAni->isPlay())
	{
		_equipmentAni->stop();
	}
}

void playerEquipment::equipment_axeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		int num = _equipmentAni->getFrameIndex();
		
		if (num == 0)	_equipmentImage->aniRender(hdc, x - 18, y - 33 , _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 18, y - 18 , _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 6, y + 24, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 6, y + 36 , _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 6, y + 48 , _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x , y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x +24, y -15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x +30, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x +33, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 48, y - 15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 54, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 57, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 9 , y - 48, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 9 , y - 45, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 9, y - 33, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 9, y - 31, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 9, y - 18, _equipmentAni);
	}
}

void playerEquipment::equipment_pickaxeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 18, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 18, y - 18, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 6, y + 24, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 6, y + 36, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 6, y + 48, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x, y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 24, y - 15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x + 30, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x + 33, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 48, y - 15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 54, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 57, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 9, y - 48, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 9, y - 45, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 9, y - 33, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 9, y - 31, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 9, y - 18, _equipmentAni);
	}
}

void playerEquipment::equipment_hoeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 18, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 18, y - 18, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 6, y + 24, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 6, y + 36, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 6, y + 48, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x, y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 24, y - 15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x + 30, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x + 33, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x, y - 33, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 21, y - 33, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 48, y - 15, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 54, y, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 57, y + 18, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 9, y - 48, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 9, y - 45, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 9, y - 33, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 9, y - 31, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 9, y - 18, _equipmentAni);
	}
}

void playerEquipment::equipment_wateringcanRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 9, y + 48, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 9, y + 39, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 6, y + 9, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x + 27, y +27, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x + 27, y +12, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 15, y - 3, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 45, y + 24 , _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 45, y +9, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 36, y - 3, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 9, y + 15, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 9, y + 12, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 9, y - 18, _equipmentAni);
	}
}

void playerEquipment::equipment_scytheRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x + 42, y + 24, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x + 30, y + 48, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 24, y + 72, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 18, y + 72, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 39, y + 72, _equipmentAni);
		if (num == 5)	_equipmentImage->aniRender(hdc, x - 39, y + 54, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x + 12, y, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x + 33, y, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 33, y + 39, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x + 33, y + 63, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x + 9, y + 72, _equipmentAni);
		if (num == 5)	_equipmentImage->aniRender(hdc, x - 21, y + 66, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 12, y, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 30, y, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x - 30, y + 24, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x - 36, y + 45, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x - 21, y + 63, _equipmentAni);
		if (num == 5)	_equipmentImage->aniRender(hdc, x +6, y + 66, _equipmentAni);
	}
	else if (direction == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		int num = _equipmentAni->getFrameIndex();

		if (num == 0)	_equipmentImage->aniRender(hdc, x - 24, y + 15, _equipmentAni);
		if (num == 1)	_equipmentImage->aniRender(hdc, x - 24, y - 12, _equipmentAni);
		if (num == 2)	_equipmentImage->aniRender(hdc, x + 6, y - 12, _equipmentAni);
		if (num == 3)	_equipmentImage->aniRender(hdc, x + 18, y - 12, _equipmentAni);
		if (num == 4)	_equipmentImage->aniRender(hdc, x + 39, y, _equipmentAni);
		if (num == 5)	_equipmentImage->aniRender(hdc, x + 45, y + 12, _equipmentAni);
	}
}

void playerEquipment::equipment_attackRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction)
{
	_equipmentImage->aniRender(hdc, x, y, _equipmentAni);
}
