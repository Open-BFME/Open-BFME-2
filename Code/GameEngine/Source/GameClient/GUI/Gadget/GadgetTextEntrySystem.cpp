// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// platformsdk
// ?GadgetTextEntrySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// @0x003207F5 694B (Ghidra boundary, EH frame): the text entry system
// callback, slot 0x84 of the system table 0x9BC9DC. Reference semantics:
// Open-BFME-1 GadgetTextEntry.cpp GadgetTextEntrySystem (the ZH body plus
// cursor placement, edit-done and the click-through reset). Target facts:
// user data through winGetUserData, instance state at +8; the EntryData
// layout of GadgetTextEntryInsertCharacter.cpp (drawTextFromStart +0x13,
// charPos +0x1C, conCharPos +0x1E) plus a byte at +0x14 tested on destroy,
// the construct list at +0x18 and a short at +0x20 cleared with the
// construct text; GadgetTextEntrySetCursorPosition 0x00320737 places the
// cursor; DisplayStringManager slot 15 frees the strings; IMEManager slots
// 14 (attach) and 19 (isAttachedTo); GameWindowManager slots 35 (winDestroy),
// 48 (winGetFocus) and 58 (winSendSystemMsg). On destroy a set +0x14 byte
// passes 2 to the click-through handler's setter 0x00432AEB. The focused
// window is kept in a file static (0x00E01D44) stored after unrelated loads.
#include <windows.h>
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23
};

enum
{
	GGM_FOCUS_CHANGE = 0x4003,
	GEM_GET_TEXT = 0x402F,
	GEM_SET_TEXT = 0x4030,
	GEM_EDIT_DONE = 0x4031
};

enum
{
	WIN_STATE_SELECTED = 0x04,
	WIN_STATE_HILITED = 0x02
};

#define BitSet(x, i) ((x) |= (i))
#define BitClear(x, i) ((x) &= ~(i))

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


#include "../../../../Include/GameClient/DisplayString.h"

#include "../../../../Include/GameClient/DisplayStringManager.h"

#include "../../../../Include/GameClient/IMEManagerClass.h"

#include "../../../../Include/GameClient/GameWindowManager.h"

// Native calls at the documented setter sites target the already rowed
// Rva00432AEB provider (same thiscall int(int) ABI); use its linker identity.
#include "../../../../Include/GameClient/Rva00432AEB.h"

struct EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	UnsignedInt validation;
	short maxTextLen;
	Bool receivedUnichar;
	Bool drawTextFromStart;
	Bool systemFlag;
	unsigned char m_pad15[0x18 - 0x15];
	GameWindow *constructList;
	UnsignedShort charPos;
	UnsignedShort conCharPos;
	UnsignedShort unknown20;
};

extern GameWindowManager *TheWindowManager;
extern DisplayStringManager *TheDisplayStringManager;
extern IMEManager *TheIMEManager;
extern int g_Va00E032C8;

void GadgetTextEntrySetCursorPosition(GameWindow *window, UnsignedInt position);

static GameWindow *curWindow = NULL;

WindowMsgHandledType GadgetTextEntrySystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	EntryData *entryData = (EntryData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch (msg)
	{
		case GEM_GET_TEXT:
			*(UnicodeString *)mData2 = entryData->text->getText();
			break;

		case GEM_SET_TEXT:
		{
			const UnicodeString *ustr = (const UnicodeString *)mData1;
			entryData->text->setText(*ustr);
			if (TheWindowManager->winGetFocus() == window)
				GadgetTextEntrySetCursorPosition(window, ustr->getLength());
			else
				GadgetTextEntrySetCursorPosition(window, 0);
			entryData->constructText->setText(UnicodeString::TheEmptyString);
			entryData->conCharPos = entryData->charPos;
			entryData->unknown20 = 0;

			// set our secret text string to be filled with '*' the same length
			entryData->sText->setText(UnicodeString::TheEmptyString);
			Int len = ustr->getLength();
			for (Int i = 0; i < len; i++)
				entryData->sText->appendChar(L'*');
			break;
		}

		case GWM_CREATE:
			break;

		case GWM_DESTROY:
			if (entryData && entryData->systemFlag)
				((Rva00432AEB *)g_Va00E032C8)->rva00432AEB(2);

			// delete the edit display strings
			TheDisplayStringManager->freeDisplayString(entryData->text);
			TheDisplayStringManager->freeDisplayString(entryData->sText);
			TheDisplayStringManager->freeDisplayString(entryData->constructText);

			// delete construct list
			if (entryData->constructList && TheWindowManager)
				TheWindowManager->winDestroy(entryData->constructList);

			// free all edit data
			delete (EntryData *)window->winGetUserData();
			break;

		case GWM_INPUT_FOCUS:
			if (mData1 == false)
			{
				// we're losing focus
				if (entryData->drawTextFromStart)
				{
					entryData->drawTextFromStart = false;
					TheWindowManager->winSendSystemMsg(window->winGetOwner(),
						GEM_EDIT_DONE, (WindowMsgData)window, 1);
				}
				GadgetTextEntrySetCursorPosition(window, entryData->text->getTextLength());
				entryData->conCharPos = entryData->charPos;
				BitClear(instData->m_state, WIN_STATE_SELECTED);
				BitClear(instData->m_state, WIN_STATE_HILITED);
				curWindow = NULL;

				if (entryData->constructList)
					entryData->constructList->winHide(true);
				entryData->constructText->setText(UnicodeString::TheEmptyString);
				entryData->unknown20 = 0;
				if (TheIMEManager && TheIMEManager->isAttachedTo(window))
					TheIMEManager->attach(NULL);
			}
			else
			{
				GadgetTextEntrySetCursorPosition(window, entryData->text->getTextLength());
				entryData->conCharPos = 0;
				curWindow = window;
				if (TheIMEManager)
					TheIMEManager->attach(window);
				BitSet(instData->m_state, WIN_STATE_SELECTED);
				BitSet(instData->m_state, WIN_STATE_HILITED);
				entryData->drawTextFromStart = false;
			}

			TheWindowManager->winSendSystemMsg(window->winGetOwner(),
				GGM_FOCUS_CHANGE, mData1, window->winGetWindowId());

			*(Bool *)mData2 = true;
			break;

		default:
			return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
