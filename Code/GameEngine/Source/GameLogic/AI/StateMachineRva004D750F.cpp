// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// ?rva004D750F@StateMachine@@QAEXPAVObject@@@Z at retail 0x004D750F (14B).
// Locked-guard tail-jmp to ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z 0x004D7435.
// Evidence: cmp byte [ecx+0x38] (m_locked per StateMachineGoal layout) then jmp to rowed
// setGoalObject; vtable slot 14 (offset 0x38) of 20 Rva004D759C-derived vtables;
// callees all rowed; callers in 0x00344xxx and 0x00350xxx plus vtable jmp.

class Object;

class StateMachine
{
public:
	unsigned char m_pad00[0x38]; // +0x00..0x37 (vtable placeholder + members)
	bool m_locked; // +0x38

	void setGoalObject(Object *obj);
	void rva004D750F(Object *obj);
};

void StateMachine::rva004D750F(Object *obj)
{
	if (m_locked)
		return;
	setGoalObject(obj);
}
