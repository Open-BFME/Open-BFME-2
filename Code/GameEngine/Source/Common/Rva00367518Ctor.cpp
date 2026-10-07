// cl: /O1 /arch:SSE /G7 /MD
//
// ??0Rva00367518@@QAE@PAVStateMachine@@@Z @ 0x00367518 (33B): ctor of unknown
// AI state with vtable 0x008172B8. Target evidence: stores vtable then zeroes
// dword at +0x58 and returns this with ret 4. Calls rowed base
// ??0AIFollowPathState@@QAE@PAVStateMachine@@I@Z at 0x00342D41 with hash
// 0x5d5fa789. Base layout copied from AIStateRva0034005DCtor.cpp. Caller
// at 0x00367C6E in 0x0036792F.
#include "../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
class StateMachine;
class Xfer;
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	Real m_2C;
	int m_30;
	Coord3D m_pathGoalPosition; // +0x34
	int m_goalLayer; // +0x40
	int m_44;
	Bool m_adjustsDestination; // +0x48
	Bool m_49;
	Bool m_4A;
	Bool m_4B;
};
class AIFollowPathState : public AIInternalMoveToState
{
public:
	AIFollowPathState(StateMachine *machine, unsigned int hash);
	virtual ~AIFollowPathState();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	int m_4C;
	Bool m_50;
	Bool m_51;
	int m_54;
};
class Rva00367518 : public AIFollowPathState
{
public:
	Rva00367518(StateMachine *machine);
private:
	int m_58; // +0x58
};
Rva00367518::Rva00367518(StateMachine *machine)
	: AIFollowPathState(machine, 0x5d5fa789u)
	, m_58(0)
{
}
