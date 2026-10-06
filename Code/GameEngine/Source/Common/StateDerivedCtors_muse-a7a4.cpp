// cl: /MD
// Six 29B State-derived ctors calling ??0State@@QAE@PAVStateMachine@@I@Z
// (0x004D73FC, ICF twin of the rowed VAsciiString overload) then installing
// their own vtable. Retail pushes a 4-byte hash (not a string address) with
// no AsciiString construction, hence the unsigned second arg. Vtables and
// hashes from retail bytes; callers are 0x004A7010 fragments.
// 0x004A6933 hash 0xAE77593F vtable 0x00852D70
// 0x004A6BCA hash 0x89496474 vtable 0x00853218
// 0x004A6C13 hash 0x5E8FE5DB vtable 0x00853260
// 0x004A6956 hash 0xC40022B2 vtable 0x00852DE0
// 0x004A6979 hash 0xCAD6313C vtable 0x00852E38
// 0x004A699C hash 0xE6B21889 vtable 0x00852E90

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva004A6933_vftable: matched references place it at VA 0xc52d70 (retail .rdata value 7).
extern "C" char Rva004A6933_vftable = 7;
// Rva004A6BCA_vftable: matched references place it at VA 0xc53218 (retail .rdata value 7).
extern "C" char Rva004A6BCA_vftable = 7;
// Rva004A6C13_vftable: matched references place it at VA 0xc53260 (retail .rdata value 7).
extern "C" char Rva004A6C13_vftable = 7;
// Rva004A6956_vftable: matched references place it at VA 0xc52de0 (retail .rdata value 7).
extern "C" char Rva004A6956_vftable = 7;
// Rva004A6979_vftable: matched references place it at VA 0xc52e38 (retail .rdata value 7).
extern "C" char Rva004A6979_vftable = 7;
// Rva004A699C_vftable: matched references place it at VA 0xc52e90 (retail .rdata value 7).
extern "C" char Rva004A699C_vftable = 7;

class __declspec(novtable) Rva004A6933 : public State
{
public:
	Rva004A6933(StateMachine *machine);
	virtual ~Rva004A6933();
};

class __declspec(novtable) Rva004A6BCA : public State
{
public:
	Rva004A6BCA(StateMachine *machine);
	virtual ~Rva004A6BCA();
};

class __declspec(novtable) Rva004A6C13 : public State
{
public:
	Rva004A6C13(StateMachine *machine);
	virtual ~Rva004A6C13();
};

class __declspec(novtable) Rva004A6956 : public State
{
public:
	Rva004A6956(StateMachine *machine);
	virtual ~Rva004A6956();
};

class __declspec(novtable) Rva004A6979 : public State
{
public:
	Rva004A6979(StateMachine *machine);
	virtual ~Rva004A6979();
};

class __declspec(novtable) Rva004A699C : public State
{
public:
	Rva004A699C(StateMachine *machine);
	virtual ~Rva004A699C();
};

Rva004A6933::Rva004A6933(StateMachine *machine) : State(machine, 0xAE77593Fu)
{
	*reinterpret_cast<char **>(this) = &Rva004A6933_vftable;
}

Rva004A6BCA::Rva004A6BCA(StateMachine *machine) : State(machine, 0x89496474u)
{
	*reinterpret_cast<char **>(this) = &Rva004A6BCA_vftable;
}

Rva004A6C13::Rva004A6C13(StateMachine *machine) : State(machine, 0x5E8FE5DBu)
{
	*reinterpret_cast<char **>(this) = &Rva004A6C13_vftable;
}

Rva004A6956::Rva004A6956(StateMachine *machine) : State(machine, 0xC40022B2u)
{
	*reinterpret_cast<char **>(this) = &Rva004A6956_vftable;
}

Rva004A6979::Rva004A6979(StateMachine *machine) : State(machine, 0xCAD6313Cu)
{
	*reinterpret_cast<char **>(this) = &Rva004A6979_vftable;
}

Rva004A699C::Rva004A699C(StateMachine *machine) : State(machine, 0xE6B21889u)
{
	*reinterpret_cast<char **>(this) = &Rva004A699C_vftable;
}
