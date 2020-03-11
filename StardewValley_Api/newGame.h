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
	int _hairNum, _shirtsNum;											//�Ӹ��� ���� ��ȣ

	int _hairR, _hairG, _hairB, _pantsR, _pantsG, _pantsB;

	image *_selectCharacterInfo;

	image *_barFront, *_barBack, *_controlButton, *_okayButton, *_cancelButton;
	RECT _hairRControlRect, _hairGControlRect, _hairBControlRect, _pantsRControlRect, _pantsGControlRect, _pantsBControlRect;		//Ŀ���͸���¡ ��ư ��Ʈ
	RECT _frontHair, _backHair, _frontShirts, _backShirts;
	RECT _okayButtonRect, _cancelButtonRect;

	BAR_BUTTON_KIND _nowButtonKind;

	//�۾� �Է��� ���� �����Դϴ�
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

	//��Ʈ�ѹ�ư = Ŀ���͸���¡ �� ��ư
	//���� ��Ʈ�ѹ�ư�� ��ġ�� ã���ش�
	int barLocationX(int num);

	//��Ʈ�ѹ�ư�� ��Ʈ�� �����̰� �׷��ش�
	void barControlButton(BAR_BUTTON_KIND kind, int num);

	//��Ʈ�ѹ�ư�� �Է��� ó�����ش�.
	void barControlButtonMove();

	//��ư�� ó���ϴ� �Լ��̴�.
	void selectButton();

	//�̸��Է��� ó���ϴ� �Լ��Դϴ�
	void enteredName();

	//Ȯ���� ������ �����ϴ� �Լ��̴�
	void gameStart();
};

