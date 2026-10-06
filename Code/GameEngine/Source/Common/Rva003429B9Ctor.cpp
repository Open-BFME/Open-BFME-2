// cl: /MD /EHsc
// ??0Rva003429B9@@QAE@PAVStateMachine@@@Z @0x003429B9 59B: AIInternalMoveToState-derived ctor, hash 0xFA014ECE, vtable 0x008126C0, floats 0x4C 0x50 0x54 zero via movss plus 0x58 zero plus bytes 0x5C 0 0x5D 1.
// Donor Code/GameEngine/Source/GameLogic/AI/AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Callers 0x00343417 unclaimed.
class StateMachine;
struct Coord3D
{
	float x, y, z;
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva003429B9 : public AIInternalMoveToState
{
public:
	Rva003429B9(StateMachine *machine);
private:
	float m_4C;
	float m_50;
	float m_54;
	int m_58;
	bool m_5C;
	bool m_5D;
};
Rva003429B9::Rva003429B9(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xFA014ECEu)
{
	m_4C = 0.0f;
	m_50 = 0.0f;
	m_54 = 0.0f;
	_ReadWriteBarrier();
	m_58 = 0;
	m_5C = false;
	m_5D = true;
}
