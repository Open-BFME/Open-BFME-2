// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// AIAttackApproachTargetState::onEnter, retail 0x0034CD3A (783 bytes): slot 4
// of vtable 0x00C12610 (slot-2 name getter "AIAttackApproachTargetState";
// slots 5/6 are the rowed onExit 0x0034894C and update 0x003488AF), with the
// AIStates.cpp helpers it calls:
//
//  - rva003430A3 0x003430A3 (123 bytes): the attack line-of-sight test. True
//    unless the owner's template has kind byte +0x10F mask 8 or byte +0x122
//    mask 0x40, the weapon's template is neither the +0x2C9400 byte-field
//    kind nor a contact weapon (pinned WeaponTemplate::isContactWeapon), and
//    the stack line-of-sight partition filter (vtable 0x00C07150, rowed
//    Rva002619C1Filter::allow) refuses the victim. Also called outside this
//    unit (0x0046C7A4), so it is external cdecl.
//  - rva00343FB0 0x00343FB0 (173 bytes): static, owner in ESI. False for an
//    immobile owner (kind byte +0x108 mask 4) or one whose outermost
//    container is; otherwise BFME1's rva0016B010 (contact/field weapon,
//    non-human player, no AI, state 0x3E, AI slot 143 != 2, AI byte +0x3C1,
//    owner byte +0x249). Not yet exact (forward pin in symbols.csv): retail
//    walks the containers with a retested loop (while (c && c->next)) yet
//    keeps the owner in ESI; every retested-loop shape tried here makes cl
//    choose EDI, which also moves onEnter's registers. The break-loop shape
//    below keeps the retail ESI convention (onEnter exact) but drops the
//    retest; bank reverse/attempts/0x00343fb0.cpp has the retail-shaped body.
//  - canPursue 0x00344635 (276 bytes): static, owner in ESI, victim in EDI,
//    weapon on the stack; Zero Hour's canPursue as BFME1 shaped it (status
//    0x26 with a container, crush test, weapon too-close test 0x002C9AFE,
//    locomotor speed 0x002627E8 against the victim's 0x0028AC7D).
//
// onEnter is Zero Hour's with BFME 2 target facts: the owner position is
// saved at +0x58; a destroyed goal fails; status 0x44 or AI byte +0x3CC
// takes a direct fire/fail exit through AI::rva002FE193 and the
// line-of-sight test (else the machine's slot 14 clears the goal); a victim
// rowed Rva0034311ECheck fails; the view-blocked test is rva003430A3;
// the guard-retaliate block is rva00343FB0; an AI module flag +0x24 with
// layer >= 17 and no quick path, or a non-moving owner (Object::rva002907A1,
// locomotor 0x001E46E1 speed < 0.1), waits two seconds (+0x68, flag +0x71).
// Donors: Zero Hour AIStates.cpp, BFME1 AIAttackApproachTargetState_onEnter.cpp.
//
// AIAttackApproachTargetState00C12678::onEnter 0x0034D049 (383 bytes, slot 4
// of vtable 0x00C12678): the same body for the BFME 2 position-approach
// variant -- no victim branch, the weapon range test against the machine's
// goal position, owner position at +0x4C, timestamp +0x58, wait frame +0x5C
// and wait flag +0x62; its computePath 0x00340546 (221 bytes, slot 17,
// ComputePath10/20) is the goal-position half of Zero Hour's with the waiting
// byte refreshed from the AI after requestAttackPath. The goal pointer is read
// before the timestamp store
// (retail keeps the negated frame rate in ECX across the argument pushes).
//
// AIAttackPursueTargetState (vtable 0x00C12730): onEnter 0x0034D345 (349
// bytes, slot 4) and computePath 0x00345246 (333 bytes, slot 17), Zero Hour's
// bodies with BFME 2's status 0x44 / AI byte +0x3CC direct exit (as in the
// approach onEnter), the AI slot 143 == 2 command-source test with owner byte
// +0x249, CritterDesync 27/13 and 12/26, the AI blocked-frames count +0x16C,
// path +0x140 and waiting byte +0x3B1, and the static isSamePosition and
// canPursue register helpers of this unit.
//
// AIAttackFireDuringApproachState (vtable 0x00C12798, BFME only; layout from
// the rowed xfer 0x0034081A): onEnter 0x0034D4A2 (277 bytes, CritterDesync
// 28/16/29) remembers the victim ID +0x64 and its position +0x50 and fails on
// the victim physics flag pair (pinned 0x00390533); computePath 0x00350497
// (468 bytes, ComputePath15) refinds the victim by ID, then asks the
// pathfinder's engagement-spot search (pinned 0x002F23A6) and
// requestApproachPath, with the 'masiwar' debug traces gated on TheGameLogic
// +0x1B4. The machine pointer is a local there (retail reuses it after
// findObjectByID).
//
// AIAttackMeleeSquishState (vtable 0x00C12868): onEnter 0x0034D886 (261
// bytes, CritterDesync 33/22) needs template byte +0x5FD, no status 0x44 or
// AI +0x3CC, a live goal without the physics flag pair and the owner's crush
// test (Object::rva0029493F, 2) before it paths, then sets status 0x1C. Its
// FAILURE and SUCCESS returns trail the body in that order, which only the
// nested form below reproduces.
//
// AIAttackMeleeEngageState::onEnter 0x0034DC05 (540 bytes, slot 4 of vtable
// 0x00C12150, CritterDesync 35/27/36): BFME1's AIAttackMeleeEngageState_onEnter
// donor with BFME 2's fields -- the private fire state (new, constructor
// 0x0033F483) at +0x4C, timestamp +0x54, victim position +0x58, retry frame
// +0x6C and flag +0x70, weapon slot +0x74; the victim fails on the physics
// flag pair, Object +0x438 bit 0 or status 0x32; in range, the owner's
// pathfinder goal (Object::rva0028ACEE, GetGoalPosition) is written to the AI
// final position +0x180 with byte +0x3B0 cleared and status 0x1C set.
//
// AIAttackPositionFireWeaponState (vtable 0x00C11258): onEnter 0x0034AEDF
// (238 bytes) and update 0x0034AFCD (189 bytes) -- Zero Hour's
// AIAttackFireWeaponState position path with BFME 2's status 0x52 clear,
// mood MM_Action_Attack gate, the moving-owner refusal, the status-0x26
// odd-frame wait (+0x24) replayed by update, and the attack state at +0x20
// (slot 2 isWeaponSlotOkToFire, slot 0 notifyFired); update's three early
// failures are separate statements in retail.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../Common/PartitionRangeQueryCallView.h"

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
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

static __forceinline void critterDesyncLog(const char *text)
{
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, text);
	}
}

extern "C" float __cdecl fabs(double); // CRT fabs (the /O1 call); x87 result compared as float
Real normalizeAngle(Real angle);

#define PATHFIND_CELL_SIZE_F 10.0f

extern int g_Va00DBA4E4;
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4

extern GameLogic *TheGameLogic;

class TAiData
{
public:
	unsigned char m_pad00[0x4C];
	Real m_alertRangeModifier; // +0x4C
	Real m_aggressiveRangeModifier; // +0x50
	unsigned char m_pad54[0x8C - 0x54];
	Bool m_aiCrushesInfantry; // +0x8C
	unsigned char m_pad8D[0x94 - 0x8D];
	Real m_94; // +0x94 (the squish retarget range)
};

class Rva002C9B80Owner;

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *obj, const Coord3D *objPos, const Object *target, const Coord3D *targetPos);
	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
	Bool QuickDoesPathExistToStructure(Object *obj, const Coord3D *fromPos, Object *structure, Int flag);
	Bool QuickDoesPathExist(Object *obj, const Coord3D *fromPos, const Coord3D *toPos, Int flag);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

// The SiegeDeploySpecialPower module's rowed bool getter (0x004C5772).
class Rva004C5772CmpBoolField
{
public:
	Bool get() const;
};

class PolygonTrigger;
class AttackPriorityInfo;
class PartitionFilter;

