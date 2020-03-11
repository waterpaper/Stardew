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
	//�̰��� ���鿡 �ʿ��� �����͸� �Է��մϴ�. 
	//������ �� Ŭ������ ��ӹ޾� ����մϴ�
	vector<imageButton> button;

	vector<string> _tileSampleImageNameVector;					//�����̹����� �̸��� ������ �ִ� ���� ����
	vector<string> _objSampleImageNameVector;

	SCENE_NAME _sceneName;										//���� �� ������ �����մϴ�
	INGAMESCENE_NAME _ingameName;								//���� �ΰ��� ���� ������ �����մϴ�

	vector<RECT> _moveRcVector;									//�̵��� �� �ִ� ��Ʈ�� �����մϴ�

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

	//���� �̵��� �� �ִ� ��Ʈ�� �׷��ݴϴ�
	void addMoveRc(int x, int y, int width, int height);

	//��Ʈ �浹�� �Ǵ��մϴ�
	int collisionRc(RECT rc);
	//��Ʈ ��ó���� ��Ʈ�� Ŭ���ߴ��� �Ǵ��մϴ�
	int selectRc(POINT point);

	//�� ������� ��Ʈ�� �����ݴϴ�
	void clearMoveRc();

	//���� �´� Ÿ�ϸ��� �ε��Ѵ�
	void sceneLoading(const char *fileName, INGAMESCENE_NAME sceneName);

	//���� �����Ǹ� ī�޶�� �÷��̾ �������ش�.
	void setScenePosition(int x, int y);

	void setMouseFrame();

	int getIngameScene() { return (int)_ingameName; };
};

