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
		playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE) return;								//�÷��̾ ��� �����϶� ��� ���°� ������Ʈ �Ǹ� ������Ʈ�� �ʿ���� �극��ũ�Ѵ�

	//�ൿ ���� �����̴� ���� �����ִ� ����ó��
	if (!(_playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		_playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
		&& _playerAvatar.playerAniIsPlay())
		return;


	if (playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		playerActiveState == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
	{
		if (TILEMAPMANAGER->getTileMapAttribute(_playerState.getPlayerPositionX() / (TILE_SIZE_X), _playerState.getPlayerPositionY() / (TILE_SIZE_Y)) == TILE_TERRAINKIND::TILE_TERRAINKIND_GRASS)
		{
			if (!_sound.effIsPlaySound("Ǯ�ȱ�"))
			{
				_sound.effSoundPlay("Ǯ�ȱ�");
				_sound.effSoundOff("��ȱ�");
				_sound.effSoundOff("���ȱ�");
			}
		}
		else if (TILEMAPMANAGER->getTileMapAttribute(_playerState.getPlayerPositionX() / (TILE_SIZE_X), _playerState.getPlayerPositionY() / (TILE_SIZE_Y)) == TILE_TERRAINKIND::TILE_TERRAINKIND_SOIL)
		{
			if (!_sound.effIsPlaySound("��ȱ�"))
			{
				_sound.effSoundPlay("��ȱ�");
				_sound.effSoundOff("Ǯ�ȱ�");
				_sound.effSoundOff("���ȱ�");
			}
		}
		else if (!_sound.effIsPlaySound("���ȱ�"))
		{
			_sound.effSoundPlay("���ȱ�");
			_sound.effSoundOff("��ȱ�");
			_sound.effSoundOff("Ǯ�ȱ�");
		}
		

		if (playerDirection != _playerState.getPlayerDirection() ||
			playerActiveState != _playerState.getPlayerActiveStateNow())										//�÷��̾ ������ �ٲٰų� �ൿ�� �ٲٸ� �ƹ�Ÿ ���� �ʿ�
		{
			_playerState.setPlayerDirection(playerDirection);
			_playerState.setPlayerActiveStateNow(playerActiveState);

			_playerAvatar.playerActiveEnd();
			_playerAvatar.update(_playerState);
			_playerEquipment.equipAniStop();
		}

		if (obstacle())
		{
			//�̵��� �����Ҷ�
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

		_sound.effSoundOff("���ȱ�");
		_sound.effSoundOff("Ǯ�ȱ�");
		_sound.effSoundOff("��ȱ�");
	}
	else
	{
		if (playerActiveState != _playerState.getPlayerActiveStateNow())										//�÷��̾ �ൿ�� �ٲٸ� �ƹ�Ÿ ���� �ʿ�
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
	IMAGEMANAGER->render("UI_���ùڽ�", hdc, rcTemp.left, rcTemp.top);
}

bool player::obstacle()
{
	/*
	���� �̵���Ų ��Ʈ�� Ÿ�� �Ӽ��� �˻��� �ش���� ������ �̵��ϰ� �ȴ�
	�»�, ����, ���, ���� 4���� ���� Ÿ�ϸ��� �����Ѵ�
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


	//���� �ʿ��� ������� ���θ� �Ǵ��Ѵ�
	if (moveRectTemp.left<0 || moveRectTemp.right> tileMapTemp.getTileMapSize().x*(TILE_SIZE_X)
		|| moveRectTemp.top<0 || moveRectTemp.bottom>tileMapTemp.getTileMapSize().y*(TILE_SIZE_Y))				return false;

	//�̵��� 4���� ���� �����Ѵ�.
	//�»�
	terrainkindTemp = tileMapTemp.getKindTerrian(leftTop.x, leftTop.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//Ÿ�� �Ӽ� �˻�
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
		//������Ʈ �˻�
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

	//����
	terrainkindTemp = tileMapTemp.getKindTerrian(leftBottom.x, leftBottom.y);
	if (!tileMapTemp.getIsTerrain(leftBottom.x, leftBottom.y) || tileMapTemp.getIsObject(leftBottom.x, leftBottom.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//Ÿ�� �Ӽ� �˻�
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
		//������Ʈ �˻�
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

	//���
	terrainkindTemp = tileMapTemp.getKindTerrian(rightTop.x, rightTop.y);
	if (!tileMapTemp.getIsTerrain(rightTop.x, rightTop.y) || tileMapTemp.getIsObject(rightTop.x, rightTop.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//Ÿ�� �Ӽ� �˻�
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
		//������Ʈ �˻�
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

	//����
	terrainkindTemp = tileMapTemp.getKindTerrian(rightBottom.x, rightBottom.y);
	if (!tileMapTemp.getIsTerrain(rightBottom.x, rightBottom.y) || tileMapTemp.getIsObject(rightBottom.x, rightBottom.y)
		|| terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || terrainkindTemp == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		//Ÿ�� �Ӽ� �˻�
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
		//������Ʈ �˻�
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

	//npc�˻�
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


	//�̲����� ó��
	if (_playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		//���˻�

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
		//�Ʒ��˻�

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
		//���˻�

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

		//�Ʒ��˻�

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
		//���ʰ˻�

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

		//�����ʰ˻�

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
		//���ʰ˻�

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

		//�����ʰ˻�

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
