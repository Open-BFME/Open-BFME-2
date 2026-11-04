// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// platformsdk
// ?gogoMessageBox@GameWindowManager@@UAEPAVGameWindow@@HHHHGVUnicodeString@@0P6AXXZ111@Z @0x002C187D 137B
// GameWindowManager::gogoMessageBox 11-arg forwarder to 12-arg with FALSE; BFME1 donor GameWindowManagerMessageBox.cpp; vtable 0x7C7C90 slot 18 calls slot 17 (+0x44); UnicodeString by-value via StringBase<G> pins 0x37050/0x36E70.

typedef int Int;
typedef unsigned short wchar_t;
typedef unsigned short UnsignedShort;
typedef bool Bool;

class UnicodeString;

#include <windows.h>
#include "unicode_string.h"


class GameWindow;

typedef void (*GameWinMsgBoxFunc)(void);

#include "../../../Include/GameClient/GameWindowManager.h"

GameWindow *GameWindowManager::gogoMessageBox(Int x, Int y, Int width, Int height, UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString, GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback)
{
	return gogoMessageBox(x, y, width, height, buttonFlags, titleString, bodyString, yesCallback, noCallback, okCallback, cancelCallback, false);
}
