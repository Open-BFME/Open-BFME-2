// cl: /MD
// ??0Rva004A9947@@QAE@PAVStateMachine@@@Z @0x004A9947 29B: derived State ctor pushing name hash 0x83242288.
// Evidence: unlock lane; callee rowed 0x004D73FC State hash overload via its pinned ICF twin; caller 0x004A9DF2;
// vtable 0x00854010; recipe from StateCtor.cpp whose header notes this 29B push-pop-esi form is what the same
// source compiles to elsewhere (that TU keeps this in edx for 27B because the base body is visible there).
class StateMachine;

class __declspec(novtable) State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva004A9947_vftable: retail vtable at VA 0x00854010; gate DIR32-fills the store like the StateCtor.cpp tables.
extern "C" char Rva004A9947_vftable = -3;

class __declspec(novtable) Rva004A9947 : public State
{
public:
	Rva004A9947(StateMachine *machine);
	virtual ~Rva004A9947();
};

Rva004A9947::Rva004A9947(StateMachine *machine) : State(machine, 0x83242288u)
{
	*reinterpret_cast<char **>(this) = &Rva004A9947_vftable;
}
