#include "stdafx.h"
#include "npcManager.h"


npcManager::npcManager()
{
}


npcManager::~npcManager()
{
	release();
}

HRESULT npcManager::init()
{
	release();

	aniAdd();

	npc *npcTemp;
	npcTemp = new npc_abigail();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_emily();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_leah();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_marnie();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_pierre();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;


	return S_OK;
}

void npcManager::update()
{
	if (INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN == SCENEMANAGER->getIngameName())
	{
		for (int i = 0; i < vNpc.size(); i++)
		{
			if (vNpc[i]->getIngameScene() == INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN)
			{
				vNpc[i]->update();
			}
		}
	}
}

void npcManager::render(HDC hdc)
{
	int temp = SCENEMANAGER->getIngameName();
	for (int i = 0; i < vNpc.size(); i++)
	{
		vNpc[i]->render(hdc, temp);

	}
}

void npcManager::reRender(HDC hdc, RECT rect)
{
	RECT rcTemp;
	INGAMESCENE_NAME ingameName = (INGAMESCENE_NAME)SCENEMANAGER->getIngameName();

	for (int i = 0; i < vNpc.size(); i++)
	{
		if (vNpc[i]->getIngameScene() != ingameName)	continue;

		if (IntersectRect(&rcTemp, &rect, &vNpc[i]->getRc()))
		{
			vNpc[i]->render(hdc, ingameName);
			return;
		}
	}
}

void npcManager::release()
{
	if (vNpc.size() != 0)
	{
		/*
		�޸𸮸��� �ذ��ϱ� ���� ��Ҹ��� delete
		�� ���� capacity�� �ʱ�ȭ�Ѵ�
		*/
		for (int i = 0; i < vNpc.size(); i++)
		{

			SAFE_DELETE(vNpc[i]);

		}
		vNpc.clear();
		vNpc.shrink_to_fit();
	}
}

void npcManager::npcClear()
{
	release();

	npc *npcTemp;
	npcTemp = new npc_abigail();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_emily();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_leah();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_marnie();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;

	npcTemp = new npc_pierre();
	npcTemp->init();
	vNpc.push_back(npcTemp);
	npcTemp = nullptr;
}

