// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva005AE30A@@QAE@PAX@Z
// retail 0x005AE3A6..0x005AE4E5 (319 bytes) thiscall RET 4.
//
// The LAN messenger screen's constructor, the sibling of
// AptMessengerOnline::AptMessengerOnline (AptMessengerOnlineConstructor.cpp):
// it runs the AptMessenger constructor (pinned 0x0051215B), installs the
// vftables 0x00C726A0/0x00C7269C that the rowed destructor 0x005AE30A
// (Rva005AE30ADtor.cpp) and the scalar deleting destructor 0x005AE38A
// restore, sets its flag at +0x2A0 and titles the messenger tabs
// "APT:MessengerTab0" with "APT:LanEveryoneTab", "APT:MessengerTab1" with
// "APT:LanPlayersTab" and "APT:CurrentLobbyName" with "APT:LobbyRoom"
// through TheGameText->fetch (vslot 15) and the rowed
// BfmeAptWindowManager::bfmeSetText 0x00225301. WorldBuilder's twin
// 0x01514A00 is unnamed and has the same statements; the only caller is
// 0x00511523. The class keeps the destructor's address-derived name.
#include "unicode_string.h"
#include "ascii_string.h"

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char m_pad004[0x58 - 0x04];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class AptMessenger : public _bfme_AptGameWindow
{
public:
	AptMessenger(void *context);
	virtual ~AptMessenger();
private:
	unsigned char m_pad27C[0x2A0 - 0x27C];
};

class Rva005AE30A : public AptMessenger
{
public:
	Rva005AE30A(void *context);
	virtual ~Rva005AE30A();
private:
	bool m_2A0;
};

Rva005AE30A::Rva005AE30A(void *context)
	: AptMessenger(context),
	  m_2A0(true)
{
	{
		AsciiString window("APT:MessengerTab0");
		g_bfmeAptWindowManager->bfmeSetText(window, TheGameText->fetch("APT:LanEveryoneTab"), false);
	}
	{
		AsciiString window("APT:MessengerTab1");
		g_bfmeAptWindowManager->bfmeSetText(window, TheGameText->fetch("APT:LanPlayersTab"), false);
	}
	{
		AsciiString window("APT:CurrentLobbyName");
		g_bfmeAptWindowManager->bfmeSetText(window, TheGameText->fetch("APT:LobbyRoom"), false);
	}
}
