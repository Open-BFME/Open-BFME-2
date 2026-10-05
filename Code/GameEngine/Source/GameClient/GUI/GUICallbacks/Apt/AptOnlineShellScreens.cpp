// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /G7 /EHsc
//
// BFME2's online shell Apt callbacks "AptOnline::ShellUnloadScreen",
// 0x005171A3, and "AptOnline::ShellLoadScreen", 0x00517724, bound by those
// names as member pointers by the shell's registration; that binding is
// their only reference. The class is named for the strings' prefix
// (AptOnlineShellCallbacks.cpp views the same object). The shell's Apt
// variables "OnlineShellStartScreen" and "OnlineAdvMode" share 0x00517207.

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

#include "ascii_string.h"

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

// The GameSpy misc preferences file and the UserPreferences members it
// keeps (all rowed).
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void setBool(const AsciiString &key, bool value);
	virtual bool write();
	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();

	unsigned char m_rest[0x14 - 0x04];
};

// The shell's sub-screens by name (0x00DD1568, ended by a null name): each
// is made by its factory and sets the shell's mode at +0x2B4.
struct AptOnlineScreenEntry
{
	const char *name;
	AptOnlineSubScreen *(*create)(AptOnline *shell);
	int mode;
};

extern AptOnlineScreenEntry g_Va00DD1568[];


// The sub-screens the shell's table makes, each by its unrowed constructor
// taking the shell (pinned by address; the classes keep those addresses).
// The guards are the screens' instances: a factory makes nothing while
// its screen is up.
class Rva005B8F69
{
public:
	Rva005B8F69(AptOnline *shell);

private:
	unsigned char m_pad[0x90];
};

extern void *g_Va00E06478;

class Rva00572885
{
public:
	Rva00572885(AptOnline *shell);

private:
	unsigned char m_pad[0xE0];
};

extern void *g_Va00E062EC;

class Rva005B9BBC
{
public:
	Rva005B9BBC(AptOnline *shell);

private:
	unsigned char m_pad[0x68];
};

extern void *g_Va00E06480;

class Rva005BA1FD
{
public:
	Rva005BA1FD(AptOnline *shell);

private:
	unsigned char m_pad[0x4E0];
};

class Rva005BA28E
{
public:
	Rva005BA28E(AptOnline *shell);

private:
	unsigned char m_pad[0x4E0];
};

class Rva005BAB7E
{
public:
	Rva005BAB7E(AptOnline *shell);

private:
	unsigned char m_pad[0xA0];
};

extern void *g_Va00E06550;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
	virtual void slot10(int value, int mode) = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class AptOnline
{
public:
	void ShellUnloadScreen(const char *name);
	void ShellLoadScreen(const char *name);
	void rva00517207(int query, char *value, bool set);
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
// TheGameSpyInfo's vslot 10.
void AptOnline::rva00516F08()
{
	if (TheGameSpyInfo)
		TheGameSpyInfo->slot10(1, m_mode);
}

// Retail 0x00517207, 263 bytes. Bound as the Apt variables
// "OnlineShellStartScreen" (0: the current sub-screen's name, read only)
// and "OnlineAdvMode" (1: the GameSpy misc preference "InAdvMode"), so it
// keeps its address.
void AptOnline::rva00517207(int query, char *value, bool set)
{
	if (!set)
		value[0] = 0;
	switch (query)
	{
	case 0:
		if (!set)
			strcpy(value, m_currentName.str());
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
			strcpy(value, prefs.getBool(AsciiString("InAdvMode"), false) ? "1" : "0");
		break;
	}
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")

// Retail 0x00516D09, 68 bytes: the shell table's factory for a new "Stats" sub-screen unless one is up (0x00E06478).
AptOnlineSubScreen *__cdecl Rva00516D09(AptOnline *shell)
{
	if (g_Va00E06478)
		return 0;
	return (AptOnlineSubScreen *)new Rva005B8F69(shell);
}

// Retail 0x00516D4D, 68 bytes: the shell table's factory for a new "OnlineLogin" sub-screen unless one is up (0x00E062EC).
AptOnlineSubScreen *__cdecl Rva00516D4D(AptOnline *shell)
{
	if (g_Va00E062EC)
		return 0;
	return (AptOnlineSubScreen *)new Rva00572885(shell);
}

// Retail 0x00516D91, 65 bytes: the shell table's factory for a new "OnlineHome" sub-screen unless one is up (0x00E06480).
// ?Rva00516D91@@YAPAUAptOnlineSubScreen@@PAVAptOnline@@@Z present-unmatched
AptOnlineSubScreen *__cdecl Rva00516D91(AptOnline *shell)
{
	if (g_Va00E06480)
		return 0;
	return (AptOnlineSubScreen *)new Rva005B9BBC(shell);
}

// Retail 0x00516DD2, 56 bytes: the shell table's factory for a new "OnlineOpenPlay" sub-screen.
// ?Rva00516DD2@@YAPAUAptOnlineSubScreen@@PAVAptOnline@@@Z present-unmatched
AptOnlineSubScreen *__cdecl Rva00516DD2(AptOnline *shell)
{
	return (AptOnlineSubScreen *)new Rva005BA1FD(shell);
}

// Retail 0x00516E10, 56 bytes: the shell table's factory for a new "OnlineStrategic" sub-screen.
// ?Rva00516E10@@YAPAUAptOnlineSubScreen@@PAVAptOnline@@@Z present-unmatched
AptOnlineSubScreen *__cdecl Rva00516E10(AptOnline *shell)
{
	return (AptOnlineSubScreen *)new Rva005BA28E(shell);
}

// Retail 0x00516E4E, 68 bytes: the shell table's factory for a new "OnlineQuickMatch" sub-screen unless one is up (0x00E06550).
// ?Rva00516E4E@@YAPAUAptOnlineSubScreen@@PAVAptOnline@@@Z present-unmatched
AptOnlineSubScreen *__cdecl Rva00516E4E(AptOnline *shell)
{
	if (g_Va00E06550)
		return 0;
	return (AptOnlineSubScreen *)new Rva005BAB7E(shell);
}
