#include "stdafx.h"
#include "maptool_sub.h"

maptool_sub::maptool_sub()
{
}


maptool_sub::~maptool_sub()
{
}

HRESULT maptool_sub::init()
{
	_maptoolSubBackgroundImg = IMAGEMANAGER->findImage("����â_���");
	_cameraImg = IMAGEMANAGER->findImage("����â_ī�޶�");
	_sampleSelectRectImg = IMAGEMANAGER->findImage("����â_���ü���");

	imageButtonAdd("����â_��������ư", "", 370, 30, 100, 80, MAPTOOL_BUTTON_SIZECHANGE, true);

	imageButtonAdd("����â_Ÿ�Ϲ�ư", "", 40, 130, 100, 80, MAPTOOL_BUTTON_TILE, true);
	imageButtonAdd("����â_������Ʈ��ư", "", 150, 130, 100, 80, MAPTOOL_BUTTON_OBJECT, true);
	imageButtonAdd("����â_�Ӽ���ư", "", 260, 130, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE, true);
	imageButtonAdd("����â_�̹�����ư", "", 370, 130, 100, 80, MAPTOOL_BUTTON_IMAGE, true);

	imageButtonAdd("����â_������ư", "", 370, 260, 100, 80, MAPTOOL_BUTTON_EREASER, true);
	imageButtonAdd("����â_�ʱ�ȭ��ư", "", 370, 350, 100, 80, MAPTOOL_BUTTON_INIT, true);

	imageButtonAdd("����â_�����ư", "", 370, 480, 100, 80, MAPTOOL_BUTTON_SAVE, true);
	imageButtonAdd("����â_�ε��ư", "", 370, 570, 100, 80, MAPTOOL_BUTTON_LOAD, true);
	imageButtonAdd("����â_�������ư", "", 370, 660, 100, 80, MAPTOOL_BUTTON_QUIT, true);

	imageButtonAdd("����â_������ư", "", 430, 225, 24, 24, MAPTOOL_BUTTON_NEXT, true);
	imageButtonAdd("����â_������ư", "", 380, 225, 24, 24, MAPTOOL_BUTTON_BEFORE, true);

	imageButtonAdd("����â_�Ʒ���ư", "", 46, 60, 24, 24, MAPTOOL_BUTTON_DOWN, true);
	imageButtonAdd("����â_����ư", "", 88, 60, 24, 24, MAPTOOL_BUTTON_UP, true);

	imageButtonAttributeAdd("����â_�Ӽ����ư", "", 60, 250, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL, true);
	imageButtonAttributeAdd("����â_�Ӽ�Ǯ��ư", "", 170, 250, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS, true);
	imageButtonAttributeAdd("����â_�Ӽ��Ϲݹ�ư", "", 60, 340, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL, true);
	imageButtonAttributeAdd("����â_�Ӽ��̵��Ұ���ư", "", 170, 340, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE, true);

	for (int i = 0; i < TILE_SAMPLE_COUNT_Y; i++)
	{
		for (int j = 0; j < TILE_SAMPLE_COUNT_X; j++)
		{
			rc[i][j] = RectMake(
				(SUBWINSIZEX - 200) / TILE_SAMPLE_COUNT_X * j + 50,
				TILE_SAMPLE_TOTALIMAGE_SIZEX / TILE_SAMPLE_COUNT_Y * i + 220,
				(SUBWINSIZEX - 200) / TILE_SAMPLE_COUNT_X, TILE_SAMPLE_TOTALIMAGE_SIZEY / TILE_SAMPLE_COUNT_Y);
		}
	}

	_sizeXRect = RectMake(256, 70, 80, 20);
	_sizeYRect = RectMake(256, 98, 80, 20);

	_nowSizeX = to_string(TILEMAPMANAGER->getTileMapSize().x);
	_nowSizeY = to_string(TILEMAPMANAGER->getTileMapSize().y);

	_isSizeX = false, _isSizeY = false;

	_nowIndex = 0, _startFrameX = 0, _startFrameY = 0, _endFrameX = 0, _endFrameY = 0, _nowTileNum = 0;

	_maptoolButtonKind = MAPTOOL_BUTTON_NULL;
	_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL;

	_sampleClick = false;
	_nowAction = "";


	SUBWIN->SetCTRL(CTRL_NULL);

	return S_OK;
}

