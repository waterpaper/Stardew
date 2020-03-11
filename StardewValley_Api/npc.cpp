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

	_shadow = IMAGEMANAGER->findImage("�׸���");
	_aniCharacterImg = ANIMATIONMANAGER->findAnimation(_name + "_DownMove");

	return S_OK;
}

void npc::update()
{
	/*
	npc�� �ൿ�� ������Ʈ �Ѵ�
	��� ���½� Ȯ�������� ��� ���¿� �����̴� ���·� �ٲ�� �ǰ�
	���� ���� ���� �ٲ�� �ȴ�
	�׸��� ��� ���°� ������ ������ �ð����� ���� �ൿ �������Ǹ� ������Ų��

	�����Ͻÿ��� ������ �ٲ�� �ȵǹǷ� �����̴� Ÿ���� ������ ��� ���·� �ٲٸ鼭 �������¸� �����Ѵ�
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
	}//�÷��̾ ��� �����϶� ��� ���°� ������Ʈ �Ǹ� ������Ʈ�� �ʿ���� �극��ũ�Ѵ�

	/*
	//�����̴� �� ���� ó���� �����ִ� ����ó��
	if ((_action == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE ||
		_action == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
		&& _playerAvatar.playerAniIsPlay())
		return;
		*/

	if (action == NPC_ACTION::NPC_ACTION_MOVE)
	{
		if (direction != _direction || _action != _action)										//�÷��̾ ������ �ٲٰų� �ൿ�� �ٲٸ� �ƹ�Ÿ ���� �ʿ�
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
