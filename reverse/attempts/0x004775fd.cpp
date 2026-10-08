// ?exitObjectViaDoor@HordeTransportContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.89 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail target 0x004775FD is the slot-2 body in the ExitInterface vtable
// installed at HordeTransportContain +0x30 by its matched constructor
// 0x00477003. AIExitStateMethods.cpp gives slot 2 the (Object*, ExitDoorType)
// ABI. The target checks the horde template flag, materializes the nested
// contain list through slots 0x7C/0x108, notifies each child through slot 0xA8,
// then delegates each exit and the original exit to 0x0046525F. That callee's
// identity remains address-derived; WB's callgraph lead and OpenContain's
// source method suggest exitObjectViaDoor but do not prove its body identity.
#include <list>

typedef _STL::list<int, _STL::allocator<int> > IntList;

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

class Object;
class ContainedListInterface;

template<int N> class ContainVSlots : public ContainVSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class ContainVSlots<0>
{
};

class ObjectContainInterface : public ContainVSlots<31>
{
public:
	virtual ContainedListInterface *slot7C() = 0;
};

class Rva0036AE51ListView
{
public:
	void *m_begin;
	IntList *m_list;
	IntList rva0036AE51();
};

class ContainedListInterface : public ContainVSlots<42>
{
public:
	virtual void slotA8(Object *obj) = 0;
	virtual void gap43() = 0;
	virtual void gap44() = 0;
	virtual void gap45() = 0;
	virtual void gap46() = 0;
	virtual void gap47() = 0;
	virtual void gap48() = 0;
	virtual void gap49() = 0;
	virtual void gap50() = 0;
	virtual void gap51() = 0;
	virtual void gap52() = 0;
	virtual void gap53() = 0;
	virtual void gap54() = 0;
	virtual void gap55() = 0;
	virtual void gap56() = 0;
	virtual void gap57() = 0;
	virtual void gap58() = 0;
	virtual void gap59() = 0;
	virtual void gap60() = 0;
	virtual void gap61() = 0;
	virtual void gap62() = 0;
	virtual void gap63() = 0;
	virtual void gap64() = 0;
	virtual void gap65() = 0;
	virtual Rva0036AE51ListView slot108() = 0;
};

struct ObjectTemplate
{
	unsigned char pad[0x115];
	unsigned char flags;
};

class Object
{
public:
	void *m_vtable;
	ObjectTemplate *m_template;
	unsigned char pad08[0x248];
	ObjectContainInterface *m_contain;
	unsigned char pad254[0x200];
	unsigned char m_454;
};

enum ExitDoorType
{
	EXIT_DOOR_0 = 0
};

class Rva0046525F
{
public:
	void rva0046525F(Object *obj, ExitDoorType exitDoor);
};

class __declspec(novtable) HordeTransportContain
{
public:
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);
};

void HordeTransportContain::exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor)
{
	if ((newObj->m_template->flags & 0x20) == 0) {
		((Rva0046525F *)this)->rva0046525F(newObj, exitDoor);
		return;
	}

	ContainedListInterface *contain = newObj->m_contain->slot7C();
	if (contain == 0)
		return;
	IntList objects = contain->slot108().rva0036AE51();
	for (IntList::iterator it = objects.begin(); it != objects.end(); ++it) {
		Object *rider = (Object *)*it;
		if (rider->m_454 == 0) {
			contain->slotA8(rider);
			((Rva0046525F *)this)->rva0046525F(rider, exitDoor);
		}
	}
	for (IntList::iterator it = objects.begin(); it != objects.end(); ++it) {
		Object *rider = (Object *)*it;
		contain->slotA8(rider);
		((Rva0046525F *)this)->rva0046525F(rider, exitDoor);
	}
	((Rva0046525F *)this)->rva0046525F(newObj, exitDoor);
}
