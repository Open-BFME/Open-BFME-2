// cl: /DNDEBUG /MD
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

class Render2DClass
{
public:
	void Render();
};

class Rva000448C4Forwarder
{
public:
	void rva000448C4();
private:
	char m_lead[0x168];
	Render2DClass *m_target;
};

// vtable 0x00BC3C80#64: (+0x168)->Render (0x0011A040)
void Rva000448C4Forwarder::rva000448C4()
{
	m_target->Render();
}

// Both +0x34 callees are rowed members of BfmeSceneVector (SceneSpatialRescale*.cpp).
struct Rva00141F90Bounds;
class BfmeSceneVector
{
public:
	void rva00141F90(const Rva00141F90Bounds &bounds);	// 0x00141F90
	void Set_Level(UnsignedInt level);			// 0x00142060
};

class Rva001428E0Forwarder
{
public:
	void rva001428E0(Int bounds);
private:
	char m_lead[0x34];
	BfmeSceneVector m_target;
};

// vtable 0x00BC6310#18 (??_7Rva0006EE6F@@6B@): +0x34.rva00141F90
void Rva001428E0Forwarder::rva001428E0(Int bounds)
{
	m_target.rva00141F90(*reinterpret_cast<const Rva00141F90Bounds *>(bounds));
}

class Rva001428F0Forwarder
{
public:
	void rva001428F0(Int level);
private:
	char m_lead[0x34];
	BfmeSceneVector m_target;
};

// vtable 0x00BC6310#19 (??_7Rva0006EE6F@@6B@): +0x34.rva00142060
void Rva001428F0Forwarder::rva001428F0(Int level)
{
	m_target.Set_Level(level);
}

struct Rva002BEECDSubject;
class Rva002BEECD
{
public:
	Bool rva002BEECD(Rva002BEECDSubject *subject);	// rowed 0x002BEECD
};

class Rva002BEF43Forwarder
{
public:
	void rva002BEF43(Int subject);
private:
	char m_lead[0x4];
	Rva002BEECD m_target;
};

// vtable 0x00BFE4F4#1: +0x4.rva002BEECD
void Rva002BEF43Forwarder::rva002BEF43(Int subject)
{
	m_target.rva002BEECD(reinterpret_cast<Rva002BEECDSubject *>(subject));
}

class Gen0058BCD0
{
public:
	void handle(Int a0);
};

class Rva002D4670Forwarder
{
public:
	void rva002D4670(Int a0);
private:
	char m_lead[0x8];
	Gen0058BCD0 m_target;
};

// vtable 0x00C02AEC#1 (??_7Impl002D4594@@6B@): +0x8.handle
void Rva002D4670Forwarder::rva002D4670(Int a0)
{
	m_target.handle(a0);
}

class Rva002D39E5
{
public:
	void handle(Int a0);	// rowed 0x002D39E5
};

class Rva002D4678Forwarder
{
public:
	void rva002D4678(Int a0);
private:
	char m_lead[0x8];
	Rva002D39E5 m_target;
};

// vtable 0x00C02AF4#1 (??_7Impl002D45C9@@6B@): +0x8.rva002D39E5
void Rva002D4678Forwarder::rva002D4678(Int a0)
{
	m_target.handle(a0);
}
