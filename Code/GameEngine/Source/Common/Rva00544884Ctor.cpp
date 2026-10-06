// cl: /MD
// ??0Rva00544884@@QAE@PAVStateMachine@@@Z, retail 0x00544884, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x7EC09A9E then vtable 0x00C69C30. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x00544A0E in 0x005448A1; prev
// 0x00544867 same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69C30[];

class Rva00544884 : public AIInternalMoveToState
{
public:
	Rva00544884(StateMachine *machine);
};

Rva00544884::Rva00544884(StateMachine *machine) : AIInternalMoveToState(machine, 0x7EC09A9Eu)
{
	*(const void **)this = g_00C69C30;
}
