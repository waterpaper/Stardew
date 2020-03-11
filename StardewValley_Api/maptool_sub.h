#pragma once
#include "gameNode.h"
#include "tile_Info.h"
#include "scene.h"

#define ID_COMBOBOX 100


enum MAPTOOL_BUTTON_KIND
{
	MAPTOOL_BUTTON_NULL = 0,
	MAPTOOL_BUTTON_TILE,
	MAPTOOL_BUTTON_OBJECT,
	MAPTOOL_BUTTON_EREASER,
	MAPTOOL_BUTTON_INIT,
	MAPTOOL_BUTTON_ATTRIBUTE,
	MAPTOOL_BUTTON_IMAGE,
	MAPTOOL_BUTTON_SAVE,
	MAPTOOL_BUTTON_LOAD,
	MAPTOOL_BUTTON_SIZECHANGE,
	MAPTOOL_BUTTON_UP,
	MAPTOOL_BUTTON_DOWN,
	MAPTOOL_BUTTON_NEXT,
	MAPTOOL_BUTTON_BEFORE,
	MAPTOOL_BUTTON_QUIT,
	MAPTOOL_BUTTON_END
};

enum MAPTOOL_BUTTON_ATTRIBUTE_KIND
{
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL=1000,
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS,
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL,
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL,
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE,
	MAPTOOL_BUTTON_ATTRIBUTE_KIND_END
};

class maptool_sub :public gameNode
{
private:
	//����̹���
	image *_maptoolSubBackgroundImg;
	
	//ī�޶� �̹���
	image *_cameraImg;

	//���� �̹���
	image *_sampleImg;

	//���ü��� �̹���
	image *_sampleSelectRectImg;

	//�̹��� ��ư
	vector<imageButton> _vbutton;
	vector<imageButton> _vAttributeButton;

	//�۾� �Է��� ���� �����Դϴ�
	string _changeSizeX, _changeSizeY;
	RECT _sizeXRect, _sizeYRect;
	bool _isSizeX, _isSizeY;

	string _nowSizeX, _nowSizeY;

	//���� �ൿ�� ����ϱ� ���� �����Դϴ�
	string _nowAction;


	//���õ� Ÿ���� �Ǵ��ϱ� ���� ����
	RECT rc[TILE_SIZE_X][TILE_SIZE_Y];

	int _startFrameX, _startFrameY;
	int _endFrameX, _endFrameY;
	MAPTOOL_BUTTON_KIND _maptoolButtonKind;
	MAPTOOL_BUTTON_ATTRIBUTE_KIND _maptoolAttributeButtonKind;

	int _nowTileNum;											//���� Ÿ���� �׸��� �迭 ��ġ
	int _nowIndex;												//���� �̹��� �ε���
	int _sampleMaxIndex;										//���� �̹��� �ִ� �ε���
	bool _sampleClick;											//������ Ŭ���޴��� ����


public:
	maptool_sub();
	~maptool_sub();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void imageButtonAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame);
	void imageButtonAttributeAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame);
	void imageButtonRender(HDC hdc);
	void imageButtonPoint();
	void imageButtonClear();

	void sampleImageRender(HDC hdc);
	void sampleSelectRender();
	void sampleSelecrtRectRender(HDC hdc);		//���õ� �̹����� �����ִ� ��Ʈ�� �����մϴ�

	void clickSelect();				//Ŭ���� � �ൿ�� �ϴ��� �Ǵ��մϴ�
	void clickButton();				//Ŭ���� � ��ư�� Ŭ���Ǿ����� �Ǵ��մϴ�

	void enteredSize();				//������ ����� �Է��մϴ�
	void minimapCameraRender(HDC hdc);//�̴ϸ� ī�޶� �����մϴ�
};

