// cl: /DNDEBUG /MD
//
// AIWanderState::onExit, retail 0x0034A323 (65 bytes): slot 5 of vtable
// 0x00C12A70, whose slot-2 name getter returns AIWanderState. It starts with
// the Zero Hour body (chain to AIFollowWaypointPathState::onExit, rowed
// 0x0034A0D7); BFME2 then clears model condition 4*32+2 on the owner
// (Object+0x10C words, notifier 0x0028AE6D) and passes 0 to the owner AI's
// vslot 142 (+0x238) without a null check.
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
template <int N> class AIWanderStateAISlots : public AIWanderStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIWanderStateAISlots<0>
{
};
// AIUpdateInterface: vslot 142 (+0x238) takes one argument.
class AIUpdateInterface : public AIWanderStateAISlots<142>
{
public:
	virtual void rva0034A323Slot142(int value) = 0;
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
};
class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
class AIWanderState : public AIFollowWaypointPathState
{
public:
	virtual void onExit(StateExitType status);
};
void AIWanderState::onExit(StateExitType status)
{
	AIFollowWaypointPathState::onExit(status);
	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->clearModelConditionState(4 * 32 + 2);
		Object::getAI(obj)->rva0034A323Slot142(0);
	}
}