class AI
{
public:
	static Bool rva002FE193(Object *owner, Object *nemesis);
	Object *rva002FF8DD(const PolygonTrigger *area, Object *owner, const AttackPriorityInfo *info);
	Object *findClosestEnemy(const Object *me, Real range, UnsignedInt qualifiers, const AttackPriorityInfo *info, PartitionFilter *optionalFilter, Int extra);
	Pathfinder *pathfinder() { return m_pathfinder; }
	const TAiData *getAiData() { return m_aiData; }
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	unsigned char m_pad14[0x18 - 0x14];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

class Locomotor
{
public:
	enum LocoFlag
	{
		IS_BRAKING = 0,
		ALLOW_INVALID_POSITION,
		MAINTAIN_POS_IS_VALID,
		PRECISE_Z_POS
	};
	Real getMaxTurnRate(Object *obj) const;
	void setUsePreciseZPos(Bool b)
	{
		if (b)
			m_flags |= (1 << PRECISE_Z_POS);
		else
			m_flags &= ~(1 << PRECISE_Z_POS);
	}
private:
	unsigned char m_pad00[0x44];
	unsigned int m_flags; // +0x44
};

// Locomotor speed for an object (0x001E46E1), rowed under this name.
class Rva001E46E1
{
public:
	Real rva001E46E1(Object *obj);
};

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

class AIUpdateInterface : public AIApproachAISlots<136>
{
public:
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
	Bool computeQuickPath(const Coord3D *destination);
	Object *checkForCrateToPickup();
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	void requestAttackPath(ObjectID victimID, const Coord3D *victimPos);
	void destroyPath();
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void rva00262B0F(Int value);
	Bool isMoving() const;
	void requestApproachPath(Coord3D *destination);
	void *getPath() const { return m_path; }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	Bool isBlockedAndStuck() const { return m_blockedFrames > 0; }
	UnsignedInt getMoodMatrixValue() const;
	Bool isAttackPath() const { return m_3b2; }
	void setPathExtraDistance(Real dist);
private:
	const AIUpdateModuleData *m_moduleData; // +0x04
	unsigned char m_pad008[0x30 - 0x08];
public:
	class Rva00346FA5 *m_goalPath; // +0x30
private:
	unsigned char m_pad034[0x70 - 0x34];
public:
	const AttackPriorityInfo *m_attackInfo; // +0x70
private:
	unsigned char m_pad074[0x140 - 0x74];
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
	unsigned char m_kindOf[0x14]; // +0x108
	unsigned char m_pad11C[0x122 - 0x11C];
	unsigned char m_122; // +0x122
	unsigned char m_pad123[0x53C - 0x123];
	Real m_53c; // +0x53C
	unsigned char m_pad540[0x5FD - 0x540];
	Bool m_5fd; // +0x5FD
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const Coord3D *getUnitDirectionVector2D() const;
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class TeamPrototype
{
public:
	unsigned char m_pad00[0x216];
	Bool m_216; // +0x216
};

class Team
{
public:
	Object *getTeamTargetObject();
	void rva0039D84A(Object *target);
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};

class Player
{
public:
	unsigned char m_pad00[0x5C];
	Int m_playerType; // +0x5C
};

class Object : public Thing
{
public:
	// This retail view reads +0x258; the named Object::getAI provider reads +0x19C.
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
	Bool rva002907A1();
	Bool isSignificantlyAboveTerrain() const;
	Bool rva0029493F(Object *other, Int test);
	Real rva0028AC7D() const;
	Bool rva0028ADE0() const;
	const Rva0028AC4EEntry *rva0028AC4E() const;
	void rva0028CDB6();
	Real GetRelativeAngle(const Coord3D *pos) const;
	Real getOrientation() const { return m_orientation; }
	Bool rva002943B2(const Player *player);
	Bool isOutOfAmmo() const;
	Object *adjustVictim(Object *owner, bool useWeaponRange, Int index);
	void rva0028ACDC(const Coord3D *pos);
	void setStatus(ObjectStatusTypes bit, Bool set);
	Bool isKindOf(KindOfType t) const;
	void preFireCurrentWeapon(const Object *victim, const Coord3D *pos);
	void rva0028FC8F();
	void fireCurrentWeapon(const Coord3D *pos);
	void fireCurrentWeapon(Object *victim, Int goalID);
	Bool getWorldspaceBestContactPoint(Coord3D *result, const Coord3D *from, const char *boneName, Int a, Int b, Bool c) const;
	void rva0028ACEE(const Coord3D *pos, Int layer);
	Bool GetGoalPosition(Coord3D *pos) const;
	void *rva0029439D();
	friend class AIAttackMeleeHordeWaitPathState;
protected:
	Module *findModule(NameKeyType key) const;
public:
	ObjectID getID() const { return (ObjectID)m_id; }
	Real m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	Int m_id; // +0x74
	unsigned char m_pad078[0x94 - 0x78];
	UnsignedInt m_94; // +0x94 (bit 0: destroyed)
	unsigned char m_pad098[0xB8 - 0x98];
	Real m_geometryRadiusB8; // +0xB8
	unsigned char m_pad0BC[0x1C0 - 0xBC];
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
	unsigned char m_pad308[0x438 - 0x308];
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
	unsigned char m_pad34[0x148 - 0x34];
	Real m_continueAttackRange; // +0x148
	unsigned char m_pad14C[0x161 - 0x14C];
	Bool m_161; // +0x161 (keeps attacking a dead victim)
	unsigned char m_pad162[0x16B - 0x162];
	Bool m_16b; // +0x16B
	Bool is16b() const { return m_16b; }
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;
	char isWithinAttackRange(Object *source, void *pos, Real extra, Int flag) const;
	Bool rva002C9AFE(const Object *source, const void *target) const;
	WeaponStatus getStatus() const;
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};

class Rva002C9B80Owner
{
public:
	Bool isWithinAttackRange(Object *source, const Coord3D *sourcePos, Object *victim, const Coord3D *victimPos, Real extra, Bool flag);
};

// The line-of-sight partition filter (vtable 0x00C07150).
class Rva002619C1FilterBase
{
public:
	Rva002619C1FilterBase() : m_zero(0) {}
	Int m_zero;
};

class Rva002619C1Filter : public Rva002619C1FilterBase
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
struct StateIdView
{
	unsigned char m_pad00[0x04];
	UnsignedInt m_id; // +0x04
};

enum
{
	AI_IDLE = 0,
	AI_ATTACK_OBJECT = 10,
	AI_PICK_UP_CRATE = 0x27, // ZH's 40, one lower in BFME 2
	INVALID_STATE_ID = 999999
};

class StateMachine : public StateMachineSlots<4>
{
public:
	virtual StateReturnType updateStateMachine(); // slot 4
	virtual void slot05();
	virtual void slot06();
	virtual StateReturnType initDefaultState(); // slot 7
	virtual StateReturnType setState(UnsignedInt newStateID); // slot 8
	virtual StateMachine *slot09(); // returns a new attack sub-machine (AIAttackSquadState::onEnter)
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	UnsignedInt getCurrentStateID() const { return m_currentState ? m_currentState->m_id : INVALID_STATE_ID; }
	inline Bool isInAttackState() const;
	void setGoalPosition(const Coord3D *pos);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	StateIdView *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x20 - 0x18];
public:
	Int m_goalObjectID; // +0x20
private:
	Coord3D m_goalPosition; // +0x24
	unsigned char m_pad30[0x38 - 0x30];
public:
	Bool m_locked; // +0x38 (ZH lock()/unlock() without the debug owner string)
};

// StateMachine::isGoalObjectDestroyed (0x004D7ADD), rowed under this name.
class TurretStateMachine
{
public:
	Bool rva004D7ADD();
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
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
protected:
	virtual Bool computePath();
	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
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
	void *log = theLogicRandomLogFile;
	if (log != 0)
		fprintf(log, text);
}

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};

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
	StateReturnType rva0034D98B();
	UnsignedInt m_approachTimestamp; // +0x4C
	Coord3D m_prevVictimPos; // +0x50
	Int m_cellX; // +0x5C
	Int m_cellY; // +0x60
	Bool m_64; // +0x64
};

// AIAttackFireWeaponState, vtable 0x00C111F8.
class AttackStateHost;
class AIAttackFireWeaponState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	AttackStateHost *m_att; // +0x20
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
};

class Rva0034E3A5Helper
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void rva0034E3CESlot5();
	virtual void s06(); virtual void s07();
	virtual void rva0034E3D8Slot8(Int value);
};

