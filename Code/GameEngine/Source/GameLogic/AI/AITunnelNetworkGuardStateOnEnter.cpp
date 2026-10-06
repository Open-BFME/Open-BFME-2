// cl: /DNDEBUG /MD /EHsc
//
// AITunnelNetworkGuardState::onEnter, retail 0x00342086 (154 bytes): slot 4
// of vtable 0x00C11850, whose slot-2 name getter returns
// AITunnelNetworkGuardState. Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): a new AITNGuardMachine (rowed ctor
// 0x00546001) over the owner, given the AI's guard location (vslot 118) and
// guard mode (vslot 125), then initDefaultState (machine vslot 7) and, unless
// that fails, setState(AI_GUARD_RETURN = 5003) (vslot 8).
// Layout (target evidence): m_guardMachine +0x20; the TN guard machine keeps
// its position to guard at +0x3C and its guard mode at +0x4C; sizeof 0x50.
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum
{
	AI_GUARD_RETURN = 5003
};
enum GuardMode
{
	GUARDMODE_NORMAL = 0
};
struct Coord3D
{
	Real x, y, z;
};
class Object;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AIUpdateInterface : public VSlots<118>
{
public:
	virtual const Coord3D *getGuardLocation(void) const = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual void slot123() = 0;
	virtual void slot124() = 0;
	virtual GuardMode getGuardMode(void) const = 0;
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
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(StateID newStateID);
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AITNGuardMachine : public StateMachine
{
public:
	AITNGuardMachine(Object *owner);
	void setTargetPositionToGuard(const Coord3D *pos) { m_positionToGuard = *pos; }
	void setGuardMode(GuardMode guardMode) { m_guardMode = guardMode; }
private:
	unsigned char m_pad18[0x3C - 0x18];
	Coord3D m_positionToGuard; // +0x3C
	unsigned char m_pad48[0x4C - 0x48];
	GuardMode m_guardMode; // +0x4C
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AITunnelNetworkGuardState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	AITNGuardMachine *m_guardMachine; // +0x20
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AITunnelNetworkGuardState::onEnter()
{

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardMachine = new AITNGuardMachine( getMachineOwner());

	// tell the guarding machine what it is guarding with
	m_guardMachine->setTargetPositionToGuard( ai->getGuardLocation() ); 
	m_guardMachine->setGuardMode(ai->getGuardMode());

	// now that essential parameters are set, set the machine's initial state
	if (m_guardMachine->initDefaultState() == STATE_FAILURE) 
		return STATE_FAILURE;
	return m_guardMachine->setState(AI_GUARD_RETURN);
}