void maptool_sub::release()
{

}

void maptool_sub::update()
{
	if (_maptoolButtonKind == MAPTOOL_BUTTON_LOAD)
	{
		POINT ptTemp;
		ptTemp = TILEMAPMANAGER->getTileMapSize();

		_nowSizeX = to_string(ptTemp.x);
		_nowSizeY = to_string(ptTemp.y);
	}

	imageButtonPoint();

	clickSelect();

	enteredSize();
}
void maptool_sub::render(HDC hdc)
{
	_maptoolSubBackgroundImg->render(hdc);
	imageButtonRender(hdc);
	TILEMAPMANAGER->minimapRender(hdc, 300, 200, 50, 530);

	minimapCameraRender(hdc);

	//����//�۾�ü ����
	SelectObject(hdc, hSmallFont);
	SetTextColor(hdc, RGB(183, 89, 20));

	//�۾����
	char temp[128];
	sprintf_s(temp, "x : %s y : %s", _nowSizeX.c_str(), _nowSizeY.c_str());

	TextOut(hdc, 120, 37, _nowAction.c_str(), strlen(_nowAction.c_str()));
	if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE)
	{
		char tempTileNum[128];
		sprintf_s(tempTileNum, "tileNum : %d ", _nowTileNum + 1);

		TextOut(hdc, 120, 68, tempTileNum, strlen(tempTileNum));
	}

	SetTextAlign(hdc, TA_RIGHT);
	TextOut(hdc, 210, 95, temp, strlen(temp));
	TextOut(hdc, 320, 70, _changeSizeX.c_str(), strlen(_changeSizeX.c_str()));
	TextOut(hdc, 320, 95, _changeSizeY.c_str(), strlen(_changeSizeY.c_str()));
	SetTextAlign(hdc, TA_LEFT);

	//����
	SetTextColor(hdc, RGB(0, 0, 0));

	sampleImageRender(hdc);
}

void maptool_sub::imageButtonAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame)
{
	imageButton buttonTemp;

	buttonTemp._img = IMAGEMANAGER->findImage(imageName);
	buttonTemp._text = text;
	buttonTemp._rc = RectMake(x, y, width, height);
	buttonTemp._kind = kind;
	buttonTemp._isFrame = frame;
	buttonTemp._ischeck = false;
	buttonTemp._currentX = 0;

	_vbutton.push_back(buttonTemp);
}

void maptool_sub::imageButtonAttributeAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame)
{
	imageButton buttonTemp;

	buttonTemp._img = IMAGEMANAGER->findImage(imageName);
	buttonTemp._text = text;
	buttonTemp._rc = RectMake(x, y, width, height);
	buttonTemp._kind = kind;
	buttonTemp._isFrame = frame;
	buttonTemp._ischeck = false;
	buttonTemp._currentX = 0;

	_vAttributeButton.push_back(buttonTemp);
}

