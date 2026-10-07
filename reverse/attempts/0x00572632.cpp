// ?rva00572632@Login@AptOnline@@QAEXPBD@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva00572632@Login@AptOnline@@QAEXPBD@Z @ 0x00572632 (310B).
// Same Login owner layout as AptOnlineLoginLocale.cpp; target's DoOpenLocale
// and DisableButton* calls identify the callback behavior, not its source name.

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
	virtual bool write();
	int rva00559782();
	unsigned char m_rest[0x14 - 0x04];
};

class BfmeObjELB
{
public:
	void bfmeTailELB(int flag);
};

extern BfmeObjELB *g_bfmeObjELB;

class Rva0056DCBFTarget
{
public:
	void rva0056DCBF(bool flag);
};

class BfmeAptWindowManager
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value,
		void *a4, void *a5, void *a6, void *a7);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern Rva0056DCBFTarget *TheRva0056DCBFTarget;

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value,
		void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct AptOnlineLoginOwner
{
	unsigned char pad[0x274];
	void *movie;
};

namespace AptOnline
{
class Login
{
public:
	void rva00572632(const char *unused);

private:
	unsigned char pad000[0x58];
	AptOnlineLoginOwner *owner;
	unsigned char pad05c[0xD0 - 0x5C];
	bool m_d0;
	unsigned char pad0d1[3];
	int m_locale;
};
}

void AptOnline::Login::rva00572632(const char *unused)
{
	if (g_bfmeObjELB != 0) {
		g_bfmeAptWindowManager->invoke(owner->movie, "CallChild", 1,
			"DisableButtonDeleteNickname", 0, 0, 0, 0);
		g_bfmeAptWindowManager->invoke(owner->movie, "CallChild", 1,
			"DisableButtonCreate", 0, 0, 0, 0);
		g_bfmeAptWindowManager->invoke(owner->movie, "CallChild", 1,
			"DisableButtonLogin", 0, 0, 0, 0);
		g_bfmeAptWindowManager->invoke(owner->movie, "CallChild", 1,
			"DisableButtonServiceTerms", 0, 0, 0, 0);
		GameSpyMiscPreferences prefs;
		if (prefs.rva00559782() >= 1 && prefs.rva00559782() <= 0x25) {
			m_locale = prefs.rva00559782();
			g_bfmeObjELB->bfmeTailELB(0);
		} else {
			m_d0 = false;
			g_bfmeAptWindowManager->invoke(owner->movie, "CallChild", 1,
				"DoOpenLocale", 0, 0, 0, 0);
			TheRva0056DCBFTarget->rva0056DCBF(false);
		}
	}
}
