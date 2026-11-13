// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AG: each calls a rowed function whose ledger name types its return (or
// convention) differently from what this call site needs, so the callee
// is bound through an alias pin in reverse/symbols.csv under an
// address-derived name (the rowed bodies answer 0/1 in eax, i.e. bool, and
// 0x0023C7F5 ignores ECX, so the thiscall spelling reaches the same
// bytes). As in VslotSmallBodiesA-AF, classes and methods are
// address-derived and model only what each body touches.

#include <new>

typedef int Int;
typedef float Real;

// 0x00131CF2 and 0x00151415 (texture tables): true when the +0x14 object's
// +0x08 (resp. +0x04) is set, else the rowed 0x00130FCE on this object.
// 0x0057B97C: 1 when the +0x34 object exists and the rowed 0x005D4E6F
// holds for it, else 0.
// 0x003FF312: false while +0x10 is clear, else the rowed GameSlot
// 0x003FF145 of the +0x18 slot for the +0x38 address.
struct BfmeNetAddress;
// 0x0023DAF7: the rowed 0x0023C7F5 with both arguments on the +0x08
// member.
// 0x005FEEC7 and 0x005FEEE6 (adjacent slots of table VA 0x00C7A454): each
// first runs the shared empty base slot 0x0047A69C (pinned there as
// Gen_003bcb40::m) with its index, then stores entry [index] of the +0x08
// object's +0x18 table into its +0x24, resp. resets +0x24 to 7 when it
// holds that entry.
#include "../../Include/Common/Gen_003bcb40.h"
// 0x005C4352 and 0x005C4553 (tables VA 0x00C745E0/0x00C746D8): field-parse
// builders: the shared empty base slot 0x0047A69C (alias-pinned here as a
// buildFieldParse), then the pinned MultiIniFieldParse::add of the table at
// VA 0x00C74540 (resp. 0x00C74630) with offset 0.
struct FieldParse;
#include "../../Include/Common/INI/FieldParse.h"
extern const FieldParse g_rva005C4352FieldParse[];
extern const FieldParse g_rva005C4553FieldParse[];
extern const FieldParse g_rva005C47A8FieldParse[];
// 0x00576FFE (table VA 0x00C6E8F0): the dword the rowed getter 0x0042D697
// reads through the object the rowed getter 0x00328A83 (alias-pinned with
// its pointer result) reaches from the +0x08 object's +0x04 member.
// 0x00466E0A and 0x004BC51B: interface overrides (interface at +0x34
// resp. +0x10) that only dispatch to virtual slot 28 resp. 13 of the
// complete object. SpecialPowerModule's 0x00251C11 and 0x00251C24 are at
// the end of this file.
template <int N>
class Rva00251C24Slots : public Rva00251C24Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <>
class Rva00251C24Slots<0>
{
};
template <int SLOT, int SIZE>
class Rva00251C24Primary : public Rva00251C24Slots<SLOT>
{
public:
	virtual void target();
private:
	char m_pad04[SIZE - 4];
};
#include "../../Include/Common/Rva00251C24Iface.h"
class Rva004BC51B : public Rva00251C24Primary<13, 0x10>, public Rva00251C24Iface
{
public:
	void forward();
};
void Rva004BC51B::forward()
{
	target();
}

class AsciiString;
class Rva003F7B59
{
public:
	void *rva003F7B59(const AsciiString *a, Int b);
	Int m_00;
};
struct Rva005C456FSub04
{
	char m_pad00[0x24];
	Int m_24;
};
struct Rva005C456FSub08
{
	Int m_00;
	Int m_04;
	Int m_08;
	Int m_0C;
	Int m_10;
};
class Rva005C456F
{
public:
	void rva005C456F(Rva003F7B59 *evaBucket);
private:
	Int m_00;
	Rva005C456FSub04 *m_04;
	Rva005C456FSub08 *m_08;
};
void Rva005C456F::rva005C456F(Rva003F7B59 *evaBucket)
{
	Rva005C456FSub08 *s = m_08;
	if (s->m_08 != 0 || m_04->m_24 == evaBucket->m_00)
		evaBucket->rva003F7B59((const AsciiString *)&s->m_0C, (Int)&s->m_10);
}

class Rva005C47DC
{
public:
	void rva005C47DC(Int unused);
private:
	char m_pad00[0x14];
	Int m_14;
};
void Rva005C47DC::rva005C47DC(Int)
{
	Int remainingCount = m_14;
	if (remainingCount > 0)
		m_14 = remainingCount - 1;
}

