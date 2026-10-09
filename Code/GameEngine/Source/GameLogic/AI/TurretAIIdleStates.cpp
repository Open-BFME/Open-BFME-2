// cl: /ICode/Libraries/Include/Lib /DNDEBUG /MD
//
// TurretAI idle and hold-turret states with their file-static
// frameToSleepTime, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// TurretAI.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - frameToSleepTime, retail 0x004D7CB9 (45 bytes): Zero Hour's static.
//    Retail passes its first frame in EAX (the value the preceding
//    friend_getNextIdleMoodTargetFrame call returns) and the other three on
//    the stack, caller-popped. That is the convention cl 7.1 gives an
//    internal-linkage function whose every call site is in the unit: it is
//    reproduced here by compiling the static together with its callers, no
//    /GL or __fastcall needed (/arch:SSE gives retail's cmova chain).
//  - TurretAIIdleState::update, retail 0x004D88F6 (63 bytes), and
//    TurretAIHoldTurretState::update, retail 0x004D8935 (63 bytes): Zero
//    Hour's bodies. The turret's friend_getNextIdleMoodTargetFrame
//    (0x004D837D) and friend_checkForIdleMoodTarget (0x004D88AC) are out of
//    line. (The two onEnter callers, 0x004D83D1 and 0x004D84D2, are banked
//    near-misses: their argument pushes are scheduled differently.)
//  - TurretAIIdleScanState::onEnter, retail 0x004D8448 (138 bytes): Zero
//    Hour's body (idle scan angles from the turret data +0x50 / +0x54,
//    desired angle +0x20; TurretAI.cpp lines 1381 and 1382).
//  - TurretAI::friend_isSweepEnabled, retail 0x004D8365 (24 bytes): Zero
//    Hour's body (m_enableSweepUntil +0x24).
//  - TurretAIRecenterTurretState::update, retail 0x004D8D25 (90 bytes), and
//    TurretAIIdleScanState::update, retail 0x004D8D7F (107 bytes): Zero
//    Hour's bodies without the under-construction early-out; natural angle
//    and pitch are the turret data's +0x08 / +0x0C; friend_turnTowardsAngle
//    is 0x004D8990 and friend_turnTowardsPitch the rowed 0x004D80EE.
//  - TurretAI::friend_getTurretTarget, retail 0x004D81F1 (110 bytes): moved
//    here unchanged from TurretAI_friendGetTurretTarget.cpp (that file keeps
//    TurretStateMachine::getGoalObject 0x004D7726 and its alternatename).
//  - TurretAIAimTurretState::update, retail 0x004D8EAC..0x004D92E9 (1085
//    bytes): Zero Hour's body (WorldBuilder twin 0x01351790, TurretAI.cpp
//    assert line 1077) with BFME 2 deltas: SetModelAngle(obj, relAngle) right
//    after the relative angle (Object::GetRelativeAngle pin 0x000B4542), the
//    bridge distances through Object 0x002637E2 (position, point), the
//    getVectorTo through 0x001E438B, the attack range through 0x002C9BC3 and
//    no `v.length() > 0` guard before ASin. It must share this unit with
//    friend_getTurretTarget and friend_isSweepEnabled: retail keeps `enemy`
//    in ESI across calls after friend_getTurretTarget (cl knows the same-unit
//    callee does not keep &enemy) and keeps EDX/XMM0 live across
//    friend_isSweepEnabled. SetModelAngle is a thiscall member (the caller
//    loads this into ECX); its row needs the member spelling.
//    AI vslots: addTargeter 0x204 isTemporarilyPreventingAimSuccess 0x208
//    isDoingGroundMovement 0x224 getLastCommandSource 0x23C; AI state machine
//    +0x30; Object position +0x38 ID +0x74 geometry +0xA8 AI +0x258 team
//    +0x304; turret owner +0x10 angle +0x18 victim team +0x28 positive sweep
//    +0x3A force-attacking +0x3E; turret data sweep +0x10 sweep speed +0x28
//    fire pitch +0x40 min pitch +0x44 ground pitch +0x48 allows pitch +0x66.
// BFME 2 layout (target evidence): the state machine's turret +0x3C; the
// turret's which-turret +0x0C and data +0x08 (recenter time +0x60); the AI's
// turret sync +0x210 (resetNextMoodCheckTime is the rowed 0x00263025); the
// states' m_nextIdleScan / m_timestamp at +0x20.
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;

