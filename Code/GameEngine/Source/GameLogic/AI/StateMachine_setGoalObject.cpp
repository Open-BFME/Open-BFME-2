// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// ?setGoalObject@StateMachine@@UAEXPBVObject@@@Z at retail 0x004D750F (14B).
// Zero Hour's StateMachine::setGoalObject: the locked guard, then a tail-jmp to
// ?internalSetGoalObject@StateMachine@@QAEXPBVObject@@@Z 0x004D7435.
// Evidence: cmp byte [ecx+0x38] (m_locked per StateMachineGoal layout) then jmp to the
// rowed worker; the body is slot 14 (offset 0x38) of StateMachine's vtable 0x00860740
// and of the 24 other vtables that keep it, the slot the StateMachine view
// (reference/shims/bfme2_statemachine/StateMachineView.h) declares virtual
// setGoalObject(const Object *).

class Object;

#include "../../../Include/Common/StateMachineClass.h"

void StateMachine::setGoalObject(const Object *obj)
{
	if (m_locked)
		return;
	internalSetGoalObject(obj);
}
