#pragma once
#include "singletonBase.h"
#include "player.h"

class playerManager : public singletonBase<playerManager>
{
private:
	player _player;
	bool _isTake;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	color getPlayerHairColor() { return _player.getPlayerHairColor(); };
	color getPlayerPantsColor() { return _player.getPlayerPantsColor(); };
	int getPlayerHairNum() { return _player.getPlayerHairNum(); };
	int getPlayerShirtsNum() { return _player.getPlayerShirtsNum(); };

	void setPlayerHairColor(color hairColor) { _player.setPlayerHairColor(hairColor); };
	void setPlayerPantsColor(color pantsColor) { _player.setPlayerPantsColor(pantsColor); };
	void setPlayerHairNum(int num) { _player.setPlayerHairNum(num); };
	void setPlayerShirtsNum(int num) { _player.setPlayerShirtsNum(num); };
	void setPlayerAvatarMoveSetting() { 
		_isTake = false;
	_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_IDLE, _player.getPlayerState().getPlayerDirection());
	_player.isPlayerAniStop();
	};
	void setPlayerAvatarTakeMoveSetting() { 
		_isTake = true;
		_player.update(PLAYER_ACTIVE_STATE::PLAYER_ACTIVE_STATE_TAKEMOVEIDLE, _player.getPlayerState().getPlayerDirection());
		_player.isPlayerAniStop();
	};

	playerState getPlayerState() { return _player.getPlayerState(); };
	playerAvatar getPlayerAvatar() { return _player.getPlayerAvatar(); };

	int getPlayerMoney() { return _player.getPlayerMoney(); };

	void setPlayerMoney(int money) { _player.setPlayerMoney(money); };
	void setPlayerPosition(float x, float y) { _player.setPlayerPosition(x, y); };
	void setPlayerName(string name) { _player.setPlayerName(name); };
	void setPlayerFarmName(string farmName) { _player.setPlayerFarmName(farmName); };
	void setPlayerHp(int Hp) { _player.setPlayerHp(Hp); };
	void setPlayerActingPower(int actingpower) { _player.setPlayerActingPower(actingpower); };
	void setTarget();

	void setPlayerFull_Hp_Actingpower() { _player.setPlayerFull_Hp_Actingpower(); };
};

