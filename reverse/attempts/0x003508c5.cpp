// ?rva003508C5@Rva00351949Host@@QAEXH@Z
// partial score=0.67 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR draft (bank): register allocation swaps ESI/EDI against retail; move to
// Code/GameEngine/Source/GameLogic/AI/ and restore the ../../Common include paths.
//
// AIAttackAimAtTargetState::updateInternal, retail 0x003508C5 (1104 bytes):
// the body AIAttackAimAtTargetState::update (slot 6 of vtable 0x00C11008,
// rowed 0x00351949) calls with false. WorldBuilder names the twin
// AIAttackAimAtTargetState::updateInternal (0x00E1F350, AIStates.cpp); it
// returns the StateReturnType in EAX and tests its argument as a byte.
// Zero Hour AIAttackAimAtTargetState::update is the lead. BFME2 differences
// read from retail (the twin agrees): no AI or no weapon (Object
// 0x0028ADE0) fails; an attacked victim fails when dead (+0x438 bit 0)
// with status 0x32 or when 0x002943B2 refuses the owner's player; a slow
// turner (template +0x53C below 360) whose AI slot 143 is not 2 fails when
// 0x0028F326 rejects the victim within ten times its vision range; aiming
// clamps to 0.035 (0.3 while disabled kind 3) and status 0x4B succeeds at
// once; an attacked victim of kind 60 or 137 with a contact or +0x2C9400
// weapon aims at its best contact point ("Ram"); a slow turner re-chooses
// its locomotor set and latches its orientation at +0x1C0; the weapon's
// aim offset (+0x30) is applied; with status 0x3A the shooter (or the
// object 0x002931BA names) must still be in range; a victim rowed
// Rva0034311ECheck fails; and the argument stops before the aim test,
// which also passes inside half the locomotor turn rate.

#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../Code/Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

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
enum ObjectStatusTypes
{
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_3A = 0x3A,
	OBJECT_STATUS_4B = 0x4B
};

class Object;
class Player;

extern "C" float __cdecl fabs(double); // CRT fabs (the /O1 call); x87 result compared as float
Real normalizeAngle(Real angle);

extern GameLogic *TheGameLogic;

template <int N> class AIAimAISlots : public AIAimAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIAimAISlots<0>
{
};

class AIUpdateInterface : public AIAimAISlots<129>
{
public:
	virtual void addTargeter(ObjectID id, Bool add) = 0;	// slot 129
	virtual Bool isTemporarilyPreventingAimSuccess() = 0;	// slot 130
	virtual void slot131() = 0;
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &newPos) = 0;	// slot 132
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void setLocomotorGoalOrientation(Real angle) = 0;	// slot 135
	virtual void slot136() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual void chooseLocomotorSet(Int set) = 0;	// slot 142
	virtual Int slot143() = 0;
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Real getTurretTurnRate(WhichTurretType tur) const;
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *obj) const;	// 0x001E3E9F
};

struct Rva0028AC4EEntry;

class ThingTemplate
{
public:
	Bool isKindOf3C() const { return (m_kindOf[0x07] & 0x10) != 0; }
	Bool isKindOf89() const { return (m_kindOf[0x11] & 0x02) != 0; }
	Bool isKindOf96() const { return (m_kindOf[0x12] & 0x40) != 0; }
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[0x1C]; // +0x108
	unsigned char m_pad124[0x53C - 0x124];
	Real m_53c; // +0x53C
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;	// 0x002C9400
};

class WeaponTemplate
{
public:
	Bool isContactWeapon() const;	// 0x0047A699
	unsigned char m_pad00[0x2C];
	Real m_aimDelta; // +0x2C
	Real m_aimOffset; // +0x30
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;	// 0x002CB933
	char isWithinAttackRange(Object *source, void *pos, Real extra, Int flag) const;	// 0x002CB902
private:
	unsigned char m_pad00[0x04];
	const WeaponTemplate *m_template; // +0x04
};

// The vision-range reach test 0x0028F326, pinned under this view.
class Rva0028F326Owner
{
public:
	unsigned char rva0028F326(unsigned int victim, float range);
};

class Object
{
public:
	Bool rva0028ADE0() const;	// 0x0028ADE0
	const Weapon *getCurrentWeapon(WeaponSlotType *slot = 0) const;	// 0x0028AEBD
	Bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	Player *getControllingPlayer() const;	// 0x0028AFA9
	Bool rva002943B2(const Player *player);	// 0x002943B2
	Real getVisionRange() const;	// 0x0028DDE0
	const Rva0028AC4EEntry *rva0028AC4E() const;	// 0x0028AC4E
	Bool getWorldspaceBestContactPoint(Coord3D *out, const Coord3D *from, const char *bone,
		Int a, Int b, Bool c) const;	// 0x002904DC
	Real GetRelativeAngle(const Coord3D *pos) const;	// 0x000B4542
	Bool rva002931BA();	// 0x002931BA

	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	Bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Bool isDisabledByType3() const { return (m_disabled & 8) != 0; }
	Real getOrientation() const { return m_orientation; }

private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id; // +0x74
public:
	ObjectID m_78; // +0x78
	unsigned char m_pad07C[0x1C0 - 0x7C];
	Real m_1c0; // +0x1C0
	unsigned char m_pad1C4[0x1C8 - 0x1C4];
private:
	unsigned char m_disabled; // +0x1C8
	unsigned char m_pad1C9[0x258 - 0x1C9];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_438; // +0x438
};

