#pragma once
enum ANIMAL_KIND
{
	ANIMAL_KIND_NULL,
	ANIMAL_KIND_CHICKEN,
	ANIMAL_KIND_COW,
	ANIMAL_KIND_GOAT,
	ANIMAL_KIND_DUCK,
	ANIMAL_KIND_SHEEP,
	ANIMAL_KIND_PIG,
	ANIMAL_KIND_RABBIT,
	ANIMAL_KIND_END,
};

enum ANIMAL_DIRECTION
{
	ANIMAL_DIRECTION_NULL = -1,
	ANIMAL_DIRECTION_DOWN,
	ANIMAL_DIRECTION_RIGHT,
	ANIMAL_DIRECTION_UP,
	ANIMAL_DIRECTION_LEFT,
	ANIMAL_DIRECTION_END
};
enum ANIMAL_ACTING
{
	ANIMAL_ACTING_NULL = -1,
	ANIMAL_ACTING_IDLE,
	ANIMAL_ACTING_MOVE,
	ANIMAL_ACTING_END
};

class animal
{
private:
	image *_img;
	POINT _frame;
	int _frameCount;

	RECT _rc;
	int _posX, _posY;
	int _width, _height;
	int _speed;
	int _lifeperiod;
	int _moveTime;
	int _idleTime;
	int _settingTime;

	ANIMAL_DIRECTION _dirction;
	ANIMAL_ACTING _acting;
	ANIMAL_KIND _kind;

	bool _isBaby;
	bool _isDayProduction;

public:
	animal();
	~animal();

	HRESULT init(ANIMAL_KIND kind, int period);
	void update();
	void render(HDC hdc);
	void release();

	void frameAnimation();

	image *getAnimalImage() { return _img; };
	POINT getImageFrame() { return _frame; };
	int getPositionX() { return _posX; };
	int	getPositionY() { return _posY; };
	RECT getRc() { return _rc; };
	int getWidth() { return _width; };
	int getHeight() { return _height; };
	POINT getPosition() { return POINT{ _posX,_posY }; };
	int getSpeed() { return _speed; };
	int getLifePeriod() { return _lifeperiod; };
	ANIMAL_DIRECTION getDirction() { return _dirction; };
	ANIMAL_KIND getKind() { return _kind; };
	ANIMAL_ACTING getActing() { return _acting; };
	bool getIsBaby() { return _isBaby; };
	bool getIsDayProduction() { return _isDayProduction; };

	void setAnimalImage(image *img) { _img = img; };
	void setImageFrame(POINT frame) { _frame = frame; };
	void setRc(RECT rc) { _rc = rc; };
	void setPositionX(int posX) { _posX = posX; _rc = RectMakeCenter(_posX, _posY, _width, _height);};
	void setPositionY(int posY) { _posY = posY; _rc = RectMakeCenter(_posX, _posY, _width, _height);};
	void setPosition(POINT position) { _posX = position.x, _posY = position.y; _rc = RectMakeCenter(_posX, _posY, _width, _height);};
	void setSpeed(int speed) { _speed = speed; };
	void setLifePeriod(int period) {
		_lifeperiod = period;
		if (_lifeperiod == 4)
		{
			setIsBaby(true);
		}

	};
	void setDirction(ANIMAL_DIRECTION direction) { _dirction = direction; };
	void setKind(ANIMAL_KIND kind) { _kind = kind; };
	void setActing(ANIMAL_ACTING acting) { _acting = acting; };
	void setIsBaby(bool isbaby);
	void setIsDayProduction(bool isDayProduction) { _isDayProduction = isDayProduction; };
};

