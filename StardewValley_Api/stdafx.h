// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.

#include <fstream>

//STL
#include<string>
#include<map>
#include<vector>

//====================================
//	## 내가 만든 헤더파일## 
//====================================
#include "drawShapesFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "TimeManager.h"
#include "sound.h"
#include "animationmanager.h"
#include "effectManager.h"
#include "playerManager.h"
#include "sceneManager.h"
#include "inputManager.h"
#include "tileMapManager.h"
#include "cameraManger.h"
#include "uiManager.h"
#include "inventoryManager.h"
#include "itemManager.h"
#include "subWIndow.h"
#include "gameTimeManager.h"
#include "npcManager.h"
#include "farmManager.h"
#include "animalManager.h"
#include "item.h"
#include "UTIL.h"

using namespace std;
using namespace UTIL;

//====================================
//	## 싱글톤 추가 ## 
//====================================
#define RND						randomFunction::getSingleton()
#define KEYMANAGER				keyManager::getSingleton()
#define IMAGEMANAGER			imageManager::getSingleton()
#define TIMEMANAGER				timeManager::getSingleton()
#define ANIMATIONMANAGER		animationManager::getSingleton()
#define EFFECTMANAGER			effectManager::getSingleton()
#define PLAYERMANAGER			playerManager::getSingleton()
#define SCENEMANAGER			sceneManager::getSingleton()
#define INPUTMANAGER			inputManager::getSingleton()
#define TILEMAPMANAGER			tileMapManager::getSingleton()
#define CAMERAMANAGER			cameraManger::getSingleton()
#define UIMANAGER				uiManager::getSingleton()
#define INVENTORYMANAGER		inventoryManager::getSingleton()
#define GAMETIMEMANAGER			gameTimeManager::getSingleton()
#define ITEMMANAGER				itemManager::getSingleton()
#define NPCMANAGER				npcManager::getSingleton()
#define FARMMANAGER				farmManager::getSingleton()
#define ANIMALMANAGER			animalManager::getSingleton()
#define SUBWIN					subWindow::getSingleton()

//====================================
//	## 디파인문 ## (윈도우 초기화 셋팅)
//====================================

#define WINNAME (LPTSTR)(TEXT("StardewValley Api Project"))

//전체 화면 사이즈
#define WINSIZEX 1024
#define WINSIZEY 768

#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================
//	## 매크로 함수 ## (메인게임의 릴리즈 부분에서 사용) 
//==================================================

#define SAFE_DELETE(p)	{if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr;}}

//==================================================
//	## 전역변수 ## (인스턴스, 윈도우 핸들, 마우스좌표) 
//	winmain에 선언되어있습니다
//==================================================
extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;
extern sound _sound;
extern bool _isDebug, _isAttribute;
extern bool _isSound;
extern HFONT hFont, hMediumFont, hSmallFont, OldFont;
extern int _mouseFrameX, _mouseFrameY;

//==================================================
//	## 전역 상태,타입 enum 
//==================================================