// cl: /O1 /DNDEBUG /MD
//
// Scalar deleting destructors of classes whose destructor is empty and
// inline, batch C01: the 29-byte wrapper stores the class's own vtable,
// then frees through operator delete (0x0002FD60) when bit 0 of the flags is
// set and returns this (ret 4). Each class is named after the ledger name its
// vtable already carries, else after the wrapper's address; the dummy tag
// constructors (no retail counterpart) only make this TU emit each vtable and
// with it the deleting destructor. No layout or identity beyond that is
// modelled.
//
//   wrapper     vtable
//   0x00051E4D  0x00BC5128  Rva00051E4D
//   0x000723C7  0x00BC64B0  BfmeBaseCC
//   0x00072899  0x00BC650C  RefCountClass
//   0x00074626  0x00BC65A8  Rva00074626
//   0x0007DFF2  0x00BC6F24  Rva0007DFF2
//   0x000906DE  0x00BC7E94  Rva000906DE
//   0x000A8E9C  0x00BC93BC  AptDisplayStringBase
//   0x000A8EF6  0x00BC93DC  Rva000A8EF6
//   0x000EF9D6  0x00BCEF94  HashableClass
//   0x000EFA0E  0x00BCEF9C  Rva000EFA0E
//   0x001164B6  0x00BCFB24  Rva001164B6
//   0x001A4697  0x00BD6CB4  BFME2MotionChannel
//   0x00203E76  0x00BE3990  Rva00203E76
//   0x0020E20C  0x00BE4318  Rva0020E20C
//   0x00215E42  0x00BE5838  Rva00215E42
//   0x002BED74  0x00BFE4EC  Rva002BED74
//   0x002C1283  0x00BFE5B4  Rva002C1283
//   0x002D252B  0x00C02A5C  Rva002D252B
//   0x002D3556  0x00C02A84  Rva002D3556
//   0x00306DE9  0x00C07E84  InputChunk
//   0x0037F57E  0x00C18DFC  Rva0037F57E
//   0x00381D78  0x00C19230  Rva00381D78
//   0x0039AE75  0x00C1AD60  Rva0039AE75
//   0x003EE711  0x00C363B8  Rva003EE711
//   C37298 lifetime now has its complete registry-base provider.

#include <new.h>

struct EmitVtableTag;
// This synthetic overload only emits this view's table. Its tag must not
// collide with another view's synthetic constructor of the same class.
struct C01VtableEmissionTag;

class Rva00051E4D
{
public:
	Rva00051E4D(C01VtableEmissionTag *);
	virtual ~Rva00051E4D() {}
};

// ?<Rva00051E4D::Rva00051E4D> absent-from-retail
Rva00051E4D::Rva00051E4D(C01VtableEmissionTag *)
{
}

class BfmeBaseCC
{
public:
	BfmeBaseCC(EmitVtableTag *);
	virtual ~BfmeBaseCC() {}
};

// ?<BfmeBaseCC::BfmeBaseCC> absent-from-retail
BfmeBaseCC::BfmeBaseCC(EmitVtableTag *)
{
}

// WWLib refcount.h declares the destructor protected: virtual ~RefCountClass(void)
// (retail mangle MAE, witnessed by the matched ??1RefCountClass@@MAE@XZ at
// 0x00072892 and the census-named ??_GRefCountClass@@MAEPAXI@Z COMDAT copies).
// Consumer-compatible two-virtual view, matching GapBodiesGE31.cpp: Delete_This
// is slot zero (supplied externally, not called here) and the protected empty
// dtor is slot one; the deleting-dtor body does not depend on the NumRefs
// layout, so no members are modelled.
class RefCountClass
{
public:
	RefCountClass(EmitVtableTag *);
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
};

// ?<RefCountClass::RefCountClass> absent-from-retail
RefCountClass::RefCountClass(EmitVtableTag *)
{
}

class Rva00074626
{
public:
	Rva00074626(EmitVtableTag *);
	virtual ~Rva00074626();
};

// ?<Rva00074626::Rva00074626> absent-from-retail
Rva00074626::Rva00074626(EmitVtableTag *)
{
}

// Keep the qualified call before the inline definition so MSVC emits the
// standalone seven-byte destructor while still inlining it in the deleting dtor.
// ?bfmeAnchorC01Rva00074626 absent-from-retail
void bfmeAnchorC01Rva00074626(Rva00074626 *p) { p->Rva00074626::~Rva00074626(); }

// ??1Rva00074626@@UAE@XZ @0x0007461F 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
inline Rva00074626::~Rva00074626()
{
}

