// cl: /EHsc /MD
// platformsdk
// stlport
//
// ?rva00405C04@Rva00405A50@@QAEXPAVBfmeThingGX@@@Z @0x00405C04 (371B, RET 4):
// shows a timed hint on the owner of the rowed 0x00405A50 (same +0x2A4
// holder, same EH thunk 0x00B84F02 as 0x00405AC9). Target facts: it bails
// while TheInGameUI slot 0x1BC holds or TheScriptEngine +0x1A104 is set;
// a function-local timeGetTime stamp (guard 0x00E02F60) and a pending byte
// 0x00E02F58 time the current hint; the same hint (bfmeSameGX) only
// refreshes once its slot-2 duration has run out, while a new one replaces
// the held hint (slot 1 hands over an owning pointer; 0x00405AC9 stores it)
// unless the radar override source is missing or its 0x002D36D8 test is
// set: then the holder is cleared (0x000AD6F4) and the override reset
// (0x002D370A). The pending byte defers a still-running repeat to 0x00405A50. The WorldBuilder twin
// 0x01079F10 has the same calls; owner and method names stay address-derived.

// The hint's slot 1 hands over an owning STLport auto_ptr; passing that
// temporary on by value goes through auto_ptr_ref as retail does.
#include <windows.h>
#include <memory>
class BfmeThingGX
{
public:
	virtual ~BfmeThingGX();
	virtual std::auto_ptr<BfmeThingGX> clone();	// +0x04
	virtual unsigned int getDuration();		// +0x08
};

int bfmeSameGX(BfmeThingGX *left, BfmeThingGX *right);

// The +0x2A4 owning holder (rowed clear 0x000AD6F4); 0x00405AC9 assigns an
// owning pointer to it.
class Rva000AD6F4
{
public:
	BfmeThingGX *get() const { return m_ptr; }
	void clear();
	Rva000AD6F4 &operator=(std::auto_ptr<BfmeThingGX> ptr);
private:
	BfmeThingGX *m_ptr;
};

class InGameUI
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(000) SLOT(001) SLOT(002) SLOT(003) SLOT(004) SLOT(005) SLOT(006) SLOT(007) SLOT(008) SLOT(009)
	SLOT(010) SLOT(011) SLOT(012) SLOT(013) SLOT(014) SLOT(015) SLOT(016) SLOT(017) SLOT(018) SLOT(019)
	SLOT(020) SLOT(021) SLOT(022) SLOT(023) SLOT(024) SLOT(025) SLOT(026) SLOT(027) SLOT(028) SLOT(029)
	SLOT(030) SLOT(031) SLOT(032) SLOT(033) SLOT(034) SLOT(035) SLOT(036) SLOT(037) SLOT(038) SLOT(039)
	SLOT(040) SLOT(041) SLOT(042) SLOT(043) SLOT(044) SLOT(045) SLOT(046) SLOT(047) SLOT(048) SLOT(049)
	SLOT(050) SLOT(051) SLOT(052) SLOT(053) SLOT(054) SLOT(055) SLOT(056) SLOT(057) SLOT(058) SLOT(059)
	SLOT(060) SLOT(061) SLOT(062) SLOT(063) SLOT(064) SLOT(065) SLOT(066) SLOT(067) SLOT(068) SLOT(069)
	SLOT(070) SLOT(071) SLOT(072) SLOT(073) SLOT(074) SLOT(075) SLOT(076) SLOT(077) SLOT(078) SLOT(079)
	SLOT(080) SLOT(081) SLOT(082) SLOT(083) SLOT(084) SLOT(085) SLOT(086) SLOT(087) SLOT(088) SLOT(089)
	SLOT(090) SLOT(091) SLOT(092) SLOT(093) SLOT(094)
	virtual bool slot095();			// +0x17C
	SLOT(096) SLOT(097) SLOT(098) SLOT(099)
	SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109)
	SLOT(110)
