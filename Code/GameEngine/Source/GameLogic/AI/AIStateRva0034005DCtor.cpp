// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0Rva0034005D@@QAE@PAVStateMachine@@@Z @ 0x0034005D (33B): ctor of unknown
// AI state with vtable 0x00811EB8. Target evidence: stores vtable then byte 1
// at +0x4C and returns this with ret 4. Calls pinned base
// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@I@Z at 0x0033F279 with hash
// 0x6e6fe691. Base layout and flags copied from AIStatesSmallUpdates.cpp.
// Callers include 0x00346CDD which chains this as its base.
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
struct Coord3D
{
	Real x, y, z;
};
class StateMachine;
class Xfer;
class State
{
public:
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
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	Bool m_adjustsDestination; // +0x48
};
class Rva0034005D : public AIInternalMoveToState
{
public:
	Rva0034005D(StateMachine *machine);
private:
	Bool m_unk4C; // +0x4C
};
Rva0034005D::Rva0034005D(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x6e6fe691u)
	, m_unk4C(true)
{
}

// ??0Rva003400CE@@QAE@PAVStateMachine@@@Z @ 0x003400CE (37B): another
// AIInternalMoveToState-derived state (pinned base 0x0033F279, hash
// 0xf0a7ff17), vtable 0x00811F00; zeroes a dword at +0x4C and a byte at
// +0x50, ret 4.
class Rva003400CE : public AIInternalMoveToState
{
public:
	Rva003400CE(StateMachine *machine);
private:
	int m_4C; // +0x4C
	Bool m_50; // +0x50
};
Rva003400CE::Rva003400CE(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xf0a7ff17u)
	, m_4C(0)
	, m_50(false)
{
}
