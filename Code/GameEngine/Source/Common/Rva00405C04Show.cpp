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
#include "../../Include/Common/Rva000AD6F4.h"
// The +0x2A4 holder owns a BfmeThingGX here.
static __forceinline BfmeThingGX *heldHint(const Rva000AD6F4 &holder) { return (BfmeThingGX *)holder.m_ptr; }

#include "../../Include/GameClient/InGameUI.h"
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

struct TreeHintRef00217D4C;
class RadarWindowOverrideSource
{
public:
	void ShowHelpBox(const TreeHintRef00217D4C &hint);
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
	if (TheInGameUI->areTooltipsDisabled() || ((Rva00405C04ScriptEngineView *)TheScriptEngine)->m_endGameTimer >= 0)
		return;

	bool expired = false;
	static unsigned long s_shownAt = timeGetTime();

	if (heldHint(m_hint) && (char)bfmeSameGX(hint, heldHint(m_hint)))
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
		if (TheInGameUI->slot95() || TheDisconnectMenu)
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
	BfmeThingGX *old = (BfmeThingGX *)m_ptr;
	m_ptr = ptr.release();
	::operator delete(old ? ((Rva00405AC9Slot0 *)old)->slot0(0) : 0);
	return *this;
}
