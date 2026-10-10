// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?rva005430E7@@YA_NPAUState@@PAX@Z, retail 0x005430E7..0x00543163 (124
// bytes): Zero Hour AIGuard.cpp's hasAttackedMeAndICanReturnFire, the
// AIGuardMachine transition condition (to state 5005, the attack-aggressor
// state). Its address is the test of the condition table the rowed
// AIGuardMachine ctor 0x00543163 hands to defineState for states 5003 and
// 5001; this spelling is the one AIGuardMachineCtor.cpp references.
//
// Target evidence: owner = state +0x18 machine +0x14 owner; body module at
// owner +0x254 and its vslot 18 (+0x48) is getClearableLastAttacker; the
// rowed GameLogic::findObjectByID 0x00049DC5 on TheGameLogic; the rowed
// Object::getRelationship 0x0028D156 (ENEMIES = 0); the target's private
// status byte +0x438 bit 0 (isEffectivelyDead); the rowed
// Object::isAbleToAttack 0x00290B73; the rowed
// Object::getAbleToAttackSpecificObject 0x0028D051 with ATTACK_NEW_TARGET 0
// and CMD_FROM_AI 2; result 3 or 2 (POSSIBLE / POSSIBLE_AFTER_MOVING) is
// true. BFME 2 differs from the donor: the attacker id is read once and the
// clearLastAttacker call is gone.
#include "../../Common/GameLogicObjectLookupView.h"
typedef bool Bool;
#define NULL 0
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class BodyModuleInterface : public VSlots<18>
{
public:
	virtual ObjectID getClearableLastAttacker() const = 0;
};
class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Relationship getRelationship(const Object *that) const;
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType cmdSource) const;
private:
	unsigned char m_pad00[0x254];
	BodyModuleInterface *m_body; // +0x254
	unsigned char m_pad258[0x438 - 0x258];
	unsigned char m_privateStatus; // +0x438
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
struct State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
private:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
extern GameLogic *TheGameLogic;

Bool rva005430E7(State *thisState, void * /*userData*/)
{
	Object *obj = thisState->getMachineOwner();
	BodyModuleInterface *bmi = obj ? obj->getBodyModule() : NULL;

	if (!(obj && bmi)) {
		return false;
	}

	ObjectID attacker = bmi->getClearableLastAttacker();
	if (attacker == INVALID_OBJECT_ID) {
		return false;
	}

	Object *target = TheGameLogic->findObjectByID(attacker);
	if (!target) {
		return false;
	}

	if (obj->getRelationship(target) != ENEMIES) {
		return false;
	}

	if (target->isEffectivelyDead()) {
		return false;
	}

	if (!obj->isAbleToAttack()) {
		return false;
	}

	CanAttackResult result = obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, target, CMD_FROM_AI);
	if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING) {
		return true;
	}
	return false;
}
