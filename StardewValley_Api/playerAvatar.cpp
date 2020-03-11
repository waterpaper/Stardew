#include "stdafx.h"
#include "playerAvatar.h"


playerAvatar::playerAvatar()
{
	playerAnimationAdd();

	_playerAniBody = ANIMATIONMANAGER->findAnimation("playerAniBody_DownMove");
	_playerAniArm = ANIMATIONMANAGER->findAnimation("playerAniArm_DownMove");
	_playerAniPants = ANIMATIONMANAGER->findAnimation("playerAniPants_DownMove");

	blue = CreateSolidBrush(RGB(0, 0, 255));
}


playerAvatar::~playerAvatar()
{
}

HRESULT playerAvatar::init()
{
	_hairR = 0, _hairG = 0, _hairB = 0;
	_pantsR = 0, _pantsG = 0, _pantsB = 0;
	_hairFrameX = 0, _hairFrameY = 0;
	_shirtsFrameX = 0, _shirtsFrameY = 0;

	_playerHair = IMAGEMANAGER->findImage("playerHair");
	_playerBody = IMAGEMANAGER->findImage("playerBody");
	_playerArm = IMAGEMANAGER->findImage("playerArm");
	_playerShirts = IMAGEMANAGER->findImage("playerShirts");
	_playerPants = IMAGEMANAGER->findImage("playerPants");
	_shadow = IMAGEMANAGER->findImage("그림자");

	playerHairColor(color{ _hairR, _hairG, _hairB });
	playerPantsColor(color{ _pantsR, _pantsG, _pantsB });

	return S_OK;
}
void playerAvatar::release()
{

}

void playerAvatar::update(playerState playerState)
{
	if (playerAniIsPlay()) return;																//애니메이션이 진행중일때에는 다시 시작하지 않기 위해서 리턴한다

	string strTempBody, strTempArm, strTempPants;

	//각 방향별 정의
	//각 방향에 맞는 스트링과 프레임을 설정해준다
	if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
	{
		_hairFrameY = 0;
		_shirtsFrameY = 0;
		strTempBody = "playerAniBody_Down";
		strTempArm = "playerAniArm_Down";
		strTempPants = "playerAniPants_Down";
	}
	else if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
	{
		_hairFrameY = 1;
		_shirtsFrameY = 1;
		strTempBody = "playerAniBody_Right";
		strTempArm = "playerAniArm_Right";
		strTempPants = "playerAniPants_Right";
	}
	else if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
	{
		_hairFrameY = 2;
		_shirtsFrameY = 2;
		strTempBody = "playerAniBody_Left";
		strTempArm = "playerAniArm_Left";
		strTempPants = "playerAniPants_Left";
	}
	else if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP)
	{
		_hairFrameY = 3;
		_shirtsFrameY = 3;
		strTempBody = "playerAniBody_Up";
		strTempArm = "playerAniArm_Up";
		strTempPants = "playerAniPants_Up";
	}

	//각 행동별 정의
	//방향에 각 행동을 추가하여 애니메이션을 설정, 실행해준다 
	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE ||
		playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE)
	{
		_playerAniBody = ANIMATIONMANAGER->findAnimation(strTempBody + "Move");
		_playerAniArm = ANIMATIONMANAGER->findAnimation(strTempArm + "Move");
		_playerAniPants = ANIMATIONMANAGER->findAnimation(strTempPants + "Move");

		if (!(playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE))
		{
			playerActiveStart();
		}
	}
	else if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK ||
		playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE)
	{
		_playerAniBody = ANIMATIONMANAGER->findAnimation(strTempBody + "Attack");
		_playerAniArm = ANIMATIONMANAGER->findAnimation(strTempArm + "Attack");
		_playerAniPants = ANIMATIONMANAGER->findAnimation(strTempPants + "Attack");
		playerActiveStart();
	}
	else if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE ||
		playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE ||
		playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE)
	{
		_playerAniBody = ANIMATIONMANAGER->findAnimation(strTempBody + "Smash");
		_playerAniArm = ANIMATIONMANAGER->findAnimation(strTempArm + "Smash");
		_playerAniPants = ANIMATIONMANAGER->findAnimation(strTempPants + "Smash");
		playerActiveStart();
	}
	else if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
	{
		_playerAniBody = ANIMATIONMANAGER->findAnimation(strTempBody + "Watering");
		_playerAniArm = ANIMATIONMANAGER->findAnimation(strTempArm + "Watering");
		_playerAniPants = ANIMATIONMANAGER->findAnimation(strTempPants + "Watering");
		playerActiveStart();
	}
	else if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE||
		playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE)
	{
		_playerAniBody = ANIMATIONMANAGER->findAnimation(strTempBody + "TakeMove");
		_playerAniArm = ANIMATIONMANAGER->findAnimation(strTempArm + "TakeMove");
		_playerAniPants = ANIMATIONMANAGER->findAnimation(strTempPants + "TakeMove");
		if (!(playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE))
		{
			playerActiveStart();
		}
	}

}

