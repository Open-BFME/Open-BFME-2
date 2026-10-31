// cl: /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP=
// stlport
//
// AIStates.cpp bodies of BFME 2's attack state machine that are not yet rowed
// in the per-state units (declarations carried from
// AIAttackApproachTargetStateOnEnter.cpp, the same unit's views).
//
// AIAttackMeleeEngageState::updateInternal, retail 0x003497E6 (1308 bytes):
// the update helper of vtable 0x00C12150 (its CRC trace literal names it;
// matched slot 0x00349D02 calls it and sets status 0x1C on -1). Ported from
// Open-BFME-1's AIAttackMeleeEngageState_updateInternal.cpp (retail 0x00178470
// there). The victim test is two statements in retail: a combined
// "!victim || status 0x33" return lets cl lay the merged FAILURE return block
// at the retry site, while retail keeps it at the computePath failure.

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include <vector>
// Keep the retail direct call to the CRT fprintf thunk. /D_CRTIMP= avoids
// changing it to an indirect IAT call when adopting the real FILE signature.
#include <stdio.h>
#include "Coord2D.h"
#include "Common/Snapshot.h"
#include "RTS/XYDistanceCallView.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum WhichTurretType
{
	TURRET_INVALID = -1
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum KindOfType
{
	KINDOF_CE = 0xCE
};
enum MoodMatrixAction
{
	MM_Action_Attack = 2
};
enum WeaponStatus
{
	READY_TO_FIRE = 0,
	PRE_ATTACK = 4
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_0D = 0x0D,
	OBJECT_STATUS_19 = 0x19,
	OBJECT_STATUS_1B = 0x1B,
	OBJECT_STATUS_1C = 0x1C,
	OBJECT_STATUS_25 = 0x25,
	OBJECT_STATUS_26 = 0x26,
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_33 = 0x33,
	OBJECT_STATUS_41 = 0x41,
	OBJECT_STATUS_44 = 0x44,
	OBJECT_STATUS_4B = 0x4B,
	OBJECT_STATUS_52 = 0x52
};

class Object;
class Weapon;

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		FILE *log = static_cast<FILE *>(theLogicRandomLogFile);
		if (log != 0)
			fprintf(log, text);
	}
}

// math.h: its sqrt declaration keeps the x87 result store after the argument
// pops, and its float fabs overload is the CRT fabs compared as float.
#include <math.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
Real normalizeAngle(Real angle);

#define PATHFIND_CELL_SIZE_F 10.0f

extern int BfmeLogicFramesPerSecond;
#define LOGICFRAMES_PER_SECOND BfmeLogicFramesPerSecond

extern GameLogic *TheGameLogic;

class TAiData
{
public:
	unsigned char m_pad00[0x4C];
	Real m_alertRangeModifier; // +0x4C
	Real m_aggressiveRangeModifier; // +0x50
	unsigned char m_pad54[0x8C - 0x54];
	Bool m_aiCrushesInfantry; // +0x8C
	unsigned char m_pad8D[0xB8 - 0x8D];
	Bool m_teamPathWait; // +0xB8
};

class Rva002C9B80Owner;
class LocomotorSet;

class Pathfinder
{
public:
	Bool AdjustDestination(Object *obj, const LocomotorSet &set, Coord3D *dest, const Coord3D *group);
	Bool isAttackViewBlockedByObstacle(const Object *obj, const Coord3D *objPos, const Object *target, const Coord3D *targetPos);
	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
	Bool rva002ED313(Object *obj);
};

class AI
{
public:
	static Bool rva002FE193(Object *owner, Object *nemesis);
	Pathfinder *pathfinder() { return m_pathfinder; }
	const TAiData *getObservedAiData() { return m_aiData; }
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

class Locomotor
{
public:
	Real getMaxSpeed(Object *obj) const;
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS
	};
	Real getMaxTurnRate(Object *obj) const;
	const struct LocomotorTemplateView *getTemplate() const { return m_template; }
	void setUsePreciseZPos(Bool b)
	{
		if (b)
			m_flags |= (1 << PRECISE_Z_POS);
		else
			m_flags &= ~(1 << PRECISE_Z_POS);
	}
private:
	unsigned char m_pad00[4];
	const struct LocomotorTemplateView *m_template; // +0x04
	unsigned char m_pad08[0x44 - 8];
	unsigned int m_flags; // +0x44
};

struct LocomotorTemplateView { char prefix[0x10B]; Bool m_10b; };
// Locomotor min speed (0x001E3F08), rowed under this name.
struct Rva001E3F08Arg;
class Rva001E3F08
{
public:
	Real rva001E3F08(Rva001E3F08Arg *obj);
};

struct Rva0028AC4EEntry;

// AI current-locomotor speed (0x002627E8), rowed under this name.
class Rva002627E8
{
public:
	Real rva002627E8() const;
};

class AIUpdateModuleData
{
public:
	unsigned char m_pad00[0x20];
	Real m_20; // +0x20
	Bool m_24; // +0x24
};

enum MoodMatrixParameters
{
	MM_Controller_Player = 0x00000001,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200,
	MM_Mood_Normal = 0x00000400,
	MM_Mood_Alert = 0x00000800,
	MM_Mood_Aggressive = 0x00001000,
	MM_Mood_Bitmask = (MM_Mood_Sleep | MM_Mood_Passive | MM_Mood_Normal | MM_Mood_Alert | MM_Mood_Aggressive)
};

template <int N> class AIApproachAISlots : public AIApproachAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIApproachAISlots<0>
{
};

// The 0x00262FEB one-store setter is ICF-shared with the rowed
// ParticleEmitterDefClass::Set_Burst_Size; retail calls it directly.
class ParticleEmitterDefClass
{
public:
	virtual void Set_Burst_Size(unsigned int value);
};

