#include "stdafx.h"
#include "animal.h"


animal::animal()
{
}


animal::~animal()
{
}


HRESULT animal::init(ANIMAL_KIND kind, int period)
{
	_kind = kind;
	_moveTime = 0;
	_idleTime = 0;
	_settingTime = 0;
	_isDayProduction = true;

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린닭");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_닭");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width=48, _height = 48;

		_posX = RND->getFromIntTo(336 + 24, 816 - 24);
		_posY = RND->getFromIntTo(384 + 24, 720 - 24);

		_rc = RectMakeCenter(_posX, _posY, 48, 48);
		while (ANIMALMANAGER->coopRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(336 + 24, 816 - 24);
			_posY = RND->getFromIntTo(384 + 24, 720 - 24);

			_rc = RectMakeCenter(_posX, _posY, 48, 48);
		}
	}
	if (_kind == ANIMAL_KIND::ANIMAL_KIND_DUCK)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린오리");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_오리");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 48, _height = 48;

		_posX = RND->getFromIntTo(336 + 24, 816 - 24);
		_posY = RND->getFromIntTo(384 + 24, 720 - 24);

		_rc = RectMakeCenter(_posX, _posY, 48, 48);
		while (ANIMALMANAGER->coopRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(336 + 24, 816 - 24);
			_posY = RND->getFromIntTo(384 + 24, 720 - 24);

			_rc = RectMakeCenter(_posX, _posY, 48, 48);
		}
	}

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린토끼");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_토끼");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 48, _height = 48;

		_posX = RND->getFromIntTo(336 + 24, 816 - 24);
		_posY = RND->getFromIntTo(384 + 24, 720 - 24);

		_rc = RectMakeCenter(_posX, _posY, 48, 48);

		while (ANIMALMANAGER->coopRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(336 + 24, 816 - 24);
			_posY = RND->getFromIntTo(384 + 24, 720 - 24);

			_rc = RectMakeCenter(_posX, _posY, 48, 48);
		}
	}

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_COW)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린소");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_소");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 96, _height = 96;

		_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
		_posY = RND->getFromIntTo(288 + 48, 678 - 48);

		_rc = RectMakeCenter(_posX, _posY, 96, 96);

		while (ANIMALMANAGER->barnRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
			_posY = RND->getFromIntTo(288 + 48, 912 - 48);

			_rc = RectMakeCenter(_posX, _posY, 96, 96);
		}
	}

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린양");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_양");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 96, _height = 96;

		_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
		_posY = RND->getFromIntTo(288 + 48, 912 - 48);

		_rc = RectMakeCenter(_posX, _posY, 96, 96);

		while (ANIMALMANAGER->barnRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
			_posY = RND->getFromIntTo(288 + 48, 912 - 48);

			_rc = RectMakeCenter(_posX, _posY, 96, 96);
		}
	}

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_GOAT)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린젖소");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_젖소");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 96, _height = 96;

		_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
		_posY = RND->getFromIntTo(288 + 48, 912 - 48);

		_rc = RectMakeCenter(_posX, _posY, 96, 96);

		while (ANIMALMANAGER->barnRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
			_posY = RND->getFromIntTo(288 + 48, 912 - 48);

			_rc = RectMakeCenter(_posX, _posY, 96, 96);
		}
	}

	if (_kind == ANIMAL_KIND::ANIMAL_KIND_PIG)
	{
		if (period < 4)
		{
			_img = IMAGEMANAGER->findImage("동물_어린돼지");
			_isBaby = true;
		}
		else
		{
			_img = IMAGEMANAGER->findImage("동물_돼지");
			_isBaby = false;
		}
		_frame = POINT{ 0, 0 };
		_frameCount = 0;
		_width = 96, _height = 96;

		_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
		_posY = RND->getFromIntTo(288 + 48, 912 - 48);

		_rc = RectMakeCenter(_posX, _posY, 96, 96);

		while (ANIMALMANAGER->barnRectCollision(_rc))
		{
			_posX = RND->getFromIntTo(144 + 48, 1008 - 48);
			_posY = RND->getFromIntTo(288 + 48, 912 - 48);

			_rc = RectMakeCenter(_posX, _posY, 96, 96);
		}
	}
	_speed = 3;

	_dirction = ANIMAL_DIRECTION::ANIMAL_DIRECTION_DOWN;

	return S_OK;
}