void maptool_sub::imageButtonRender(HDC hdc)
{
	/*
	�̹��� ��ư�� �׷��ݴϴ�
	�������̹���(���콺 �÷����� �޶����� �̹���)�� �����ϴ� ��ư�� �ƴ� ��ư�� ������ �׷��ݴϴ�.
	*/
	for (int i = 0; i < _vbutton.size(); i++)
	{
		if (_vbutton[i]._isFrame)
		{
			if (_vbutton[i]._ischeck)
			{
				_vbutton[i]._img->frameRender(hdc, _vbutton[i]._rc.left, _vbutton[i]._rc.top, _vbutton[i]._currentX, 0);
			}
			else
			{
				_vbutton[i]._img->frameRender(hdc, _vbutton[i]._rc.left, _vbutton[i]._rc.top, 0, 0);
			}
		}
		else
		{
			_vbutton[i]._img->render(hdc, _vbutton[i]._rc.left, _vbutton[i]._rc.top);
		}

		//�����
		SetBkMode(hdc, TRANSPARENT);
		//����
		SetTextColor(hdc, RGB(0, 0, 0));

		TextOut(hdc, 0, 0, _vbutton[i]._text.c_str(), _vbutton[i]._text.size());
	}

	//�Ӽ�����϶�
	if (_isAttribute)
	{
		for (int i = 0; i < _vAttributeButton.size(); i++)
		{
			if (_vAttributeButton[i]._isFrame)
			{
				if (_vAttributeButton[i]._ischeck)
				{
					_vAttributeButton[i]._img->frameRender(hdc, _vAttributeButton[i]._rc.left, _vAttributeButton[i]._rc.top, _vAttributeButton[i]._currentX, 0);
				}
				else
				{
					_vAttributeButton[i]._img->frameRender(hdc, _vAttributeButton[i]._rc.left, _vAttributeButton[i]._rc.top, 0, 0);
				}
			}
			else
			{
				_vAttributeButton[i]._img->render(hdc, _vAttributeButton[i]._rc.left, _vAttributeButton[i]._rc.top);
			}

			//�����
			SetBkMode(hdc, TRANSPARENT);
			//����
			SetTextColor(hdc, RGB(0, 0, 0));

			TextOut(hdc, 0, 0, _vAttributeButton[i]._text.c_str(), _vAttributeButton[i]._text.size());
		}
	}
}

void maptool_sub::imageButtonPoint()
{
	/*
	���� ���콺�� � ��ư���� �ִ��� �Ǵ��մϴ�
	*/
	POINT pointTemp = SUBWIN->GetMousePos();

	for (int i = 0; i < _vbutton.size(); i++)
	{
		if (!_vbutton[i]._isFrame) continue;

		if (PtInRect(&_vbutton[i]._rc, pointTemp))
		{
			_vbutton[i]._ischeck = true;
			_vbutton[i]._currentX = 1;
		}
		else
		{
			_vbutton[i]._ischeck = false;
			_vbutton[i]._currentX = 0;
		}
	}

	//�Ӽ�����϶�
	if (_isAttribute)
	{
		for (int i = 0; i < _vAttributeButton.size(); i++)
		{
			if (!_vAttributeButton[i]._isFrame) continue;

			if (PtInRect(&_vAttributeButton[i]._rc, pointTemp))
			{
				_vAttributeButton[i]._ischeck = true;
				_vAttributeButton[i]._currentX = 1;
			}
			else
			{
				_vAttributeButton[i]._ischeck = false;
				_vAttributeButton[i]._currentX = 0;
			}
		}
	}
}

void maptool_sub::imageButtonClear()
{
	vector<imageButton> vTemp;

	_vbutton.swap(vTemp);
	vTemp.clear();
}

void maptool_sub::sampleImageRender(HDC hdc)
{
	/*
	�����̹����� �����մϴ�
	������Ʈ�� ��� �߰������� �����ϱ� ���� ����մϴ�
	*/
	if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE)
	{
		_sampleImg->render(hdc, 50, 220, TILE_SAMPLE_TOTALIMAGE_SIZEX, TILE_SAMPLE_TOTALIMAGE_SIZEY);
		sampleSelecrtRectRender(hdc);
	}
	else if (_maptoolButtonKind == MAPTOOL_BUTTON_OBJECT)
	{
		if (_sampleImg->getIsFrame())
		{
			int moveX = 50 + (TILE_SAMPLE_TOTALIMAGE_SIZEX - _sampleImg->getFrameWidth()) / 2;
			int moveY = 220 + (TILE_SAMPLE_TOTALIMAGE_SIZEY - _sampleImg->getFrameHeight()) / 2;

			_sampleImg->frameRender(hdc, moveX, moveY, 0, 0);
		}
		else
		{
			int moveX = 50 + (TILE_SAMPLE_TOTALIMAGE_SIZEX - _sampleImg->getWidth()) / 2;
			int moveY = 220 + (TILE_SAMPLE_TOTALIMAGE_SIZEY - _sampleImg->getHeight()) / 2;

			if (_sampleImg->getWidth() > TILE_SAMPLE_TOTALIMAGE_SIZEX && _sampleImg->getHeight() > TILE_SAMPLE_TOTALIMAGE_SIZEY)
			{
				_sampleImg->render(hdc, 50, 220, TILE_SAMPLE_TOTALIMAGE_SIZEX, TILE_SAMPLE_TOTALIMAGE_SIZEY);
			}
			else if (_sampleImg->getHeight() > TILE_SAMPLE_TOTALIMAGE_SIZEY)
			{
				_sampleImg->render(hdc, moveX, 220, _sampleImg->getWidth(), TILE_SAMPLE_TOTALIMAGE_SIZEY);
			}
			else if (_sampleImg->getWidth() > TILE_SAMPLE_TOTALIMAGE_SIZEX)
			{
				_sampleImg->render(hdc, 50, moveY, TILE_SAMPLE_TOTALIMAGE_SIZEX, _sampleImg->getHeight());
			}
			else
			{
				_sampleImg->render(hdc, moveX, moveY, _sampleImg->getWidth(), _sampleImg->getHeight());
			}
		}
	}
}

