#pragma once
#include "tileMap.h"

class maptool_main
{
private:
	image *_sampleExampleImage;						//커서 아래에 출력될 이미지입니다.
	int _currentTileX, _currentTileY;				//선택된 타일의 위치를 저장한 변수이다.
	char str[128];

	int _maxTileX, _maxTileY;						//전체 타일맵의 수를 저장한 변수이다.

	int _startX;
	int _startY;

	int _maptoolCameraPositionX, _maptoolCameraPositionY;//카메랑 이동을 위한 변수를 저장한다
	int _moveSpeed;

	POINT _imageFrame;									//사용자가 선택한 타일 혹은 오브젝트를 가진 변수이다.

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

	void cameraMove();								//맵툴에서 카메라 이동을 관리합니다
	void initMap();									//초기화 됏을때를 처리합니다
	void eraser(int x, int y);						//지우개를 처리합니다
	void saveMap();									//선택된 타일에 맵을 저장합니다
	void loadMap();									//선택된 타일에 맵을 불러옵니다
	void imageLoadMap();							//맵에 이미지를 로드합니다
	void mapClick();								//맵에 어느부분이 클릭되었는지 판단합니다
	void setMapTerrain(int x, int y);				//사용자가 선택한 화면에 좌표를 인식하고 맵을 바꿔줍니다
	void setMapObject(int x, int y);				//사용자가 선택한 화면에 좌표를 인식하고 오브젝트를 추가합니다
	void setMapAttribute(int x, int y);				//사용자가 선택한 화면에 좌표를 인식하고 속성을 바꿔줍니다
	void inputKeyboard();							//키보드 입력을 처리합니다.
	void sampleExampleImageRender(HDC hdc);			//커서 아래에 선택된 샘플 이미지를 출력합니다

};

