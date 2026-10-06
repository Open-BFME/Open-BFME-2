// ?rva00579542@Rva005794ED@@UAEXXZ
// partial score=0.8 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005794ED@@UAE@XZ @0x005794ED 85B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x18.
// Evidence: deleting-dtor callers 0x0042D4EB 0x0042D7A3 0x0042D7C6 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ECBC 0x00C6EE28; prev Rva004FAC6BCtor.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

extern const void *const g_00C6ECBC[];
extern const void *const g_00C6EE28[];

class Rva005794EDBase
{
public:
	virtual ~Rva005794EDBase();
};

// ??1Rva005794EDBase@@UAE@XZ present-unmatched
inline Rva005794EDBase::~Rva005794EDBase()
{
	*(const void **)this = g_00C6EE28;
}

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	__forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }

	TargetRef00217D4C *m_ptr;
};

class __declspec(novtable) Rva005794ED : public Rva005794EDBase
{
public:
	virtual ~Rva005794ED();
	virtual void rva00579435(bool newState);
	virtual void PlayAlertFlash();
	virtual void HaltAlertFlash();
	virtual void rva00579542();
	void OnClicked(const char *unused);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	TreeHintRef00217D4C m_18;
	bool m_1C;
};

Rva005794ED::~Rva005794ED()
{
	*(const void **)this = g_00C6ECBC;
}

// The +0x18 holder's action, rowed at 0x0044BD79.
class BfmeA1042N
{
public:
	void bfmeGo1042D();
};

// ?OnClicked@Rva005794ED@@QAEXPBD@Z @0x005794DD 16B: the button's
// "_level%u." + path + "_OnClicked" delegate, bound by the constructor
// 0x00579575; fires the +0x18 target when one is set.
void Rva005794ED::OnClicked(const char *unused)
{
	if (m_18.m_ptr != 0)
		((BfmeA1042N *)&m_18)->bfmeGo1042D();
}

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

static __forceinline const char *Rva005794EDGetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

void Rva005794ED::rva00579435(bool newState)
{
	if (newState == m_1C)
		return;
	const char *state = newState ? "_up" : "_disabled";
	const char *prefix = Rva005794EDGetStr(m_08);
	Rva0050E9FEAptCall(TheRva00222A8BTarget, (void *)m_04, prefix, "SetState", &state);
	m_1C = newState;
}

// ?PlayAlertFlash@Rva005794ED@@UAEXXZ @0x0057948B 41B: vtable slot 2;
// calls the movie's "PlayAlertFlash".
void Rva005794ED::PlayAlertFlash()
{
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_04, Rva005794EDGetStr(m_08), "PlayAlertFlash");
}

// ?HaltAlertFlash@Rva005794ED@@UAEXXZ @0x005794B4 41B: vtable slot 3;
// calls the movie's "HaltAlertFlash".
void Rva005794ED::HaltAlertFlash()
{
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_04, Rva005794EDGetStr(m_08), "HaltAlertFlash");
}

// ?rva00579542@Rva005794ED@@UAEXXZ @0x00579542 43B: vtable slot 6; empties
// the +0x18 target (slot 5 0x0057956D assigns it). Retail registers the
// temporary's unwind (out-of-line dtor 0x005F8F96) but never runs its inline
// release on the normal path; cl 13.10 here reloads and tests the temporary.
void Rva005794ED::rva00579542()
{
	m_18 = TreeHintRef00217D4C();
}
