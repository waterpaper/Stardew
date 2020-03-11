#pragma once
#include"gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;	//�� ��Ʈ
	int _x, _y;			//��ǥ
	int _width;			//�� ���α���(�̰ɷ� ������)

	image* _progressBarFront;	//�� �� �̹���
	image* _progressBarBack;	//�� �� �̹���

public:
	progressBar();
	~progressBar();

	//�� �ʱ�ȭ(���̹���, ���̹���, x, y, ���α���, ���α���)
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	int getWidth() { return _width; };

	//���α׷����� ������ ����
	void setGauge(float currentGauge, float maxGauge);

	//���α׷����� ��ġ
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	//ü�¹� ��Ʈ
	RECT getRect() { return _rcProgress; }
};