class AIUpdateInterface : public AIApproachAISlots<135>
{
public:
	virtual void slot135(Real angle) = 0;
	virtual void slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142(Int mode) = 0;
	virtual Int slot143() = 0;
	virtual void notifyVictimIsDead() = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	Int rva00260DED() const;
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Bool isQuickPathAvailable(const Coord3D *destination) const;
	Real getTurretTurnRate(WhichTurretType tur) const;
	Real getCurLocomotorSpeed() const { return ((const Rva002627E8 *)this)->rva002627E8(); }
	void setCurrentVictim(const Object *victim);
	void setDesiredSpeed(Real speed);
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void requestAttackPath(ObjectID victimID, const Coord3D *victimPos);
	void destroyPath();
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void friend_setGoalObject(Object *obj);
	Bool isMoving() const;
	void requestApproachPath(Coord3D *destination);
	void *getPath() const { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	Bool isBlockedAndStuck() const { return m_blockedFrames > 0; }
	UnsignedInt getMoodMatrixValue() const;
	Bool isAttackPath() const { return m_3b2; }
	void setPathExtraDistance(Real dist);
	Object *checkForCrateToPickup();
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void rva00262AEA();
	void rva00262ACE();
	__declspec(dllimport) __forceinline void rva00262FEB(Int id) { ((ParticleEmitterDefClass *)this)->ParticleEmitterDefClass::Set_Burst_Size(id); }
	const LocomotorSet *getLocomotorSet() const { return (const LocomotorSet *)m_locomotorSet; }
private:
	const AIUpdateModuleData *m_moduleData; // +0x04
	unsigned char m_pad008[0x30 - 0x08];
public:
	class Rva00346FA5 *m_goalPath; // +0x30
private:
	unsigned char m_pad034[0x48 - 0x34];
public:
	Int m_48; // +0x48
private:
	unsigned char m_pad04C[0x140 - 0x4C];
	void *m_path; // +0x140
	unsigned char m_pad144[0x16C - 0x144];
public:
	Int m_blockedFrames; // +0x16C
	unsigned char m_pad170[0x180 - 0x170];
	Coord3D m_finalPosition; // +0x180
	unsigned char m_pad18C[0x194 - 0x18C];
	Int m_currentGoalPathIndex; // +0x194
	unsigned char m_pad198[0x1A0 - 0x198];
	Int m_1a0; // +0x1A0
	unsigned char m_pad1A4[0x1CC - 0x1A4];
	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
private:
	Locomotor *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x3B0 - 0x1F4];
public:
	Bool m_3b0; // +0x3B0
private:
	Bool m_waitingForPath; // +0x3B1
	Bool m_3b2; // +0x3B2
	unsigned char m_pad3B3[0x3C1 - 0x3B3];
public:
	Bool m_3c1; // +0x3C1
	unsigned char m_pad3C2[0x3C7 - 0x3C2];
	Bool m_3c7; // +0x3C7
	unsigned char m_pad3C8[0x3CC - 0x3C8];
	Bool m_3cc; // +0x3CC
};

class ThingTemplate
{
public:
	Bool isKindOfImmobile() const { return (m_kindOf[0] & 4) != 0; }
	Bool isKindOfProjectile() const { return (m_kindOf[3] & 2) != 0; }
	UnsignedInt kindOfWord(Int i) const { return ((const UnsignedInt *)m_kindOf)[i]; }
	unsigned char m_pad00[0x108];
	volatile unsigned char m_kindOf[0x14]; // +0x108
	unsigned char m_pad11C[0x122 - 0x11C];
	unsigned char m_122; // +0x122
	unsigned char m_pad123[0x53C - 0x123];
	Real m_firingArc; // +0x53C
	unsigned char m_pad540[0x5FD - 0x540];
	Bool m_useCrushAttack; // +0x5FD
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const Coord3D *getUnitDirectionVector2D() const;
	void setOrientation(Real angle);
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class Team;
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};
// The member walk (rowed iterate_TeamMemberList 0x00263864 and advance
// 0x00263526), as ScriptActions_doPlayerForceEmotion.cpp declares it.
template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

#include "../../../Include/Common/MemoryPoolObject.h"

