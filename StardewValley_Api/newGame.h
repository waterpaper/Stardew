#pragma once
#define BAR_STARTX (WINSIZEX / 2 + 130)
#define BAR_ENDX (WINSIZEX / 2 + 130+255)

#define BAR_HAIRR_Y 380
#define BAR_HAIRG_Y 430
#define BAR_HAIRB_Y 480
#define BAR_PANTSR_Y 550
#define BAR_PANTSG_Y 600
#define BAR_PANTSB_Y 650

enum BAR_BUTTON_KIND
{
	BAR_BUTTON_KIND_NULL=0,
	BAR_BUTTON_KIND_HAIR_R,
	BAR_BUTTON_KIND_HAIR_G,
	BAR_BUTTON_KIND_HAIR_B,
	BAR_BUTTON_KIND_PANTS_R,
	BAR_BUTTON_KIND_PANTS_G,
	BAR_BUTTON_KIND_PANTS_B,
	BAR_BUTTON_KIND_END,
};

class newGame
{
private:
	int _hairNum, _shirtsNum;											//머리와 셔츠 번호

	int _hairR, _hairG, _hairB, _pantsR, _pantsG, _pantsB;

	image *_selectCharacterInfo;

	image *_barFront, *_barBack, *_controlButton, *_okayButton, *_cancelButton;
	RECT _hairRControlRect, _hairGControlRect, _hairBControlRect, _pantsRControlRect, _pantsGControlRect, _pantsBControlRect;		//커스터마이징 버튼 렉트
	RECT _frontHair, _backHair, _frontShirts, _backShirts;
	RECT _okayButtonRect, _cancelButtonRect;

	BAR_BUTTON_KIND _nowButtonKind;

	//글씨 입력을 위한 변수입니다
	string _playerName, _farmName;
	RECT _nameRect, _farmNameRect;
	bool _isName, _isFarmName;

public:
	newGame();
	~newGame();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	//컨트롤버튼 = 커스터마이징 바 버튼
	//현재 컨트롤버튼의 위치를 찾아준다
	int barLocationX(int num);

	//컨트롤버튼의 렉트를 움직이고 그려준다
	void barControlButton(BAR_BUTTON_KIND kind, int num);

	//컨트롤버튼을 입력을 처리해준다.
	void barControlButtonMove();

	//버튼을 처리하는 함수이다.
	void selectButton();

	//이름입력을 처리하는 함수입니다
	void enteredName();

	//확인후 게임을 시작하는 함수이다
	void gameStart();
};

