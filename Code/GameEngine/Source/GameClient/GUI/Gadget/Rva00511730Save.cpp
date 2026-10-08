// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00511730@@YAXH@Z @0x00511730 135B.
// Free cdecl helper saving text-entry text into a global UnicodeString.
// Evidence: 11 retail callers all push 0 and pop ecx (cdecl 1 int arg, always
// 0, ignored; callee ends leave/ret with no return value, callers discard EAX).
// Callees GadgetTextEntryGetText rowed 0x00320AAB, StringBase<G>::set pinned
// 0x00037150, releaseBuffer rowed 0x00036E70, EH_prolog rowed 0x00629188.
// Globals g_Va00E046B8 (state with flag +0x278, field +0x27C, window +0x298),
// g_Va00E048C0 (target UnicodeString), empty via UnicodeString::TheEmptyString
// data 0x00A0C898. Flag/model donor TU GadgetComboBoxAddEntry.cpp
// (same dir, /O1 /DNDEBUG /MD /EHsc, UnicodeString/GameWindow); /O1 for the
// EBP frame plus and/or EH states, /EHsc for __EH_prolog. push ecx after the
// prolog is /O1 stack allocation, not a this-save: callers do not set ECX
// (e.g. 0x0044127C saves this in ESI), so this is YA not QAE. Volatile window
// member pins retail's add+cmp [eax]/push [eax] shape (two memory reads) over
// mov+test/push eax; precedent Debug_FrameCommands.cpp and INIFileTableGetName.cpp.
typedef unsigned short wchar_t;

#include "unicode_string.h"
#include "ascii_string.h"


class GameWindow
{
public:
	unsigned int winGetStyle();
};

UnicodeString GadgetTextEntryGetText(GameWindow *textentry);

struct Rva00511730State
{
	char m_pad00[0x278];
	unsigned char m_flag278;
	char m_pad279[3];
	int m_field27C;
	char m_pad280[0x298 - 0x280];
	GameWindow * volatile m_window298;
};

extern Rva00511730State *g_Va00E046B8;

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

struct Global009FE958;
class LANAPI; extern LANAPI *TheLAN;
#define TheLAN ((Global009FE958 *)TheLAN)

// TheGameLogic (0x00DFE78C): the game mode at +0x110.
class GameLogic
{
public:
	bool isInMultiplayerGame();

	unsigned char m_pad000[0x110];
	int m_110; // +0x110
};

extern GameLogic *TheGameLogic;

// TheWritableGlobalData (0x00DFE758): a flag at +0xA44 that must be set for
// the messenger to open in a multiplayer game.
class GlobalData
{
public:
	unsigned char m_pad000[0xA44];
	int m_A44; // +0xA44
};

extern GlobalData *TheWritableGlobalData;

// What TheWindowManager's slot 32 makes of an Apt file; slot 0 is run on it
// with 0. Names stay slot placeholders.
class Rva005116C2Screen
{
public:
	virtual void v00(int value) = 0;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
#undef V
	virtual Rva005116C2Screen *v32(AsciiString filename) = 0;
};

extern GameWindowManager *TheWindowManager;
UnicodeString g_Va00E048C0;

void __cdecl Rva00511730(int unused)
{
	if (!g_Va00E046B8)
		return;
	if (g_Va00E046B8->m_flag278)
		return;
	g_Va00E046B8->m_field27C = 2;
	g_Va00E046B8->m_flag278 = 1;
	if (g_Va00E046B8->m_window298)
	{
		g_Va00E048C0.set(GadgetTextEntryGetText(g_Va00E046B8->m_window298));
	}
	else
	{
		g_Va00E048C0.set(UnicodeString::TheEmptyString);
	}
}
// Retail 0x005116C2, 110 bytes: opens "Messenger.apt" when online (or on
// a LAN) and no messenger is up, except in a multiplayer game of mode 3 or
// with the global flag at +0xA44 clear.
void Rva005116C2()
{
	if ((TheGameSpyInfo || TheLAN) && !g_Va00E046B8)
	{
		GameLogic *logic = TheGameLogic;
		if (logic->isInMultiplayerGame()
			&& (logic->m_110 == 3 || !TheWritableGlobalData->m_A44))
			return;
		TheWindowManager->v32(AsciiString("Messenger.apt"))->v00(0);
	}
}

// ?g_Va00E046B8@@3PAURva00511730State@@A: the global at VA 0xe046b8 is ?g_Va00E046B8@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00E046B8@@3PAURva00511730State@@A=?g_Va00E046B8@@3HA")
