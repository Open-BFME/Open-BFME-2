// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /ICode/Libraries/Include /ICode/GameEngine/Source/Common
//
// ?computeApproachPoint@SiegeDeploySpecialPower@@QAE?AURva004598F2Point@@PAVObject@@PAU2@PA_N@Z,
// retail 0x004C5877, 706 bytes (EH RET 0x10). Named by the "computeApproachPoint
// for " debug string of its WorldBuilder twin (0x01263640, SiegeDeploySpecialPower.cpp;
// WB offsets run eight lower on Object, four lower on the module).
// The approach point toward a siege target: start from the target's position;
// if the target has a SiegeDockingBehavior module, clear status 0x40 on our
// Object, ask the module's +0x20 interface slot 2 for a dock index for our
// Object ID and, when it is non-negative, set status 0x40 again and take the
// index's two dock points (0x004598F2 for the approach point, 0x0045992F
// copied to *dockPosition) and set *docked. If docked and the approach point
// is more than 1.0 from the target: step 0.1 of the offset toward it; unless
// the module data byte at +0x22 is set, bend that offset through the Pathfinder
// AdjustMeleeOffset (0x002E8C6E, TheAI->pathfinder at +0x10) and restart from
// the target position; then normalise, move up to ten 5.0 steps while the
// point lies on a wall, and add the module data float at +0x2C times the
// direction. The x product reads direction.x first with the scale assignment
// on its right so retail keeps scale in xmm3 and multiplies it by the
// memory x operand (movaps+mulss mem); y/z load into regs first.
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { BFME_STATUS_40 = 0x40 };

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
};

class SiegeDockingBehavior
{
public:
	Rva004598F2Point rva004598F2(int index);
	Rva004598F2Point rva0045992F(int index);
	unsigned char m_pad00[0x20];
	SiegeDockingIface m_iface;
};

class Module;

class Object
{
public:
	const Rva004598F2Point *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	void setStatus(ObjectStatusTypes status, bool set);
	friend class SiegeDeploySpecialPower; protected: Module *findModule(NameKeyType key) const; public:
	unsigned char m_pad00[0x38];
	Rva004598F2Point m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

class Pathfinder
{
public:
	bool IsPointOnWall(int pos, bool flag);
	void AdjustMeleeOffset(Object *self, Object *target, Coord3D *offset);
};

class AIHead
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
class AI;
extern AI *TheAI;

struct SiegeDeployModuleDataView
{
	unsigned char m_pad00[0x22];
	bool m_noAdjust;
	unsigned char m_pad23[0x2C - 0x23];
	float m_approachScale;
};

class SiegeDeploySpecialPower
{
public:
	Rva004598F2Point computeApproachPoint(Object *target, Rva004598F2Point *dockPosition, bool *docked);
private:
	unsigned char m_pad00[0x04];
	const SiegeDeployModuleDataView *m_moduleData;
	Object *m_object;
};

Rva004598F2Point SiegeDeploySpecialPower::computeApproachPoint(Object *target, Rva004598F2Point *dockPosition, bool *docked)
{
	Rva004598F2Point position;
	position.x = target->m_position.x;
	position.y = target->m_position.y;
	position.z = target->m_position.z;
	static const NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
	SiegeDockingBehavior *dock = (SiegeDockingBehavior *)target->findModule(key);
	if (dock)
	{
		m_object->setStatus(BFME_STATUS_40, false);
		int index = dock->m_iface.dockIndexFor(m_object->getID());
		if (index >= 0)
		{
			m_object->setStatus(BFME_STATUS_40, true);
			position = dock->rva004598F2(index);
			*dockPosition = dock->rva0045992F(index);
			*docked = true;
		}
		else
		{
			*docked = false;
		}
	}

	if (*docked)
	{
		const Rva004598F2Point *targetPosition = target->getPosition();
		Rva004598F2Point offset;
		offset.x = position.x - targetPosition->x;
		offset.y = position.y - targetPosition->y;
		offset.z = position.z - targetPosition->z;
		if (offset.x * offset.x + offset.y * offset.y + offset.z * offset.z > 1.0f)
		{
			offset.x *= 0.1f;
			offset.y *= 0.1f;
			offset.z *= 0.1f;
			if (!m_moduleData->m_noAdjust)
			{
				((AIHead *)TheAI)->m_pathfinder->AdjustMeleeOffset(m_object, target, (Coord3D*)&offset);
				position = *targetPosition;
				position.x += offset.x;
				position.y += offset.y;
				position.z += offset.z;
			}
			((Coord3D *)&offset)->Normalize();
			Rva004598F2Point direction = offset;
			offset.x *= 5.0f;
			offset.y *= 5.0f;
			offset.z *= 5.0f;
			for (int i = 0; i < 10; ++i)
			{
				Pathfinder *pathfinder = ((AIHead *)TheAI)->m_pathfinder;
				if (!pathfinder->IsPointOnWall((int)(void *)&position, false))
					break;
				position.x += offset.x;
				position.y += offset.y;
				position.z += offset.z;
			}
			float scale;
			Rva004598F2Point approach;
			approach.x = direction.x * (scale = m_moduleData->m_approachScale);
			approach.y = direction.y * scale;
			approach.z = direction.z * scale;
			position.x += approach.x;
			position.y += approach.y;
			position.z += approach.z;
		}
	}
	return position;
}
