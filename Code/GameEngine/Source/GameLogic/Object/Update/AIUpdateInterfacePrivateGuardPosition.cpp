// cl: /O1 /DNDEBUG /MD /arch:SSE
#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

// ?privateGuardPosition@AIUpdateInterface@@MAEXPBUCoord3D@@W4GuardMode@@W4CommandSourceType@@@Z
// 0x00264BC2 249B: AIUpdateInterface guard order. Checks testStatus 0x26,
// rva002907A1 and KINDOF_PROJECTILE, sets guard target 0x50/0x54 to LOCATION,
// clips to playable area via TheTerrainLogic when cmdSource is player, stores
// position +0x58, guardMode +0x4C, clear via slot 0x14 and setState 0x10 via
// slot 0x20. Vtable slot 63 of DeployStyle/Siege/Supply/Transport/Wander/
// HordeWorker AIUpdates. Sibling privateGuardObject 0x00264D0E slot 64 shares
// guards, target logic, clear and state. ZH donor AIUpdate.cpp
// privateGuardPosition supplies position/clip/state shape.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum ObjectStatusTypes
{
	BFME_OBJECT_STATUS_26 = 0x26
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_LOCATION = 0,
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_GUARD = 0x10
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Bool isInRegionNoZ(const Coord3D *query) const
	{
		return (lo.x < query->x) && (query->x < hi.x)
			&& (lo.y < query->y) && (query->y < hi.y);
	}
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_unmodelled_08[0x108 - 8];
	unsigned char m_kindof[16];
};

class Thing
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva002907A1();
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void getExtent(Region3D *extent) const = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual Coord3D findClosestEdgePoint(const Coord3D *closestTo) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

protected:
	virtual void privateGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource);

public:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	Coord3D m_locationToGuard;
};

void AIUpdateInterface::privateGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource)
{
	Object *obj = m_object;
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->rva002907A1())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;
	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_LOCATION;
	else
		m_guardTargetType[0] = GUARDTARGET_LOCATION;
	Coord3D adjPos;
	adjPos.x = pos->x;
	adjPos.y = pos->y;
	adjPos.z = pos->z;
	if (cmdSource == CMD_FROM_PLAYER) {
		Region3D r;
		TheTerrainLogic->getExtent(&r);
		if (!r.isInRegionNoZ(&adjPos))
			adjPos = TheTerrainLogic->findClosestEdgePoint(&adjPos);
	}
	m_locationToGuard = adjPos;
	m_guardMode = guardMode;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}
