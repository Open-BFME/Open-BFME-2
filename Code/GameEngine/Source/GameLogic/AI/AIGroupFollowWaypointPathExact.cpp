// cl: /DNDEBUG /MD /ICode/Libraries/Include
//
// ?rva0036FA56@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z, retail 0x0036FA56, 54 bytes.
// AIGroup forward of aiFollowWaypointPathExact to each member via the rowed
// AICommandInterface method at 0x0036ECE7. Evidence: same list-at-+0x00 plus
// Object+0x258 plus +0x20 subobject loop as the rowed groupAttackTeam at
// 0x0036FF33 in AIGroupAttackTeam.cpp; caller at 0x003BF712; prev/next are
// aiGuardPosition and groupAttackTeam with compatible flags.

#include "Lib/Coord3D.h"

#include <list>

class Waypoint;
class Object;
class Rva003427DD;

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;


enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_AIRCRAFT = 12
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void aiEvacuate(Bool exposeStealthUnits, CommandSourceType cmdSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);
	void rva0036F200(Object *obj, CommandSourceType cmdSource);
	void rva0036F265(Object *obj, CommandSourceType cmdSource);
	void rva0036F2CA(Object *obj, CommandSourceType cmdSource);
	void rva0026C3AC(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
	void rva0036F400(const Rva003427DD *arg, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int arg);
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[(UnsignedInt)t >> 5] & (1u << ((UnsignedInt)t & 31))) != 0; }
private:
	char m_pad[0x108];
	UnsignedInt m_kindof[4]; // +0x108
};

class ContainModuleInterface
{
public:
	template <int N> struct Slot {};
	virtual void slot(Slot<0>); virtual void slot(Slot<1>); virtual void slot(Slot<2>); virtual void slot(Slot<3>);
	virtual void slot(Slot<4>); virtual void slot(Slot<5>); virtual void slot(Slot<6>); virtual void slot(Slot<7>);
	virtual void slot(Slot<8>); virtual void slot(Slot<9>); virtual void slot(Slot<10>); virtual void slot(Slot<11>);
	virtual void slot(Slot<12>); virtual void slot(Slot<13>); virtual void slot(Slot<14>); virtual void slot(Slot<15>);
	virtual void slot(Slot<16>); virtual void slot(Slot<17>); virtual void slot(Slot<18>); virtual void slot(Slot<19>);
	virtual void slot(Slot<20>); virtual void slot(Slot<21>); virtual void slot(Slot<22>); virtual void slot(Slot<23>);
	virtual void slot(Slot<24>); virtual void slot(Slot<25>); virtual void slot(Slot<26>); virtual void slot(Slot<27>);
	virtual void slot(Slot<28>); virtual void slot(Slot<29>); virtual void slot(Slot<30>); virtual void slot(Slot<31>);
	virtual void orderAllPassengersToExit(CommandSourceType cmdSource); // +0x80
};

class TerrainLogic
{
public:
	template <int N> struct Slot {};
	virtual void slot(Slot<0>); virtual void slot(Slot<1>); virtual void slot(Slot<2>); virtual void slot(Slot<3>);
	virtual void slot(Slot<4>); virtual void slot(Slot<5>); virtual void slot(Slot<6>);
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const; // +0x1C
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges = false);
};

extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	Bool isAirborneTarget() const { return ((m_status >> 6) & 1) != 0; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
private:
	char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	char m_pad44[0x94 - 0x44];
	UnsignedInt m_status; // +0x94
	char m_pad98[0x250 - 0x98];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[0x258 - 0x254];
public:
	AIUpdateInterface *m_ai; // +0x258
};

