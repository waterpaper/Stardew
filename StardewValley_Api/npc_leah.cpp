#include "stdafx.h"
#include "npc_leah.h"


npc_leah::npc_leah()
{
}


npc_leah::~npc_leah()
{
}

HRESULT npc_leah::init()
{
	npc::init();

	_position = POINT{ 1800,1632 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "레아";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_LEAH;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN;

	_characterImg = IMAGEMANAGER->findImage("캐릭터_레아");
	_portraitImg = IMAGEMANAGER->findImage("캐릭터_초상화_레아");
	_feelingImg = IMAGEMANAGER->findImage("캐릭터_호감도_레아");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("레아_DownMove");

	addString();

	return S_OK;
}

void npc_leah::update()
{
	npc::update();
}

void npc_leah::render(HDC hdc, int sceneName)
{
	npc::render(hdc, sceneName);
}

void npc_leah::release()
{

}

void npc_leah::addString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	string stringTmep;

	sprintf(dirTemp, "string/character/leah.txt");
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
