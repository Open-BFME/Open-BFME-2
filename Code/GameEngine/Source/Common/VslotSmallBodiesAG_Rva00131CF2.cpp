// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Split from VslotSmallBodiesAG.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AG: each calls a rowed function whose ledger name types its return (or
// convention) differently from what this call site needs, so the callee
// is bound through an alias pin in reverse/symbols.csv under an
// address-derived name (the rowed bodies answer 0/1 in eax, i.e. bool, and
// 0x0023C7F5 ignores ECX, so the thiscall spelling reaches the same
// bytes). As in VslotSmallBodiesA-AF, classes and methods are
// address-derived and model only what each body touches.

typedef int Int;
typedef float Real;

// 0x00131CF2 and 0x00151415 (texture tables): true when the +0x14 object's
// +0x08 (resp. +0x04) is set, else the rowed 0x00130FCE on this object.
struct Rva00131CF2Info
{
	Int m_00;
	Int m_04;
	Int m_08;
};
// The body at 0x00130FCE is rowed under this placeholder.
class BfmeThingURB
{
public:
	int bfmeGoURB();
};

class Rva00130FCE
{
public:
	__declspec(noinline) bool rva00130FCE() { return (char)((BfmeThingURB *)this)->bfmeGoURB() != 0; }
};
class Rva00131CF2 : public Rva00130FCE
{
public:
	bool rva00131CF2();
	bool rva00151415();
private:
	char m_pad00[0x14];
	Rva00131CF2Info *m_14;
};
bool Rva00131CF2::rva00131CF2()
{
	Rva00131CF2Info *info = m_14;
	if (info && info->m_08)
		return true;
	return rva00130FCE();
}
bool Rva00131CF2::rva00151415()
{
	Rva00131CF2Info *info = m_14;
	if (info && info->m_04)
		return true;
	return rva00130FCE();
}

// 0x0057B97C: 1 when the +0x34 object exists and the rowed 0x005D4E6F
// holds for it, else 0.
class Rva005D4E6F
{
public:
	Int rva005D4E6F();
};
class Rva0057B97C
{
public:
	Int rva0057B97C();
private:
	char m_pad00[0x34];
	Rva005D4E6F *m_34;
};
Int Rva0057B97C::rva0057B97C()
{
	if (m_34 && (char)m_34->rva005D4E6F())
		return 1;
	return 0;
}

// 0x0023DAF7: slot 1 of Rva0023DAE8's table (retail VA 0x00BEDAA0, slot 0 the
// shared deleting destructor 0x005FAA31): the rowed 0x0023C7F5 with both
// arguments on the +0x08 member.
class Rva0023C7F5
{
public:
	Int rva0023C7F5(Real a, Int b);
};
#include "../../Include/Common/Rva0007DF07.h"
class Rva0023DAE8 : public Rva0007DF07
{
public:
	virtual ~Rva0023DAE8();
	virtual void rva0023DAF7(Real a, Int b);
private:
	Rva0023C7F5 m_08;
};
void Rva0023DAE8::rva0023DAF7(Real a, Int b)
{
	m_08.rva0023C7F5(a, b);
}

// Slots 3 and 4 of the retail table at VA 0x00C7A448 call the empty base
// member at 0x0047A69C. The out-of-line definition preserves both calls.
#include "../../Include/Common/Gen_003bcb40.h"
struct Rva005FEEC7Info
{
	char m_pad00[0x18];
	Int *m_18;
	char m_pad1C[0x08];
	Int m_24;
};
class Rva005FEEC7 : public Gen_003bcb40
{
public:
	void rva005FEEC7(Int index);
	void rva005FEEE6(Int index);
private:
	Int m_00;
	Int m_04;
	Rva005FEEC7Info *m_08;
};
void Rva005FEEC7::rva005FEEC7(Int index)
{
	m(index);
	m_08->m_24 = m_08->m_18[index];
}
void Rva005FEEC7::rva005FEEE6(Int index)
{
	m(index);
	if (m_08->m_24 == m_08->m_18[index])
		m_08->m_24 = 7;
}

// The three derived field parsers call the base implementation at
// 0x0047A69C, then add their own field tables at offset 0.
struct FieldParse;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
#include "Rva004FA830.h"

// Native table bytes establish the names, offsets and parser pointers.
// Keep the existing opaque global spellings; no original owner type is inferred.
class LivingWorldAutoResolveBattleBonusTable
{
public:
    static void iniAppendBonusToTable(INI *, void *, void *, const void *);
};

static const char *const typeNames[] = { "TACTICAL", "WORLD", 0 };
static const char *const strengtheningRangeNames[] = { "THIS_TERRIORITY", "ALL_ARMIES", 0 };

