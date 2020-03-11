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
	//배경이미지
	image *_maptoolSubBackgroundImg;
	
	//카메라 이미지
	image *_cameraImg;

	//샘플 이미지
	image *_sampleImg;

	//샘플선택 이미지
	image *_sampleSelectRectImg;

	//이미지 버튼
	vector<imageButton> _vbutton;
	vector<imageButton> _vAttributeButton;

	//글씨 입력을 위한 변수입니다
	string _changeSizeX, _changeSizeY;
	RECT _sizeXRect, _sizeYRect;
	bool _isSizeX, _isSizeY;

	string _nowSizeX, _nowSizeY;

	//현재 행동을 출력하기 위한 변수입니다
	string _nowAction;


	//선택된 타일을 판단하기 위한 변수
	RECT rc[TILE_SIZE_X][TILE_SIZE_Y];

	int _startFrameX, _startFrameY;
	int _endFrameX, _endFrameY;
	MAPTOOL_BUTTON_KIND _maptoolButtonKind;
	MAPTOOL_BUTTON_ATTRIBUTE_KIND _maptoolAttributeButtonKind;

	int _nowTileNum;											//현재 타일을 그리는 배열 위치
	int _nowIndex;												//현재 이미지 인덱스
	int _sampleMaxIndex;										//샘플 이미지 최대 인덱스
	bool _sampleClick;											//샘플을 클릭햇는지 여부


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
	void sampleSelecrtRectRender(HDC hdc);		//선택된 이미지를 보여주는 렉트를 랜더합니다

	void clickSelect();				//클릭시 어떤 행동을 하는지 판단합니다
	void clickButton();				//클릭시 어떤 버튼이 클릭되었는지 판단합니다

	void enteredSize();				//변경할 사이즈를 입력합니다
	void minimapCameraRender(HDC hdc);//미니맵 카메라를 랜더합니다
};

