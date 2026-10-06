// ?rva0028F44C@Object@@QAE_NPAV1@@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /G7
//
// SCRATCH CANDIDATE - NOT COMPILED, NOT A MATCH CLAIM.
// Target: Object::rva0028F44C, retail RVA 0x0028F44C, 112 bytes
// [0x0028F44C, 0x0028F4BC), __thiscall + callee-popped one argument (ret 4 at
// 0x0028F4B9), bool result (callers 0x00508411 / 0x0050843A test al).
//
// Best established home TU: Code/GameEngine/Source/GameLogic/Object/
// ObjectRva002931F5.cpp - it already declares, and already byte-matches,
// every helper this body uses: ThingTemplate::m_flags114 (+0x114),
// Object::m_template (+0x04), Object::m_containedBy (+0x274), and the
// const member void *rva0028C197() (retail 0x0028C197).
// Alternative home: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// (reverse/tu_map.csv proposes 0x0028F44C for it), but that unit declares
// neither +0x04 nor +0x274 nor rva0028C197 yet.
//
// Names are address-qualified. No alliance/horde semantic name is claimed:
// the 0x2000 template bit and the virtual at slot 0x24C are not identified.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

enum KindOfType
{
	KINDOF_DUMMY = 0
};

enum ObjectStatusTypes
{
	STATUS_5F = 0x5F,
	STATUS_60 = 0x60
};

// Established layout: same struct ObjectRva002931F5.cpp matches against
// retail 0x002931F5, which reads the identical +0x114 word with the identical
// 0x2000 mask. +0x114 is a template flag word; its upstream name is NOT
// established and is not spelled here.
struct ThingTemplate
{
	unsigned char m_pad[0x114];
	unsigned int m_flags114;
};

// The interface Object::rva0028C197 returns (it is the +0x250 provider's slot
// 31 interface - the same object LargeGroupBonusUpdateUpdate.cpp calls its
// "contain" interface). Retail calls its vtable slot 0x24C, i.e. the 148th
// virtual (index 147), with one Object* argument and reads a bool answer.
// Gap-count style copied from Rva00490225Slots<96> in
// LargeGroupBonusUpdateUpdate.cpp.
template <int N> class Rva0028F44CSlots : public Rva0028F44CSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0028F44CSlots<0>
{
};

class Object;

class Rva0028F44CContain : public Rva0028F44CSlots<147>
{
public:
	virtual Bool slot147(Object *other) = 0;
};

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Object *rva002931F5(Bool checkProducer);
	Bool rva00293926(KindOfType kind);
	int rva002933CD();
	void *rva0029439D();
	Bool isKindOf(KindOfType kind) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028C197() const;

	// The body under recovery.
	Bool rva0028F44C(Object *other);

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x78 - 0x08];
	ObjectID m_producerID;
	unsigned char m_pad7C[0x274 - 0x7C];
	Object *m_containedBy;
};

// ?rva0028F44C@Object@@QAE_NPAV1@@Z  retail 0x0028F44C, 112 bytes.
//
// Variant A (this file). Statement order chosen to mirror retail:
//   * 0x0028F451 test the argument before anything else (retail: test esi,esi
//     at 0x28F451, je at 0x28F453, before the mask load at 0x28F455);
//   * the mask lives in ONE register (retail mov edx,0x2000 once, then four
//     `test dword ptr [eax+0x114], edx` - a register form, never an immediate
//     `and`), so it must be a source variable, not an inlined literal;
//   * the receiver loop re-tests the loop condition on the advanced pointer
//     (retail 0x28F47A mov ecx,eax / 0x28F47C jmp back to 0x28F45A), so the
//     loop body must NOT fold the parent's test into the condition - the
//     parent's own test is a separate mandatory early return (retail
//     0x28F472/0x28F478), or the second test disappears from the body;
//   * the other object is normalized with the same two-step walk but with no
//     loop (retail 0x28F47E..0x28F49E uses esi, and re-loads esi from the
//     saved parent at 0x28F49E).
Bool Object::rva0028F44C(Object *other)
{
	const UnsignedInt flag = 0x2000;
	if (other == 0)
		return false;

	Object *container = this;
	while ((container->m_template->m_flags114 & flag) == 0)
	{
		Object *parent = container->m_containedBy;
		if (parent == 0)
			return false;
		if ((parent->m_template->m_flags114 & flag) == 0)
			return false;
		container = parent;
	}

	Object *normalized = other;
	if ((normalized->m_template->m_flags114 & flag) == 0)
	{
		Object *parent = normalized->m_containedBy;
		if (parent == 0)
			return false;
		if ((parent->m_template->m_flags114 & flag) == 0)
			return false;
		normalized = parent;
	}

	Rva0028F44CContain *contain = (Rva0028F44CContain *)container->rva0028C197();
	if (contain == 0)
		return false;
	return contain->slot147(normalized);
}

// ---------------------------------------------------------------------------
// Variant B - only if Variant A fails. Same semantics, the advance folded into
// the assignment, which frees one live pointer and is the shape lever for the
// register wall recorded in reverse/re_attempts.log:4110 ("edx-eax swap needs
// shape lever"). Do not run both bodies in one unit: 112 bytes is the whole
// extent, so the second definition is not retail code either.
//
// Bool Object::rva0028F44C(Object *other)
// {
// 	const UnsignedInt flag = 0x2000;
// 	if (other == 0)
// 		return false;
// 	Object *container = this;
// 	for (;;)
// 	{
// 		if ((container->m_template->m_flags114 & flag) != 0)
// 			break;
// 		container = container->m_containedBy;
// 		if (container == 0)
// 			return false;
// 		if ((container->m_template->m_flags114 & flag) == 0)
// 			return false;
// 	}
// 	Object *normalized = other;
// 	if ((normalized->m_template->m_flags114 & flag) == 0)
// 	{
// 		normalized = normalized->m_containedBy;
// 		if (normalized == 0)
// 			return false;
// 		if ((normalized->m_template->m_flags114 & flag) == 0)
// 			return false;
// 	}
// 	Rva0028F44CContain *contain = (Rva0028F44CContain *)container->rva0028C197();
// 	if (contain == 0)
// 		return false;
// 	return contain->slot147(normalized);
// }