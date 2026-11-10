// cl: /DNDEBUG /MD
// Split from VslotSmallBodiesAI.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Vtable-slot forwarders with no ledger owner and no Ghidra entry, batch AI:
// each loads a member (or takes a member's address) and tail-jumps to a
// rowed or pinned method, or to a virtual slot of the member. As in
// VslotSmallBodiesA-AH, classes and methods are address-derived unless the
// ledger names them, and model only what each body touches.

typedef int Int;
typedef unsigned int UnsignedInt;

// Native 0x0059B14E..0x0059B19A (RET 4): a nonzero input selects an
// experience-level handle with the receiver's +0x08 value; a valid handle
// adds its award to +0x04. The receiver's original identity is unknown.
// The two-word handle and award query agree with ExperienceLevelSystem.cpp.
class ExperienceLevelList;
struct ExperienceLevelNode;
class Rva00288CFA;
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
// Virtual slot N of a member object.
template <int N>
class Rva004888F8Slots : public Rva004888F8Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <>
class Rva004888F8Slots<0>
{
};
template <int N>
class Rva004888F8Target : public Rva004888F8Slots<N>
{
public:
	virtual void target();
};

// 0x004888F8: slot 4 of the +0x24 object.
class Rva004888F8
{
public:
	void rva004888F8();
private:
	char m_pad00[0x24];
	Rva004888F8Target<4> *m_24;
};


// 0x005778C9: slot 2 of the +0x3C object.
// 0x005C3525: slot 5 of the +0x08 object.
// 0x005CC9C3: slot 1 of the +0x24 object.
// 0x0060037E and 0x00600386 (three tables each): slots 2 and 3 of the
// +0x08 object.
// 0x002ABC76: the rowed AsciiStringRef::write of the +0x04 reference.
#include "../../Include/Common/AsciiStringRef.h"
// 0x0057433D: the rowed getter 0x0042D6B4 of the +0x08 object.
// 0x005753AC (two tables): the rowed RAMFile::write of the +0x04 file,
// called directly.
#include "../../Include/Common/RAMFileClass.h"
// 0x005785CD: target starts after the ret at 0x005785CC and ends at the ret
// before the rowed 0x005785F6 entry. It conditionally calls the rowed
// StrategicHUD::CommandUIImpl::Update 0x005D2A53 for this+0x44 then the shared
// empty body 0x000B3FD0 for this+0x4C and this+0x48. Field ownership and the
// address-derived class identity are structural views.
namespace StrategicHUD { class CommandUIImpl { public: void Update(); }; }
#include "../../Include/Common/Rva000B3FD0.h"
class Rva005785CD
{
public:
	void rva005785CD();

private:
	char m_pad00[0x44];
	StrategicHUD::CommandUIImpl *m_commandUI;
	Rva000B3FD0 *m_48;
	Rva000B3FD0 *m_4C;
};
void Rva005785CD::rva005785CD()
{
	if (m_commandUI != 0)
		m_commandUI->Update();
	if (m_4C != 0)
		m_4C->rva000B3FD0();
	if (m_48 != 0)
		m_48->rva000B3FD0();
}

// 0x0059B19A: the rowed length 0x00513E03 of the +0x04 object.
// 0x005FC9F8 (two tables): the rowed 0x005FC8FD of the +0x18 object.
#include "../../Include/GameClient/ArmyMemberIconMovieClip.h"
namespace StrategicHUD {
}

