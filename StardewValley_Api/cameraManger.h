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

	void cameraMove(int positionX, int positionY);									//ī�޶� ��ġ�� �̵��մϴ�
	void cameraAllTileRender(HDC hdc, int mapSizeX, int mapSizeY);					//���ۿ� ��� Ÿ���� �����մϴ�

	void minimapRender(HDC hdc, int minimapSizeX, int minimapSizeY, int posX, int posY);		//�̴ϸʷ���
	void setMinimapSize(POINT mapSize);

	POINT getCameraPos() { return _camera; };
	int getCameraPosX() { return _camera.x; };
	int getCameraPosY() { return _camera.y; };
	bool getIsBottomCamera() { return _isBottomCamera; };

	void setCameraPos(POINT camera) { _camera = camera; };
	void setCameraPosX(int cameraX) { _camera.x = cameraX; };
	void setCameraPosY(int cameraY) { _camera.y = cameraY; };
};

