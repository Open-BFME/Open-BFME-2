// cl: /O1 /DNDEBUG /MD
//
// AIUpgrade::build, retail0x0059738A (78 bytes, RET4). The complete
// native17-entry AIUpgrade table atVA C70BD0 places build atslot15
// and getCostPerTick atslot8 (constructor597331 installs this table).
// Identity (target): WorldBuilder's debug AIUpgrade.cpp lines 36..37 names it
// (wb-lead 2/callgraph): the builder object (ObjectID +0x08) runs the upgrade's
// command button (+0x30) through Object::doCommandButton (0x00296749, flags
// 1 and 0), then the object query 0x0028BC58(0) is asked through its slot 6
// about the button's +0x24 field, and that answer is returned.
// The slot-6 receiver and the argument are not identified by target evidence
// and stay opaque.

#include "../../../Common/GameLogicObjectLookupView.h"

class CommandButton
{
public:
	int getField24() const { return m_field24; }

private:
	unsigned char m_pad00[0x24];
	int m_field24; // +0x24 retail-measured
};

// Opaque receiver returned by Object::rva0028BC58; slot 6 answers the query.
class Rva0028BC58Result
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual char slot6(int value);
};

class AsciiString;
class Object
{
public:
	void doCommandButton(const CommandButton *commandButton, int cmdSource, bool flags);
	void *rva0028BC58(int which);
	const AsciiString *rva00290E67() const;
	char m_pad00[0x4];
};

extern GameLogic *TheGameLogic;

// The lookup chain is visible in this unit, as in ProjectileNuggetObjectEffect.cpp:
// storage and traversal from native _M_find 0x002888D4 and GameLogic::findObjectByID
// 0x00049DC5 (both rowed; out-of-line COMDAT copies). Seeing that neither touches
// TheGameLogic nor the AIUpgrade lets rva005973D8 keep both lookup operands in
// EBX/EDI across its two calls, as retail does.
struct AIUpgradeLookupNode { AIUpgradeLookupNode *next; ObjectID key; Object *object; };
struct AIUpgradeLookupBuckets {
 AIUpgradeLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 AIUpgradeLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct AIUpgradeLookupMap { unsigned char hashEqual[4]; AIUpgradeLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 AIUpgradeLookupMap *map=(AIUpgradeLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 AIUpgradeLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

class AIUpgrade
{
public:
	virtual ~AIUpgrade();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7(int value);
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual bool build(void *context); // native slot15
	virtual void slot16();
	int rva005973D8();
	void rva005975C0();

private:
	unsigned char m_pad04[0x08 - 0x04];
	ObjectID m_builderID; // +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	int m_remaining10; // +0x10
	unsigned char m_pad14[0x30 - 0x14];
	const CommandButton *m_commandButton; // +0x30
};

bool AIUpgrade::build(void *context)
{
	TheGameLogic->findObjectByID(m_builderID)->doCommandButton(m_commandButton, 1, 0);
	ObjectID id = m_builderID;
	Rva0028BC58Result *result = (Rva0028BC58Result *)TheGameLogic->findObjectByID(id)->rva0028BC58(0);
	return result->slot6(m_commandButton->getField24()) ? true : false;
}

// Native 0x005973D8..0x00597426 (78B, RET0) follows build; WB 0x01537BF0 (AIUpgrade.cpp)
// gives the shape: with a positive count at +0x10, an existing builder object answers
// slot 6 of its rva0028BC58(0) query about the button's +0x24 field; no answer -> 1.
// Original name unproven.
int AIUpgrade::rva005973D8()
{
	if (m_remaining10 > 0) {
		if (TheGameLogic->findObjectByID(m_builderID) != 0) {
			Rva0028BC58Result *result = (Rva0028BC58Result *)TheGameLogic->findObjectByID(m_builderID)->rva0028BC58(0);
			if (result->slot6(m_commandButton->getField24()))
				return 0;
		}
		return 1;
	}
	return 0;
}

// Native5975C0..5975D7: retain this across the existing int-returning
// helper5973D8, test only AL, and dispatch slot7 with2 when set. The
// explicit low-byte conversion preserves that observed test without a
// second callee name or a different declaration for its return type.
// Constructor597331 installs C70BD0: the complete17-entry table places
// this dispatch at1C and build at3C; the following word is float400.
// Unused slot declarations above express positions only, not their ABI.
void AIUpgrade::rva005975C0()
{
    if (static_cast<unsigned char>(rva005973D8()))
        slot7(2);
}
