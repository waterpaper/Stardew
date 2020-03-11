#pragma once
#include "scene.h"

enum SHOPSCENE_MOVE
{
	SHOPSCENE_MOVE_NULL = -1,
	SHOPSCENE_MOVE_TOWN,
	SHOPSCENE_MOVE_SHOP,
	SHOPSCENE_MOVE_BAG,
	SHOPSCENE_MOVE_END
};

class shopScene:public scene
{
private:
	int _inventoryNum;
	image *_bag;

public:
	shopScene();
	~shopScene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

