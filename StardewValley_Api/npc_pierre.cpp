#include "stdafx.h"
#include "npc_pierre.h"


npc_pierre::npc_pierre()
{
}


npc_pierre::~npc_pierre()
{
}

HRESULT npc_pierre::init()
{
	npc::init();

	_position = POINT{ 336,336 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "�ǿ���";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_PIERRE;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_SHOP;

	_characterImg = IMAGEMANAGER->findImage("ĳ����_�ǿ���");
	_portraitImg = IMAGEMANAGER->findImage("ĳ����_�ʻ�ȭ_�ǿ���");
	_feelingImg = IMAGEMANAGER->findImage("ĳ����_ȣ����_�ǿ���");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("�ǿ���_DownMove");

	addString();

	return S_OK;
}

void npc_pierre::update()
{
	npc::update();
}

void npc_pierre::render(HDC hdc, int sceneName)
{
	npc::render(hdc, sceneName);
}

void npc_pierre::release()
{
}

void npc_pierre::addString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	string stringTmep;

	sprintf(dirTemp, "string/character/pierre.txt");
	ifstream inFile(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);
	sscanf_s(strTemp, "num : %d\r\n", &num);

	for (int i = 0; i < num; i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		stringTmep = strTemp;

		_vConversation.push_back(stringTmep);
	}

	inFile.close();
}
