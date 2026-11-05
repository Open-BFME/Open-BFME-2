// cl: /MD /Ireference/shims/bfme2_ascii
//
// ?rva004443E7@AptLanLobby@@QAEXXZ, retail 0x004443E7 37B.
// Class: these bodies run on the LAN lobby screen (vftable 0x00C3E0F8, its
// +0x288 AptMpGameSetup panel, state at +0x6A4), which retail's callback strings
// and WorldBuilder's AptLanLobby.cpp name AptLanLobby; the rows were
// formerly labelled GameEngine. OnGameCreate 0x004469D1 and OnGameJoin
// 0x00446A1C are WorldBuilder's names (AptLanLobby.cpp:1295 / :1320 assert
// m_currentState against CS_HOST_SETUP_WAIT / CS_JOIN_SETUP_WAIT, then the
// same 0x004467AC call and "DoCreateGame" / "DoJoinGame" invoke).
// Calls member at +0x288 slot 1 then global 0xDFE958 slot 0x48 then tail to GameEngine terminateChild.
// Evidence: add ecx 0x288 and call [eax+4]; mov ecx [0xDFE958] test and call [eax+0x48];
// mov ecx [0xDFE710 TheGameEngine] jmp to rowed stopHeadlessClients 0x2260F7;
// callers at 0x44459D 0x444E7E 0x444EA4 0x444EE5 0x44666D.

#include "unicode_string.h"

class LANAPI; extern LANAPI *TheLAN;

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

extern class GameEngine *TheGameEngine;

// The +0x288 panel's rowed bodies: 0x0044303D (1040 bytes; registers the
// panel's Apt callbacks) and 0x0043DC0F.
class GameInfo;
#include "../../../../../Include/GameClient/AptMpGameSetup.h"

class Global004443E7958View
{
public:
	virtual void g0();
	virtual void g1();
	virtual void g2();
	virtual void g3();
	virtual void g4();
	virtual void g5();
	virtual void g6();
	virtual void g7();
	virtual void g8();
	virtual void g9();
	virtual void g10();
	virtual void g11();
	virtual void g12();
	virtual void g13();
	virtual void g14();
	virtual void g15();
	virtual void g16();
	virtual void g17();
	virtual void g18();
};

#include "../../../../../Include/Common/Rva00222A8BTarget.h"

#define TheGlobal004443E7958 (*(Global004443E7958View **)&TheLAN)
#define TheGameEngine004443E7 (*(class GameEngine **)&TheGameEngine)
#define TheInvoke00444E8ATarget (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)

// Free helpers the key handler below calls: 0x00444040 is rowed; 0x005116C2
// (110 bytes, no arguments, opens "Messenger.apt" when no messenger state
// exists) is AptMessenger::OpenScreen; 0x00511730 is rowed.
void Rva00444040Enable();
class AptMessenger
{
public:
 static AptMessenger *s_instance;
public:
	static void OpenScreen();
};
void __cdecl Rva00511730(int unused);

struct Rva00511730State;

#include "../../../../../Include/Common/GameEngine.h"

class AptLanLobby
{
public:
	void rva004443E7();
	void Cancel(int unused);
	void CancelMenu();
	void rva00444EC8();
	virtual int rva0044522D(int msg, unsigned char key, int flags);
	void OnGameCreate();
	virtual void rva004442DB();
	void OnGameJoin();

private:
	// Unrowed 0x004467AC (549 bytes): prepares the LAN game info for a
	// create or join and reports success; pinned by address.
	bool rva004467AC();
public:

private:
	char m_pad04[0x274 - 4];
	void *m_owner; // +0x274
	char m_pad278[0x288 - 0x278];
	AptMpGameSetup m_panel; // +0x288..+0x668
	char m_pad668[0x6A4 - 0x668];
	int m_currentState; // +0x6A4
	char m_pad6a8[0x6C0 - 0x6A8];
	unsigned char m_6c0; // +0x6C0
};

void AptLanLobby::Cancel(int unused)
{
	(void)unused;
	if (m_currentState == 6)
		m_panel.field2c3 = 0;
	else {
		rva004443E7();
		m_currentState = 0;
	}
}

