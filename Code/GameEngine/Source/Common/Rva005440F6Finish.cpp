// cl: /MD
// ?ableToAdvance@AIDockMachine@@SA_NPAUState@@PAX@Z, retail 0x005440F6, 61 bytes.
//
// Target facts: the rowed AIDockMachine ctor 0x005448A1 pushes the .rdata
// condition table 0x00869C78 for state 1, whose only entry is this function
// with target state 2 (then the null terminator); vtable 0x008699A0 slot 2
// returns the name string AIDockMachine. The body takes the state's machine
// (+0x18), its goal object through the rowed getGoalObject 0x004D7726 (pinned
// as StateMachine::getGoalObject) and that object's dock interface through
// the rowed Object::getDockUpdateInterface 0x0028BCB4, then asks interface
// slot 4 with the machine owner (+0x14) and the machine's +0x3C (the dock
// approach position the ctor sets to -1).
// Donor-carried: the name and role are Zero Hour's AIDockMachine::ableToAdvance
// (AIDock.cpp), the condition of AI_DOCK_WAIT_FOR_CLEARANCE leading to
// AI_DOCK_ADVANCE_POSITION; interface slot 4 is ZH's isClearToAdvance.
// The cdecl userData argument is unused, as in Zero Hour.

typedef bool Bool;

class Object;
class DockUpdateInterface;

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
};

class DockUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual unsigned char isClearToAdvance(Object *owner, int position);
};

class StateMachine
{
public:
	Object *getGoalObject();
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18];
};

class AIDockMachine : public StateMachine
{
public:
	static Bool ableToAdvance(struct State *thisState, void *userData);
	int m_approachPosition; // +0x3C
};

struct State
{
	unsigned char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};

Bool AIDockMachine::ableToAdvance(State *thisState, void *userData)
{
	Object *goal = thisState->m_machine->getGoalObject();
	AIDockMachine *machine = (AIDockMachine *)thisState->m_machine;
	bool result;
	if (goal == 0) {
		result = false;
	} else {
		DockUpdateInterface *dock = goal->getDockUpdateInterface();
		if (dock == 0) {
			result = false;
		} else {
			Object *owner = thisState->m_machine->m_owner;
			result = dock->isClearToAdvance(owner, machine->m_approachPosition) != 0;
		}
	}
	return result;
}
