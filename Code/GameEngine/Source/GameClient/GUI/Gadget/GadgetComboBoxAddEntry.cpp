// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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

#ifndef NULL
#define NULL 0
#endif

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