class TeamPrototype
{
public:
	unsigned char m_pad00[0x216];
	Bool m_216; // +0x216
	unsigned char m_pad217[0x334 - 0x217];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

#include "../../../Include/Common/TeamBFME2.h"

inline DLINK_ITERATOR<Team> iterate_TeamInstanceList(const TeamPrototype *proto)
{
	return DLINK_ITERATOR<Team>(proto->m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
public:
	unsigned char m_pad00[0x5C];
	Int m_playerType; // +0x5C
	unsigned char m_pad60[0x32C - 0x60];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
};

// Object +0xA8 geometry-shape list (index accessor 0x006BD980, rowed under
// this name); each shape carries its bounding radius at +0x08.
struct BfmeShapeE15
{
	unsigned char m_pad00[0x08];
	Real m_boundingRadius; // +0x08
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *getGeometryShape(Int index);
	unsigned char m_pad00[0x10];
};

class Object : public Thing
{
public:
	Bool rva0028CECF();	// thing-template gate, rowed 0x0028CECF
	AIUpdateInterface *getObservedAI() { return m_ai; }
	Object *getContainedBy() { return m_containedBy; }
	Object *getOutermostContainer()
	{
		Object *container = m_containedBy;
		while (container && container->m_containedBy)
			container = container->m_containedBy;
		return container;
	}
	Bool isInImmobileContainer()
	{
		Object *container = getOutermostContainer();
		return container && container->isKindOfImmobile();
	}
	Bool isKindOfImmobile() const { return getTemplate()->isKindOfImmobile(); }
	Bool isKindOfProjectile() const { return getTemplate()->isKindOfProjectile(); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	Player *getControllingPlayer() const;
	Int rva0028B511() const;
	Bool isMobile() const;
	Bool isSignificantlyAboveTerrain() const;
	Bool rva0029493F(Object *other, Int test);
	Real rva0028AC7D() const;
	Bool hasAnyWeapon() const;
	const Rva0028AC4EEntry *rva0028AC4E() const;
	void rva0028CDB6();
	Bool rva0028C264(Int *out, Int kind);
	Real GetRelativeAngle(const Coord3D *pos) const;
	Real getOrientation() const { return m_orientation; }
	Bool rva002943B2(const Player *player);
	Object *rva002931F5(Bool flag);
	void rva00346C53(ObjectStatusTypes bit, Bool set);
	void rva0028AE6D();
	void rva0028ACDC(int pos);
	void setStatus(ObjectStatusTypes bit, Bool set);
	Bool isKindOf(KindOfType t) const;
	void preFireCurrentWeapon(const Object *victim, const Coord3D *pos);
	void setFiringConditionForCurrentWeapon();
	void fireCurrentWeapon(const Coord3D *pos);
	void rva0028ACEE(int pos, Int layer);
	Bool GetGoalPosition(Coord3D *pos) const;
	void *rva0029439D();
	ObjectID getID() const { return (ObjectID)m_id; }
	Real m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	Int m_id; // +0x74
	unsigned char m_pad078[0xA8 - 0x78];
	BfmeObjE15 m_geometryShapes; // +0xA8
	Real m_geometryRadiusB8; // +0xB8
	unsigned char m_pad0BC[0x110 - 0xBC];
	UnsignedInt m_110; // +0x110
	unsigned char m_pad114[0x1C0 - 0x114];
	Real m_1c0; // +0x1C0
	unsigned char m_pad1C4[0x1C8 - 0x1C4];
	UnsignedInt m_1c8; // +0x1C8
	unsigned char m_pad1CC[0x249 - 0x1CC];
	Bool m_249; // +0x249
	unsigned char m_pad24A[0x250 - 0x24A];
	void *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	void *m_physics; // +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x410 - 0x308];
	Int m_410; // +0x410
	unsigned char m_pad414[0x438 - 0x414];
	UnsignedInt m_438; // +0x438
};

Bool rva00344EB2Gate(Object *obj, Thing *other);

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Rva002C9407ByteField
{
public:
	unsigned char get() const;
};
class Rva002C940EByteField
{
public:
	unsigned char get() const;
};

class WeaponTemplate
{
public:
	Bool isContactWeapon() const;
	unsigned char m_pad00[0x2C];
	Real m_aimDelta; // +0x2C
	Real m_aimOffset; // +0x30
	unsigned char m_pad34[0x16B - 0x34];
	Bool m_noVictimNeeded; // +0x16B
};

#include "../../../Include/GameLogic/Weapon.h"

// BFME 2's partition filter base (ctor 0x000421C8): a vptr and the +0x04 link
// to the next filter (link 0x00625790 appends its argument and returns this).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *objOther) = 0;
	virtual Int getPlayerMask(); // slot 2, 0x0036CC7A
	Rva000421C8 *link(Rva000421C8 *next);
private:
	Rva000421C8 *m_next; // +0x04
};

// The line-of-sight partition filter (vtable 0x00C07150).
class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(Object *owner) : m_owner(owner) {}
	virtual ~Rva002619C1Filter() {}
	virtual Bool allow(Object *other);

	Object *m_owner;
};

template <int N> class StateMachineSlots : public StateMachineSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class StateMachineSlots<0>
{
};

// A state's ID (+0x04), as StateMachine::getCurrentStateID reads it.
template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};

// A machine's current state: slot 8 answers whether it is an idle state.
class StateIdleView : public VirtualSlots<8>
{
public:
	virtual Bool isIdle() const;
};

enum
{
	AI_ATTACK_OBJECT = 10,
	AI_PICK_UP_CRATE = 0x27
};

class StateMachine : public StateMachineSlots<4>
{
public:
	virtual StateReturnType updateStateMachine(); // slot 4
	virtual void slot05();
	virtual void slot06();
	virtual StateReturnType initDefaultState(); // slot 7
	virtual StateReturnType setState(UnsignedInt newStateID); // slot 8
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj); // slot 14
	Bool isGoalObjectDestroyed() const;
	Bool isInIdleState() const { return m_currentState ? m_currentState->isIdle() : true; }
	void setGoalPosition(const Coord3D *pos);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	// This local +0x24 view must not emit the shared +0x28 getter.
	const Coord3D *locomotorGoalPosition() const { return &m_goalPosition; }
private:
	StateIdleView *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void slot05();
	virtual StateReturnType update();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Bool computePath();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getObservedMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->locomotorGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
	Bool getAdjustsDestination() const;
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - 0x2C];
	Bool m_adjustsDestination; // +0x48
	Bool m_waitingForPath; // +0x49
};

class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	StateReturnType updateInternal();
	Coord3D m_prevVictimPos; // +0x4C
	Coord3D m_ownerPosition; // +0x58
	Int m_approachTimestamp; // +0x64
	UnsignedInt m_waitFrame; // +0x68
	Bool m_follow; // +0x6C
	Bool m_isAttackingObject; // +0x6D
	Bool m_stopIfInRange; // +0x6E
	Bool m_isInitialApproach; // +0x6F
	Bool m_isForceAttacking; // +0x70
	Bool m_waiting; // +0x71
};

// The BFME 2 approach variant of vtable 0x00C12678 (rowed onExit/update in
// AIAttackApproachTargetStateOnExit.cpp, constructor 0x00342978).
class AIAttackApproachTargetState00C12678 : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	Coord3D m_ownerPosition; // +0x4C
	Int m_approachTimestamp; // +0x58
	UnsignedInt m_waitFrame; // +0x5C
	Bool m_stopIfInRange; // +0x60
	Bool m_isInitialApproach; // +0x61
	Bool m_waiting; // +0x62
};

// AIAttackPursueTargetState, vtable 0x00C12730 (constructor 0x003429B9;
// rowed updateInternal 0x0034939E).
class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	Coord3D m_prevVictimPos; // +0x4C
	UnsignedInt m_approachTimestamp; // +0x58
	Bool m_follow; // +0x5C
	Bool m_isAttackingObject; // +0x5D
	Bool m_stopIfInRange; // +0x5E
	Bool m_isInitialApproach; // +0x5F
	Bool m_isForceAttacking; // +0x60
};