// AIFollowPathAsTeamState, vtable 0x00C121E8.
class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	virtual Bool computePath();
private:
	Int m_index; // +0x4C
	unsigned char m_pad50[0x54 - 0x50];
	Bool m_adjustFinal; // +0x54
	unsigned char m_pad55[0x57 - 0x55];
	Bool m_57; // +0x57
	Int m_lastCommandSource; // +0x58
	Rva0034E3A5Helper *m_5c; // +0x5C
	Int m_60; // +0x60
	Bool m_64; // +0x64
};

// AIAttackPositionAimAtTargetState, vtable 0x00C11068.
class AIAttackPositionAimAtTargetState : public State
{
public:
	virtual StateReturnType onEnter();
	StateReturnType rva0034A570(Bool firstFrame);
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
	virtual void notifyNewVictimChosen(Object *victim);
	virtual Bool isWeaponSlotOkToFire(WeaponSlotType wslot);
	virtual Bool isAttackingObject() const;
	virtual const Coord3D *getOriginalVictimPos() const;
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

// AIAttackAreaState, vtable 0x00C11900 (isAttack 0x003422EF rowed in
// AIAttackStatesIsAttack.cpp, onExit 0x0034234C in AIStatesMoreExits.cpp).
class AIAttackAreaState : public State
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_attackMachine; // +0x20
	UnsignedInt m_nextEnemyScanTime; // +0x24
};

// AIAttackMeleeHordeWaitPathState, vtable 0x00C10FA0 (xfer 0x0034074C rowed
// in AIStatesXfer.cpp with the same +0x20/+0x24 members).
class AIAttackMeleeHordeWaitPathState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_waitUntilFrame; // +0x20
	Int m_bfmeValue24; // +0x24
};

// AIAttackSquadState, vtable 0x00C112C0 (name 0x0033F517, xfer 0x003414F6,
// onEnter 0x00351951, onExit 0x00341557).
class AIAttackSquadState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	Object *chooseVictim();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	StateMachine *m_attackSquadMachine; // +0x20
	Bool m_sawStatus1C; // +0x24
};

// The melee engage state's private fire state (constructor 0x0033F483).
class Rva0033F483
{
public:
	Rva0033F483(StateMachine *machine, Int weaponSlot);
	unsigned char m_pad00[0x28];
};

// AIAttackMeleeEngageState, vtable 0x00C12150 (computePath 0x003457AC rowed in
// AIStatesBfmeComputePath.cpp).
class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
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

// Retail 0033F9FE..0033FA64: position half of the line-of-sight guard.
// Native calls establish Object / Coord3D / Weapon roles; filter shape reused
// from the independently matched object-target guard below, not a donor name.
class Rva0026163A
{
public:
 Bool rva0026163A(const Coord3D *target);
};

Bool rva0033F9FE(Object *source, const Coord3D *target, Weapon *weapon)
{
 if (weapon && target && !((const Rva002C9400ByteField *)weapon->getTemplate())->get() &&
     !weapon->getTemplate()->isContactWeapon())
 {
  Rva002619C1Filter filter(source);
  if (!((Rva0026163A *)&filter)->rva0026163A(target))
   return false;
 }
 return true;
}

Bool rva003430A3(Object *source, Object *victim, Weapon *weapon)
{
	if (weapon && victim && !((const Rva002C9400ByteField *)weapon->getTemplate())->get() &&
		!weapon->getTemplate()->isContactWeapon() &&
		((source->getTemplate()->m_kindOf[7] & 8) || (source->getTemplate()->m_122 & 0x40)))
	{
		Rva002619C1Filter filter(source);
		if (!filter.allow(victim))
			return false;
	}
	return true;
}

// ?rva00343FB0@@YA_NPAVObject@@@Z present-unmatched
static Bool rva00343FB0(Object *obj)
{
	if (obj->isKindOfImmobile())
		return false;
	Object *container = obj->getContainedBy();
	while (container)
	{
		Object *outer = container->getContainedBy();
		if (!outer)
			break;
		container = outer;
	}
	if (container && container->isKindOfImmobile())
		return false;

	Weapon *weapon = obj->getCurrentWeapon();
	if (weapon && (((const Rva002C9400ByteField *)weapon->getTemplate())->get() ||
			((const Rva002C9407ByteField *)weapon->getTemplate())->get()))
		return true;
	if (obj->getControllingPlayer()->m_playerType)
		return true;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return true;
	if (ai->rva00260DED() == 0x3e || ai->slot143() != 2 || ai->m_3c1 || obj->m_249)
		return true;
	return false;
}

// Rowed at 0x0033FA8E from AIAttackApproachTargetState_computePath_Bfme.cpp;
// VC7.1 passes its three pointers in registers, so callers only match with a
// definition in the same unit.
static __declspec(noinline) Bool isSamePosition(const Coord3D *ourPos,
	const Coord3D *prevTargetPos, const Coord3D *curTargetPos)
{
	Coord3D diff;
	diff.x = curTargetPos->x - prevTargetPos->x;
	diff.y = curTargetPos->y - prevTargetPos->y;
	Coord3D toTarget;
	toTarget.x = curTargetPos->x - ourPos->x;
	toTarget.y = curTargetPos->y - ourPos->y;
	const float TOLERANCE_FACTOR = 1.0f / (10.0f * 10.0f);
	float toleranceSqr = (toTarget.x*toTarget.x+toTarget.y*toTarget.y) * TOLERANCE_FACTOR;
	if (diff.x * diff.x + diff.y * diff.y > toleranceSqr)
		return false;
	return true;
}

static Bool canPursue(Object *source, Weapon *weapon, Object *victim)
{
	if (!victim->m_physics)
		return false;
	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return false;
	AIUpdateInterface *ai = source->getObservedAI();
	if (!ai)
		return false;

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return false;

	if (TheAI->m_aiData->m_aiCrushesInfantry)
	{
		if (source->getControllingPlayer() &&
			source->getControllingPlayer()->m_playerType == 1 &&
			source->rva0029493F(victim, 2))
		{
			return true;
		}
	}

	if (weapon->rva002C9AFE(source, victim))
		return false;

	Real ourMaxSpeed = source->getObservedAI()->getCurLocomotorSpeed();
	Real victimSpeed = victim->rva0028AC7D();
	if (victimSpeed >= ourMaxSpeed)
		return false;
	if (victimSpeed < ourMaxSpeed * 0.1f)
		return false;
	Real dx = victim->getPosition()->x - source->getPosition()->x;
	Real dy = victim->getPosition()->y - source->getPosition()->y;
	const Coord3D *victimDirection = victim->getUnitDirectionVector2D();
	Coord3D victimDirectionVector;
	victimDirectionVector.x = victimDirection->x;
	victimDirectionVector.y = victimDirection->y;
	if (dx * victimDirectionVector.x + dy * victimDirectionVector.y < 0)
		return false;
	return true;
}

