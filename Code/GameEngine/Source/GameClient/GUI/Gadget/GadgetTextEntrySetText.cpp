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

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

inline void GadgetTextEntrySetText(GameWindow *g, UnicodeString text)
{
	TheWindowManager->winSendSystemMsg(g, 0x4030, (WindowMsgData)&text, 0);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (*_bfmeInlineAnchor_GadgetTextEntrySetText_0)(GameWindow *g, UnicodeString text) = &GadgetTextEntrySetText;
