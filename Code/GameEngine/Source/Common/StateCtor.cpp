// cl: /MD
// ??0State@@QAE@PAVStateMachine@@VAsciiString@@@Z at retail 0x004D73FC (43B).
// Base State ctor: three INVALID_STATE_IDs (999999), owner machine, vector
// homes zeroed, base vtable. BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/Common/StateMachine.cpp
// State::State(StateMachine *machine, AsciiString name) verbatim minus debug
// (name unused in release, hence ret 8 with second arg untouched). Vtable
// 0x008605D8 overwritten by 40+ derived State ctors (0x004A6933 0x004A6BCA
// 0x004A6C13 plus 0x0033Fxxx family); callees none (leaf, gate-ready).
//
// BFME2 derived ctors push a name hash where the BFME1 donor passed the
// AsciiString; the hash signature is the pinned ICF twin of this body at
// 0x004D73FC and is defined below as well so that the two derived ctors of
// this TU (retail 0x004D7491 and 0x004D74AC, 27 bytes each, adjacent to the
// base) see the base body: cl then keeps this in edx across the base call,
// as retail does (the same ctors compiled elsewhere spend push/pop esi, 29
// bytes). Honest address names: hashes 0xC17A0A70 and 0xDF4D3EB3, vtables
// 0x00860668 and 0x008606B0, callers 0x00343A39 / 0x00346F79.

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class StateMachine;

class AsciiString
{
public:
	void *m_data;
};

// State_vftable: matched references place it at VA 0xc605d8 (retail .rdata value -3).
extern "C" char State_vftable = -3;

class __declspec(novtable) State : public Snapshot
{
public:
	State(StateMachine *machine, AsciiString name);
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

	int m_id; // +0x04
	int m_successStateID; // +0x08
	int m_failureStateID; // +0x0C
	void *m_transitionsFirst; // +0x10
	void *m_transitionsLast; // +0x14
	StateMachine *m_machine; // +0x18
	bool m_tail1C; // +0x1C
};

// The State ctor installs VA 0x00C605D8. Its first native slot is the
// deleting destructor at RVA 0x004A10FD, which calls 0x0049B47C before
// testing the delete flag. That complete body resets the shared Snapshot
// vptr to VA 0x00BBB554. The released base has no additional owned fields;
// use the canonical Snapshot definition so both bytes and binding agree.
State::~State() {}

State::State(StateMachine *machine, AsciiString name)
{
	m_id = 999999;
	m_successStateID = 999999;
	m_failureStateID = 999999;
	m_machine = machine;
	*reinterpret_cast<char **>(this) = &State_vftable;
	m_tail1C = false;
	m_transitionsFirst = 0;
	m_transitionsLast = 0;
}

State::State(StateMachine *machine, unsigned int hash)
{
	m_id = 999999;
	m_successStateID = 999999;
	m_failureStateID = 999999;
	m_machine = machine;
	*reinterpret_cast<char **>(this) = &State_vftable;
	m_tail1C = false;
	m_transitionsFirst = 0;
	m_transitionsLast = 0;
}

// Rva004D7491_vftable: matched references place it at VA 0xc60668 (retail .rdata value -3).
extern "C" char Rva004D7491_vftable = -3;
// Rva004D74AC_vftable: matched references place it at VA 0xc606b0 (retail .rdata value -3).
extern "C" char Rva004D74AC_vftable = -3;

class __declspec(novtable) Rva004D7491 : public State
{
public:
	Rva004D7491(StateMachine *machine);
	virtual ~Rva004D7491();
};

class __declspec(novtable) Rva004D74AC : public State
{
public:
	Rva004D74AC(StateMachine *machine);
	virtual ~Rva004D74AC();
};

// ??0Rva004D7491@@QAE@PAVStateMachine@@@Z
Rva004D7491::Rva004D7491(StateMachine *machine) : State(machine, 0xC17A0A70u)
{
	*reinterpret_cast<char **>(this) = &Rva004D7491_vftable;
}

// ??0Rva004D74AC@@QAE@PAVStateMachine@@@Z
Rva004D74AC::Rva004D74AC(StateMachine *machine) : State(machine, 0xDF4D3EB3u)
{
	*reinterpret_cast<char **>(this) = &Rva004D74AC_vftable;
}
