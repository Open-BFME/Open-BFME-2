// cl: /DNDEBUG /MD /EHsc
// ??0Rva00342843@@QAE@PAVStateMachine@@@Z @0x00342843 37B
// AIInternalMoveToState-derived ctor, hash 0x5106D8AC, vtable 0x008124D8,
// dword 0x4C zero via and plus byte 0x50 zero. Recipe from landed precedent
// Rva00342B87Ctor.cpp (33B, same base + vtable + 0x4C shape) plus byte-zero
// member like Rva003429B9Ctor.cpp. Donor AIStatesSmallUpdates.cpp
// AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Evidence: base pin 0x0033F279 AIInternalMoveToState ctor; caller 0x00351D8C.
class StateMachine;
#include "../../../Libraries/Include/Lib/Coord3D.h"
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
class Rva00342843 : public AIInternalMoveToState
{
public:
	Rva00342843(StateMachine *machine);
private:
	int m_4C;
	bool m_50;
};
Rva00342843::Rva00342843(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x5106D8ACu)
{
	m_4C = 0;
	m_50 = false;
}
