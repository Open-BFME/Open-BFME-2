// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Table-reached bodies from .text gaps no ledger row covers (seat-3 batch G;
// see GapBodiesS3A.cpp). Retail bytes establish every shape; owning classes
// are not recovered unless a callee names them, so each keeps an
// address-derived name and a view of only the members it touches.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

// --- 0x00343EFA (144B): a turret-state predicate: the machine's owner (+0x14)
// and goal object exist, the owner's template enables it (+0x5FD), the goal is
// not busy (+0x274), the owner's AI (+0x258) has a turret for its current
// weapon, TheAI's data enables it (+0x8C), the owner is controlled by a
// player of type 1, the rowed Object 0x0029493F check (mode 2) passes and the
// template lacks flag 0x10 of byte +0x113.
class Player;
class AI;
extern AI *TheAI;

enum WhichTurretType { TURRET_INVALID = -1 };

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;	// 0x0026275E
};

struct Rva00343EFATemplateView
{
	char m_pad000[0x113];
	unsigned char m_113;									// +0x113
	char m_pad114[0x5FD - 0x114];
	bool m_useCrushAttack;												// +0x5FD
};

struct Rva00343EFAPlayerView
{
	char m_pad[0x5C];
	int m_type;												// +0x5C
};

class Object
{
public:
	Player *getControllingPlayer() const;					// 0x0028AFA9
	bool rva0029493F(Object *other, int mode);				// 0x0029493F
	int m_00;
	Rva00343EFATemplateView *m_template;					// +0x04
	char m_pad008[0x258 - 8];
	AIUpdateInterface *m_ai;								// +0x258
	char m_pad25C[0x274 - 0x25C];
	int m_274;												// +0x274
};

class TurretStateMachine
{
public:
	Object *getGoalObject();								// 0x004D7726
	char m_pad[0x14];
	Object *m_owner;										// +0x14
	Object *getOwner() const { return m_owner; }
};

struct Rva00343EFAState
{
	char m_pad[0x18];
	TurretStateMachine *m_machine;							// +0x18
};

struct Rva00343EFAAIData
{
	char m_pad[0x8C];
	bool m_aiCrushesInfantry;												// +0x8C
};

struct Rva00343EFAAIView
{
	char m_pad[0x18];
	Rva00343EFAAIData *m_data;								// +0x18
};

bool wantToSquishTarget(Rva00343EFAState *state)
{
	Object *owner = state->m_machine->getOwner();
	Object *goal = state->m_machine->getGoalObject();
	if (owner && goal &&
			owner->m_template->m_useCrushAttack &&
			goal->m_274 == 0 &&
			owner->m_ai &&
			owner->m_ai->getWhichTurretForCurWeapon() != TURRET_INVALID &&
			((Rva00343EFAAIView *)TheAI)->m_data->m_aiCrushesInfantry &&
			owner->getControllingPlayer() &&
			((Rva00343EFAPlayerView *)owner->getControllingPlayer())->m_type == 1 &&
			owner->rva0029493F(goal, 2) &&
			!(owner->m_template->m_113 & 0x10))
		return true;
	return false;
}
