#pragma once
#include "singletonBase.h"
#include "maptool_main.h"
#include "maptool_sub.h"

#define SUBWINSIZEX 500
#define SUBWINSIZEY 768

enum CTRL
{
	CTRL_NULL,
	CTRL_TERRAINDRAW,
	CTRL_TERRAINSELECT,
	CTRL_OBJECTDRAW,
	CTRL_OBJECTSELECT,
	CTRL_ATTRIBUTE,
	CTRL_ERASER,
	CTRL_INIT,
	CTRL_SIZECHANGE,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_IMAGELOAD,
	CTRL_END
};

class subWindow :public singletonBase<subWindow>
{
private:
	HINSTANCE hInst;
	HWND sub_HWnd;
	static POINT sub_PtMouse;
	static CTRL sub_currentCtrl;

	int tileNum;						//Ÿ���� ���° �迭�� ������ �Ǵ��մϴ�
	POINT clickStartFrame;				//�̹��� �ȿ��� ���ۿ� ��ġ�� frame�� ��ġ�� ��Ÿ���ϴ�.
	POINT clickEndFrame;				//�̹��� �ȿ��� ���� ��ġ�� frame�� ��ġ�� ��Ÿ���ϴ�.
	int clickIndex;						//���õ� �̹����� ��ġ�� �̹����� ��Ÿ���ϴ�.
	MAPTOOL_BUTTON_ATTRIBUTE_KIND attributeKind; //���õ� �Ӽ��� ������ ��Ÿ���ϴ�.

	image* sub_BackBuffer;
	gameNode* sub_CurrentScene;

	image *_subMouseImg;

	bool isActive;

	maptool_main *maptool;

public:
	subWindow();
	~subWindow();

	void init();
	void release();
	void update();
	void render();

	void CreateSubWindow();				//���� �����츦 �������ش�.

	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		//������������ �ݹ��Լ��� �������ش�.

	void SetScene(gameNode* scene);

	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }

	void SetIndex(int index) { clickIndex = index; };
	int GetIndex() { return clickIndex; };

	void SetTileNum(int num) { tileNum = num; };
	int GetTileNum() { return tileNum; };

	void SetStartFramePoint(POINT frame) { clickStartFrame = frame; }
	POINT GetStartFramePoint() { return clickStartFrame; }

	void SetEndFramePoint(POINT frame) { clickEndFrame = frame; }
	POINT GetEndFramePoint() { return clickEndFrame; }

	void setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND kind) { attributeKind = kind; };
	MAPTOOL_BUTTON_ATTRIBUTE_KIND getAttributeKind() { return attributeKind; };

	void SetMaptool(maptool_main * maptool) { this->maptool = maptool; }
	maptool_main* GetMaptool() { return maptool; }

	static POINT GetMousePos() { return sub_PtMouse; }
	static void SetMousePos(int x, int y) { sub_PtMouse = POINT{ x,y }; };

	static CTRL GetCTRL() { return sub_currentCtrl; }
	void SetCTRL(CTRL ctrl) { sub_currentCtrl = ctrl; }

	HWND getHwnd() { return sub_HWnd; };
	HINSTANCE getInst() { return hInst; };
};

