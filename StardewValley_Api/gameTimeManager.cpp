#include "stdafx.h"
#include "gameTimeManager.h"


gameTimeManager::gameTimeManager()
{
}


gameTimeManager::~gameTimeManager()
{
}

HRESULT gameTimeManager::init()
{
	_gameTime.setSeason(SEASON_SPRING);
	_gameTime.setWeek(WEEK_MONDAY);
	_gameTime.setDate(1);
	_gameTime.setHour(6);
	_gameTime.setMin(0);

	_minUpdateTime = 10000;
	_timeTemp = GetTickCount();

	return S_OK;
}

void gameTimeManager::update()
{
	inputKey();
	long timeTemp = GetTickCount();

	if (_minUpdateTime < timeTemp - _timeTemp)
	{
		_timeTemp = GetTickCount();
		_gameTime.setMin(_gameTime.getMin() + 10);

		if (_gameTime.getHour() == 5 && _gameTime.getMin() == 50)
		{
			FARMMANAGER->growCrops();
			ANIMALMANAGER->nextDay();
			PLAYERMANAGER->setPlayerFull_Hp_Actingpower();
		}

		if (_gameTime.getMin() > 50)
		{
			//시간 추가

			_gameTime.setHour(_gameTime.getHour() + 1);
			_gameTime.setMin(0);


			if (_gameTime.getHour() > 23)
			{
				// 날짜 추가
				_gameTime.setHour(0);
				_gameTime.setDate(_gameTime.getDate() + 1);
				_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
	

				if (_gameTime.getDate() > 27)
				{
					//계절추가
					_gameTime.setDate(1);
					_gameTime.setSeason((SEASON)_gameTime.getSeason() + 1);

					if (_gameTime.getSeason() >= 5)
					{
						_gameTime.setSeason(SEASON_SPRING);
					}

					TILEMAPMANAGER->seasonImageSeting();
					TILEMAPMANAGER->allRender();
				}
			}
		}
	}
}

void gameTimeManager::inputKey()
{
	/*
	시간을 넘어가기 위한 키입력을 처리하는 부분입니다
	*/

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		/*
		1시간을 추가합니다
		*/
		_timeTemp = GetTickCount();
		_gameTime.setHour(_gameTime.getHour() + 1);
		_gameTime.setMin(0);

		if (_gameTime.getHour() > 23)
		{
			// 날짜 추가
			_gameTime.setHour(0);
			_gameTime.setDate(_gameTime.getDate() + 1);
			_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
			FARMMANAGER->growCrops();
			ANIMALMANAGER->nextDay();

			if (_gameTime.getDate() > 28)
			{
				//계절추가
				_gameTime.setDate(1);
				_gameTime.setSeason((SEASON)_gameTime.getSeason() + 1);

				if (_gameTime.getSeason() >= 5)
				{
					_gameTime.setSeason(SEASON_SPRING);
				}

				TILEMAPMANAGER->seasonImageSeting();
				TILEMAPMANAGER->allRender();
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		/*
		하루를 추가합니다
		*/
		_timeTemp = GetTickCount();

		// 날짜 추가
		_gameTime.setMin(0);
		_gameTime.setHour(6);
		_gameTime.setDate(_gameTime.getDate() + 1);
		_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
		FARMMANAGER->growCrops();
		ANIMALMANAGER->nextDay();

		if (_gameTime.getDate() > 28)
		{
			//계절추가
			_gameTime.setDate(1);
			_gameTime.setSeason((SEASON)_gameTime.getSeason() + 1);

			if (_gameTime.getSeason() >= 5)
			{
				_gameTime.setSeason(SEASON_SPRING);
			}

			TILEMAPMANAGER->seasonImageSeting();
			TILEMAPMANAGER->allRender();
		}
	}

}

void gameTimeManager::nextDay()
{
	// 날짜 추가
	_gameTime.setMin(0);
	_gameTime.setHour(6);
	_gameTime.setDate(_gameTime.getDate() + 1);
	_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
	FARMMANAGER->growCrops();
	ANIMALMANAGER->nextDay();
	PLAYERMANAGER->setPlayerFull_Hp_Actingpower();

	if (_gameTime.getDate() > 28)
	{
		//계절추가
		_gameTime.setDate(1);
		_gameTime.setSeason((SEASON)_gameTime.getSeason() + 1);

		if (_gameTime.getSeason() >= 5)
		{
			_gameTime.setSeason(SEASON_SPRING);
		}

		TILEMAPMANAGER->seasonImageSeting();
		TILEMAPMANAGER->allRender();
	}
}

gameTimeValue gameTimeManager::getGameTime()
{
	gameTimeValue temp;

	temp.season = _gameTime.getSeason();
	temp.week = _gameTime.getWeek();
	temp.date = _gameTime.getDate();
	temp.hour = _gameTime.getHour();
	temp.min = _gameTime.getMin();

	return temp;
}
