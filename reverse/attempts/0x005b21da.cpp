// ?M3@Rva005B5C70Sub@@QAEXPAURva005B5C70Entry@@HH@Z
// partial score=0.98 date=2026-10-07
// cl: -Oy- -GR- -EHsc- /Ireference/shims/bfme2_ascii
// ?Run@Rva005B5C70Box@@QAEXH@Z @0x005B5C70 132B: flagged entry apply.
// Resolves the selected index through the rowed GetSelected, fetches the
// entry through the rowed 3-arg getter, runs the pinned 3-arg consumer on
// the +0x27C sub-object with the (a != 0) flag, stamps the byte +0x14, and
// unless a set +0x48 entry meets a cleared global, fires the rowed UI
// callback with the out-bool d. Rowed callees by matched names; the middle
// params are unused padding. Targets from retail REL32/DIR32.
#include "ascii_string.h"

class GameWindow;
void __cdecl GadgetListBoxGetSelected(GameWindow *w, int *sel);
int __cdecl Rva003253BEGet(GameWindow *w, int a, int b);
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_rva005B5C70Str[];
extern unsigned char g_rva005B5C02Flag;
void __cdecl Rva004E6816Fire(Rva00222A8BTarget *t, void *p, const char *s, bool *b);

struct Rva005B5C70Entry
{
	char pad[0x48];
	unsigned char m_48;

	void M3(struct Rva005B5C70Obj *o, int z, int f);
};

struct Rva005B5C70Sub
{
	char m_pad00[0x144];
	Rva005B5C70Entry *m_144;
	unsigned char m_148;
	char m_pad149[3];
	int m_14c;
	char m_pad150[0x3c];
	int m_18c;

	void M3(Rva005B5C70Entry *e, int z, int f);
};

struct Rva005B5C70Mid
{
	char pad[0x274];
	void *m_274;
};

struct Rva005B5C70Box
{
	char pad[4];
	Rva005B5C70Mid *m_4;
	GameWindow *m_8;
	char pad2[0x14 - 0xc];
	unsigned char m_14;

	void Run(int a);
};

void Rva005B5C70Box::Run(int a)
{
	int r;
	GadgetListBoxGetSelected(m_8, &r);
	Rva005B5C70Entry *e = (Rva005B5C70Entry *)Rva003253BEGet(m_8, r, 0);
	if (e == 0)
		return;
	Rva005B5C70Sub *s = (Rva005B5C70Sub *)m_4;
	int flag = (((unsigned char *)&a)[0] != 0);
	s = (Rva005B5C70Sub *)((char *)s + 0x27c);
	s->M3(e, 0, flag);
	m_14 = 1;
	if (e->m_48 == 0)
		((unsigned char *)&a)[3] = 1;
	else {
		((unsigned char *)&a)[3] = 0;
		if (g_rva005B5C02Flag != 0)
			((unsigned char *)&a)[3] = 1;
	}
	Rva004E6816Fire(TheRva00222A8BTarget, m_4->m_274, g_rva005B5C70Str, (bool *)&((unsigned char *)&a)[3]);
}

// Retail 0x005B21DA (187 bytes), called by Run through the +0x27C view.
// The caller's REL32 supports the M3 wrapper spelling and three-argument ABI;
// the manager/display/transition and window-manager accesses below follow the
// target body. The +0x1E8 manager string and the transition vtable slot remain
// address-derived structural views.
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;
class Display;
extern Display *TheDisplay;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, bool immediate);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

struct Rva005B21DATransitionVtable
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void releaseGroups(); // verified GameWindowTransitionsHandler slot 9
};

struct Rva005B21DAWindowManagerVtable
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
};

class Rva005B1E71
{
public:
	void rva005B1E71();
};

class Rva001DBB82OneSetter
{
public:
	void enable();
};

void Rva005B5C70Sub::M3(Rva005B5C70Entry *e, int z, int f)
{
	if (m_144 == e)
		return;
	m_144 = e;
	m_148 = (unsigned char)z;
	m_18c = 0;

	if (((const AsciiString *)((const char *)TheCreateAHeroManager + 0x1e8))->isEmpty())
		f = 0;

	switch (f) {
	case 1:
		((unsigned char *)TheDisplay)[0x141] = 1;
		((Rva005B21DATransitionVtable *)TheTransitionHandler)->releaseGroups();
		TheTransitionHandler->setGroup(*(const AsciiString *)((const char *)TheCreateAHeroManager + 0x1e8), false);
		((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
		((Rva005B21DAWindowManagerVtable *)TheWindowManager)->slot10();
		m_14c = 1;
		break;

	case 0:
		((Rva005B1E71 *)this)->rva005B1E71();
		m_14c = 0;
		break;
	}
}