// Native BC6778 has scalar7827B followed by two purecall43B810 slots.
// BFME1 ffactory.h at9e3be919b supplies Get_File/Return_File names and
// signatures; native slot count and constructor/destructor bytes agree.
class FileClass;
class FileFactoryClass
{
public:
	FileFactoryClass();
	virtual ~FileFactoryClass() {}
	virtual FileClass *Get_File(const char *filename) = 0;
	virtual void Return_File(FileClass *file) = 0;
};

// ??0FileFactoryClass@@QAE@XZ @0x0007838A 9B: the default constructor, storing the
// class's own vtable and returning this.
__declspec(noinline) inline FileFactoryClass::FileFactoryClass()
{
}

class Rva0007DFF2
{
public:
	Rva0007DFF2(EmitVtableTag *);
	virtual ~Rva0007DFF2() {}
	virtual void slot1() = 0; // 0x007C6F24: __purecall
};

// ?<Rva0007DFF2::Rva0007DFF2> absent-from-retail
Rva0007DFF2::Rva0007DFF2(EmitVtableTag *)
{
}

class Rva000906DE
{
public:
	Rva000906DE();
	// Retail table 0x007C7E94 has four __purecall slots before the destructor.
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual ~Rva000906DE();
};

// ??0Rva000906DE@@QAE@XZ @0x00090778 9B: the default constructor, storing the
// class's own vtable and returning this.
Rva000906DE::Rva000906DE()
{
}

// ??1Rva000906DE@@UAE@XZ @0x00090771 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva000906DE::~Rva000906DE()
{
}

class AptDisplayStringBase
{
public:
	AptDisplayStringBase();
	AptDisplayStringBase(EmitVtableTag *);
	virtual ~AptDisplayStringBase();
};

// ??0AptDisplayStringBase@@QAE@XZ @0x000A9567 9B: the default constructor, storing the
// class's own vtable and returning this. Inline (selectany COMDAT) because the
// W3DAptDisplayString units emit the same copy.
inline AptDisplayStringBase::AptDisplayStringBase()
{
}

// ?<AptDisplayStringBase::AptDisplayStringBase> absent-from-retail
AptDisplayStringBase::AptDisplayStringBase(EmitVtableTag *)
{
}

// ??1AptDisplayStringBase@@UAE@XZ @0x000A8E95 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline. Inline for the same reason.
inline AptDisplayStringBase::~AptDisplayStringBase()
{
}

// ?<bfmeKeepAptDisplayStringBase> absent-from-retail
// Emits the two inline bodies above out of line, as the other units do.
void bfmeKeepAptDisplayStringBase()
{
	AptDisplayStringBase base;
}

class Rva000A8EF6
{
public:
	Rva000A8EF6();
	Rva000A8EF6(EmitVtableTag *);
	virtual ~Rva000A8EF6();
};

// ??0Rva000A8EF6@@QAE@XZ @0x000A8EE6 9B: the default constructor, storing the
// class's own vtable and returning this.
Rva000A8EF6::Rva000A8EF6()
{
}

// ?<Rva000A8EF6::Rva000A8EF6> absent-from-retail
Rva000A8EF6::Rva000A8EF6(EmitVtableTag *)
{
}

// ??1Rva000A8EF6@@UAE@XZ @0x000A8EEF 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva000A8EF6::~Rva000A8EF6()
{
}

// BFME 1 hash.h at ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies
// the Hashable contract. Native BCEF94 has deleting dtor 4EF9D6 followed
// by purecall 43B810; geometry ctor F1E48 zeroes NextHash at base+4.
class HashableClass
{
public:
	HashableClass(EmitVtableTag *);
	virtual ~HashableClass() {}
	virtual const char *Get_Key(void)=0;
private:
	HashableClass *NextHash;
};

// ?<HashableClass::HashableClass> absent-from-retail
HashableClass::HashableClass(EmitVtableTag *)
{
}

class Rva000EFA0E
{
public:
	Rva000EFA0E(EmitVtableTag *);
	virtual ~Rva000EFA0E();
};

// ?<Rva000EFA0E::Rva000EFA0E> absent-from-retail
Rva000EFA0E::Rva000EFA0E(EmitVtableTag *)
{
}

// ??1Rva000EFA0E@@UAE@XZ @0x00108650 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva000EFA0E::~Rva000EFA0E()
{
}

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva001164B6.h"

// ??1Rva001164B6@@UAE@XZ @0x0011647B 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva001164B6::~Rva001164B6()
{
}

class BFME2MotionChannel
{
public:
	BFME2MotionChannel(EmitVtableTag *);
	virtual ~BFME2MotionChannel();
};

// ?<BFME2MotionChannel::BFME2MotionChannel> absent-from-retail
BFME2MotionChannel::BFME2MotionChannel(EmitVtableTag *)
{
}

// ??1BFME2MotionChannel@@UAE@XZ @0x001A466C 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
BFME2MotionChannel::~BFME2MotionChannel()
{
}

