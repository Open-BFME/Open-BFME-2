// cl: /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner and no Ghidra size, generated
// by tools/slot_forwarders.py (family vjmp). Each body was sized from its
// bytes (a branch-free hop ending in jmp, followed by a known boundary).
// Every class and method here is address-derived: the bytes prove the hop
// and the slot or callee, nothing more. A tail-jumped virtual slot passes
// the caller's arguments through untouched, so its argument count is not
// provable and the slot is declared without arguments (inference).
// A direct callee's argument count comes from its own ret N; an unnamed
// callee is pinned by address in reverse/symbols.csv.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

#include "../../Include/Common/SizedForwarderSlots.h"

class Rva00085B36Lead
{
public:
	virtual void lead0();
private:
	char m_lead[0xB0];
};

class Rva00085B36Forwarder : public Rva00085B36Lead, public SizedForwarderSlots
{
public:
	void rva00085B36();
};

// vtable 0x00BC7568#95: base at +0xB4 ->slot10()
void Rva00085B36Forwarder::rva00085B36()
{
	slot10();
}

class Rva000AF012Forwarder
{
public:
	void rva000AF012();
private:
	char m_lead[0xC];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BC95D8#1: (+0xC)->slot2()
void Rva000AF012Forwarder::rva000AF012()
{
	m_inner->slot2();
}