struct Rva003678D6Sub04
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual bool v8();
};
struct Rva003678D6Sub28
{
	Int m_00;
	Rva003678D6Sub04 *m_04;
	bool check() const { return m_04 ? m_04->v8() : true; }
};
class Rva003678D6
{
public:
	bool rva003678D6();
private:
	char m_pad00[0x28];
	Rva003678D6Sub28 *m_28;
};
bool Rva003678D6::rva003678D6()
{
	return !m_28->check();
}

namespace FXParticleSystem
{
class CPUParticle
{
public:
	virtual void *deleteInstance(Int pool);
	bool update();
	char m_pad04[0x60];
	CPUParticle *m_next64;
};
}
class Rva003AFDAA
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual FXParticleSystem::CPUParticle *v8();
	void rva003AFDF1();
};
void Rva003AFDAA::rva003AFDF1()
{
	FXParticleSystem::CPUParticle *p = v8();
	while (p)
	{
		FXParticleSystem::CPUParticle *next = p->m_next64;
		if (!p->update())
			::operator delete(p->deleteInstance(0));
		p = next;
	}
}

#include "../../Include/Common/Rva003F409F.h"
struct Rva003F82F4Sub04
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual bool v12(Rva003F409F *arg);
};
// Slot 0 of Rva003F82E2's one-slot table 0x00C37310 (constructor in RvaSmallVtableCtors.cpp).
class Rva003F82E2
{
public:
	virtual bool rva003F82F4(Rva003F409F *arg);
private:
	Rva003F82F4Sub04 *m_04;
};
bool Rva003F82E2::rva003F82F4(Rva003F409F *arg)
{
	arg->rva003F409F(m_04->v12(arg));
	return true;
}

class INI;
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void rva00421749(INI *ini, void *instance, void *store, const void *userData)
{
	iniParseObjectFilter(ini, instance, *static_cast<void **>(store), userData);
}

enum ObjectStatusTypes
{
	OBJECT_STATUS_25 = 0x25
};
#include "../GameLogic/Object/object.h"
#include "../../Include/Common/StateMachineClass.h"
#include "../../Include/Common/StateMachine.h"
int rva0034373F(State *state, void *)
{
	return !state->m_machine->m_owner->testStatus(OBJECT_STATUS_25);
}

#include "../../Include/GameLogic/Waypoint.h"
extern Waypoint *g_waypointListHead;
#include "../../Include/Common/Rva0027CE80.h"
void Rva0027CE80::rva0027CE80()
{
	while (g_waypointListHead)
		::delete g_waypointListHead;
}

class Display;
extern Display *TheDisplay;
class LANAPI;
extern LANAPI *TheLAN;
struct LANView0044446D : public Rva00251C24Slots<54>
{
	virtual bool v54();
};
#include "../../Include/GameClient/AptMpGameSetup.h"
#include "../../Include/GameClient/Rva0043DFE0.h"
struct Rva004469D1Receiver
{
	void rva0044446D(bool flag);
	char m_pad00[0x288];
	int m_288;
};
void Rva004469D1Receiver::rva0044446D(bool flag)
{
	if (flag)
	{
		if (TheLAN && !reinterpret_cast<LANView0044446D *>(TheLAN)->v54())
			reinterpret_cast<AptMpGameSetup *>(&m_288)->rva0043DC0F();
	}
	else
	{
		reinterpret_cast<Rva0043DFE0 *>(&m_288)->rva0043DBA3();
	}
}


// 0x00251C11 and 0x00251C24: SpecialPowerModule's overrides of BehaviorModuleInterface (its +0x0C base)
// slots 43 and 44, table VA 0x00BEFCF8 (installed by ??0SpecialPowerModule 0x00493C5A). Slot 43 hands its
// float to the +0x10 SpecialPowerModuleInterface's startPowerRecharge (slot 15); slot 44 calls the primary
// table's slot 12, rva00493805.
#include "../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../Include/GameLogic/Module/SpecialPowerModule.h"
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	virtual void rva00493805();			// primary slot 12
	virtual void slot43(float readyFraction);	// BehaviorModuleInterface slot 43
	virtual void slot44();				// BehaviorModuleInterface slot 44
};
void SpecialPowerModule::slot43(float readyFraction)
{
	startPowerRecharge(readyFraction);
}
void SpecialPowerModule::slot44()
{
	rva00493805();
}
