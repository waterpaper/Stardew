#pragma once
#include "playerState.h"

struct color
{
	int r, g, b;
};

class playerAvatar
{
private:
	int _hairR, _hairG, _hairB;								//머리색을 나타내는 r,g,b
	int _pantsR, _pantsG, _pantsB;							//바지색을 나타내는 r,g,b
	int _hairFrameX, _hairFrameY;							//플레이어 머리 프레임
	int _shirtsFrameX, _shirtsFrameY;						//플레이어 옷 프레임

	image *_playerHair;										//플레이어 아바타의 각 이미지를 정의한다.
	image *_playerBody;
	image *_playerArm;
	image *_playerShirts;
	image *_playerPants;
	image *_shadow;

	animation *_playerAniBody;								//플레이어 아바타의 몸통 애니매이션을 정의한다
	animation *_playerAniArm;								//머리와 셔츠의 경우 방향 조절만 하면 되므로 따로 처리한다
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

	void playerAnimationAdd();								//플레이어의 애니메이션을 추가합니다.

	bool playerAniIsPlay();									//플레이어의 애니메이션이 진행중인지 검사합니다.
	void playerActiveStart();								//플레이어 행동시 애니메이션을 출력합니다.
	void playerActiveEnd();									//플레이어 행동종료시 애니메이션을 종료합니다.

	void playerHairColor(color hairColor);					//플레이어 헤어 색을 변경해 줍니다.
	void playerPantsColor(color pantsColor);				//플레이어 바지 색을 변경해 줍니다.
	void setPlayerHairNum(int num) { _hairFrameX = num; };	//플레이어 헤어를 변경해줍니다.
	void setPlayerShirtsNum(int num) { _shirtsFrameX = num; };//플레이어 셔츠를 변경해줍니다.

	color getPlayerHairColor() { return color{ _hairR, _hairG, _hairB }; };
	color getPlayerPantsColor() { return color{ _pantsR, _pantsG, _pantsB }; };
	int getPlayerHairNum() { return _hairFrameX; };
	int getPlayerShirtsNum() { return _shirtsFrameX; };
};

