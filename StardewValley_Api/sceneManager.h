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
	//현재씬
	static gameNode* _currentScene;
	//씬목록
	mSceneList _mSceneList;
	INGAMESCENE_NAME _ingameName;								//현재 인게임 씬의 종류를 정의합니다

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
	//씬추가하기
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬변경(현재씬으로)
	HRESULT changeScene(string sceneName);

	//현재위치를 다시 그려준다
	void reDrawPosition(bool isPlayer, int floor, int positionX, int positionY, int width, int height, int cameraX, int cameraY);

	int getIngameName();
	void setIngameName(INGAMESCENE_NAME name) { _ingameName = name; };
};

