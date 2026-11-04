// cl: /O1 /DNDEBUG /MD
// ?privateGuardRetaliate@AIUpdateInterface@@MAEXPAVObject@@PBUCoord3D@@HW4CommandSourceType@@@Z
//
// retail 0x00267DF1 (85 bytes). Chain lane: calls rowed 0x00265667 with own
// pos plus flag, so every callee is resolved. Guard on first arg, three
// StateMachine virtuals (slots 5, 14, 8 with 62), field +0x48 takes flag,
// then rowed Object::getCurrentWeapon(0) and write third arg to weapon+0x34.
// Evidence: vtable slot 66 of AIUpdate derivatives; layout (+8 object,
// +0x30 machine) plus this-call into AIUpdateInterface::rva00265667 shared with
// sibling TU Rva00263910Goal.cpp.
// Identity: WorldBuilder's AIUpdate.cpp:7496 asserts in
// AIUpdateInterface::privateGuardRetaliate, whose body makes the same
// machine calls (clear, setGoalObject at slot 14, goal set, setState 62) then
// getCurrentWeapon and setMaxShotCount; Zero Hour's privateGuardRetaliate
// (victim, pos, maxShotsToFire, cmdSource) has the same sequence, and it is
// the aiDoCommand handler PrivateCommands declares at this slot.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"


#include "../../../../../Include/Common/StateMachineClass.h"

#include "../../../../../Include/GameLogic/Weapon.h"

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

#include "../../object.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../../Include/GameLogic/AIStateMachineClass.h"

void AIUpdateInterface::privateGuardRetaliate(Object *victim, const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource)
{
	if (victim == 0)
		return;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	rva00265667(pos, cmdSource);
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(62);
	const Weapon *weapon = m_object->getCurrentWeapon((WeaponSlotType *)0);
	if (weapon == 0)
		return;
	const_cast<Weapon *>(weapon)->m_maxShotCount = maxShotsToFire;
}
