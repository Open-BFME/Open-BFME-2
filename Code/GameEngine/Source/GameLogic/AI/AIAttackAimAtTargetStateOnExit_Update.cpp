// cl: /DNDEBUG /MD
// Split from AIAttackAimAtTargetStateOnExit.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// AIAttackAimAtTargetState::onExit, retail 0x0034A508 (104 bytes): slot 5 of
// vtable 0x00C11008, whose slot-2 name getter returns AIAttackAimAtTargetState
// (slot 3 is the rowed xfer 0x00341237). Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// BFME2 differences (target evidence): after ZH's setLocomotorGoalNone (AI
// vslot 136, +0x220) the AI also restores the normal locomotor set (AI vslot
// 142, +0x238, as in the AIWanderInPlaceState bodies) when the owner
// template's Real at +0x53C (unnamed) is below 360; the aiming status is
// cleared through the rowed Object::setStatus(25, false).
// Layout: m_canTurnInPlace +0x21, m_setLocomotor +0x22, AI +0x258.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_AIMING_WEAPON = 25,
	OBJECT_STATUS_4B = 0x4B	// BFME 2 bit tested by update; label unknown
};
enum WhichTurretType
{
	TURRET_INVALID = -1
};
enum WeaponSlotType;
typedef unsigned int ObjectID;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
class Weapon;
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
struct Rva001E3F08Arg;
class Rva001E3F08
{
public:
	float rva001E3F08(Rva001E3F08Arg *p);
};
class AIUpdateInterface : public VSlots<129>
{
public:
	virtual void addTargeter(ObjectID id, Bool add) = 0;		// +0x204
	virtual Bool isTemporarilyPreventingAimSuccess() = 0;		// +0x208
	virtual void slot131() = 0;
	virtual void slot132() = 0;
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void slot135() = 0;
	virtual void setLocomotorGoalNone() = 0;
	virtual void slot137() = 0;
	virtual void slot138() = 0;
	virtual void slot139() = 0;
	virtual void slot140() = 0;
	virtual void slot141() = 0;
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretTargetObject(WhichTurretType tur, Object *victim, bool isForceAttacking);
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
	Rva001E3F08 *getCurLocomotor() const { return m_curLocomotor; }
private:
	unsigned char m_pad04[0x1F0 - 0x04];
	Rva001E3F08 *m_curLocomotor;	// +0x1F0
};
// The weapon-range interface reached through Object +0x274 -> +0x250 (BFME 2;
// identity unknown): slot 77 tests a position, slot 78 an object.
class Rva00351788RangeTest : public VSlots<77>
{
public:
	// MSVC places overloads in reverse declaration order: the object test is
	// slot 78 (+0x138), the position test slot 77 (+0x134).
	virtual Bool isInRange(Object *source, Weapon *weapon, Object *victim) = 0;
	virtual Bool isInRange(Object *source, Weapon *weapon, const Coord3D *pos) = 0;
};
struct Rva00351788RangeOwner
{
	unsigned char m_pad00[0x250];
	Rva00351788RangeTest *m_rangeTest;	// +0x250
};
class WeaponTemplate
{
public:
	Bool isContactWeapon() const;
};
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
#include "../../../Include/GameLogic/Weapon.h"
class ThingTemplate
{
public:
	Real getUnknown53C() const { return m_unknown53C; }
private:
	unsigned char m_pad00[0x53C];
	Real m_unknown53C; // +0x53C
};
class Object
{
public:
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	AIUpdateInterface *getAI() { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	void setStatus(ObjectStatusTypes bit, bool set);
	void clearStatus(ObjectStatusTypes bit) { setStatus(bit, false); }
	Bool testStatus(ObjectStatusTypes bit) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	int rva0028B511() const;
	void rva0028ACEE(int arg, int arg2);
	int getUnknown38Address() { return (int)&m_unknown38; }
	Rva00351788RangeOwner *getRangeOwner() const { return m_rangeOwner; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	unsigned int m_unknown38; // +0x38
	unsigned char m_pad3C[0x74 - 0x3C];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Rva00351788RangeOwner *m_rangeOwner; // +0x274
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	// Keep the inlined goal address without a competing standalone class-view copy.
	__declspec(dllimport) __forceinline const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad00[0x14];
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
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIAttackAimAtTargetState : public State
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	StateReturnType updateInternal(Bool flag);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	Bool m_isAttackingObject; // +0x20
	Bool m_canTurnInPlace; // +0x21
	Bool m_setLocomotor; // +0x22
	Bool m_isForceAttacking; // +0x23
};


// AIAttackAimAtTargetState::update, retail 0x00351788..0x00351949 (449 bytes,
// vtable 0x00C11008 slot 6); the WorldBuilder twin 0x00E1F050 calls the same
// providers. BFME 2 reworks Zero Hour's body (target evidence): it refreshes
// m_canTurnInPlace from the current locomotor (0x001E3F08 == 0) each frame,
// measures range through Object +0x274's interface or the weapon, feeds the
// victim's targeter list, aims the turret, and otherwise succeeds for an
// in-range contact weapon (unless the victim prevents aim success) or fails
// out of range; it then marks the owner aiming and continues in the
// unrowed 0x003508C5 (WorldBuilder: AIAttackAimAtTargetState::updateInternal).
StateReturnType AIAttackAimAtTargetState::update()
{
	Object *source = getMachineOwner();
	Weapon *weapon = source->getCurrentWeapon();
	Object *victim = getMachineGoalObject();
	const Coord3D *goalPos = getMachineGoalPosition();
	AIUpdateInterface *sourceAI = source->getAI();
	AIUpdateInterface *victimAI = victim ? victim->getAI() : 0;
	Rva001E3F08 *curLoco = sourceAI->getCurLocomotor();

	m_setLocomotor = false;
	m_canTurnInPlace = curLoco ? curLoco->rva001E3F08((Rva001E3F08Arg *)source) == 0.0f : false;

	source->rva0028ACEE(source->getUnknown38Address(), source->rva0028B511());

	char inRange = false;	// 0x002CB902 is spelled with a char result
	Rva00351788RangeOwner *rangeOwner = source->getRangeOwner();
	if (rangeOwner && weapon)
	{
		Rva00351788RangeTest *rangeTest = rangeOwner->m_rangeTest;
		if (victim)
			inRange = rangeTest->isInRange(source, weapon, victim);
		else
			inRange = rangeTest->isInRange(source, weapon, goalPos);
	}
	else if (victim && weapon)
		inRange = weapon->isWithinAttackRange((const Object *)source, (const Object *)victim, 0.0f, 1);
	else if (weapon)
		inRange = weapon->isWithinAttackRange(source, (void *)goalPos, 0.0f, 1);
	else
		return STATE_FAILURE;

	if (victimAI)
		victimAI->addTargeter(source->getID(), true);

	WhichTurretType tur = sourceAI->getWhichTurretForCurWeapon();
	if (tur != TURRET_INVALID)
	{
		if (m_isAttackingObject)
			sourceAI->setTurretTargetObject(tur, victim, m_isForceAttacking);
		else
			sourceAI->setTurretTargetPosition(tur, getMachineGoalPosition());
	}
	else
	{
		Bool preventing = victimAI && victimAI->isTemporarilyPreventingAimSuccess();
		if (weapon && weapon->getTemplate()->isContactWeapon() && inRange && !preventing)
			return STATE_SUCCESS;
		if (weapon && ((const Rva002C9400ByteField *)weapon->getTemplate())->get() && !inRange)
			return STATE_FAILURE;
	}

	if (source->testStatus(OBJECT_STATUS_4B))
		return STATE_SUCCESS;

	source->setStatus(OBJECT_STATUS_IS_AIMING_WEAPON, true);
	return updateInternal(true);
}
