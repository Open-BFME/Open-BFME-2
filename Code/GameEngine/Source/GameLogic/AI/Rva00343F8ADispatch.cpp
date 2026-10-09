// cl: /DNDEBUG /MD
//
// ?rva00343F8A@@YAXPAVRva00343F8A@@PAX@Z @0x00343F8A 38B.
//
// Goal-test dispatcher (cdecl): fetches the machine goal via rowed
// getGoalObject 0x004D7726 on the +0x18 StateMachine and routes the
// (state, opaque) pair to 0x00343DD8 when a goal exists, else to
// 0x0033FD98. The latter is rowed as a bool predicate in
// Rva0033FD98OutOfRange.cpp; this dispatcher discards its result.
// The state class mirrors only the proven +0x18 machine slot.
class Object;
class StateMachine
{
public:
	Object *getGoalObject();
};
class Rva00343F8A
{
public:
	char m_pad00[0x18];
	StateMachine *m_machine; // +0x18
};
void rva00343DD8(Rva00343F8A *st, void *arg);
bool rva0033FD98(Rva00343F8A *st, void *arg);

void rva00343F8A(Rva00343F8A *st, void *arg2)
{
	if (st->m_machine->getGoalObject() != 0)
		rva00343DD8(st, arg2);
	else
		rva0033FD98(st, arg2);
}

// Retail 33FDD6..33FDEB is an independent 21B cdecl wrapper after the
// rowed 62B predicate and before the distinct 33FDEB prologue. It forwards
// both stack arguments and inverts AL. The table at 813188 contains this
// callback with transition ID 601 and null user data. Original name unknown.
bool rva0033FDD6(Rva00343F8A *st, void *arg)
{
	return !rva0033FD98(st, arg);
}
