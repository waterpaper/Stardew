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
			//�ð� �߰�

			_gameTime.setHour(_gameTime.getHour() + 1);
			_gameTime.setMin(0);


			if (_gameTime.getHour() > 23)
			{
				// ��¥ �߰�
				_gameTime.setHour(0);
				_gameTime.setDate(_gameTime.getDate() + 1);
				_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
	

				if (_gameTime.getDate() > 27)
				{
					//�����߰�
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
	�ð��� �Ѿ�� ���� Ű�Է��� ó���ϴ� �κ��Դϴ�
	*/

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		/*
		1�ð��� �߰��մϴ�
		*/
		_timeTemp = GetTickCount();
		_gameTime.setHour(_gameTime.getHour() + 1);
		_gameTime.setMin(0);

		if (_gameTime.getHour() > 23)
		{
			// ��¥ �߰�
			_gameTime.setHour(0);
			_gameTime.setDate(_gameTime.getDate() + 1);
			_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
			FARMMANAGER->growCrops();
			ANIMALMANAGER->nextDay();

			if (_gameTime.getDate() > 28)
			{
				//�����߰�
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
		�Ϸ縦 �߰��մϴ�
		*/
		_timeTemp = GetTickCount();

		// ��¥ �߰�
		_gameTime.setMin(0);
		_gameTime.setHour(6);
		_gameTime.setDate(_gameTime.getDate() + 1);
		_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
		FARMMANAGER->growCrops();
		ANIMALMANAGER->nextDay();

		if (_gameTime.getDate() > 28)
		{
			//�����߰�
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
	// ��¥ �߰�
	_gameTime.setMin(0);
	_gameTime.setHour(6);
	_gameTime.setDate(_gameTime.getDate() + 1);
	_gameTime.setWeek((WEEK)(_gameTime.getWeek() % 7) + 1);
	FARMMANAGER->growCrops();
	ANIMALMANAGER->nextDay();
	PLAYERMANAGER->setPlayerFull_Hp_Actingpower();

	if (_gameTime.getDate() > 28)
	{
		//�����߰�
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
