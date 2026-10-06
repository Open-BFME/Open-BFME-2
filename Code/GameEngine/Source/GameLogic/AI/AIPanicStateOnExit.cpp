// cl: /DNDEBUG /MD
//
// AIPanicState::onExit, retail 0x0034A4DB (45 bytes).
// Identity: slot 5 of vtable 0x00C12B70 (installed by the unrowed ctor at
// 0x00342D31), whose slot 2 is the rowed name getter 0x00342D3B returning the
// literal AIPanicState; the body is the Zero Hour AIStates.cpp
// AIPanicState::onExit (clear the panicking model condition on the machine
// owner, then chain to AIInternalMoveToState::onExit, rowed at 0x003473A4).
// BFME2 delta: the condition is bit 2*32+13 of the Object+0x10C words (byte
// +0x115 mask 0x20) with the pinned notifier 0x0028AE6D.
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_PANICKING = 2 * 32 + 13
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
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
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
public:
	virtual void onExit(StateExitType status);
};
class AIPanicState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
void AIPanicState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	obj->clearModelConditionState(MODELCONDITION_PANICKING);
	AIInternalMoveToState::onExit(status);
}
