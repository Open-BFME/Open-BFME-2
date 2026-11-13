// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??1Rva00575F38@@UAE@XZ retail 0x00575F38..0x00576021 (233 bytes EH).
// The destructor the scalar deleting dtor 0x005760E9 calls (vtable
// 0x00C6E720). WorldBuilder twin 0x014D3330 (unnamed) has the same shape.
// Five bases: +0x00 phase interface over Base0_00576C4B (reset to
// 0x00BDBA74; constructor table 0x00C6E430), +0x04
// VBase00C6EE28 (0x00C6EE28) +0x08 BfmeCtorVirtualBase001B3A20 (0x00C078DC)
// +0x0C the rowed Rva005CD1A9 (out-of-line dtor 0x005CD1A9) and +0x14
// Rva005753E9 (0x00C6E5C4); the derived vtables are 0x00C6E720 0x00C6E700
// 0x00C6E6EC 0x00C6E6E4 and 0x00C6E6B8. Target evidence: the +0x18 owner's
// +0x04 object gives (rowed getter 0x00574AAC) the receiver of the rowed
// 0x005CB84A(0); when the rowed check 0x002B254F on TheLivingWorldLogic
// passes the +0x14 base is erased (rowed 0x002B7250 on the +0x04 list of
// the object returned by 0x002B256E called on TheLivingWorldLogic); then
// the members die: +0x40 (rowed Rva005CD651 dtor) +0x30 (0x005CD7DA)
// +0x2C and +0x28 (rowed Rva000AD6F4 dtor 0x000AD6F4) and +0x24
// (0x0055076F). The retained address-derived spelling is the rowed destructor's.
// WB identifies the owning phase as PlanningPhaseBehavior::Impl through its
// translateGameMessage table slot; member type names remain borrowed views.
//
// Constructor 0x0057621A..0x00576323 is 265 bytes, RET 8. The same five
// bases, EH unwind order and 0x50-byte allocation in 0x005763ED establish
// its relationship to this destructor. The owner at +0x18, int +0x1C,
// player index +0x20, and members at +0x24/+0x28/+0x2C/+0x30/+0x40 are
// target evidence. The +0x14 listener base ends at +0x18: the owner belongs
// to the derived object, rather than to that base. The record constructor
// receives one saved owner->m_04 receiver and the +0x0C base pointer. All
// out-of-line callees already have matched bodies; no constructor pin is needed.

#include <new.h>

enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class GameMessage;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class CreateAHeroData;

#include "../../../Include/Common/Rva002B254F.h"

#include "../../../Include/Common/Rva002B7250.h"

struct Rva002B256EOwner
{
	void *m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva002B256E
{
public:
	void *rva002B256E();
};

#include "../../../Include/Common/Rva005CB84A.h"

#include "../../../Include/Common/Rva00574AACAddDwordField.h"

struct Rva00575F38Owner
{
	void *m_00;
	Rva00574AACAddDwordField *m_04; // +0x04
};

#include "../../../Include/GameClient/UserInputTranslator.h"

// The base constructors and destructors use the existing retail tables.
namespace PhaseBaseTables {
extern "C" const void *const __identifier("??_7VBase00C6EE28@@6B@")[];
extern "C" const void *const __identifier("??_7BfmeCtorVirtualBase001B3A20@@6B@")[];
}

class __declspec(novtable) VBase00C6EE28
{
public:
	VBase00C6EE28();
	virtual ~VBase00C6EE28()
	{
		*(const void **)this = PhaseBaseTables::__identifier("??_7VBase00C6EE28@@6B@");
	}
};
// ??0VBase00C6EE28@@QAE@XZ @0x002E701A 9B: the default constructor, storing the
// class's own vtable (VA 0x00C6EE28) and returning this.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
inline VBase00C6EE28::VBase00C6EE28()
{
	*(const void **)this = PhaseBaseTables::__identifier("??_7VBase00C6EE28@@6B@");
}

// ?bfmeAnchorVBase00C6EE28Ctor absent-from-retail
void *bfmeAnchorVBase00C6EE28Ctor(void *where)
{
	return ::new (where) VBase00C6EE28();
}

class __declspec(novtable) BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtorVirtualBase001B3A20()
	{
		*(const void **)this = PhaseBaseTables::__identifier("??_7BfmeCtorVirtualBase001B3A20@@6B@");
	}
	virtual ~BfmeCtorVirtualBase001B3A20()
	{
		*(const void **)this = PhaseBaseTables::__identifier("??_7BfmeCtorVirtualBase001B3A20@@6B@");
	}
};

