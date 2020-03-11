#pragma once

class maptool_function
{
public:
	maptool_function();
	~maptool_function();
	
	void maptool_sizechange(int x, int y) { TILEMAPMANAGER->setTileMapSize(POINT{ x,y }); };
	void maptool_minimaprender(HDC hdc, int x, int y) { TILEMAPMANAGER->minimapRender(hdc, 300, 300, x, y); };
	void maptool_init() { TILEMAPMANAGER->init(); };
};

