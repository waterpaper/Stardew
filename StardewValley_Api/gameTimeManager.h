#pragma once
#include "singletonBase.h"
#include "gameTime.h"

struct gameTimeValue
{
	SEASON season;	//현재 계절
	int date;		//현재 날짜
	WEEK week;		//현재 요일
	int hour;		//현재 시간
	int min;		//현재 분
};

class gameTimeManager:public singletonBase<gameTimeManager>
{
private:
	gameTime _gameTime;
	int _minUpdateTime;
	long _timeTemp;

public:
	gameTimeManager();
	~gameTimeManager();

	SEASON getSeason() { return _gameTime.getSeason(); };
	int getDate() { return _gameTime.getDate(); };
	WEEK getWeek() { return _gameTime.getWeek(); };
	int getHour() { return _gameTime.getHour(); };
	int getMin() { return _gameTime.getMin(); };

	void setSeason(int season) { _gameTime.setSeason(season); };
	void setDate(int date) { _gameTime.setDate(date); };
	void setWeek(int week) { _gameTime.setWeek(week); };
	void setHour(int hour) { _gameTime.setHour(hour); };
	void setMin(int min) { _gameTime.setMin(min); };

	HRESULT init();
	void update();
	
	void inputKey();

	void nextDay();

	void addMenuTime(long time) { _timeTemp += time; };

	gameTimeValue getGameTime();
};

