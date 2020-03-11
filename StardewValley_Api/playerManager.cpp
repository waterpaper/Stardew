#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	_player.init();
	_isTake = false;
	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	setTarget();
	//아이템이 없어졋을때 행동변화 예외처리
	POINT targetTemp = _player.getTarget();

	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D'))		//방향키를 뗏을 때
	{
		if (!_isTake)
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE, _player.getPlayerState().getPlayerDirection());
		}
		else
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE, _player.getPlayerState().getPlayerDirection());
		}
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//아이템 종류에 따라 행동을 정의합니다
		int num = UIMANAGER->getKindNum();
		item itemTemp = INVENTORYMANAGER->getItem(num, 0);

		if (itemTemp.getItemCategory() == ITEMKIND_TOOL)
		{
			if (itemTemp.getItemDivision() == TOOLKIND_AXE)
			{
				//플레이어 동작확인
				if (_player.getPlayerAvatar().playerAniIsPlay())
				{
					return;
				}

				//플레이어 행동력 여부 확인
				if (_player.getPlayerActingPower() <= 1)
				{
					return;
				}
				else
				{
					_player.setPlayerActingPower(_player.getPlayerActingPower() - 2);
				}

				_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE, _player.getPlayerState().getPlayerDirection());

				if (_player.getPlayerEquipment().isAvailable(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE, targetTemp.x, targetTemp.y))
				{
					//삭제하고 나서 동작 추가

					_sound.effSoundPlay("허공찍기");
				}
			}
			else if (itemTemp.getItemDivision() == TOOLKIND_HOE)
			{
				//플레이어 동작확인
				if (_player.getPlayerAvatar().playerAniIsPlay())
				{
					return;
				}

				//플레이어 행동력 여부 확인
				if (_player.getPlayerActingPower() <= 1)
				{
					return;
				}
				else
				{
					_player.setPlayerActingPower(_player.getPlayerActingPower() - 2);
				}

				_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE, _player.getPlayerState().getPlayerDirection());
				if (_player.getPlayerEquipment().isAvailable(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE, targetTemp.x, targetTemp.y))
				{
					FARMMANAGER->setHoeingField(targetTemp.x, targetTemp.y);

					_sound.effSoundPlay("호미질");
				}
			}
			else if (itemTemp.getItemDivision() == TOOLKIND_PICKAXE)
			{
				//플레이어 동작확인
				if (_player.getPlayerAvatar().playerAniIsPlay())
				{
					return;
				}

				//플레이어 행동력 여부 확인
				if (_player.getPlayerActingPower() <= 1)
				{
					return;
				}
				else
				{
					_player.setPlayerActingPower(_player.getPlayerActingPower() - 2);
				}

				_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE, _player.getPlayerState().getPlayerDirection());

				if (_player.getPlayerEquipment().isAvailable(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE, targetTemp.x, targetTemp.y))
				{
					_sound.effSoundPlay("허공찍기");
				}
			}
			else if (itemTemp.getItemDivision() == TOOLKIND_SCYTHE)
			{
				//플레이어 동작확인
				if (_player.getPlayerAvatar().playerAniIsPlay())
				{
					return;
				}

				//플레이어 행동력 여부 확인
				if (_player.getPlayerActingPower() <= 1)
				{
					return;
				}
				else
				{
					_player.setPlayerActingPower(_player.getPlayerActingPower() - 2);
				}

				_sound.effSoundPlay("낫질");
				_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE, _player.getPlayerState().getPlayerDirection());

				if (_player.getPlayerEquipment().isAvailable(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE, targetTemp.x, targetTemp.y))
				{
					_sound.effSoundPlay("풀베기");
				}
			}
			else if (itemTemp.getItemDivision() == TOOLKIND_WATERINGCAN)
			{
				//플레이어 동작확인
				if (_player.getPlayerAvatar().playerAniIsPlay())
				{
					return;
				}

				//플레이어 행동력 여부 확인
				if (_player.getPlayerActingPower() <= 1)
				{
					return;
				}
				else
				{
					_player.setPlayerActingPower(_player.getPlayerActingPower() - 2);
				}

				_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING, _player.getPlayerState().getPlayerDirection());
				if (_player.getPlayerEquipment().isAvailable(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING, targetTemp.x, targetTemp.y))
				{
					FARMMANAGER->setWateringField(targetTemp.x, targetTemp.y);
					_sound.effSoundPlay("물주기");
				}
			}
		}
		else if (itemTemp.getItemCategory() == ITEMKIND_SEED)
		{
			if (_player.getPlayerAvatar().playerAniIsPlay())
			{
				return;
			}

			if (FARMMANAGER->setSeedField(targetTemp.x, targetTemp.y, (SEEDKIND)itemTemp.getItemDivision()))
			{
				INVENTORYMANAGER->deleteItem(num, 0);
			}
		}

		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//npc 우클릭시 선택한 아이템 종류가 없거나 툴, 무기면 대화
		int select;
		int num = UIMANAGER->getKindNum();
		item itemTemp = INVENTORYMANAGER->getItem(num, 0);

		if (FARMMANAGER->getIsHarvesting(targetTemp.x, targetTemp.y))
		{
			FARMMANAGER->harvesting(targetTemp.x, targetTemp.y);
			_sound.effSoundPlay("아이템습득");
			return;
		}
		if (SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_BARN)
		{
			select = ANIMALMANAGER->selectBarnAnimalNum();

			if (select != -1)
			{
				ANIMALMANAGER->barnGetItem(select);
				_sound.effSoundPlay("아이템습득");
				return;
			}
		}
		if (SCENEMANAGER->getIngameName() == INGAMESCENE_NAME::INGAMESCENE_NAME_COOP)
		{

			select = ANIMALMANAGER->selectCoopAnimalNum();

			if (select != -1)
			{
				ANIMALMANAGER->coopGetItem(select);
				_sound.effSoundPlay("아이템습득");
				return;
			}
		}

		if (itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_NULL || itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_EQUIPMENT ||
			itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_TOOL)
		{
			NPCMANAGER->playerConversation(POINT{ (LONG)_player.getPlayerState().getPlayerPositionX(),(LONG)_player.getPlayerState().getPlayerPositionY() });
		}
		else
		{
			//우클릭시 선택한 아이템 종류가 음식이거나 
			if (!(NPCMANAGER->playerPresent(POINT{ (LONG)_player.getPlayerState().getPlayerPositionX(),(LONG)_player.getPlayerState().getPlayerPositionY() })))
			{
				if (itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_FOOD || itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_CROPS
					|| itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_ANIMALITEM)
				{
					UIMANAGER->setSelectDialogKind(UI_SELECTDIALOGKIND::UI_SELECTDIALOGKIND_EATTINGITEM);
					UIMANAGER->changeUi("UI_selectDialog");
				}
				return;
			}
		}
	}

	if (_isTake)
	{
		ITEMMANAGER->collisionItem(_player.getPlayerState().getPlayerRc());
		//움직임
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_UP);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT);
			return;
		}
	}
	else
	{
		ITEMMANAGER->collisionItem(_player.getPlayerState().getPlayerRc());
		//움직임
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_UP);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN);
			return;
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE, PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT);
			return;
		}
	}

	//아무행동 x
	if (!_player.isPlayerAniIsPlay())
	{
		if (!_isTake)
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE, _player.getPlayerState().getPlayerDirection());
		}
		else
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE, _player.getPlayerState().getPlayerDirection());
		}
	}
}