void AptLanLobby::CancelMenu()
{
	if (TheInvoke00444E8ATarget == 0)
		return;
	if (m_currentState == 0)
		return;
	m_currentState = 0;
	rva004443E7();
	Rva00222A8BTarget *t = TheInvoke00444E8ATarget;
	t->invoke(m_owner, "CancelGame", 0, 0, 0, 0, 0, 0);
}

// Retail 0x0044522D, 123 bytes: slot 1 of the LAN lobby screen's own vftable
// 0x00C3E0F8 (the object this view describes, AptLanLobby). Name unknown. Message 0x15 with +0x6C0 clear: key 0x1C/0x9C
// with flag 0x4 or 0x8 handles (and on flag 0x1 opens the messenger or saves
// its text); key 1 on flag 0x1 dispatches on +0x6A4 (1, or 4 and 9). Key 1
// is written first: retail shares the second case's return block.
int AptLanLobby::rva0044522D(int msg, unsigned char key, int flags)
{
	if (!m_6c0 && msg == 0x15)
	{
		switch (key)
		{
		case 1:
			if (flags & 1)
			{
				switch (m_currentState)
				{
				case 1:
					Rva00444040Enable();
					return 1;
				case 4:
				case 9:
					Cancel(0);
					return 1;
				}
			}
			break;
		case 0x1C:
		case 0x9C:
			if (flags & 0xC)
			{
				if (flags & 1)
				{
					if (!AptMessenger::s_instance)
						AptMessenger::OpenScreen();
					else
						Rva00511730(0);
				}
				return 1;
			}
			break;
		}
	}
	return 0;
}

// Retail 0x004469D1, 75 bytes, and 0x00446A1C, 75 bytes: the lobby screen's
// create and join continuations. From state 3 (create) or 8 (join) they run
// 0x004467AC and on success invoke "DoCreateGame" / "DoJoinGame" on the
// screen owner (+0x274) and advance to 4 / 9; on failure they fall back to
// state 1. Names from WorldBuilder (see the head of this file).
void AptLanLobby::OnGameCreate()
{
	if (m_currentState != 3)
		return;
	if (rva004467AC())
	{
		TheInvoke00444E8ATarget->invoke(m_owner, "DoCreateGame", 0, 0, 0, 0, 0, 0);
		m_currentState = 4;
	}
	else
		m_currentState = 1;
}

void AptLanLobby::OnGameJoin()
{
	if (m_currentState != 8)
		return;
	if (rva004467AC())
	{
		TheInvoke00444E8ATarget->invoke(m_owner, "DoJoinGame", 0, 0, 0, 0, 0, 0);
		m_currentState = 9;
	}
	else
		m_currentState = 1;
}

// Retail 0x004442DB, 34 bytes: slot 12 of the lobby screen's vftable
// 0x00C3E0F8. Name unknown. Runs the +0x288 panel's 0x0044303D, then puts
// the Apt window manager into background mode 1 unless it is already there
// (the rowed rva002233A6, as Rva00444525Init does after pushing the screen).
void AptLanLobby::rva004442DB()
{
	m_panel.rva0044303D();
	if (TheInvoke00444E8ATarget->m_31C != 1)
		TheInvoke00444E8ATarget->rva002233A6(1);
}

// 0x00444EC8 (149 bytes): the host left the LAN game: the +0x288 setup
// panel's 0x0043DC0F step, the same reset as 0x00444E8A, then the
// "GUI:HostLeftTitle" / "GUI:HostLeft" message box (Zero Hour's LAN
// host-left notice). Method name unrecovered.

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

class GameWindow;
void MessageBoxOk(UnicodeString titleString, UnicodeString bodyString, void (*okCallback)(void));

void AptLanLobby::rva00444EC8()
{
	m_panel.rva0043DC0F();
	rva004443E7();
	m_currentState = 0;
	void *owner = m_owner;
	TheInvoke00444E8ATarget->invoke(owner, "CancelGame", 0, 0, 0, 0, 0, 0);
	MessageBoxOk(TheGameText->fetch("GUI:HostLeftTitle"), TheGameText->fetch("GUI:HostLeft"), 0);
}
