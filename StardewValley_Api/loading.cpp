#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체
	memset(&_imageResource, 0, sizeof(tagImageResource));


	_imageResource.keyName.resize(keyName.size(), '0');
	for (int i = 0; i < keyName.size(); i++)
	{
		_imageResource.keyName[i] = keyName[i];
	}
	//_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName.resize(keyName.size(), '0');
	for (int i = 0; i < keyName.size(); i++)
	{
		_imageResource.keyName[i] = keyName[i];
	}
	//_imageResource.keyName = keyname;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName.resize(keyName.size(), '0');
	for (int i = 0; i < keyName.size(); i++)
	{
		_imageResource.keyName[i] = keyName[i];
	}
	//_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{

	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName.resize(keyName.size(), '0');
	for (int i = 0; i < keyName.size(); i++)
	{
		_imageResource.keyName[i] = keyName[i];
	}
	//_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{

	_kind = LOAD_KIND_FRAMEIMAGE_1;
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName.resize(keyName.size(), '0');
	for (int i = 0; i < keyName.size(); i++)
	{
		_imageResource.keyName[i] = keyName[i];
	}
	//_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{
}

HRESULT loading::init()
{
	//로딩화면 백그라운드 초기화
	_background = IMAGEMANAGER->addImage("loadingImg", "images/title/loading_backImage.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loadingBackGround = IMAGEMANAGER->addImage("loadingsImg", "images/title/progressBarFront.bmp", 800, 60, true, RGB(255, 0, 255));
	
	_nowX = 300;
	_rc = RectMakeCenter(_nowX, 720, 48, 48);
	/*
	//로딩바 초기화를 하자
	_loadingBar = new progressBar;
	_loadingBar->init("images/title/progressBarFront.bmp", "images/title/progressBarBack.bmp", 100, WINSIZEY / 2 + 270, 600, 10);
	_loadingBar->setGauge(0, 0);
	*/

	//로딩바 게이지 초기화
	_currentGauge = 0;

	//캐릭터 이미지
	_loadingCharacter  = IMAGEMANAGER->addFrameImage("junimo", "images/character/character_junimo.bmp", 128 * 3, 16 * 3, 8, 1, true, RGB(255, 0, 255));

	count = 0;
	index = 0;
	return S_OK;

}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	//_loadingBar->update();
	loadingAni();
}

void loading::render()
{
	_background->render(getMemDC());
	_loadingBackGround->render(getMemDC(),100,700);
//	_loadingBar->render();

	_loadingCharacter->frameRender(getMemDC(), _rc.left, _rc.top,_loadingCharacter->getFrameX(), _loadingCharacter->getFrameY());
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	tagImageResource img = item->getImageResource();

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		break;
	case LOAD_KIND_IMAGE_1:
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND_IMAGE_2:
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	}
	//로딩바 이미지 변경
	//_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	_nowX = (float)_currentGauge/_vLoadItem.size()*600+300;
	_rc = RectMakeCenter(_nowX, 720, 48, 48);
	//카운트
	_currentGauge++;
	return FALSE;
}

void loading::loadingAni()
{
	count++;
	_loadingCharacter->setFrameY(0);
	if (count % 5 == 0)
	{
		count = 0;
		index++;
		if (index > _loadingCharacter->getMaxFrameX())
		{
			index = 0;
		}
		_loadingCharacter->setFrameX(index);
	}

}

