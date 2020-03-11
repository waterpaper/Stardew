#include "stdafx.h"
#include "npc_marnie.h"


npc_marnie::npc_marnie()
{
}


npc_marnie::~npc_marnie()
{
}

HRESULT npc_marnie::init()
{
	npc::init();

	_position = POINT{ 696,336 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "����";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_MARNIE;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_ANIMALSHOP;

	_characterImg = IMAGEMANAGER->findImage("ĳ����_����");
	_portraitImg = IMAGEMANAGER->findImage("ĳ����_�ʻ�ȭ_����");
	_feelingImg = IMAGEMANAGER->findImage("ĳ����_ȣ����_����");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("����_DownMove");

	addString();

	return S_OK;
}

void npc_marnie::update()
{
	npc::update();
}

void npc_marnie::render(HDC hdc, int sceneName)
{
	npc::render(hdc, sceneName);
}

void npc_marnie::release()
{
}

void npc_marnie::addString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	string stringTmep;

	sprintf(dirTemp, "string/character/marnie.txt");
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
