// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// ?Rva001EF552Chat@@YGXVUnicodeString@@H@Z
// ?Rva001EF552Chat@@YGXABVUnicodeString@@H@Z, retail 0x001EF552, 107 bytes.
// Chain from 0x00381C82: if TheGameSpyGame flags at +0x10/+0x11 set, show a copy
// of the text via TheInGameUI slot 0x40, then forward (1, text, color) to
// Rva00381C82AddChatText. Evidence: rowed callees, TheInGameUI use, ret 8.
#include "unicode_string.h"

struct Rva001EF552State
{
	char m_pad[0x10];
	bool m10;
	bool m11;
};

class GameSpyStagingRoom;
extern GameSpyStagingRoom *TheGameSpyGame;

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

void Rva00381C82AddChatText(int window, const UnicodeString &text, int color);

void __stdcall Rva001EF552Chat(UnicodeString text, int color)
{
	if (TheGameSpyGame)
	{
		if ((((Rva001EF552State *)TheGameSpyGame)->m10?((Rva001EF552State *)TheGameSpyGame)->m10:((Rva001EF552State *)TheGameSpyGame)->m10))
		{
			if (((Rva001EF552State *)TheGameSpyGame)->m11)
			{
				TheInGameUI->rva0029E846(text);
			}
		}
	}
	Rva00381C82AddChatText(1, text, color);
}
