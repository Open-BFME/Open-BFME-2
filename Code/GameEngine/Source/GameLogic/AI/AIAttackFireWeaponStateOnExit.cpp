// cl: /DNDEBUG /MD
//
// AIAttackFireWeaponState::onExit, retail 0x0034B08A (83 bytes): slot 5 of
// vtable 0x00C111F8, whose slot-2 name getter returns AIAttackFireWeaponState.
// Ported from Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// clear the firing-weapon and ignoring-stealth statuses, and cancel a
// pending pre-attack on the current weapon.
// BFME 2 differences (target evidence): the two statuses are cleared one at
// a time through the rowed Object::setStatus (0x0D and 0x1B); the weapon's
// setPreAttackFinishedFrame refreshes its status (the rowed
// Weapon::getStatus) after storing the frame (+0x1C); and status 0x52 is
// cleared at the end.
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_FIRING_WEAPON = 0x0D,
	OBJECT_STATUS_IGNORING_STEALTH = 0x1B,
	OBJECT_STATUS_BFME_52 = 0x52
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponStatus
{
	READY_TO_FIRE = 0,
	PRE_ATTACK = 4
};
#include "../../../Include/GameLogic/Weapon.h"
class Object
{
public:
	void setStatus(ObjectStatusTypes status, Bool set);
	void clearStatus(ObjectStatusTypes status) { setStatus(status, false); }
	Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0);
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
class AIAttackFireWeaponState : public State
{
public:
	virtual void onExit(StateExitType status);
};

//----------------------------------------------------------------------------------------------------------
void AIAttackFireWeaponState::onExit( StateExitType status )
{
	// contained by AIAttackState, so no separate timer
	Object *obj = getMachineOwner();
	obj->clearStatus( OBJECT_STATUS_IS_FIRING_WEAPON );
	obj->clearStatus( OBJECT_STATUS_IGNORING_STEALTH );

	// this can occur if we start a preattack (eg, bayonet)
	// and the target moves out range before we can actually "fire"...
	// leaving us thinking we're still "pre attacking". cancel this state
	// to avoid confusion. (srj)
	Weapon* weapon = obj->getCurrentWeapon();
	if (weapon && weapon->getStatus() == PRE_ATTACK)
	{
		weapon->m_whenPreAttackFinished = 0;
		weapon->getStatus();
	}
	obj->clearStatus( OBJECT_STATUS_BFME_52 );
}
