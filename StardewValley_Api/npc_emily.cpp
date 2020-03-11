#include "stdafx.h"
#include "npc_emily.h"


npc_emily::npc_emily()
{
}


npc_emily::~npc_emily()
{
}

HRESULT npc_emily::init()
{
	npc::init();

	_position = POINT{ 984,1536 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "에밀리";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_EMILY;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN;

	_characterImg = IMAGEMANAGER->findImage("캐릭터_에밀리");
	_portraitImg = IMAGEMANAGER->findImage("캐릭터_초상화_에밀리");
	_feelingImg = IMAGEMANAGER->findImage("캐릭터_호감도_에밀리");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("에밀리_DownMove");

	addString();

	return S_OK;
}

void npc_emily::update()
{
	npc::update();
}


void npc_emily::render(HDC hdc, int sceneName)
{
	npc::render(hdc, sceneName);
}

void npc_emily::release()
{

}

void npc_emily::addString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	string stringTmep;

	sprintf(dirTemp, "string/character/emily.txt");
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