#include "Coord3D.h"

int GetGameLogicRandomValue(int low, int high, char *file, int line);
Real GetGameLogicRandomValueReal(Real low, Real high, char *file, int line);
#define TURRETAI_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\TurretAI.cpp"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
#define STATE_SLEEP(x) ((StateReturnType)(x))
#define FOREVER 0x3fffffff

enum WhichTurretType
{
	TURRET_INVALID = -1
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class Object;
class Team;
class Weapon;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_CONTINUED_TARGET = 2,
	ATTACK_CONTINUED_TARGET_FORCED = 3
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

enum TurretTargetType
{
	TARGET_NONE,
	TARGET_OBJECT,
	TARGET_POSITION
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_BRIDGE = 22
};

enum ObjectID
{
	INVALID_ID = 0
};

class StateMachine
{
public:
	virtual void _rsvd00();
	virtual void _rsvd01();
	virtual void _rsvd02();
	virtual void _rsvd03();
	virtual void _rsvd04();
	virtual void _rsvd05();
	virtual void _rsvd06();
	virtual void _rsvd07();
	virtual void _rsvd08();
	virtual void _rsvd09();
	virtual void _rsvd10();
	virtual void _rsvd11();
	virtual void _rsvd12();
	virtual void _rsvd13();
	virtual void setGoalObject(Object *o); // slot 0x38
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x20 - 0x18];
public:
	ObjectID m_goalObjectID; // +0x20
	Coord3D m_goalPosition; // +0x24
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class AIUpdateInterface : public VSlots<129>
{
public:
	virtual void addTargeter(UnsignedInt id, Bool add) = 0; // slot 0x204
	virtual Bool isTemporarilyPreventingAimSuccess() = 0; // slot 0x208
	virtual void slot131() = 0;
	virtual void slot132() = 0;
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void slot135() = 0;
	virtual void slot136() = 0;
	virtual Bool isDoingGroundMovement() const = 0; // slot 0x224
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void slot142() = 0;
	virtual CommandSourceType getLastCommandSource() const = 0; // slot 0x23C

	void rva00263025(); // resetNextMoodCheckTime
	void resetNextMoodCheckTime() { rva00263025(); }
	WhichTurretType friend_getTurretSync() const { return m_turretSyncFlag; }
	void friend_setTurretSync(WhichTurretType t) { m_turretSyncFlag = t; }
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
private:
	unsigned char m_pad04[0x30 - 0x04];
	StateMachine *m_stateMachine; // +0x30
	unsigned char m_pad34[0x210 - 0x34];
	WhichTurretType m_turretSyncFlag; // +0x210
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 0x1f)); }
private:
	unsigned char m_pad00[0x108];
	UnsignedInt m_kindOf[8]; // +0x108
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class Rva001E438B
{
public:
	void rva001E438B(float *out, const float *pos);
};

class Object
{
public:
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *victim, CommandSourceType src) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Real rva002637E2(const Coord3D *from, const Coord3D *to) const;
	Real GetRelativeAngle(const Coord3D *pos) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	const Coord3D *getPosition() const { return &m_position; }
	UnsignedInt getID() const { return m_id; }
	AIUpdateInterface *getAI() const { return m_ai; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	Team *getTeam() const { return m_team; }
	void getVectorTo3D(const Coord3D *pos, Coord3D &v) { ((Rva001E438B *)this)->rva001E438B(&v.x, &pos->x); }

	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	UnsignedInt m_id; // +0x74
	unsigned char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_padA9[0x258 - 0xA9];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_deadFlags; // +0x438
};

