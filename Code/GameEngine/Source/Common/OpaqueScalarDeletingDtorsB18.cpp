// cl: /O1 /Ob2 /EHs /DNDEBUG /MD /Ireference/shims/bfme2_ascii

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"
#include "../../Include/Common/Rva00041004Lock.h"
//
// Opaque scalar deleting destructors, batch B18: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// (docs/reconstruction/deleting-destructor-identity-audit.md).
// Rva005FCF0E now models the consumed prefix established by its native
// destructor; the other owner views remain layout-free.
//
//   wrapper     dtor        vtable#slot
//   0x005F8DE7  0x005F8CB0  0x00C79CF0#0
//   0x005F8F3E  0x005F8F5A  0x00C79CF8#0
//   0x005F8F5F  0x005F8F7B  0x00C79D0C#0
//   0x005FA125  0x005FA141  0x00C79D78#0
//   0x005FAFCC  0x005FAF5D  0x00C79E30#0
//   0x005FB1E8  0x005FB1AD  0x00C79EDC#0
//   0x005FBC04  0x005FBBEE  0x00C79FF4#0
//   0x005FCF59  0x005FCF0E  0x00C7A1BC#0
//   0x005FCFC9  0x005FCFE5  0x00C7A1D0#0
//   0x005FD0DE  0x005FCFEA  0x00C7A1F4#0
//   0x005FDA1D  0x005FD9FF  0x00C7A2E8#0
//   0x005FEDB1  0x005FED4D  0x00C7A448#0
//   0x005FEFB0  0x005FEF65  0x00C7A464#0
//   0x005FF145  0x005FF13A  0x00C7A478#0
//   0x005FF9A9  0x005FF95C  0x00C7A530#0
//   0x006003D3  0x00600379  0x00C7A620#0
//   0x00600510  0x00600505  0x00C7A64C#0
//   0x00604572  0x00604465  0x00C7A94C#0
//   0x0073EF08  0x0073EF24  0x00CF1538#2

struct EmitVtableTag;

class Rva005F8CB0
{
public:
	Rva005F8CB0(EmitVtableTag *);
public:
	virtual ~Rva005F8CB0();
};

// ?<Rva005F8CB0::Rva005F8CB0> absent-from-retail
Rva005F8CB0::Rva005F8CB0(EmitVtableTag *)
{
}

class Rva005F8F5A
{
public:
	Rva005F8F5A(EmitVtableTag *);
public:
	virtual ~Rva005F8F5A();
};

// ?<Rva005F8F5A::Rva005F8F5A> absent-from-retail
Rva005F8F5A::Rva005F8F5A(EmitVtableTag *)
{
}

class Rva005F8F7B
{
public:
	Rva005F8F7B(EmitVtableTag *);
public:
	virtual ~Rva005F8F7B();
};

// ?<Rva005F8F7B::Rva005F8F7B> absent-from-retail
Rva005F8F7B::Rva005F8F7B(EmitVtableTag *)
{
}

class Rva005FA141
{
public:
	Rva005FA141(EmitVtableTag *);
public:
	virtual ~Rva005FA141();
};

// ?<Rva005FA141::Rva005FA141> absent-from-retail
Rva005FA141::Rva005FA141(EmitVtableTag *)
{
}

class Rva005FB1AD
{
public:
	Rva005FB1AD(EmitVtableTag *);
public:
	virtual ~Rva005FB1AD();
};

// ?<Rva005FB1AD::Rva005FB1AD> absent-from-retail
Rva005FB1AD::Rva005FB1AD(EmitVtableTag *)
{
}

class Rva005FBBEE;
class Rva005FBC20
{
public:
	Rva005FBC20(Rva005FBBEE *owner, unsigned level, const AsciiString &name);
private:
	char m_storage[0x50];
};

class Rva005FBBEE
{
public:
	Rva005FBBEE(EmitVtableTag *);
	Rva005FBBEE(unsigned level, const AsciiString &name);
public:
	virtual ~Rva005FBBEE();
	// Retail table 0x00C79FF4: three __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
private:
	Rva005FBC20 *m_impl;
};