void npcManager::aniAdd()
{
	ANIMATIONMANAGER->addAnimation("�������_DownMove", "ĳ����_�������", 0 * 4, 0 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("���и�_DownMove", "ĳ����_���и�", 0 * 4, 0 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_DownMove", "ĳ����_����", 0 * 4, 0 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�ǿ���_DownMove", "ĳ����_�ǿ���", 0 * 4, 0 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_DownMove", "ĳ����_����", 0 * 4, 0 * 4 + 3, 8, false, true);

	ANIMATIONMANAGER->addAnimation("�������_RightMove", "ĳ����_�������", 1 * 4, 1 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("���и�_RightMove", "ĳ����_���и�", 1 * 4, 1 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_RightMove", "ĳ����_����", 1 * 4, 1 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�ǿ���_RightMove", "ĳ����_�ǿ���", 1 * 4, 1 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_RightMove", "ĳ����_����", 1 * 4, 1 * 4 + 3, 8, false, true);

	ANIMATIONMANAGER->addAnimation("�������_UpMove", "ĳ����_�������", 2 * 4, 2 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("���и�_UpMove", "ĳ����_���и�", 2 * 4, 2 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_UpMove", "ĳ����_����", 2 * 4, 2 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�ǿ���_UpMove", "ĳ����_�ǿ���", 2 * 4, 2 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_UpMove", "ĳ����_����", 2 * 4, 2 * 4 + 3, 8, false, true);

	ANIMATIONMANAGER->addAnimation("�������_LeftMove", "ĳ����_�������", 3 * 4, 3 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("���и�_LeftMove", "ĳ����_���и�", 3 * 4, 3 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_LeftMove", "ĳ����_����", 3 * 4, 3 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("�ǿ���_LeftMove", "ĳ����_�ǿ���", 3 * 4, 3 * 4 + 3, 8, false, true);
	ANIMATIONMANAGER->addAnimation("����_LeftMove", "ĳ����_����", 3 * 4, 3 * 4 + 3, 8, false, true);
}

void npcManager::playerConversation(POINT point)
{
	double rectPointTempX, rectPointTempY;
	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	RECT rcTemp;

	for (int i = 0; i < vNpc.size(); i++)
	{
		rcTemp = vNpc[i]->getRc();
		if (PtInRect(&rcTemp, POINT{ m_ptMouse.x + cameraTemp.x,m_ptMouse.y + cameraTemp.y }))
		{
			rectPointTempX = rcTemp.left + (rcTemp.right - rcTemp.left) / 2;
			rectPointTempY = rcTemp.top + (rcTemp.bottom - rcTemp.top) / 2;

			if (getDistance(point.x, point.y, rectPointTempX, rectPointTempY) < 100.0)
			{
				nowNpcKind = (NPC_KIND)i;
				isPresent = false;
				UIMANAGER->setIsConversation(true);
				UIMANAGER->changeUi("UI_conversation");
				break;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}
}

bool npcManager::playerPresent(POINT point)
{
	double rectPointTempX, rectPointTempY;
	POINT cameraTemp = CAMERAMANAGER->getCameraPos();
	RECT rcTemp;

	for (int i = 0; i < vNpc.size(); i++)
	{
		rcTemp = vNpc[i]->getRc();
		if (PtInRect(&rcTemp, POINT{ m_ptMouse.x + cameraTemp.x,m_ptMouse.y + cameraTemp.y }))
		{
			rectPointTempX = rcTemp.left + (rcTemp.right - rcTemp.left) / 2;
			rectPointTempY = rcTemp.top + (rcTemp.bottom - rcTemp.top) / 2;

			if (getDistance(point.x, point.y, rectPointTempX, rectPointTempY) < 100.0)
			{
				nowNpcKind = (NPC_KIND)i;
				isPresent = true;
				UIMANAGER->setIsConversation(true);
				INVENTORYMANAGER->deleteItem(UIMANAGER->getKindNum(), 0);

				UIMANAGER->changeUi("UI_conversation");
				vNpc[i]->setFeeling(vNpc[i]->getFeeling() + 10);
				return true;
			}
			else
			{
				continue;
			}
		}
		else
		{
			continue;
		}
	}

	return false;
}

bool npcManager::getRectCollision(RECT rc, INGAMESCENE_NAME ingameName)
{
	RECT rcTemp;
	for (int i = 0; i < vNpc.size(); i++)
	{
		if (vNpc[i]->getIngameScene() != ingameName)	continue;

		if (IntersectRect(&rcTemp, &rc, &vNpc[i]->getCollisionRc()))
		{
			return true;
		}
	}
	return false;
}

bool npcManager::getvNpcCollision(RECT rc)
{
	RECT rcTemp;
	INGAMESCENE_NAME ingameName=(INGAMESCENE_NAME)SCENEMANAGER->getIngameName();
	int num = 0;

	for (int i = 0; i < vNpc.size(); i++)
	{
		if (vNpc[i]->getIngameScene() != ingameName)	continue;

		if (IntersectRect(&rcTemp, &rc, &vNpc[i]->getCollisionRc()))
		{
			num++;
			if (num > 1)
			{
				return true;
			}
		}
	}
	return false;
}

bool npcManager::playerCollision(RECT rc)
{
	RECT playerCollisionRectTemp = PLAYERMANAGER->getPlayerState().getPlayerCollisionRc();
	RECT rcTemp;

	if (IntersectRect(&rcTemp, &rc, &playerCollisionRectTemp))
	{
		return true;
	}

	return false;
}

bool npcManager::objectCollision(RECT rc)
{
	POINT leftTop, leftBottom, rightTop, rightBottom;
	POINT mapSize = TILEMAPMANAGER->getTileMapSize();
	tileMap tileMapTemp = TILEMAPMANAGER->getTileMap();
	TILE_TERRAINKIND tileKind;

	leftTop.x = (rc.left + 1) / (TILE_SIZE_X), leftTop.y = (rc.top + 1) / (TILE_SIZE_Y);
	leftBottom.x = (rc.left + 1) / (TILE_SIZE_X), leftBottom.y = (rc.bottom - 1) / (TILE_SIZE_Y);
	rightTop.x = (rc.right - 1) / (TILE_SIZE_X), rightTop.y = (rc.top + 1) / (TILE_SIZE_Y);
	rightBottom.x = (rc.right - 1) / (TILE_SIZE_X), rightBottom.y = (rc.bottom - 1) / (TILE_SIZE_Y);


	//���� �ʿ��� ������� ���θ� �Ǵ��Ѵ�
	if (rc.left<0 || rc.right> mapSize.x*(TILE_SIZE_X)
		|| rc.top<0 || rc.bottom>mapSize.y*(TILE_SIZE_Y))				return false;

	//�̵��� 4���� ���� �����Ѵ�.
	//�»�
	tileKind = tileMapTemp.getKindTerrian(leftTop.x, leftTop.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		return false;
	}
	//����
	tileKind = tileMapTemp.getKindTerrian(leftBottom.x, leftBottom.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		return false;
	}//���
	tileKind = tileMapTemp.getKindTerrian(rightTop.x, rightTop.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		return false;
	}//����
	tileKind = tileMapTemp.getKindTerrian(rightBottom.x, rightBottom.y);

	if (!tileMapTemp.getIsTerrain(leftTop.x, leftTop.y) || tileMapTemp.getIsObject(leftTop.x, leftTop.y)
		|| tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_NOTMOVE || tileKind == TILE_TERRAINKIND::TILE_TERRAINKIND_WALL)
	{
		return false;
	}

	return true;
}
