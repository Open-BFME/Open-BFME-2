// cl: /O1 /MD
// ??0Rva00544810@@QAE@PAVStateMachine@@@Z, retail 0x00544810, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x26F20F3B then vtable 0x00C69B10. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x0054494B in 0x005448A1; prev/next
// Rva0054482D same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69B10[];

class Rva00544810 : public AIInternalMoveToState
{
public:
	Rva00544810(StateMachine *machine);
};

Rva00544810::Rva00544810(StateMachine *machine) : AIInternalMoveToState(machine, 0x26F20F3Bu)
{
	*(const void **)this = g_00C69B10;
}