// AIAttackFireDuringApproachState, vtable 0x00C12798 (rowed xfer 0x0034081A).
class AIAttackFireDuringApproachState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	UnsignedInt m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	ObjectID m_victimID; // +0x64
	Bool m_68; // +0x68
};

// The pathfinder's melee engagement-spot search (0x002F23A6), pinned under
// this name.
class Rva002F23A6
{
public:
	Bool rva002F23A6(Object *source, int weapon, int locomotorSet, Coord3D *goalPos,
		Object *victim);
};

// TheGameLogic's BFME debug level (+0x1B4), private padding in the shared
// GameLogic view.
static __forceinline Int gameLogicDebugLevel()
{
	return *(const Int *)((const char *)TheGameLogic + 0x1B4);
}

static __forceinline void debugTrace(const char *text)
{
	FILE *log = static_cast<FILE *>(theLogicRandomLogFile);
	if (log != 0)
		fprintf(log, text);
}

// The object behind Object::rva0029439D; its slot 68 yields the object a
// melee squish should really target.
class Rva0029439DView : public VirtualSlots<68>
{
public:
	virtual Object *slot68();
};

// AIAttackMeleeSquishState, vtable 0x00C12868 (rowed xfer 0x00340A92, onExit
// 0x003497C7).
class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	UnsignedInt m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	Bool m_64; // +0x64
};

// AIAttackFireWeaponState, vtable 0x00C111F8.
class AIAttackFireWeaponState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	void *m_att; // +0x1C
	Int m_20; // +0x20
	Bool m_waitOddFrame; // +0x24
};

// An enclosing container's contain module (Object +0x250), slot 77.
class ContainFirePointView : public VirtualSlots<77>
{
public:
	virtual Bool attemptBestFirePointPosition(Object *source, Weapon *weapon, const Coord3D *targetPos);
};

// The AI's locomotor-goal slots (132 and 135), as AIFaceStateUpdate.cpp views them.
class AITurnView : public VirtualSlots<132>
{
public:
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &newPos);
	virtual void slot133();
	virtual void slot134();
	virtual void setLocomotorGoalOrientation(Real angle);
};

// The AI's goal path (+0x30): position by index (0x00346FA5).
class Rva00346FA5
{
public:
	void *rva00346FA5(Int index) const;
	char m_pad[0x3C];
	_STL::vector<Coord3D> m_goalPath;
};
void *Rva00346FA5::rva00346FA5(Int i) const
{
	if (i < 0 || i >= m_goalPath.size())
		return NULL;

	return (void *)&m_goalPath[i];
}

class Rva00340E5E
{
public:
	Real rva00340E5E() const;
};

// AIFollowPathAsTeamState, vtable 0x00C121E8.
class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	Bool canMoveToNextFormationPathPoint();
	Int m_index; // +0x4C
	Int m_retryCount; // +0x50
	Bool m_adjustFinal; // +0x54
	Bool m_adjustFinalOverride; // +0x55
	Bool m_waitingForTeam; // +0x56
	Bool m_57; // +0x57
	Int m_lastCommandSource; // +0x58
	StateMachine *m_5c; // +0x5C
	Real m_60; // +0x60
	Bool m_64; // +0x64
};

// AIAttackPositionAimAtTargetState, vtable 0x00C11068.
class AIAttackPositionAimAtTargetState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	StateReturnType updateInternal(Bool firstFrame);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_canTurnInPlace; // +0x20
	Bool m_setLocomotor; // +0x21
};

// The attack state a fire state reports to (AIAttackState's machine).
class AttackStateHost
{
public:
	virtual void notifyFired();
	virtual void slot01();
	virtual Bool isWeaponSlotOkToFire(WeaponSlotType wslot);
};

// AIAttackPositionFireWeaponState, vtable 0x00C11258.
class AIAttackPositionFireWeaponState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	Int m_1c; // +0x1C
	AttackStateHost *m_att; // +0x20
	Bool m_waitOddFrame; // +0x24
};

// The melee engage state's private fire state (constructor 0x0033F483).
class Rva0033F483 : public VirtualSlots<4>
{
public:
	Rva0033F483(StateMachine *machine, Int weaponSlot);
	virtual StateReturnType onEnter();
	virtual void onExit(Int status);
	virtual StateReturnType update();
	unsigned char m_pad04[0x28 - 0x04];
};

// A resolved target's contain module (Object +0x250), slot 31, and the rider
// it returns (slot 18), as AIAttackMeleeEngageState::updateInternal calls them.
class Rva003497E6Rider : public VirtualSlots<18>
{
public:
	virtual Object *slot18(Int, const Coord3D *pos, Real, Int, Int);
};

class Rva003497E6Contain : public VirtualSlots<31>
{
public:
	virtual Rva003497E6Rider *slot31();
};

// AIAttackMeleeEngageState, vtable 0x00C12150 (computePath 0x003457AC rowed in
// AIStatesBfmeComputePath.cpp).
class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	StateReturnType updateInternal();
	Rva0033F483 *m_fireState; // +0x4C
	Int m_50; // +0x50
	UnsignedInt m_approachTimestamp; // +0x54
	Coord3D m_prevVictimPos; // +0x58
	unsigned char m_pad64[0x6C - 0x64];
	UnsignedInt m_retryFrame; // +0x6C
	Bool m_retryPending; // +0x70
	Bool m_noEngagementSpot; // +0x71
	unsigned char m_pad72[0x74 - 0x72];
	Int m_weaponSlot; // +0x74
};

// Physics flag-pair check (0x00390533), pinned under this name.
class Rva00390533
{
public:
	Bool rva00390533();
};

Bool Rva0034311ECheck(Object *obj);
Bool rva003430A3(Object *source, Object *victim, Weapon *weapon);

