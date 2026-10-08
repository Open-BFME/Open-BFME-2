// cl: /DNDEBUG /MD
//
// BFME2's online login screen Apt callback "AptOnline::Login::AcceptLocale",
// 0x00572571, bound by that name as a member pointer by the screen's
// registration; that binding is its only reference. Unlike the link
// buttons (AptOnlineLoginCallbacks.cpp, built without EH) its unit keeps
// an EH frame for the preferences local, and it is built /G7 (the byte
// flag goes out as mov al without the P6 xor).

class GameWindow;

void GadgetListBoxGetSelected(GameWindow *listBox, int *selected);
int Rva003253BEGet(GameWindow *listBox, int row, int column);

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool write();
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();

	// Rowed 0x005597CB (stores the locale).
	void rva005597CB(int locale);

	unsigned char m_rest[0x14 - 0x04];
};

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The login screen instance (Rva0056E79EDtor.cpp's g_Va00E062EC); its
// recovered 0x0057179D takes the screen's byte flag.
class AptOnlineLogin
{
public:
	void rva0057179D(bool flag);
};

extern int g_Va00E062EC;

// Set when no locale is selected.
extern bool g_Va00E062F0;

struct AptOnlineLoginOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
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
		m_locale = Rva003253BEGet(m_locales, selected, 0);
		GameSpyMiscPreferences prefs;
		prefs.rva005597CB(m_locale);
		prefs.write();
	}
	else
		g_Va00E062F0 = true;
	TheRva00222A8BTarget->invoke(m_owner->m_movie, "CallChild", 1, "DoCloseLocale", 0, 0, 0, 0);
	((AptOnlineLogin *)g_Va00E062EC)->rva0057179D(m_d0);
}
