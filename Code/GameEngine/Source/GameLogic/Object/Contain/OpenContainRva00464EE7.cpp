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
class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0x258 - 0x08];
	void *m_ai;
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
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
	virtual void slot36() {}
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
