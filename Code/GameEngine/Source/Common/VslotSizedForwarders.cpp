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

class MilesAudioManager : public SizedForwarderSlots
{
public:
	virtual void rva000512BC();
};

// vtable 0x00BC55B0#96: this->slot94()
void MilesAudioManager::rva000512BC()
{
	slot94();
}

class Rva0008BD2BLead
{
public:
	virtual void lead0();
private:
	char m_lead[0x24C4];
};

class Rva0008BD2BForwarder : public Rva0008BD2BLead, public SizedForwarderSlots
{
public:
	void rva0008BD2B();
};

// vtable 0x00BC7568#138: base at +0x24C8 ->slot20()
void Rva0008BD2BForwarder::rva0008BD2B()
{
	slot20();
}

class Rva00091D32Forwarder
{
public:
	void rva00091D32();
private:
	char m_lead[0x14];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BC80A0#5: (+0x14)->slot132()
void Rva00091D32Forwarder::rva00091D32()
{
	m_inner->slot132();
}

// Slot 0 of the one-slot table 0x00BC957C that ??0Rva000ABD56 installs; the
// vptr is the old +0 pad.
class Rva000ABD56
{
public:
	virtual void rva000ABD68();
private:
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BC957C#0 (??_7Rva000ABD56@@6B@): (+0x4)->slot3()
void Rva000ABD56::rva000ABD68()
{
	m_inner->slot3();
}

class Rva0029AC98Forwarder : public SizedForwarderSlots
{
public:
	void rva0029AC98();
};

// vtable 0x00BC7A88#83: this->slot67()
void Rva0029AC98Forwarder::rva0029AC98()
{
	slot67();
}

class Rva0030ADE8Forwarder : public SizedForwarderSlots
{
public:
	void rva0030ADE8();
};

// vtable 0x00BC8318#1 (??_7Rva00985E4@@6B@): this->slot14()
void Rva0030ADE8Forwarder::rva0030ADE8()
{
	slot14();
}

class Rva00328CC5Forwarder
{
public:
	void rva00328CC5();
private:
	char m_lead[0x18];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00C0D8D8#2: (+0x18)->slot0()
void Rva00328CC5Forwarder::rva00328CC5()
{
	m_inner->slot0();
}

class Rva00328CCCForwarder
{
public:
	void rva00328CCC();
private:
	char m_lead[0xC];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00C0D8E4#2: (+0xC)->slot1()
void Rva00328CCCForwarder::rva00328CCC()
{
	m_inner->slot1();
}

