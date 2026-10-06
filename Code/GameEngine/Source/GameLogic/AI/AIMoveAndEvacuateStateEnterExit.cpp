// cl: /DNDEBUG /MD
//
// AIMoveAndEvacuateState::onEnter, retail 0x0034EB7E (106 bytes), and
// AIMoveAndEvacuateState::onExit, retail 0x00349FD0 (37 bytes): slots 4 and
// 5 of vtable 0x00C12C28, whose slot-2 name getter returns
// AIMoveAndEvacuateState (slot 6 is the rowed update 0x00353C27). Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// BFME2 layout (target evidence): machine lock byte +0x38, machine goal
// position +0x24, owner position +0x38; state goal +0x20, adjusts-destination
// +0x48 (setAdjustsDestination logs "CritterDesync" under the global log flag)
// and m_origin +0x4C. getGoalObject and setGoalPosition are pinned StateMachine
// callees; the base onEnter/onExit are pinned AIInternalMoveToState bodies.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};
struct Coord3D
{
	Real x, y, z;
};
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void setGoalPosition(const Coord3D *pos);
	void lock(const char *msg) { m_locked = true; }
	void unlock() { m_locked = false; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
	unsigned char m_pad30[0x38 - 0x30];
	Bool m_locked; // +0x38
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
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	__forceinline void setAdjustsDestination(Bool b)
	{
		if (b)
		{
			if (g_00E03745)
			{
				FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
				if (log)
					fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 49");
			}
		}
		else
		{
			if (g_00E03745)
			{
				FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
				if (log)
					fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 56");
			}
		}
		m_adjustsDestination = b;
	}
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	Bool m_adjustsDestination; // +0x48
};
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	Coord3D m_origin; // +0x4C
};

StateReturnType AIMoveAndEvacuateState::onEnter()
{
	Object *obj = getMachineOwner();

	getMachine()->lock("AIMoveAndEvacuateState::onEnter");		// This state is not user interruptable.

	m_origin = *obj->getPosition();
	setAdjustsDestination(true);

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	return AIInternalMoveToState::onEnter();
}

void AIMoveAndEvacuateState::onExit( StateExitType status )
{
	getMachine()->unlock();
	getMachine()->setGoalPosition(&m_origin); // In case we follow with a AIMoveAndDeleteState.
	AIInternalMoveToState::onExit( status );
}
