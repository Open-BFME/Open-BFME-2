// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Target facts: retail body 0x00464EE7..0x00464FC7 is 224 bytes. VA 0x00C435E8
// is the OpenContain primary vtable; entry 19 at 0x00C43634 contains VA
// 0x00864EE7. The body copies the list at this+0x54, compares each member's
// controlling player to the argument's, checks the template byte at +0x10C,
// accesses AI at Object+0x258, and returns true. Its helper calls are pinned
// by their retail direct-call targets below.
//
// Structural inferences: OpenContain ownership follows from primary-vtable
// membership; m_object at +8 and its +0x20 interface follow the module layout
// used by neighboring OpenContain recovery. The copied list is viewed as
// list<int>, matching the existing OpenContain field/copy-constructor bodies.
// The method name and both helper identities remain address-derived; the
// donor OpenContain::onCollide behavior is only a semantic lead and is not
// used as target identity evidence.

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// The target REL32 at 0x00464EFE selects the list<int> copy-constructor
// twin at 0x0036ADF9. Its existing gen-alias record ties it to the typed
// list copy body; this local wrapper stores exactly that list at offset zero.
// The constructor keeps its name address-derived because no wider identity is
// claimed for this 88-byte EH-operand variant.

class Player;
class ThingTemplate
{
public:
	char m_pad00[0x10C];
	unsigned char m_kindFlags;
};

class Rva00373EC6
{
public:
	void rva0037446E(int, int, int, int);
};

class Rva00439E0C;
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0x258 - 0x08];
	void *m_ai;
	char m_pad25c[0x274 - 0x25c];
	// Target body 0x00464120 clears this dword with `and [object+0x274],0`.
	// Its semantic field name is not established by the retail accesses here.
	unsigned int m_word274;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	void kill(DamageType, DeathType);
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiExit(Object *, CommandSourceType);
};

class OpenContainActionIface
{
public:
	virtual void slot00() {}
	virtual void slot01() {}
	virtual void slot02() {}
	virtual void slot03() {}
	virtual void slot04() {}
	virtual void slot05() {}
	virtual void slot06() {}
	virtual void slot07() {}
	virtual void slot08() {}
	virtual void slot09() {}
	virtual void slot10() {}
	virtual void slot11() {}
	virtual void slot12() {}
	virtual void slot13() {}
	virtual void slot14() {}
	virtual void slot15() {}
	virtual void slot16() {}
	virtual void slot17() {}
	virtual void slot18() {}
	virtual void slot19() {}
	virtual void slot20() {}
	virtual void slot21() {}
	virtual void slot22() {}
	virtual void slot23() {}
	virtual void slot24() {}
	virtual void slot25() {}
	virtual void slot26() {}
	virtual void slot27() {}
	virtual void slot28() {}
	virtual void slot29() {}
	virtual void slot30() {}
	virtual void slot31() {}
	virtual void rva00465011(Object *object);
	virtual void slot33() {}
	virtual void slot34() {}
	virtual void slot35() {}
	virtual void rva00463138();
	virtual void slot37() {}
	virtual void slot38() {}
	virtual void slot39() {}
	virtual void slot40() {}
	virtual void rva00464EE7Action(Object *, int);
};

class AIUpdateInterfaceView
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

class Rva00439E0C
{
public:
	void rva00439E0C(Object *, int, int, int);
};

class GameLogic
{
public:
	char m_pad00[0x178];
	Rva00439E0C *m_178;
	void destroyObject(Object *);
};

extern GameLogic *TheGameLogic;

typedef _STL::list<int, _STL::allocator<int> > IntList;

class Rva0036ADF9ListCopy
{
public:
	Rva0036ADF9ListCopy(const IntList &source);
	~Rva0036ADF9ListCopy() {}
	IntList m_list;
};

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

class OpenContain
{
public:
	virtual ~OpenContain();
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void onDelete();
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void rva00464286() = 0;
	virtual bool rva00464EE7(Object *object);
private:
	friend class OpenContainActionIface;
	void *m_moduleData;
	Object *m_object;
	char m_pad0C[0x14];
	OpenContainActionIface m_iface20;
	char m_pad24[0x30];
	IntList m_containList;
	char m_pad58[0xDF - 0x58];
	// Retail sets this target-proven byte before constructing its list snapshot.
	unsigned char m_byteDF;
};

