#include "stdafx.h"
#include "effectManager.h"
#include"effect.h"

effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	m_vTotalEffect.clear();
	addEffect("이펙트_호미질", "이펙트_호미질", 384, 48, 384 / 8, 48, 7, 0.05f, 30);
	addEffect("이펙트_수확", "이펙트_수확", 288, 96, 288 / 6, 96, 5, 0.05f, 30);
	addEffect("이펙트_돌제거", "이펙트_돌제거", 384, 48, 384 / 8, 48, 5, 0.05f, 30);
	addEffect("이펙트_풀제거", "이펙트_풀제거", 336, 48, 336 / 7, 48, 5, 0.05f, 30);
	addEffect("이펙트_물", "이펙트_물", 480, 48, 480 / 10, 48, 5, 0.05f, 30);
	addEffect("이펙트_나무제거", "이펙트_나무제거", 2800, 160, 2800 / 10, 160, 3, 0.05f, 30);
	addEffect("이펙트_나무1쓰러짐", "오브젝트_나무1_벌목", 2592, 2160, 2592 / 9, 2160 / 5, 8, 0.05f, 30);


	_isTree = false;
	_treeX = 0;
	_treeY = 0;
	return S_OK;
}

void effectManager::release()
{
	viTotalEffect vIter;		//모든 이펙트 관리할 벡터
	miEffect mIter;				//이펙트클래스 담겨있는 녀석

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//이펙트가 담겨 있는 맵
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//이펙트 클래스를 담은 벡터
				viEffect vArriter;

				for (vArriter = mIter->second.begin(); vArriter != mIter->second.end();)
				{
					//이펙트 클래스 릴리즈
					(*vArriter)->release();
					SAFE_DELETE(*vArriter);
					vArriter = mIter->second.erase(vArriter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void effectManager::update()
{
	viTotalEffect vIter;
	miEffect mIter;

	if (_isTree)
	{
		if (!getIsRunning("이펙트_나무1쓰러짐"))
		{
			play("이펙트_나무제거", _treeX + 72, _treeY + 50);
			for (int i=0;i<10;i++)
			{
				int randX = RND->getInt(280);
				int randY = RND->getFromIntTo(80,100);
				ITEMMANAGER->materialWoodDrop(_treeX+ randX, _treeY+ randY, true);
			}
			_isTree = false;
		}
	}

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}

}

void effectManager::render(HDC hdc)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;

			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render(hdc);
			}
		}
	}
}

void effectManager::addEffect(string effectKey, char * imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{

	image* img;
	vEffect vEffectBuffer; //이펙트 버퍼
	mEffect mArrEffect;		//맵으로 만든 이펙트

	//이미지가 이미지매니저에 등록이 되어 있다면
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(effectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//버퍼 크기만큼 이펙트를 할당후 초기화 해서 벡터로 만든다.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//벡터 담긴 이펙트 버퍼를 맵에 넣는다.
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));
	//맵에 담긴 벡터를 토탈벡터에 담자.
	m_vTotalEffect.push_back(mArrEffect);


}

void effectManager::play(string effectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	if (effectKey.compare("이펙트_나무1쓰러짐") == 0)
	{
		_isTree = true;
		_treeX = x, _treeY = y;
	}

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{

			//이펙트 키값과 비교해서 같지 않다면 다음 맵으로 넘기자.
			if (!(mIter->first == effectKey))break;



			//이펙트 키값과 일치하면 이펙트를 플레이 하자.
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning())continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}

bool effectManager::getIsRunning(string effectKey)
{
	viTotalEffect vIter;
	miEffect mIter;
	viEffect vArrIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{

			//이펙트 키값과 비교해서 같지 않다면 다음 맵으로 넘기자.
			if (!(mIter->first == effectKey))break;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) return true;
				else return false;

			}
		}
	}

	return false;
}
