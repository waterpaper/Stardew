#include "stdafx.h"
#include "maptool_main.h"


maptool_main::maptool_main()
{
}


maptool_main::~maptool_main()
{
}

HRESULT maptool_main::init()
{
	_maxTileX = TILEMAPMANAGER->getTileMapSize().x;
	_maxTileY = TILEMAPMANAGER->getTileMapSize().y;

	_startX = INIT_X;
	_startY = INIT_Y;

	_maptoolCameraPositionX = 0;
	_maptoolCameraPositionY = 0;

	_currentTileX = 0;
	_currentTileY = 0;

	_moveSpeed = 5;
	_sampleExampleImage == nullptr;

	CAMERAMANAGER->setCameraPos(POINT{ 0,0 });
	TILEMAPMANAGER->setTileMapSize(POINT{32,32});

	return S_OK;
}

void maptool_main::render(HDC hdc)
{
	//��� ������ ī�޶󿡼� �����մϴ�
	CAMERAMANAGER->render(hdc, true, vector<RECT>{});
	CTRL ctrl = SUBWIN->GetCTRL();

	if (ctrl == CTRL_TERRAINDRAW || ctrl == CTRL_OBJECTDRAW)
	{
		if (_sampleExampleImage != nullptr)
		{
			sampleExampleImageRender(hdc);
		}
	}
	else
	{
		_sampleExampleImage == nullptr;
	}

	//���õ� Ÿ�� �����Դϴ�
	//�����
	SetBkMode(hdc, TRANSPARENT);
	sprintf_s(str, "tileX : %d, tileY : %d", _currentTileX, _currentTileY);
	TextOut(hdc, 700, 20, str, strlen(str));
}

void maptool_main::update()
{
	ctrl = SUBWIN->GetCTRL();

	cameraMove();
	mapClick();
	inputKeyboard();

	if (ctrl == CTRL_INIT)
	{
		initMap();
	}
	else if (ctrl == CTRL_SIZECHANGE)
	{
		_maptoolCameraPositionX = 0;
		_maptoolCameraPositionY = 0;

		_maxTileX = TILEMAPMANAGER->getTileMapSize().x;
		_maxTileY = TILEMAPMANAGER->getTileMapSize().y;

		SUBWIN->SetCTRL(CTRL_NULL);
	}
	else if (ctrl == CTRL_IMAGELOAD)
	{
		imageLoadMap();
	}
	else if (ctrl == CTRL_TERRAINSELECT)
	{
		_sampleExampleImage = IMAGEMANAGER->findImage("sampleExample");
		SUBWIN->SetCTRL(CTRL_TERRAINDRAW);
	}
	else if (ctrl == CTRL_OBJECTSELECT)
	{
		_sampleExampleImage = IMAGEMANAGER->findImage("sampleExample");
		SUBWIN->SetCTRL(CTRL_OBJECTDRAW);
	}
	else if (ctrl == CTRL_SAVE)
	{
		saveMap();
		
	}
	else if (ctrl == CTRL_LOAD)
	{
		loadMap();

		_maxTileX = TILEMAPMANAGER->getTileMapSize().x;
		_maxTileY = TILEMAPMANAGER->getTileMapSize().y;
		_maptoolCameraPositionX = 0;
		_maptoolCameraPositionY = 0;
	}
}

void maptool_main::release()
{
}

void maptool_main::cameraMove()
{
	/*
	�������� ī�޶� �������� �����մϴ�
	������ �÷��̾�� �ٸ��� ������ ī�޶�Ŵ����� ����ϵ� ���ʿ��� �����̸� �ȵǹǷ�
	���� ���� �� ����, �̻����� �ö��� �ʰ� �����մϴ�
	*/

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_maptoolCameraPositionX -= _moveSpeed;

		if (_maptoolCameraPositionX < 0)
			_maptoolCameraPositionX = 0;

		CAMERAMANAGER->cameraMove(_maptoolCameraPositionX + WINSIZEX / 2, _maptoolCameraPositionY + WINSIZEY / 2);
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_maptoolCameraPositionX += _moveSpeed;

		if (_maptoolCameraPositionX > _maxTileX*(TILE_SIZE_X)-WINSIZEX)
			_maptoolCameraPositionX = _maxTileX * (TILE_SIZE_X)-WINSIZEX;

		CAMERAMANAGER->cameraMove(_maptoolCameraPositionX + WINSIZEX / 2, _maptoolCameraPositionY + WINSIZEY / 2);
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_maptoolCameraPositionY += _moveSpeed;

		if (_maptoolCameraPositionY > _maxTileY*(TILE_SIZE_Y)-WINSIZEY)
			_maptoolCameraPositionY = _maxTileY * (TILE_SIZE_Y)-WINSIZEY;

		CAMERAMANAGER->cameraMove(_maptoolCameraPositionX + WINSIZEX / 2, _maptoolCameraPositionY + WINSIZEY / 2);
	}
	else if (KEYMANAGER->isStayKeyDown('W'))
	{
		_maptoolCameraPositionY -= _moveSpeed;

		if (_maptoolCameraPositionY < 0)
			_maptoolCameraPositionY = 0;

		CAMERAMANAGER->cameraMove(_maptoolCameraPositionX + WINSIZEX / 2, _maptoolCameraPositionY + WINSIZEY / 2);
	}
}

