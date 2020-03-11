#include "stdafx.h"
#include "loadGameScene.h"


loadGameScene::loadGameScene()
{
}


loadGameScene::~loadGameScene()
{
}

HRESULT loadGameScene::init()
{
	_sceneName = SCENE_NAME::SCENE_NAME_LOAD_SCENE;

	scene::init();

	_backImg = IMAGEMANAGER->findImage("�ε�ȭ��");

	_load1 = RectMake(190, 164, 653, 113);
	_load2 = RectMake(190, 288, 653, 113);
	_load3 = RectMake(190, 414, 653, 113);

	imageButtonAdd("cancel��ư", "", 900, 50, 26 * 3, 12 * 3, LOADGAMEBUTTON_CANCELBUTTON, true);
	
	initLoadData();
	num = -1;
	_isLoad = false;

	return S_OK;
}

void loadGameScene::update()
{
	scene::update();

	if (_isLoad)
	{
		if (_loadGame.loadgame(num))
		{
			UIMANAGER->changeUi("UI_general");
			SCENEMANAGER->changeScene("startScene");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < button.size(); i++)
		{
			if (PtInRect(&button[i]._rc, m_ptMouse))
			{
				if (button[i]._kind == LOADGAMEBUTTON_CANCELBUTTON)
				{
					SCENEMANAGER->changeScene("titleScene");
				}
			}
		}

		if (PtInRect(&_load1, m_ptMouse))
		{
			num = 1;
		}
		else if (PtInRect(&_load2, m_ptMouse))
		{
			num = 2;
		}
		else if (PtInRect(&_load3, m_ptMouse))
		{
			num = 3;
		}

	}
}

void loadGameScene::render()
{
	if (num == -1)
	{
		_backImg->render(getMemDC(), 0, 0);
	}
	else
	{
		IMAGEMANAGER->render("UI_�ε�ȭ��", getMemDC(), 0, 0);
		_isLoad = true;
		return;
	}
	scene::render();

	char strTemp[256];

	if (!_isLoad1)
	{
		sprintf(strTemp, "����� �����Ͱ� �����ϴ�", _load1_Name.c_str());
		TextOut(getMemDC(), _load1.left + 60, _load1.top + 25, strTemp, strlen(strTemp));//�̸�
	}
	else
	{
		if (_load1_Name.size() != 0)
		{
			sprintf(strTemp, "%s", _load1_Name.c_str());
			TextOut(getMemDC(), _load1.left + 60, _load1.top + 25, strTemp, strlen(strTemp));//�̸�
		}
		if (_load1_FarmName.size() != 0)
		{
			sprintf(strTemp, "%s ����", _load1_FarmName.c_str());
			TextOut(getMemDC(), _load1.left + 60, _load1.top + 70, strTemp, strlen(strTemp));//�����̸�
		}
		sprintf(strTemp, "%s", _load1_Date.c_str());
		TextOut(getMemDC(), _load1.left + 290, _load1.top + 70, strTemp, strlen(strTemp));//�ð�
	}

	if (!_isLoad2)
	{
		sprintf(strTemp, "����� �����Ͱ� �����ϴ�", _load2_Name.c_str());
		TextOut(getMemDC(), _load2.left + 60, _load2.top + 25, strTemp, strlen(strTemp));//�̸�
	}
	else
	{
		if (_load2_Name.size() != 0)
		{
			sprintf(strTemp, "%s", _load2_Name.c_str());
			TextOut(getMemDC(), _load2.left + 60, _load2.top + 25, strTemp, strlen(strTemp));//�̸�
		}
		if (_load2_FarmName.size() != 0)
		{
			sprintf(strTemp, "%s ����", _load2_FarmName.c_str());
			TextOut(getMemDC(), _load2.left + 60, _load2.top + 70, strTemp, strlen(strTemp));//�����̸�
		}
		sprintf(strTemp, "%s", _load2_Date.c_str());
		TextOut(getMemDC(), _load2.left + 290, _load2.top + 70, strTemp, strlen(strTemp));//�ð�
	}

	if (!_isLoad3)
	{
		sprintf(strTemp, "����� �����Ͱ� �����ϴ�", _load3_Name.c_str());
		TextOut(getMemDC(), _load3.left + 60, _load3.top + 25, strTemp, strlen(strTemp));//�̸�
	}
	else
	{
		if (_load3_FarmName.size() != 0)
		{
			sprintf(strTemp, "%s", _load3_Name.c_str());
			TextOut(getMemDC(), _load3.left + 60, _load3.top + 25, strTemp, strlen(strTemp));//�̸�
		}
		if (_load3_FarmName.size() != 0)
		{
			sprintf(strTemp, "%s ����", _load1_FarmName.c_str());
			TextOut(getMemDC(), _load3.left + 60, _load3.top + 70, strTemp, strlen(strTemp));//�����̸�
		}
		sprintf(strTemp, "%s", _load1_Date.c_str());
		TextOut(getMemDC(), _load3.left + 290, _load3.top + 70, strTemp, strlen(strTemp));//�ð�
	}
}

