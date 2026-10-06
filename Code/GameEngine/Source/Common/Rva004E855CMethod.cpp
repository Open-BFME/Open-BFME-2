// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva004E855CClose@@YAXXZ @ 0x004E855C (196B):
// Free guarded chat-close helper. If g_Va00E04478 and its state at +0x27C
// allow (not 3/4, zero sets 4 and returns), save the text-entry text at
// +0x284 into g_00E0447C (empty fallback), fire CloseChat via rowed
// Rva00222A8BTarget::invoke on the level at +0x274, set state 3 and run the
// rowed Rva004E84ABRun refresh. Evidence: chain via 0x004E84AB; callers at
// 0x00512E01 0x0050ECBF 0x0043CC57; callees all rowed; donor TU
// Rva00511730Save.cpp (same GetText/set/releaseBuffer/EH_prolog shape).

#include "unicode_string.h"

class GameWindow;

UnicodeString __cdecl GadgetTextEntryGetText(GameWindow *textentry);

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

struct Rva004E855CState
{
	char m_pad00[0x274];
	void *m_level274;
	char m_pad278[4];
	int m_state27C;
	char m_pad280[0x284 - 0x280];
	GameWindow * volatile m_window284;
};

extern Rva004E855CState *g_Va00E04478;
extern UnicodeString g_00E0447C;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

void __cdecl Rva004E84ABRun();

// ?g_Va00E04478@@3PAURva004E855CState@@A: the global at VA 0xe04478 is ?g_Va00E04478@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00E04478@@3PAURva004E855CState@@A=?g_Va00E04478@@3HA")

void __cdecl Rva004E855CClose()
{
	if (!g_Va00E04478)
		return;
	if (g_Va00E04478->m_state27C == 3)
		return;
	if (g_Va00E04478->m_state27C == 4)
		return;
	if (g_Va00E04478->m_state27C == 0)
	{
		g_Va00E04478->m_state27C = 4;
		return;
	}
	if (g_Va00E04478->m_window284)
	{
		g_00E0447C.set(GadgetTextEntryGetText(g_Va00E04478->m_window284));
	}
	else
	{
		g_00E0447C.set(UnicodeString::TheEmptyString);
	}
	TheRva00222A8BTarget->invoke(g_Va00E04478->m_level274, "CloseChat", 0, 0, 0, 0, 0, 0);
	g_Va00E04478->m_state27C = 3;
	Rva004E84ABRun();
}