// ?<Rva005FBBEE::Rva005FBBEE> absent-from-retail
Rva005FBBEE::Rva005FBBEE(EmitVtableTag *)
{
}

// Native5FBE0D..5FBE57: the existing C79FF4 owner allocates its50-byte
// implementation and forwards its own pointer plus level and name.
Rva005FBBEE::Rva005FBBEE(unsigned level, const AsciiString &name)
{
	m_impl = new Rva005FBC20(this, level, name);
}

// Native5FCF0E..5FCF59 is a75B destructor tied independently to this
// existing opaque owner by its rowed deleting wrapper5FCF59/vtableC7A1BC.
// It calls full26B owning-pointer reset5FCB2D on receiver+18 then releases
// storage+8 through free30830 and restores the folded base tableBC6F20.
// Only consumed offsets and teardown are target facts. The storage view's
// words+C/+10 and word14 are unknown; no vector payload or full retail
// allocation size is inferred. EH states distinguish both cleanup steps.
// The call-only member destructor view uses the rowed reset's complete ABI.
extern "C" const void *const vtbl_00BC6F20[];
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
class __declspec(novtable) Rva005FCF0EBase {
public:
 Rva005FCF0EBase() : word04(0) {}
 // ?<Rva005FCF0EBase::~Rva005FCF0EBase> present-unmatched
 __forceinline virtual ~Rva005FCF0EBase() {*(const void**)this=vtbl_00BC6F20;}
protected: int word04;
};
#include "../../Include/Common/Rva00330757Member.h"

__forceinline Rva00330757Member::~Rva00330757Member()
{
    if (field00) free(field00);
}
class Rva005FCB2DReleaseView {
public:
 Rva005FCB2DReleaseView() {}
 Rva005FCB2DReleaseView(void *value) : owned(value) {}
 ~Rva005FCB2DReleaseView();
private: void *owned;
};
#pragma comment(linker, "/alternatename:??1Rva005FCB2DReleaseView@@QAE@XZ=?clear@Rva005FCB2D@@QAEXXZ")

class Rva005FCF0E : public Rva005FCF0EBase, public Rva00330757Member
{
public:
	Rva005FCF0E(EmitVtableTag *);
    Rva005FCF0E(unsigned int level, const AsciiString &name);
public:
	virtual ~Rva005FCF0E();
private:
	Rva005FCB2DReleaseView member18;
};

// ?<Rva005FCF0E::Rva005FCF0E> absent-from-retail
Rva005FCF0E::Rva005FCF0E(EmitVtableTag *)
{
}

Rva005FCF0E::~Rva005FCF0E() {}

class Rva005FCFE5 : public Rva005FCF0E
{
public:
	Rva005FCFE5(EmitVtableTag *);
    Rva005FCFE5(unsigned int level);
public:
	virtual ~Rva005FCFE5();
};

// ?<Rva005FCFE5::Rva005FCFE5> absent-from-retail
Rva005FCFE5::Rva005FCFE5(EmitVtableTag *) : Rva005FCF0E((EmitVtableTag *)0)
{
}

class Rva005FCFEA
{
public:
	Rva005FCFEA(EmitVtableTag *);
public:
	virtual ~Rva005FCFEA();
};

// ?<Rva005FCFEA::Rva005FCFEA> absent-from-retail
Rva005FCFEA::Rva005FCFEA(EmitVtableTag *)
{
}

// StrategicHUD::ArmyUnitSwapperMovieClip (vtable 0x00C7A2E8: the deleting dtor
// 0x005FDA1D, then the five notify* slots).
namespace StrategicHUD {
class ArmyUnitSwapperMovieClip
{
public:
	ArmyUnitSwapperMovieClip(EmitVtableTag *);
public:
	virtual ~ArmyUnitSwapperMovieClip();
	virtual void notifyClosed();
	virtual void notifyExit();
	virtual void notifyMoveDown();
	virtual void notifyMoveUp();
	virtual void notifySwap();
};
}

// ?<StrategicHUD::ArmyUnitSwapperMovieClip::ArmyUnitSwapperMovieClip> absent-from-retail
StrategicHUD::ArmyUnitSwapperMovieClip::ArmyUnitSwapperMovieClip(EmitVtableTag *)
{
}