void loadGameScene::release()
{
	scene::release();
}

void loadGameScene::initLoadData()
{
	char dirTemp[256];
	char strTemp[1000];
	char middleTemp[512];

	int numTemp1, numTemp2;

	int num;
	string stringTemp;

	sprintf(dirTemp, "save/load1.ini");
	ifstream inFile(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);

	if (!strcmp(strTemp,"y") == 0)
	{
		_isLoad1 = false;
	}
	else
	{
		_isLoad1 = true;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "name : %s\r\n", &middleTemp);
		_load1_Name = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "farmName : %s\r\n", &middleTemp);
		_load1_FarmName = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "Date : %d, %d\r\n", &numTemp1, &numTemp2);

		if (numTemp1 == 1)
		{
			_load1_Date = "��";
		}
		else if (numTemp1 == 2)
		{
			_load1_Date = "����";
		}
		else if (numTemp1 == 3)
		{
			_load1_Date = "����";
		}
		else if (numTemp1 == 4)
		{
			_load1_Date = "�ܿ�";
		}
		_load1_Date = _load1_Date+(", " +to_string(numTemp2)+"��");
	}
	inFile.close();

	sprintf(dirTemp, "save/load2.ini");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);

	if (!strcmp(strTemp, "y") == 0)
	{
		_isLoad2 = false;
	}
	else
	{
		_isLoad2 = true;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "name : %s\r\n", &middleTemp);
		_load2_Name = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "farmName : %s\r\n", &middleTemp);
		_load2_FarmName = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "Date : %d, %d\r\n", &numTemp1, &numTemp2);

		if (numTemp1 == 1)
		{
			_load2_Date = "��";
		}
		else if (numTemp1 == 2)
		{
			_load2_Date = "����";
		}
		else if (numTemp1 == 3)
		{
			_load2_Date = "����";
		}
		else if (numTemp1 == 4)
		{
			_load2_Date = "�ܿ�";
		}
		_load2_Date = _load2_Date + (", " + to_string(numTemp2)+"��");
	}

	inFile.close();

	sprintf(dirTemp, "save/load3.ini");
	inFile.open(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);

	if (!strcmp(strTemp, "y") == 0)
	{
		_isLoad3 = false;
	}
	else
	{
		_isLoad3 = true;

		ZeroMemory(strTemp, sizeof(strTemp));
		sscanf_s(strTemp, "name : %s\r\n", &middleTemp);
		_load3_Name = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "farmName : %s\r\n", &middleTemp);
		_load3_FarmName = middleTemp;

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 1000);
		sscanf_s(strTemp, "Date : %d, %d\r\n", &numTemp1, &numTemp2);

		if (numTemp1 == 1)
		{
			_load3_Date = "��";
		}
		else if (numTemp1 == 2)
		{
			_load3_Date = "����";
		}
		else if (numTemp1 == 3)
		{
			_load3_Date = "����";
		}
		else if (numTemp1 == 4)
		{
			_load3_Date = "�ܿ�";
		}
		_load3_Date = _load3_Date + (", " + to_string(numTemp2) + "��");
	}

	inFile.close();
}
