// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk
// ?GadgetComboBoxAddEntry@@YAHPAVGameWindow@@VUnicodeString@@H@Z @0x00322DC5 84B.
// ZH donor GadgetComboBox.cpp GadgetComboBoxAddEntry: null -> -1,
// GCM_ADD_ENTRY 0x4022 via TheWindowManager at 0x9FEF1C slot 58 0xE8 with &text and color.
// Retail calls 0x00036E70 releaseBuffer; 40+ callers include 0x0043F306 0x0043F3C3.
typedef unsigned short wchar_t;
typedef int Int;
typedef Int Color;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class UnicodeString;
class AsciiString;

#include <windows.h>
#include "unicode_string.h"


class GameWindow;

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

Int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, Color color)
{
	if (comboBox == NULL)
		return -1;
	return (Int)TheWindowManager->winSendSystemMsg(comboBox, 0x4022, (WindowMsgData)&text, color);
}

Int Rva00322E19Add(GameWindow *comboBox, UnicodeString text, Color color)
{
	if (comboBox == NULL)
		return -1;
	return (Int)TheWindowManager->winSendSystemMsg(comboBox, 0x4023, (WindowMsgData)&text, color);
}
