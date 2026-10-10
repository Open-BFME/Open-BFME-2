// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// ?Rva001EF552Chat@@YGXVUnicodeString@@H@Z
// ?Rva001EF552Chat@@YGXABVUnicodeString@@H@Z, retail 0x001EF552, 107 bytes.
// Chain from 0x00381C82: if g_00E02324 flags at +0x10/+0x11 set, show a copy
// of the text via TheInGameUI slot 0x40, then forward (1, text, color) to
// Rva00381C82AddChatText. Evidence: rowed callees, TheInGameUI use, ret 8.
#include "unicode_string.h"

struct Rva001EF552State
{
	char m_pad[0x10];
	bool m10;
	bool m11;
};

extern Rva001EF552State *g_00E02324;

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void message(UnicodeString format, ...);
};

extern InGameUI *TheInGameUI;

void Rva00381C82AddChatText(int window, const UnicodeString &text, int color);

void __stdcall Rva001EF552Chat(UnicodeString text, int color)
{
	if (g_00E02324)
	{
		if ((g_00E02324->m10?g_00E02324->m10:g_00E02324->m10))
		{
			if (g_00E02324->m11)
			{
				TheInGameUI->message(text);
			}
		}
	}
	Rva00381C82AddChatText(1, text, color);
}
