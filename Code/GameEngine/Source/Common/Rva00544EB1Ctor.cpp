// cl: /MD
// ??0Rva00544EB1@@QAE@PAVStateMachine@@@Z, retail 0x00544EB1, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x29E75AEF then vtable 0x00C69E08. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x00544F16; prev 0x00544E3B same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69E08[];

class Rva00544EB1 : public AIInternalMoveToState
{
public:
	Rva00544EB1(StateMachine *machine);
};

Rva00544EB1::Rva00544EB1(StateMachine *machine) : AIInternalMoveToState(machine, 0x29E75AEFu)
{
	*(const void **)this = g_00C69E08;
}
