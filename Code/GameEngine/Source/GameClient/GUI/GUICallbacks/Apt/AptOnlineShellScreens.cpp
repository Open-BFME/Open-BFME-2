// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// BFME2's online shell Apt callbacks "AptOnline::ShellUnloadScreen",
// 0x005171A3, and "AptOnline::ShellLoadScreen", 0x00517724, bound by those
// names as member pointers by the shell's registration; that binding is
// their only reference. The class is named for the strings' prefix
// (AptOnlineShellCallbacks.cpp views the same object). The shell's Apt
// variables "OnlineShellStartScreen" and "OnlineAdvMode" share 0x00517207.

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include "ascii_string.h"
#include <string.h>

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	// The pointer vectors' shared erase 0x001FF51F and push_back
	// 0x004DFCB0 (both rowed under other element types).
	T *erase(T *position);
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// A loaded sub-screen: its name at +0x5C, deleted through vslot 0 and a
// separate operator delete (AnimateWindowManager.cpp's spelling).
struct AptOnlineSubScreen
{
	virtual void *deleteInstance(int flags);
	virtual void v1();
	virtual void v2();

	unsigned char m_pad04[0x5C - 0x04];
	const char *m_name; // +0x5C
};

class AptOnline;

#include "../../../../../Include/Common/UserPreferences.h"
#include "../../../../../Include/Common/GameSpyMiscPreferencesClass.h"

// The shell's sub-screens by name (0x00DD1568, ended by a null name): each
// is made by its factory and sets the shell's mode at +0x2B4.
struct AptOnlineScreenEntry
{
	const char *name;
	AptOnlineSubScreen *(*create)(AptOnline *shell);
	int mode;
};



// The sub-screens the shell's table makes, each by its constructor taking
// the shell. Unrecovered screen identities keep their address names.
// The guards are the screens' instances: a factory makes nothing while
// its screen is up.
class Rva005B8F69
{
public:
	Rva005B8F69(AptOnline *shell);

private:
	unsigned char m_pad[0x90];
};

// The matched Stats destructor owns this singleton; only its nullness is used here.
class Rva005B7FA4;
extern Rva005B7FA4 *g_00E06478;

class AptOnlineLogin
{
public:
	AptOnlineLogin(AptOnline *shell);
	static AptOnlineSubScreen *Create(AptOnline *shell);

private:
	unsigned char m_pad[0xE0];
};

// The constructor's existing singleton owner, also used by AptOnlineLogin.cpp.
class BfmeObjELB;
extern BfmeObjELB *g_bfmeObjELB;

// Opaque singleton state owned by ColdGlobalDwordGetters.cpp; used only as a zero test.
extern int g_Va00E06480;

// The OpenPlay (0x005BA1FD) and Strategic (0x005BA28E) constructors are
// rowed taking the shell as an int (Rva005BA1FDCtor.cpp).
class AptOnlineOpenPlay
{
public:
	AptOnlineOpenPlay(int shell);

private:
	unsigned char m_pad[0x4E0];
};

class Rva005BA28E
{
public:
	Rva005BA28E(int shell);

private:
	unsigned char m_pad[0x4E0];
};

extern int g_Va00E06550;

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

class AptOnline
{
public:
	class OnlineHome;
	class OnlineQuickMatch;

	void ShellUnloadScreen(const char *name);
	void ShellLoadScreen(const char *name);
	void ExternFunc(int query, char *value, bool set);
	void rva00516F08();

private:
	unsigned char m_pad000[0x280];
	_STL::vector<AptOnlineSubScreen *, _STL::allocator<AptOnlineSubScreen *> > m_screens; // +0x280
	unsigned char m_pad28c[0x290 - 0x28C];
	AptOnlineSubScreen *m_current; // +0x290
	AsciiString m_currentName; // +0x294
	unsigned char m_pad298[0x2B4 - 0x298];
	int m_mode; // +0x2B4
};

// The Home (0x005B9BBC) and QuickMatch (0x005BAB7E) constructors are rowed
// under these nested names (AptOnlineHomeConstructor.cpp,
// AptOnlineQuickMatchConstructor.cpp).
class AptOnline::OnlineHome
{
public:
	OnlineHome(AptOnline *shell);

private:
	unsigned char m_pad[0x68];
};

class AptOnline::OnlineQuickMatch
{
public:
	OnlineQuickMatch(AptOnline *shell);

private:
	unsigned char m_pad[0xA0];
};

// The table's factories, defined below; the table precedes its walker.
class AptOnlineHome
{
public:
	static AptOnlineSubScreen *Create(AptOnline *shell);
};
AptOnlineSubScreen *__cdecl Rva00516D09(AptOnline *shell);
AptOnlineSubScreen *__cdecl Rva00516DD2(AptOnline *shell);
AptOnlineSubScreen *__cdecl Rva00516E10(AptOnline *shell);
AptOnlineSubScreen *__cdecl Rva00516E4E(AptOnline *shell);
// 0x00DD1568: the shell's sub-screen table, seven 12-byte entries ending in
// a null name, as retail's .data holds them (names 0x00C663B0/A4/90/80/70
// and 0x00BE6390, factories 0x00516D4D/91, 0x00516E4E, 0x00516DD2,
// 0x00516E10 and 0x00516D09, modes 0/4/3/1/2/5). No other unit defines it.
AptOnlineScreenEntry g_Va00DD1568[] =
{
	{ "OnlineLogin", &AptOnlineLogin::Create, 0 },
	{ "OnlineHome", &AptOnlineHome::Create, 4 },
	{ "OnlineQuickMatch", &Rva00516E4E, 3 },
	{ "OnlineOpenPlay", &Rva00516DD2, 1 },
	{ "OnlineStrategic", &Rva00516E10, 2 },
	{ "Stats", &Rva00516D09, 5 },
	{ 0, 0, 0 }
};

