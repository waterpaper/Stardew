#pragma once
#include"stdafx.h"
#include"image.h"

static HFONT OldFont;

class gameNode
{
private:
	HDC _hdc;
	//����� �̹����� ����ƽ���� ����
	static image* _backBuffer;
	bool _managerInit;

public:
	gameNode();
	~gameNode();

	bool _isRectRend;
	bool _start;

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit, bool imageLoad);									//�̹����� �� �ε��� �� �ʱ�ȭ�Ǵ� �Ŵ����� �ƴ� �������� �����մϴ�
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(HDC hdc);

	//����� ������
	image* getBackBuffer() { return _backBuffer; };

	//�߰�(�޸� DC)
	HDC getMemDC() { return _backBuffer->getMemDC(); };

	//�߰� HDC���
	HDC getHDC() { return _hdc; };

	virtual int getIngameScene() { return 0; };

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};