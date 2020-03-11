#pragma once

enum SEASON
{
	SEASON_NULL,
	SEASON_SPRING,
	SEASON_SUMMER,
	SEASON_FALL,
	SEASON_WINTER,
	SEASON_END
};

enum WEEK 
{
	WEEK_NULL,
	WEEK_MONDAY,
	WEEK_TUESDAY,
	WEEK_WEDNESDAY,
	WEEK_THURSDAY,
	WEEK_FRIDAY,
	WEEK_SATURDAY,
	WEEK_SUNDAY,
	WEEK_END
};

class gameTime
{
private:
	SEASON _nowSeason;	//현재 계절
	int _nowDate;		//현재 날짜
	WEEK _nowWeek;		//현재 요일
	int _nowHour;		//현재 시간
	int _nowMin;		//현재 분

public:
	gameTime();
	~gameTime();

	SEASON getSeason() { return _nowSeason;};
	int getDate() { return _nowDate; };
	WEEK getWeek() { return _nowWeek; };
	int getHour() { return _nowHour; };
	int getMin() { return _nowMin; };

	void setSeason(int season) { 
		if (season==1)
		{
			_nowSeason = SEASON_SPRING;
		}
		else if (season == 2)
		{
			_nowSeason = SEASON_SUMMER;
		}
		else if (season == 3)
		{
			_nowSeason = SEASON_FALL;
		}
		else if (season == 4)
		{
			_nowSeason = SEASON_WINTER;
		}
		else
		{
			_nowSeason = SEASON_END;
		}
	};
	void setDate(int date) { _nowDate = date ; };
	void setWeek(int week) { 
		if (week == 1)
		{
			_nowWeek = WEEK_MONDAY;
		}
		else if (week == 2)
		{
			_nowWeek = WEEK_TUESDAY;
		}
		else if (week == 3)
		{
			_nowWeek = WEEK_WEDNESDAY;
		}
		else if (week == 4)
		{
			_nowWeek = WEEK_THURSDAY;
		}
		else if (week == 5)
		{
			_nowWeek = WEEK_FRIDAY;
		}
		else if (week == 6)
		{
			_nowWeek = WEEK_SATURDAY;
		}
		else if (week == 7)
		{
			_nowWeek = WEEK_SUNDAY;
		}
		else
		{
			_nowWeek = WEEK_END;
		}
	};
	void setHour(int hour) { _nowHour = hour; };
	void setMin(int min) { _nowMin = min; };
};

