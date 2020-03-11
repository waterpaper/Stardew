#pragma once
#include"stdafx.h"
#include"image.h"

static HFONT OldFont;

class gameNode
{
private:
	HDC _hdc;
	//백버퍼 이미지를 스태틱으로 변경
	static image* _backBuffer;
	bool _managerInit;

public:
	gameNode();
	~gameNode();

	bool _isRectRend;
	bool _start;

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit, bool imageLoad);									//이미지가 다 로딩된 후 초기화되는 매니저와 아닌 매지저를 구분합니다
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(HDC hdc);

	//백버퍼 얻어오기
	image* getBackBuffer() { return _backBuffer; };

	//추가(메모리 DC)
	HDC getMemDC() { return _backBuffer->getMemDC(); };

	//추가 HDC얻기
	HDC getHDC() { return _hdc; };

	virtual int getIngameScene() { return 0; };

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};