StateReturnType AIAttackApproachTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getObservedAI();
	if (source->isKindOfProjectile())
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	m_ownerPosition = *source->getPosition();

	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_FAILURE;

	m_waiting = false;
	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();

	if (source->testStatus(OBJECT_STATUS_44) || ai->m_3cc)
	{
		if (weapon && victim && AI::rva002FE193(source, victim) &&
			rva003430A3(source, victim, weapon))
			return STATE_SUCCESS;
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	m_prevVictimPos.x = 0.0f;
	m_prevVictimPos.y = 0.0f;
	m_prevVictimPos.z = 0.0f;
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;

	if (victim)
	{
		if (!weapon)
			return STATE_FAILURE;
		if (Rva0034311ECheck(victim))
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
		{
			Bool viewBlocked = false;
			if (ai->isDoingGroundMovement() && !victim->isSignificantlyAboveTerrain())
				viewBlocked = !rva003430A3(source, victim, weapon);
			if (!viewBlocked)
				return STATE_SUCCESS;
		}
		if (!rva00343FB0(source))
			return STATE_FAILURE;
		if (canPursue(source, weapon, victim))
			return STATE_SUCCESS;
		if (ai->getAIUpdateModuleData()->m_24 && source->rva0028B511() >= 17 &&
			!ai->isQuickPathAvailable(victim->getPosition()))
		{
			m_waiting = true;
			m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
			return STATE_CONTINUE;
		}
	}
	else
	{
		if (!weapon || !weapon->getTemplate()->m_16b)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange(source, (void *)getMachineGoalPosition(), 0.0f, 1))
			return STATE_SUCCESS;
		if (!rva00343FB0(source))
			return STATE_FAILURE;
	}

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->rva002907A1())
		mobile = false;
	if (((Rva001E46E1 *)ai->getCurLocomotor())->rva001E46E1(source) < 0.1f)
		mobile = false;
	if (!mobile)
	{
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			ai->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			ai->setTurretTargetPosition(tur, getMachineGoalPosition());
	}

	if (computePath() == false)
		return STATE_FAILURE;
	if (m_waiting)
		return STATE_CONTINUE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackApproachTargetState00C12678::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getObservedAI();
	if (source->isKindOfProjectile())
	{
		if (ai->getCurLocomotor())
			ai->getCurLocomotor()->setUsePreciseZPos(true);
	}

	m_ownerPosition = *source->getPosition();
	m_waiting = false;
	Weapon *weapon = source->getCurrentWeapon();
	const Coord3D *goalPos = getMachineGoalPosition();
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;
	if (weapon->isWithinAttackRange(source, (void *)goalPos, 0.0f, 1))
		return STATE_SUCCESS;
	if (!rva00343FB0(source))
		return STATE_FAILURE;

	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
		return STATE_FAILURE;

	Bool mobile = true;
	if (!source->rva002907A1())
		mobile = false;
	if (((Rva001E46E1 *)ai->getCurLocomotor())->rva001E46E1(source) < 0.1f)
		mobile = false;
	if (!mobile)
	{
		m_waiting = true;
		m_waitFrame = TheGameLogic->getFrame() + 2 * LOGICFRAMES_PER_SECOND;
		return STATE_CONTINUE;
	}

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
		ai->setTurretTargetPosition(tur, getMachineGoalPosition());

	if (computePath() == false)
		return STATE_FAILURE;
	if (m_waiting)
		return STATE_CONTINUE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 21");
	setAdjustsDestination(false);
	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 22");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackPursueTargetState::onEnter()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getObservedAI();
	if (source->isKindOfProjectile())
		return STATE_SUCCESS;
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;
	if (!m_isAttackingObject)
		return STATE_SUCCESS;

	if (source->testStatus(OBJECT_STATUS_44) || ai->m_3cc)
	{
		if (AI::rva002FE193(source, getMachineGoalObject()))
			return STATE_SUCCESS;
		getMachine()->setGoalObject(0);
		return STATE_FAILURE;
	}

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 27");
	setAdjustsDestination(false);
	if (source->getControllingPlayer()->m_playerType == 0)
	{
		if (ai->slot143() == 2 && !source->m_249)
			return STATE_SUCCESS;
	}

	m_prevVictimPos.x = 0.0f;
	m_prevVictimPos.y = 0.0f;
	m_prevVictimPos.z = 0.0f;
	m_approachTimestamp = -LOGICFRAMES_PER_SECOND;

	Object *victim = getMachineGoalObject();
	if (!victim)
		return STATE_SUCCESS;
	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (!canPursue(source, weapon, victim))
		return STATE_SUCCESS;

	WhichTurretType tur = ai->getWhichTurretForCurWeapon();
	if (tur == TURRET_INVALID)
		return STATE_SUCCESS;
	ai->setTurretTargetObject(tur, victim, m_isForceAttacking);

	critterDesyncLog("CritterDesync: ComputePath13");
	if (computePath() == false)
		return STATE_SUCCESS;
	return AIInternalMoveToState::onEnter();
}

Bool AIAttackPursueTargetState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath12");
	Bool forceRepath = false;
	if (getMachineOwner()->rva002907A1() == false)
		return false;
	AIUpdateInterface *ai = getMachineOwner()->getObservedAI();
	if (ai->isBlockedAndStuck())
		return false;
	if (m_waitingForPath)
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	if (getMachineGoalObject())
	{
		Object *source = getMachineOwner();
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos,
				getMachineGoalObject()->getPosition()))
			return true;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;
		if (!canPursue(source, weapon, getMachineGoalObject()))
			return false;
		Object *victim = getMachineGoalObject();
		m_prevVictimPos = *victim->getPosition();
		critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 26");
		setAdjustsDestination(true);
		m_goalPosition = m_prevVictimPos;
		ai->requestPath(&m_goalPosition, false);
		m_waitingForPath = ai->isWaitingForPath();
		m_stopIfInRange = false;
		return true;
	}
	return false;
}

Bool AIAttackApproachTargetState00C12678::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath10");
	Bool forceRepath = false;
	if (getMachineOwner()->rva002907A1() == false)
		return false;
	AIUpdateInterface *ai = getMachineOwner()->getObservedAI();
	if (m_waitingForPath)
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 20");
	setAdjustsDestination(true);
	m_stopIfInRange = false;
	m_goalPosition = *getMachineGoalPosition();
	if (!forceRepath)
		return true;
	ai->requestAttackPath(INVALID_OBJECT_ID, &m_goalPosition);
	m_waitingForPath = ai->isWaitingForPath();
	return true;
}

StateReturnType AIAttackFireDuringApproachState::onEnter()
{
	Object *source = getMachineOwner();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_FAILURE;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 28");
	setAdjustsDestination(false);
	m_approachTimestamp = 0;
	Object *victim = getMachineGoalObject();
	if (victim)
	{
		m_victimID = victim->getID();
		if (victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533())
			return STATE_FAILURE;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return STATE_FAILURE;
		if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
			return STATE_SUCCESS;

		m_prevVictimPos = *victim->getPosition();
		source->m_ai->destroyPath();
		critterDesyncLog("CritterDesync: ComputePath16");
		if (computePath() == false)
			return STATE_SUCCESS;
		StateReturnType ret = AIInternalMoveToState::onEnter();
		critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 29");
		setAdjustsDestination(true);
		return ret;
	}
	return STATE_FAILURE;
}

Bool AIAttackFireDuringApproachState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath15");
	Bool forceRepath = false;
	StateMachine *machine = getMachine();
	AIUpdateInterface *ai = machine->getOwner()->getObservedAI();
	if (ai->isBlockedAndStuck())
		return false;
	if (m_waitingForPath && ai->isWaitingForPath())
		return true;
	if (!forceRepath && ai->getPath() == 0 && !ai->isWaitingForPath())
		forceRepath = true;
	if (!forceRepath && TheGameLogic->getFrame() - m_approachTimestamp < (UnsignedInt)LOGICFRAMES_PER_SECOND)
		return true;
	m_approachTimestamp = TheGameLogic->getFrame();

	Object *victim = TheGameLogic->findObjectByID(m_victimID);
	if (victim)
	{
		Object *source = machine->getOwner();
		if (!forceRepath && isSamePosition(source->getPosition(), &m_prevVictimPos, victim->getPosition()))
			return true;
		Weapon *weapon = source->getCurrentWeapon();
		if (!weapon)
			return false;
		m_prevVictimPos = *victim->getPosition();
		if (gameLogicDebugLevel() > 0 && !forceRepath)
			debugTrace("masiwar called by AIAttackFireDuringApproachState::computePath [1]");
		if (!forceRepath && ((Rva002C9B80Owner *)weapon)->isWithinAttackRange(source, &m_goalPosition,
				victim, &m_prevVictimPos, 0.0f, true))
			return true;
		m_goalPosition = m_prevVictimPos;
		if (gameLogicDebugLevel() > 0)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "AIAttackFireDuringApproachState::computePath will call FindMeleeEngagmentLocation with m_goalPosition=%f,%f",
					(double)m_goalPosition.x, (double)m_goalPosition.y);
		}
		((Rva002F23A6 *)TheAI->pathfinder())->rva002F23A6(source, (int)weapon,
			(int)&ai->m_locomotorSet, &m_goalPosition, victim);
		source->rva0028ACDC(&m_goalPosition);
		ai->requestApproachPath(&m_goalPosition);
		m_waitingForPath = ai->isWaitingForPath();
		return true;
	}
	return false;
}

StateReturnType AIAttackMeleeSquishState::onEnter()
{
	StateMachine *machine = getMachine();
	Object *source = machine->getOwner();
	if (!source->testStatus(OBJECT_STATUS_44) && !source->m_ai->m_3cc && source->getTemplate()->m_5fd)
	{
		if (!((TurretStateMachine *)machine)->rva004D7ADD())
		{
			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 33");
			setAdjustsDestination(false);
			m_approachTimestamp = 0;
			Object *victim = getMachineGoalObject();
			if (victim && !(victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()))
			{
				if (!source->rva0029493F(victim, 2))
					return STATE_SUCCESS;
				m_prevVictimPos = *victim->getPosition();
				source->m_ai->destroyPath();
				critterDesyncLog("CritterDesync: ComputePath22");
				if (computePath() == false)
					return STATE_SUCCESS;
				source->setStatus(OBJECT_STATUS_1C, true);
				return AIInternalMoveToState::onEnter();
			}
		}
		return STATE_FAILURE;
	}
	return STATE_SUCCESS;
}