extern const FieldParse g_rva005C4352FieldParse[] = {
    { "Type", &INI::parseIndexList, typeNames, 0x08 },
    { "Amount", &INI::parseInt, 0, 0x0C },
    { 0, 0, 0, 0 }
};
extern const FieldParse g_rva005C4553FieldParse[] = {
    { "StrengtheningRange", &INI::parseIndexList, strengtheningRangeNames, 0x08 },
    { "BonusKey", &INI::parseAsciiString, 0, 0x0C },
    { "Bonus", &LivingWorldAutoResolveBattleBonusTable::iniAppendBonusToTable, 0, 0x10 },
    { 0, 0, 0, 0 }
};
extern const FieldParse g_rva005C47A8FieldParse[] = {
    { "NumUpgradesPerTurn", &INI::parseInt, 0, 0x08 },
    { "UpgradeableUnits", &INI::parseAsciiStringVectorAppend, 0, 0x0C },
    { 0, 0, 0, 0 }
};
class Rva005C4352 : public Rva004FA830
{
public:
	void rva005C4553(MultiIniFieldParse &p);
	void rva005C47A8(MultiIniFieldParse &p);
};
// 0x005C4352 is slot 3 of Rva005C44A3's table 0x00C745D4 (installed by its
// constructor 0x005C44A3): the "IncreaseCommandPoints" bonus's builder, whose
// Type/Amount fields are the constructor's +0x08/+0x0C.
class Rva005C44A3
{
public:
	virtual void rva005C4352(MultiIniFieldParse &p);
};
void Rva005C44A3::rva005C4352(MultiIniFieldParse &multiIniFieldParse)
{
	reinterpret_cast<Rva004FA830 *>(this)->Rva004FA830::buildFieldParse(multiIniFieldParse);
	multiIniFieldParse.add(g_rva005C4352FieldParse, 0);
}
void Rva005C4352::rva005C4553(MultiIniFieldParse &multiIniFieldParse)
{
	Rva004FA830::buildFieldParse(multiIniFieldParse);
	multiIniFieldParse.add(g_rva005C4553FieldParse, 0);
}
// 0x005C47A8: the same builder over the table at VA 0x00C74704.
void Rva005C4352::rva005C47A8(MultiIniFieldParse &multiIniFieldParse)
{
	Rva004FA830::buildFieldParse(multiIniFieldParse);
	multiIniFieldParse.add(g_rva005C47A8FieldParse, 0);
}

// 0x00576FFE (table VA 0x00C6E8F0): the dword the rowed getter 0x0042D697
// reads through the object the rowed getter 0x00328A83 (alias-pinned with
// its pointer result) reaches from the +0x08 object's +0x04 member.
#include "../../Include/Common/Rva0042D697PtrChaseField.h"
#include "../../Include/Common/Rva00328A83PtrChaseField.h"
struct Rva00576FFEInfo
{
	Int m_00;
	Rva00328A83PtrChaseField *m_04;
};
class Rva00576FFE
{
public:
	Int rva00576FFE();
private:
	Int m_00;
	Int m_04;
	Rva00576FFEInfo *m_08;
};
Int Rva00576FFE::rva00576FFE()
{
	return ((Rva0042D697PtrChaseField *)m_08->m_04->get())->get();
}

// 0x00251C24, 0x004624E3, 0x00466E0A and 0x004BC51B: interface overrides
// (interface at +0x0C, +0x20, +0x34 resp. +0x10) that only dispatch to
// virtual slot 12, 18, 28 resp. 13 of the complete object.
// 0x00251C11 (the slot just before 0x00251C24 in the same vtable, at
// 0x007EFDA4): hands its float to virtual slot 15 of the object at +0x04.
class Rva00251C11Primary
{
public:
	virtual void p00();
};
class Rva00251C11Base04
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void rva00251C11Target(Real value);
};
class Rva00251C11 : public Rva00251C11Primary
{
public:
	void rva00251C11(Real value);
private:
	Rva00251C11Base04 m_04;
};


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
class Rva00251C24 : public Rva00251C24Primary<12, 0x0C>, public Rva00251C24Iface
{
public:
	void forward();
};

class Rva004624E3 : public Rva00251C24Primary<18, 0x20>, public Rva00251C24Iface
{
public:
	void forward();
};

class Rva00466E0A : public Rva00251C24Primary<28, 0x34>, public Rva00251C24Iface
{
public:
	void forward();
};

class Rva004BC51B : public Rva00251C24Primary<13, 0x10>, public Rva00251C24Iface
{
public:
	void forward();
};


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
	void rva005C456F(Rva003F7B59 *arg);
private:
	Int m_00;
	Rva005C456FSub04 *m_04;
	Rva005C456FSub08 *m_08;
};


class Rva005C47DC
{
public:
	void rva005C47DC(Int unused);
private:
	char m_pad00[0x14];
	Int m_14;
};


#include "../../Include/Common/AsciiStringRef.h"
struct Rva0032AFA4Pair
{
	AsciiStringRef m_a;
	AsciiStringRef m_b;
};
class Rva0032AFA4
{
public:
	Int rva0032AFA4(char *buf);
private:
	Int m_00;
	Rva0032AFA4Pair *m_04;
};


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


class Rva0037B7C7
{
public:
	void rva0037BC65();
};
#include "../../Include/Common/RecorderClass.h"


#include <new>
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


#include "../../Include/Common/Rva003F409F.h"
struct Rva003F82F4Sub04
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual bool v12(Rva003F409F *arg);
};
class Rva003F82F4
{
public:
	bool rva003F82F4(Rva003F409F *arg);
private:
	Int m_00;
	Rva003F82F4Sub04 *m_04;
};


class INI;
void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void rva00421749(INI *ini, void *instance, void *store, const void *userData);


enum ObjectStatusTypes
{
	OBJECT_STATUS_25 = 0x25
};
#include "../GameLogic/Object/object.h"
#include "../../Include/Common/StateMachineClass.h"
#include "../../Include/Common/StateMachine.h"
int rva0034373F(State *state, void *);


#include "../../Include/GameLogic/Waypoint.h"
extern Waypoint *g_waypointListHead;
#include "../../Include/Common/Rva0027CE80.h"


class Display;
extern Display *TheDisplay;
struct DisplayView002D7B50 : public Rva00251C24Slots<82>
{
	virtual void v82(Int a, Int b);
};
void rva002D7B50(Int a, Int b);


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