// Retail 0x003497E6, 1308 bytes (vtable 0x00C12150's update helper; its CRC
// literal names it). Ported from Open-BFME-1's
// AIAttackMeleeEngageState_updateInternal.cpp (retail 0x00178470 there): the
// fire state, retry frame and flags sit four bytes lower in BFME 2, the
// status bits are 0x33/0x4B/0x25, the goal update is the 0x0028ACEE
// /GetGoalPosition pair the onEnter above uses, and the retry delays are five
// and two LOGICFRAMES_PER_SECOND.
StateReturnType AIAttackMeleeEngageState::updateInternal()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getObservedAI();
	Object *victim = getObservedMachineGoalObject();
	if (!victim)
		return STATE_FAILURE;
	if (victim->testStatus(OBJECT_STATUS_33))
		return STATE_FAILURE;
	if (victim->rva002943B2(source->getControllingPlayer()))
		return STATE_FAILURE;
	if (victim->m_438 & 1)
		return STATE_FAILURE;

	ai->setCurrentVictim(victim);
	if (source->rva0029493F(victim, 2) && source->getTemplate()->m_useCrushAttack &&
		source->rva0028CECF())
		return STATE_SUCCESS;

	if (m_retryPending)
	{
		if (m_retryFrame >= TheGameLogic->getFrame())
			return STATE_CONTINUE;
		m_retryPending = false;
		return STATE_FAILURE;
	}

	Bool inRange = false;
	if (rva00344EB2Gate(source, victim))
	{
		inRange = true;
		Real dist = (Real)sqrt(((Rva000CBA20 *)source)->distSq((const Rva000CBA20Point *)victim->getPosition()));
		Real sourceRadius = source->m_geometryShapes.getGeometryShape(0)->m_boundingRadius;
		BfmeShapeE15 *victimShape = victim->m_geometryShapes.getGeometryShape(0);
		Real surfaceGap = dist - (victimShape->m_boundingRadius + (sourceRadius + 10.0f));
		Real gap = surfaceGap + victim->rva0028AC7D();
		if (gap < 0.0f)
			gap = 0.0f;

		Real maxSpeed = 999999.0f;
		if (source->rva0028AC4E())
			maxSpeed = ((Locomotor *)source->rva0028AC4E())->getMaxSpeed(source);
		ai->setDesiredSpeed(gap);
		Bool closing = gap < maxSpeed;
		source->setStatus(OBJECT_STATUS_4B, closing);
		source->rva00346C53(OBJECT_STATUS_4B, closing);

		if (closing && m_50)
			m_50 = m_fireState->onEnter();

		Object *resolved = victim->rva002931F5(false);
		if (!m_50)
		{
			m_50 = m_fireState->update();
			if (m_50)
				m_fireState->onExit(0);

			if ((victim->m_438 & 1) && resolved)
			{
				Rva003497E6Contain *contain = (Rva003497E6Contain *)resolved->m_contain;
				if (contain)
				{
					Rva003497E6Rider *rider = contain->slot31();
					if (rider)
					{
						victim = rider->slot18(0, source->getPosition(), 0.0f, 0, 0);
						if (!victim)
							return STATE_CONTINUE;
						ai->friend_setGoalObject(victim);
						getMachine()->setGoalObject(victim);
					}
				}
			}
		}
	}
	else
	{
		ai->setDesiredSpeed(999999.0f);
		if (!m_50)
		{
			m_fireState->onExit(0);
			m_50 = -1;
		}
		if (source->testStatus(OBJECT_STATUS_4B))
		{
			source->rva00346C53(OBJECT_STATUS_4B, false);
			source->setStatus(OBJECT_STATUS_4B, false);
		}
	}

	if (source->testStatus(OBJECT_STATUS_1C) && !inRange)
		ai->destroyPath();

	Weapon *weapon = source->getCurrentWeapon();
	if ((gameLogicDebugLevel() > 0 && source->testStatus(OBJECT_STATUS_25) && victim->testStatus(OBJECT_STATUS_25)) ||
		(!ai->getPath() && weapon))
		debugTrace("masiwar called by AIAttackMeleeEngageState::updateInternal [1]");
	if ((source->testStatus(OBJECT_STATUS_25) && victim->testStatus(OBJECT_STATUS_25)) ||
		(!ai->getPath() && weapon && weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1) &&
			TheAI->pathfinder()->rva002ED313(source)))
	{
		Coord3D pos;
		pos.x = source->getPosition()->x;
		pos.y = source->getPosition()->y;
		pos.z = source->getPosition()->z;
		source->rva0028ACEE((int)&pos, source->rva0028B511());
		if (source->GetGoalPosition(&pos))
		{
			ai->m_finalPosition = pos;
			ai->m_3b0 = false;
		}
		source->setStatus(OBJECT_STATUS_1C, true);
		return STATE_SUCCESS;
	}

	critterDesyncLog("CritterDesync: ComputePath28");
	if (computePath() == false)
		return STATE_FAILURE;
	if (m_retryPending)
		return STATE_CONTINUE;

	StateReturnType code = AIInternalMoveToState::update();
	if (inRange)
	{
		if (code == STATE_CONTINUE)
			return STATE_CONTINUE;
	}
	else if (code == STATE_CONTINUE)
	{
		if (ai->getPath() || m_waitingForPath)
			return STATE_CONTINUE;
	}

	Bool canRepath = TheAI->pathfinder()->rva002ED313(source);
	if (!ai->getPath())
		canRepath = true;
	if (weapon && weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1) && canRepath)
	{
		Coord3D pos;
		pos.x = source->getPosition()->x;
		pos.y = source->getPosition()->y;
		pos.z = source->getPosition()->z;
		source->rva0028ACEE((int)&pos, source->rva0028B511());
		if (source->GetGoalPosition(&pos))
		{
			ai->m_finalPosition = pos;
			ai->m_3b0 = false;
		}
		return STATE_SUCCESS;
	}

	m_retryPending = true;
	if (m_noEngagementSpot)
		m_retryFrame = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND * 5;
	else
		m_retryFrame = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND * 2;
	return STATE_CONTINUE;
}

