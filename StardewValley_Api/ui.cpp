#include "stdafx.h"
#include "ui.h"


ui::ui()
{
}


ui::~ui()
{
	release();
}

HRESULT ui::init()
{
	return S_OK;
}

void ui::update()
{
	imageButtonPoint();
}

void ui::release()
{
	imageButtonClear();
	uiImageClear();
}

void ui::render(HDC hdc)
{
	uiImageRender(hdc);
	imageButtonRender(hdc);
}

void ui::imageButtonRender(HDC hdc)
{
	/*
	이미지 버튼을 그려줍니다
	프레임이미지(마우스 올렷을시 달라지는 이미지)가 존재하는 버튼과 아닌 버튼을 구별해 그려줍니다.
	*/
	for (int i = 0; i < _vButton.size(); i++)
	{
		if (_vButton[i]._img != nullptr)
		{
			if (_vButton[i]._isFrame)
			{
				if (_vButton[i]._ischeck)
				{
					_vButton[i]._img->frameRender(hdc, _vButton[i]._rc.left, _vButton[i]._rc.top, _vButton[i]._currentX, 0);
				}
				else
				{
					_vButton[i]._img->frameRender(hdc, _vButton[i]._rc.left, _vButton[i]._rc.top, 0, 0);
				}
			}
			else
			{
				_vButton[i]._img->render(hdc, _vButton[i]._rc.left, _vButton[i]._rc.top);
			}

			//배경모드
			SetBkMode(hdc, TRANSPARENT);
			//색상
			SetTextColor(hdc, RGB(0, 0, 0));

			TextOut(hdc, 0, 0, _vButton[i]._text.c_str(), _vButton[i]._text.size());
		}
	}
}

void ui::imageButtonPoint()
{
	/*
	현재 마우스가 어떤 버튼위에 있는지 판단합니다
	*/
	for (int i = 0; i < _vButton.size(); i++)
	{
		if (!_vButton[i]._isFrame || _vButton[i]._img == nullptr) continue;

		if (PtInRect(&_vButton[i]._rc, m_ptMouse))
		{
			_vButton[i]._ischeck = true;
			_vButton[i]._currentX = 1;
		}
		else
		{
			_vButton[i]._ischeck = false;
			_vButton[i]._currentX = 0;
		}
	}
}

void ui::imageButtonAdd(char * imageName, string text, int x, int y, int width, int height, int kind, bool frame)
{
	imageButton buttonTemp;
	if (imageName == nullptr)
	{
		buttonTemp._img = nullptr;
	}
	else
	{
		buttonTemp._img = IMAGEMANAGER->findImage(imageName);
	}
	buttonTemp._text = text;
	buttonTemp._rc = RectMake(x, y, width, height);
	buttonTemp._kind = kind;
	buttonTemp._isFrame = frame;
	buttonTemp._ischeck = false;
	buttonTemp._currentX = 0;

	_vButton.push_back(buttonTemp);
}

void ui::imageButtonClear()
{
	vector<imageButton> temp;
	_vButton.swap(temp);
	temp.clear();
}

void ui::uiImageAdd(char * imageName, int x, int y, int width, int height, int kind , bool frame)
{
	imageUi uiTemp;

	uiTemp.uiImg = IMAGEMANAGER->findImage(imageName);
	uiTemp.startX = x;
	uiTemp.startY = y;
	uiTemp.width = width;
	uiTemp.height = height;
	uiTemp.rc = RectMake(x, y, width, height);
	uiTemp.uiKind = kind;
	uiTemp.isFrame = frame;

	_vUiImage.push_back(uiTemp);
}

void ui::uiImageRender(HDC hdc)
{
	for (int i = 0; i < _vUiImage.size(); i++)
	{
		if (_vUiImage[i].isFrame)
		{
			_vUiImage[i].uiImg->frameRender(hdc, _vUiImage[i].startX, _vUiImage[i].startY, _vUiImage[i].uiImg->getFrameX(),0);
		}
		else
		{
			_vUiImage[i].uiImg->render(hdc, _vUiImage[i].startX, _vUiImage[i].startY,0,0, _vUiImage[i].width, _vUiImage[i].height);
		}
	}
}

void ui::uiImageClear()
{
	vector<imageUi> temp;
	_vUiImage.swap(temp);
	temp.clear();
}