class Rva002C9BC3Owner
{
public:
	Real rva002C9BC3(void *source, void *pos);
};

class Weapon
{
public:
	char isWithinAttackRange(Object *source, void *pos, Real extra, Int flags) const;
	Bool isWithinAttackRange(const Object *source, const Object *victim, Real extra, Int flags) const;
	Real getAttackRange(const Object *source, const Coord3D *pos) const { return ((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)source, (void *)pos); }
};

struct TBridgeAttackInfo
{
	Coord3D attackPoint1;
	Coord3D attackPoint2;
};

class TerrainLogic
{
public:
	void getBridgeAttackPoints(const Object *bridge, TBridgeAttackInfo *info);
};
extern TerrainLogic *TheTerrainLogic;

Real normalizeAngle(Real angle);
Real ASin(Real x);
extern "C" double __cdecl fabs(double);

struct TurretAIData
{
	unsigned char m_pad00[0x08];
	Real m_naturalTurretAngle; // +0x08
	Real m_naturalTurretPitch; // +0x0C
	Real m_turretFireAngleSweep[6]; // +0x10
	Real m_turretSweepSpeedModifier[6]; // +0x28
	Real m_firePitch; // +0x40
	Real m_minPitch; // +0x44
	Real m_groundUnitPitch; // +0x48
	unsigned char m_pad4C[0x50 - 0x4C];
	Real m_minIdleScanAngle; // +0x50
	Real m_maxIdleScanAngle; // +0x54
	unsigned char m_pad58[0x60 - 0x58];
	UnsignedInt m_recenterTime; // +0x60
	unsigned char m_pad64[0x66 - 0x64];
	Bool m_isAllowsPitch; // +0x66
};

class TurretStateMachine;

class TurretAI
{
public:
	UnsignedInt rva004D837D();
	void friend_checkForIdleMoodTarget();
	WhichTurretType friend_getWhichTurret() const { return m_whichTurret; }
	UnsignedInt getRecenterTime() const { return m_data->m_recenterTime; }
	Real getMinIdleScanAngle() const { return m_data->m_minIdleScanAngle; }
	Real getMaxIdleScanAngle() const { return m_data->m_maxIdleScanAngle; }
	Bool friend_isSweepEnabled() const;
	Bool friend_turnTowardsAngle(Real desiredAngle, Real rateModifier, Real relThresh);
	Bool friend_turnTowardsPitch(Real desiredPitch, Real rateModifier);
	Real getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	Real getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }
	TurretTargetType friend_getTurretTarget(Object *&obj, Coord3D &pos) const;
	Bool friend_isAnyWeaponInRangeOf(const Object *o) const;
	void setTurretTargetObject(Object *o, Bool forceAttacking);
	Object *getOwner() const { return m_owner; }
	Real getTurretAngle() const { return m_angle; }
	Real getTurretFireAngleSweepForWeaponSlot(WeaponSlotType slot) const { return m_data->m_turretFireAngleSweep[slot]; }
	Real getTurretSweepSpeedModifierForWeaponSlot(WeaponSlotType slot) const { return m_data->m_turretSweepSpeedModifier[slot]; }
	Bool isAllowsPitch() const { return m_data->m_isAllowsPitch; }
	Real getFirePitch() const { return m_data->m_firePitch; }
	Real getMinPitch() const { return m_data->m_minPitch; }
	Real getGroundUnitPitch() const { return m_data->m_groundUnitPitch; }
	Team *friend_getVictimInitialTeam() const { return m_victimInitialTeam; }
	Bool friend_getPositiveSweep() const { return m_positiveSweep; }
	void friend_setPositiveSweep(Bool b) { m_positiveSweep = b; }
	Bool isForceAttacking() const { return m_isForceAttacking; }
	Bool friend_getTargetWasSetByIdleMood() const { return m_targetWasSetByIdleMood; }