#undef SLOT
	virtual bool slot111();			// +0x1BC
};
extern InGameUI *TheInGameUI;

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
struct Rva00405C04ScriptEngineView
{
	char m_pad[0x1A104];
	int m_endGameTimer;
};

class DisconnectMenu;
extern DisconnectMenu *TheDisconnectMenu;

class RadarWindowOverrideSource
{
public:
	void rva002D370A();
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D36D8
{
public:
	int rva002D36D8();
};

static bool s_hintPending;

class Rva00405A50
{
public:
	void rva00405A50();
	void rva00405C04(BfmeThingGX *hint);
private:
	char m_pad000[0x214];
	bool m_214;
	char m_pad215[0x2A4 - 0x215];
	Rva000AD6F4 m_hint;	// +0x2A4
};

void Rva00405A50::rva00405C04(BfmeThingGX *hint)
{
	if (TheInGameUI->slot111() || ((Rva00405C04ScriptEngineView *)TheScriptEngine)->m_endGameTimer >= 0)
		return;

	bool expired = false;
	static unsigned long s_shownAt = timeGetTime();

	if (m_hint.get() && (char)bfmeSameGX(hint, m_hint.get()))
	{
		m_214 = true;
		unsigned int duration = hint->getDuration();
		if (s_hintPending || s_shownAt + duration >= timeGetTime())
			return;
		expired = true;
	}
	else if (!theRadarWindowOverrideSource || (char)((Rva002D36D8 *)theRadarWindowOverrideSource)->rva002D36D8())
	{
		m_hint.clear();
		if (theRadarWindowOverrideSource)
			theRadarWindowOverrideSource->rva002D370A();
		return;
	}

	m_214 = true;
	if (!expired)
	{
		m_hint = hint->clone();
		s_shownAt = timeGetTime();
		s_hintPending = false;
	}
	else
	{
		s_hintPending = true;
		if (TheInGameUI->slot095() || TheDisconnectMenu)
			return;
		rva00405A50();
	}
}

// ?clone@OldSchoolHelpBoxContentSource@@UAE?AU?$auto_ptr@VBfmeThingGX@@@_STL@@XZ @0x00405D7C
// (64B, RET 4): slot 1 of vtable 0x00838970 (the class of the rowed copy
// constructor 0x00405B60, 0x10 bytes): a heap copy of itself handed back in
// an STLport auto_ptr, the clone 0x00405C04 stores. Class named by its WB createContent slot
// (vtable 0x00838970).
class OldSchoolHelpBoxContentSource : public BfmeThingGX
{
public:
	OldSchoolHelpBoxContentSource(const OldSchoolHelpBoxContentSource &o) throw();
	virtual std::auto_ptr<BfmeThingGX> clone();
private:
	int m_4;
	int m_8;
	int m_c;
};

std::auto_ptr<BfmeThingGX> OldSchoolHelpBoxContentSource::clone()
{
	std::auto_ptr<BfmeThingGX> copy(new OldSchoolHelpBoxContentSource(*this));
	return copy;
}

// ??4Rva000AD6F4@@QAEAAV0@U?$auto_ptr@VBfmeThingGX@@@_STL@@@Z @0x00405AC9 65B: takes ownership
// from the by-value auto_ptr, then runs the previous object's slot-0 teardown with flag 0 and
// frees what it returns; byte-identical to Rva0042C1F9::rva0042C1F9 (0x0042C1F9) except its own
// EH handler (formerly the alias dup_00405ac9).
struct Rva00405AC9Slot0 { virtual void *slot0(int flags); };
Rva000AD6F4 &Rva000AD6F4::operator=(std::auto_ptr<BfmeThingGX> ptr)
{
	BfmeThingGX *old = m_ptr;
	m_ptr = ptr.release();
	::operator delete(old ? ((Rva00405AC9Slot0 *)old)->slot0(0) : 0);
	return *this;
}