void maptool_sub::sampleSelectRender()
{
	int sampleTileSizeX = TILE_SAMPLE_TOTALIMAGE_SIZEX / TILE_SAMPLE_COUNT_X;
	int sampleTileSizeY = TILE_SAMPLE_TOTALIMAGE_SIZEY / TILE_SAMPLE_COUNT_Y;

	if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE)
	{
		IMAGEMANAGER->deleteImage("sampleExample");

		image *temp1 = IMAGEMANAGER->addImage("sampleExampleTemp1", TILE_SAMPLE_TOTALIMAGE_SIZEX, TILE_SAMPLE_TOTALIMAGE_SIZEY);
		image *temp2 = IMAGEMANAGER->addImage("sampleExampleTemp2", (_endFrameX + 1 - _startFrameX)*(sampleTileSizeX), (_endFrameY + 1 - _startFrameY)*(sampleTileSizeY));
		image *sample = IMAGEMANAGER->addImage("sampleExample", (_endFrameX + 1 - _startFrameX)*(TILE_SIZE_X), (_endFrameY + 1 - _startFrameY)*(TILE_SIZE_Y));

		_sampleImg->render(temp1->getMemDC(), 0, 0, TILE_SAMPLE_TOTALIMAGE_SIZEX, TILE_SAMPLE_TOTALIMAGE_SIZEY);
		temp1->render(temp2->getMemDC(), 0, 0, _startFrameX*sampleTileSizeX, _startFrameY*sampleTileSizeY,
			(_endFrameX + 1 - _startFrameX)*sampleTileSizeX, (_endFrameY + 1 - _startFrameY)*sampleTileSizeY);
		temp2->render(sample->getMemDC(), 0, 0, (_endFrameX + 1 - _startFrameX)*(TILE_SIZE_X), (_endFrameY + 1 - _startFrameY)*(TILE_SIZE_Y));

		temp1 = nullptr, temp2 = nullptr, sample = nullptr;

		IMAGEMANAGER->deleteImage("sampleExampleTemp1");
		IMAGEMANAGER->deleteImage("sampleExampleTemp2");

		SUBWIN->SetCTRL(CTRL_TERRAINSELECT);
	}
	else if (_maptoolButtonKind == MAPTOOL_BUTTON_OBJECT)
	{
		IMAGEMANAGER->deleteImage("sampleExample");
		image *temp = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));
		image *sample;

		if (temp->getIsFrame())
		{
			sample = IMAGEMANAGER->addImage("sampleExample", temp->getFrameWidth(), temp->getFrameHeight());
			temp->frameRender(sample->getMemDC(), 0, 0, 0, 0);
		}
		else
		{
			sample = IMAGEMANAGER->addImage("sampleExample", temp->getWidth(), temp->getHeight());
			temp->render(sample->getMemDC(), 0, 0);
		}
		SUBWIN->SetCTRL(CTRL_OBJECTSELECT);

		temp = nullptr;
		sample = nullptr;
	}
}

