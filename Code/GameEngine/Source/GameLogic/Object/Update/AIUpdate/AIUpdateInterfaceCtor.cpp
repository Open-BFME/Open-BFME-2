// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// ??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0026E9BD,
// 984 bytes (EH). BFME2's AIUpdateInterface constructor (WB E36130,
// AIUpdate.cpp), the base the rowed Dozer/Worker/GiantBird constructors run.
// As in Zero Hour it constructs UpdateModule, the sixteen waypoint
// coordinates (+0x74, eh vector constructor iterator with the folded empty
// Coord3D ctor/dtor), the locomotor set (+0x1CC), the +0x214 string and the
// BFME2-only members +0x224, +0x244, +0x290, the +0x2DC 128-bit mask, +0x2EC
// and +0x3D0, then resets the scalars in WB source order, builds the turret
// AI for the one turret slot, picks LOCOMOTORSET_NORMAL, looks up the attack
// priority, wakes the module and binds the object event list (+0x220).
// Layout and the five vtables (0x00BFA480, 0x00BFA3C0 +0xC, 0x00C53A98
// +0x10, 0x00C47B88 +0x20, 0x00C52F88 +0x24) are the ones the rowed
// destructor 0x0026E836 unwinds; unnamed fields keep their offsets.
#include "ascii_string.h"

#include <string.h>

class Thing;
class ModuleData;
class Object;
class TurretAIData;
class AttackPriorityInfo;
struct Rva00336283Element;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum WhichTurretType { TURRET_MAIN = 0 };

