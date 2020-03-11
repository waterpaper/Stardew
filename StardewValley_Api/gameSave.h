#pragma once
class gameSave
{
private:
	HANDLE file;																				//세이브를 위한 변수
	DWORD write;

public:
	gameSave();
	~gameSave();
	
	void nowGameSave(int num);
};

