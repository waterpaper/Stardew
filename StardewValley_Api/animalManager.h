#pragma once
#include "singletonBase.h"
#include "animal.h"

class animalManager:public singletonBase<animalManager>
{
private:
	vector<animal> _vCoopAnimal;
	vector<animal> _vBarnAnimal;

public:
	animalManager();
	~animalManager();

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();

	vector<animal> getAniMalBarnVector() { return _vBarnAnimal; };
	vector<animal> getAniMalCoopVector() { return _vCoopAnimal; };

	void clearAnimal();

	void addAnimal(ANIMAL_KIND animalkind, int period);
	void barnUpdate();
	void barnRender(HDC hdc);
	void coopUpdate();
	void coopRender(HDC hdc);
	void nextDay();
	void barnGetItem(int num);
	void coopGetItem(int num);
	void animalMove();
	bool nextMoveCollision(RECT rc, int num = -1);

	int selectCoopAnimalNum();
	int selectBarnAnimalNum();

	bool coopRectCollision(RECT rc, int num = -1);
	bool barnRectCollision(RECT rc, int num = -1);
};

