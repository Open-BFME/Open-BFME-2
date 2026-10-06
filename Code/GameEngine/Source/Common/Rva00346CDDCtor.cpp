// cl: /MD
// ??0Rva00346CDD@@QAE@PAVStateMachine@@@Z, retail 0x00346CDD, 24 bytes.
// Evidence: calls rowed base ??0Rva0034005D@@QAE@PAVStateMachine@@@Z and stores
// vtable g_00C136A0, ret 4 single StateMachine arg. Vtable slot unknown.
class StateMachine;
class Rva0034005D
{
public:
	Rva0034005D(StateMachine *machine);
};
extern const void *const g_00C136A0[];
class Rva00346CDD : public Rva0034005D
{
public:
	Rva00346CDD(StateMachine *machine);
};
Rva00346CDD::Rva00346CDD(StateMachine *machine)
	: Rva0034005D(machine)
{
	*(const void **)this = g_00C136A0;
}
