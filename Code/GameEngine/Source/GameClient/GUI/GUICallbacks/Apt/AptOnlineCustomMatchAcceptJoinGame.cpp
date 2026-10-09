// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?AcceptJoinGame@AptOnlineCustomMatch@@QAEXPBD@Z retail 0x005A5632..0x005A57BA
// (392 bytes). The screen's registration binds this body as
// "AptOnline::CustomMatch::AcceptJoinGame" (string VA 0x00C719B0 next to the
// address 0x009A5632 at 0x005A5E41); the screen's message handler also calls
// it directly in state 10 (0x005A65D3). WorldBuilder twin 0x014ED470.
// In the join-password state (+0x488 == 10) it reads the password entry
// (+0x49C) through the rowed GadgetTextEntryGetText, closes the pop-up
// (+0x4A0) and disables both pop-up windows (+0x498 and +0x49C). An empty
// password or a vanished game (rowed GetGameToJoin) closes the movie's
// password box ("ClosePassword") and reports GUI:JoinFailedBadPassword or
// GUI:HostLeft under GUI:JoinFailedDefault through the rowed GSMessageBoxOk;
// otherwise it requests the join (rowed RequestJoinGame) and closes the
// password overlay (pinned GameSpyCloseOverlay 0x00548B97 with 5).
#include "ascii_string.h"
#include "unicode_string.h"

class GameWindow
{
public:
	int winEnable(bool enable);
};

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0); // slot 15
};

extern GameTextInterface *TheGameText;

typedef void (*GameWinMsgBoxFunc)(void);
void GSMessageBoxOk(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc okFunc);

enum GSOverlayType
{
	GSOVERLAY_GAMEPASSWORD = 5
};
void GameSpyCloseOverlay(GSOverlayType overlay);

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
};

class GameSpyStagingRoom;

class AptOnlineCustomMatch
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	// vslot 10: the screen's Apt path for its callbacks.
	virtual const char *v10();

	void AcceptJoinGame(const char *unused);
	GameSpyStagingRoom *GetGameToJoin();
	bool RequestJoinGame(const char *password);

private:
	__forceinline void closePasswordBox()
	{
		void *movie = m_owner->m_movie;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "ClosePassword");
	}

	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x488 - 0x5C];
	int m_state; // +0x488
	unsigned char m_pad48c[0x498 - 0x48C];
	GameWindow *m_passwordPopUp; // +0x498
	GameWindow *m_passwordEntry; // +0x49C
	bool m_popUp; // +0x4A0
};

void AptOnlineCustomMatch::AcceptJoinGame(const char *unused)
{
	if (m_state != 10)
		return;

	AsciiString password(GadgetTextEntryGetText(m_passwordEntry));
	m_popUp = false;
	m_passwordPopUp->winEnable(false);
	m_passwordEntry->winEnable(false);
	if (password.isEmpty())
	{
		closePasswordBox();
		m_state = 1;
		GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), TheGameText->fetch("GUI:JoinFailedBadPassword"), 0);
		return;
	}
	GameSpyStagingRoom *room = GetGameToJoin();
	if (room == 0)
	{
		closePasswordBox();
		m_state = 1;
		GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), TheGameText->fetch("GUI:HostLeft"), 0);
		return;
	}
	RequestJoinGame(password.str());
	GameSpyCloseOverlay(GSOVERLAY_GAMEPASSWORD);
}
