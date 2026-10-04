// ??0SupplyTruckStateMachine@@QAE@PAVObject@@@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /MD /EHsc
// class-gate: allow AsciiString 4-byte trivial view to pass VAsciiString by value to rowed base 0x004D79E1 with no copy-ctor call like the base TU's own view
// ??0SupplyTruckStateMachine@@QAE@PAVObject@@@Z
// partial score=0.96 date=2026-09-30
// ??0SupplyTruckStateMachine@@QAE@PAVObject@@@Z @0x004A7010 373B
// StateMachine-derived ctor: base Rva004D759C(owner, hash F95C8C34, false),
// vtable 0x008532A8, then six 0x20 State news with defineState ids
// 1,0,2,3,4,5 and conds C53330/C53390/C53360/C53330/C53300/C53300.
// Evidence: unlock packet (all callees rowed), caller SupplyTruckAIUpdate
// ctor 0x004A71A1 news 0x3C then calls here, callees Rva004D759C base,
// six Rva004A6xxx State ctors, defineState, operator new.
class Object;
class AsciiString
{
public:
	AsciiString(unsigned int h) : m_data((void *)h) {}
	void *m_data;
};
class Rva004D759C
{
public:
	Rva004D759C(Object *owner, unsigned int nameHash, bool flag);
	virtual ~Rva004D759C();
};
struct State;
struct StateConditionInfo
{
	void *m_test;
	unsigned int m_toState;
	void *m_userData;
};
class StateMachine
{
public:
	void defineState(unsigned int id, State *state, unsigned int success, unsigned int failure, const StateConditionInfo *conds);
};
class Rva004A6BCA
{
public:
	Rva004A6BCA(StateMachine *m);
	virtual ~Rva004A6BCA();
	char m_pad[0x20 - 4];
};
class Rva004A6C13
{
public:
	Rva004A6C13(StateMachine *m);
	virtual ~Rva004A6C13();
	char m_pad[0x20 - 4];
};
class Rva004A6933
{
public:
	Rva004A6933(StateMachine *m);
	virtual ~Rva004A6933();
	char m_pad[0x20 - 4];
};
class Rva004A6956
{
public:
	Rva004A6956(StateMachine *m);
	virtual ~Rva004A6956();
	char m_pad[0x20 - 4];
};
class Rva004A6979
{
public:
	Rva004A6979(StateMachine *m);
	virtual ~Rva004A6979();
	char m_pad[0x20 - 4];
};
class Rva004A699C
{
public:
	Rva004A699C(StateMachine *m);
	virtual ~Rva004A699C();
	char m_pad[0x20 - 4];
};
void *__cdecl operator new(unsigned int size) throw();
extern const void *const g_00C532A8[];
extern const StateConditionInfo g_00C53330[];
extern const StateConditionInfo g_00C53390[];
extern const StateConditionInfo g_00C53360[];
extern const StateConditionInfo g_00C53300[];
class __declspec(novtable) SupplyTruckStateMachine : public Rva004D759C
{
public:
	SupplyTruckStateMachine(Object *owner);
	virtual ~SupplyTruckStateMachine();
	char m_pad[0x3C - 4];
};
// ??0SupplyTruckStateMachine@@QAE@PAVObject@@@Z present-unmatched
SupplyTruckStateMachine::SupplyTruckStateMachine(Object *owner) : Rva004D759C(owner, 0xF95C8C34u, false)
{
	*(const void **)this = g_00C532A8;
	StateMachine *machine = (StateMachine *)this;
	machine->defineState(1, (State *)new Rva004A6BCA(machine), 1, 1, g_00C53330);
	machine->defineState(0, (State *)new Rva004A6C13(machine), 1, 1, g_00C53390);
	machine->defineState(2, (State *)new Rva004A6933(machine), 1, 3, g_00C53360);
	machine->defineState(3, (State *)new Rva004A6956(machine), 2, 1, g_00C53330);
	machine->defineState(4, (State *)new Rva004A6979(machine), 1, 1, g_00C53300);
	machine->defineState(5, (State *)new Rva004A699C(machine), 1, 1, g_00C53300);
}
