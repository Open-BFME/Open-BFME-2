// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BFME2's lobby clans panel (the MpGameSetup panel's +0x190 member) Apt
// callbacks "AptMpClans::WebSite" (0x0057F41A) and "AptMpClans::InitGadgets"
// (0x0057F9A3), bound by those names as member pointers by the panel's
// registration 0x0057FAB0; that binding is their only reference. The class
// is named for the strings' prefix.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *window, const unsigned short *operation, const unsigned short *file, const unsigned short *parameters, const unsigned short *directory, int show);

class GameWindow;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void bfmeMinimizeCurrentThreadWindow();
void GadgetListBoxSetColumnWidths(GameWindow *listBox, int columns, int *widths);

class AptMpClans
{
public:
	void WebSite(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

	// Unrowed 0x0057F7AC (372 bytes; sets the clan name text) and the
	// player list refill 0x0057F5ED, pinned by address.
	void rva0057F7AC(const UnicodeString &name);
	void rva0057F5ED();

private:
	unsigned char m_pad000[0xA0];
	GameWindow *m_clanName; // +0xA0
	GameWindow *m_clanPlayers; // +0xA4
};

// Retail 0x0057F41A, 108 bytes: "AptMpClans::WebSite" opens the localized
// URL:ClanWarsHome in Internet Explorer and minimizes the game window.
void AptMpClans::WebSite(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:ClanWarsHome");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}

// Retail 0x0057F9A3, 121 bytes: "AptMpClans::InitGadgets" keeps the
// "ClanPlayers" list box (two columns, 65 and 35 wide) and the "ClanName"
// window, clearing and refilling the latter's panel.
void AptMpClans::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (strcmp(name, "ClanPlayers") == 0)
	{
		int widths[2];
		widths[0] = 65;
		widths[1] = 35;
		GadgetListBoxSetColumnWidths(window, 2, widths);
		m_clanPlayers = window;
	}
	else if (strcmp(name, "ClanName") == 0)
	{
		m_clanName = window;
		rva0057F7AC(UnicodeString::TheEmptyString);
		rva0057F5ED();
	}
}