private:
	unsigned char m_pad00[0x08];
	const TurretAIData *m_data; // +0x08
	WhichTurretType m_whichTurret; // +0x0C
	Object *m_owner; // +0x10
	TurretStateMachine *m_machine; // +0x14
	Real m_angle; // +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	UnsignedInt m_enableSweepUntil; // +0x24
	Team *m_victimInitialTeam; // +0x28
	mutable TurretTargetType m_target; // +0x2C
	unsigned char m_pad30[0x3A - 0x30];
	Bool m_positiveSweep; // +0x3A
	unsigned char m_pad3B[0x3E - 0x3B];
	Bool m_isForceAttacking; // +0x3E
	mutable Bool m_targetWasSetByIdleMood; // +0x3F
};

class TurretStateMachine : public StateMachine
{
public:
	TurretAI *getTurretAI() const { return m_turretAI; }
	Object *getGoalObject();
private:
	unsigned char m_pad30[0x3C - 0x30];
	TurretAI *m_turretAI; // +0x3C
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(Int status);
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class TurretState : public State
{
protected:
	TurretAI *getTurretAI() const { return ((TurretStateMachine *)getMachine())->getTurretAI(); }
};

class TurretAIIdleState : public TurretState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_nextIdleScan; // +0x20
};

class TurretAIRecenterTurretState : public TurretState
{
public:
	virtual StateReturnType update();
};

class TurretAIIdleScanState : public TurretState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Real m_desiredAngle; // +0x20
};

class TurretAIAimTurretState : public TurretState
{
public:
	virtual StateReturnType update();
	void SetModelAngle(Object *obj, Real angle);
};

class TurretAIHoldTurretState : public TurretState
{
public:
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_timestamp; // +0x20
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static StateReturnType frameToSleepTime(
	UnsignedInt frame1,
	UnsignedInt frame2 = FOREVER,
	UnsignedInt frame3 = FOREVER,
	UnsignedInt frame4 = FOREVER
)
{
	if (frame1 > frame2) frame1 = frame2;
	if (frame1 > frame3) frame1 = frame3;
	if (frame1 > frame4) frame1 = frame4;
	UnsignedInt now = TheGameLogic->getFrame();
	if (frame1 > now)
	{
		return STATE_SLEEP(frame1 - now);
	}
	else
	{
		// ignore times that are in the past, since this can frequently happen
		return STATE_CONTINUE;
	}
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIIdleState::update()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now >= m_nextIdleScan)
	{
		return STATE_FAILURE;
	}

	TurretAI* turret = getTurretAI();
	turret->friend_checkForIdleMoodTarget();