// Thing-template gate 0x0028CECF (pinned under this name).
class Rva0028CECFOwner
{
public:
	Bool rva0028CECF();
};

// The owner's contain module (+0x250) slot 31 and the object it returns,
// whose slot 85 says whether the victim may be squished from inside.
class SquishRiderView : public VirtualSlots<85>
{
public:
	virtual Bool slot85(Object *victim);
};

class SquishContainView : public VirtualSlots<31>
{
public:
	virtual SquishRiderView *slot31();
};

// Retail 0x0034D98B, 629 bytes: the body of AIAttackMeleeSquishState's slot 6
// (0x0034DC00 is a 5-byte jump here). Path extra distance 50 while chasing;
// a contained owner whose rider accepts the victim stops (AI slot 136). A gone
// or dead victim (status 0x32, Object +0x438 bit 0) lets an armed squisher
// (+0x64) retarget the closest enemy in TAiData +0x94 it can crush
// (CritterDesync 23); otherwise the crush test, status 0x33 / stealth gates
// and CritterDesync 24/25 path to the victim, chasing its position when the
// template has kind byte +0x11A bit 7. Status 0x1C mirrors 0x0028CECF.
// Codegen: the retarget branch comes first in source; cl sinks that
// return-terminated then-block to the end of the function, and the merged
// FAILURE / SUCCESS blocks stay at their last source occurrence (the
// ComputePath24 test and the rider stop), as retail lays them out. The named
// Bool for the 0x1C status is what keeps retail's EBP frame.
StateReturnType AIAttackMeleeSquishState::rva0034D98B()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getObservedAI();
	ai->setPathExtraDistance(50.0f);
	Object *victim = getMachineGoalObject();
	if (obj->m_contain && !((Rva0028CECFOwner *)obj)->rva0028CECF())
	{
		SquishRiderView *rider = ((SquishContainView *)obj->m_contain)->slot31();
		if (rider && rider->slot85(victim))
		{
			ai->slot136();
			return STATE_SUCCESS;
		}
	}

	if (((TurretStateMachine *)getMachine())->rva004D7ADD() ||
		(victim && ((victim->m_438 & 1) || victim->testStatus(OBJECT_STATUS_32))))
	{
		ai->setPathExtraDistance(0.0f);
		if (m_64 && ((Rva0028CECFOwner *)obj)->rva0028CECF())
		{
			m_64 = false;
			const AttackPriorityInfo *info = ai->m_attackInfo;
			Object *enemy = TheAI->findClosestEnemy(obj, TheAI->getAiData()->m_94, 2, info, 0, 0);
			if (enemy && obj->rva0029493F(enemy, 2))
			{
				getMachine()->setGoalObject(enemy);
				critterDesyncLog("CritterDesync: ComputePath23");
				if (!computePath())
					return STATE_FAILURE;
				m_64 = true;
			}
		}
		return AIInternalMoveToState::update();
	}

	StateReturnType status = STATE_FAILURE;
	if (victim)
	{
		if (!obj->rva0029493F(victim, 2))
			return STATE_SUCCESS;
		if (victim->testStatus(OBJECT_STATUS_33) || victim->rva002943B2(obj->getControllingPlayer()))
			return STATE_FAILURE;
		ai->setCurrentVictim(victim);
		critterDesyncLog("CritterDesync: ComputePath24");
		if (!computePath())
			return STATE_FAILURE;
		status = AIInternalMoveToState::update();
		if (status != STATE_CONTINUE)
		{
			if (victim->m_438 & 1)
				return STATE_SUCCESS;
			if (!(obj->getTemplate()->m_kindOf[0x12] & 0x80))
				return STATE_SUCCESS;
			m_goalPosition = *victim->getPosition();
			obj->getObservedAI()->destroyPath();
			critterDesyncLog("CritterDesync: ComputePath25");
			if (computePath())
			{
				obj->setStatus(OBJECT_STATUS_1C, true);
				return AIInternalMoveToState::onEnter();
			}
			return STATE_SUCCESS;
		}
	}
	Bool squishing = ((Rva0028CECFOwner *)obj)->rva0028CECF();
	obj->setStatus(OBJECT_STATUS_1C, squishing);
	return status;
}

StateReturnType AIAttackMeleeEngageState::onEnter()
{
	Object *source = getMachineOwner();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;

	if (!m_fireState)
		m_fireState = new Rva0033F483(getMachine(), m_weaponSlot);
	m_50 = -1;

	critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 35");
	setAdjustsDestination(false);
	m_approachTimestamp = 0;
	m_retryPending = false;
	m_retryFrame = 0;

	AIUpdateInterface *ai = source->m_ai;
	Object *victim = getMachineGoalObject();
	if (!victim || (victim->m_physics && ((Rva00390533 *)victim->m_physics)->rva00390533()) ||
		(victim->m_438 & 1) || victim->testStatus(OBJECT_STATUS_32))
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;

	if (weapon->isWithinAttackRange((const Object *)source, victim, 0.0f, 1))
	{
		Coord3D pos;
		pos.x = source->getPosition()->x;
		pos.y = source->getPosition()->y;
		pos.z = source->getPosition()->z;
		source->rva0028ACEE(&pos, source->rva0028B511());
		if (source->GetGoalPosition(&pos))
		{
			ai->m_finalPosition = pos;
			ai->m_3b0 = false;
		}
		source->setStatus(OBJECT_STATUS_1C, true);
		return STATE_SUCCESS;
	}

	m_prevVictimPos = *victim->getPosition();
	if (source->testStatus(OBJECT_STATUS_26) && source->m_containedBy)
	{
		source->setStatus(OBJECT_STATUS_1C, false);
		return STATE_FAILURE;
	}

	ai->destroyPath();
	critterDesyncLog("CritterDesync: ComputePath27");
	if (computePath() == false)
		return STATE_FAILURE;
	if (m_retryPending)
		return STATE_CONTINUE;

	StateReturnType ret = AIInternalMoveToState::onEnter();
	critterDesyncLog("CritterDesync: setAdjustDestination(TRUE) 36");
	setAdjustsDestination(true);
	return ret;
}

StateReturnType AIAttackPositionFireWeaponState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getObservedAI();
	m_waitOddFrame = false;
	obj->setStatus(OBJECT_STATUS_52, false);
	if ((ai->getMoodMatrixActionAdjustment(MM_Action_Attack) & 1) == 0)
		return STATE_FAILURE;

	Weapon *weapon = obj->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (!obj->isKindOfImmobile() && !((const Rva002C940EByteField *)weapon->getTemplate())->get() &&
		!((const Rva002C9400ByteField *)weapon->getTemplate())->get() && ai->isMoving())
		return STATE_FAILURE;
	if (!weapon->isWithinAttackRange(obj, (void *)getMachineGoalPosition(), 0.0f, 1))
		return STATE_FAILURE;

	if (weapon->getStatus() != READY_TO_FIRE)
		return STATE_SUCCESS;
	if (obj->testStatus(OBJECT_STATUS_26) && (TheGameLogic->getFrame() & 1))
	{
		m_waitOddFrame = true;
		return STATE_CONTINUE;
	}
	obj->setStatus(OBJECT_STATUS_0D, true);
	obj->preFireCurrentWeapon(getMachineGoalObject(), getMachineGoalPosition());
	return STATE_CONTINUE;
}

