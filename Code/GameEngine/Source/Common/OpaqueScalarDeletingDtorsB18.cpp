// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
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
//   0x005F6530  0x005F64F5  0x00C796D0#0
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

class Rva005F64F5
{
public:
	Rva005F64F5(EmitVtableTag *);
public:
	virtual ~Rva005F64F5();
};

// ?<Rva005F64F5::Rva005F64F5> absent-from-retail
Rva005F64F5::Rva005F64F5(EmitVtableTag *)
{
}

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

class Rva005FAF5D
{
public:
	Rva005FAF5D(EmitVtableTag *);
public:
	virtual ~Rva005FAF5D();
};

// ?<Rva005FAF5D::Rva005FAF5D> absent-from-retail
Rva005FAF5D::Rva005FAF5D(EmitVtableTag *)
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

class Rva005FBBEE
{
public:
	Rva005FBBEE(EmitVtableTag *);
public:
	virtual ~Rva005FBBEE();
};

// ?<Rva005FBBEE::Rva005FBBEE> absent-from-retail
Rva005FBBEE::Rva005FBBEE(EmitVtableTag *)
{
}

// Native5FCF0E..5FCF59 is a75B destructor tied independently to this
// existing opaque owner by its rowed deleting wrapper5FCF59/vtableC7A1BC.
// It calls full26B owning-pointer reset5FCB2D on receiver+18 then releases
// storage+8 through free30830 and restores the folded base tableBC6F20.
// Only consumed offsets and teardown are target facts. The storage view's
// words+C/+10 and word14 are unknown; no vector payload or full retail
// allocation size is inferred. EH states distinguish both cleanup steps.
// The call-only member destructor view uses the rowed reset's complete ABI.
void free(void*);
extern "C" const void *const vtbl_00BC6F20[];
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
class __declspec(novtable) Rva005FCF0EBase {
public:
 Rva005FCF0EBase() : word04(0) {}
 // ?<Rva005FCF0EBase::~Rva005FCF0EBase> present-unmatched
 __forceinline virtual ~Rva005FCF0EBase() {*(const void**)this=vtbl_00BC6F20;}
protected: int word04;
};
class Rva00330757Member {
public:
 Rva00330757Member();
 // ?<Rva00330757Member::~Rva00330757Member> present-unmatched
 __forceinline ~Rva00330757Member() {if(begin)free(begin);}
private: void *begin,*unknown0C,*unknown10; int unknown14;
};
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

class Rva005FD9FF
{
public:
	Rva005FD9FF(EmitVtableTag *);
public:
	virtual ~Rva005FD9FF();
};

// ?<Rva005FD9FF::Rva005FD9FF> absent-from-retail
Rva005FD9FF::Rva005FD9FF(EmitVtableTag *)
{
}

class Rva005FED4D
{
public:
	Rva005FED4D(EmitVtableTag *);
public:
	virtual ~Rva005FED4D();
};

// ?<Rva005FED4D::Rva005FED4D> absent-from-retail
Rva005FED4D::Rva005FED4D(EmitVtableTag *)
{
}

class Rva005FEF65
{
public:
	Rva005FEF65(EmitVtableTag *);
public:
	virtual ~Rva005FEF65();
};

// ?<Rva005FEF65::Rva005FEF65> absent-from-retail
Rva005FEF65::Rva005FEF65(EmitVtableTag *)
{
}

class Rva005FF13A
{
public:
	Rva005FF13A(EmitVtableTag *);
public:
	virtual ~Rva005FF13A();
};

// ?<Rva005FF13A::Rva005FF13A> absent-from-retail
Rva005FF13A::Rva005FF13A(EmitVtableTag *)
{
}

class Rva005FF95C
{
public:
	Rva005FF95C(EmitVtableTag *);
public:
	virtual ~Rva005FF95C();
};

// ?<Rva005FF95C::Rva005FF95C> absent-from-retail
Rva005FF95C::Rva005FF95C(EmitVtableTag *)
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
struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07();
	virtual ~Rva0007DF07() {}
};

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
class Rva005FCB47
{
public:
    Rva005FCB47(Rva005FCF0E *owner, unsigned int level, const AsciiString &name);
private:
    unsigned char m_storage[0x38];
};

// Target5FCEA9-5FCF0E: base word04 zero; observer storage ctor at+8;
// vtableC7A1BC; 0x38-byte allocation and implementation ctor; holder at+18.
Rva005FCF0E::Rva005FCF0E(unsigned int level, const AsciiString &name)
    : member18(new Rva005FCB47(this, level, name))
{
}