	return frameToSleepTime(turret->rva004D837D(), m_nextIdleScan);
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIHoldTurretState::update()
{
	if (TheGameLogic->getFrame() >= m_timestamp)
		return STATE_SUCCESS;

	TurretAI* turret = getTurretAI();
	turret->friend_checkForIdleMoodTarget();

	return frameToSleepTime(turret->rva004D837D(), m_timestamp);
}

//----------------------------------------------------------------------------------------------------------
Bool TurretAI::friend_isSweepEnabled() const
{
	if (m_enableSweepUntil != 0 && m_enableSweepUntil > TheGameLogic->getFrame())
		return true;

	return false;
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIIdleScanState::onEnter()
{
	Real minA = getTurretAI()->getMinIdleScanAngle();
	Real maxA = getTurretAI()->getMaxIdleScanAngle();
	if (minA == 0.0f && maxA == 0.0f)
		return STATE_SUCCESS;

	m_desiredAngle = minA + GetGameLogicRandomValueReal(0, maxA - minA, TURRETAI_FILE, 1381);
	if (GetGameLogicRandomValue( 0, 1, TURRETAI_FILE, 1382 ) == 0)
		m_desiredAngle = -m_desiredAngle;

	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------------------
/**
 * Rotate the owner's turret to its home orientation.
 */
StateReturnType TurretAIRecenterTurretState::update()
{
	TurretAI* turret = getTurretAI();
	Bool angleAligned = turret->friend_turnTowardsAngle(turret->getNaturalTurretAngle(), 0.5f, 0.0f);
	Bool pitchAligned = turret->friend_turnTowardsPitch(turret->getNaturalTurretPitch(), 0.5f);

	if( angleAligned && pitchAligned )
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
/**
 * Rotate the owner's turret to its scan orientation.
 */
StateReturnType TurretAIIdleScanState::update()
{
	Bool angleAligned = getTurretAI()->friend_turnTowardsAngle(getTurretAI()->getNaturalTurretAngle() + m_desiredAngle, 0.5f, 0.0f);
	Bool pitchAligned = getTurretAI()->friend_turnTowardsPitch(getTurretAI()->getNaturalTurretPitch(), 0.5f);

	if( angleAligned && pitchAligned )
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------------------
TurretTargetType TurretAI::friend_getTurretTarget(Object *&obj, Coord3D &pos) const
{
	obj = 0;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	if (m_target == TARGET_OBJECT)
	{
		obj = m_machine->getGoalObject();
		if (obj == 0 || (obj->m_deadFlags & 1))
		{
			m_machine->setGoalObject(0);
			m_target = TARGET_NONE;
			m_targetWasSetByIdleMood = false;
		}
	}
	else if (m_target == TARGET_POSITION)
	{
		obj = 0;
		pos = m_machine->m_goalPosition;
	}

	return m_target;
}

//----------------------------------------------------------------------------------------------------------
/**
 * Rotate our turret to point at the machine's goal
 */
StateReturnType TurretAIAimTurretState::update()
{
	TurretAI* turret = getTurretAI();
	Object* obj = turret->getOwner();
	AIUpdateInterface* ai = obj->getAI();
	if( !ai )
	{
		return STATE_FAILURE;
	}

	Object* enemy;
	AIUpdateInterface* enemyAI=0;
	Coord3D enemyPosition;
	Bool preventing = false;
	TurretTargetType targetType =  turret->friend_getTurretTarget(enemy, enemyPosition);
	Object *enemyForDistanceCheckOnly = enemy;

	Bool nothingInRange = false;
	switch (targetType)
	{
		case TARGET_NONE:
		{
			return STATE_FAILURE;
		}

		case TARGET_OBJECT:
		{
			Bool isPrimaryEnemy = (enemy && enemy == ai->getGoalObject());
			Bool ableToAttackTarget = obj->isAbleToAttack();
			if (ableToAttackTarget)
			{
				CanAttackResult result = obj->getAbleToAttackSpecificObject(
							turret->isForceAttacking() ? ATTACK_CONTINUED_TARGET_FORCED : ATTACK_CONTINUED_TARGET,
							enemy,
							ai->getLastCommandSource()
						);
				ableToAttackTarget = result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING;
			}

			nothingInRange = !turret->friend_isAnyWeaponInRangeOf(enemy);
			if (enemy == 0 || !ableToAttackTarget ||
					(!isPrimaryEnemy && nothingInRange) ||
					enemy->getTeam() != turret->friend_getVictimInitialTeam()
			)
			{
				if (turret->friend_getTargetWasSetByIdleMood())
				{
					turret->setTurretTargetObject(0, false);
				}
				return STATE_FAILURE;
			}

			if (enemy->isKindOf(KINDOF_BRIDGE))
			{
				TBridgeAttackInfo info;
				TheTerrainLogic->getBridgeAttackPoints(enemy, &info);
				Real distSqr = obj->rva002637E2(obj->getPosition(), &info.attackPoint1);
				if (distSqr > obj->rva002637E2(obj->getPosition(), &info.attackPoint2))
				{
					enemyPosition = info.attackPoint2;
				}
				else
				{
					enemyPosition = info.attackPoint1;
				}
			}
			else
			{
				enemyPosition = *enemy->getPosition();
			}

			enemyAI = enemy ? enemy->getAI() : 0;

			if (enemyAI)
				enemyAI->addTargeter(obj->getID(), true);

			preventing = enemyAI && enemyAI->isTemporarilyPreventingAimSuccess();

			enemy = 0;
			break;
		}

		case TARGET_POSITION:
		{
			break;
		}
	}

	WeaponSlotType slot;
	const Weapon *curWeapon = obj->getCurrentWeapon( &slot );
	if (!curWeapon)
	{
		return STATE_FAILURE;
	}

	Real turnSpeedModifier = 1.0f;

	Real relAngle = obj->GetRelativeAngle( &enemyPosition );
	SetModelAngle(obj, relAngle);

	Real aimAngle = relAngle;
	Real sweep = turret->getTurretFireAngleSweepForWeaponSlot( slot );
	if (sweep > 0.0f && turret->friend_isSweepEnabled())
	{
		if (turret->friend_getPositiveSweep())
			aimAngle += sweep;
		else
			aimAngle -= sweep;

		turnSpeedModifier = turret->getTurretSweepSpeedModifierForWeaponSlot( slot );
	}

	const Real REL_THRESH = 0.035f;
	Bool turnAlignedToNemesis = turret->friend_turnTowardsAngle(aimAngle, turnSpeedModifier, REL_THRESH);

	if (sweep > 0.0f)
	{
		if (turnAlignedToNemesis)
			turret->friend_setPositiveSweep(!turret->friend_getPositiveSweep());

		Real angleDiff = normalizeAngle(relAngle - turret->getTurretAngle());
		turnAlignedToNemesis = (fabs(angleDiff) < sweep);
	}

	Bool pitchAlignedToNemesis = true;

	if( turret->isAllowsPitch() )
	{
		Real desiredPitch = 0;

		if( turret->getFirePitch() > 0 )
		{
			desiredPitch = turret->getFirePitch();
		}
		else
		{
			Coord3D v;
			obj->getVectorTo3D(&enemyPosition, v);

			v.z -= obj->getGeometryInfo().getMaxHeightAbovePosition() / 2;

			Real actualPitch;
			actualPitch = ASin( v.z / v.length() );

			desiredPitch = actualPitch;
			if( desiredPitch < turret->getMinPitch() )
			{
				desiredPitch = turret->getMinPitch();
			}
			if (turret->getGroundUnitPitch() > 0) {
				Bool adjust = false;
				if (!enemy) {
					adjust = true;
				}
				if (enemy && enemy->isKindOf(KINDOF_IMMOBILE)) {
					adjust = true;
				}
				if (enemyAI && enemyAI->isDoingGroundMovement()) {
					adjust = true;
				}
				if (adjust) {
					Real range = curWeapon->getAttackRange(obj, &enemyPosition);
					Real dist = v.length();
					if (range<1) range = 1;
					Real groundPitch = turret->getGroundUnitPitch() * (dist/range);
					desiredPitch = actualPitch+groundPitch;
					if (desiredPitch < turret->getMinPitch()) {
						desiredPitch = turret->getMinPitch();
					}
				}
			}

		}

		pitchAlignedToNemesis = turret->friend_turnTowardsPitch(desiredPitch, 1.0f);
	}

	if (turnAlignedToNemesis && pitchAlignedToNemesis &&
		((enemyForDistanceCheckOnly && curWeapon->isWithinAttackRange((const Object *)obj, (const Object *)enemyForDistanceCheckOnly, 0.0f, 1)) ||
		 (!enemyForDistanceCheckOnly && curWeapon->isWithinAttackRange(obj, &enemyPosition, 0.0f, 1))))
	{
		if (preventing || nothingInRange)
		{
			return STATE_CONTINUE;
		}
		return STATE_SUCCESS;
	}

	return STATE_CONTINUE;
}
