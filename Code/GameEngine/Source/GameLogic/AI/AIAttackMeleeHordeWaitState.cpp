// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 575ba2b04 AIAttackMeleeHordeWaitState_update.cpp is the primary
// semantic donor. Native344F57..345076287B and WBE11AE0 independently
// name onEnter; target C10F40 namegetter/xfer/exit corroborate owner.
// Member18 machine, machine14 owner, wait20, Object contain250,
// kind93, Horde slots77/85/89/90 and3*frame-rate delay are target facts.
// Reuse actual target providers; names of formation/memberID carried from
// donor, while exact interpretation of Object74 remains unresolved.
typedef bool Bool;typedef unsigned UnsignedInt;
#include "../../../Include/Common/StateMachineClass.h"
enum ObjectStatusTypes {OBJECT_STATUS_26=0x26};
class Object;class Thing;
bool rva00344EB2Gate(Object *,Thing *);
#include "../../../Include/GameLogic/Module/HordeContainInterface.h"
#include "../../../Include/GameLogic/Module/ContainModule.h"
struct TargetTemplate {char pad00[0x113];unsigned char kinds113;};
class Object {public:
 bool testStatus(ObjectStatusTypes)const;
 Object *rva002931F5(bool);
 int rva0028B511()const;
 float rva00263763(const void *)const;
 ContainModuleInterface *getContain()const{return m_contain;}
 UnsignedInt getMeleeFormation()const{return m_meleeFormation;}
 bool hasTargetKind93()const{return (m_template->kinds113&0x20)!=0;}
 void *vtable;TargetTemplate *m_template;
 char pad08[0x74-8];UnsignedInt m_meleeFormation;
 char pad78[0x250-0x78];ContainModuleInterface *m_contain;
};
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
class AIAttackMeleeHordeWaitState {public:
 virtual ~AIAttackMeleeHordeWaitState();
 virtual void slot1();
 virtual const char *name()const;
 virtual void slot3();
 virtual StateReturnType onEnter();
 virtual void onExit(int);
 virtual StateReturnType update();
 virtual void slot7();
 private:char pad04[0x18-4];StateMachine *m_machine;char pad1C[4];UnsignedInt m_waitUntil;};
StateReturnType AIAttackMeleeHordeWaitState::onEnter()
{
	Object *attacker = m_machine->m_owner;
	if (m_machine->isGoalObjectDestroyed())
		return STATE_SUCCESS;

	Object *candidateVictim = m_machine->getGoalObject();
	if (candidateVictim == 0)
		return STATE_SUCCESS;

	ContainModuleInterface *containModule = attacker->getContain();
	if (containModule != 0)
	{
		HordeContainInterface *owningHorde = containModule->slot31();
		if (owningHorde == 0)
			return STATE_SUCCESS;

		// The machine goal is the initial candidate; successful horde resolution
		// changes the object used by the readiness check and melee commands.
		unsigned int selectedMeleeFormation = candidateVictim->getMeleeFormation();
		if (candidateVictim->testStatus(OBJECT_STATUS_26))
		{
			Object *resolvedMember = candidateVictim->rva002931F5(false);
			if (resolvedMember != 0)
			{
				selectedMeleeFormation = resolvedMember->getMeleeFormation();
				candidateVictim = resolvedMember;
			}
		}

		// This formation follows the candidate unless resolution supplies a member.
		// Predicate true selects failure; false can be an early-out, not validation.
		if (rva00344EB2Gate(attacker,(Thing*)candidateVictim))
			return STATE_FAILURE;

		if (!owningHorde->isMeleeTargetReady(candidateVictim))
		{
			int maximumDistance = 40;
			// This target template kind93 is distinct from status26
			// used by the target resolver above.
			if (candidateVictim->hasTargetKind93() &&
				attacker->rva0028B511() != 1)
				maximumDistance = 60;

			if (attacker->rva00263763(candidateVictim) <
				(float)(maximumDistance * maximumDistance))
				owningHorde->prepareMeleeTarget(candidateVictim);
			else
				return STATE_FAILURE;
		}

		owningHorde->setMeleeFormation(selectedMeleeFormation);
		m_waitUntil = TheGameLogic->getFrame() + BfmeLogicFramesPerSecond*3;
		owningHorde->beginMelee(candidateVictim);
	}

	return STATE_CONTINUE;
}

