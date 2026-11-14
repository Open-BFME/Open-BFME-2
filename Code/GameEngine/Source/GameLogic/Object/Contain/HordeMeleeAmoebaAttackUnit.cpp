// cl: /O1 /DNDEBUG /MD
// stlport
// HordeMeleeAmoeba::AttackUnit, retail 0x00587253 (74 bytes):
// ?AttackUnit@HordeMeleeAmoeba@@QAEXPAVObject@@0@Z
// Identity (target): WorldBuilder's debug HordeMeleeAmoeba.cpp:618..624
// HordeMeleeAmoeba::AttackUnit asserts the attacker's AI, its current
// weapon and weapon->isMeleeWeapon(), then calls the AI's 0x0026D3FB with
// the victim, Object::rva0028CDB6 and the AI's slot 0x220, as retail does.
// Layout (target): Object AI at +0x258; the melee flag is the rowed byte
// getter 0x002C9400 on the weapon's template (+0x04).
class Object;

#include "../../../../Include/Common/Rva002C9400ByteField.h"

class Weapon
{
public:
	bool isMeleeWeapon() const { return m_template->get() != 0; }

private:
	unsigned char m_pad00[0x04];
	const Rva002C9400ByteField *m_template; // +0x04
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../object.h"

#include "../../../../Include/GameLogic/HordeMeleeAmoeba.h"

void HordeMeleeAmoeba::AttackUnit(Object *attacker, Object *victim)
{
	AIUpdateInterface *ai = attacker->getAI();
	if (!ai)
		return;
	const Weapon *weapon = attacker->getCurrentWeapon(0);
	if (!weapon)
		return;
	if (!weapon->isMeleeWeapon())
		return;
	ai->rva0026D3FB(victim);
	attacker->rva0028CDB6();
	ai->setLocomotorGoalNone();
}
// Native22B cdecl wrapper at58723D. The direct987B callee operates on
// two Object pointers and returns the selected Object* (or null) in EAX.
// The original wrapper and pathfinder-member names remain unknown.
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;
Object *Rva0058723D(Object *unit,Object *current)
{
 return TheAI->pathfinder()->rva002F14F9(unit,current);
}

