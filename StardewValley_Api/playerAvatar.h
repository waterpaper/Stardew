#pragma once
#include "playerState.h"

struct color
{
	int r, g, b;
};

class playerAvatar
{
private:
	int _hairR, _hairG, _hairB;								//�Ӹ����� ��Ÿ���� r,g,b
	int _pantsR, _pantsG, _pantsB;							//�������� ��Ÿ���� r,g,b
	int _hairFrameX, _hairFrameY;							//�÷��̾� �Ӹ� ������
	int _shirtsFrameX, _shirtsFrameY;						//�÷��̾� �� ������

	image *_playerHair;										//�÷��̾� �ƹ�Ÿ�� �� �̹����� �����Ѵ�.
	image *_playerBody;
	image *_playerArm;
	image *_playerShirts;
	image *_playerPants;
	image *_shadow;

	animation *_playerAniBody;								//�÷��̾� �ƹ�Ÿ�� ���� �ִϸ��̼��� �����Ѵ�
	animation *_playerAniArm;								//�Ӹ��� ������ ��� ���� ������ �ϸ� �ǹǷ� ���� ó���Ѵ�
	animation *_playerAniPants;

	HBRUSH blue, oBrush;
public:
	playerAvatar();
	~playerAvatar();

	HRESULT init();
	void release();
	void update(playerState playerState);
	void render(HDC hdc, playerState playerState);

	void hairShirtsRender(HDC hdc, playerState playerState, int x,int y);

	void playerAnimationAdd();								//�÷��̾��� �ִϸ��̼��� �߰��մϴ�.

	bool playerAniIsPlay();									//�÷��̾��� �ִϸ��̼��� ���������� �˻��մϴ�.
	void playerActiveStart();								//�÷��̾� �ൿ�� �ִϸ��̼��� ����մϴ�.
	void playerActiveEnd();									//�÷��̾� �ൿ����� �ִϸ��̼��� �����մϴ�.

	void playerHairColor(color hairColor);					//�÷��̾� ��� ���� ������ �ݴϴ�.
	void playerPantsColor(color pantsColor);				//�÷��̾� ���� ���� ������ �ݴϴ�.
	void setPlayerHairNum(int num) { _hairFrameX = num; };	//�÷��̾� �� �������ݴϴ�.
	void setPlayerShirtsNum(int num) { _shirtsFrameX = num; };//�÷��̾� ������ �������ݴϴ�.

	color getPlayerHairColor() { return color{ _hairR, _hairG, _hairB }; };
	color getPlayerPantsColor() { return color{ _pantsR, _pantsG, _pantsB }; };
	int getPlayerHairNum() { return _hairFrameX; };
	int getPlayerShirtsNum() { return _shirtsFrameX; };
};

