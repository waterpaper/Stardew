#pragma once
#include "singletonBase.h"

class cameraManger :public singletonBase<cameraManger>
{
private:
	POINT _camera;
	POINT _mapsize;
	image *_totalBuffer;
	image *add;
	image *_totalMinimapBuffer;

	bool _isBottomCamera;

public:
	cameraManger();
	~cameraManger();

	HRESULT init();
	void render(HDC hdc, bool isMapTool, vector<RECT> moveRect);
	void release();

	void cameraMove(int positionX, int positionY);									//카메라 위치를 이동합니다
	void cameraAllTileRender(HDC hdc, int mapSizeX, int mapSizeY);					//버퍼에 모든 타일을 랜더합니다

	void minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY);		//미니맵랜더
	void setMinimapSize(POINT mapSize);

	POINT getCameraPos() { return _camera; };
	int getCameraPosX() { return _camera.x; };
	int getCameraPosY() { return _camera.y; };
	bool getIsBottomCamera() { return _isBottomCamera; };

	void setCameraPos(POINT camera) { _camera = camera; };
	void setCameraPosX(int cameraX) { _camera.x = cameraX; };
	void setCameraPosY(int cameraY) { _camera.y = cameraY; };
};

