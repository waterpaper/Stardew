#include "stdafx.h"
#include "subWIndow.h"

POINT subWindow::sub_PtMouse = POINT{ 0,0 };
CTRL subWindow::sub_currentCtrl = CTRL_NULL;

subWindow::subWindow()
{
	sub_BackBuffer = new image();
	sub_BackBuffer->init(SUBWINSIZEX, SUBWINSIZEY);
}


subWindow::~subWindow()
{
	SAFE_DELETE(sub_BackBuffer);
}

void subWindow::init()
{
	CreateSubWindow();

	isActive = false;
	_subMouseImg = IMAGEMANAGER->findImage("마우스");
	SetCursor(false);

	clickStartFrame = { 0,0 };
	clickEndFrame = { 0,0 };
	clickIndex = 0;
}

void subWindow::release()
{

}

void subWindow::update()
{
	if (sub_CurrentScene != NULL)
	{
		sub_CurrentScene->update();
	}
}

void subWindow::render()
{
	HDC hdc = GetDC(sub_HWnd);
	PatBlt(sub_BackBuffer->getMemDC(), 0, 0, SUBWINSIZEX, SUBWINSIZEY, WHITENESS);

	if (sub_CurrentScene != NULL)
	{
		sub_CurrentScene->render(sub_BackBuffer->getMemDC());
		
		if (isActive)
		{
			_subMouseImg->frameRender(sub_BackBuffer->getMemDC(), sub_PtMouse.x, sub_PtMouse.y);
		}
	}
	sub_BackBuffer->render(hdc);
	ReleaseDC(sub_HWnd, hdc);
}

void subWindow::CreateSubWindow()
{
	//로그 윈도우 생성
	int x, y, cx, cy;
	WNDCLASS wc;
	RECT rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)subWindow::WndLogProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "tileSelect";
	RegisterClass(&wc);
	//부모 윈도우 오른쪽에 위치 하자.
	RECT rcWin;
	GetWindowRect(m_hWnd, &rcWin);

	cx = SUBWINSIZEX;
	cy = SUBWINSIZEY;
	x = rcWin.right;
	y = rcWin.top;

	rc.left = 0;
	rc.top = 0;
	rc.right = cx;
	rc.bottom = cy;

	HWND hParenthWnd = NULL;
	hInst = NULL;

	hParenthWnd = m_hWnd;
	hInst = GetModuleHandle(NULL);

	sub_HWnd = CreateWindow("tileSelect", "tileSelect",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL, hInst, NULL);

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(sub_HWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER);

	ShowWindow(sub_HWnd, SW_SHOW);
}

LRESULT subWindow::WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(true);
		sub_PtMouse.x = LOWORD(lParam);
		sub_PtMouse.y = HIWORD(lParam);
		break;
	case WM_CHAR:
		int nKey;
		nKey = (TCHAR)wParam; //누른 키 값을 아스키 값으로 받음

		if (INPUTMANAGER->getIskeyBoardStart())	//키보드 입력을 사용할때만
		{
			INPUTMANAGER->addKeyBoard(nKey);
		}
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void subWindow::SetScene(gameNode * scene)
{
	sub_CurrentScene = scene;
	sub_CurrentScene->init();
}