class Rva005CD1A9
{
public:
	Rva005CD1A9();
	virtual ~Rva005CD1A9();

private:
	int m_04;
};

#include "../../../Include/Common/Rva002B2B66.h"
#include "../../../Include/Common/Rva00328A83PtrChaseField.h"
#include "../../../Include/GameClient/Rva00574A98.h"
#include "../../../Include/Common/Rva005A0B4CList.h"
class Rva005CC61E { public: Rva005CC61E(); private: void *ptr; };

class Rva005753E9
{
public:
	__declspec(dllimport) __forceinline Rva005753E9() {}
	virtual ~Rva005753E9() {}
};

class Rva0055076F
{
public:
	Rva0055076F() : m_member() {}
	~Rva0055076F();

private:
	Rva005CC61E m_member;
};

#include "../../../Include/Common/Rva000AD6F4.h"

class Rva005CD7BD
{
public:
	Rva005CD7BD(void *source, int value, int owner);
private:
	void *m_words[4];
};

// The +0x30 record. Retail's destructor calls its 39-byte cleanup 0x005CD7DA
// directly, and so does the constructor's unwind funclet 0x0079B3ED (jmp
// 0x005CD7DA), so the cleanup is the record's own out-of-line destructor. It
// is bound to that row's existing destructor spelling, as the sibling phase
// units Rva00576C4BDtor.cpp, Rva005776A7Ctor.cpp and Rva005770F7Dtor.cpp do
// (LINK-085); an inline forwarder would emit a body retail does not have.
class Wrap2000576C4B
{
public:
	__forceinline Wrap2000576C4B(void *source, Rva005CD1A9 *owner)
		: m_record(((Rva00574A98 *)source)->rva00574A98(),
			((Rva00328A83PtrChaseField *)source)->get(), (int)owner) {}
	~Wrap2000576C4B();

private:
	Rva005CD7BD m_record;
};

class Rva005CD651
{
public:
	Rva005CD651(int);
	virtual ~Rva005CD651();
private:
	char m_data[12];
};

// Rva00575F38 is PlanningPhaseBehavior::Impl: its vftable 0x00C6E720 holds
// Impl::translateGameMessage 0x00575C15 at slot 0 (StrategicInGameUIPlanningPhaseBehavior.cpp).
class Rva00575D45;
namespace StrategicInGameUI { class PlanningPhaseBehavior { public: class Impl; }; }
class StrategicInGameUI::PlanningPhaseBehavior::Impl : public UserInputTranslator, public VBase00C6EE28, public BfmeCtorVirtualBase001B3A20,
	public Rva005CD1A9, public Rva005753E9
{
public:
	Impl(class Rva00575D45 *owner, int value);
	virtual GameMessageDisposition translateGameMessage(const GameMessage *);
	virtual ~Impl();
	virtual int OnMouseLeftClick(const IRegion2D &, int);

private:
	Rva00575F38Owner *m_owner; // +0x18
	int m_1C;                // +0x1C
	int m_20;                // +0x20
	Rva0055076F m_24;      // +0x24
	Rva000AD6F4 m_28;  // +0x28
	Rva000AD6F4 m_2C;  // +0x2C
	Wrap2000576C4B m_30;   // +0x30
	Rva005CD651 m_40;      // +0x40
};

StrategicInGameUI::PlanningPhaseBehavior::Impl::~Impl()
{
	reinterpret_cast<Rva005CB84A *>(m_owner->m_04->get())->rva005CB84A(0);
	if ((unsigned char)reinterpret_cast<Rva002B254F *>(TheLivingWorldLogic)->rva002B254F())
	{
		reinterpret_cast<Rva002B256EOwner *>(reinterpret_cast<Rva002B256E *>(TheLivingWorldLogic)->rva002B256E())->m_list.rva002B7250(
			reinterpret_cast<CreateAHeroData *>(static_cast<Rva005753E9 *>(this)));
	}
}

StrategicInGameUI::PlanningPhaseBehavior::Impl::Impl(Rva00575D45 *owner, int value)
	: m_owner((Rva00575F38Owner *)owner), m_1C(value),
	  m_20(((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66()),
	  m_30(m_owner->m_04, this),
	  m_40(((Rva00328A83PtrChaseField *)m_owner->m_04)->get())
{
	if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
		((Rva005A0B4CList *)((char *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E() + 4))
			->append((Rva002BA8F1Listener *)(Rva005753E9 *)this);
}