StateReturnType AIAttackPositionFireWeaponState::update()
{
	Object *obj = getMachineOwner();
	WeaponSlotType wslot;
	Weapon *weapon = obj->getCurrentWeapon(&wslot);
	if (!weapon)
		return STATE_FAILURE;
	if (obj->m_438 & 1)
		return STATE_FAILURE;
	if (obj->testStatus(OBJECT_STATUS_52))
		return STATE_FAILURE;
	if (m_waitOddFrame)
	{
		m_waitOddFrame = false;
		obj->setStatus(OBJECT_STATUS_0D, true);
		obj->preFireCurrentWeapon(getMachineGoalObject(), getMachineGoalPosition());
		return STATE_CONTINUE;
	}
	WeaponStatus status = weapon->getStatus();
	if (status == PRE_ATTACK)
		return STATE_CONTINUE;
	if (status != READY_TO_FIRE)
		return STATE_FAILURE;
	if (m_att && !m_att->isWeaponSlotOkToFire(wslot))
		return STATE_FAILURE;
	obj->rva0028FC8F();
	obj->fireCurrentWeapon(getMachineGoalPosition());
	obj->setStatus(OBJECT_STATUS_1B, false);
	m_att->notifyFired();
	return STATE_SUCCESS;
}

// Retail 0x00351951, 162 bytes: slot 4 of the same vtable. ZH builds the
// sub-machine with newInstance(AIAttackThenIdleStateMachine); BFME 2 asks the
// owning machine for it (slot 9), then gates the chosen victim as update does.
StateReturnType AIAttackSquadState::onEnter()
{
	Object *owner = getMachineOwner();
	if (!owner)
		return STATE_FAILURE;

	m_attackSquadMachine = getMachine()->slot09();
	AIUpdateInterface *ai = owner->getObservedAI();
	Object *victim = chooseVictim();
	Weapon *weapon = owner->getCurrentWeapon();
	if (weapon && victim && !weapon->isWithinAttackRange((const Object *)owner, victim, 0.0f, 1) &&
		(!rva00343FB0(owner) || ai->m_3cc))
		return STATE_FAILURE;

	m_attackSquadMachine->setGoalObject(victim);
	if (ai)
	{
		ai->setCurrentVictim(victim);
		getMachine()->setGoalObject(victim);
		ai->rva00262B0F((Int)victim);
	}
	m_sawStatus1C = false;
	return m_attackSquadMachine->initDefaultState();
}

// Retail 0x003519F3, 466 bytes: slot 6 of vtable 0x00C112C0, whose name slot
// 0x0033F517 returns "AIAttackSquadState". ZH AIStates.cpp's update gives the
// skeleton (sub-machine update, sleep folded to CONTINUE, AI_IDLE check, crate
// pickup, chooseVictim); BFME 2 adds the status 0x1C latch, the goal sync,
// the approach/range gates and the same-player release.
StateReturnType AIAttackSquadState::update()
{
	if (!m_attackSquadMachine)
		return STATE_FAILURE;

	StateMachine *machine = getMachine();
	if (machine->getOwner()->testStatus(OBJECT_STATUS_1C))
		m_sawStatus1C = true;
	Object *owner = machine->getOwner();
	AIUpdateInterface *ai = owner->getObservedAI();
	Object *goal = machine->getGoalObject();
	if (goal != m_attackSquadMachine->getGoalObject())
		m_attackSquadMachine->setGoalObject(goal);

	StateReturnType status = m_attackSquadMachine->updateStateMachine();
	if (status > STATE_CONTINUE)
		status = STATE_CONTINUE;
	if (!m_attackSquadMachine)
		return STATE_CONTINUE;
	if (m_attackSquadMachine->getCurrentStateID() != AI_IDLE)
		return status;

	Weapon *weapon = owner->getCurrentWeapon();
	if (!weapon)
		return STATE_FAILURE;
	if (goal && !(goal->m_438 & 1) &&
		!TheAI->pathfinder()->CanApproachToTarget(owner, goal->getPosition(), (Rva002C9B80Owner *)weapon, false))
		return STATE_FAILURE;

	if (owner->testStatus(OBJECT_STATUS_26) && owner->m_containedBy)
		return STATE_SUCCESS;

	Object *crate = ai->checkForCrateToPickup();
	if (crate)
	{
		m_attackSquadMachine->setGoalObject(crate);
		m_attackSquadMachine->setState(AI_PICK_UP_CRATE);
		return STATE_CONTINUE;
	}

	Object *victim = chooseVictim();
	if (!victim)
		return STATE_SUCCESS;
	if (!owner->testStatus(OBJECT_STATUS_41))
	{
		const ThingTemplate *tmpl = victim->getTemplate();
		if (!(tmpl->m_kindOf[0x06] & 0x80) && !(tmpl->m_kindOf[0x13] & 0x08) && !(tmpl->m_kindOf[0x0B] & 0x40) &&
			victim->getControllingPlayer() == owner->getControllingPlayer())
		{
			ai->rva00262B0F(0);
			getMachine()->setGoalObject(0);
			m_attackSquadMachine->setGoalObject(0);
			return STATE_SUCCESS;
		}
	}

	if (!weapon->isWithinAttackRange((const Object *)owner, victim, 0.0f, 1) && (!rva00343FB0(owner) || ai->m_3cc))
		return STATE_FAILURE;

	m_attackSquadMachine->setGoalObject(victim);
	ai->setCurrentVictim(victim);
	getMachine()->setGoalObject(victim);
	ai->rva00262B0F((Int)victim);
	m_attackSquadMachine->setState(AI_ATTACK_OBJECT);
	return STATE_CONTINUE;
}

// Retail 0x003450DB, 300 bytes: slot 6 of 0x00C10FA0. Succeeds when the goal
// is gone; until the wait frame passes it continues. A structure goal asks
// the pathfinder's QuickDoesPathExistToStructure; a goal of kind bit 93 with
// an active SiegeDeploySpecialPower module counts as reachable. Reachable (or
// a quick path to its position) fails the wait; otherwise wait one second and
// two frames more and succeed after the sixth retry.
StateReturnType AIAttackMeleeHordeWaitPathState::update()
{
	Object *owner = getMachineOwner();
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;
	Object *goal = getMachineGoalObject();
	if (!goal)
		return STATE_SUCCESS;
	if (m_waitUntilFrame > TheGameLogic->getFrame())
		return STATE_CONTINUE;

	Bool reachable = false;
	if (goal->getTemplate()->m_kindOf[0] & 0x80)
		reachable = TheAI->pathfinder()->QuickDoesPathExistToStructure(owner, owner->getPosition(), goal, 0);
	if (goal->getTemplate()->m_kindOf[11] & 0x20)
	{
		static NameKeyType siegeKey = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
		Module *mod = goal->findModule(siegeKey);
		if (mod && ((Rva004C5772CmpBoolField *)mod)->get())
			reachable = true;
	}
	if (!reachable && TheAI->pathfinder()->QuickDoesPathExist(owner, owner->getPosition(), goal->getPosition(), 0))
		reachable = true;
	if (reachable)
		return STATE_FAILURE;

	m_waitUntilFrame = TheGameLogic->getFrame() + LOGICFRAMES_PER_SECOND + 2;
	++m_bfmeValue24;
	return m_bfmeValue24 > 5 ? STATE_SUCCESS : STATE_CONTINUE;
}

// AI slot 121, the area to guard (ZH AIUpdateInterface::getAreaToGuard).
class AIAreaGuardView : public VirtualSlots<121>
{
public:
	virtual const PolygonTrigger *getAreaToGuard() const;
};

// Retail 0x0034680D, 232 bytes: slot 6 of 0x00C11900. ZH
// AIAttackAreaState::update with the scan rate LOGICFRAMES_PER_SECOND, the
// enemy search as AI 0x002FF8DD (area, owner, the AI's +0x70 attack info),
// the pinned Object::adjustVictim for victims with template kind bit
// +0x115/0x20, and the machine lock written as its +0x38 byte.
StateReturnType AIAttackAreaState::update()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now >= m_nextEnemyScanTime)
	{
		Object *owner = getMachineOwner();
		if (owner->isOutOfAmmo() && !owner->isKindOfProjectile())
			return STATE_FAILURE;
		m_nextEnemyScanTime = now + LOGICFRAMES_PER_SECOND;
		AIUpdateInterface *ai = owner->getObservedAI();
		if (((AIAreaGuardView *)ai)->getAreaToGuard() == 0)
			return STATE_FAILURE;
		Object *victim = TheAI->rva002FF8DD(((AIAreaGuardView *)ai)->getAreaToGuard(), owner, ai->m_attackInfo);
		if (victim && (victim->getTemplate()->m_kindOf[0x0D] & 0x20))
			victim = victim->adjustVictim(owner, 1, 0);
		m_attackMachine->setGoalObject(victim);
		if (m_attackMachine->getCurrentStateID() == AI_IDLE && victim)
			m_attackMachine->setState(AI_ATTACK_OBJECT);
		if (!victim)
			return STATE_SUCCESS;
	}
	getMachine()->m_locked = true;
	StateReturnType status = m_attackMachine->updateStateMachine();
	if (status > STATE_CONTINUE)
		status = STATE_CONTINUE;
	getMachine()->m_locked = false;
	return status;
}