class UpdateModuleRoot
{
public:
	virtual void r0() = 0;
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class UpdateModuleSecond
{
public:
	virtual void s0() = 0;
};

class UpdateModuleThird
{
public:
	virtual void t0() = 0;
private:
	char m_pad14[12];
};

class UpdateModule : public UpdateModuleRoot, public UpdateModuleSecond, public UpdateModuleThird
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class AIUpdateInterfaceFourth
{
public:
	virtual void u0() = 0;
};

class AIUpdateInterfaceFifth
{
public:
	virtual void v0() = 0;
};

class AIUpdateModuleDataView
{
public:
	unsigned char m_pad00[0x14];
	const TurretAIData *m_turretData[1];		// +0x14
	unsigned char m_pad18[0x2C - 0x18];
	AsciiString m_objectEventsListName;		// +0x2C
	unsigned char m_pad30[0x44 - 0x30];
	AsciiString m_attackPriorityName;		// +0x44
};

class StateMachine;
class Locomotor;

// The waypoint queue element: Coord3D with the empty out-of-line ctor/dtor
// retail folds (0x0047A6A9, 0x000B3FD0).
#define COORD3D_VIEW_EXTERN_CTOR
#define COORD3D_VIEW_EXTERN_DTOR
#include "../../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

struct AIUpdatePoint
{
	float x, y, z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// LocomotorSet (0x24 bytes).
class Rva001E7087
{
	friend class AIUpdateInterface;
public:
	Rva001E7087();
protected:
	virtual ~Rva001E7087();
private:
	void rvaClear();
	unsigned char m_pad04[0x24 - 4];
};

// One class: the 0x26E7C8 ctor installs vtable 0xBFA3A4, whose slot 0 is the
// deleting dtor 0x26E81A over this dtor 0x26E7EA (the +0x224 unwind target).
class Rva0026E7EA
{
public:
	Rva0026E7EA() throw();
	virtual ~Rva0026E7EA();
private:
	unsigned char m_pad[0xC];
};

class Rva0042526Member
{
public:
	Rva0042526Member() throw();
private:
	unsigned char m_pad[0x4C];
};

namespace _STL {
template <int _Words> struct _Base_bitset
{
	_Base_bitset() throw();
	unsigned long _M_w[_Words];
};
}

class Rva0026AFDAMember
{
public:
	__declspec(dllimport) __forceinline Rva0026AFDAMember() throw() { initMember(); }
	Rva0026AFDAMember *initMember() throw();
	~Rva0026AFDAMember();
private:
	unsigned char m_pad[0xC4];
};

class Rva00262436
{
public:
	Rva00262436 *rva00262436(int owner);
private:
	unsigned char m_pad[0xC];
};

class TurretAI
{
public:
	TurretAI(Object *owner, const TurretAIData *data, WhichTurretType tur);
private:
	unsigned char m_pad[0x40];
};

#include "../../../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class LuaScriptEngine
{
public:
	Rva00336283Element *rva00337DEF(const AsciiString &name);
};
extern LuaScriptEngine *TheLuaScriptEngine;

class AIUpdateInterface : public UpdateModule, public AIUpdateInterfaceFourth, public AIUpdateInterfaceFifth
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	virtual bool chooseLocomotorSet(int wst);
protected:
	virtual ~AIUpdateInterface();
	const AIUpdateModuleDataView *getAIUpdateModuleData() const { return (const AIUpdateModuleDataView *)m_moduleData; }
private:
	int m_priorWaypointID;				// +0x28
	int m_currentWaypointID;			// +0x2C
	StateMachine *m_stateMachine;			// +0x30
	int m_nextEnemyScanTime;			// +0x34
	int m_currentVictimID;				// +0x38
	int m_3C;
	int m_40;
	float m_desiredSpeed;				// +0x44
	int m_lastCommandSource;			// +0x48
	int m_guardMode;				// +0x4C
	int m_guardTargetType[2];			// +0x50
	AIUpdatePoint m_locationToGuard;		// +0x58
	int m_objectToGuard;				// +0x64
	int m_areaToGuard;				// +0x68
	int m_6C;
	const AttackPriorityInfo *m_attackInfo;		// +0x70
	Coord3D m_waypointQueue[16];			// +0x74
	int m_waypointCount;				// +0x134
	int m_waypointIndex;				// +0x138
	int m_completedWaypoint;			// +0x13C
	int m_path;					// +0x140
	int m_requestedVictimID;			// +0x144
	AIUpdatePoint m_requestedDestination;		// +0x148
	AIUpdatePoint m_requestedDestination2;		// +0x154
	int m_pathTimestamp;				// +0x160
	int m_ignoreObstacleID;				// +0x164
	float m_pathExtraDistance;			// +0x168
	int m_16C;
	float m_170;
	float m_bumpSpeedLimit;				// +0x174
	int m_178;
	int m_17C;
	AIUpdatePoint m_finalPosition;			// +0x180
	int m_18C;
	int m_190;
	int m_194;
	int m_198;
	int m_19C;
	float m_1A0;
	int m_1A4;
	unsigned char m_pad1A8[0x1C8 - 0x1A8];
	int m_1C8;
	Rva001E7087 m_locomotorSet;			// +0x1CC
	Locomotor *m_curLocomotor;			// +0x1F0
	int m_curLocomotorSet;				// +0x1F4
	float m_1F8;
	int m_1FC;
	AIUpdatePoint m_locomotorGoalData;		// +0x200
	TurretAI *m_turretAI[1];			// +0x20C
	int m_210;
	AsciiString m_214;				// +0x214
	int m_218;
	int m_21C;
	Rva00336283Element *m_objectEventsList;		// +0x220
	Rva0026E7EA m_224;				// +0x224
	int m_234;
	int m_238;
	int m_23C;
	int m_240;
	Rva0042526Member m_244;				// +0x244
	Rva0042526Member m_290;				// +0x290
	_STL::_Base_bitset<4> m_2DC;			// +0x2DC
	Rva0026AFDAMember m_2EC;			// +0x2EC
	bool m_3B0, m_3B1, m_3B2, m_3B3, m_3B4, m_3B5, m_3B6, m_3B7;
	bool m_3B8, m_3B9, m_3BA, m_3BB, m_3BC, m_3BD, m_3BE, m_3BF;
	bool m_3C0, m_3C1, m_3C2, m_3C3, m_3C4, m_3C5, m_3C6, m_3C7;
	bool m_3C8, m_3C9, m_3CA, m_3CB, m_3CC, m_3CD, m_3CE, m_3CF;
	Rva00262436 m_3D0;				// +0x3D0
	int m_3DC;
	bool m_3E0;
};

AIUpdateInterface::AIUpdateInterface(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_178(0),
	m_1A0(3.402823466e+38f),
	m_1C8(0),
	m_objectEventsList(0),
	m_234(0),
	m_3C1(false),
	m_3CD(false),
	m_3CE(false),
	m_3CF(false)
{
	int i;

	m_3D0.rva00262436((int)this);
	m_3E0 = false;
	m_priorWaypointID = 0xfacade;
	m_currentWaypointID = 0xfacade;
	m_stateMachine = 0;
	m_nextEnemyScanTime = 0;
	m_currentVictimID = 0;
	m_3C = 0;
	m_40 = 0;
	m_desiredSpeed = 999999.0f;
	m_lastCommandSource = 2;
	m_guardMode = 0;
	m_guardTargetType[0] = m_guardTargetType[1] = 4;
	m_locationToGuard.zero();
	m_objectToGuard = 0;
	m_areaToGuard = 0;
	m_240 = 0;
	m_6C = 0;
	m_attackInfo = 0;
	m_waypointCount = 0;
	m_waypointIndex = 0;
	m_completedWaypoint = 0;
	m_path = 0;
	m_requestedVictimID = 0;
	m_requestedDestination.zero();
	m_requestedDestination2.zero();
	m_pathTimestamp = 0;
	m_ignoreObstacleID = 0;
	m_pathExtraDistance = 0.0f;
	m_16C = 0;
	m_170 = 0.0f;
	m_bumpSpeedLimit = 999999.0f;
	m_17C = 0;
	m_finalPosition.zero();
	m_18C = 0;
	m_190 = 0;
	m_194 = -1;
	m_198 = 0;
	m_19C = 0;
	m_locomotorSet.rvaClear();
	m_curLocomotor = 0;
	m_curLocomotorSet = -1;
	m_1F8 = 0.0f;
	m_1FC = 0;
	m_locomotorGoalData.zero();
	for (i = 0; i < 1; i++)
		m_turretAI[i] = 0;
	m_210 = -1;
	m_218 = 0;
	m_21C = 0;
	m_238 = 0;
	m_23C = 0;
	m_3B0 = false;
	m_3B1 = false;
	m_3DC = 0;
	m_3B2 = false;
	m_3B3 = false;
	m_3B4 = false;
	m_3B5 = false;
	m_3B6 = false;
	m_3B7 = false;
	m_3B8 = false;
	m_3B9 = false;
	m_3BA = false;
	m_3BB = false;
	m_3BC = false;
	m_3BD = false;
	m_3BE = true;
	m_3BF = false;
	m_3C0 = false;
	m_3C2 = false;
	m_3C3 = false;
	m_1A4 = 0;
	m_3C4 = false;
	m_3C7 = false;
	m_3C5 = false;
	m_3C6 = false;
	m_3C8 = true;
	m_3C9 = false;
	m_3CA = false;
	memset(&m_244, 0, sizeof(m_244));
	m_3CB = false;
	m_3CC = false;

	const AIUpdateModuleDataView *aIUpdateModuleDataView = getAIUpdateModuleData();
	for (i = 0; i < 1; i++)
	{
		if (aIUpdateModuleDataView->m_turretData[i])
			m_turretAI[i] = new TurretAI(getObject(), aIUpdateModuleDataView->m_turretData[i], (WhichTurretType)i);
	}

	chooseLocomotorSet(0);

	if (!aIUpdateModuleDataView->m_attackPriorityName.isEmpty())
	{
		m_attackInfo = TheScriptEngine->getAttackInfo(aIUpdateModuleDataView->m_attackPriorityName);
		aIUpdateModuleDataView->m_attackPriorityName.compare("DefaultAttackPriority");
	}

	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);

	m_objectEventsList = TheLuaScriptEngine->rva00337DEF(aIUpdateModuleDataView->m_objectEventsListName);
}
