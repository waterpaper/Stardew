#include "stdafx.h"
#include "npc.h"


npc::npc()
{
}


npc::~npc()
{
}

HRESULT npc::init()
{
	_position = POINT{ 0,0 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_NULL;
	_speed = 3;

	_characterImg = nullptr;
	_portraitImg = nullptr;
	_feelingImg = nullptr;

	_aniCharacterImg = nullptr;

	_moveTime = 0;
	_idleTime = 0;
	_settingTime = 0;

	blue = CreateSolidBrush(RGB(0, 0, 255));

	_shadow = IMAGEMANAGER->findImage("그림자");
	_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_DownMove");

	return S_OK;
}

void npc::update()
{
	/*
	npc의 행동을 업데이트 한다
	대기 상태시 확률적으로 대기 상태와 움직이는 상태로 바뀌게 되고
	방향 또한 같이 바뀌게 된다
	그리고 대기 상태가 나오면 랜덤한 시간동안 다음 행동 상태정의를 지연시킨다

	움직일시에는 방향이 바뀌면 안되므로 움직이는 타임이 지나면 대기 상태로 바꾸면서 다음상태를 정의한다
	*/
	NPC_ACTION action;
	NPC_DIRECTION direction;

	if (_action == NPC_ACTION::NPC_ACTION_MOVE)
	{
		move();
		if (GetTickCount() - _moveTime > 2000)
		{
			action = NPC_ACTION::NPC_ACTION_IDLE;
			_idleTime = GetTickCount();
			_settingTime = RND->getFromIntTo(4000, 6000);

			actionUpdate(action, _direction);
		}
	}

	if (_action == NPC_ACTION::NPC_ACTION_IDLE)
	{
		if (GetTickCount() - _idleTime >= _settingTime)
		{
			int num = RND->getInt(100);

			if (num >= 35)
			{
				action = NPC_ACTION::NPC_ACTION_IDLE;
				_idleTime = GetTickCount();
				_settingTime = RND->getFromIntTo(4000, 6000);
			}
			else
			{
				action = NPC_ACTION::NPC_ACTION_MOVE;
				_moveTime = GetTickCount();
			}

			num = RND->getInt(40);
			if (num < 5)
			{
				direction = NPC_DIRECTION::NPC_DIRECTION_DOWN;
				actionUpdate(action, direction);
			}
			else if (num < 10)
			{
				direction = NPC_DIRECTION::NPC_DIRECTION_RIGHT;
				actionUpdate(action, direction);
			}
			else if (num < 15)
			{
				direction = NPC_DIRECTION::NPC_DIRECTION_UP;
				actionUpdate(action, direction);
			}
			else if (num < 20)
			{
				direction = NPC_DIRECTION::NPC_DIRECTION_LEFT;
				actionUpdate(action, direction);
			}
			else
			{
				actionUpdate(action, _direction);
			}
		}
	}
}

void npc::render(HDC hdc, int sceneName)
{
	if ((INGAMESCENE_NAME)sceneName == _locationScene)
	{
		if (_isDebug)
		{
			RectangleMake(hdc, _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top);
			oBrush = (HBRUSH)SelectObject(hdc, blue);
			Rectangle(hdc, _collisionRc.left, _collisionRc.top, _collisionRc.right, _collisionRc.bottom);
			SelectObject(hdc, oBrush);
		}

		_shadow->render(hdc, _position.x - 24 + 6, _rc.bottom - 14);
		_characterImg->aniRender(hdc, _rc.left, _rc.top, _aniCharacterImg);
	}
}

void npc::release()
{
}

void npc::actionUpdate(NPC_ACTION action, NPC_DIRECTION direction)
{
	if (_action == NPC_ACTION::NPC_ACTION_IDLE &&
		action == NPC_ACTION::NPC_ACTION_IDLE)
	{
		_aniCharacterImg->stop();
		return;
	}//플레이어가 대기 상태일때 대기 상태가 업데이트 되면 업데이트가 필요없어 브레이크한다

	/*
	//움직이는 것 도중 처리를 막아주는 예외처리
	if ((_action == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		_action == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
		&& _playerAvatar.playerAniIsPlay())
		return;
		*/

	if (action == NPC_ACTION::NPC_ACTION_MOVE)
	{
		if (direction != _direction || _action != _action)										//플레이어가 방향을 바꾸거나 행동을 바꾸면 아바타 변경 필요
		{
			if (direction == NPC_DIRECTION::NPC_DIRECTION_DOWN)
			{
				_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_DownMove");
			}
			else if (direction == NPC_DIRECTION::NPC_DIRECTION_RIGHT)
			{
				_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_RightMove");
			}
			else if (direction == NPC_DIRECTION::NPC_DIRECTION_UP)
			{
				_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_UpMove");
			}
			else if (direction == NPC_DIRECTION::NPC_DIRECTION_LEFT)
			{
				_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_LeftMove");
			}
			_action = action;
			_direction = direction;

			_aniCharacterImg->start();
		}
	}
	else if (action == NPC_ACTION::NPC_ACTION_IDLE)
	{
		_action = action;
		_direction = direction;
		_aniCharacterImg->stop();

		if (direction == NPC_DIRECTION::NPC_DIRECTION_DOWN)
		{
			_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_DownMove");
		}
		else if (direction == NPC_DIRECTION::NPC_DIRECTION_RIGHT)
		{
			_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_RightMove");
		}
		else if (direction == NPC_DIRECTION::NPC_DIRECTION_UP)
		{
			_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_UpMove");
		}
		else if (direction == NPC_DIRECTION::NPC_DIRECTION_LEFT)
		{
			_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_LeftMove");
		}
	}
}

void npc::move()
{
	POINT pointTemp = { _position.x, _position.y };
	RECT collisionTemp;

	if (_direction == NPC_DIRECTION::NPC_DIRECTION_DOWN)
	{
		pointTemp.y += _speed;
	}
	else if (_direction == NPC_DIRECTION::NPC_DIRECTION_RIGHT)
	{
		pointTemp.x += _speed;
	}
	else if (_direction == NPC_DIRECTION::NPC_DIRECTION_UP)
	{
		pointTemp.y -= _speed;
	}
	else if (_direction == NPC_DIRECTION::NPC_DIRECTION_LEFT)
	{
		pointTemp.x -= _speed;
	}

	collisionTemp = RectMakeCenter(pointTemp.x, pointTemp.y + 24, 48, 48);

	if (!NPCMANAGER->objectCollision(collisionTemp)||NPCMANAGER->playerCollision(collisionTemp) || NPCMANAGER->getvNpcCollision(collisionTemp))
	{
		_action = NPC_ACTION::NPC_ACTION_IDLE;
		_idleTime = GetTickCount();
		_settingTime = RND->getFromIntTo(4000, 6000);
		actionUpdate(_action, _direction);
		return;
	}

	_position = pointTemp;
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
}

void npc::setAnimaiton(const char* key)
{
	_aniCharacterImg = ANIMATIONMANAGER->findAnimation(key);
}
