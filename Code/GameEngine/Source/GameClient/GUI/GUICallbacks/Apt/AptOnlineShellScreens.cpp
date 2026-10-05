// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /G7
//
// BFME2's online shell Apt callbacks "AptOnline::ShellUnloadScreen",
// 0x005171A3, and "AptOnline::ShellLoadScreen", 0x00517724, bound by those
// names as member pointers by the shell's registration; that binding is
// their only reference. The class is named for the strings' prefix
// (AptOnlineShellCallbacks.cpp views the same object).

extern "C" int __cdecl strcmp(const char *left, const char *right);

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

// The shell's sub-screens by name (0x00DD1568, ended by a null name): each
// is made by its factory and sets the shell's mode at +0x2B4.
struct AptOnlineScreenEntry
{
	const char *name;
	AptOnlineSubScreen *(*create)(AptOnline *shell);
	int mode;
};

extern AptOnlineScreenEntry g_Va00DD1568[];

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
// ?ShellLoadScreen@AptOnline@@QAEXPBD@Z present-unmatched
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
