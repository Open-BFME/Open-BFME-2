// cl: /MD
// ??0Rva00544867@@QAE@PAVStateMachine@@@Z, retail 0x00544867, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0xDAF68697 then vtable 0x00C69BE8. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x00544A3E in 0x005448A1; prev
// 0x0054484A same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

extern const void *const g_00C69BE8[];

class Rva00544867 : public AIInternalMoveToState
{
public:
	Rva00544867(StateMachine *machine);
};

Rva00544867::Rva00544867(StateMachine *machine) : AIInternalMoveToState(machine, 0xDAF68697u)
{
	*(const void **)this = g_00C69BE8;
}