// Rva001DB080 now emits its native two-slot translator table and exact29B
// deleting destructor from Rva0042C5C3Dtor.cpp; the single-slot emitter was
// an incomplete base view and is removed.

class Rva00203E76
{
public:
	Rva00203E76(EmitVtableTag *);
	virtual ~Rva00203E76() {}
};

// ?<Rva00203E76::Rva00203E76> absent-from-retail
Rva00203E76::Rva00203E76(EmitVtableTag *)
{
}

#include "../../Include/Common/RegionArmyComparatorView.h"

// ?<Rva0020E20C::Rva0020E20C> absent-from-retail
Rva0020E20C::Rva0020E20C(EmitVtableTag *)
{
}

// The canonical two-slot base keeps its empty destructor inline; its
// 7-byte emitted body at20E205 restores BE4318, as before.

class Rva00215E42
{
public:
	Rva00215E42(EmitVtableTag *);
	Rva00215E42();
	Rva00215E42(const Rva00215E42 &);
	virtual ~Rva00215E42();
	// Retail table 0x007E5838 has five __purecall entries after slot 0.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual int slot5() = 0;
};
// ??0Rva00215E42@@QAE@XZ @0x0029A287 9B: the default constructor, storing the
// class's own vtable (VA 0x00BE5838) and returning this.
Rva00215E42::Rva00215E42()
{
}

// ?<Rva00215E42::Rva00215E42> absent-from-retail
Rva00215E42::Rva00215E42(EmitVtableTag *)
{
}

// ??0Rva00215E42@@QAE@ABV0@@Z @0x004059B3 11B: the copy constructor, which
// copies nothing and stores the class's own vtable (ret 4); skeleton twin of
// Snapshot's copy constructor 0x00001745.
Rva00215E42::Rva00215E42(const Rva00215E42 &)
{
}

// ??1Rva00215E42@@UAE@XZ @0x004059AC 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva00215E42::~Rva00215E42()
{
}

// Rva002BED74's constructor and destructor are inline (select-any COMDATs):
// Rva005CBB0AWrap.cpp derives its two wrapper payloads from this class, and
// expands both there, emitting identical copies (their destructors fold to
// 0x002BEDA4, which stores this class's table 0x00BFE4EC).
class Rva002BED74
{
public:
	Rva002BED74();
	Rva002BED74(EmitVtableTag *);
	virtual ~Rva002BED74();
};

// ??0Rva002BED74@@QAE@XZ @0x002BEDB5 9B: the default constructor, storing the
// class's own vtable and returning this.
inline Rva002BED74::Rva002BED74()
{
}

// ?<Rva002BED74::Rva002BED74> absent-from-retail
Rva002BED74::Rva002BED74(EmitVtableTag *)
{
}

// ??1Rva002BED74@@UAE@XZ @0x002BEDA4 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
inline Rva002BED74::~Rva002BED74()
{
}

// Keeps this unit's emission of the two inline bodies above: compiled without
// inlining, the anchor calls both out of line.
#pragma inline_depth(0)
// ?bfmeAnchorC01Rva002BED74 absent-from-retail
void bfmeAnchorC01Rva002BED74(void *where)
{
	((Rva002BED74 *)where)->Rva002BED74::Rva002BED74();
	((Rva002BED74 *)where)->Rva002BED74::~Rva002BED74();
}
#pragma inline_depth()

class Rva002C1283
{
public:
	Rva002C1283();
	Rva002C1283(EmitVtableTag *);
	virtual ~Rva002C1283() {}
};

// The default constructor at 0x002C127A is emitted by its modal-window
// home, GameWindowManagerModal.cpp. Keep only the vtable-emission overload
// here so that the default constructor has one strong definition.

// ?<Rva002C1283::Rva002C1283> absent-from-retail
Rva002C1283::Rva002C1283(EmitVtableTag *)
{
}

class Rva002D252B
{
public:
	Rva002D252B(EmitVtableTag *);
	virtual ~Rva002D252B() {}
};

// ?<Rva002D252B::Rva002D252B> absent-from-retail
Rva002D252B::Rva002D252B(EmitVtableTag *)
{
}

// Base destructor7B is rowed from RadarWindowOverrideCreatePing.cpp.
// Keep this identical inline view so scalar29 expands the vtable restore.
class Rva002D3556
{
public:
	Rva002D3556(EmitVtableTag *);
	virtual ~Rva002D3556() {}
	virtual void rva002D3D2A() = 0;
	virtual void rva002D4AEF(float, float) = 0;
	virtual void DoStartFade() = 0;
	int references;
};

// ?<Rva002D3556::Rva002D3556> absent-from-retail
Rva002D3556::Rva002D3556(EmitVtableTag *)
{
}