void playerAvatar::render(HDC hdc, playerState playerState)
{
	int x = playerState.getPlayerPositionX() - playerState.getPlayerWitdh() / 2;
	int y = playerState.getPlayerPositionY() - playerState.getPlayerHeight() / 2;
	RECT rectTemp = playerState.getPlayerRc();
	RECT rectTemp2 = playerState.getPlayerCollisionRc();

	if(_isDebug)
	{ 
		Rectangle(hdc, rectTemp.left, rectTemp.top, rectTemp.right, rectTemp.bottom);
		oBrush = (HBRUSH)SelectObject(hdc, blue);
		Rectangle(hdc, rectTemp2.left, rectTemp2.top, rectTemp2.right, rectTemp2.bottom);
		SelectObject(hdc, oBrush);
	}

	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE)
	{
		if (_playerAniBody->getFrameIndex() % 2 == 0)
		{
			_shadow->render(hdc, x + 6, playerState.getPlayerPositionY() + playerState.getPlayerHeight() / 2 - 14);
		}
		else
		{
			_shadow->render(hdc, x + 10, playerState.getPlayerPositionY() + playerState.getPlayerHeight() / 2 - 14,24,16);
		}
	}
	else
	{
		_shadow->render(hdc, x + 6, playerState.getPlayerPositionY() + playerState.getPlayerHeight() / 2 - 14);
	}
	
	_playerBody->aniRender(hdc, x, y, _playerAniBody);
	_playerPants->aniRender(hdc, x, y, _playerAniPants);
	hairShirtsRender(hdc, playerState, x, y);
	_playerArm->aniRender(hdc, x, y, _playerAniArm);
}

void playerAvatar::hairShirtsRender(HDC hdc, playerState playerState, int x, int y)
{
	//걸을때 높낮이 조절 처리하기 위함
	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_MOVE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE)
	{
		if (_playerAniBody->getFrameIndex() == 0)
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y, _hairFrameX, _hairFrameY);
		}
		else
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 + 2, _shirtsFrameX, _shirtsFrameY);
			if ((playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN) &&
				(_playerAniBody->getFrameIndex() == 2 || _playerAniBody->getFrameIndex() == 4))
			{
				_playerHair->frameRender(hdc, x, y + 6, _hairFrameX, _hairFrameY);
			}
			else
			{
				_playerHair->frameRender(hdc, x, y + 3, _hairFrameX, _hairFrameY);
			}
		}
	}

	//공격시 높낮이 조절 처리하기 위함
	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_ATTACK
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_SCYTHE)
	{
		int temp = 3 * _playerAniBody->getFrameIndex();

		if ((playerState.getPlayerDirection() != PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN) && temp > 3)
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y + 3, _hairFrameX, _hairFrameY);
		}
		else
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - 2 + temp, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y - 3 + temp, _hairFrameX, _hairFrameY);
		}
	}

	//스매쉬시 높낮이 조절 처리하기 위함
	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_AXE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_HOE
		|| playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_PICKAXE)
	{
		int temp = _playerAniBody->getFrameIndex() * 3;

		if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
		{
			temp -= 9;
		}

		if ((playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_UP))
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - 3, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y, _hairFrameX, _hairFrameY);
		}
		else if (temp == 12)
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - 3, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y - 3, _hairFrameX, _hairFrameY);
		}
		else
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - temp, _shirtsFrameX, _shirtsFrameY);
			_playerHair->frameRender(hdc, x, y - temp + 3, _hairFrameX, _hairFrameY);
		}
	}

	//물뿌리개시 높낮이 조절 처리하기 위함
	if (playerState.getPlayerActiveStateNow() == PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_WATERING)
	{
		if (_playerAniBody->getFrameIndex() == 0)
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 + 6, _shirtsFrameX, _shirtsFrameY);

			if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
			{
				_playerHair->frameRender(hdc, x, y + 12, _hairFrameX, _hairFrameY);
			}
			else
			{
				_playerHair->frameRender(hdc, x, y + 6, _hairFrameX, _hairFrameY);
			}
		}
		else if (_playerAniBody->getFrameIndex() == 1)
		{
			_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 + 3, _shirtsFrameX, _shirtsFrameY);
			if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
			{
				_playerHair->frameRender(hdc, x, y + 9, _hairFrameX, _hairFrameY);
			}
			else
			{
				_playerHair->frameRender(hdc, x, y + 3, _hairFrameX, _hairFrameY);
			}
		}
		else if (_playerAniBody->getFrameIndex() == 2)
		{
			if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_DOWN)
			{
				_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - 6, _shirtsFrameX, _shirtsFrameY);
			}
			else
			{
				_playerShirts->frameRender(hdc, x + 4 * 3, y + 15 * 3 - 12, _shirtsFrameX, _shirtsFrameY);
			}

			if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_LEFT)
			{
				_playerHair->frameRender(hdc, x + 6, y - 9, _hairFrameX, _hairFrameY);
			}
			else if (playerState.getPlayerDirection() == PLAYER_DIRECTION::PLAYER_DIRECTION_RIGHT)
			{
				_playerHair->frameRender(hdc, x - 3, y - 9, _hairFrameX, _hairFrameY);
			}
			else
			{
				_playerHair->frameRender(hdc, x, y - 9, _hairFrameX, _hairFrameY);
			}
		}
	}
}

