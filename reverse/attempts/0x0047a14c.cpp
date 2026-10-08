// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z,
// retail 0x0047A14C..0x0047A251 (261 bytes, EH, RET 8): slot 2 of
// HordeGarrisonContain's exit interface (+0x30), Zero Hour's
// ExitInterface::exitObjectViaDoor. When the exiting object's +0x250 body
// hands out a horde contain (its slot 0x7C), the horde's members (slot 0x108
// list view, rowed list-return helper 0x0036AE51) leave first: every member
// not flagged at +0x454, then every member, each removed from the horde (its
// slot 0xA8) and passed to the rowed GarrisonContain::exitObjectViaDoor --
// stopping after one when the module data's +0xAC exit delay is set -- and
// finally the object itself. Without a horde the object exits directly.
// WorldBuilder's twin (0x011A8120) is unnamed.

#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

typedef ContainmentList IntList;

namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
}

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1
};

class Object;
class Rva0047A14CHorde;

class Rva0047A14CBody
{
public:
#define V(n) virtual void b##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30)
#undef V
	virtual Rva0047A14CHorde *slot7C();		// slot 31
};

class Object
{
public:
	char m_pad000[0x250];
	Rva0047A14CBody *m_body250;				// +0x250
	char m_pad254[0x454 - 0x254];
	unsigned char m_454;					// +0x454
};

class Rva0047A14CHorde
{
public:
#define V(n) virtual void s##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
	virtual void slotA8(Object *member);	// slot 42
	V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65)
#undef V
	virtual Rva0036AE51ListView slot108();	// slot 66
};

struct HordeGarrisonContainModuleData
{
	unsigned char m_pad00[0xAC];
	unsigned int m_exitDelayAC;				// +0xAC
};

class GarrisonContainBase
{
public:
	virtual ~GarrisonContainBase();
protected:
	const HordeGarrisonContainModuleData *m_moduleData;	// +0x04
	unsigned char m_pad08[0x30 - 0x08];
};

class ExitInterface
{
public:
	virtual void e0();
	virtual void e1();
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor) = 0;
};

class GarrisonContain : public GarrisonContainBase, public ExitInterface
{
public:
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);
};

class HordeGarrisonContain : public GarrisonContain
{
public:
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);
};

void HordeGarrisonContain::exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor)
{
	Object *member;
	const HordeGarrisonContainModuleData *data = m_moduleData;
	Rva0047A14CBody *body = exitObj->m_body250;
	if (body)
	{
		Rva0047A14CHorde *horde = body->slot7C();
		if (horde)
		{
			IntList members = horde->slot108().rva0036AE51();
			IntList::iterator it;
			for (it = members.begin(); it != members.end(); ++it)
			{
				member = (Object *)containmentFirstWord(*it);
				if (member->m_454)
					continue;
				horde->slotA8(member);
				GarrisonContain::exitObjectViaDoor(member, exitDoor);
				if (data->m_exitDelayAC > 0)
					return;
			}
			for (it = members.begin(); it != members.end(); ++it)
			{
				member = (Object *)containmentFirstWord(*it);
				horde->slotA8(member);
				GarrisonContain::exitObjectViaDoor(member, exitDoor);
				if (data->m_exitDelayAC > 0)
					return;
			}
			GarrisonContain::exitObjectViaDoor(exitObj, exitDoor);
			return;
		}
	}
	GarrisonContain::exitObjectViaDoor(exitObj, exitDoor);
}
