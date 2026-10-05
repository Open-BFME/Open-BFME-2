// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's skirmish screen Apt callbacks, 0x00521741 onward, bound by these
// names ("AptSkirmish::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x6B8 is the screen's state, +0x6D0
// its profile name entry.

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
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

// The skirmish screen instance (Rva0052192DInit.cpp's g_00E04930).
extern int g_00E04930;

class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

class AptSkirmish
{
public:
	void OnInitialized(const char *unused);
	// Bound under both "AptSkirmish::Back" and "AptSkirmish::Exit" (one
	// body or two folded), so it keeps its address.
	void rva0052174E(const char *unused);
	void StartGame(const char *unused);
	void OnStatsMenu(const char *unused);
	void rva00521770(const char *unused);
	void OnExitStatsScreen(const char *unused);
	void OnClosed(const char *unused);
	void OnNewProfileMenu(const char *unused);
	void OnDeleteProfileMenu(const char *unused);
	void OnChangeProfileMenu(const char *unused);

	// Unrowed 0x00521CFF (358 bytes) and 0x00522556 (277 bytes), pinned by
	// address.
	void rva00521CFF();
	void rva00522556();

private:
	unsigned char m_pad000[0x6B8];
	int m_state; // +0x6B8
	unsigned char m_pad6bc[0x6C1 - 0x6BC];
	bool m_6c1; // +0x6C1
	bool m_6c2; // +0x6C2
	unsigned char m_pad6c3[0x6D0 - 0x6C3];
	GameWindow *m_nameEntry; // +0x6D0
};

// Retail 0x00521643, 21 bytes. Name unknown. With the skirmish screen up,
// the Apt window manager's 0x00222479 (as Rva00433D27Enable and its twins).
void Rva00521643Enable()
{
	if (g_00E04930 == 0)
		return;
	((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}

// Retail 0x00521741, 13 bytes: "AptSkirmish::OnInitialized".
void AptSkirmish::OnInitialized(const char *unused)
{
	m_state = 1;
}

// Retail 0x0052174E, 8 bytes: bound as "AptSkirmish::Back" and
// "AptSkirmish::Exit".
void AptSkirmish::rva0052174E(const char *unused)
{
	Rva00521643Enable();
}

// Retail 0x00521756, 13 bytes: "AptSkirmish::StartGame".
void AptSkirmish::StartGame(const char *unused)
{
	m_state = 10;
}

class SkirmishPreferences
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3slotC();
	bool Rva0043B9E8();
};
class GameInfo
{
public:
	virtual void *v0slot0(int v);
};
extern GameInfo *TheSkirmishGameInfo;
extern int g_Va00E0333C;
void __cdecl operator delete(void *p);
class Panel00E0333C
{
public:
	virtual void p0();
	virtual void p1slot4();
};
void Rva00521643Enable();

// Retail 0x00521763, 13 bytes: "AptSkirmish::OnStatsMenu".
void AptSkirmish::OnStatsMenu(const char *unused)
{
	m_state = 8;
}

// Retail 0x00521770, 158 bytes: state machine for stats/profile screens.
// Cases 2/3/4 on m_state; case 2 checks SkirmishPreferences at +0x698,
// tears down TheSkirmishGameInfo, notifies g_Va00E0333C panel and re-enables.
void AptSkirmish::rva00521770(const char *unused)
{
	(void)unused;
	switch (m_state) {
	case 2: {
		m_6c1 = true;
		m_state = 7;
		SkirmishPreferences *prefs = (SkirmishPreferences *)((char *)this + 0x698);
		if (prefs->Rva0043B9E8())
			return;
		prefs->v3slotC();
		GameInfo *g = TheSkirmishGameInfo;
		void *toFree;
		if (g != 0)
			toFree = g->v0slot0(0);
		else
			toFree = 0;
		operator delete(toFree);
		TheSkirmishGameInfo = 0;
		Panel00E0333C *panel = (Panel00E0333C *)(void *)g_Va00E0333C;
		if (panel != 0)
			panel->p1slot4();
		Rva00521643Enable();
		break;
	}
	case 3:
		m_6c1 = true;
		m_state = 5;
		break;
	case 4:
		m_6c1 = true;
		m_state = 7;
		break;
	}
}

// Retail 0x00521826, 27 bytes: "AptSkirmish::OnExitStatsScreen".
void AptSkirmish::OnExitStatsScreen(const char *unused)
{
	if (m_state == 8 || m_state == 9)
		m_state = 7;
}

// Retail 0x00521E65, 17 bytes: "AptSkirmish::OnClosed".
void AptSkirmish::OnClosed(const char *unused)
{
	if (m_state == 11)
		rva00521CFF();
}

// Retail 0x00521E76, 76 bytes: "AptSkirmish::OnNewProfileMenu" focuses
// and clears the profile name entry.
void AptSkirmish::OnNewProfileMenu(const char *unused)
{
	m_state = 2;
	TheWindowManager->winSetFocus(m_nameEntry);
	GadgetTextEntrySetText(m_nameEntry, UnicodeString::TheEmptyString);
	m_6c2 = true;
}

// Retail 0x0052266B, 22 bytes: "AptSkirmish::OnDeleteProfileMenu".
void AptSkirmish::OnDeleteProfileMenu(const char *unused)
{
	rva00522556();
	m_state = 3;
}

// Retail 0x00522681, 22 bytes: "AptSkirmish::OnChangeProfileMenu".
void AptSkirmish::OnChangeProfileMenu(const char *unused)
{
	rva00522556();
	m_state = 4;
}
