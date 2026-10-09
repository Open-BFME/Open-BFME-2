// ?rva00515C64@AptMainMenu@@QAEHXZ
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?rva00515C64@AptMainMenu@@QAEHXZ
// Retail 0x00515C64..0x00515F7B (791 bytes, followed by the 12-entry jump
// table of the inner switch, which this build emits after the code as well).
// BANKED NEAR MISS (score ~0.97): every instruction and the frame size
// (0x20) match; only the stack-slot assignment differs (18 operands):
// retail puts the "0" save-name temporary at [ebp-0x14], the callback int at
// [ebp-0x18] (shared with case 6's spilled fetch result) and the by-value
// argument's ESP save at [ebp-0x2c]; this build puts the callback at
// [ebp-0x14], the temporary at [ebp-0x18] and shares the ESP save with the
// spill at [ebp-0x1c]. Tried: callback declared at function / case-9 /
// per-case scope, forwarding by-value int ctor (frame grows to 0x24), the
// found flag hoisted. Plus the three pins listed below.
//
// AptMainMenu's per-frame state machine (vtable entry 0x00865F24; returns 1):
// 1 hides the shell and, when the "0" save state loads, resets the engine
// and leaves the restart (else waits in 2); 4 updates the credits roll and
// asks the Apt movie level to "HideCredits" when it finished; 5 / 6 check the
// firewall helper at +0x290 (rowed init 0x005B7107) and either show the
// "GUI:FirewallNoAdmin" box (AptMessageBox pin 0x00437E84) or queue screen
// 6 / 10; 7 returns to idle; 9 runs the menu-to-submenu transition (rowed
// 0x00514F2E) and opens the queued screen at +0x28C (save/load modes,
// options, create-a-hero, the two campaign wrappers with the side at +0x2A8,
// the LAN / online restarts registering callbacks 0x005148AA / 0x005148FD
// through the rowed 0x003FE7E6 registry, skirmish after rowed
// GameLogic::rva00376E92), then idles.
// The callback temporary follows Rva00211FA8Registration.cpp's forwarding
// constructor. Inner case bodies are written in retail's layout order.
// PINS (all placeholder-named addresses):
//   ?Rva00515BCA@@YAXD@Z -> 0x00515BCA  (retail passes the side byte as is)
//   ?Rva00515C17@@YAXD@Z -> 0x00515C17
//   ?rva00514E20@AptMainMenu@@QAEXXZ -> 0x00514E20  (called with the menu in ECX)
#include "unicode_string.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

class AptSaveLoad { public: static void OpenScreen(int mode, int screen, bool flag); };
class AptOptions { public: static void OpenScreen(bool a, bool b, bool c, bool d); };
class AptCreateAHero { public: static void OpenScreen(int mode); };
class AptSkirmish { public: static void OpenScreen(int mode); };
void Rva00515BCA(char side);	// 0x00515BCA
void Rva00515C17(char side);	// 0x00515C17
void Rva00437E84(int owner, const UnicodeString &title, const UnicodeString &message);	// AptMessageBox::Show

// The callback wrapper (rowed ctor 0x00211E75) and its forwarding by-value
// form, as in Rva00211FA8Registration.cpp.
struct Impl00211E75;
class Rva00211E75
{
public:
	Rva00211E75(const int *arg);
	Rva00211E75(const Rva00211E75 &);
	~Rva00211E75();
private:
	Impl00211E75 *m_impl;
};
class Rva00211E75Callback : public Rva00211E75
{
public:
	~Rva00211E75Callback();
	Rva00211E75Callback(int callback) : Rva00211E75(&callback) {}
	Rva00211E75Callback(const int *callback) : Rva00211E75(callback) {}
};
bool Rva003FE7E6(Rva00211E75Callback callback, int *id);
extern int g_00E02EC4;
void Rva005148AA();	// restart callbacks bound below
void Rva005148FD();

class Rva00690CB0Owner { public: bool init(); };

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual UnicodeString fetch(const char *label, bool *exists = 0);	// +0x3C
};
extern GameTextInterface *TheGameText;

