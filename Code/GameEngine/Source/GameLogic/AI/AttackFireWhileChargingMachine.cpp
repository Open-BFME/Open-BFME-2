// cl: /DNDEBUG /MD /EHsc
// ??0AttackFireWhileChargingMachine@@QAE@PAVObject@@HI_N@Z @0x00343838 115B.
// Name is a scalar hash: factory 34B1E9 pushes an immediate key, with no
// string construction or destruction. Keep the established host-word view.
// StateMachine-family ctor (thiscall, four params): base-constructs the rowed
// StateMachine base from (owner, name, flag), installs its vftable 0x00811C30
// (shared with the destructor 0x0033FB95, whose unit names the class from
// the slot 2 getter 0x0033FBA0), then one
// new-expression state block into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). Too few constants
// to keep ebx, so the zeros ride as immediates and the dead state reset
// takes whatever bl holds.
#include "../../../Include/Common/StateMachineClass.h"

// Rowed 0x00343042 as AIChargeTargetState::AIChargeTargetState (AIStateRva0034005DCtor.cpp).
class AIChargeTargetState
{
public:
	AIChargeTargetState(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x58 - 4];
};

class AttackFireWhileChargingMachine : public StateMachine
{
public:
	AttackFireWhileChargingMachine(Object *owner, int u, unsigned int name, bool flag);
	virtual ~AttackFireWhileChargingMachine();
};

AttackFireWhileChargingMachine::AttackFireWhileChargingMachine(Object *owner, int u, unsigned int name, bool flag)
	: StateMachine(owner, name, flag)
{
	(void)u;
	AIChargeTargetState *aIChargeTargetState = new AIChargeTargetState((StateMachine *)this);
	((StateMachine *)this)->defineState(0, (State *)aIChargeTargetState, 0x270E, 0x270F, (const StateConditionInfo *)0);
}
