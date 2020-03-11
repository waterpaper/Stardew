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
	_maptoolSubBackgroundImg = IMAGEMANAGER->findImage("맵툴창_배경");
	_cameraImg = IMAGEMANAGER->findImage("맵툴창_카메라");
	_sampleSelectRectImg = IMAGEMANAGER->findImage("맵툴창_샘플선택");

	imageButtonAdd("맵툴창_사이즈변경버튼", "", 370, 30, 100, 80, MAPTOOL_BUTTON_SIZECHANGE, true);

	imageButtonAdd("맵툴창_타일버튼", "", 40, 130, 100, 80, MAPTOOL_BUTTON_TILE, true);
	imageButtonAdd("맵툴창_오브젝트버튼", "", 150, 130, 100, 80, MAPTOOL_BUTTON_OBJECT, true);
	imageButtonAdd("맵툴창_속성버튼", "", 260, 130, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE, true);
	imageButtonAdd("맵툴창_이미지버튼", "", 370, 130, 100, 80, MAPTOOL_BUTTON_IMAGE, true);

	imageButtonAdd("맵툴창_지우기버튼", "", 370, 260, 100, 80, MAPTOOL_BUTTON_EREASER, true);
	imageButtonAdd("맵툴창_초기화버튼", "", 370, 350, 100, 80, MAPTOOL_BUTTON_INIT, true);

	imageButtonAdd("맵툴창_저장버튼", "", 370, 480, 100, 80, MAPTOOL_BUTTON_SAVE, true);
	imageButtonAdd("맵툴창_로드버튼", "", 370, 570, 100, 80, MAPTOOL_BUTTON_LOAD, true);
	imageButtonAdd("맵툴창_나가기버튼", "", 370, 660, 100, 80, MAPTOOL_BUTTON_QUIT, true);

	imageButtonAdd("맵툴창_다음버튼", "", 430, 225, 24, 24, MAPTOOL_BUTTON_NEXT, true);
	imageButtonAdd("맵툴창_이전버튼", "", 380, 225, 24, 24, MAPTOOL_BUTTON_BEFORE, true);

	imageButtonAdd("맵툴창_아래버튼", "", 46, 60, 24, 24, MAPTOOL_BUTTON_DOWN, true);
	imageButtonAdd("맵툴창_위버튼", "", 88, 60, 24, 24, MAPTOOL_BUTTON_UP, true);

	imageButtonAttributeAdd("맵툴창_속성흙버튼", "", 60, 250, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_SOIL, true);
	imageButtonAttributeAdd("맵툴창_속성풀버튼", "", 170, 250, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_GRASS, true);
	imageButtonAttributeAdd("맵툴창_속성일반버튼", "", 60, 340, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_NORMAL, true);
	imageButtonAttributeAdd("맵툴창_속성이동불가버튼", "", 170, 340, 100, 80, MAPTOOL_BUTTON_ATTRIBUTE_KIND_NOTMOVE, true);

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

	//색상//글씨체 선택
	SelectObject(hdc, hSmallFont);
	SetTextColor(hdc, RGB(183, 89, 20));

	//글씨출력
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

	//색상
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
	이미지 버튼을 그려줍니다
	프레임이미지(마우스 올렷을시 달라지는 이미지)가 존재하는 버튼과 아닌 버튼을 구별해 그려줍니다.
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

		//배경모드
		SetBkMode(hdc, TRANSPARENT);
		//색상
		SetTextColor(hdc, RGB(0, 0, 0));

		TextOut(hdc, 0, 0, _vbutton[i]._text.c_str(), _vbutton[i]._text.size());
	}

	//속성모드일때
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

			//배경모드
			SetBkMode(hdc, TRANSPARENT);
			//색상
			SetTextColor(hdc, RGB(0, 0, 0));

			TextOut(hdc, 0, 0, _vAttributeButton[i]._text.c_str(), _vAttributeButton[i]._text.size());
		}
	}
}

void maptool_sub::imageButtonPoint()
{
	/*
	현재 마우스가 어떤 버튼위에 있는지 판단합니다
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

	//속성모드일때
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
	샘플이미지를 랜더합니다
	오브젝트의 경우 중간지점에 랜더하기 위해 계산합니다
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
	타일맵 선택시 선택된 크기만큼의 사각형을 랜더합니다
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
	클릭시 어떤 행동을 할지 판단합니다
	*/
	POINT mouse = SUBWIN->GetMousePos();

	if (SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//타일을 클릭햇을시
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

		//글씨 처리
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

		//버튼클릭
		clickButton();
	}
	else if (SUBWIN->GetIsActive() && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		//타일을 클릭햇을시
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
	클릭시 어떤 버튼이 클릭되었는지 판단합니다
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

				_nowAction = "타일 그리기";

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

				_nowAction = "오브젝트 그리기";

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

				_nowAction = "지우개";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_INIT)
			{
				SUBWIN->SetCTRL(CTRL_INIT);
				_maptoolButtonKind = MAPTOOL_BUTTON_INIT;
				TILEMAPMANAGER->init(stoi(_nowSizeX), stoi(_nowSizeY));

				_nowAction = "초기화";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_IMAGE)
			{
				SUBWIN->SetCTRL(CTRL_IMAGELOAD);
				_maptoolButtonKind = MAPTOOL_BUTTON_IMAGE;

				_nowAction = "이미지 선택";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_ATTRIBUTE)
			{
				_isAttribute = true;

				SUBWIN->SetCTRL(CTRL_ATTRIBUTE);
				_maptoolButtonKind = MAPTOOL_BUTTON_ATTRIBUTE;
				_maptoolAttributeButtonKind = MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL;
				SUBWIN->setAttributeKind(MAPTOOL_BUTTON_ATTRIBUTE_KIND_NULL);

				_nowAction = "속성 선택";

				TILEMAPMANAGER->attributeRender();
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_UP)
			{
				//위버튼 클릭시
				if (_nowTileNum < TILE_NUM_MAX - 1)
				{
					_nowTileNum++;
				}

				SUBWIN->SetTileNum(_nowTileNum);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_DOWN)
			{
				//아래버튼 클릭시
				if (_nowTileNum > 0)
				{
					_nowTileNum--;
				}
				SUBWIN->SetTileNum(_nowTileNum);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_BEFORE)
			{
				/*
				이전버튼클릭시
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
				다음버튼클릭시
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
				사이즈 변경시
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

				_nowAction = "사이즈 변경";
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_SAVE)
			{
				SUBWIN->SetCTRL(CTRL_SAVE);
				_maptoolButtonKind = MAPTOOL_BUTTON_SAVE;
				_nowAction = "저장";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_LOAD)
			{
				SUBWIN->SetCTRL(CTRL_LOAD);
				_maptoolButtonKind = MAPTOOL_BUTTON_LOAD;
				_nowAction = "로드";
				ShowCursor(true);
			}
			if (_vbutton[i]._kind == MAPTOOL_BUTTON_QUIT)
			{
				SCENEMANAGER->changeScene("titleScene");
				DestroyWindow(SUBWIN->getHwnd());
			}


			_sound.effSoundPlay("메뉴선택");
		}
	}

	//속성모드일시
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
	사이즈 변경 글씨 입력을 처리합니다
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
		//카메라
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
