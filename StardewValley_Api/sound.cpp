#include"stdafx.h"
#include "sound.h"

sound::sound()
{
}


sound::~sound()
{
}

void sound::init()
{
	//FMOD사용 초기화
	FMOD_System_Create(&g_pSystem);
	FMOD_System_Init(g_pSystem, TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	FMOD_System_Create(&effg_pSystem);
	FMOD_System_Init(effg_pSystem, TOTALEFFSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드 채널 할당
	g_pSound = new FMOD_SOUND *[TOTALSOUNDBUFFER];
	g_pChannel = new FMOD_CHANNEL *[TOTALSOUNDBUFFER];
	effg_pSound = new FMOD_SOUND *[TOTALEFFSOUNDBUFFER];
	effg_pChannel = new FMOD_CHANNEL *[TOTALEFFSOUNDBUFFER];

	memset(g_pSound, 0, sizeof(FMOD_SOUND*)*(TOTALSOUNDBUFFER));
	memset(g_pChannel, 0, sizeof(FMOD_CHANNEL*)*(TOTALSOUNDBUFFER));
	memset(effg_pSound, 0, sizeof(FMOD_SOUND*)*(TOTALEFFSOUNDBUFFER));
	memset(effg_pChannel, 0, sizeof(FMOD_CHANNEL*)*(TOTALEFFSOUNDBUFFER));

	//볼륨 초기화
	_bgmVolume = 0.5f;
	_effVolume = 1.0f;

	addSound();
}

void sound::update()
{
	FMOD_System_Update(g_pSystem);
	FMOD_System_Update(effg_pSystem);
}

void sound::release()
{
	soundOff();
	FMOD_Sound_Release(*g_pSound);
	FMOD_Channel_Stop(*g_pChannel);
	FMOD_System_Release(g_pSystem);
	FMOD_System_Close(g_pSystem);

	effSoundOff();
	FMOD_Sound_Release(*effg_pSound);
	FMOD_Channel_Stop(*effg_pChannel);
	FMOD_System_Release(effg_pSystem);
	FMOD_System_Close(effg_pSystem);

	/*
	fmod에서 3d쓰고 싶으면
	3d음향 거리값 설정 가능
	set3DminMaxDistance
	*/
}

void sound::addBgmSound(string keyName, string soundName, bool loop = FALSE)
{
	if (loop)
	{
		FMOD_System_CreateStream(g_pSystem, soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &g_pSound[m_totalBgmSounds.size()]);
	}
	else
	{
		FMOD_System_CreateStream(g_pSystem, soundName.c_str(), FMOD_DEFAULT, nullptr, &g_pSound[m_totalBgmSounds.size()]);
	}

	m_totalBgmSounds.insert(make_pair(keyName, &g_pSound[m_totalBgmSounds.size()]));
}

void sound::soundPlay(string keyName)
{
	if (!_isSound) return;

	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	//채널에서 플레이 해야하니 카운트 돌리자.
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//배경음 재생
			FMOD_System_PlaySound(g_pSystem, *iter->second, 0, 0, &g_pChannel[count]);
			FMOD_Channel_SetVolume(g_pChannel[count], _bgmVolume);
		}
	}
	//m_totalBgmSounds.insert(make_pair(keyName, &g_pSound[m_totalBgmSounds.size()]));
}

void sound::soundOff()
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		FMOD_Channel_Stop(g_pChannel[count]);
	}
}

void sound::soundOff(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();
	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_Stop(g_pChannel[count]);
		}
	}
}

void sound::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(g_pChannel[count], true);
		}
	}
}

void sound::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(g_pChannel[count], false);
		}
	}
}

bool sound::isPlaySound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPlay;
	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_IsPlaying(g_pChannel[count], &isPlay);
		}
	}

	return isPlay;
}

bool sound::isPauseSound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPause;

	arrSoundIter iter = m_totalBgmSounds.begin();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_GetPaused(g_pChannel[count], &isPause);
		}
	}

	return isPause;
}