// ZH Region3D, for the terrain extent test below.
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
	Bool isInRegionNoZ(const Coord3D *query) const
	{
		return (lo.x < query->x) && (query->x < hi.x) && (lo.y < query->y) && (query->y < hi.y);
	}
};

// TheTerrainLogic's slot 8, ZH TerrainLogic::getExtent.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class TerrainLogicExtentView : public VirtualSlots<8>
{
public:
	virtual void getExtent(Region3D *extent) const;
};

// Retail 0x00345BCF, 220 bytes: slot 17 of AIFollowPathAsTeamState (vtable
// 0x00C121E8). An owner outside the terrain extent whose goal lies inside it
// takes AIUpdateInterface::computeQuickPath; everything else logs
// ComputePath34 and runs the base computePath.
Bool AIFollowPathAsTeamState::computePath()
{
	critterDesyncLog("CritterDesync: ComputePath33");
	Object *owner = getMachineOwner();
	Coord3D pos; // the extent test ignores z, which retail never copies
	pos.x = owner->getPosition()->x;
	pos.y = owner->getPosition()->y;
	AIUpdateInterface *ai = owner->getObservedAI();
	Region3D extent;
	((const TerrainLogicExtentView *)TheTerrainLogic)->getExtent(&extent);
	if (ai && !extent.isInRegionNoZ(&pos) && extent.isInRegionNoZ(&m_goalPosition))
		return ai->computeQuickPath(&m_goalPosition);

	critterDesyncLog("CritterDesync: ComputePath34");
	return AIInternalMoveToState::computePath();
}

// Retail 0x0034E3A5, 528 bytes: slot 4 of AIFollowPathAsTeamState (vtable
// 0x00C121E8). Zero Hour's AIFollowPathState::onEnter with BFME 2's team
// additions: the +0x5C helper is reset (slots 5 and 8), the AI's last command
// source (slot 143) is remembered at +0x58 and its +0x1A0 at +0x60, and path
// points already behind the owner are skipped (a negative dot product of
// owner-to-point and point-to-next) before the CritterDesync 44/45/46 traces.
// The register pairs of that dot product follow the order the two Coord2D are
// filled (fromOwner first); /G7 then hoists the next-point loads.
StateReturnType AIFollowPathAsTeamState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getObservedAI();
	m_index = 0;
	if (m_5c)
	{
		m_5c->rva0034E3CESlot5();
		m_5c->rva0034E3D8Slot8(0);
	}
	m_lastCommandSource = ai->slot143();
	m_64 = false;
	m_57 = false;
	const Coord3D *pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index);
	if (pos == 0)
		return STATE_FAILURE;
	m_60 = ai->m_1a0;
	m_goalPosition = *pos;
	const Coord3D *nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
	m_adjustFinal = true;
	while (nextPos)
	{
		const Coord3D *goal = &m_goalPosition;
		Coord2D fromOwner;
		fromOwner.x = goal->x;
		fromOwner.y = goal->y;
		Coord2D toNext;
		toNext.x = nextPos->x;
		toNext.y = nextPos->y;
		fromOwner.x -= obj->getPosition()->x;
		fromOwner.y -= obj->getPosition()->y;
		toNext.x -= goal->x;
		toNext.y -= goal->y;
		if (!(toNext.x * fromOwner.x + toNext.y * fromOwner.y < 0.0f))
			break;
		m_index++;
		m_goalPosition = *nextPos;
		nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
	}
	ai->m_currentGoalPathIndex = m_index;

	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
			fprintf(log, "CritterDesync: setAdjustDestination(nextPos=%s) 44", nextPos ? "VALID" : "NULL");
	}
	setAdjustsDestination(nextPos != 0);
	m_adjustFinal = true;
	StateReturnType ret = AIInternalMoveToState::onEnter();
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
		critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 45");
		setAdjustsDestination(false);
	}
	else
	{
		if (g_00E03745)
		{
			void *log = theLogicRandomLogFile;
			if (log != 0)
				fprintf(log, "CritterDesync: setAdjustDestination(m_adjustFinal=%s) 46", m_adjustFinal ? "TRUE" : "FALSE");
		}
		setAdjustsDestination(m_adjustFinal);
		ai->setPathExtraDistance(0.0f);
	}
	return ret;
}

// A state's slot 8, ZH State::isAttack.
class StateAttackView : public VirtualSlots<8>
{
public:
	virtual Bool isAttack() const;
};

inline Bool StateMachine::isInAttackState() const
{
	return m_currentState ? ((const StateAttackView *)m_currentState)->isAttack() : true;
}

// AIAttackMoveToState (vtable 0x00C13548, name slot 0x00345CFA) keeps its
// attack-move machine at +0x54. Retail 0x00340F25, 29 bytes, its slot 9: true
// while that machine is not in an attack state (no null test, unlike ZH's
// isAttack).
class AIAttackMoveToState : public State
{
public:
	virtual Bool rva00340F25() const;
private:
	unsigned char m_pad1C[0x54 - 0x1C];
	StateMachine *m_attackMoveMachine; // +0x54
};

Bool AIAttackMoveToState::rva00340F25() const
{
	return m_attackMoveMachine->isInAttackState() ? false : true;
}

Real Cos(Real angle);
Real Sin(Real angle);
#define PI_F 3.14159265359f

// The locomotor's aim-at-position hook (0x001E702E, rowed under this name).
class Rva001E702E
{
public:
	void rva001E702E(Thing *obj, Int targetPos, Int flag);
};

// BFME 2's partition filter base (ctor 0x000421C8): a vptr and the +0x04 link
// to the next filter (link 0x00625790 appends its argument and returns this).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *objOther) = 0;
	Rva000421C8 *link(Rva000421C8 *next);
private:
	Rva000421C8 *m_next; // +0x04
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};
class PartitionFilterPossibleToAttack : public Rva000421C8
{
public:
	PartitionFilterPossibleToAttack(AbleToAttackType t, const Object *obj, Int commandSource)
		: m_obj(obj), m_commandSource(commandSource), m_attackType(t) {}
	virtual Bool allow(Object *objOther);
private:
	const Object *m_obj; // +0x08
	Int m_commandSource; // +0x0C
	AbleToAttackType m_attackType; // +0x10
};
class PartitionFilterSameMapStatus : public Rva000421C8
{
public:
	PartitionFilterSameMapStatus(const Object *obj) : m_obj(obj) {}
	virtual Bool allow(Object *objOther);
private:
	const Object *m_obj; // +0x08
};
// vftable 0x00BFAD04 (rowed allow 0x00260E2A): Zero Hour's
// PartitionFilterSamePlayer.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(const Player *player) : m_player(player) {}
	virtual Bool allow(Object *objOther);
private:
	const Player *m_player; // +0x08
};
extern PartitionManager *ThePartitionManager;

