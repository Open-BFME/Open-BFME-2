// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1ProductionUpdateModuleData@@UAE@XZ, retail 0x0049E2B3, 153 bytes.
//
// ProductionUpdate data dtor over INI table 0x00C517F0 (companion of the ctor
// TU ProductionUpdateModuleDataCtor.cpp, which documents the member layout).
// Destruction order, read from the descending EH states 4..0:
//
//   state 4 (body): walk the +0x3C modifier list null-testing each value,
//     delete heap entries through ??1ProductionModifierEntry (rowed
//     0x0049D12D) plus operator delete (rowed 0x002FD60), then clear the
//     nodes through the rowed _List_base clear at 0x0023DAA5. The value is a
//     named local, which homes it to [ebp-0x10] for the delete push.
//   state 3: the +0x48 nullable holder through the pinned PoolMember op at
//     0x0050ED3. The +0x48 field is NOT an AsciiString (the ctor TU only
//     zero-initializes it, which is byte-identical either way); it is a
//     nullable pointer with Release_Ref semantics, destroyed by an inline
//     dtor so the test/je/call stays inline.
//   state 2: the +0x44 AsciiString through the folded 0x0036410.
//   state 1: the +0x3C list base through the rowed 0x004EC395, kept external
//     by a declared-only explicit specialization (ctor-TU twin-pin pattern;
//     the inline header body would otherwise inline here).
//   state 0: the +0x1C QuantityModifier vector through the rowed 0x0049E274,
//     likewise via declared-only explicit specialization.
//
// The entry vtable store (0x00C515F0) is the compiler's virtual-dtor store
// (rewritten by the gate); the exit restore to the ModuleData base table
// 0x00BBB554 is the TU-local Snapshot base's inline dtor (LargeGroupBonus
// precedent). Members are declared in offset order so reverse destruction
// yields states 3/2/1/0.

#include <list>
#include <vector>

typedef int Int;

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class ProductionModifierEntry
{
public:
	~ProductionModifierEntry();

private:
	AsciiString m_name; // +0
	Rva00360D26Member m_filter; // +4
};

struct QuantityModifier;

struct PoolMember
{
	void Rva0050ED3();
};

// Nullable Release_Ref holder at +0x48. Inline dtor keeps the null check and
// the release call inline under state 3.
struct NullablePoolRef
{
	~NullablePoolRef()
	{
		if (m_ptr != 0)
			m_ptr->Rva0050ED3();
	}

	PoolMember *m_ptr;
};

// 12B list node mirror for the body walk (next at +0, value pointer at +8;
// prev at +4 never read here).
struct ModifierListNode
{
	ModifierListNode *m_next;
	ModifierListNode *m_prev;
	ProductionModifierEntry *m_value;
};

namespace _STL
{

// Declared-only explicit specializations: keep the member-destruction calls
// external (resolved through the ledger rows) and throwing (retail states).
template <>
_List_base<Int, allocator<Int> >::~_List_base();
template <>
vector<QuantityModifier, allocator<QuantityModifier> >::~vector();

}

// ModuleData stand-in: virtuals give the derived dtor its entry vtable
// store; the inline dtor restores the base table 0x00BBB554 after all
// members fall (LargeGroupBonus precedent).
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class ProductionUpdateModuleData : public Snapshot
{
public:
	virtual ~ProductionUpdateModuleData();

private:
	// +0 is the base vptr (retail 0x00C515F0); no explicit slot follows, so
	// members land on the ctor TU's offsets.
	int m_unused04; // +4, untouched padding
	Int m_numDoorAnimations; // +8
	unsigned int m_doorOpeningTime; // +0xC
	unsigned int m_doorWaitOpenTime; // +0x10
	unsigned int m_doorClosingTime; // +0x14
	unsigned int m_constructionCompleteDuration; // +0x18
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > m_quantityModifiers; // +0x1C
	Int m_maxQueueEntries; // +0x28
	unsigned int m_disabledTypesToProcess; // +0x2C
	bool m_giveNoXP; // +0x30
	unsigned int m_unitInvulnerableTime; // +0x34
	unsigned int m_specialPrepModelconditionTime; // +0x38
	_STL::_List_base<Int, _STL::allocator<Int> > m_modifierList; // +0x3C, element type unproven; storage only
	bool m_veteranUnitsFromVeteranFactory; // +0x40
	bool m_setBonusModelConditionOnSpeedBonus; // +0x41
	AsciiString m_bonusForType; // +0x44
	NullablePoolRef m_poolRef; // +0x48, nullable Release_Ref holder (not a string)
	bool m_secondaryQueue; // +0x4C
};

// ??1ProductionUpdateModuleData@@UAE@XZ @0x0049E2B3
ProductionUpdateModuleData::~ProductionUpdateModuleData()
{
	// Named reference binds the list address to ebx for the head loads, the
	// clear call and the base-dtor call alike (ctor-TU precedent); the head
	// itself stays a reloaded rvalue so the loop compares against [ebx].
	_STL::_List_base<Int, _STL::allocator<Int> > &modifiers = m_modifierList;
	ModifierListNode *node = (*reinterpret_cast<ModifierListNode **>(&modifiers))->m_next;
	while (node != *reinterpret_cast<ModifierListNode **>(&modifiers))
	{
		ProductionModifierEntry *value = node->m_value;
		if (value != 0)
			delete value;
		node = node->m_next;
	}
	modifiers.clear();
}
