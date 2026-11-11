// cl: /I. /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@SiegeDeploySpecialPower@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x004C5E80 (691 bytes): slot 9 of the update table 0x0085DCCC (the same
// table holds the rowed slot 2 0x004C575F) installed by the matched ctor
// 0x004C56BA, so `this` is the module +0x10 and the Object sits at -8.
// Target evidence: the deploy phase +0x38 drives the rowed setter
// 0x004C5BE3; +0x3C counts frames against module data +0x18; +0x40 is the
// target ObjectID looked up through TheGameLogic; +0x54 receives the rowed
// approach point 0x004C5877 for direction +0x64; +0x60 alternates moving and
// facing; +0x70 is the stop request (rowed stopSpecialPower 0x004C5E41).
// Structure carried from the WorldBuilder twin 0x01262FD0: phase 1 sets a
// flag when the object faces the target within 0.15 rad and a dynamic portal
// above the wall answers, queried once per branch (target test 0x0028B35B or
// AI slot 110); retail merges the two queries. AI slot meanings (110, 136,
// 143) and helper names are by address; the AI is a view.

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <math.h>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_ZERO = 0
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Object;
class Module;
#include "../../../../Include/GameLogic/Module/DynamicPortalBehaviour.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
class SiegeDeployAIHead
{
	unsigned char m_pad[0x20];
};
template<int N> class SiegeDeployAISlots : public SiegeDeployAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template<> class SiegeDeployAISlots<0>
{
};
class SiegeDeployAIView : public SiegeDeployAISlots<110>
{
public:
	virtual bool slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual void slot123() = 0;
	virtual void slot124() = 0;
	virtual void slot125() = 0;
	virtual void slot126() = 0;
	virtual void slot127() = 0;
	virtual void slot128() = 0;
	virtual void slot129() = 0;
	virtual void slot130() = 0;
	virtual void slot131() = 0;
	virtual void slot132() = 0;
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void slot135() = 0;
	virtual void slot136() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142() = 0;
	virtual int slot143() = 0;
};

class Drawable;
#include "../../../Common/Thing/thing.h"
#include "../object.h"

struct __declspec(novtable) SiegeDeploySpecialPowerModuleData
{
	unsigned char m_pad[0x18];
	unsigned m_delay;			// +0x18
};
extern GameLogic *TheGameLogic;

struct Rva004598F2Point
{
public:
	Rva004598F2Point() {}
	Rva004598F2Point(const Rva004598F2Point &other) : x(other.x), y(other.y), z(other.z) {}
	Rva004598F2Point(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};

class SiegeDeployPrimary
{
public:
	virtual ~SiegeDeployPrimary();
protected:
	const SiegeDeploySpecialPowerModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};
class SiegeDeployIface0C
{
public:
	virtual void f0C();
};
class SiegeDeployUpdateIface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual void u8();
	virtual UpdateSleepTime update() = 0;	// slot 9
};

class SiegeDeploySpecialPower : public SiegeDeployPrimary, public SiegeDeployIface0C, public SiegeDeployUpdateIface
{
public:
	virtual UpdateSleepTime update();
	void rva004C573C();
	void rva004C5E62();
	Rva004598F2Point computeApproachPoint(Object *target, Rva004598F2Point *direction, bool *docked);
private:
	void setPhase(int phase);
	unsigned char m_pad14[0x38 - 0x14];
	int m_phase;				// +0x38
	unsigned m_frame;			// +0x3C
	unsigned m_targetID;			// +0x40
	unsigned char m_pad44[0x54 - 0x44];
	Rva004598F2Point m_approach;		// +0x54
	bool m_turn;				// +0x60
	Coord3D m_direction;			// +0x64
	bool m_stop;				// +0x70
};

UpdateSleepTime SiegeDeploySpecialPower::update()
{
	Object *obj = m_object;
	if (obj->m_privateStatus & 1)
	{
		rva004C573C();
		goto inactive;
	}
	if (!m_phase)
		goto inactive;
	if (m_stop)
	{
		setPhase(4);
		m_stop = false;
		return UPDATE_SLEEP_NONE;
	}
	AIUpdateInterface *ai = obj->m_ai;
	SiegeDeployAIView *view = (SiegeDeployAIView *)ai;
	if (!ai)
	{
		rva004C5E62();
		return UPDATE_SLEEP_FOREVER;
	}
	if (!obj->getDrawable())
		return UPDATE_SLEEP_FOREVER;
	if ((!view->slot110() && view->slot143() != 2) || (view->slot110() && view->slot143() == 0))
	{
		rva004C5E62();
		return UPDATE_SLEEP_FOREVER;
	}
	Object *targetObject = 0;
	if (m_targetID)
	{
		targetObject = TheGameLogic->findObjectByID((ObjectID)m_targetID);
		if (!targetObject || (targetObject->m_privateStatus & 1))
		{
			targetObject = 0;
			m_targetID = 0;
			if (m_phase == 3)
				setPhase(4);
		}
	}
	if (!targetObject)
		setPhase(4);
	switch (m_phase)
	{
	case 0:
		targetObject->setStatus((ObjectStatusTypes)64, false);
		return UPDATE_SLEEP_FOREVER;
	case 1:
	{
		Coord3D *offset = &m_direction;
		Rva004598F2Point face(obj->m_cachedPos);
		face.x += offset->x;
		face.y += offset->y;
		face.z += offset->z;
		bool ok = fabs(obj->GetRelativeAngle((const Coord3D *)&face)) < 0.15f;
		if (ok)
		{
			ok = false;
			if (obj->rva0028B35B(targetObject))
			{
				Module *portal = DynamicPortalBehaviour::rva004608E0(obj);
				if (portal && ((DynamicPortalBehaviour *)portal)->IsEndPortalAboveWall(0))
					ok = true;
			}
			else if (view->slot110())
			{
				Module *portal = DynamicPortalBehaviour::rva004608E0(obj);
				if (portal && ((DynamicPortalBehaviour *)portal)->IsEndPortalAboveWall(0))
					ok = true;
			}
		}
		if (ok)
		{
			view->slot136();
			ai->rva0045003E(0, CMD_FROM_AI);
			setPhase(2);
			break;
		}
		if (view->slot110())
		{
			ai->ignoreObstacle(targetObject);
			if (m_turn)
				m_turn = false;
			else
				m_turn = true;
			if (m_turn)
			{
				bool docked = false;
				m_approach = computeApproachPoint(targetObject, (Rva004598F2Point *)offset, &docked);
				if (docked)
					ai->aiMoveToPosition((const Coord3D *)&m_approach, CMD_FROM_AI);
			}
			else
			{
				face.x = obj->m_cachedPos.x;
				face.y = obj->m_cachedPos.y;
				face.z = obj->m_cachedPos.z;
				face.x += offset->x;
				face.y += offset->y;
				face.z += offset->z;
				ai->aiFacePosition((const Coord3D *)&face, CMD_FROM_AI);
			}
		}
		break;
	}
	case 2:
		if (++m_frame >= m_moduleData->m_delay)
			setPhase(3);
		break;
	case 4:
		setPhase(0);
		break;
	}
	return UPDATE_SLEEP_NONE;
inactive:
	return UPDATE_SLEEP_FOREVER;
}