void playerManager::render(HDC hdc)
{
	_player.render(hdc);

	if (_isTake)
	{
		//아이템 종류에 따라 들고 가는 아이템을 출력합니다
		int num = UIMANAGER->getKindNum();
		item itemTemp = INVENTORYMANAGER->getItem(num, 0);
		RECT rectTemp = RectMakeCenter(_player.getPlayerState().getPlayerPositionX(), _player.getPlayerState().getPlayerPositionY() - 48, 48, 48);

		if (itemTemp.getItemCategory() == ITEMKIND::ITEMKIND_NULL)
		{
			_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE, _player.getPlayerState().getPlayerDirection());
			_isTake = false;
			return;
		}
		itemTemp.getItemImg()->frameRender(hdc, rectTemp.left, rectTemp.top, itemTemp.getItemImageFrame().x, itemTemp.getItemImageFrame().y);
	}
}

void playerManager::setTarget()
{
	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	POINT postionTemp = POINT{ (LONG)_player.getPlayerState().getPlayerPositionX(),(LONG)_player.getPlayerState().getPlayerPositionY() + 24 };
	RECT playerCollisionRect = RectMake(_player.getPlayerState().getPlayerRc().left, _player.getPlayerState().getPlayerRc().top + 48, 48, 48);

	if (PtInRect(&playerCollisionRect, POINT{ m_ptMouse.x + cameraTemp.x, m_ptMouse.y + cameraTemp.y }))
	{
		_player.setTarget((postionTemp.x) / (TILE_SIZE_X), postionTemp.y / (TILE_SIZE_Y));
		return;
	}

	float angle = getAngle(postionTemp.x, postionTemp.y, m_ptMouse.x + cameraTemp.x, m_ptMouse.y + cameraTemp.y) * 180 / PI;

	if (22.5 < angle&&angle < 67.5)_player.setTarget((postionTemp.x + 48) / (TILE_SIZE_X), (postionTemp.y - 48) / (TILE_SIZE_Y));
	else if (67.5 < angle&&angle < 112.5)_player.setTarget((postionTemp.x) / (TILE_SIZE_X), (postionTemp.y - 48) / (TILE_SIZE_Y));
	else if (112.5 < angle&&angle < 157.5)_player.setTarget((postionTemp.x - 48) / (TILE_SIZE_X), (postionTemp.y - 48) / (TILE_SIZE_Y));
	else if (157.5 < angle&&angle < 202.5)_player.setTarget((postionTemp.x - 48) / (TILE_SIZE_X), (postionTemp.y) / (TILE_SIZE_Y));
	else if (202.5 < angle&&angle < 247.5)_player.setTarget((postionTemp.x - 48) / (TILE_SIZE_X), (postionTemp.y + 48) / (TILE_SIZE_Y));
	else if (247.5 < angle&&angle < 292.5)_player.setTarget((postionTemp.x) / (TILE_SIZE_X), (postionTemp.y + 48) / (TILE_SIZE_Y));
	else if (292.5 < angle&&angle < 337.5)_player.setTarget((postionTemp.x + 48) / (TILE_SIZE_X), (postionTemp.y + 48) / (TILE_SIZE_Y));
	else _player.setTarget((postionTemp.x + 48) / (TILE_SIZE_X), (postionTemp.y) / (TILE_SIZE_Y));

}
