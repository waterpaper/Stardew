#pragma once
#include "playerState.h"
#include "playerAvatar.h"
#include "playerEquipment.h"

class player
{
private:
	playerState _playerState;
	playerAvatar _playerAvatar;
	playerEquipment _playerEquipment;

	POINT _target;

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update(PLAYER_ACTIVE_STATE playerActiveState, PLAYER_DIRECTION playerDirection);
	void render(HDC hdc);

	bool obstacle();
	void slideMove();

	playerState getPlayerState() { return _playerState; };
	playerAvatar getPlayerAvatar() { return _playerAvatar; };
	playerEquipment getPlayerEquipment() { return _playerEquipment; };
	bool isPlayerAniIsPlay() { return _playerAvatar.playerAniIsPlay(); };
	void isPlayerAniStop() { _playerAvatar.playerActiveEnd(); };

	color getPlayerHairColor() { return _playerAvatar.getPlayerHairColor(); };
	color getPlayerPantsColor() { return _playerAvatar.getPlayerPantsColor(); };
	int getPlayerHairNum() { return _playerAvatar.getPlayerHairNum(); };
	int getPlayerShirtsNum() { return _playerAvatar.getPlayerShirtsNum(); };
	int getPlayerMoney() { return _playerState.getPlayerMoney(); };
	int getPlayerActingPower() { return _playerState.getPlayerActingPower(); };
	POINT getTarget() { return _target; };


	void setPlayerHairColor(color hairColor) { _playerAvatar.playerHairColor(hairColor); };
	void setPlayerPantsColor(color pantsColor) { _playerAvatar.playerPantsColor(pantsColor); };
	void setPlayerHairNum(int num) { _playerAvatar.setPlayerHairNum(num); };
	void setPlayerShirtsNum(int num) { _playerAvatar.setPlayerShirtsNum(num); };

	void setPlayerPosition(float x, float y) { _playerState.setPlayerPosition(x, y); };
	void setPlayerName(string name) { _playerState.setPlayerName(name); };
	void setPlayerFarmName(string farmName) { _playerState.setPlayerFarmName(farmName); };
	void setPlayerMoney(int money) { _playerState.setPlayerMoney(money); };
	void setPlayerHp(int Hp) { _playerState.setPlayerHp(Hp); };
	void setPlayerActingPower(int actingpower) { _playerState.setPlayerActingPower(actingpower); };
	void setTarget(int x, int y) { _target.x = x, _target.y = y; };

	void setPlayerFull_Hp_Actingpower() {
		_playerState.setPlayerHp(_playerState.getPlayerMaxHp());
		_playerState.setPlayerActingPower(_playerState.getPlayerActingPowerMax());
	};
};

