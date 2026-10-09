// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?projectileFireAtObjectOrPosition@BezierProjectileBehavior@@UAEXPAVObject@@PBUCoord3D@@@Z
// Retail 0x0045BB8A..0x0045BF06 (892 bytes): slot 13 of the primary vftable
// 0x00841E04 (projectileLaunchAtObjectOrPosition 0x0045B936 calls it on the
// victim; MissileUpdate calls it directly at 0x004A773E). WorldBuilder twin
// 0x01180720 (callgraph score 9.0; it calls calcFlightPath). BFME 1 donor:
// reference/open-bfme-1 BezierProjectileBehavior_projectileFireAtObjectOrPosition.cpp
// (the ZH DumbProjectileBehavior projectileFireAtObjectOrPosition shape).
// BFME 2 deltas from retail: the weapon template (+0x3C) speeds are at
// +0x68/+0x6C/+0x70 with the scale flag at +0x74; the max-speed clamp; the
// drawable comes from the 0x005508E2 getter; the producer shroud test
// first excludes a producer of status 1 (0x0028F4EF) whose team is an enemy
// of the active local player; the cell test is TheShroudManager.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED = 1
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;	// 0x00712020
};

class Team
{
public:
	Relationship getRelationship(const Team *that) const;	// 0x003A0FD2
};

class Player
{
public:
	Bool isPlayerActive() const;	// 0x002AA231
	unsigned char m_pad000[0x54];
	Int m_playerIndex;		// +0x54
	unsigned char m_pad058[0x2EC - 0x58];
	Team *m_defaultTeam;		// +0x2EC
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
	unsigned char m_pad00[0x10];
	Player *m_local;		// +0x10
};
extern PlayerList *ThePlayerList;

class Drawable
{
public:
	void fadeOut(UnsignedInt frames);	// 0x00270756
	void fadeIn(UnsignedInt frames);	// 0x002707A8
	void rva00272D77(UnsignedInt a, UnsignedInt b);	// 0x00272D77
	void setDrawableHidden(Bool hidden);	// 0x00271601
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[4];	// +0x108
};

class Thing
{
public:
	void setOrientation(Real angle);	// 0x0030AB9D
};

class Object : public Thing
{
public:
	Drawable *getDrawable() const;	// 0x005508E2
	Int rva0028F4EF();		// 0x0028F4EF
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;	// 0x0028D2A2
	void updateShroudNow();		// 0x0028C11A
	void rva0023D3AF(void *frame);	// 0x0023D3AF
	__forceinline UnsignedInt isKindOf(Int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }
	const Coord3D *getPosition() const { return &m_position; }
	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_transform[0x30];	// +0x08
	Coord3D m_position;			// +0x38
	unsigned char m_pad044[0x78 - 0x44];
	ObjectID m_producerID;			// +0x78
	unsigned char m_pad07C[0x25C - 0x7C];
	void *m_25C;				// +0x25C
	unsigned char m_pad260[0x304 - 0x260];
	Team *m_team;				// +0x304
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// +0x18
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);	// 0x002802FE
};
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *TheShroudManager;
extern GameLogic *TheGameLogic;

class GameEngine
{
public:
	unsigned char m_pad00[0x38];
	Int m_framesPerSecond;		// +0x38
};
extern GameEngine *TheGameEngine;
extern float g_00DBA500;	// logic frames per millisecond (0.03)

class WeaponTemplate
{
public:
	Coord3D *getAimPosition(Coord3D *out, const Object *proj, const Object *victim, Int flag);	// 0x002CAB3A
	Real getMinimumAttackRange() const;	// 0x002C92FA
	Real rva0049CB57() const;		// 0x0049CB57, getUnmodifiedAttackRange
	Real getWeaponSpeed() const { return m_weaponSpeed; }
	Real getMinWeaponSpeed() const { return m_minWeaponSpeed; }
	Real getMaxWeaponSpeed() const { return m_maxWeaponSpeed; }
	Bool isScaleWeaponSpeed() const { return m_scaleWeaponSpeed; }
	unsigned char m_pad00[0x68];
	Real m_weaponSpeed;			// +0x68
	Real m_minWeaponSpeed;			// +0x6C
	Real m_maxWeaponSpeed;			// +0x70
	Bool m_scaleWeaponSpeed;		// +0x74
};

class ModuleData;

struct BezierProjectileBehaviorModuleData
{
	unsigned char m_pad00[0x18];
	Bool m_snapZToTerrain;			// +0x18
	unsigned char m_pad19[0x40 - 0x19];
	UnsignedInt m_value40;			// +0x40
	UnsignedInt m_value44;			// +0x44
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData;		// +0x04
	Object *m_object;			// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);	// 0x0044DF71
};

template <typename T>
static __forceinline const T &bezierMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

class BezierProjectileBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
private:
	Bool calcFlightPath(Bool recalcNumSegments);	// 0x0045B5F4
	const BezierProjectileBehaviorModuleData *getBezierProjectileBehaviorModuleData() const
	{
		return (const BezierProjectileBehaviorModuleData *)m_moduleData;
	}

	unsigned char m_pad14[0x3C - 0x14];
	WeaponTemplate *m_weapon;		// +0x3C
	unsigned char m_pad40[0x50 - 0x40];
	Coord3D m_flightPathStart;		// +0x50
	Coord3D m_flightPathEnd;		// +0x5C
	Real m_flightPathSpeed;			// +0x68
	Int m_flightPathSegments;		// +0x6C
	Int m_currentFlightPathStep;		// +0x70
};

void BezierProjectileBehavior::projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos)
{
	const BezierProjectileBehaviorModuleData *md = getBezierProjectileBehaviorModuleData();
	Object *obj = getObject();
	Real weaponSpeed = m_weapon ? m_weapon->getWeaponSpeed() : 0.0f;
	Real minWeaponSpeed = m_weapon ? m_weapon->getMinWeaponSpeed() : 0.0f;

	setWakeFrame(obj, UPDATE_SLEEP_NONE);

	if (!md)
		return;

	Coord3D victimPosToUse;
	if (victim)
	{
		Coord3D aim;
		victimPosToUse = *m_weapon->getAimPosition(&aim, obj, victim, 1);
	}
	else
	{
		victimPosToUse = *victimPos;
	}

	if (md->m_snapZToTerrain)
	{
		if (TheTerrainLogic->getLayerForDestination(0, &victimPosToUse) == LAYER_GROUND)
			victimPosToUse.z = TheTerrainLogic->getGroundHeight(victimPosToUse.x, victimPosToUse.y, 0);
	}

	if (m_weapon && m_weapon->isScaleWeaponSpeed())
	{
		weaponSpeed = bezierMax(weaponSpeed, minWeaponSpeed);

		Real minRange = m_weapon->getMinimumAttackRange();
		Real maxRange = m_weapon->rva0049CB57();
		Real dx = obj->getPosition()->x - victimPosToUse.x;
		Real dy = obj->getPosition()->y - victimPosToUse.y;
		Real distSq = dx * dx + dy * dy;
		m_flightPathSpeed = ((distSq - minRange) / (maxRange - minRange)) *
			(weaponSpeed - minWeaponSpeed) + minWeaponSpeed;
		if (m_flightPathSpeed > m_weapon->getMaxWeaponSpeed())
			m_flightPathSpeed = m_weapon->getMaxWeaponSpeed();
	}
	else
	{
		m_flightPathSpeed = weaponSpeed;
	}

	if (obj->m_25C && obj->isKindOf(0x62))
		obj->setOrientation(obj->getTransformMatrix()->Get_Z_Rotation());

	m_flightPathStart = *getObject()->getPosition();
	m_flightPathEnd = victimPosToUse;

	if (!calcFlightPath(true))
	{
		TheGameLogic->destroyObject(obj);
		return;
	}

	m_currentFlightPathStep = 0;

	Drawable *draw = obj->getDrawable();
	if (draw && !obj->isKindOf(0x5A) && !obj->isKindOf(0x0A))
	{
		Int player = ThePlayerList ? ThePlayerList->getLocalPlayer()->m_playerIndex : 0;

		Object *producer = TheGameLogic->findObjectByID(obj->m_producerID);
		Bool producerShrouded = false;
		if (producer)
		{
			Bool spotted = false;
			if (producer->rva0028F4EF() == 1)
			{
				Player *local = ThePlayerList->getLocalPlayer();
				Relationship rel = producer->m_team ? producer->m_team->getRelationship(local->m_defaultTeam) : NEUTRAL;
				spotted = (rel == ENEMIES && local->isPlayerActive());
			}
			producerShrouded = (producer->getShroudStatusForPlayer(player) == CELLSHROUD_FOGGED && !spotted);
		}

		Bool cellClear = TheShroudManager->getShroudStatusForPlayer(player, &m_flightPathEnd) == CELLSHROUD_CLEAR;

		if (producerShrouded)
		{
			if (!cellClear)
				draw->fadeOut((Int)((Real)TheGameEngine->m_framesPerSecond * (Real)m_flightPathSegments));
			else if (md->m_value40 != 0 || md->m_value44 != 0)
				draw->rva00272D77((Int)((Real)md->m_value40 * g_00DBA500), (Int)((Real)md->m_value44 * g_00DBA500));
		}
		else if (cellClear)
		{
			draw->fadeIn((Int)((Real)TheGameEngine->m_framesPerSecond * (Real)m_flightPathSegments));
		}
		else
		{
			draw->setDrawableHidden(true);
		}
	}

	update();
	getObject()->updateShroudNow();
	getObject()->rva0023D3AF((void *)TheGameLogic->getFrame());
	update();
	getObject()->updateShroudNow();
}
