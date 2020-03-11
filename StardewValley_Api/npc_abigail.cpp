#include "stdafx.h"
#include "npc_abigail.h"


npc_abigail::npc_abigail()
{
}


npc_abigail::~npc_abigail()
{
}

HRESULT npc_abigail::init()
{
	npc::init();

	_position = POINT{ 1464,1200 };
	//_position = POINT{ 43*48,27*48 };
	_rc = RectMakeCenter(_position.x, _position.y, 48, 96);
	_collisionRc = RectMakeCenter(_position.x, _position.y + 24, 48, 48);
	_name = "�������";
	_direction = NPC_DIRECTION_DOWN;
	_action = NPC_ACTION_IDLE;
	_feeling = 0;
	_kind = NPC_KIND_EMILY;
	_locationScene = INGAMESCENE_NAME::INGAMESCENE_NAME_TOWN;

	_characterImg = IMAGEMANAGER->findImage("ĳ����_�������");
	_portraitImg = IMAGEMANAGER->findImage("ĳ����_�ʻ�ȭ_�������");
	_feelingImg = IMAGEMANAGER->findImage("ĳ����_ȣ����_�������");

	_aniCharacterImg = ANIMATIONMANAGER->findAnimation("�������_DownMove");

	addString();

	return S_OK;
}

void npc_abigail::update()
{
	npc::update();
}

void npc_abigail::render(HDC hdc, int sceneName)
{
	npc::render(hdc, sceneName);
}

void npc_abigail::release()
{

}

void npc_abigail::addString()
{
	char dirTemp[256];
	char strTemp[1000];
	int num;
	string stringTmep;

	sprintf(dirTemp, "string/character/abigail.txt");
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
