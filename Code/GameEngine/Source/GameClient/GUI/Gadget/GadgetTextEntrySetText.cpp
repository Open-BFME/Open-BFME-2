// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?GadgetTextEntrySetText@@YAXPAVGameWindow@@VUnicodeString@@@Z @0x002C17EB 66B
// GadgetTextEntrySetText; ZH donor GadgetTextEntry.h inline verbatim shape
// (winSendSystemMsg GEM_SET_TEXT 0x4030 with &text and 0); TheWindowManager at
// 0x9FEF1C slot 58 0xE8; UnicodeString by-value param destroyed via
// StringBase-G releaseBuffer 0x36E70; callers pass UnicodeString via G copy
// ctor (0x002C1C74 0x00322D63 0x0032305C); pin SetListLength int mismatches
// the destructor and copy-ctor evidence.

typedef unsigned short wchar_t;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class UnicodeString;
class AsciiString;

#include "unicode_string.h"


class GameWindow;

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

inline void GadgetTextEntrySetText(GameWindow *gameWindow, UnicodeString text)
{
	TheWindowManager->winSendSystemMsg(gameWindow, 0x4030, (WindowMsgData)&text, 0);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (*_bfmeInlineAnchor_GadgetTextEntrySetText_0)(GameWindow *g, UnicodeString text) = &GadgetTextEntrySetText;