void sound::addEffSound(string keyName, string soundName, bool loop)
{
	if (loop)
	{
		FMOD_System_CreateStream(effg_pSystem, soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &effg_pSound[m_totalEffSounds.size()]);
	}
	else
	{
		FMOD_System_CreateStream(effg_pSystem, soundName.c_str(), FMOD_DEFAULT, nullptr, &effg_pSound[m_totalEffSounds.size()]);
	}

	m_totalEffSounds.insert(make_pair(keyName, &effg_pSound[m_totalEffSounds.size()]));
}

void sound::effSoundOff()
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		FMOD_Channel_Stop(effg_pChannel[count]);
	}
}

void sound::effSoundOff(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_Stop(effg_pChannel[count]);
		}
	}
}

void sound::effSoundPlay(string keyName)
{
	if (!_isSound) return;

	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();
	//채널에서 플레이 해야하니 카운트 돌리자.
	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//배경음 재생
			FMOD_System_PlaySound(effg_pSystem, *iter->second, 0, 0, &effg_pChannel[count]);
			FMOD_Channel_SetVolume(effg_pChannel[count], _effVolume);
			return;
		}
	}
}

void sound::effPause(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(effg_pChannel[count], true);
		}
	}
}

void sound::effResume(string keyName)
{
	int count = 0;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_SetPaused(effg_pChannel[count], false);
		}
	}
}

bool sound::effIsPlaySound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPlay = false;
	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_IsPlaying(effg_pChannel[count], &isPlay);
		}
	}

	return isPlay;
}

bool sound::effIsPauseSound(string keyName)
{
	int count = 0;
	FMOD_BOOL isPause;

	arrSoundIter iter = m_totalEffSounds.begin();

	for (iter; iter != m_totalEffSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			FMOD_Channel_GetPaused(effg_pChannel[count], &isPause);
		}
	}

	return isPause;
}

void sound::addSound()
{
	addBgmSound("시작화면", "sound/opening.mp3", true);
	addBgmSound("맵툴", "sound/maptool.mp3", true);
	addBgmSound("농장", "sound/farm.mp3", true);
	addBgmSound("마을", "sound/town.mp3", true);

	addEffSound("나무깨기", "sound/breakTree.mp3", false);
	addEffSound("나무쓰러짐", "sound/removeTree.mp3", false);
	addEffSound("낫질", "sound/scythe.mp3", false);
	addEffSound("돌걷기", "sound/move_rock.mp3", false);
	addEffSound("돌캐기", "sound/removeRock.mp3", false);
	addEffSound("물주기", "sound/watering.mp3", false);
	addEffSound("아이템습득", "sound/getItem.mp3", false);
	addEffSound("풀걷기", "sound/move_grass.mp3", false);
	addEffSound("풀베기", "sound/removeGrass.mp3", false);
	addEffSound("허공찍기", "sound/smash.mp3", false);
	addEffSound("흙걷기", "sound/move_soil.mp3", false);
	addEffSound("메뉴오픈", "sound/menuopen.mp3", false);
	addEffSound("메뉴닫기", "sound/menuclose.mp3", false);
	addEffSound("캐릭터대화", "sound/character.mp3", false);
	addEffSound("메뉴선택", "sound/menu_select.mp3", false);
	addEffSound("호미질", "sound/hoe.mp3", false);

	addEffSound("닭", "sound/chicken.mp3", false);
	addEffSound("오리", "sound/duck.mp3", false);
	addEffSound("토끼", "sound/rabbit.mp3", false);
	addEffSound("소", "sound/cow.mp3", false);
	addEffSound("젖소", "sound/goat.mp3", false);
	addEffSound("양", "sound/sheep.mp3", false);
	addEffSound("돼지", "sound/pig.mp3", false);
}

void sound::setBgmVolume(float bgmVolume)
{
	int count = 0;
	arrSoundIter iter = m_totalBgmSounds.begin();

	_bgmVolume = bgmVolume;
	update();

	for (iter; iter != m_totalBgmSounds.end(); ++iter, count++)
	{
		FMOD_Channel_SetVolume(g_pChannel[count], _bgmVolume);
	}
}

