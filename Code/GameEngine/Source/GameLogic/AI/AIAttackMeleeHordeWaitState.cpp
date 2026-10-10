// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1 575ba2b04 AIAttackMeleeHordeWaitState_update.cpp is the primary
// semantic donor. Native344F57..345076287B and WBE11AE0 independently
// name onEnter; target C10F40 namegetter/xfer/exit corroborate owner.
// Member18 machine, machine14 owner, wait20, Object contain250,
// kind93, Horde slots77/85/89/90 and3*frame-rate delay are target facts.
// Reuse actual target providers; names of formation/memberID carried from
// donor, while exact interpretation of Object74 remains unresolved.
typedef bool Bool;typedef unsigned UnsignedInt;
enum StateReturnType {STATE_CONTINUE=0,STATE_SUCCESS=-1,STATE_FAILURE=-2};
enum ObjectStatusTypes {OBJECT_STATUS_26=0x26};
class Object;class Thing;
bool rva00344EB2Gate(Object *,Thing *);
class TurretStateMachine {public:bool rva004D7ADD();};
class StateMachine {public:Object *getGoalObject();char pad00[0x14];Object *m_owner;};
class HordeContainInterface {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void beginMelee(Object *);
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual bool isMeleeTargetReady(Object *);
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void prepareMeleeTarget(Object *);
 virtual void setMeleeFormation(unsigned);
};
class ContainModuleInterface {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual HordeContainInterface *getHordeContainInterface();
};
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
extern int g_Va00DBA4E4;
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
	if (((TurretStateMachine *)m_machine)->rva004D7ADD())
		return STATE_SUCCESS;

	Object *candidateVictim = m_machine->getGoalObject();
	if (candidateVictim == 0)
		return STATE_SUCCESS;

	ContainModuleInterface *containModule = attacker->getContain();
	if (containModule != 0)
	{
		HordeContainInterface *owningHorde = containModule->getHordeContainInterface();
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
		m_waitUntil = TheGameLogic->getFrame() + g_Va00DBA4E4*3;
		owningHorde->beginMelee(candidateVictim);
	}

	return STATE_CONTINUE;
}