void animal::update()
{
	/*
	애니멀의 행동을 업데이트 한다
	대기 상태시 확률적으로 대기 상태와 움직이는 상태로 바뀌게 되고
	방향 또한 같이 바뀌게 된다
	그리고 대기 상태가 나오면 랜덤한 시간동안 다음 행동 상태정의를 지연시킨다

	움직일시에는 방향이 바뀌면 안되므로 움직이는 타임이 지나면 대기 상태로 바꾸면서 다음상태를 정의한다
	*/
	if (_acting == ANIMAL_ACTING::ANIMAL_ACTING_MOVE)
	{
		frameAnimation();

		if (GetTickCount() - _moveTime > 1000)
		{
			_acting = ANIMAL_ACTING::ANIMAL_ACTING_IDLE;
			_idleTime = GetTickCount();
			_settingTime = RND->getFromIntTo(2000, 4000);
			_frame.x = 0;
		}
	}

	if (_acting == ANIMAL_ACTING::ANIMAL_ACTING_IDLE)
	{
		if (GetTickCount() - _idleTime >= _settingTime)
		{
			int num = RND->getInt(100);

			if (num >= 35)
			{
				_acting = ANIMAL_ACTING::ANIMAL_ACTING_IDLE;
				_idleTime = GetTickCount();
				_settingTime = RND->getFromIntTo(2000, 4000);
			}
			else
			{
				_acting = ANIMAL_ACTING::ANIMAL_ACTING_MOVE;
				_moveTime = GetTickCount();
			}

			num = RND->getInt(40);
			if (num < 5)
			{
				_dirction = ANIMAL_DIRECTION::ANIMAL_DIRECTION_DOWN;
				_frame.y = 0;
			}
			else if (num < 10)
			{
				_dirction = ANIMAL_DIRECTION::ANIMAL_DIRECTION_RIGHT;
				_frame.y = 1;
			}
			else if (num < 15)
			{
				_dirction = ANIMAL_DIRECTION::ANIMAL_DIRECTION_UP;
				_frame.y = 2;
			}
			else if (num < 20)
			{
				_dirction = ANIMAL_DIRECTION::ANIMAL_DIRECTION_LEFT;
				_frame.y = 3;
			}
		}
	}

}

void animal::render(HDC hdc)
{
	_img->frameRender(hdc, _rc.left, _rc.top, _frame.x, _frame.y);
}

void animal::release()
{

}

void animal::frameAnimation()
{
	_frameCount++;
	if (_frameCount == 20)
	{
		_frameCount = 0;
		_frame.x += 1;

		if (_frame.x >= 4)
		{
			_frame.x = 0;
		}
	}
}

void animal::setIsBaby(bool isbaby)
{
	_isBaby = isbaby;

	if (_isBaby)
	{
		if (_kind==ANIMAL_KIND::ANIMAL_KIND_CHICKEN)
		{
			_img = IMAGEMANAGER->findImage("동물_닭");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_DUCK)
		{
			_img = IMAGEMANAGER->findImage("동물_오리");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_RABBIT)
		{
			_img = IMAGEMANAGER->findImage("동물_토끼");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_COW)
		{
			_img = IMAGEMANAGER->findImage("동물_소");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_GOAT)
		{
			_img = IMAGEMANAGER->findImage("동물_젖소");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_SHEEP)
		{
			_img = IMAGEMANAGER->findImage("동물_양");
			_isBaby = false;
		}
		if (_kind == ANIMAL_KIND::ANIMAL_KIND_PIG)
		{
			_img = IMAGEMANAGER->findImage("동물_돼지");
			_isBaby = false;
		}
	}
}

