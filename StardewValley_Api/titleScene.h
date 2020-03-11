#pragma once
#include "scene.h"

enum TITLESCENE_BUTTON_KIND
{
	TITLESCENE_BUTTON_NULL = 0,
	TITLESCENE_BUTTON_STARTGAMESCENE,
	TITLESCENE_BUTTON_LOADGAMESCENE,
	TITLESCENE_BUTTON_MAPTOOLSCENE,
	TITLESCENE_BUTTON_QUIT,
	TITLESCENE_BUTTON_END
};

class titleScene :public scene
{
private:
	int _sceneRenderCameraX, _sceneRenderCameraY;
	int _startCount;
	int _buttonNum;

	bool _isMove;
	bool _isSelectMenuCreate;

	image *_back;
	image *_img1, *_img2, *_img3;
	image *_bird;
	image *_title;

	RECT _backRc, _img1Rc, _img2Rc, _img3Rc, _birdRc, _titleRc;

	animation *_birdAni;

	vector<cloud> cloudVector;
	

public:
	titleScene();
	~titleScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	//�����߰�
	void cloudAdd();

	//���� ������
	void cloudMove();

	//��ư �Ǵ�
	void selectButton();

	//Ű �Է� �Ǵ�
	void enteredKey();

	//�ʱ� ȭ�� ������
	void imageMove();

	//�޴���ư ������ �߰�
	void crateSelectMenuButton();
};

