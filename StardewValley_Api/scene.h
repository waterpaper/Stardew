#pragma once
#include "gameNode.h"
#include "button.h"

struct cloud
{
	image *_img;
	RECT _rc;
	int _speed;
};

enum SCENE_NAME
{
	SCENE_NAME_NULL_SCENE,
	SCENE_NAME_LOADDING_SCENE,
	SCENE_NAME_LOAD_SCENE,
	SCENE_NAME_START_SCENE,
	SCENE_NAME_MAPTOOL_SCENE,
	SCENE_NAME_INGAME_SCENE,
	SCENE_NAME_INGAME_SHOP_SCENE,
	SCENE_NAME_SCENE_END
};

enum INGAMESCENE_NAME
{
	INGAMESCENE_NAME_NULL,
	INGAMESCENE_NAME_HOME,
	INGAMESCENE_NAME_FARM,
	INGAMESCENE_NAME_HOMETOTOWN,
	INGAMESCENE_NAME_TOWN,
	INGAMESCENE_NAME_SHOP,
	INGAMESCENE_NAME_ANIMALSHOP,
	INGAMESCENE_NAME_BARN,
	INGAMESCENE_NAME_COOP,
	INGAMESCENE_NAME_END
};

class scene : public gameNode
{
protected:
	//이곳에 씬들에 필요한 데이터를 입력합니다. 
	//씬들은 이 클래스를 상속받아 사용합니다
	vector<imageButton> button;

	vector<string> _tileSampleImageNameVector;					//샘플이미지의 이름을 가지고 있는 백터 선언
	vector<string> _objSampleImageNameVector;

	SCENE_NAME _sceneName;										//현재 씬 종류를 정의합니다
	INGAMESCENE_NAME _ingameName;								//현재 인게임 씬의 종류를 정의합니다

	vector<RECT> _moveRcVector;									//이동할 수 있는 렉트를 정의합니다

	image *_blackScreen;
	int _blackAlpha;

	int _currentMapX;
	int _currentMapY;
	
public:
	scene();
	~scene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	void imageButtonRender();
	void imageButtonPoint();

	void imageButtonAdd(char* imageName, string text,int x, int y, int width, int height, int kind, bool frame = false);
	void imageButtonClear();

	//맵을 이동할 수 있는 렉트를 그려줍니다
	void addMoveRc(int x, int y, int width, int height);

	//렉트 충돌을 판단합니다
	int collisionRc(RECT rc);
	//렉트 근처에서 렉트를 클릭했는지 판단합니다
	int selectRc(POINT point);

	//각 씬변경시 렉트를 지워줍니다
	void clearMoveRc();

	//씬에 맞는 타일맵을 로딩한다
	void sceneLoading(const char *fileName, INGAMESCENE_NAME sceneName);

	//씬이 조정되면 카메라와 플레이어를 조정해준다.
	void setScenePosition(int x, int y);

	void setMouseFrame();

	int getIngameScene() { return (int)_ingameName; };
};

