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
	addEffect("����Ʈ_ȣ����", "����Ʈ_ȣ����", 384, 48, 384 / 8, 48, 7, 0.05f, 30);
	addEffect("����Ʈ_��Ȯ", "����Ʈ_��Ȯ", 288, 96, 288 / 6, 96, 5, 0.05f, 30);
	addEffect("����Ʈ_������", "����Ʈ_������", 384, 48, 384 / 8, 48, 5, 0.05f, 30);
	addEffect("����Ʈ_Ǯ����", "����Ʈ_Ǯ����", 336, 48, 336 / 7, 48, 5, 0.05f, 30);
	addEffect("����Ʈ_��", "����Ʈ_��", 480, 48, 480 / 10, 48, 5, 0.05f, 30);
	addEffect("����Ʈ_��������", "����Ʈ_��������", 2800, 160, 2800 / 10, 160, 3, 0.05f, 30);
	addEffect("����Ʈ_����1������", "������Ʈ_����1_����", 2592, 2160, 2592 / 9, 2160 / 5, 8, 0.05f, 30);


	_isTree = false;
	_treeX = 0;
	_treeY = 0;
	return S_OK;
}

void effectManager::release()
{
	viTotalEffect vIter;		//��� ����Ʈ ������ ����
	miEffect mIter;				//����ƮŬ���� ����ִ� �༮

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//����Ʈ�� ��� �ִ� ��
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//����Ʈ Ŭ������ ���� ����
				viEffect vArriter;

				for (vArriter = mIter->second.begin(); vArriter != mIter->second.end();)
				{
					//����Ʈ Ŭ���� ������
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
		if (!getIsRunning("����Ʈ_����1������"))
		{
			play("����Ʈ_��������", _treeX + 72, _treeY + 50);
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
	vEffect vEffectBuffer; //����Ʈ ����
	mEffect mArrEffect;		//������ ���� ����Ʈ

	//�̹����� �̹����Ŵ����� ����� �Ǿ� �ִٸ�
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addImage(effectKey, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//���� ũ�⸸ŭ ����Ʈ�� �Ҵ��� �ʱ�ȭ �ؼ� ���ͷ� �����.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//���� ��� ����Ʈ ���۸� �ʿ� �ִ´�.
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));
	//�ʿ� ��� ���͸� ��Ż���Ϳ� ����.
	m_vTotalEffect.push_back(mArrEffect);


}

void effectManager::play(string effectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	if (effectKey.compare("����Ʈ_����1������") == 0)
	{
		_isTree = true;
		_treeX = x, _treeY = y;
	}

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{

			//����Ʈ Ű���� ���ؼ� ���� �ʴٸ� ���� ������ �ѱ���.
			if (!(mIter->first == effectKey))break;



			//����Ʈ Ű���� ��ġ�ϸ� ����Ʈ�� �÷��� ����.
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

			//����Ʈ Ű���� ���ؼ� ���� �ʴٸ� ���� ������ �ѱ���.
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
