#pragma once
#include "tileMap.h"

class maptool_main
{
private:
	image *_sampleExampleImage;						//Ŀ�� �Ʒ��� ��µ� �̹����Դϴ�.
	int _currentTileX, _currentTileY;				//���õ� Ÿ���� ��ġ�� ������ �����̴�.
	char str[128];

	int _maxTileX, _maxTileY;						//��ü Ÿ�ϸ��� ���� ������ �����̴�.

	int _startX;
	int _startY;

	int _maptoolCameraPositionX, _maptoolCameraPositionY;//ī�޶� �̵��� ���� ������ �����Ѵ�
	int _moveSpeed;

	POINT _imageFrame;									//����ڰ� ������ Ÿ�� Ȥ�� ������Ʈ�� ���� �����̴�.

	OPENFILENAME OFN;

	int ctrl;

	char lpstrFile[MAX_PATH] = "";

public:
	maptool_main();
	~maptool_main();

	HRESULT init();
	void render(HDC hdc);
	void update();
	void release();

	void cameraMove();								//�������� ī�޶� �̵��� �����մϴ�
	void initMap();									//�ʱ�ȭ �������� ó���մϴ�
	void eraser(int x, int y);						//���찳�� ó���մϴ�
	void saveMap();									//���õ� Ÿ�Ͽ� ���� �����մϴ�
	void loadMap();									//���õ� Ÿ�Ͽ� ���� �ҷ��ɴϴ�
	void imageLoadMap();							//�ʿ� �̹����� �ε��մϴ�
	void mapClick();								//�ʿ� ����κ��� Ŭ���Ǿ����� �Ǵ��մϴ�
	void setMapTerrain(int x, int y);				//����ڰ� ������ ȭ�鿡 ��ǥ�� �ν��ϰ� ���� �ٲ��ݴϴ�
	void setMapObject(int x, int y);				//����ڰ� ������ ȭ�鿡 ��ǥ�� �ν��ϰ� ������Ʈ�� �߰��մϴ�
	void setMapAttribute(int x, int y);				//����ڰ� ������ ȭ�鿡 ��ǥ�� �ν��ϰ� �Ӽ��� �ٲ��ݴϴ�
	void inputKeyboard();							//Ű���� �Է��� ó���մϴ�.
	void sampleExampleImageRender(HDC hdc);			//Ŀ�� �Ʒ��� ���õ� ���� �̹����� ����մϴ�

};

