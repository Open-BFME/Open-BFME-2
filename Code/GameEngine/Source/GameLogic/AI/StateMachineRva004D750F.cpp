// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// ?setGoalObject@StateMachine@@UAEXPBVObject@@@Z at retail 0x004D750F (14B): slot 14
// of StateMachine's vtable 0x00C60740 (and of the 20 derived machine tables), named
// virtual setGoalObject(const Object *) by Zero Hour and the canonical view.
// Evidence: cmp byte [ecx+0x38] (m_locked per StateMachineGoal layout) then a tail jmp
// to the storing worker 0x004D7435, rowed under the BFME1 donor spelling
// ?setGoalObject@StateMachine@@QAEXPAVObject@@@Z (Zero Hour's internalSetGoalObject).
// Direct callers in 0x00344xxx and 0x00350xxx reach it as a qualified call.

class Object;

class StateMachine
{
public:
	virtual ~StateMachine();
	void setGoalObject(Object *obj);
	virtual void setGoalObject(const Object *obj);

private:
	unsigned char m_pad04[0x38 - 0x04]; // +0x04..0x37
	bool m_locked; // +0x38
};

void StateMachine::setGoalObject(const Object *obj)
{
	if (m_locked)
		return;
	setGoalObject(const_cast<Object *>(obj));
}
