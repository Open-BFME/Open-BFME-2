// ?initiateIntentToDoSpecialPower@SiegeDeploySpecialPower@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// stlport
//
// ?initiateIntentToDoSpecialPower@SiegeDeploySpecialPower@@UAEXPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@IPBVWaypoint@@@Z,
// retail 0x004C6133, 568 bytes (EH RET 0x14). Slot 0 of the special-power
// interface at +0x20 (this-0x20 is the module), the plain-siege sibling of the
// Horde variant 0x004C6588; WB 0x01263A70 (SiegeDeploySpecialPower.cpp 345-).
// If the interface's slot 2 (0x004C575F) reports the power already deployed,
// or there is no target Object or no AI, nothing happens. Otherwise find a
// dock: the target itself when its SiegeDockingBehavior accepts our Object ID,
// else the first Object within the module data radius (+0x24) of the target
// that has one (a kind-0x3C partition filter). With a dock, computeApproachPoint
// (0x004C5877) fills the approach point at +0x54 and the dock position at
// +0x64; if it docked, the AI ignores the dock as an obstacle, idles and moves
// to the approach point, the deploy phase goes to 1 and the dock's ID is
// remembered at +0x40; otherwise the remembered ID clears and the deploy is
// stopped (0x004C5E62). Without a dock the AI moves to the target position,
// pushed by the module data +0x28 along the target's forward vector when that
// is positive. Wakes the module.
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
#include "PartitionRangeQueryCallView.h"
class SpecialPowerTemplate;
class Waypoint;
class Module;
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// A KindOfMaskType built from its set bits (0x00045411 one bit; the first
// argument is unused).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int reserved, int bit) throw();
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct Rva004598F2Point
{
	Rva004598F2Point() {}
	Rva004598F2Point(const Rva004598F2Point &other) : x(other.x), y(other.y), z(other.z) {}
	float x;
	float y;
	float z;
};

class SiegeDockingIface
{
public:
	virtual void gap0();
	virtual void gap1();
	virtual int dockIndexFor(ObjectID id);
	virtual bool acceptsDockFor(ObjectID id);
};

class SiegeDockingBehavior
{
public:
	unsigned char m_pad00[0x20];
	SiegeDockingIface m_iface;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterfaceHead
{
	unsigned char m_pad00[0x20];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
public:
	void ignoreObstacle(const Object *obj);
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x08];
	float m_xAxis;
	unsigned char m_pad0C[0x18 - 0x0C];
	float m_yAxis;
	unsigned char m_pad1C[0x28 - 0x1C];
	float m_zAxis;
	unsigned char m_pad2C[0x38 - 0x2C];
	Rva004598F2Point m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai;
};

class UpdateModule
{
protected:
	virtual ~UpdateModule();
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	const void *m_moduleData;												// +0x04
	Object *m_object;														// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way) = 0;
	virtual void gap1();
	virtual bool rva004C575F();
};

class SpecialPowerStopInterface
{
public:
	virtual void gap0();
};

struct SiegeDeployModuleDataView
{
	unsigned char m_pad00[0x24];
	float m_searchRadius;											// +0x24
	float m_pushDistance;											// +0x28
};

class SiegeDeploySpecialPower : public UpdateModule, public SpecialPowerUpdateInterface, public SpecialPowerStopInterface
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way);
	Rva004598F2Point computeApproachPoint(Object *target, Rva004598F2Point *dockPosition, bool *docked);
	void rva004C5E62();
private:
	void rva004C5BE3(int state);
	const SiegeDeployModuleDataView *data() const { return (const SiegeDeployModuleDataView *)m_moduleData; }

	unsigned char m_pad28[0x40 - 0x28];
	ObjectID m_dockID;												// +0x40
	unsigned char m_pad44[0x54 - 0x44];
	Rva004598F2Point m_approachPoint;								// +0x54
	bool m_docked;													// +0x60
	unsigned char m_pad61[3];
	Rva004598F2Point m_dockPosition;								// +0x64
};

void SiegeDeploySpecialPower::initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
	const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way)
{
	if (rva004C575F())
		return;
	if (!targetObj)
		return;
	Object *dockObject = 0;
	Object *self = m_object;
	AIUpdateInterface *ai = self->m_ai;
	if (!ai)
		return;
	static const NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	SiegeDockingBehavior *dock = (SiegeDockingBehavior *)targetObj->findModule(key);
	if (!dock)
		return;
	if (dock->m_iface.acceptsDockFor(self->getID()))
	{
		dockObject = TheGameLogic->findObjectByID(targetObj->m_id);
	}
	else
	{
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(
			(const Coord3D *)&targetObj->m_position, data()->m_searchRadius, 0,
			&Rva003959FA(BfmeFixedStorage0004543D(0, 0x3C)), 1);
		Object *other;
		while ((other = hits.next()) != 0)
		{
			SiegeDockingBehavior *otherDock = (SiegeDockingBehavior *)other->findModule(key);
			if (otherDock && otherDock->m_iface.acceptsDockFor(self->getID()))
			{
				dockObject = other;
				break;
			}
		}
	}
	if (dockObject)
	{
		bool docked = false;
		m_approachPoint = computeApproachPoint(dockObject, &m_dockPosition, &docked);
		if (docked)
		{
			ai->ignoreObstacle(dockObject);
			ai->aiIdle(CMD_FROM_AI);
			ai->aiMoveToPosition((const Coord3D *)&m_approachPoint, CMD_FROM_AI);
			m_docked = true;
			rva004C5BE3(1);
			m_dockID = dockObject->m_id;
		}
		else
		{
			m_dockID = INVALID_OBJECT_ID;
			rva004C5E62();
		}
	}
	else
	{
		if (data()->m_pushDistance > 0.0f)
		{
			Rva004598F2Point pos(targetObj->m_position);
			Rva004598F2Point p;
			p.z = pos.z;
			Rva004598F2Point forward;
			forward.x = targetObj->m_xAxis;
			forward.y = targetObj->m_yAxis;
			forward.z = targetObj->m_zAxis;
			float scale = data()->m_pushDistance;
			forward.x *= scale;
			forward.y *= scale;
			forward.z *= scale;
			p.x = pos.x + forward.x;
			p.y = pos.y + forward.y;
			ai->aiMoveToPosition((const Coord3D *)&p, CMD_FROM_AI);
		}
		else
		{
			ai->aiMoveToPosition((const Coord3D *)&targetObj->m_position, CMD_FROM_AI);
		}
	}
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
