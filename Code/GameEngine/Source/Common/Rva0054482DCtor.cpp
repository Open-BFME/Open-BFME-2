// cl: /MD
// ??0Rva0054482D@@QAE@PAVStateMachine@@@Z, retail 0x0054482D, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x58821EDA then vtable 0x00C69B58. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x0054497B in 0x005448A1; prev/next
// ConstIntGetters4 same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69B58[];

class Rva0054482D : public AIInternalMoveToState
{
public:
	Rva0054482D(StateMachine *machine);
};

Rva0054482D::Rva0054482D(StateMachine *machine) : AIInternalMoveToState(machine, 0x58821EDAu)
{
	*(const void **)this = g_00C69B58;
}