void maptool_main::initMap()
{
	/*
	���� ������ �ʱ�ȭ�մϴ�
	*/
	_maptoolCameraPositionX = 0;
	_maptoolCameraPositionY = 0;

	SUBWIN->SetCTRL(CTRL_END);
}

void maptool_main::eraser(int x, int y)
{
	TagTile_TERRAIN tileTemp;

	if (TILEMAPMANAGER->getIsObject(x, y))
	{
		tileMap tileMapTemp = TILEMAPMANAGER->getTileMap();
		vTileObject objectTemp = tileMapTemp.getTileObject();
		POINT camera = CAMERAMANAGER->getCameraPos();

		for (int i = 0; i < objectTemp.size(); i++)
		{
			if (PtInRect(&objectTemp[i]->objectTotalRc, POINT{ m_ptMouse.x + camera.x,m_ptMouse.y + camera.y }))
			{
				TILEMAPMANAGER->deleteObject(i);
				break;
			}
		}
	}

	if (TILEMAPMANAGER->getTileMapAttribute(x, y) != TILE_TERRAINKIND_NULL)
	{
		tileTemp.tileNum = 0;
		tileTemp.imageIndex[0] = -1;
		tileTemp.imageIndex[1] = -1;
		tileTemp.imageIndex[2] = -1;
		tileTemp.isTerrain = false;
		tileTemp.isObject = false;
		tileTemp.tileFrame[0] = POINT{ -1,-1 };
		tileTemp.tileFrame[1] = POINT{ -1,-1 };
		tileTemp.tileFrame[2] = POINT{ -1,-1 };
		tileTemp.tilePos = POINT{ x*TILE_SIZE_X,y*TILE_SIZE_Y };
		tileTemp.tile_terrainKind = TILE_TERRAINKIND_NULL;
		tileTemp.tileRc = RectMake(x*TILE_SIZE_X, y*TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
		tileTemp.tileTerrainImg[0] = nullptr;
		tileTemp.tileTerrainImg[1] = nullptr;
		tileTemp.tileTerrainImg[2] = nullptr;

		for (int i = 0; i < TILE_NUM_MAX; i++)
		{
			TILEMAPMANAGER->setTile(tileTemp, x, y, i);
		}
	}
}

void maptool_main::saveMap()
{
	/*
	���� �����մϴ�
	*/

	char strTemp[256];
	char dir[256];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = "������(*.*)\0*.map*\0";

	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 1000;

	sprintf(dir, "\\map");

	//GetCurrentDirectory :  ���� ���α׷��� �۾� ��θ� ������ ���
	GetCurrentDirectory(256, strTemp);
	strcat(strTemp, dir);

	OFN.lpstrInitialDir = strTemp;

	if (0 != GetSaveFileName(&OFN))
	{
		strcat(OFN.lpstrFile, ".map");
		TILEMAPMANAGER->saveTileMapIamge(OFN.lpstrFile);
	}

	SUBWIN->SetCTRL(CTRL_NULL);
	SUBWIN->SetMousePos(0, 0);

	ShowCursor(false);
}

void maptool_main::loadMap()
{
	/*
	���� �ҷ��ɴϴ�
	*/
	char strTemp[256];
	char dir[256];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = "������(*.*)\0*.map*\0";

	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 1000;
	
	sprintf(dir, "\\map");
	
	//GetCurrentDirectory :  ���� ���α׷��� �۾� ��θ� ������ ���
	GetCurrentDirectory(256, strTemp);
	strcat(strTemp, dir);

	OFN.lpstrInitialDir = strTemp;

	if (0 != GetOpenFileName(&OFN))
	{
		TILEMAPMANAGER->loadTileMapIamge(OFN.lpstrFile, INGAMESCENE_NAME::INGAMESCENE_NAME_NULL);
	}

	CAMERAMANAGER->setCameraPos(POINT{0,0});
	SUBWIN->SetCTRL(CTRL_NULL);
	SUBWIN->SetMousePos(0, 0);
	ShowCursor(false);
}

void maptool_main::imageLoadMap()
{
	/*
	�ʿ� �̹����� �ҷ��ɴϴ�
	*/
	char strTemp[256];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = "All Files(*.*)\0*.*\0";

	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 1000;
	OFN.lpstrInitialDir = "C:\\Users\\Lee\\source\\repos\\StardewValleyApi_leeinjae\\StardewValley_Api\\images\\background";

	if (0 != GetOpenFileName(&OFN))
	{
		sscanf_s(OFN.lpstrFile, "C:\\Users\\Lee\\source\\repos\\StardewValleyApi_leeinjae\\StardewValley_Api\\images\\background\\%s.bmp", &strTemp, sizeof(strTemp));
		TILEMAPMANAGER->addTileMapIamge(strTemp);
	}

	SUBWIN->SetCTRL(CTRL_NULL);
	SUBWIN->SetMousePos(0, 0);
	ShowCursor(false);
}

void maptool_main::mapClick()
{
	/*
	//�ʿ� ����κ��� Ŭ���Ǿ����� �Ǵ��մϴ�
	*/
	POINT camera;
	camera = CAMERAMANAGER->getCameraPos();

	_currentTileX = (m_ptMouse.x + camera.x) / (TILE_SIZE_X);
	_currentTileY = (m_ptMouse.y + camera.y) / (TILE_SIZE_Y);

	if (!SUBWIN->GetIsActive() && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (ctrl == CTRL_TERRAINDRAW)
		{
			setMapTerrain((m_ptMouse.x + camera.x) / (TILE_SIZE_X), (m_ptMouse.y + camera.y) / (TILE_SIZE_Y));
		}

		if (ctrl == CTRL_OBJECTDRAW)
		{
			setMapObject((m_ptMouse.x + camera.x) / (TILE_SIZE_X), (m_ptMouse.y + camera.y) / (TILE_SIZE_Y));
		}

		if (ctrl == CTRL_ERASER)
		{
			eraser((m_ptMouse.x + camera.x) / (TILE_SIZE_X), (m_ptMouse.y + camera.y) / (TILE_SIZE_Y));
		}

		if (ctrl == CTRL_ATTRIBUTE)
		{
			setMapAttribute((m_ptMouse.x + camera.x) / (TILE_SIZE_X), (m_ptMouse.y + camera.y) / (TILE_SIZE_Y));
		}
	}
}

void maptool_main::setMapTerrain(int x, int y)
{
	/*
	//����ڰ� ������ ȭ�鿡 ��ǥ�� �ν��ϰ� ���� �ٲ��ݴϴ�
	���õ� ũ�⸸ŭ ���� �ٲ��ָ� �� ũ�Ⱑ �Ѿ�� �����մϴ�
	*/
	TagTile_TERRAIN tileTemp;
	POINT startPt = SUBWIN->GetStartFramePoint(), endPt = SUBWIN->GetEndFramePoint();
	int num = SUBWIN->GetTileNum();

	tileTemp.imageIndex[num] = SUBWIN->GetIndex();
	tileTemp.tileTerrainImg[num] = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(tileTemp.imageIndex[num]));
	tileTemp.tileNum = num + 1;

	TILEMAPMANAGER->setTile(tileTemp, x, y, startPt, endPt, num);
}