class AptMainMenuCredits
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
#undef V
	virtual void update();	// +0x28
	unsigned char m_pad04[0x34 - 4];
	bool m_finished;	// +0x34
};
extern AptMainMenuCredits *g_bfmeSinkBOE;

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *name, int a, const char *b, void *c, void *d, void *e, void *f);
	void rva00222F55(bool hide);	// hide the background
};
extern Rva00222A8BTarget *g_bfmeAptWindowManager;

class Shell
{
public:
	void rva0035BF4C(bool hide);
	void rva0035C7CF(bool flag);
};
extern Shell *TheShell;

class GameState { public: int rva002DF2F6(const UnicodeString &name); };
extern GameState *TheGameState;

class GameEngine
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
#undef V
	virtual void reset();	// +0x24
};
extern GameEngine *TheGameEngine;
extern GameLogic *TheGameLogic;

class AptMainMenu
{
public:
	int rva00515C64();
	void rva00514F2E();
	void rva00514E20();	// 0x00514E20
private:
	unsigned char m_pad000[0x274];
	void *m_274;			// +0x274
	unsigned char m_pad278[0x27D - 0x278];
	bool m_pendingRestart;		// +0x27D
	unsigned char m_pad27E[0x288 - 0x27E];
	int m_state;			// +0x288
	int m_next;			// +0x28C
	Rva00690CB0Owner m_290;		// +0x290
	unsigned char m_pad291[0x2A8 - 0x291];
	char m_side;			// +0x2A8
};

int AptMainMenu::rva00515C64()
{
	switch (m_state)
	{
	case 1:
	{
		TheShell->rva0035BF4C(true);
		bool found = TheGameState->rva002DF2F6(UnicodeString(L"0")) != 0;
		if (found)
		{
			TheGameEngine->reset();
			TheShell->rva0035C7CF(true);
			m_pendingRestart = false;
			m_state = 0;
			g_bfmeAptWindowManager->rva00222F55(false);
		}
		else
		{
			m_state = 2;
		}
		break;
	}
	case 4:
		if (g_bfmeSinkBOE)
		{
			g_bfmeSinkBOE->update();
			if (g_bfmeSinkBOE->m_finished)
				g_bfmeAptWindowManager->invoke(m_274, "HideCredits", 0, 0, 0, 0, 0, 0);
		}
		break;
	case 5:
		if (!m_290.init())
		{
			Rva00437E84(0, TheGameText->fetch("GUI:FirewallNoAdminTitle"), TheGameText->fetch("GUI:FirewallNoAdminMessage"));
			m_state = 0;
		}
		else
		{
			m_state = 9;
			m_next = 6;
		}
		break;
	case 6:
		if (!m_290.init())
		{
			Rva00437E84(0, TheGameText->fetch("GUI:FirewallNoAdminTitle"), TheGameText->fetch("GUI:FirewallNoAdminMessage"));
			m_state = 0;
		}
		else
		{
			m_state = 9;
			m_next = 10;
		}
		break;
	case 7:
		m_state = 0;
		break;
	case 9:
	{
		rva00514F2E();
		int callback;
		switch (m_next)
		{
		case 1: AptSaveLoad::OpenScreen(2, 11, false); break;
		case 2: AptSaveLoad::OpenScreen(2, 1, false); break;
		case 3: AptSaveLoad::OpenScreen(2, 4, false); break;
		case 4: AptOptions::OpenScreen(false, true, true, false); break;
		case 5: AptOptions::OpenScreen(false, true, true, true); break;
		case 9: AptCreateAHero::OpenScreen(1); break;
		case 11: Rva00515BCA(m_side); break;
		case 12: Rva00515C17(m_side); break;
		case 6:
		{
			rva00514E20();
			callback = (int)&Rva005148AA;
			Rva003FE7E6(Rva00211E75Callback(&callback), &g_00E02EC4);
			break;
		}
		case 10:
		{
			rva00514E20();
			callback = (int)&Rva005148FD;
			Rva003FE7E6(Rva00211E75Callback(&callback), &g_00E02EC4);
			break;
		}
		case 7:
			TheGameLogic->rva00376E92(false, false);
			AptSkirmish::OpenScreen(0);
			break;
		case 8:
			TheGameLogic->rva00376E92(false, false);
			AptSkirmish::OpenScreen(1);
			break;
		}
		m_next = 0;
		m_state = 0;
		break;
	}
	}
	return 1;
}
