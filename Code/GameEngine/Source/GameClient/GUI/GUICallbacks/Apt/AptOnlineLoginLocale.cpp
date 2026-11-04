// cl: /DNDEBUG /MD
// stlport
// BFME2's online login screen Apt callback "AptOnline::Login::AcceptLocale",
// 0x00572571, bound by that name as a member pointer by the screen's
// registration; that binding is its only reference. Unlike the link
// buttons (AptOnlineLoginCallbacks.cpp, built without EH) its unit keeps
// an EH frame for the preferences local, and it is built /G7 (the byte
// flag goes out as mov al without the P6 xor).

class GameWindow;

void GadgetListBoxGetSelected(GameWindow *listBox, int *selected);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

#include "../../../../../Include/Common/UserPreferences.h"
#include "../../../../../Include/Common/GameSpyMiscPreferencesClass.h"

#include "../../../../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The login screen instance (AptOnlineLogin.cpp's g_Va00E062EC); its
// recovered 0x0057179D takes the screen's byte flag.
class AptOnlineLogin
{
public:
	void rva0057179D(bool flag);
};

class BfmeObjELB; extern BfmeObjELB *g_bfmeObjELB;

// Set when no locale is selected.
// Retail loader-zeroed byte at VA 0x00E062F0; one owner for the flag.
bool g_Va00E062F0 = false;

struct AptOnlineLoginOwner
{
public:
	char m_pad00[0x274];
	void *movie; // +0x274
};

namespace AptOnline
{
class Login
{
public:
	void AcceptLocale(const char *unused);

private:
	unsigned char m_pad000[0x58];
	AptOnlineLoginOwner *m_owner; // +0x58
	unsigned char m_pad05c[0xB8 - 0x5C];
	GameWindow *m_locales; // +0xB8
	unsigned char m_pad0bc[0xD0 - 0xBC];
	bool m_d0; // +0xD0
	unsigned char m_pad0d1[0xD4 - 0xD1];
	int m_locale; // +0xD4
};
}

// Retail 0x00572571, 193 bytes: "AptOnline::Login::AcceptLocale" saves the
// selected locale (or flags that none was chosen), tells the movie
// "DoCloseLocale" and hands the screen's flag on.
void AptOnline::Login::AcceptLocale(const char *unused)
{
	int selected = -1;
	GadgetListBoxGetSelected(m_locales, &selected);
	if (selected >= 0)
	{
		m_locale = (int)GadgetListBoxGetItemData(m_locales, selected, 0);
		GameSpyMiscPreferences prefs;
		prefs.rva005597CB(m_locale);
		prefs.write();
	}
	else
		g_Va00E062F0 = true;
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_owner->movie, "CallChild", 1, "DoCloseLocale", 0, 0, 0, 0);
	((AptOnlineLogin *)(*(int *)&g_bfmeObjELB))->rva0057179D(m_d0);
}
