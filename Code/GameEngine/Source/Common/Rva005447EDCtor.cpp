// cl: /MD
// ??0Rva005447ED@@QAE@PAVStateMachine@@@Z, retail 0x005447ED, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x26F20F3B then vtable 0x00869AB0. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x005448E3 in 0x005448A1; prev/next
// ConstIntGetters4 same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69AB0[];

class Rva005447ED : public AIInternalMoveToState
{
public:
	Rva005447ED(StateMachine *machine);
};

Rva005447ED::Rva005447ED(StateMachine *machine) : AIInternalMoveToState(machine, 0x26F20F3Bu)
{
	*(const void **)this = g_00C69AB0;
}
