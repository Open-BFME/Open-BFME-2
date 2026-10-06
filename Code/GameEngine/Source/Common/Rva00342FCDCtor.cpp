// cl: /MD
//
// ??0Rva00342FCD@@QAE@PAVStateMachine@@H@Z, retail 0x00342FCD, 37 bytes.
// Chain from 0x0033FE65 (Rva0033FE65 ctor). Derived ctor forwarding
// (machine, 0) to base Rva0033FE65 then storing arg2 at +0x28 then
// installing vtable 0x00812FA0 then zeroing byte at +0x2C. Callers
// 0x003527F3/0x00352823/0x00352855. Layout is base 0x28 plus int plus bool.
// Uses novtable plus explicit store to get store-before-vtable order like
// the State hash ctors.

class StateMachine;

class Rva0033FE65
{
public:
	Rva0033FE65(StateMachine *machine, int val);
	virtual ~Rva0033FE65();

private:
	char m_pad04[0x28 - 0x04];
};

// Rva00342FCD_vftable: matched references place it at VA 0xc12fa0 (retail .rdata value 7).
extern "C" char Rva00342FCD_vftable = 7;

class __declspec(novtable) Rva00342FCD : public Rva0033FE65
{
public:
	Rva00342FCD(StateMachine *machine, int val);

private:
	int m_28;
	bool m_2C;
};

Rva00342FCD::Rva00342FCD(StateMachine *machine, int val) : Rva0033FE65(machine, 0)
{
	m_28 = val;
	*reinterpret_cast<char **>(this) = &Rva00342FCD_vftable;
	m_2C = false;
}