class StrategicHUD::ArmyMemberIconMovieClip::Impl
{
public:
	void Update();
};
// 0x0044BD53: the rowed handle 0x0044BD5B on the +0x08 member.
// 0x0044BDF7 (8B): slot 4 of the same table (VA 0x00C3EDF0 holds
// 0x0044BD53, ..., 0x0044BDF7): the rowed functor fire 0x0044BDFF on the
// +0x08 member.
// 0x00575CA6: the rowed clear 0x000AD6F4 on the +0x24 member.
#include "../../Include/Common/Rva000AD6F4.h"
// 0x00575CAE: allocates the rowed 0x14-byte helper 0x0057551C from the
// adjusted owner pointer, then stores it through the rowed setter at +0x28.
// The helper identity follows the direct constructor call; owner type is
// address-derived and the -4/+0x28 offsets come from the target instructions.
// 0x0057956D and 0x0057B9D0: assignment of the argument to the +0x18 (resp.
// +0x30) tree hint through its rowed operator=.
// 0x0057A35A and 0x0057A37A: the rowed getter 0x0049CB82 resp. 0x005D4118
// on the +0x08 member.
namespace StrategicHUD { class ChecklistUIItemMovieClip; }
class StrategicHUD::ChecklistUIItemMovieClip
{
public:
	void Flash();
};
// 0x00456A3E: the rowed reset 0x0026549E on the +0x100 member.
// 0x005785F6, 0x005785FE, 0x00578606, 0x0057860E and 0x00578646: the rowed
// methods 0x0057E556, 0x005D3776, 0x0036CBE7, 0x005D3846 resp. 0x004C54EC
// of the +0x4C object.
class Image;
class UnicodeString;
// 0x005666BA: the rowed vector push_back 0x00566575 on the +0x90 member.
struct Rva00566575Element;
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	void push_back(const T &x);
};
}
// Forwarders through a member pointer to a member of the pointee: the rowed
// Rva000AD6F4::clear (or the rowed 0x0057702E) on member +B of the object
// at +A.
class Rva0057702E
{
public:
	void rva0057702E();
};
struct Rva0057708FInner
{
	char m_pad00[0x14];
	Rva0057702E m_14;
};
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::Selection::DeselectThis,
// retail 0x0057708F: slot 5 of the selection's vftable 0x00C6E858 (installed
// at +0 by its destructor 0x00576F48 and constructor 0x005774E3; nothing
// calls it directly). WB's twin table 0x01F4871C holds WB 0x014CE670,
// DeselectThis, in slot 5 beside the same HeroArmySelectionHandler slots 0
// and 1. It clears the owning Impl's +0x14 selection holder.
namespace StrategicInGameUI
{
class PlanRetreatsPhaseBehavior
{
public:
	class Impl;
};
}
class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl
{
public:
	class Selection;
};
class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::Selection
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04();
	virtual void DeselectThis();	// slot 5
private:
	char m_pad04[0x14 - 0x04];
	Rva0057708FInner *m_14;	// the owning Impl
};

struct Rva005770CBInner
{
	char m_pad00[0x14];
	Rva0057702E m_14;
};
class Rva005770CB
{
public:
	void rva005770CB();
private:
	char m_pad00[0x08];
	Rva005770CBInner *m_08;
};


// 0x0057709A: derived ctor of Rva005CBA04 storing vtable 0x00C6E8A8, base temp from global 0x00E0660C, outer arg at +8.
#include "../../Include/Common/BfmeFixedStorage002CF0F0.h"
extern unsigned g_Va00E0660C;
// The retail table at RVA 0x0086E8A8: 19 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00576FCE@@UAEPAXI@Z")();
void __identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?rva0057548A@Rva0057548A@@UAEHPAUParent00575E4E@@@Z")();
void __identifier("?testBit@Rva005CBA3D@@QAEHI@Z")();
void __identifier("?rva005770CB@Rva005770CB@@QAEXXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?selectArmy@Rva0057709A@@QAEXH@Z")();
void __identifier("??_ERva005770F7@@W3AEPAXI@Z")();
void __identifier("?rva00576FFE@Rva00576FFE@@QAEHXZ")();
}
extern const void *const g_00C6E8A8[19] = {
	(const void *)&__identifier("??_GRva00576FCE@@UAEPAXI@Z"), // slot 0 0x005E5A66
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 1 0x005CB9FF
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 2 0x005CB9FF
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 3 0x005CB9FF
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 4 0x005CB9FA
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 5 0x005CB9FA
	(const void *)&__identifier("?rva0057548A@Rva0057548A@@UAEHPAUParent00575E4E@@@Z"), // slot 6 0x0057548A
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 7 0x005CB9FA
	(const void *)&__identifier("?testBit@Rva005CBA3D@@QAEHI@Z"), // slot 8 0x005CBA3D
	(const void *)&__identifier("?rva005770CB@Rva005770CB@@QAEXXZ"), // slot 9 0x005770CB
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 10 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 11 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 12 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 13 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 14 0x0047A69C
	(const void *)&__identifier("?selectArmy@Rva0057709A@@QAEXH@Z"), // slot 15 0x005775C1
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 16 0x0047A69C
	(const void *)&__identifier("??_ERva005770F7@@W3AEPAXI@Z"), // slot 17 0x00577185
	(const void *)&__identifier("?rva00576FFE@Rva00576FFE@@QAEHXZ"), // slot 18 0x00576FFE
};