// WB E20060 names AIAttackPositionAimAtTargetState::updateInternal.
// AIAttackPositionAimAtTargetState's aim body, retail 0x0034A570 (665 bytes):
// vtable 0x00C11068's update (0x0034A871) calls it with false and its onEnter
// tail with true. Zero Hour's AIAttackAimAtTargetState::update position path
// with BFME 2's hasAnyWeapon test, turret turn rate, weapon aimDelta +0x2C
// (at least 0.035, 0.3 with Object +0x1C8 bit 3), locomotor max turn rate,
// the template +0x53C half-angle gate driving AI slot 142 (0/15) and Object
// +0x1C0, and the weapon aim offset +0x30 through normalizeAngle. math.h's
// float fabs overload (the CRT fabs, compared as float) gives retail's x87
// argument-pop schedule; a bare extern "C" float fabs(double) moves two pops.
StateReturnType AIAttackPositionAimAtTargetState::updateInternal(Bool firstFrame)
{
	Object *source = getMachineOwner();
	AIUpdateInterface *sourceAI = source->getObservedAI();
	if (!sourceAI)
		return STATE_FAILURE;
	if (!source->hasAnyWeapon())
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon();
	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		sourceAI->setTurretTargetPosition(tur, getMachineGoalPosition());
		if (sourceAI->getTurretTurnRate(tur) != 0.0f)
			return STATE_CONTINUE;
	}

	Real aimDelta = weapon ? weapon->getTemplate()->m_aimDelta : 0.0f;
	const Real REL_THRESH = 0.035f;
	if (aimDelta < REL_THRESH)
		aimDelta = REL_THRESH;
	Real turnRate = 0.0f;
	if (source->rva0028AC4E())
		turnRate = ((const Locomotor *)source->rva0028AC4E())->getMaxTurnRate(source);
	if ((source->m_1c8 & 8) && aimDelta < 0.3f)
		aimDelta = 0.3f;
	if (source->testStatus(OBJECT_STATUS_4B))
		return STATE_SUCCESS;

	const Coord3D *goalPos = getMachineGoalPosition();
	Coord3D goal;
	goal.x = goalPos->x;
	goal.y = goalPos->y;
	goal.z = goalPos->z;
	Real relAngle = source->GetRelativeAngle(&goal);
	const Real *threshold = &source->getTemplate()->m_firingArc;
	if (*threshold < 360.0f)
	{
		Bool beyond = false;
		Real thresholdValue = *threshold;
		if (fabs(relAngle) > thresholdValue * 0.0087250005f)
			beyond = true;
		sourceAI->slot142(beyond ? 0xF : 0);
		if (beyond)
			source->m_1c0 = source->getOrientation();
	}
	if (weapon)
	{
		Real aimOffset = weapon->getTemplate()->m_aimOffset;
		if (aimOffset > 0.0f)
			relAngle = normalizeAngle(relAngle - aimOffset);
	}

	if (m_canTurnInPlace)
	{
		if (aimDelta < 3.1415927f)
		{
			if (fabs(relAngle) > aimDelta || firstFrame)
			{
				((AITurnView *)sourceAI)->setLocomotorGoalOrientation(source->getOrientation() + relAngle);
				m_setLocomotor = true;
			}
		}
	}
	else
	{
		((AITurnView *)sourceAI)->setLocomotorGoalPositionExplicit(goal);
	}
	if (firstFrame)
		return STATE_CONTINUE;
	if (fabs(relAngle) < aimDelta || fabs(relAngle) < turnRate * 0.5f)
		return STATE_SUCCESS;

	if (source->m_1c8 & 8)
	{
		Weapon *current = source->getCurrentWeapon();
		const Coord3D *targetPos = getMachineGoalPosition();
		if (!current || !current->isWithinAttackRange(source, (void *)targetPos, 0.0f, 1))
			return STATE_FAILURE;
	}
	return STATE_CONTINUE;
}

// Retail 0x00349E74, 348 bytes (after AIFollowPathAsTeamState::onExit; the
// team path update asks it before leaving a path point). With TAiData +0xB8
// set, an owner still on its first two path points with a walking locomotor
// (template byte +0x10B) waits until every other member of its controlling
// player's teams in the same path group (+0x410) that is following the path
// (AI state 0x36, walking) has reached the same point; the 0x0028C264 kind-4
// query on the owner or on any member ends the wait.
Bool AIFollowPathAsTeamState::canMoveToNextFormationPathPoint()
{
	if (!TheAI->getObservedAiData()->m_teamPathWait)
		return true;
	Object *owner = getMachineOwner();
	Object *volatile savedOwner = owner;
	AIUpdateInterface *ai = owner->getObservedAI();
	if (!ai)
		return true;
	Int group = owner->m_410;
	Int index = ai->m_currentGoalPathIndex;
	if (index > 1)
		return true;
	if (ai->getCurLocomotor() && !ai->getCurLocomotor()->getTemplate()->m_10b)
		return true;
	Int unused;
	if (owner->rva0028C264(&unused, 4))
		return true;

	Bool ready = true;
	Player *player = owner->getControllingPlayer();
	for (PlayerTeamNode *it = player->getPlayerTeams()->m_next; it != player->getPlayerTeams(); it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(it->m_value); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
			{
				Object *member = objIter.cur();
				if (member->m_410 != group)
					continue;
				AIUpdateInterface *memberAI = member->getObservedAI();
				if (member == savedOwner)
					continue;
				if (member->rva0028C264(&unused, 4))
					return true;
				if (memberAI && memberAI->rva00260DED() == 0x36 &&
					(!memberAI->getCurLocomotor() || memberAI->getCurLocomotor()->getTemplate()->m_10b) &&
					memberAI->m_currentGoalPathIndex != index)
					ready = false;
			}
		}
	}
	return ready;
}

// WB E19730 names canMoveToNextFormationPathPoint at AIStates.cpp9353.
// Native00349E74..00349FD0 RET0 proves the complete348B boundary.
// The local savedOwner snapshot retains the native frame home while the
// register is reused for the player and member AI; its address never escapes.
// Load member AI before excluding the owner as witnessed by native349F48.
// PMF adjustment uses real MemoryPoolObject/Snapshot inheritance and the
// rowed Team next-member provider; iterator output keeps its witnessed24B ABI.

