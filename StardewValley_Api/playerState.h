#pragma once
enum PLAYER_ACTIVE_STATE
{
	PLAYER_ACTIVE_STATE_NULL = 0,
	PLAYER_ACTIVE_STATE_IDLE,
	PLAYER_ACTIVE_STATE_MOVE,
	PLAYER_ACTIVE_STATE_TAKEMOVEIDLE,
	PLAYER_ACTIVE_STATE_TAKEMOVE,
	PLAYER_ACTIVE_STATE_ATTACK,
	PLAYER_ACTIVE_STATE_SCYTHE,
	PLAYER_ACTIVE_STATE_WATERING,
	PLAYER_ACTIVE_STATE_HOE,
	PLAYER_ACTIVE_STATE_AXE,
	PLAYER_ACTIVE_STATE_PICKAXE,
	PLAYER_ACTIVE_STATE_END
};

enum PLAYER_DIRECTION
{
	PLAYER_DIRECTION_NULL = 0,
	PLAYER_DIRECTION_UP,
	PLAYER_DIRECTION_DOWN,
	PLAYER_DIRECTION_LEFT,
	PLAYER_DIRECTION_RIGHT,
	PLAYER_DIRECTION_END
};

class playerState
{
	/*
	//�÷��̾� ���¸� �����ϴ� Ŭ���� �Դϴ�.
	*/

private:
	string _playerName;								//�̸�
	string _playerFarmName;							//�����̸�
	int _playerHp;									//ü��
	int _playerMaxHp;								//ü���ִ�
	int _playerActingPower;							//�ൿ��
	int _playerActingPowerMax;						//�ൿ���ִ�
	int	_playerMoney;								//���� �ݾ�
	int _playerWitdh, _playerHeight;				//����, ����
	float _playerPositionX, _playerPositionY;		//��ġ
	float _playerSpeed;								//���ǵ�
	RECT _playerRc;									//�÷��̾� ��Ʈ
	RECT _playerCollisionRc;						//�÷��̾� �浹��Ʈ
	PLAYER_ACTIVE_STATE _playerActiveStateNow;		//�÷��̾��� ���� �ൿ����
	PLAYER_DIRECTION _playerDirection;				//�÷��̾��� ���� ����


public:
	playerState();
	~playerState();

	HRESULT init();
	void release();


	string getPlayerName() { return _playerName; };
	string getPlayerFarmName() { return _playerFarmName; };
	int getPlayerHp() { return _playerHp; };
	int getPlayerMaxHp() { return _playerMaxHp; };
	int getPlayerActingPower() { return _playerActingPower; };
	int getPlayerActingPowerMax() { return _playerActingPowerMax; };
	int getPlayerWitdh() { return _playerWitdh; };
	int getPlayerHeight() { return _playerHeight; };
	int getPlayerMoney() { return _playerMoney; };
	float getPlayerPositionX() { return _playerPositionX; };
	float getPlayerPositionY() { return _playerPositionY; };
	float getPlayerSpeed() { return _playerSpeed; };
	RECT getPlayerRc() { return _playerRc; };
	RECT getPlayerCollisionRc() { return _playerCollisionRc; };
	PLAYER_ACTIVE_STATE getPlayerActiveStateNow() { return _playerActiveStateNow; };
	PLAYER_DIRECTION getPlayerDirection() { return _playerDirection; };

	void setPlayerName(string playerName) { _playerName = playerName; };
	void setPlayerFarmName(string playerFarmName) { _playerFarmName = playerFarmName; };
	void setPlayerHp(int hp) { 
		_playerHp = hp; 
		if (_playerHp > _playerMaxHp)
		{
			_playerHp = _playerMaxHp;
		}
		else if (_playerHp < 0)
		{
			_playerHp = 0;
		}
	};
	void setPlayerMaxHp(int maxHp) { _playerMaxHp = maxHp; }
	void setPlayerActingPower(int actingPower) {
		_playerActingPower = actingPower; 
		if (_playerActingPower > _playerActingPowerMax)
		{
			_playerActingPower = _playerActingPowerMax;
		}
		else if (_playerActingPower < 0)
		{
			_playerActingPower = 0;
		}
	};
	void setPlayerActingPowerMax(int actingPowerMax) { _playerActingPowerMax = actingPowerMax; };
	void setPlayerWitdh(int width) { _playerWitdh = width; };
	void setPlayerHeight(int height) { _playerHeight = height; };
	void setPlayerMoney(int money) { _playerMoney = money; };
	void setPlayerPositionX(float positionX) { 
		_playerPositionX = positionX; 
		_playerRc = RectMakeCenter(_playerPositionX, _playerPositionY, _playerWitdh, _playerHeight);
		_playerCollisionRc = RectMakeCenter(_playerPositionX, _playerPositionY+24, _playerWitdh, _playerHeight-48);
	};
	void setPlayerPositionY(float positionY) {
		_playerPositionY = positionY; 
		_playerRc = RectMakeCenter(_playerPositionX, _playerPositionY, _playerWitdh, _playerHeight);
		_playerCollisionRc = RectMakeCenter(_playerPositionX, _playerPositionY+24, _playerWitdh, _playerHeight-48);
	};
	void setPlayerPosition(float positionX, float positionY) { 
		_playerPositionX = positionX, _playerPositionY = positionY; 
		_playerRc = RectMakeCenter(_playerPositionX, _playerPositionY, _playerWitdh, _playerHeight);
		_playerCollisionRc = RectMakeCenter(_playerPositionX, _playerPositionY+24, _playerWitdh, _playerHeight-48);
	};
	void setPlayerSpeed(float speed) { _playerSpeed = speed; };
	void setPlayerRc(RECT rc) { _playerRc = rc; };
	void setPlayerActiveStateNow(PLAYER_ACTIVE_STATE playerActiveStateNow) { _playerActiveStateNow = playerActiveStateNow; };
	void setPlayerDirection(PLAYER_DIRECTION playerDirection) { _playerDirection = playerDirection; };
};

