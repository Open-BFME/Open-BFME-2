// cl: /DNDEBUG /MD /EHsc
// ??0AttackPositionHordeStateMachine@@QAE@PAVObject@@HI@Z @0x00343A86 295B.
// Name is a scalar hash: factory 34B1E9 pushes an immediate key, with no
// string construction or destruction. Keep the established host-word view.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// StateMachine base from (owner, name, 0), installs its vftable 0x00811CF0
// (shared with the destructor 0x0033FBB7, whose unit names the class from
// the slot 2 getter 0x0033FC04), then four
// new-expression state blocks into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). The zero lives in
// esi and is recycled into 0x2BC; 0x2C0/0x2BE trade through ebx; the 0x270F
// pair rides transient ecx.
class Object;
class State;
struct StateConditionInfo;

#include "../../../Include/Common/StateMachineClass.h"


class AIAttackApproachTargetState00C12678
{
public:
	AIAttackApproachTargetState00C12678(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x64 - 4];
};

class Rva0033F460
{
public:
	Rva0033F460(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class Rva0033F4B1
{
public:
	Rva0033F4B1(StateMachine *machine, int arg0);
private:
	void *m_vtbl;
	char m_pad[0x28 - 4];
};

class AttackPositionHordeStateMachine : public StateMachine
{
public:
	AttackPositionHordeStateMachine(Object *owner, int x, unsigned int name);
	virtual ~AttackPositionHordeStateMachine();
};

AttackPositionHordeStateMachine::AttackPositionHordeStateMachine(Object *owner, int x, unsigned int name)
	: StateMachine(owner, name, false)
{
	AIAttackApproachTargetState00C12678 *s0 = new AIAttackApproachTargetState00C12678((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2BC, (State *)s0, 0x2BD, 0x2C0, (const StateConditionInfo *)0);
	Rva0033F460 *s1 = new Rva0033F460((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2C0, (State *)s1, 0x270F, 0x270F, (const StateConditionInfo *)0);
	Rva0033F4B1 *s2 = new Rva0033F4B1((StateMachine *)this, x != 0 ? x + 0x20 : 0);
	((StateMachine *)this)->defineState(0x2BD, (State *)s2, 0x2BE, 0x2BC, (const StateConditionInfo *)0);
	Rva0033F460 *s3 = new Rva0033F460((StateMachine *)this);
	((StateMachine *)this)->defineState(0x2BE, (State *)s3, 0x2BC, 0x2BC, (const StateConditionInfo *)0);
}
