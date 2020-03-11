#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	_playerState.init();
	_playerAvatar.init();
	_playerEquipment.init();
	_target = POINT{ -1,-1 };

	return S_OK;
}

void player::release()
{

}

void player::update(PLAYER_ACTIVE_STATE playerActiveState, PLAYER_DIRECTION playerDirection)
{
	if (_playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE &&
		playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE) return;								//플레이어가 대기 상태일때 대기 상태가 업데이트 되면 업데이트가 필요없어 브레이크한다

	//행동 도중 움직이는 것을 막아주는 예외처리
	if (!(_playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		_playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
		&& _playerAvatar.playerAniIsPlay())
		return;


	if (playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
	{
		if (TILEMAPMANAGER->getTileMapAttribute(_playerState.getPlayerPositionX() / (TILE_SIZE_X), _playerState.getPlayerPositionY() / (TILE_SIZE_Y)) == TILE_TERRAINKIND::TILE_TERRAINKIND_GRASS)
		{
			if (!_sound.effIsPlaySound("풀걷기"))
			{
				_sound.effSoundPlay("풀걷기");
				_sound.effSoundOff("흙걷기");
				_sound.effSoundOff("돌걷기");
			}
		}
		else if (TILEMAPMANAGER->getTileMapAttribute(_playerState.getPlayerPositionX() / (TILE_SIZE_X), _playerState.getPlayerPositionY() / (TILE_SIZE_Y)) == TILE_TERRAINKIND::TILE_TERRAINKIND_SOIL)
		{
			if (!_sound.effIsPlaySound("흙걷기"))
			{
				_sound.effSoundPlay("흙걷기");
				_sound.effSoundOff("풀걷기");
				_sound.effSoundOff("돌걷기");
			}
		}
		else if (!_sound.effIsPlaySound("돌걷기"))
		{
			_sound.effSoundPlay("돌걷기");
			_sound.effSoundOff("흙걷기");
			_sound.effSoundOff("풀걷기");
		}
		

		if (playerDirection != _playerState.getPlayerDirection() ||
			playerActiveState != _playerState.getPlayerActiveStateNow())										//플레이어가 방향을 바꾸거나 행동을 바꾸면 아바타 변경 필요
		{
			_playerState.setPlayerDirection(playerDirection);
			_playerState.setPlayerActiveStateNow(playerActiveState);

			_playerAvatar.playerActiveEnd();
			_playerAvatar.update(_playerState);
			_playerEquipment.equipAniStop();
		}

		if (obstacle())
		{
			//이동이 가능할때
			if (playerDirection == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() - _playerState.getPlayerSpeed());
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			else if (playerDirection == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() + _playerState.getPlayerSpeed());
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			else if (playerDirection == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() - _playerState.getPlayerSpeed());
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			else if (playerDirection == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() + _playerState.getPlayerSpeed());
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
		}
	}
	else if (playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE)
	{
		_playerState.setPlayerDirection(playerDirection);
		_playerState.setPlayerActiveStateNow(playerActiveState);

		_playerAvatar.update(_playerState);
		_playerAvatar.playerActiveEnd();
		_playerEquipment.equipAniStop();

		_sound.effSoundOff("돌걷기");
		_sound.effSoundOff("풀걷기");
		_sound.effSoundOff("흙걷기");
	}
	else
	{
		if (playerActiveState != _playerState.getPlayerActiveStateNow())										//플레이어가 행동을 바꾸면 아바타 변경 필요
		{
			_playerState.setPlayerDirection(playerDirection);
			_playerState.setPlayerActiveStateNow(playerActiveState);

			_playerAvatar.playerActiveEnd();
			_playerAvatar.update(_playerState);
			_playerEquipment.update(_playerState);
		}
	}
}

void player::render(HDC hdc)
{
	tileMap tileMapTemp = TILEMAPMANAGER->getTileMap();
	RECT rcTemp;

	PLAYER_ACTIVE_STATE state = _playerState.getPlayerActiveStateNow();

	if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		if (state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE ||
			state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
		{
			_playerEquipment.render(hdc, _playerState);
		}
		_playerAvatar.render(hdc, _playerState);
	}
	else
	{
		_playerAvatar.render(hdc, _playerState);

		if (state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE ||
			state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE || state == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
		{
			_playerEquipment.render(hdc, _playerState);
		}
	}
	if (tileMapTemp.getTileMapSize().x <= _target.x || tileMapTemp.getTileMapSize().y <= _target.y) return;
	if (_target.x < 0 || _target.y < 0)	return;
	rcTemp = tileMapTemp.getTileMap()[_target.y][_target.x].tileRc;
	IMAGEMANAGER->render("UI_선택박스", hdc, rcTemp.left, rcTemp.top);
}

bool player::obstacle()
{
	/*
	먼저 이동시킨 렉트로 타일 속성을 검사해 해당되지 않으면 이동하게 된다
	좌상, 좌하, 우상, 우하 4개의 점의 타일맵을 조사한다
	*/
	tileMap tileMapTemp = TILEMAPMANAGER->getTileMap();
	vTileObject tileObject = tileMapTemp.getTileObject();
	RECT moveRectTemp;
	TILE_TERRAINKIND terrainkindTemp;
	POINT leftTop, leftBottom, rightTop, rightBottom;


	if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		moveRectTemp = RectMake(_playerState.getPlayerRc().left - _playerState.getPlayerSpeed(), _playerState.getPlayerRc().bottom - 48, 48, 48);
	}
	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		moveRectTemp = RectMake(_playerState.getPlayerRc().left + _playerState.getPlayerSpeed(), _playerState.getPlayerRc().bottom - 48, 48, 48);
	}
	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		moveRectTemp = RectMake(_playerState.getPlayerRc().left, _playerState.getPlayerRc().bottom - 48 - _playerState.getPlayerSpeed(), 48, 48);
	}
	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		moveRectTemp = RectMake(_playerState.getPlayerRc().left, _playerState.getPlayerRc().bottom - 48 + _playerState.getPlayerSpeed(), 48, 48);
	}

	leftTop.x = (moveRectTemp.left + 1) / (TILE_SIZE_X), leftTop.y = (moveRectTemp.top + 1) / (TILE_SIZE_Y);
	leftBottom.x = (moveRectTemp.left + 1) / (TILE_SIZE_X), leftBottom.y = (moveRectTemp.bottom - 1) / (TILE_SIZE_Y);
	rightTop.x = (moveRectTemp.right - 1) / (TILE_SIZE_X), rightTop.y = (moveRectTemp.top + 1) / (TILE_SIZE_Y);
	rightBottom.x = (moveRectTemp.right - 1) / (TILE_SIZE_X), rightBottom.y = (moveRectTemp.bottom - 1) / (TILE_SIZE_Y);


	//먼저 맵에서 벗어낫는지 여부를 판단한다
	if (moveRectTemp.left<0 || moveRectTemp.right> tileMapTemp.getTileMapSize().x*(TILE_SIZE_X)
		|| moveRectTemp.top<0 || moveRectTemp.bottom>tileMapTemp.getTileMapSize().y*(TILE_SIZE_Y))				return false;

	//이동할 4개의 점을 조사한다.
	//좌상
	terrainkindTemp = tileMapTemp.getKindTerrian(leftTop.x, leftTop.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//타일 속성 검사
		if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
		{
			PLAYERMANAGER->setPlayerPosition(leftTop.x*TILE_SIZE_X + 48 + 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
		{
			PLAYERMANAGER->setPlayerPosition(rightTop.x*TILE_SIZE_X - 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftTop.y*TILE_SIZE_Y + _playerState.getPlayerHeight() / 2);
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftBottom.y*TILE_SIZE_Y - _playerState.getPlayerHeight() / 2);
		}

		CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());

		slideMove();
		return false;
	}

	if (tileMapTemp.getIsShader(leftTop.x, leftTop.y))
	{
		//오브젝트 검사
		for (int i = 0; i < tileObject.size(); i++)
		{
			if (PtInRect(&tileObject[i]->objectTotalRc, POINT{ moveRectTemp.left + 1,moveRectTemp.top + 1 }))
			{
				if (PtInRect(&tileObject[i]->objectCollisionRc, POINT{ moveRectTemp.left + 1,moveRectTemp.top + 1 }))		return false;

				if (tileObject[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//좌하
	terrainkindTemp = tileMapTemp.getKindTerrian(leftBottom.x, leftBottom.y);
	if (!tileMapTemp.getIsTerrain(leftBottom.x, leftBottom.y) || tileMapTemp.getIsObject(leftBottom.x, leftBottom.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//타일 속성 검사
		if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
		{
			PLAYERMANAGER->setPlayerPosition(leftTop.x*TILE_SIZE_X + 48 + 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
		{
			PLAYERMANAGER->setPlayerPosition(rightTop.x*TILE_SIZE_X - 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftTop.y*TILE_SIZE_Y + _playerState.getPlayerHeight() / 2);
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftBottom.y*TILE_SIZE_Y - _playerState.getPlayerHeight() / 2);
		}

		CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());

		slideMove();
		return false;
	}
	if (tileMapTemp.getIsShader(leftBottom.x, leftBottom.y))
	{
		//오브젝트 검사
		for (int i = 0; i < tileObject.size(); i++)
		{
			if (PtInRect(&tileObject[i]->objectTotalRc, POINT{ moveRectTemp.left + 1,moveRectTemp.bottom - 1 }))
			{
				if (PtInRect(&tileObject[i]->objectCollisionRc, POINT{ moveRectTemp.left + 1,moveRectTemp.bottom - 1 }))		return false;

				if (tileObject[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//우상
	terrainkindTemp = tileMapTemp.getKindTerrian(rightTop.x, rightTop.y);
	if (!tileMapTemp.getIsTerrain(rightTop.x, rightTop.y) || tileMapTemp.getIsObject(rightTop.x, rightTop.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//타일 속성 검사
		if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
		{
			PLAYERMANAGER->setPlayerPosition(leftTop.x*TILE_SIZE_X + 48 + 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
		{
			PLAYERMANAGER->setPlayerPosition(rightTop.x*TILE_SIZE_X - 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftTop.y*TILE_SIZE_Y + _playerState.getPlayerHeight() / 2);
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftBottom.y*TILE_SIZE_Y - _playerState.getPlayerHeight() / 2);
		}

		CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());

		slideMove();
		return false;
	}
	if (tileMapTemp.getIsShader(rightTop.x, rightTop.y))
	{
		//오브젝트 검사
		for (int i = 0; i < tileObject.size(); i++)
		{
			if (PtInRect(&tileObject[i]->objectTotalRc, POINT{ moveRectTemp.right - 1,moveRectTemp.top + 1 }))
			{
				if (PtInRect(&tileObject[i]->objectCollisionRc, POINT{ moveRectTemp.right - 1,moveRectTemp.top + 1 }))		return false;

				if (tileObject[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//우하
	terrainkindTemp = tileMapTemp.getKindTerrian(rightBottom.x, rightBottom.y);
	if (!tileMapTemp.getIsTerrain(rightBottom.x, rightBottom.y) || tileMapTemp.getIsObject(rightBottom.x, rightBottom.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//타일 속성 검사
		if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
		{
			PLAYERMANAGER->setPlayerPosition(leftTop.x*TILE_SIZE_X + 48 + 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
		{
			PLAYERMANAGER->setPlayerPosition(rightTop.x*TILE_SIZE_X - 24, _playerState.getPlayerPositionY());
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftTop.y*TILE_SIZE_Y + _playerState.getPlayerHeight() / 2);
		}
		else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
		{
			PLAYERMANAGER->setPlayerPosition(_playerState.getPlayerPositionX(), leftBottom.y*TILE_SIZE_Y - _playerState.getPlayerHeight() / 2);
		}

		CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());

		slideMove();
		return false;
	}
	if (tileMapTemp.getIsShader(rightBottom.x, rightBottom.y))
	{
		//오브젝트 검사
		for (int i = 0; i < tileObject.size(); i++)
		{
			if (PtInRect(&tileObject[i]->objectTotalRc, POINT{ moveRectTemp.right - 1,moveRectTemp.bottom - 1 }))
			{
				if (PtInRect(&tileObject[i]->objectCollisionRc, POINT{ moveRectTemp.right - 1,moveRectTemp.bottom - 1 }))		return false;

				if (tileObject[i]->tile_objectKind == TILE_OBJECTKIND::TILE_OBJECTKIND_TREE)
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
	}

	//npc검사
	if (NPCMANAGER->getRectCollision(moveRectTemp, (INGAMESCENE_NAME)SCENEMANAGER->getIngameName()))
	{
		return false;
	}

	return true;
}

void player::slideMove()
{
	tileMap tileMapTemp = TILEMAPMANAGER->getTileMap();
	vTileObject tileObject = tileMapTemp.getTileObject();
	RECT playerMoveRect = RectMake(_playerState.getPlayerRc().left, _playerState.getPlayerRc().bottom - 48, 48, 48);
	POINT playerPoint = { _playerState.getPlayerPositionX(),_playerState.getPlayerRc().bottom - 24 };
	TILE_TERRAINKIND terrainkindTemp;

	int tileX, tileY;


	//미끄러짐 처리
	if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		//위검사

		tileX = (playerPoint.x - 48) / (TILE_SIZE_X);
		tileY = (playerPoint.y - 24) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x) / (TILE_SIZE_X);
			tileY = (playerPoint.y - 24) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() - 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			return;
		}
		//아래검사

		tileX = (playerPoint.x - 48) / (TILE_SIZE_X);
		tileY = (playerPoint.y + 24) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x) / (TILE_SIZE_X);
			tileY = (playerPoint.y + 24) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() + 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}

			return;
		}
	}

	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		//위검사

		tileX = (playerPoint.x + 48) / (TILE_SIZE_X);
		tileY = (playerPoint.y - 24) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x) / (TILE_SIZE_X);
			tileY = (playerPoint.y - 24) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() - 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}

			return;
		}

		//아래검사

		tileX = (playerPoint.x + 48) / (TILE_SIZE_X);
		tileY = (playerPoint.y + 24) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x) / (TILE_SIZE_X);
			tileY = (playerPoint.y + 24) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionY(_playerState.getPlayerPositionY() + 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}

			return;
		}
	}
	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		//왼쪽검사

		tileX = (playerPoint.x - 24) / (TILE_SIZE_X);
		tileY = (playerPoint.y - 48) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x - 24) / (TILE_SIZE_X);
			tileY = (playerPoint.y) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() - 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			return;
		}

		//오른쪽검사

		tileX = (playerPoint.x + 24) / (TILE_SIZE_X);
		tileY = (playerPoint.y - 48) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x + 24) / (TILE_SIZE_X);
			tileY = (playerPoint.y) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() + 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			return;
		}


	}
	else if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		//왼쪽검사

		tileX = (playerPoint.x - 24) / (TILE_SIZE_X);
		tileY = (playerPoint.y + 48) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x - 24) / (TILE_SIZE_X);
			tileY = (playerPoint.y) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() - 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			return;
		}

		//오른쪽검사

		tileX = (playerPoint.x + 24) / (TILE_SIZE_X);
		tileY = (playerPoint.y + 48) / (TILE_SIZE_Y);

		if (tileX<0 || tileY<0 || tileX>tileMapTemp.getTileMapSize().x || tileY>tileMapTemp.getTileMapSize().y) return;

		terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

		if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
			|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
		{
			tileX = (playerPoint.x + 24) / (TILE_SIZE_X);
			tileY = (playerPoint.y) / (TILE_SIZE_Y);

			terrainkindTemp = tileMapTemp.getKindTerrian(tileX, tileY);

			if (!(!tileMapTemp.getIsTerrain(tileX, tileY) || tileMapTemp.getIsObject(tileX, tileY)
				|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL))
			{
				_playerState.setPlayerPositionX(_playerState.getPlayerPositionX() + 1);
				CAMERAMANAGER->cameraMove(_playerState.getPlayerPositionX(), _playerState.getPlayerPositionY());
			}
			return;
		}

	}
}
