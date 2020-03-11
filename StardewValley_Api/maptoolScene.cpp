#include "stdafx.h"
#include "maptoolScene.h"


maptoolScene::maptoolScene()
{
}


maptoolScene::~maptoolScene()
{
}

HRESULT maptoolScene::init()
{
	_maptool = new maptool_main();
	_sub = new maptool_sub();
	
	_maptool->init();
	SUBWIN->init();
	SUBWIN->SetScene(_sub);

	_sound.soundOff();
	_sound.soundPlay("¸ÊÅø");

	return S_OK;
}

void maptoolScene::update()
{
	_maptool->update();
	SUBWIN->update();
	SUBWIN->GetCTRL();
}

void maptoolScene::render()
{
	_maptool->render(getMemDC());
	SUBWIN->render();
}

void maptoolScene::release()
{
	_maptool->release();
}
