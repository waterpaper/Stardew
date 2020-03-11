#include "stdafx.h"
#include "ui_conversation.h"


ui_conversation::ui_conversation()
{
}


ui_conversation::~ui_conversation()
{
}

HRESULT ui_conversation::init()
{
	uiImageAdd("대화UI_대화창", 100, 450, 800, 284, false);
	imageButtonAdd("cancel버튼", "", 900, 400, 26 * 3, 12 * 3, UIBUTTONKIND_CANCEL, true);

	_nowNpc = NPCMANAGER->getNowNpc();
	_conversationStringRect = RectMake(135,490,420,220);

	if (NPCMANAGER->getIsPresent())
	{
		num = 0;
	}
	else
	{
		num = RND->getFromIntTo(1, 3);
	}

	_sound.effSoundPlay("캐릭터대화");
	return S_OK;
}

void ui_conversation::update()
{
	ui::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vButton.size(); i++)
		{
			if (PtInRect(&_vButton[i]._rc, m_ptMouse))
			{
				if (_vButton[i]._kind == UIBUTTONKIND_CANCEL)
				{
					_sound.effSoundPlay("메뉴선택");
					UIMANAGER->changeUi("UI_general");
					UIMANAGER->setIsConversation(false);
				}

				break;
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		UIMANAGER->changeUi("UI_general");
		UIMANAGER->setIsConversation(false);
		_sound.effSoundPlay("메뉴선택");
	}
}

void ui_conversation::release()
{
	ui::release();

	if (NPCMANAGER->getIsPresent())
	{
		NPCMANAGER->setIsPresent(false);
	}
}

void ui_conversation::render(HDC hdc)
{
	char strTemp[512];

	ui::render(hdc);

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(183, 89, 20));
	sprintf(strTemp, "%s", _nowNpc.getConversation(num).c_str());
	DrawText(hdc, strTemp, strlen(strTemp), &_conversationStringRect, DT_LEFT | DT_WORDBREAK);

	SetTextAlign(hdc, TA_CENTER);

	sprintf(strTemp, "%s", _nowNpc.getName().c_str());
	TextOut(hdc,740, 654, strTemp, strlen(strTemp));//이름
	SetTextAlign(hdc, TA_LEFT);
	_nowNpc.getCharacterPortrait()->render(hdc, 650, 490);
}

int ui_conversation::getKindNum()
{
	return UIMANAGER->getSelectItem();
}