void maptool_sub::sampleSelecrtRectRender(HDC hdc)
{
	/*
	Ÿ�ϸ� ���ý� ���õ� ũ�⸸ŭ�� �簢���� �����մϴ�
	*/
	int sampleTileSizeX = TILE_SAMPLE_TOTALIMAGE_SIZEX / TILE_SAMPLE_COUNT_X;
	int sampleTileSizeY = TILE_SAMPLE_TOTALIMAGE_SIZEY / TILE_SAMPLE_COUNT_Y;

	if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE && !_sampleClick)
	{
		_sampleSelectRectImg->render(hdc, 50 + _startFrameX * sampleTileSizeX, 220 + _startFrameY * sampleTileSizeY,
			(_endFrameX + 1 - _startFrameX)*sampleTileSizeX, (_endFrameY + 1 - _startFrameY)*sampleTileSizeY);
	}
}

void maptool_sub::clickSelect()
{
	/*
	Ŭ���� � �ൿ�� ���� �Ǵ��մϴ�
	*/
	POINT mouse = SUBWIN->GetMousePos();

	if (SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//Ÿ���� Ŭ��������
		for (int i = 0; i < TILE_SIZE_Y; i++)
		{
			for (int j = 0; j < TILE_SIZE_X; j++)
			{
				if (PtInRect(&rc[i][j], mouse))
				{
					_startFrameX = j;
					_startFrameY = i;

					_sampleClick = true;
				}
			}
		}

		//�۾� ó��
		if (PtInRect(&_sizeXRect, mouse))
		{
			_isSizeX = true;
			_isSizeY = false;
			INPUTMANAGER->stopKeyBoard();
			INPUTMANAGER->startKeyBoard();
		}
		else if (PtInRect(&_sizeYRect, mouse))
		{
			_isSizeX = false;
			_isSizeY = true;
			INPUTMANAGER->stopKeyBoard();
			INPUTMANAGER->startKeyBoard();
		}
		else
		{
			_isSizeX = false;
			_isSizeY = false;
			INPUTMANAGER->stopKeyBoard();
		}

		//��ưŬ��
		clickButton();
	}
	else if (SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//Ÿ���� Ŭ��������
		for (int i = 0; i < TILE_SIZE_Y; i++)
		{
			for (int j = 0; j < TILE_SIZE_X; j++)
			{
				if (PtInRect(&rc[i][j], mouse))
				{
					_endFrameX = j;
					_endFrameY = i;

					if (_startFrameX > _endFrameX)
					{
						int temp;

						temp = _endFrameX;
						_endFrameX = _startFrameX;
						_startFrameX = temp;
					}
					if (_startFrameY > _endFrameY)
					{
						int temp;

						temp = _endFrameY;
						_endFrameY = _startFrameY;
						_startFrameY = temp;
					}

					SUBWIN->SetIndex(_nowIndex);
					SUBWIN->SetStartFramePoint(PointMake(_startFrameX, _startFrameY));
					SUBWIN->SetEndFramePoint(PointMake(_endFrameX, _endFrameY));

					_sampleClick = false;

					sampleSelectRender();
				}
			}
		}
	}
}