// Retail 0x005171A3, 100 bytes: "AptOnline::ShellUnloadScreen" deletes the
// loaded sub-screen with that name.
void AptOnline::ShellUnloadScreen(const char *name)
{
	for (AptOnlineSubScreen **it = m_screens.m_start; it != m_screens.m_finish; ++it)
	{
		AptOnlineSubScreen *screen = *it;
		const char *screenName = screen->m_name;
		if (strcmp(screenName, name) == 0)
		{
			if (m_current == screen)
				m_current = 0;
			::operator delete(screen->deleteInstance(0));
			m_screens.erase(it);
			return;
		}
	}
}

// Retail 0x00517724, 197 bytes: "AptOnline::ShellLoadScreen" replaces the
// current sub-screen with a new one of that name, keeps it, and for the
// GameSpy modes 3 to 5 tells GameSpy (0x00516F08).
void AptOnline::ShellLoadScreen(const char *name)
{
	if (m_current)
	{
		m_current->v2();
		m_current = 0;
	}
	int i = 0;
	const char *screenName = g_Va00DD1568[0].name;
	while (screenName)
	{
		if (strcmp(screenName, name) == 0)
		{
			m_current = g_Va00DD1568[i].create(this);
			if (!m_current)
				return;
			m_current->v1();
			m_current->m_name = screenName;
			m_currentName = screenName;
			m_mode = g_Va00DD1568[i].mode;
			m_screens.push_back(m_current);
			if (TheGameSpyInfo && m_mode >= 3 && m_mode <= 5)
				rva00516F08();
			return;
		}
		screenName = g_Va00DD1568[++i].name;
	}
}

// Retail 0x00516F08, 25 bytes. Name unknown: hands the shell's mode to
// TheGameSpyInfo->joinPreferredGroupRoom (vslot 10).
void AptOnline::rva00516F08()
{
	if (TheGameSpyInfo)
		TheGameSpyInfo->joinPreferredGroupRoom(true, m_mode);
}

// Retail 0x00517207, 263 bytes. Bound as the Apt variables
// "OnlineShellStartScreen" (0: the current sub-screen's name, read only)
// and "OnlineAdvMode" (1: the GameSpy misc preference "InAdvMode"), so it
// keeps its address.
void AptOnline::ExternFunc(int query, char *value, bool set)
{
	if (!set)
		value[0] = 0;
	switch (query)
	{
	case 0:
		if (!set)
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_currentName.str()));
		break;
	case 1:
	{
		GameSpyMiscPreferences prefs;
		if (set)
		{
			prefs.setBool(AsciiString("InAdvMode"), value[0] == '1' || value[0] == 't');
			prefs.write();
		}
		else
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(prefs.getBool(AsciiString("InAdvMode"), false) ? "1" : "0"));
		break;
	}
	}
}

// Retail 0x00516D09, 68 bytes: the shell table's factory for a new "Stats" sub-screen unless one is up (0x00E06478).
AptOnlineSubScreen *__cdecl Rva00516D09(AptOnline *shell)
{
	if (g_00E06478)
		return 0;
	return (AptOnlineSubScreen *)new Rva005B8F69(shell);
}

// Retail 0x00516D4D, 68 bytes. WB 0x0145ADC0 names AptOnlineLogin::Create
// in AptOnlineLogin.h; the shell table's OnlineLogin entry and the call to
// the recovered constructor 0x00572885 independently establish its role.
AptOnlineSubScreen *AptOnlineLogin::Create(AptOnline *shell)
{
	if (g_bfmeObjELB)
		return 0;
	return (AptOnlineSubScreen *)new AptOnlineLogin(shell);
}

// Retail 0x00516D91, 65 bytes: the shell table's factory for a new "OnlineHome" sub-screen unless one is up (0x00E06480).
// WorldBuilder AptOnlineHome::Create, WB VA 0x0145AED0 (callgraph lead, score 1.0).
AptOnlineSubScreen *__cdecl AptOnlineHome::Create(AptOnline *shell)
{
	if (g_Va00E06480)
		return 0;
	return (AptOnlineSubScreen *)new AptOnline::OnlineHome(shell);
}

// Retail 0x00516DD2, 56 bytes: the shell table's factory for a new "OnlineOpenPlay" sub-screen.
AptOnlineSubScreen *__cdecl Rva00516DD2(AptOnline *shell)
{
	return (AptOnlineSubScreen *)new AptOnlineOpenPlay((int)shell);
}

// Retail 0x00516E10, 56 bytes: the shell table's factory for a new "OnlineStrategic" sub-screen.
AptOnlineSubScreen *__cdecl Rva00516E10(AptOnline *shell)
{
	return (AptOnlineSubScreen *)new Rva005BA28E((int)shell);
}

// Retail 0x00516E4E, 68 bytes: the shell table's factory for a new "OnlineQuickMatch" sub-screen unless one is up (0x00E06550).
AptOnlineSubScreen *__cdecl Rva00516E4E(AptOnline *shell)
{
	if (g_Va00E06550)
		return 0;
	return (AptOnlineSubScreen *)new AptOnline::OnlineQuickMatch(shell);
}

