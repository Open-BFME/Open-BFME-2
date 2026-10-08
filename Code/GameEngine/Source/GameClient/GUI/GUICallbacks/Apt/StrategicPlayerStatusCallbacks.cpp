// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// BFME2's strategic (War of the Ring) player status screen Apt callbacks,
// "StrategicPlayerStatus::OnCloseWindow" (0x00523481) and two Apt queries,
// bound by those names as member pointers by the screen's registration
// 0x00523900; that binding is their only reference. The class is named for
// the strings' prefix.

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

#include "ascii_string.h"

class GameLogic
{
public:
	unsigned char m_pad[0x6d];
	unsigned char m_6d;
};
extern GameLogic *TheGameLogic;
class Rva0023C902 { public: int rva0023C902(); };
class ScriptEngine
{
public:
	unsigned char m_pad[0x1a104];
	int m_1A104;
};
extern ScriptEngine *TheScriptEngine;
class GameWindowTransitionsHandler { public: bool isFinished(); };
extern GameWindowTransitionsHandler *TheTransitionHandler;
class Display
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual bool vslot87();
	virtual bool vslot88();
};
extern Display *TheDisplay;
class Mouse
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void vslot19(int);
};
extern Mouse *TheMouse;
class Rva005CB260;
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class InGameUI
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void vslot94(int);
	virtual bool vslot95();
	Rva005CB260 *rva000CF155();
};
extern InGameUI *TheInGameUI;
class Shell
{
public:
	void rva0035C7CF(bool);
	void push(AsciiString filename, bool shutdownImmediate);
};
extern Shell *TheShell;
struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;
struct GlobalA046B4;
extern GlobalA046B4 *g_Va00A046B4;
extern int g_Va00E048D0;
void Rva004E855CClose();

// Rva0052340DEnable.cpp's 0x0052340D.
void Rva0052340DEnable();

// The screen's color list at +0x288 (a vector of 0x00RRGGBB values).
struct StrategicPlayerColors
{
	unsigned int size() const { return m_end - m_begin; }
	unsigned int operator[](unsigned int index) const { return m_begin[index]; }

	unsigned int *m_begin;
	unsigned int *m_end;
};

class StrategicPlayerStatus
{
public:
	void OnCloseWindow(const char *unused);
	void rva005234AD();
	// Bound as "StrategicPlayerStatus::PlayerIndex" (query 0),
	// "...::NumAlliedPlayers" (1) and "...::NumEnemyPlayers" (2), so it
	// keeps its address.
	void rva00523438(int query, char *result, bool skip);
	// Bound as "StrategicPlayerStatus::EnemyColor_%d" and
	// "StrategicPlayerStatus::%sColor_%d" for each index, so it keeps its
	// address.
	void rva0052373A(int query, char *result, bool skip);

private:
	unsigned char m_pad000[0x27C];
	int m_playerIndex; // +0x27C
	int m_numAllied; // +0x280
	int m_numEnemies; // +0x284
	StrategicPlayerColors m_colors; // +0x288
};

// Retail 0x00523438, 73 bytes: bound as "StrategicPlayerStatus::PlayerIndex",
// "NumAlliedPlayers" and "NumEnemyPlayers", an Apt query answering the
// count the query selects ("0" otherwise).
void StrategicPlayerStatus::rva00523438(int query, char *result, bool skip)
{
	if (skip)
		return;
	result[0] = '0';
	result[1] = 0;
	switch (query)
	{
	case 0:
		sprintf(result, "%d", m_playerIndex);
		break;
	case 1:
		sprintf(result, "%d", m_numAllied);
		break;
	case 2:
		sprintf(result, "%d", m_numEnemies);
		break;
	}
}

// Retail 0x0052373A, 59 bytes: bound as the indexed color queries, an Apt
// query answering the color as 0xRRGGBB.
void StrategicPlayerStatus::rva0052373A(int query, char *result, bool skip)
{
	if ((unsigned int)query < m_colors.size())
		_snprintf(result, 0xFF, "0x%x", m_colors[query] & 0xFFFFFF);
}

// Retail 0x00523481, 8 bytes: "StrategicPlayerStatus::OnCloseWindow".
void StrategicPlayerStatus::OnCloseWindow(const char *unused)
{
	Rva0052340DEnable();
}

// ?rva005234AD @0x005234AD 229B: guarded StrategicPlayerStatus screen push.
void StrategicPlayerStatus::rva005234AD()
{
	if (g_Va00A04934)
		return;
	if (TheInGameUI->vslot95())
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_1A104 >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay) {
		if (TheDisplay->vslot88())
			return;
		if (TheDisplay->vslot87())
			return;
	}
	if (g_Va00E048D0)
		return;
	Rva004E855CClose();
	TheMouse->vslot19(2);
	TheShell->rva0035C7CF(false);
	TheShell->push("StrategicPlayerStatus.apt", false);
	TheInGameUI->vslot94(1);
}

// Retail 0x0050EC24..0x0050ED1F: cdecl opener called by the rowed
// AptPalantir::OnBttnObjectives. The target string identifies PlayerTribute;
// the WorldBuilder twin is AptPlayerTribute::OpenScreen (0x0135B460).
// Guards and their offsets are independently shared with 0x005234AD above.
// The extra calls use the existing pinned +0x10 InGameUI view and folded
// slot-3 forwarder, as in the matched ShowQuitMenu; their target names remain
// unresolved here. No donor class layout is assumed.
void Rva0050EC24()
{
	if (g_Va00A046B4)
		return;
	if (TheInGameUI->vslot95())
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_1A104 >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay) {
		if (TheDisplay->vslot88())
			return;
		if (TheDisplay->vslot87())
			return;
	}
	if (g_Va00E048D0)
		return;
	Rva004E855CClose();
	((Rva005CB265 *)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
	TheMouse->vslot19(2);
	TheShell->rva0035C7CF(false);
	TheShell->push("PlayerTribute.apt", false);
	TheInGameUI->vslot94(1);
}

#pragma optimize("y", off)
// ?Rva005235A5@@YGHHEH@Z @0x005235A5 48B
// Gate for query 0x15 with sub 1/0xF/0x1C and flag bit 0: runs the
// screen enabler when the flag is set, always answering true when the
// query pair matches.
int __stdcall Rva005235A5(int query, unsigned char sub, int flags)
{
	if (query != 0x15)
		return 0;
	switch (sub)
	{
	case 1:
	case 0xF:
	case 0x1C:
		break;
	default:
		return 0;
	}
	if (flags & 1)
		Rva0052340DEnable();
	return 1;
}