Bool Rva0034311ECheck(Object *victim);	// 0x0034311E

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();	// 0x004D7726
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class State
{
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	void *m_vtable;
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIAttackAimAtTargetState : public State
{
private:
	StateReturnType updateInternal(Bool stopBeforeAim);
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_isAttackingObject; // +0x20
	Bool m_canTurnInPlace; // +0x21
	Bool m_setLocomotor; // +0x22
	Bool m_isForceAttacking; // +0x23
};

StateReturnType AIAttackAimAtTargetState::updateInternal(Bool stopBeforeAim)
{
	Object *source = getMachineOwner();
	AIUpdateInterface *sourceAI = source->getAI();
	if (!sourceAI)
		return STATE_FAILURE;
	if (!source->rva0028ADE0())
		return STATE_FAILURE;

	Object *victim = getMachineGoalObject();
	const Weapon *weapon = source->getCurrentWeapon();
	if (m_isAttackingObject)
	{
		if (!victim || victim->isEffectivelyDead() || victim->testStatus(OBJECT_STATUS_32))
			return STATE_FAILURE;
		if (victim->rva002943B2(source->getControllingPlayer()))
			return STATE_FAILURE;
		if (source->getTemplate()->m_53c < 360.0f && sourceAI->slot143() != 2 &&
			!((Rva0028F326Owner *)source)->rva0028F326((unsigned int)victim, source->getVisionRange() * 10.0f))
			return STATE_FAILURE;
	}

	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(tur, getMachineGoalPosition());
		if (sourceAI->getTurretTurnRate(tur) != 0.0f)
			return STATE_CONTINUE;
	}

	const Real REL_THRESH = 0.035f;
	const Real DISABLED_THRESH = 0.3f;
	Real aimDelta = weapon ? weapon->getTemplate()->m_aimDelta : 0.0f;
	if (aimDelta < REL_THRESH)
		aimDelta = REL_THRESH;

	Real turnRate = 0.0f;
	if (source->rva0028AC4E())
		turnRate = ((const Locomotor *)source->rva0028AC4E())->getMaxTurnRate(source);

	if (source->isDisabledByType3() && aimDelta < DISABLED_THRESH)
		aimDelta = DISABLED_THRESH;

	if (source->testStatus(OBJECT_STATUS_4B))
		return STATE_SUCCESS;

	Coord3D goalPos;
	goalPos.x = getMachineGoalPosition()->x;
	goalPos.y = getMachineGoalPosition()->y;
	goalPos.z = getMachineGoalPosition()->z;
	if (m_isAttackingObject)
	{
		Bool gotContact = weapon && (victim->getTemplate()->isKindOf3C() || victim->getTemplate()->isKindOf89()) &&
			(weapon->getTemplate()->isContactWeapon() || ((const Rva002C9400ByteField *)weapon->getTemplate())->get());
		if (gotContact)
			gotContact = victim->getWorldspaceBestContactPoint(&goalPos, source->getPosition(), "Ram", 0, 0x2A, false);
		if (!victim->getTemplate()->isKindOf96() && !gotContact)
			goalPos = *victim->getPosition();
	}

	Real relAngle = source->GetRelativeAngle(&goalPos);
	if (source->getTemplate()->m_53c < 360.0f)
	{
		Bool turned = false;
		if (fabs(relAngle) > source->getTemplate()->m_53c * 3.141f / 360.0f)
			turned = true;
		sourceAI->chooseLocomotorSet(turned ? 15 : 0);
		if (turned)
			source->m_1c0 = source->getOrientation();
	}

	if (weapon && weapon->getTemplate()->m_aimOffset > 0.0f)
		relAngle = normalizeAngle(relAngle - weapon->getTemplate()->m_aimOffset);

	if (m_canTurnInPlace)
	{
		if (aimDelta < 3.1415927f)
		{
			if (fabs(relAngle) > aimDelta || stopBeforeAim)
			{
				sourceAI->setLocomotorGoalOrientation(source->getOrientation() + relAngle);
				m_setLocomotor = true;
			}
		}
	}
	else
	{
		sourceAI->setLocomotorGoalPositionExplicit(goalPos);
	}

	if (source->testStatus(OBJECT_STATUS_3A))
	{
		Object *shooter = source;
		if (shooter->rva002931BA())
		{
			shooter = TheGameLogic->findObjectByID(source->m_78);
			if (!shooter)
				shooter = source;
		}
		const Weapon *shooterWeapon = shooter->getCurrentWeapon();
		if (!shooterWeapon)
			return STATE_FAILURE;
		if (victim)
		{
			if (!shooterWeapon->isWithinAttackRange((const Object *)shooter, (const Object *)victim, 0.0f, 1))
				return STATE_FAILURE;
		}
		else if (!shooterWeapon->isWithinAttackRange(shooter, (void *)getMachineGoalPosition(), 0.0f, 1))
			return STATE_FAILURE;
	}

	if (victim && Rva0034311ECheck(victim))
		return STATE_FAILURE;

	if (stopBeforeAim)
		return STATE_CONTINUE;

	if (fabs(relAngle) < aimDelta || fabs(relAngle) < turnRate * 0.5f)
	{
		AIUpdateInterface *victimAI = victim ? victim->getAI() : 0;
		if (victimAI)
			victimAI->addTargeter(source->getID(), true);
		if (victimAI && victimAI->isTemporarilyPreventingAimSuccess())
			return STATE_CONTINUE;
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
