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
	_name = "마니";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_MARNIE;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_ANIMALSHOP;

	_characterImg = IMAGEMANAGER->findImage("캐릭터_마니");
	_portraitImg = IMAGEMANAGER->findImage("캐릭터_초상화_마니");
	_feelingImg = IMAGEMANAGER->findImage("캐릭터_호감도_마니");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("마니_DownMove");

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