// Native C11068 slot2 getter names this class; slot6 selects the complete
// 8B34A871 wrapper, push false / call34A570 / ret, preserving EAX.
// WB E20760 calls the named updateInternal E20060 with false.
StateReturnType AIAttackPositionAimAtTargetState::update()
{
	return updateInternal(false);
}

StateReturnType AIAttackFireWeaponState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getObservedAI();
	m_waitOddFrame = false;
	obj->setStatus(OBJECT_STATUS_52, false);
	if ((ai->getMoodMatrixActionAdjustment(MM_Action_Attack) & 1) == 0)
		return STATE_FAILURE;

	Object *victim = getObservedMachineGoalObject();
	if (victim)
	{
		if (!obj->testStatus(OBJECT_STATUS_41) && !obj->isKindOf(KINDOF_CE) &&
			!(victim->getTemplate()->m_kindOf[6] & 0x80) && !(victim->getTemplate()->m_kindOf[0x13] & 8) &&
			!(victim->getTemplate()->m_kindOf[0xB] & 0x40) &&
			victim->getControllingPlayer() == obj->getControllingPlayer())
		{
			ai->friend_setGoalObject(0);
			getMachine()->setGoalObject(0);
			return STATE_FAILURE;
		}
		if ((victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()) ||
			(!(obj->getTemplate()->kindOfWord(3) & 0x2000) && (victim->getTemplate()->kindOfWord(3) & 0x2000)))
		{
			getMachine()->setGoalObject(0);
			return STATE_FAILURE;
		}
	}

	Weapon *weapon = obj->getCurrentWeapon();
 Weapon *volatile savedWeapon=weapon;
	if (!weapon)
		return STATE_FAILURE;
	if (!obj->isKindOfImmobile() && !((const Rva002C940EByteField *)weapon->getTemplate())->get() &&
		!((const Rva002C9400ByteField *)weapon->getTemplate())->get() && ai->isMoving())
		return STATE_FAILURE;

	char inRange;
	if (victim)
	{
		Team *&team = obj->m_team;
		if (team->m_proto->m_216 && !team->getTeamTargetObject())
			team->setTeamTargetObject(victim);
		inRange = savedWeapon->isWithinAttackRange((const Object *)obj, victim, 0.0f, 1);
 weapon=savedWeapon;
	}
	else
	{
		inRange = weapon->isWithinAttackRange(obj, (void *)getMachineGoalPosition(), 0.0f, 1);
	}
	if (!inRange)
		return STATE_FAILURE;
	if (victim)
	{
		if (Rva0034311ECheck(victim))
			return STATE_FAILURE;
		if (!victim->isSignificantlyAboveTerrain() && ai->isDoingGroundMovement() &&
			!rva003430A3(obj, victim, weapon))
			return STATE_FAILURE;
	}

	if (weapon->getStatus() != READY_TO_FIRE)
		return STATE_SUCCESS;
	if (obj->testStatus(OBJECT_STATUS_26) && (TheGameLogic->getFrame() & 1))
	{
		m_waitOddFrame = true;
		return STATE_CONTINUE;
	}
	obj->setStatus(OBJECT_STATUS_0D, true);
	obj->preFireCurrentWeapon(getObservedMachineGoalObject(), getMachineGoalPosition());
	if (weapon->getTemplate()->m_noVictimNeeded && victim)
		getMachine()->setGoalPosition(victim->getPosition());
	return STATE_CONTINUE;
}

StateReturnType AIAttackPositionAimAtTargetState::onEnter()
{
	// contained by AIAttackState, so no separate timer
	Object *source = getMachineOwner();
	Weapon *weapon = source->getCurrentWeapon();
	const Coord3D *targetPos = getMachineGoalPosition();
	AIUpdateInterface *sourceAI = source->getObservedAI();
	Locomotor *curLoco = sourceAI->getCurLocomotor();
	m_setLocomotor = false;
	m_canTurnInPlace = curLoco ? ((Rva001E3F08 *)curLoco)->rva001E3F08((Rva001E3F08Arg *)source) == 0.0f : false;
	source->rva0028CDB6();

	char inFiringRange;
	Object *containedBy = source->m_containedBy;
	if (containedBy && weapon)
		inFiringRange = ((ContainFirePointView *)containedBy->m_contain)->attemptBestFirePointPosition(source, weapon, targetPos);
	else if (weapon)
		inFiringRange = weapon->isWithinAttackRange(source, (void *)targetPos, 0.0f, 1);
	else
		return STATE_FAILURE;

	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		//Order specific turret to attack.
		sourceAI->setTurretTargetPosition(tur, getMachineGoalPosition());
	}
	else
	{
		// Contact weapons don't aim.  They just go boom.  jba.
		if (weapon->getTemplate()->isContactWeapon() && inFiringRange)
			return STATE_SUCCESS;
		if (((const Rva002C9400ByteField *)weapon->getTemplate())->get() && !inFiringRange)
			return STATE_FAILURE;
	}
	if (source->testStatus(OBJECT_STATUS_4B))
		return STATE_SUCCESS;
	source->setStatus(OBJECT_STATUS_19, true);
	return updateInternal(true);
}

// Retail 0x0034E5B5, 1481 bytes: slot 6 of AIFollowPathAsTeamState (vtable
// 0x00C121E8). The team member first lets its own machine (+0x5C) finish an
// attack, then picks up crates (state 0x27) or mood targets (state 10, AI
// +0x48 = 2, +0x3C7); after the last point it turns to the +0x60 facing
// (within PI/10 it snaps and succeeds). The movement half is Zero Hour's
// AIFollowPathState::update with BFME 2's team wait (+0x56, rva00349E74), the
// retry count (+0x50), the step-back flag (+0x57), the skip-behind test of the
// next point, CritterDesync 47/48/35, and a failed AdjustDestination halving
// the way to the goal.
static inline Real angleBetween(Real a, Real b)
{
	return normalizeAngle(a - b);
}

