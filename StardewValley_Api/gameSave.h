#pragma once
class gameSave
{
private:
	HANDLE file;																				//���̺긦 ���� ����
	DWORD write;

public:
	gameSave();
	~gameSave();
	
	void nowGameSave(int num);
};

