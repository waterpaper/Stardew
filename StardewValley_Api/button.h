#pragma once

struct imageButton
{
	image *_img;
	RECT _rc;
	string _text;
	int _kind;

	bool _isFrame;
	bool _ischeck;

	int _currentX;
};