// Target facts: 0x00465011 is slot 32 of the OpenContain +0x20 interface
// vtable at 0x00C433B0. The body snapshots the list at parent+0x54, checks
// each rider's AI pointer at Object+0x258, and calls the already matched
// aiExit body at 0x0036F39B with the parent Object and the method argument.
// The argument's semantic role is unresolved; this address-derived slot name
// follows the target address rather than assigning a donor method name.
//
// Structural inference: this is the interface subobject at parent+0x20, as
// shown by the target's accesses at this+0x34 and this-0x18. OpenContain field
// layout is carried from adjacent target-matched bodies in this TU.
void OpenContainActionIface::rva00465011(Object *object)
{
	OpenContain *contain = (OpenContain *)((char *)this - 0x20);
	Rva0036ADF9ListCopy riders(contain->m_containList);
	for (IntList::iterator it = riders.m_list.begin(); it != riders.m_list.end(); ++it)
	{
		Object *rider = (Object *)*it;
		if (rider->m_ai != 0)
		{
			AIUpdateInterfaceView *currentAI = (AIUpdateInterfaceView *)rider->m_ai;
			Object *owner = contain->m_object;
			currentAI->m_command.aiExit(owner, (CommandSourceType)(unsigned long)object);
		}
	}
}

// Target facts: 0x00463138 is an 89-byte body at slot 36 of the OpenContain
// +0x20 interface vtable at 0x00C433B0. It walks the live list at parent+0x54,
// tests each rider template's +0x10C flag bit 1, conditionally calls the
// rowed Object::rva0028F4BC result with (0,1,0,1), then calls the pinned
// GameLogic subobject method at +0x178 with (rider,0,0,1). These accesses and
// call targets are target-proven; the address-derived method name carries no
// stronger semantic claim.
//
// Structural inference: the vtable slot belongs to the +0x20 OpenContain
// interface view established by slot 32 in this TU. The method saves the next
// list iterator before invoking either helper, matching the target's load
// order. The role of the flag and the GameLogic call remains unresolved.
void OpenContainActionIface::rva00463138()
{
	OpenContain *contain = (OpenContain *)((char *)this - 0x20);
	IntList::iterator it = contain->m_containList.begin();
	while (it != contain->m_containList.end())
	{
		Object *rider = (Object *)*it;
		const bool flagged = (rider->m_template->m_kindFlags & 2) != 0;
		++it;
		if (flagged)
		{
			Rva00373EC6 *helper = rider->rva0028F4BC();
			if (helper != 0)
				helper->rva0037446E(0, 1, 0, 1);
			TheGameLogic->m_178->rva00439E0C(rider, 0, 0, 1);
		}
	}
}

bool OpenContain::rva00464EE7(Object *object)
{
	Rva0036ADF9ListCopy riders(m_containList);
	for (IntList::iterator it = riders.m_list.begin(); it != riders.m_list.end(); ++it)
	{
		Object *rider = (Object *)*it;
		if (rider->getControllingPlayer() == object->getControllingPlayer())
			continue;

		if ((rider->m_template->m_kindFlags & 2) != 0)
		{
			if (rider->m_ai != 0)
			{
				Rva00373EC6 *helper = rider->rva0028F4BC();
				if (helper != 0)
					helper->rva0037446E(0, 1, 0, 1);
				TheGameLogic->m_178->rva00439E0C(rider, 0, 0, 1);
				Object *owner = m_object;
				AIUpdateInterfaceView *currentAI = (AIUpdateInterfaceView *)rider->m_ai;
				currentAI->m_command.aiExit(owner, CMD_FROM_AI);
			}
			else
			{
				m_iface20.rva00464EE7Action(rider, 1);
			}
		}
	}
	return true;
}

// Target facts: retail extent at 0x00464120 is 145 bytes. The existing
// OpenContain::onDelete pin and SiegeEngineContain primary slot-8 caller at
// 0x0047BB6B identify this method and preserve the primary receiver. Retail
// bytes copy the list at +0x54 through 0x0036ADF9, set byte +0xDF, dispatch
// through the +0x20 interface at vtable slot +0xA4, clear the rider dword at
// +0x274, and test template byte +0x113 bit 2 before calling rowed
// Object::kill (0x002984D4) or GameLogic::destroyObject (0x00242C09). The local
// list destructor call is 0x004EC395. List and interface layouts follow the
// adjacent byte-matched OpenContain methods in this TU; the +0x274 dword keeps
// a raw name because its meaning is not established by these accesses.
//
// Donor provenance: Open-BFME-1 revision 6583b3c1ff21db4a561285717028fdafc780b7db,
// GameLogic/Object/Contain/OpenContainOnDelete.cpp, supports the cleanup
// sequence semantically. Its offsets and manual list view do not establish
// BFME2 layout or ABI; those are supported above by BFME2 retail evidence.
void OpenContain::onDelete()
{
	m_byteDF = 1;
	Rva0036ADF9ListCopy riders(m_containList);
	for (IntList::iterator it = riders.m_list.begin(); it != riders.m_list.end(); ++it)
	{
		Object *rider = (Object *)*it;
		m_iface20.rva00464EE7Action(rider, 1);
		rider->m_word274 &= 0;
		if ((((unsigned char *)rider->m_template)[0x113] & 4) != 0)
			rider->kill((DamageType)8, (DeathType)0);
		else
			TheGameLogic->destroyObject(rider);
	}
}
