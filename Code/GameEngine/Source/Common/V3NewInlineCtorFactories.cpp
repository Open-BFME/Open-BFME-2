// cl: -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// BFME1 donor V3NewInlineCtorFactories.cpp at 6d943426. Its opaque class
// labels are retained for the already pinned factory callees; real particle
// module identities remain open. Retail establishes constructor forwarding,
// vptr locations and allocation sizes independently of those donor labels.
//
// BFME2 factories 3AD7CF / 3AD84A / 3ADA36 allocate 5C / 2C / 44 bytes and
// call the two-argument constructors at 3ACE2D / 3ACE8B / 3AD136. The first
// two constructors install vptrs at 0, 14, 18; the third also installs one at
// 20. Native base-constructor targets are 3ABB53 / 3ABBCB / 3ABE8D, which
// forward to the independently rowed particle constructors 5634F7 / 563CAF /
// 5648FE respectively. Storage follows measured full base sizes; member
// purposes remain open. The constructor bodies now live in the upstream
// ModuleCtorChainsA.cpp owner; this factory unit retains only their declarations.
//
// ---- measured layout views; unrecovered members are size carriers ----------

class V3Slot0	{ public: virtual void s0(); virtual ~V3Slot0() {} int m_a, m_b, m_c, m_d; };
class V3Slot0N	{ public: virtual void s0(); virtual ~V3Slot0N() {} int m_a, m_b, m_c, m_d; };
class V3Slot1	{ public: virtual void s0(); virtual ~V3Slot1() {} };
class V3Slot2	{ public: virtual void s0(); virtual ~V3Slot2() {} };
class V3Slot3	{ public: virtual void s0(); virtual ~V3Slot3() {} };

// ---- the two-argument form -------------------------------------------------
//
// NAME is the factory's own address; BASE is the out-of-line constructor's.

#include "../../Include/Common/BfmeAccessorMacros.h"

class V3Slot2Wide { public: virtual void s0(); virtual ~V3Slot2Wide() {} int m_a; };
struct DrawInfo2;
class RvaSmartPtr12;
struct TerrainCollisionModuleInput;
class Rva005634F7 : public V3Slot0N, public V3Slot1, public V3Slot2 {
public: Rva005634F7(void *, DrawInfo2 *);
private: char unknown1C[0x5c-0x1c];
};
class Rva003AE94E : public V3Slot0N, public V3Slot1, public V3Slot2 {
public: Rva003AE94E(void *, void *);
private: char unknown1C[0x2c-0x1c];
};
class Rva003AF076 : public V3Slot0N, public V3Slot1, public V3Slot2Wide, public V3Slot3 {
public: Rva003AF076(const RvaSmartPtr12&, const TerrainCollisionModuleInput&);
    virtual ~Rva003AF076();
private: char unknown24[0x44-0x24];
};
//
// retail 0x003AD7CF, 0x003AD84A and 0x003ADA36, 60 bytes each. Dedicated TU
// ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/V3NewInlineCtorFactories.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os; the emitted bodies are
// byte-identical to retail once relocations are masked. Only the placed bodies
// are defined here; the donor's other definitions are omitted.
//
// Every name here is donor-carried and address-derived: the host after its own
// RVA, the constructed object after its base constructor's. Retail confirms
// each callee is a constructor forwarding two arguments to a base constructor
// before installing its own vtable, which is the shape this macro declares. The
// real types, the base-class identities and the meaning of the `void *arg`
// parameter remain unrecovered; the leaf storage arrays carry measured full sizes
// without assigning names or meanings to unrecovered fields.
V3_NEW_TWO_ARG_FACTORY( Rva005E7420, Rva005EE8A0, 0x5c, Rva005634F7, (arg, (DrawInfo2 *)owner) )
V3_NEW_TWO_ARG_FACTORY( Rva005E76E0, Rva005FFAC0, 0x2c, Rva003AE94E, (arg, (void *)owner) )
V3_NEW_TWO_ARG_FACTORY( Rva005E7AD0, Rva006008D0, 0x44, Rva003AF076, (*(const RvaSmartPtr12 *)arg, *(const TerrainCollisionModuleInput *)owner) )

// ---- the clone form: one argument, and it is the receiver ------------------
//
// The second clone form in the donor is not placed by this TU and its
// declarations are omitted entirely.

class Rva003ABA36 : public V3Slot0, public V3Slot1, public V3Slot2
{
public:
	Rva003ABA36( const Rva003ABA36 & );
};

class Rva005EBCC0Object : public Rva003ABA36
{
public:
	Rva005EBCC0Object( const Rva005EBCC0Object &o );
	Rva005EBCC0Object *clone() const;
	char m_storage[ 0x8e4 - 0x1c ];
};

//
// retail 0x003AE758, 58 bytes. Same donor and /Os placement as the three
// two-argument factories above. Retail shows this body allocating 0x8e4 bytes
// and constructing the fresh block from the receiver, which is the copy
// constructor this form declares.
Rva005EBCC0Object *Rva005EBCC0Object::clone() const
{
	return new Rva005EBCC0Object( *this );
}