class Rva00600379
{
public:
	Rva00600379(EmitVtableTag *);
public:
	virtual ~Rva00600379();
};

// ?<Rva00600379::Rva00600379> absent-from-retail
Rva00600379::Rva00600379(EmitVtableTag *)
{
}

class Rva00600505
{
public:
	Rva00600505(EmitVtableTag *);
public:
	virtual ~Rva00600505();
};

// ?<Rva00600505::Rva00600505> absent-from-retail
Rva00600505::Rva00600505(EmitVtableTag *)
{
}

class Rva00604465
{
public:
	Rva00604465(EmitVtableTag *);
public:
	virtual ~Rva00604465();
};

// ?<Rva00604465::Rva00604465> absent-from-retail
Rva00604465::Rva00604465(EmitVtableTag *)
{
}

// The 0x00BC6F20 table is folded across seven classes. Reuse the rowed
// Rva0007DF07 vftable symbol only to name that address; the secondary-base
// identity at 0x0073EF24 remains unknown.
#include "../../Include/Common/Rva0007DF07.h"

class Rva0073EF24 : public Rva0040EDB, public Rva0007DF07
{
public:
	Rva0073EF24(EmitVtableTag *);
public:
	virtual ~Rva0073EF24();
};

// ?<Rva0073EF24::Rva0073EF24> absent-from-retail
Rva0073EF24::Rva0073EF24(EmitVtableTag *)
{
}

// Target5FCF75-5FCFC9 calls5FCEA9 with the input level and ArmyHeroIcon
// temporary then installs C7A1D0 matching the existing deleting destructor.
// WorldBuilder provides the ArmyMemberIconMovieClip base lead; the original
// derived owner identity remains unknown so retain its established name.
Rva005FCFE5::Rva005FCFE5(unsigned int level)
    : Rva005FCF0E(level, AsciiString("ArmyHeroIcon"))
{
}

// The complete allocation size and three argument reads are target facts
// from the 866-byte constructor at5FCB47. WB names its implementation class;
// retain an opaque ABI name while this unit's owner identity remains unknown.
// The constructor is called by its row name ??0Impl@ArmyMemberIconMovieClip@StrategicHUD@@
// (Rva005FC8FDApt.cpp); this view declares only that constructor and the size.
class AptMovieClipFrame;
#include "../../Include/GameClient/ArmyMemberIconMovieClip.h"

class StrategicHUD::ArmyMemberIconMovieClip::Impl
{
public:
    Impl(ArmyMemberIconMovieClip *owner, AptMovieClipFrame *frame, const AsciiString &name);
private:
    unsigned char m_storage[0x38];
};

// Target5FCEA9-5FCF0E: base word04 zero; observer storage ctor at+8;
// vtableC7A1BC; 0x38-byte allocation and implementation ctor; holder at+18.
Rva005FCF0E::Rva005FCF0E(unsigned int level, const AsciiString &name)
    : member18(new StrategicHUD::ArmyMemberIconMovieClip::Impl((StrategicHUD::ArmyMemberIconMovieClip *)this,
          (AptMovieClipFrame *)level, name))
{
}

// ??0Rva0073EF3A@@QAE@XZ @0x0073EF3A 10B: default constructor zeroing the
// words at +0 and +8 (the +4 word is left as is) and returning this.
class Rva0073EF3A
{
public:
	Rva0073EF3A();
private:
	int m_00;
	int m_04;
	int m_08;
};

Rva0073EF3A::Rva0073EF3A() : m_00(0), m_08(0)
{
}

// ??0Rva0073EEA7@@QAE@ABV0@@Z @0x0073EEA7 20B: copy constructor of a counted
// handle: copy the pointer and bump the +0x0C count of a non-null pointee.
struct Rva0073EEA7Target
{
	char m_pad[0x0c];
	int m_refs;
};
class Rva0073EEA7
{
public:
	Rva0073EEA7(const Rva0073EEA7 &other);
private:
	Rva0073EEA7Target *m_target;
};

Rva0073EEA7::Rva0073EEA7(const Rva0073EEA7 &other) : m_target(other.m_target)
{
	if (m_target)
		++m_target->m_refs;
}
