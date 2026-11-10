// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// BFME2's strategic (War of the Ring) player status screen Apt callbacks,
// "StrategicPlayerStatus::OnCloseWindow" (0x00523481) and two Apt queries,
// bound by those names as member pointers by the screen's registration
// 0x00523900; that binding is their only reference. The class is named for
// the strings' prefix.

#include <stdio.h>

#include "ascii_string.h"

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva0023C902 { public: int rva0023C902(); };
#include "../../../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
class GameWindowTransitionsHandler { public: bool isFinished(); };
extern GameWindowTransitionsHandler *TheTransitionHandler;
#include "../../../../../Include/GameClient/Display.h"
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
#include "../../../../../Include/Common/Rva005CB265.h"

#include "../../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
#include "../../../../../Include/GameClient/Shell.h"
extern Shell *TheShell;
struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;
struct GlobalA046B4;
extern GlobalA046B4 *g_Va00A046B4;
class DisconnectMenu; extern DisconnectMenu *TheDisconnectMenu;
struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;
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
	// Neither reads ECX: 0x00523592's one caller (0x005CD63E) leaves a
	// clobbered ECX and 0x005234AD is reached only by its tail jump.
	static void rva005234AD();
	static void rva00523592();
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
	if (TheInGameUI->slot95())
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_endGameTimer >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay) {
		if (TheDisplay->slot88())
			return;
		if (TheDisplay->slot87())
			return;
	}
	if ((*(int *)&TheDisconnectMenu))
		return;
	Rva004E855CClose();
	TheMouse->vslot19(2);
	TheShell->showShell(false);
	TheShell->push("StrategicPlayerStatus.apt", false);
	TheInGameUI->rva0029AC03(1);
}

// ?rva00523592 @0x00523592 19B: flag-gated tail call to Rva0052340DEnable or rva005234AD.
void StrategicPlayerStatus::rva00523592()
{
	if (g_Va00A04934)
		Rva0052340DEnable();
	else
		rva005234AD();
}

// Retail 0x0050EC24..0x0050ED1F: cdecl opener called by the rowed
// AptPalantir::OnBttnObjectives. The target string identifies PlayerTribute;
// the WorldBuilder twin is AptPlayerTribute::OpenScreen (0x0135B460).
// Guards and their offsets are independently shared with 0x005234AD above.
// The extra calls use the existing pinned +0x10 InGameUI view and folded
// slot-3 forwarder, as in the matched ShowQuitMenu; their target names remain
// unresolved here. No donor class layout is assumed.
class AptPlayerTribute
{
public:
	static void OpenScreen();
};

void AptPlayerTribute::OpenScreen()
{
	if (g_Va00A046B4)
		return;
	if (TheInGameUI->slot95())
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_endGameTimer >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay) {
		if (TheDisplay->slot88())
			return;
		if (TheDisplay->slot87())
			return;
	}
	if ((*(int *)&TheDisconnectMenu))
		return;
	Rva004E855CClose();
	((Rva005CB265 *)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
	TheMouse->vslot19(2);
	TheShell->showShell(false);
	TheShell->push("PlayerTribute.apt", false);
	TheInGameUI->rva0029AC03(1);
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
