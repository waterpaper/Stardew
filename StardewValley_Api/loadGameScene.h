#pragma once
#include "scene.h"
#include "loadGame.h"

enum LOADGAMEBUTTON
{
	LOADGAMEBUTTON_NULL,
	LOADGAMEBUTTON_CANCELBUTTON,
	LOADGAMEBUTTON_END
};

class loadGameScene:public scene
{
private:
	image *_backImg;
	RECT _load1, _load2, _load3;
	loadGame _loadGame;
	int num;
	bool _isLoad;

	bool _isLoad1, _isLoad2, _isLoad3;
	string _load1_Name, _load2_Name, _load3_Name;
	string _load1_FarmName, _load2_FarmName, _load3_FarmName;
	string _load1_Date, _load2_Date, _load3_Date;

	
public:
	loadGameScene();
	~loadGameScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void initLoadData();
};