void maptool_sub::clickButton()
{
	/*
	Ŭ���� � ��ư�� Ŭ���Ǿ����� �Ǵ��մϴ�
	*/

	POINT mouse = SUBWIN->GetMousePos();
	for (int i = 0; i < _vbutton.size(); i++)
	{
		if (PtInRect(&_vbutton[i]._rc, mouse))
		{
			if (_maptoolButtonKind == MAPTOOL_BUTTON_ATTRIBUTE && _vbutton[i]._kind != MAPTOOL_BUTTON_ATTRIBUTE)
			{
				_isAttribute = false;
				_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL;
				SUBWIN->setAttributeKind(_maptoolAttributeButtonKind);
				TILEMAPMANAGER->allRender();
			}

			if (_vbutton[i]._kind == MAPTOOL_BUTTON_TILE)
			{
				SUBWIN->SetCTRL(CTRL_TERRAINDRAW);
				_maptoolButtonKind = MAPTOOL_BUTTON_TILE;
				_nowIndex = 0;
				_sampleMaxIndex = TILEMAPMANAGER->getSampleTileMapMaxIndex_Terrian();
				_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(_nowIndex));

				_nowAction = "Ÿ�� �׸���";

				_startFrameX = 0;
				_startFrameY = 0;
				_endFrameX = 0;
				_endFrameY = 0;

				sampleSelectRender();

				SUBWIN->SetIndex(_nowIndex);
				SUBWIN->SetStartFramePoint(POINT{ _startFrameX,_startFrameY });
				SUBWIN->SetEndFramePoint(POINT{ _endFrameX,_endFrameY });
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_OBJECT)
			{
				SUBWIN->SetCTRL(CTRL_OBJECTDRAW);
				_maptoolButtonKind = MAPTOOL_BUTTON_OBJECT;
				_nowIndex = 0;
				_sampleMaxIndex = TILEMAPMANAGER->getSampleTileMapMaxIndex_Object();
				_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));

				_nowAction = "������Ʈ �׸���";

				_startFrameX = 0;
				_startFrameY = 0;
				_endFrameX = 0;
				_endFrameY = 0;

				sampleSelectRender();

				SUBWIN->SetIndex(_nowIndex);
				SUBWIN->SetStartFramePoint(POINT{ _startFrameX,_startFrameY });
				SUBWIN->SetEndFramePoint(POINT{ _endFrameX,_endFrameY });
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_EREASER)
			{
				SUBWIN->SetCTRL(CTRL_ERASER);
				_maptoolButtonKind = MAPTOOL_BUTTON_EREASER;

				_nowAction = "���찳";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_INIT)
			{
				SUBWIN->SetCTRL(CTRL_INIT);
				_maptoolButtonKind = MAPTOOL_BUTTON_INIT;
				TILEMAPMANAGER->init(stoi(_nowSizeX), stoi(_nowSizeY));

				_nowAction = "�ʱ�ȭ";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_IMAGE)
			{
				SUBWIN->SetCTRL(CTRL_IMAGELOAD);
				_maptoolButtonKind = MAPTOOL_BUTTON_IMAGE;

				_nowAction = "�̹��� ����";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE)
			{
				_isAttribute = true;

				SUBWIN->SetCTRL(CTRL_ATTRIBUTE);
				_maptoolButtonKind = MAPTOOL_BUTTON_ATTRIBUTE;
				_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL;
				SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL);

				_nowAction = "�Ӽ� ����";

				TILEMAPMANAGER->attributeRender();
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_UP)
			{
				//����ư Ŭ����
				if (_nowTileNum < TILE_NUM_MAX - 1)
				{
					_nowTileNum++;
				}

				SUBWIN->SetTileNum(_nowTileNum);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_DOWN)
			{
				//�Ʒ���ư Ŭ����
				if (_nowTileNum > 0)
				{
					_nowTileNum--;
				}
				SUBWIN->SetTileNum(_nowTileNum);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_BEFORE)
			{
				/*
				������ưŬ����
				*/
				if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE)
				{
					if (_nowIndex > 0)
					{
						_nowIndex--;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(_nowIndex));
					}
					else
					{
						_nowIndex = _sampleMaxIndex - 1;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(_nowIndex));
					}
				}

				if (_maptoolButtonKind == MAPTOOL_BUTTON_OBJECT)
				{
					if (_nowIndex > 0)
					{
						_nowIndex--;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));
					}
					else
					{
						_nowIndex = _sampleMaxIndex - 1;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));
					}
				}

				_startFrameX = 0;
				_startFrameY = 0;
				_endFrameX = 0;
				_endFrameY = 0;

				sampleSelectRender();

				SUBWIN->SetIndex(_nowIndex);
				SUBWIN->SetStartFramePoint(POINT{ _startFrameX,_startFrameY });
				SUBWIN->SetEndFramePoint(POINT{ _endFrameX,_endFrameY });

			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_NEXT)
			{
				/*
				������ưŬ����
				*/
				if (_maptoolButtonKind == MAPTOOL_BUTTON_TILE)
				{
					if (_nowIndex < _sampleMaxIndex - 1)
					{
						_nowIndex++;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(_nowIndex));
					}
					else
					{
						_nowIndex = 0;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Terrian(_nowIndex));
					}
				}

				if (_maptoolButtonKind == MAPTOOL_BUTTON_OBJECT)
				{
					if (_nowIndex < _sampleMaxIndex - 1)
					{
						_nowIndex++;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));
					}
					else
					{
						_nowIndex = 0;
						_sampleImg = IMAGEMANAGER->findImage(TILEMAPMANAGER->getNowSampleTileMapString_Object(_nowIndex));
					}
				}

				_startFrameX = 0;
				_startFrameY = 0;
				_endFrameX = 0;
				_endFrameY = 0;

				sampleSelectRender();

				SUBWIN->SetIndex(_nowIndex);
				SUBWIN->SetStartFramePoint(POINT{ _startFrameX,_startFrameY });
				SUBWIN->SetEndFramePoint(POINT{ _endFrameX,_endFrameY });
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_SIZECHANGE)
			{
				/*
				������ �����
				*/
				if (!_changeSizeX.size() == 0 && !_changeSizeY.size() == 0)
				{
					_nowSizeX = _changeSizeX;
					_nowSizeY = _changeSizeY;
					_changeSizeX.clear();
					_changeSizeY.clear();
					TILEMAPMANAGER->setTileMapSize(POINT{ stoi(_nowSizeX), stoi(_nowSizeY) });
					_maptoolButtonKind = MAPTOOL_BUTTON_SIZECHANGE;
					SUBWIN->SetCTRL(CTRL_SIZECHANGE);
				}

				_nowAction = "������ ����";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_SAVE)
			{
				SUBWIN->SetCTRL(CTRL_SAVE);
				_maptoolButtonKind = MAPTOOL_BUTTON_SAVE;
				_nowAction = "����";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_LOAD)
			{
				SUBWIN->SetCTRL(CTRL_LOAD);
				_maptoolButtonKind = MAPTOOL_BUTTON_LOAD;
				_nowAction = "�ε�";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_QUIT)
			{
				SCENEMANAGER->changeScene("titleScene");
				DestroyWindow(SUBWIN->getHwnd());
			}


			_sound.effSoundPlay("�޴�����");
		}
	}

	//�Ӽ�����Ͻ�
	if (_isAttribute)
	{
		for (int i = 0; i < _vAttributeButton.size(); i++)
		{
			if (PtInRect(&_vAttributeButton[i]._rc, mouse))
			{
				if (_vAttributeButton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL)
				{
					_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL;
					SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL);
				}
				if (_vAttributeButton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS)
				{
					_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS;
					SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS);
				}
				if (_vAttributeButton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL)
				{
					_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL;
					SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL);
				}
				if (_vAttributeButton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE)
				{
					_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE;
					SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE);
				}
			}
		}
	}
}

