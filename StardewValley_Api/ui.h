#pragma once
#include "playerState.h"
#include "button.h"

enum UIBUTTONKIND
{
	UIBUTTONKIND_NULL,
	UIBUTTONKIND_INVENTORY,
	UIBUTTONKIND_FEELING,
	UIBUTTONKIND_MAP,
	UIBUTTONKIND_MAKING,
	UIBUTTONKIND_EXIT,
	UIBUTTONKIND_CANCEL,
	UIBUTTONKIND_END
};

struct imageUi
{
	image *uiImg;

	int startX;
	int startY;
	int width;
	int height;

	RECT rc;

	int uiKind;
	bool isFrame;
};

class ui
{
protected:
	vector<imageUi> _vUiImage;
	vector<imageButton> _vButton;

public:
	ui();
	~ui();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void imageButtonRender(HDC hdc);
	void imageButtonPoint();

	void imageButtonAdd(char* imageName, string text, int x, int y, int width, int height, int kind, bool frame = false);
	void imageButtonClear();

	void uiImageAdd(char* imageName, int x, int y, int width, int height, int kind, bool frame = false);
	void uiImageRender(HDC hdc);
	void uiImageClear();

	//현재 선택된 아이템의 번호를 반환한다
	virtual int getKindNum() { return 0; };

};