StateReturnType AIFollowPathAsTeamState::update()
{
	StateReturnType status;
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getObservedAI();
	Bool resumed = false;
	if (m_5c)
	{
		Bool wasBusy = false;
		if (!m_5c->isInIdleState())
		{
			Object *goal = getObservedMachineGoalObject();
			if (goal && goal != m_5c->getGoalObject())
				m_5c->setGoalObject(goal);
			m_5c->updateStateMachine();
			if (!m_5c || !m_5c->isInIdleState())
				return STATE_CONTINUE;
			wasBusy = true;
			resumed = true;
			ai->m_48 = m_lastCommandSource;
		}
		if (m_5c->isInIdleState())
		{
			Object *crate = ai->checkForCrateToPickup();
			if (crate)
			{
				m_5c->setGoalObject(crate);
				m_5c->setState(AI_PICK_UP_CRATE);
				return STATE_CONTINUE;
			}
			Object *target = ai->getNextMoodTarget(!wasBusy, false);
			if (target)
			{
				ai->rva00262AEA();
				m_5c->setGoalObject(target);
				m_5c->setState(AI_ATTACK_OBJECT);
				ai->m_48 = 2;
				ai->m_3c7 = true;
				return STATE_CONTINUE;
			}
		}
	}

	getMachine()->setGoalPosition(&m_goalPosition);
	status = STATE_SUCCESS;
	if (m_64)
	{
		if (angleBetween(m_60, obj->getOrientation()) < 0.31415927f)
		{
			obj->setOrientation(m_60);
			return STATE_SUCCESS;
		}
		ai->slot135(m_60);
		return STATE_CONTINUE;
	}

	if (m_waitingForTeam)
	{
		if (((const unsigned char *)&obj->m_110)[3] & 0x20)
		{
			obj->m_110 &= ~0x20000000;
			obj->rva0028AE6D();
		}
	}
	else
	{
		status = AIInternalMoveToState::update();
		if (status == STATE_FAILURE)
		{
			if (m_retryCount > 0)
				m_retryCount--;
			else
				status = STATE_SUCCESS;
		}
		if (status != STATE_SUCCESS && status != STATE_FAILURE && !resumed)
			return status;
	}

	if (!m_waitingForTeam && status == STATE_SUCCESS)
	{
		if (m_57 && m_index > 0)
			m_index--;
		const Coord3D *pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
		_ReadWriteBarrier();
		if (pos)
		{
			Real speed = ((const Rva00340E5E *)this)->rva00340E5E();
			if (ai->isDoingGroundMovement())
				ai->setDesiredSpeed(speed);
			Real relative = obj->GetRelativeAngle(pos);
			Real turn = normalizeAngle(obj->getOrientation() + relative);
			ai->slot135(turn);
		}
		m_index++;
		ai->m_currentGoalPathIndex = m_index;
		_ReadWriteBarrier();
		m_waitingForTeam = pos != 0;
	}
	if (m_waitingForTeam && !canMoveToNextFormationPathPoint())
		return STATE_CONTINUE;

	m_waitingForTeam = false;
	m_57 = false;
	{
		Object *obj = getMachineOwner();
		AIUpdateInterface *ai = obj->getObservedAI();
		Real ownerX = obj->getPosition()->x;
		Real ownerY = obj->getPosition()->y;
		const Coord3D *pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index);
		Bool tooClose = true;
		while (pos && tooClose)
		{
			Real dx = pos->x - ownerX;
			Real dy = pos->y - ownerY;
			tooClose = false;
			if ((dx * dx + dy * dy) < PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
				tooClose = true;
			Real behindX = pos->x - ownerX;
			const Coord3D *nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
			if (nextPos && (nextPos->y - pos->y) * (pos->y - ownerY) + (nextPos->x - pos->x) * behindX < 0.0f)
				tooClose = true;
			if (tooClose)
			{
				m_index++;
				pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index);

			}
		}

		ai->rva00262FEB(0);
		if (pos == 0)
		{
			m_64 = true;
			ai->slot135(m_60);
			return STATE_CONTINUE;
		}

		ai->rva00262ACE();
		m_goalPosition = *pos;
		const Coord3D *nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
		if (nextPos)
		{
			Coord2D delta;
			delta.x = nextPos->x - pos->x;
			delta.y = nextPos->y - pos->y;
			Real offset = delta.length();
			const Coord3D *followingPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 2);
			if (followingPos)
				offset += 4 * PATHFIND_CELL_SIZE_F;
			ai->setPathExtraDistance(offset);
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 47");
			setAdjustsDestination(false);
		}
		else
		{
			ai->setPathExtraDistance(0.0f);
			if (g_00E03745 && theLogicRandomLogFile)
				fprintf(static_cast<FILE *>(theLogicRandomLogFile),
					"CritterDesync: setAdjustDestination(m_adjustFinal=%s && (m_adjustFinalOverride=%s || ai->isDoingGroundMovement()=%s) 48",
					m_adjustFinal ? "TRUE" : "FALSE", m_adjustFinalOverride ? "TRUE" : "FALSE",
					ai->isDoingGroundMovement() ? "TRUE" : "FALSE");
			setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ai->isDoingGroundMovement()));
			if (getAdjustsDestination())
			{
				Coord3D *goal = &m_goalPosition;
				if (!TheAI->pathfinder()->AdjustDestination(getMachineOwner(), *ai->getLocomotorSet(), goal, 0))
				{
					if (--m_retryCount > 0)
					{
						m_goalPosition.x += obj->getPosition()->x;
						goal->y += obj->getPosition()->y;
						goal->z += obj->getPosition()->z;
						_ReadWriteBarrier();
						goal->x *= 0.5f;
						goal->y *= 0.5f;
						goal->z *= 0.5f;
						m_57 = true;
					}
					else
						return STATE_FAILURE;
				}
				getMachineOwner()->rva0028ACDC((Int)goal);
			}
		}
	}
	critterDesyncLog("CritterDesync: ComputePath35");
	computePath();
	return STATE_CONTINUE;
}
