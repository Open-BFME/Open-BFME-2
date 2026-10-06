// cl: /O1 /MD
// ??0Rva00545DB0@@QAE@PAVStateMachine@@@Z @ 0x00545DB0 28B
// Derived ctor: base Rva00342EAC plus vtable 0x0086A1F0 and dword 0x54 zero.
// Evidence: retail vtable store plus and [esi+0x54],0; callee row ??0Rva00342EAC@@QAE@PAVStateMachine@@@Z; caller 0x0054605A.
class StateMachine;
class Rva00342EAC
{
public:
	Rva00342EAC(StateMachine *machine);
};
extern const void *const g_00C6A1F0[];
class Rva00545DB0 : public Rva00342EAC
{
public:
	Rva00545DB0(StateMachine *machine);
private:
	char m_pad[0x54 - sizeof(Rva00342EAC)];
	int m_54;
};
Rva00545DB0::Rva00545DB0(StateMachine *machine) : Rva00342EAC(machine)
{
	m_54 = 0;
	*(const void **)this = g_00C6A1F0;
}