void maptool_main::setMapObject(int x, int y)
{
	/*
	//����ڰ� ������ ȭ�鿡 ��ǥ�� �ν��ϰ� ������Ʈ�� �߰��մϴ�
	*/
	TagTile_Object *objectTemp;
	objectTemp = new TagTile_Object;

	objectTemp->imageIndex = SUBWIN->GetIndex();
	objectTemp->objectPos = POINT{ x,y };
	objectTemp->objectFrame = POINT{ 0,0 };
	objectTemp->tileObjectImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(objectTemp->imageIndex));

	TILEMAPMANAGER->addObject(objectTemp);
}

void maptool_main::setMapAttribute(int x, int y)
{
	MAPTOOL_BUTTON_ATTRIBUTE_KIND kind = SUBWIN->getAttributeKind();

	if (kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL)
	{
		return;
	}
	else if (kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS)
	{
		TILEMAPMANAGER->setTileMapAttribute(x, y, TILE_TERRAINKIND_GRASS);
	}
	else if (kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL)
	{
		TILEMAPMANAGER->setTileMapAttribute(x, y, TILE_TERRAINKIND_SOIL);
	}
	else if (kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL)
	{
		TILEMAPMANAGER->setTileMapAttribute(x, y, TILE_TERRAINKIND_NORMAL);
	}
	else if (kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE)
	{
		TILEMAPMANAGER->setTileMapAttribute(x, y, TILE_TERRAINKIND_NOTMOVE);
	}
}

void maptool_main::inputKeyboard()
{
	/*
	�ش� Ű �Է½� �ش� Ÿ���� ���̾ ���̰� �˴ϴ�
	0�� ��ü ���̾ �ٽ� �׷��ְ� �˴ϴ�
	*/
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		TILEMAPMANAGER->tileNumRender(1);
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		TILEMAPMANAGER->tileNumRender(2);
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		TILEMAPMANAGER->tileNumRender(3);
	}
	else if (KEYMANAGER->isOnceKeyDown('0'))
	{
		TILEMAPMANAGER->tileNumRender(0);
	}
}

void maptool_main::sampleExampleImageRender(HDC hdc)
{
	_sampleExampleImage->alphaRender(hdc, m_ptMouse.x, m_ptMouse.y, 123);
}
