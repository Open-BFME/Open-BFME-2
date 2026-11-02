// cl: /DNDEBUG /MD /EHsc
//
// Four LANAPI virtuals (vtable 0x00C3E680) that BFME2 reduces to calls on the
// LAN lobby screen singleton AptLanLobby::s_instance at VA 0x00E03354 where Zero Hour updates its
// windows directly. Zero Hour's response handlers follow
// ResetGameStartTimer (slot 31) in this table as they do upstream, and
// OnPlayerJoin (35), OnAccept (38), OnGameCreate (47) and OnNameChange (48)
// already land at their upstream positions, so:
//
//   slot 32  0x00248E6F  OnGameList(gameList): while in the lobby, hands the
//            list to the menu (0x00445E3E) where Zero Hour calls
//            LANDisplayGameList.
//   slot 33  0x00248E87  no arguments (plain ret) although Zero Hour's slot
//            here is OnPlayerList(LANPlayer *); calls 0x00381900 with 1 and
//            then 0. Address-named.
//   slot 36  0x00248E41  OnHostLeave: out of the lobby with a current game,
//            the menu (0x00444EC8) handles it when present; otherwise the
//            shell pops (Shell 0x0035BEC7) and LANbuttonPushed is set.
//   slot 61  0x00248E2F  BFME2-only; hands its Bool to the menu (0x0044446D).
//
// The menu's methods and 0x00381900 are not identified (address names).

typedef bool Bool;
typedef int Int;

class LANGameInfo;

struct Rva004469D1Receiver
{
	void rva0044446D(Bool value);
};

// Rows 0x00444EC8 and 0x00445E3E are AptLanLobby members.
class AptLanLobby
{
	static AptLanLobby *s_instance;
public:
	static AptLanLobby *Instance() { return s_instance; }
	void rva00445E3E(LANGameInfo *gameList);
	void rva00444EC8();
};

#include "../../Include/GameClient/Shell.h"
extern Shell *TheShell;

extern Bool LANbuttonPushed;

void Rva00381900(Int value);

class LANAPI
{
public:
	virtual void OnGameList(LANGameInfo *gameList);
	virtual void rva00248E87();
	virtual void OnHostLeave();
	virtual void rva00248E2F(Bool value);

protected:
	unsigned char m_unmodelled_04[0x41 - 0x04];
	Bool m_inLobby;								// +0x41
	unsigned char m_unmodelled_42[0x44 - 0x42];
	LANGameInfo *m_currentGame;					// +0x44
};

void LANAPI::rva00248E2F(Bool value)
{
	if (AptLanLobby::Instance())
		((Rva004469D1Receiver *)AptLanLobby::Instance())->rva0044446D(value);
}

void LANAPI::OnHostLeave()
{
	if (m_inLobby || !m_currentGame)
		return;
	if (!AptLanLobby::Instance())
	{
		TheShell->pop();
		LANbuttonPushed = true;
	}
	else
	{
		AptLanLobby::Instance()->rva00444EC8();
	}
}

void LANAPI::OnGameList(LANGameInfo *gameList)
{
	if (m_inLobby && AptLanLobby::Instance())
		AptLanLobby::Instance()->rva00445E3E(gameList);
}

void LANAPI::rva00248E87()
{
	Rva00381900(1);
	Rva00381900(0);
}