class AIGroup
{
public:
	void rva0036FA56(const Waypoint *waypoint, CommandSourceType cmdSource);
	void groupMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void groupMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
	void rva003700C0(Object *obj, CommandSourceType cmdSource);
	void rva003700F6(Object *obj, CommandSourceType cmdSource);
	void rva0037012C(Object *obj, CommandSourceType cmdSource);
	void rva00370162(Object *obj, CommandSourceType cmdSource);
	void rva00370217(Object *obj, CommandSourceType cmdSource);
	void groupHarvest(const Coord3D *pos, CommandSourceType cmdSource);
	void groupExit(Object *objectToExit, CommandSourceType cmdSource);
	void groupEvacuate(CommandSourceType cmdSource);
	void rva00370399(const Rva003427DD *arg, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FA56(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiFollowWaypointPathExact(waypoint, cmdSource);
	}
}

// Ten more AIGroup forwards of the same 54-byte shape, each to the rowed
// AICommandInterface method its call reaches; only the call displacement differs
// from rva0036FA56's bytes. Zero Hour's AIGroup.cpp has groupMoveToAndEvacuate,
// groupMoveToAndEvacuateAndExit and groupExit as exactly this loop over
// aiMoveToAndEvacuate, aiMoveToAndEvacuateAndExit and aiExit; the others keep
// their addresses, as their callees do.

// retail 0x0036FA8C, 54 bytes -> AICommandInterface::aiMoveToAndEvacuate
void AIGroup::groupMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiMoveToAndEvacuate(pos, cmdSource);
	}
}

// retail 0x0036FAC2, 54 bytes -> AICommandInterface::aiMoveToAndEvacuateAndExit
void AIGroup::groupMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiMoveToAndEvacuateAndExit(pos, cmdSource);
	}
}

// retail 0x003700C0, 54 bytes -> AICommandInterface::rva0036F19B
void AIGroup::rva003700C0(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F19B(obj, cmdSource);
	}
}

// retail 0x003700F6, 54 bytes -> AICommandInterface::rva0036F200
void AIGroup::rva003700F6(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F200(obj, cmdSource);
	}
}

// retail 0x0037012C, 54 bytes -> AICommandInterface::rva0036F265
void AIGroup::rva0037012C(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F265(obj, cmdSource);
	}
}

// retail 0x00370162, 54 bytes -> AICommandInterface::rva0036F2CA
void AIGroup::rva00370162(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F2CA(obj, cmdSource);
	}
}

// retail 0x00370217, 54 bytes -> AICommandInterface::rva0026C3AC
void AIGroup::rva00370217(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0026C3AC(obj, cmdSource);
	}
}

// retail 0x0037024D, 54 bytes -> AICommandInterface::aiHarvest
void AIGroup::groupHarvest(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiHarvest(pos, cmdSource);
	}
}

// retail 0x00370283, 54 bytes -> AICommandInterface::aiExit
void AIGroup::groupExit(Object *objectToExit, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiExit(objectToExit, cmdSource);
	}
}

// retail 0x00370399, 54 bytes -> AICommandInterface::rva0036F400
void AIGroup::rva00370399(const Rva003427DD *arg, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F400(arg, cmdSource);
	}
}

// ?groupEvacuate@AIGroup@@QAEXW4CommandSourceType@@@Z, retail 0x003702B9, 224 bytes.
// Zero Hour's groupEvacuate: an airborne aircraft moves to the ground (or
// bridge) under it and evacuates there, any other AI unit evacuates in place,
// and a structure orders its passengers out (ContainModuleInterface slot 32,
// +0x80). BFME 2 keeps the AI at Object+0x258, the contain module at +0x250
// and the airborne status bit at +0x94 bit 6; the kind-of mask is the
// template's +0x108 (KINDOF_STRUCTURE bit 7, KINDOF_AIRCRAFT bit 12).
// Retail copies the position member by member with no load hoisted past a
// store, which the drop point declared at function scope reproduces; the
// kind-of tests are fully inlined.
void AIGroup::groupEvacuate(CommandSourceType cmdSource)
{
	Coord3D pos;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		AIUpdateInterface *ai = obj->getAI();
		if (ai)
		{
			if (obj->isKindOf(KINDOF_AIRCRAFT) && obj->isAirborneTarget())
			{
				pos.x = obj->getPosition()->x;
				pos.y = obj->getPosition()->y;
				pos.z = obj->getPosition()->z;
				PathfindLayerEnum layerAtDest = TheTerrainLogic->getHighestLayerForDestination(&pos);
				pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layerAtDest);
				ai->m_commands.aiMoveToAndEvacuate(&pos, cmdSource);
			}
			else
			{
				ai->m_commands.aiEvacuate(false, cmdSource);
			}
		}
		else if (obj->isKindOf(KINDOF_STRUCTURE))
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				contain->orderAllPassengersToExit(cmdSource);
		}
	}
}
