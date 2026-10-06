// cl: /MD
// ??0Rva0054484A@@QAE@PAVStateMachine@@@Z, retail 0x0054484A, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x493559EF then vtable 0x00C69BA0. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x005449AC in 0x005448A1; prev
// 0x0054482D same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69BA0[];

class Rva0054484A : public AIInternalMoveToState
{
public:
	Rva0054484A(StateMachine *machine);
};

Rva0054484A::Rva0054484A(StateMachine *machine) : AIInternalMoveToState(machine, 0x493559EFu)
{
	*(const void **)this = g_00C69BA0;
}