// Retail 0x0034AAC8, 1047 bytes: slot 6 of AIAttackFireWeaponState (vtable
// 0x00C111F8). Zero Hour's update with BFME 2's additions: Object +0x438 bit 0
// and status 0x52 fail; a template +0x16B weapon holds fire unless the victim
// is immobile; otherwise a walking turretless owner aims its locomotor
// (0x001E702E) at the victim -- its "Ram" contact point for kind 0x10F/0x119
// victims of contact or byte-field weapons, swung by the template +0x30 aim
// offset 1000 units out when that is positive -- when the template +0x2C aim
// delta is under PI; a dead victim ends an object attack unless template
// +0x161. The odd-frame wait, READY_TO_FIRE / PRE_ATTACK, the slot test and
// the firing condition follow Zero Hour; the object shot passes the machine's
// +0x20 goal ID, and a destroyed/dead victim with a continue-attack range
// (+0x148) re-targets around the original victim position through BFME 2's
// chained partition filters (scoped to the query, as retail destroys them
// before the new goal is set).
StateReturnType AIAttackFireWeaponState::update()
{
	Object *obj = getMachineOwner();
	Object *victim = getMachineGoalObject();
	Int goalID = getMachine()->m_goalObjectID;
	WeaponSlotType wslot;
	Weapon *weapon = obj->getCurrentWeapon(&wslot);
	if (!weapon)
		return STATE_FAILURE;
	if (obj->m_438 & 1)
		return STATE_FAILURE;
	if (obj->testStatus(OBJECT_STATUS_52))
		return STATE_FAILURE;

	Bool holdFire;
	if (weapon->getTemplate()->is16b() && !(victim && victim->isKindOfImmobile()))
	{
		holdFire = true;
	}
	else
	{
		holdFire = false;
		AIUpdateInterface *ai;
		if (victim && (ai = obj->getObservedAI()) != 0 && ai->getCurLocomotor() && ai->getWhichTurretForCurWeapon() == TURRET_INVALID)
		{
			Coord3D target;
			target.x = victim->getPosition()->x;
			target.y = victim->getPosition()->y;
			target.z = victim->getPosition()->z;
			if (((victim->getTemplate()->m_kindOf[7] & 0x10) || (victim->getTemplate()->m_kindOf[0x11] & 2)) &&
				(weapon->getTemplate()->isContactWeapon() || ((const Rva002C9400ByteField *)weapon->getTemplate())->get()))
				victim->getWorldspaceBestContactPoint(&target, obj->getPosition(), "Ram", 0, 0x2a, false);
			if (weapon->getTemplate()->m_aimOffset > 0.0f)
			{
				Real offset = weapon->getTemplate()->m_aimOffset;
				Real relative = obj->GetRelativeAngle(&target) - offset;
				Real angle = obj->getOrientation() + relative;
				target = *obj->getPosition();
				target.x += Cos(angle) * 1000.0f;
				target.y += Sin(angle) * 1000.0f;
			}
			Real aimDelta = weapon->getTemplate()->m_aimDelta;
			if (aimDelta < PI_F)
				((Rva001E702E *)ai->getCurLocomotor())->rva001E702E(obj, (Int)&target, 0);
		}
		if (m_att && m_att->isAttackingObject() &&
			(!victim || (victim->m_438 & 1) || victim->testStatus(OBJECT_STATUS_32)) &&
			!weapon->getTemplate()->m_161)
		{
			getMachine()->setGoalObject(0);
			return STATE_SUCCESS;
		}
	}

	if (m_waitOddFrame)
	{
		m_waitOddFrame = false;
		obj->setStatus(OBJECT_STATUS_0D, true);
		obj->preFireCurrentWeapon(victim, getMachineGoalPosition());
		return STATE_CONTINUE;
	}

	WeaponStatus status = weapon->getStatus();
	if (status == PRE_ATTACK)
		return STATE_CONTINUE;
	if (status != READY_TO_FIRE)
		return STATE_FAILURE;
	if (m_att && !m_att->isWeaponSlotOkToFire(wslot))
		return STATE_FAILURE;

	obj->rva0028FC8F();
	if (m_att && m_att->isAttackingObject() && !holdFire)
	{
		obj->fireCurrentWeapon(victim, goalID);
		obj->setStatus(OBJECT_STATUS_1B, false);
		Real continueRange = weapon->getTemplate()->m_continueAttackRange;
		if (continueRange > 0.0f && victim &&
			((victim->m_94 & 1) || (victim->m_438 & 1) || victim->testStatus(OBJECT_STATUS_32)))
		{
			const Coord3D *originalVictimPos = m_att ? m_att->getOriginalVictimPos() : 0;
			if (originalVictimPos)
			{
				AIUpdateInterface *ai = obj->getObservedAI();
				Int lastCmdSource = ai ? ai->slot143() : 2;
				{
					PartitionFilterSameMapStatus filterMapStatus(obj);
					PartitionFilterPossibleToAttack filterAttack(ATTACK_NEW_TARGET, obj, lastCmdSource);
					Rva00260E2AFilter filterPlayer(victim->getControllingPlayer());
					victim = ThePartitionManager->getClosestObject(originalVictimPos, continueRange, 0,
						filterPlayer.link(filterAttack.link(&filterMapStatus)));
				}
				if (victim)
				{
					getMachine()->setGoalObject(victim);
					m_att->notifyNewVictimChosen(victim);
				}
			}
		}
	}
	else
	{
		obj->fireCurrentWeapon(getMachineGoalPosition());
		obj->setStatus(OBJECT_STATUS_1B, false);
	}
	m_att->notifyFired();
	return STATE_SUCCESS;
}

// AIAttackMeleeSquishState::computePath, native 0x003408C4..0x00340A92/462B.
// Identity: slot17 of vtable C12868; its slot2 returns C128B0 (class name),
// with matched onEnter34D886, onExit3497C7 and xfer340A92. WB E14C40 carries
// ComputePath21 and the same owner/goal/containment/radius/requestPath spine.
// ZH approach computePath supplies the repath/timestamp/comparison purpose;
// squish victim selection and outward radius displacement are BFME target facts.
// Cache the normalized scalar components before constructing the scaled offset;
// that leaves the original escaped vector untouched and eliminates false stores.
// The first member add followed by a pointer for y/z preserves native addressing.
struct SquishCoordCopy:Coord3D{ __forceinline SquishCoordCopy(float x_,float y_,float z_){x=x_;y=y_;z=z_;}

 __forceinline SquishCoordCopy(const Coord3D&p){x=p.x;y=p.y;z=p.z;}
 __forceinline void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}
};
Bool AIAttackMeleeSquishState::computePath()
{
 critterDesyncLog("CritterDesync: ComputePath21");
 Bool forceRepath=false;
 AIUpdateInterface*ai=getMachineOwner()->getObservedAI();
 if(ai->isBlockedAndStuck())return false;
 if(m_waitingForPath)return true;
 if(!forceRepath && ai->getPath()==0 && !ai->isWaitingForPath())forceRepath=true;
 if(!forceRepath && TheGameLogic->getFrame()-m_approachTimestamp<(UnsignedInt)LOGICFRAMES_PER_SECOND)return true;
 m_approachTimestamp=TheGameLogic->getFrame();
 if(getMachineGoalObject()){
  Object*source=getMachineOwner();
  if(!forceRepath && isSamePosition(source->getPosition(),&m_prevVictimPos,getMachineGoalObject()->getPosition()))return true;
  Weapon*weapon=source->getCurrentWeapon();if(!weapon)return false;
  Object*victim=getMachineGoalObject();
  Rva0029439DView*contain=(Rva0029439DView*)victim->rva0029439D();
  if(contain){Object*actual=contain->slot68();if(actual)victim=actual;}
  m_prevVictimPos=*victim->getPosition();
  if(source->rva0029493F(victim,2)){
   SquishCoordCopy delta(m_prevVictimPos);delta.sub(source->getPosition());delta.normalize();
   float scale=2.0f*source->m_geometryRadiusB8;float dx=delta.x,dy=delta.y,dz=delta.z;SquishCoordCopy scaled(dx*scale,dy*scale,dz*scale);
   m_goalPosition=m_prevVictimPos;
   m_goalPosition.x+=scaled.x;Coord3D*goal=&m_goalPosition;goal->y+=scaled.y;goal->z+=scaled.z;
   ai->requestPath(&m_goalPosition,false);m_waitingForPath=ai->isWaitingForPath();return true;
  }
 }
 return false;
}

// Retail 0x00345076, 101 bytes: slot 4 of 0x00C10FA0. Clears +0x24, succeeds
// at once when the pinned rva004D7ADD reports the goal gone or there is no goal
// object, otherwise waits from the current frame, one second and two frames
// longer for an owner with status 0x44 or the AI's +0x3CC flag.
StateReturnType AIAttackMeleeHordeWaitPathState::onEnter()
{
	m_bfmeValue24 = 0;
	if (((TurretStateMachine *)getMachine())->rva004D7ADD())
		return STATE_SUCCESS;
	if (!getMachineGoalObject())
		return STATE_SUCCESS;

	UnsignedInt now = TheGameLogic->getFrame();
	m_waitUntilFrame = now;
	Object *owner = getMachineOwner();
	if (owner->testStatus(OBJECT_STATUS_44) || owner->getObservedAI()->m_3cc)
		// Same-valued conditional retains native commutative operand order.
		m_waitUntilFrame = (now ? now : now) + LOGICFRAMES_PER_SECOND + 2;
	return STATE_CONTINUE;
}