class Rva005CBA04
{
public:
	virtual ~Rva005CBA04();
	Rva005CBA04(BfmeFixedStorage002CF0F0 storage);
private:
	BfmeFixedStorage002CF0F0 m_storage;
};

class __declspec(novtable) Rva0057709A : public Rva005CBA04
{
public:
	Rva0057709A(int v);
private:
	int m_08;
};

Rva0057709A::Rva0057709A(int v)
	: Rva005CBA04(*(BfmeFixedStorage002CF0F0 *)&g_Va00E0660C), m_08(v)
{
	*(const void **)this = g_00C6E8A8;
}

// 0x00578616, 0x0057861E, 0x00578626 (8B each), after the +0x4C forwarders
// above in the same Palantir vtable run: the +0x48 object receives the two
// ints through the leaf thunks 0x005D3272/79/80 (Rva005D3287Thunk.cpp).
// 0x005CC4DA..0x005CC538 (six bodies in two tables, 11 bytes each): slot N
// of the object at +0x08 of the receiver's +0x10 object, as a tail jump.
template <int N>
struct Rva005CC4DAInner
{
	char m_pad00[0x08];
	Rva004888F8Target<N> *m_08;
};

// 0x005CC4DA: slot 2.
// 0x005CC4E5: slot 5.
// 0x005CC4F0: slot 6.
// 0x005CC522: slot 1.
// 0x005CC52D: slot 4.
// 0x005CC538: slot 3.
// 0x005CC984..0x005CC9B8 (one table, RET 4 with the argument unused): slot N
// of the +0x24 object; the two middle bodies first set (slot 3) or clear
// (slot 4) the +0x23 flag.
// Slot N taking two integer arguments.
template <int N>
class Rva005EA539Target : public Rva004888F8Slots<N>
{
public:
	virtual void target(Int a, Int b);
};


// 0x005EA539: slot 4 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
// 0x005EA54D: slot 5 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
// 0x005EA561: slot 6 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
// 0x00494ABE (RET 4, argument unused): the receiver's own slot 2.
// 0x005CFB93 (RET 4, argument unused): slot 1 of the +0x08 object.
// 0x005D1358: tail jump to slot 2 of the object the +0x08 object points to
// first.
// 0x005EA052: tail jump to slot 1 of the +0x04 object of the +0x08 object.
// 0x00575DDA, 0x00575DE6 and 0x00575DF2: pass the receiver's +0x0C word to a
// rowed method of the +0x04 object.
struct Rva005757F9Value;
// 0x005EA254: drops the +0x08 count and, once it reaches zero, runs the
// rowed 0x005EA0C0 on the +0x04 object.
// 0x003698A5 and 0x003698BB (RET 8): the receiver's rowed 0x00368E95 toward
// an object's +0x38 position (flag set) or toward a given position (flag
// clear), with the waypoint passed through.
struct Coord3D;
class Waypoint;
// 0x005CCB0E (RET 4, argument unused): the receiver's rowed
// StrategicInGameUI::ChecklistItem::Impl 0x005CCA57.
namespace StrategicInGameUI
{
	class ChecklistItem
	{
	public:
		class Impl
		{
		public:
			void rva005CCA57();
		};
	};
}
