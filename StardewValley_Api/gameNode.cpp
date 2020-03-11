#include "stdafx.h"
#include "gameNode.h"

image* gameNode::_backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);
//����� ������

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	_start = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit, bool imageLoad)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;
	
	_isDebug = false;
	_isAttribute = false;
	_isSound = true;

	if (managerInit)
	{
		if (!imageLoad)
		{
			KEYMANAGER->init();
			IMAGEMANAGER->init();
			TIMEMANAGER->init();
			SCENEMANAGER->init();
			INPUTMANAGER->init();
			CAMERAMANAGER->init();
			_sound.init();
		}
		else
		{
			//�̹����� �ε���� �ʱ�ȭ�ؾ��ϴ� �Ŵ������� ���⼭ �ʱ�ȭ �մϴ�.
			PLAYERMANAGER->init();
			ANIMATIONMANAGER->init();
			EFFECTMANAGER->init();
			TILEMAPMANAGER->init();
			UIMANAGER->init(); 
			INVENTORYMANAGER->init();
			ITEMMANAGER->init();
			GAMETIMEMANAGER->init();
			NPCMANAGER->init();
			FARMMANAGER->init();
			ANIMALMANAGER->init();
			
		}
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		ANIMATIONMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		PLAYERMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		INPUTMANAGER->releaseSingleton();
		TILEMAPMANAGER->releaseSingleton();
		CAMERAMANAGER->releaseSingleton();
		UIMANAGER->releaseSingleton();
		ITEMMANAGER->releaseSingleton();
		INVENTORYMANAGER->releaseSingleton();
		GAMETIMEMANAGER->releaseSingleton();
		NPCMANAGER->releaseSingleton();
		FARMMANAGER->releaseSingleton();
		ANIMALMANAGER->releaseSingleton();
		_sound.release();
		
		/*
		ENEMYMANAGER->releaseSingleton();
		EQUIPMENTMANAGER->releaseSingleton();
		*/
	}

	ReleaseDC(m_hWnd, _hdc);

}

void gameNode::update()
{
	InvalidateRect(m_hWnd, NULL, false);
}

void gameNode::render()
{
}

void gameNode::render(HDC hdc)
{
	return;
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT clientRect;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(false);
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CHAR:
		int nKey;
		nKey = (TCHAR)wParam; //���� Ű ���� �ƽ�Ű ������ ����

		if (INPUTMANAGER->getIskeyBoardStart())	//Ű���� �Է��� ����Ҷ���
		{
			INPUTMANAGER->addKeyBoard(nKey);
		}
		break;

		/*������ ������ ����(�������) ����
		case WM_SIZE:
			if (_start&&KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				RECT rc;

				SetMapMode(getMemDC(), MM_ANISOTROPIC);
				SetWindowExtEx(getMemDC(), WINSIZEX, WINSIZEY, NULL);

				AdjustWindowRect(&rc, WINSTYLE, false);
				rc.right = m_ptMouse.x;
				rc.bottom = m_ptMouse.y;

				SetViewportExtEx(getMemDC(), rc.right, rc.bottom, NULL);

				//�� RECT ������ ������ ������ ����
				SetWindowPos(m_hWnd, NULL, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

				IMAGEMANAGER->setImageReSize("backbuffer", rc.right, rc.bottom);
			}
			else
			{
				_start = true;
			}

			break;
			*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

