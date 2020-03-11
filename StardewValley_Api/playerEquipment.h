#pragma once
#include "playerState.h"

class playerEquipment
{
private:
	image *_equipmentImage;
	animation *_equipmentAni;

public:
	playerEquipment();
	~playerEquipment();

	bool isAvailable(PLAYER_ACTIVE_STATE state, int x, int y);

	void init();
	void update(playerState state);
	void render(HDC hdc, playerState state);
	void aniAdd();

	bool equipAniIsPlay();									//����� �ִϸ��̼��� ���������� �˻��մϴ�.
	void equipAniStop();									//����� �ִϸ��̼��� �����մϴ�.

	void equipment_axeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
	void equipment_pickaxeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
	void equipment_hoeRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
	void equipment_wateringcanRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
	void equipment_scytheRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
	void equipment_attackRender(HDC hdc, int x, int y, PLAYER_DIRECTION direction);
};

