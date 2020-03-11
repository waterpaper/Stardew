#pragma once
#include "singletonBase.h"
#pragma warning(disable : 4996)

class inputManager:public singletonBase<inputManager>
{
private:
	char cTemp[256];
	string _word;

	bool _isKeyboardStart;

public:
	inputManager();
	~inputManager();

	HRESULT init();
	void release();
	void update();

	string getKeyBoard() { return _word; };
	void addKeyBoard(int nKey) {
		if (nKey == VK_BACK) //�ƽ�Ű�� ���� Back spaceŰ�� ����Ű ���� �̿��Ͽ� ó��
		{
			if (_word.size() <= 0) return;

			_word.erase(_word.size() - 1);
		}
		else
		{
			sprintf(cTemp, "%c", nKey);  //���ڸ� �Է��ϸ� ���ڿ����߰� stdio.h �߰��ؾ���

			string sTemp(cTemp);

			_word += sTemp;
		}
	};

	void startKeyBoard() { _isKeyboardStart = true; };
	void stopKeyBoard() {
		_isKeyboardStart = false;
		_word.clear();
	};

	bool getIskeyBoardStart() { return _isKeyboardStart; };
};