class InputChunk
{
public:
	InputChunk();
	InputChunk(EmitVtableTag *);
	virtual ~InputChunk() {}
};

// ??0InputChunk@@QAE@XZ @0x00306DE0 9B: the default constructor, storing the
// class's own vtable (VA 0x00C07E84) and returning this.
__declspec(noinline) inline InputChunk::InputChunk()
{
}

// ?<InputChunk::InputChunk> absent-from-retail
InputChunk::InputChunk(EmitVtableTag *)
{
}

#include "../../Include/Common/Rva0037F57E.h"

// ??0Rva0037F57E@@QAE@XZ @0x0037F4C0 9B: the empty ctor, installing the
// one-slot vtable 0x00818DFC (slot 0 the deleting dtor below) and returning this.
Rva0037F57E::Rva0037F57E()
{
}

// ??1Rva0037F57E@@UAE@XZ @0x0037F4C9 7B: the empty dtor, restoring the vtable;
// the deleting dtor below still expands it inline.
Rva0037F57E::~Rva0037F57E()
{
}

class Rva00381D78
{
public:
	Rva00381D78();
	Rva00381D78(EmitVtableTag *);
	virtual ~Rva00381D78();
};

// ??0Rva00381D78@@QAE@XZ @0x00381D95 9B: the default constructor, storing the
// class's own vtable and returning this.
Rva00381D78::Rva00381D78()
{
}

// ?<Rva00381D78::Rva00381D78> absent-from-retail
Rva00381D78::Rva00381D78(EmitVtableTag *)
{
}

// ??1Rva00381D78@@UAE@XZ @0x00381D71 7B: the empty dtor, restoring the vtable;
// the deleting dtor still expands it inline.
Rva00381D78::~Rva00381D78()
{
}

#include "../../Include/Common/Rva0039AE75.h"

// ?<Rva0039AE75::Rva0039AE75> absent-from-retail
Rva0039AE75::Rva0039AE75(EmitVtableTag *)
{
}

struct Rva003EE746Color;
struct Rva003EE746Region;
class Rva003EE711
{
public:
	Rva003EE711();
	Rva003EE711(EmitVtableTag *);
	virtual ~Rva003EE711() {}
	virtual Rva003EE746Color color(const Rva003EE746Region *) = 0;
};

// ??0Rva003EE711@@QAE@XZ @0x003EE708 9B: the default constructor, storing the
// class's own vtable (VA 0x00C363B8) and returning this.
__declspec(noinline) inline Rva003EE711::Rva003EE711()
{
}

// ?<Rva003EE711::Rva003EE711> absent-from-retail
Rva003EE711::Rva003EE711(EmitVtableTag *)
{
}

// The complete native15-slot base and its29B deleting destructor now
// belong to Rva0056AC26Base2 in the real registry lifetime unit.

// Native constructors have byte-identical inline copies in their users.
// Keep these providers select-any so those copies can merge.
// ?bfmeAnchorC01FileFactoryClass absent-from-retail
void *bfmeAnchorC01FileFactoryClass(void *where)
{
    ((FileFactoryClass *)where)->FileFactoryClass::FileFactoryClass();
    return where;
}

// ?bfmeAnchorC01InputChunk absent-from-retail
void *bfmeAnchorC01InputChunk(void *where) { return new (where) InputChunk(); }

// ?bfmeAnchorC01Rva003EE711 absent-from-retail
void *bfmeAnchorC01Rva003EE711(void *where)
{
    ((Rva003EE711 *)where)->Rva003EE711::Rva003EE711();
    return where;
}


// The class whose vtable is VA 0x00C38B8C: its deleting dtor 0x00406B1D calls
// the empty Rva00215E42 dtor 0x004059AC, and its default constructor
// 0x00406B14 (9B) and copy constructor 0x00406B5F (11B, ret 4) only store its
// own vtable - the same shapes as Rva00215E42's 0x0029A287 and 0x004059B3
// above. Derived from Rva00215E42: the base members expand inline here, the
// base vptr store dies under the derived one in both constructors, and the
// empty derived destructor reduces to the base's restore of VA 0x00BE5838 -
// byte for byte the 0x004059AC body, so the linker folded the two (its row
// is an ICF alias of ~Rva00215E42).
class Rva00406B14 : public Rva00215E42
{
public:
	Rva00406B14();
	Rva00406B14(const Rva00406B14 &);
	virtual ~Rva00406B14();
};

Rva00406B14::Rva00406B14()
{
}

Rva00406B14::Rva00406B14(const Rva00406B14 &)
{
}

// ??1Rva00406B14@@UAE@XZ @0x004059AC 7B: ICF-folded with ~Rva00215E42 (the
// deleting dtor 0x00406B1D calls it there).
Rva00406B14::~Rva00406B14()
{
}
