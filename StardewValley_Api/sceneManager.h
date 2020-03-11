#pragma once
#include"singletonBase.h"
#include "scene.h"

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//�����
	static gameNode* _currentScene;
	//�����
	mSceneList _mSceneList;
	INGAMESCENE_NAME _ingameName;								//���� �ΰ��� ���� ������ �����մϴ�

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
	//���߰��ϱ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//������(���������)
	HRESULT changeScene(string sceneName);

	//������ġ�� �ٽ� �׷��ش�
	void reDrawPosition(bool isPlayer, int floor, int positionX, int positionY, int width, int height, int cameraX, int cameraY);

	int getIngameName();
	void setIngameName(INGAMESCENE_NAME name) { _ingameName = name; };
};

