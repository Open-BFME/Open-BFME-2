// cl: /DNDEBUG /MD /EHsc
// ??0Rva00342B87@@QAE@PAVStateMachine@@@Z @0x00342B87 33B: AIInternalMoveToState-derived ctor, hash 0x67979DC4, vtable 0x008128D0, dword 0x4C zero via and.
// Donor Code/GameEngine/Source/GameLogic/AI/AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Callers 0x0034B9C5 0x0034C75E 0x00352887 0x00368056 unclaimed.
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
class Rva00342B87 : public AIInternalMoveToState
{
public:
	Rva00342B87(StateMachine *machine);
private:
	int m_4C;
};
Rva00342B87::Rva00342B87(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x67979DC4u)
{
	m_4C = 0;
}
