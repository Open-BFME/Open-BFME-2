// cl: /O1 /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner and no Ghidra size, generated
// by tools/slot_forwarders.py (family djmp). Each body was sized from its
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

class RadiusDecal
{
public:
	void clear();
};

class Rva000B333DForwarder
{
public:
	void rva000B333D();
private:
	char m_lead[0x218];
	RadiusDecal m_target;
};

// vtable 0x00BCBC40#34 (??_7Rva000CA119@@6BRva000C79C9@@@): +0x218.clear
void Rva000B333DForwarder::rva000B333D()
{
	m_target.clear();
}

class Rva002D3AB5Target
{
public:
	void rva002D3AB5(Int a0);
};

class Rva002D4680Forwarder
{
public:
	void rva002D4680(Int a0);
private:
	char m_lead[0x8];
	Rva002D3AB5Target m_target;
};

// vtable 0x00C02AFC#1 (??_7Impl002D45FE@@6B@): +0x8.rva002D3AB5
void Rva002D4680Forwarder::rva002D4680(Int a0)
{
	m_target.rva002D3AB5(a0);
}

class Rva002D54E5Target
{
public:
	void rva002D54E5();
};

class Rva002D55CAForwarder
{
public:
	void rva002D55CA();
private:
	char m_lead[0x10];
	Rva002D54E5Target *m_target;
};

// vtable 0x00C02AA8#1 (??_7Rva002D3573@@6BGameEngineDeletingBase@@@): (+0x10)->rva002D54E5
void Rva002D55CAForwarder::rva002D55CA()
{
	m_target->rva002D54E5();
}

class Rva002D65F6Target
{
public:
	void rva002D65F6();
};

class Rva002D6AE2Forwarder
{
public:
	void rva002D6AE2();
private:
	char m_lead[0x10];
	Rva002D65F6Target *m_target;
};

// vtable 0x00C02AA8#10 (??_7Rva002D3573@@6BGameEngineDeletingBase@@@): (+0x10)->rva002D65F6
void Rva002D6AE2Forwarder::rva002D6AE2()
{
	m_target->rva002D65F6();
}