void maptool_sub::enteredSize()
{
	/*
	������ ���� �۾� �Է��� ó���մϴ�
	*/
	if (_isSizeX)
	{
		_changeSizeX = INPUTMANAGER->getKeyBoard();
	}
	else if (_isSizeY)
	{
		_changeSizeY = INPUTMANAGER->getKeyBoard();
	}
}

void maptool_sub::minimapCameraRender(HDC hdc)
{
	int totalMapSizeX = stoi(_nowSizeX)*(TILE_SIZE_X);
	int totalMapSizeY = stoi(_nowSizeY)*(TILE_SIZE_Y);

	POINT camera = CAMERAMANAGER->getCameraPos();

	if (_cameraImg != nullptr)
	{
		//ī�޶�
		if (totalMapSizeX < WINSIZEX && totalMapSizeY < WINSIZEY)
		{
			_cameraImg->render(hdc, 50, 530, TILE_MINIMAP_SIZEX, TILE_MINIMAP_SIZEY);
		}
		else if (totalMapSizeX < WINSIZEX)
		{
			_cameraImg->render(hdc, 50, 530 + camera.y / (totalMapSizeY / 200), TILE_MINIMAP_SIZEX, 200 * WINSIZEY / totalMapSizeY);
		}
		else if (totalMapSizeY < WINSIZEY)
		{
			_cameraImg->render(hdc, 50 + camera.x / (totalMapSizeX / 300), 530, 300 * WINSIZEX / totalMapSizeX, TILE_MINIMAP_SIZEY);
		}
		else
		{
			_cameraImg->render(hdc, 50 + camera.x / (totalMapSizeX / 300), 530 + camera.y / (totalMapSizeY / 200),
				300 * WINSIZEX / totalMapSizeX, 200 * WINSIZEY / totalMapSizeY);
		}
	}
}
