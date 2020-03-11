#pragma once
#include "ui.h"
enum UIBUTTONKIND_EXITKIND
{
	UIBUTTONKIND_EXITKIND_NULL,
	UIBUTTONKIND_EXITKIND_TITLE=100,
	UIBUTTONKIND_EXITKIND_EXIT,
	UIBUTTONKIND_EXITKIND_BACKGROUND,
	UIBUTTONKIND_EXITKIND_EFFECT,
	UIBUTTONKIND_EXITKIND_END
};
class ui_exit:public ui
{
private:
	image *_barFront, *_barBack, *_controlButton;
	RECT _frontBackGroundVolume, _backBackGroundVolume, _frontEffectVolume, _backEffectVolume;		//음량바를 보여주기 위한 변수
	RECT _backGroundControlButton, _effectControlButton;											//음량바 조절을 위한 변수

	int _backgroundVolumeSize, _effectVolumeSize;


public:
	ui_exit();
	~ui_exit();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void barControlButtonMove(UIBUTTONKIND_EXITKIND kind, int num);
};

