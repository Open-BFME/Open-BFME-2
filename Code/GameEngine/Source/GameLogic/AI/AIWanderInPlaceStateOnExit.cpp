// cl: /DNDEBUG /MD
//
// AIWanderInPlaceState::onExit, retail 0x0034A364 (42 bytes): slot 5 of vtable
// 0x00C12AC8, whose slot-2 name getter returns AIWanderInPlaceState and whose
// slot 3 is the rowed AIWanderInPlaceState::xfer 0x003411BD. Zero Hour's
// AIStates.cpp onExit runs only the base onExit; BFME2 (target evidence) then
// restores the normal locomotor set through AIUpdateInterface vslot 142
// (+0x238, chooseLocomotorSet as in the ZH onEnter's LOCOMOTORSET_WANDER call
// at the same slot) when the owner (+0x14 of the machine +0x18) has an AI
// (+0x258). The base onExit is the pinned AIInternalMoveToState body.
typedef bool Bool;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_WANDER = 3
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x258];
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
	virtual StateReturnType update();
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
class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

void AIWanderInPlaceState::onExit( StateExitType status )
{
	AIInternalMoveToState::onExit( status );
	AIUpdateInterface *ai = getMachineOwner()->getAI();
	if (ai) {
		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
	}
}