void playerAvatar::playerAnimationAdd()
{
	//플레이어 움직임 애니메이션을 상하좌우로 경우에 맞게 추가합니다
	//움직임
	ANIMATIONMANAGER->addAnimation("playerAniBody_DownMove", "playerBody", 0 * 6, 0 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_DownMove", "playerArm", 0 * 6, 0 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_DownMove", "playerPants", 0 * 6, 0 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_RightMove", "playerBody", 1 * 6, 1 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_RightMove", "playerArm", 1 * 6, 1 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_RightMove", "playerPants", 1 * 6, 1 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_LeftMove", "playerBody", 2 * 6, 2 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_LeftMove", "playerArm", 2 * 6, 2 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_LeftMove", "playerPants", 2 * 6, 2 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_UpMove", "playerBody", 3 * 6, 3 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_UpMove", "playerArm", 3 * 6, 3 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_UpMove", "playerPants", 3 * 6, 3 * 6 + 4, 8, false, true);

	//공격모션(낫질포함)
	ANIMATIONMANAGER->addAnimation("playerAniBody_DownAttack", "playerBody", 4 * 6, 4 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_DownAttack", "playerArm", 4 * 6, 4 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_DownAttack", "playerPants", 4 * 6, 4 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_RightAttack", "playerBody", 5 * 6, 5 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_RightAttack", "playerArm", 5 * 6, 5 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_RightAttack", "playerPants", 5 * 6, 5 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_LeftAttack", "playerBody", 6 * 6, 6 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_LeftAttack", "playerArm", 6 * 6, 6 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_LeftAttack", "playerPants", 6 * 6, 6 * 6 + 5, 20, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_UpAttack", "playerBody", 7 * 6, 7 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_UpAttack", "playerArm", 7 * 6, 7 * 6 + 5, 20, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_UpAttack", "playerPants", 7 * 6, 7 * 6 + 5, 20, false, false);

	//스매쉬모션(도끼, 호미, 곡괭이)
	ANIMATIONMANAGER->addAnimation("playerAniBody_DownSmash", "playerBody", 8 * 6, 8 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_DownSmash", "playerArm", 8 * 6, 8 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_DownSmash", "playerPants", 8 * 6, 8 * 6 + 4, 10, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_RightSmash", "playerBody", 9 * 6, 9 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_RightSmash", "playerArm", 9 * 6, 9 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_RightSmash", "playerPants", 9 * 6, 9 * 6 + 4, 10, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_LeftSmash", "playerBody", 10 * 6, 10 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_LeftSmash", "playerArm", 10 * 6, 10 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_LeftSmash", "playerPants", 10 * 6, 10 * 6 + 4, 10, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_UpSmash", "playerBody", 11 * 6, 11 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_UpSmash", "playerArm", 11 * 6, 11 * 6 + 4, 10, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_UpSmash", "playerPants", 11 * 6, 11 * 6 + 4, 10, false, false);

	//물뿌리개 모션
	ANIMATIONMANAGER->addAnimation("playerAniBody_DownWatering", "playerBody", 12 * 6, 12 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_DownWatering", "playerArm", 12 * 6, 12 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_DownWatering", "playerPants", 12 * 6, 12 * 6 + 2, 5, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_RightWatering", "playerBody", 13 * 6, 13 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_RightWatering", "playerArm", 13 * 6, 13 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_RightWatering", "playerPants", 13 * 6, 13 * 6 + 2, 5, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_LeftWatering", "playerBody", 14 * 6, 14 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_LeftWatering", "playerArm", 14 * 6, 14 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_LeftWatering", "playerPants", 14 * 6, 14 * 6 + 2, 5, false, false);

	ANIMATIONMANAGER->addAnimation("playerAniBody_UpWatering", "playerBody", 15 * 6, 15 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniArm_UpWatering", "playerArm", 15 * 6, 15 * 6 + 2, 5, false, false);
	ANIMATIONMANAGER->addAnimation("playerAniPants_UpWatering", "playerPants", 15 * 6, 15 * 6 + 2, 5, false, false);

	//물건 들기 모션
	ANIMATIONMANAGER->addAnimation("playerAniBody_DownTakeMove", "playerBody", 0 * 6, 0 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_DownTakeMove", "playerArm", 16 * 6, 16 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_DownTakeMove", "playerPants", 0 * 6, 0 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_RightTakeMove", "playerBody", 1 * 6, 1 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_RightTakeMove", "playerArm", 17 * 6, 17 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_RightTakeMove", "playerPants", 1 * 6, 1 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_LeftTakeMove", "playerBody", 2 * 6, 2 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_LeftTakeMove", "playerArm", 18 * 6, 18 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_LeftTakeMove", "playerPants", 2 * 6, 2 * 6 + 4, 8, false, true);

	ANIMATIONMANAGER->addAnimation("playerAniBody_UpTakeMove", "playerBody", 3 * 6, 3 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniArm_UpTakeMove", "playerArm", 19 * 6, 19 * 6 + 4, 8, false, true);
	ANIMATIONMANAGER->addAnimation("playerAniPants_UpTakeMove", "playerPants", 3 * 6, 3 * 6 + 4, 8, false, true);
}

bool playerAvatar::playerAniIsPlay()
{
	if (_playerAniBody->isPlay())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void playerAvatar::playerActiveStart()
{
	if (!_playerAniBody->isPlay())
	{
		_playerAniBody->start();
		_playerAniArm->start();
		_playerAniPants->start();
	}
}

void playerAvatar::playerActiveEnd()
{
	if (_playerAniBody->isPlay())
	{
		_playerAniBody->stop();
		_playerAniArm->stop();
		_playerAniPants->stop();
	}
}

void playerAvatar::playerHairColor(color hairColor)
{
	_hairR = hairColor.r;
	_hairG = hairColor.g;
	_hairB = hairColor.b;

	IMAGEMANAGER->deleteImage("playerHair");
	IMAGEMANAGER->addFrameImage("playerHair", "images/player/player_hairs.bmp", 512 * 3, 128 * 3, 32, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->setColorImage("playerHair", RGB(_hairR, _hairG, _hairB), RGB(255, 0, 255));
	_playerHair = IMAGEMANAGER->findImage("playerHair");
}

void playerAvatar::playerPantsColor(color pantsColor)
{
	_pantsR = pantsColor.r;
	_pantsG = pantsColor.g;
	_pantsB = pantsColor.b;

	IMAGEMANAGER->deleteImage("playerPants");
	IMAGEMANAGER->addFrameImage("playerPants", "images/player/player_pants.bmp", 96 * 3, 512 * 3, 6, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->setColorImage("playerPants", RGB(_pantsR, _pantsG, _pantsB), RGB(255, 0, 255));
	_playerPants = IMAGEMANAGER->findImage("playerPants");
}
