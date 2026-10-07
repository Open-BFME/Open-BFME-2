// Two negative-adjust forwarders (8B each): add ecx, -N then tail-jump.
// 0x00330BDB: add ecx, -0x34, jmp 0x0030B706.
// 0x005CEC55: add ecx, -4, jmp 0x005CC788.
// Read as member functions explicitly destroying an object situated below
// this (enclosing/sibling teardown): p->~T() as the sole statement.
// Callee identities unproven (opaque dtor pins); owner names and the
// cleanup reading are address-derived. One ledger row per body.

class Rva0030B706Obj
{
public:
	~Rva0030B706Obj();
};

class Rva005CC788Obj
{
public:
	~Rva005CC788Obj();
};

class Rva00330BDBMid
{
public:
	void cleanup();
};

class Rva005CEC55Mid
{
public:
	void cleanup();
};


void Rva005CEC55Mid::cleanup()
{
	((Rva005CC788Obj *)((char *)this - 4))->~Rva005CC788Obj();
}
