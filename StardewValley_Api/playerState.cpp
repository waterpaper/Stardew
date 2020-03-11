#include "stdafx.h"
#include "playerState.h"


playerState::playerState()
{
}


playerState::~playerState()
{
}

HRESULT playerState::init()
{
	_playerHp = 100;
	_playerMaxHp = 100;
	_playerActingPower = 200;
	_playerActingPowerMax = 200;
	_playerMoney = 100000;
	_playerWitdh = 16 * 3, _playerHeight = 32 * 3;
	_playerSpeed = 4;
	_playerPositionX = WINSIZEX / 2, _playerPositionY = WINSIZEY / 2;
	_playerRc = RectMakeCenter(_playerPositionX, _playerPositionY, _playerWitdh, _playerHeight);
	_playerCollisionRc = RectMakeCenter(_playerPositionX, _playerPositionY + 24, _playerWitdh, _playerHeight - 48);
	_playerActiveStateNow = PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE;
	_playerDirection = PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN;

	return S_OK;
}

void playerState::release()
{
}
