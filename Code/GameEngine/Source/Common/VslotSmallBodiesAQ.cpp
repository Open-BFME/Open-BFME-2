// cl: /DNDEBUG /MD
//
// Vtable-slot bodies with no ledger owner and no Ghidra entry, batch AQ:
// each calls an unrowed Ghidra-listed function on the complete object (or
// on this object) and drops its one argument; the callees are pinned in
// reverse/symbols.csv under address-derived names (no-argument thiscall,
// plain ret). Classes are address-derived.

typedef int Int;

// 0x00082E12 (interface at +0x08) and 0x005E19BF (interface at +0x0C): the
// pinned 0x00082D6A resp. 0x005E1928 of the complete object.
class Rva00082D6A
{
public:
	virtual void primarySlot();
	void rva00082D6A();
private:
	Int m_04;
};
class Rva00082E12Iface
{
public:
	virtual void rva00082E12(Int unused) = 0;
};
class Rva00082E12 : public Rva00082D6A, public Rva00082E12Iface
{
public:
	void rva00082E12(Int unused);
};
void Rva00082E12::rva00082E12(Int)
{
	rva00082D6A();
}
class Rva005E1928
{
public:
	virtual void primarySlot();
	void rva005E1928();
private:
	Int m_04;
	Int m_08;
};
class Rva005E19BFIface
{
public:
	virtual void rva005E19BF(Int unused) = 0;
};
class Rva005E19BF : public Rva005E1928, public Rva005E19BFIface
{
public:
	void rva005E19BF(Int unused);
};
void Rva005E19BF::rva005E19BF(Int)
{
	rva005E1928();
}

// 0x005CC24C: the pinned 0x005CC23B of this object.
// The target writes AL on both branches; keep its return type bool despite
// the existing void pin. Only the byte at +0x0C is established by this body.
extern void ToggleQuitMenu();
class Rva005CC23B
{
public:
	bool rva005CC23B();
private:
	char m_pad[0xC];
	unsigned char m_enabled;
};
class Rva005CC24C : public Rva005CC23B
{
public:
	void rva005CC24C(Int unused);
};
bool Rva005CC23B::rva005CC23B()
{
	if (m_enabled) {
		ToggleQuitMenu();
		return true;
	}
	return false;
}
void Rva005CC24C::rva005CC24C(Int)
{
	rva005CC23B();
}
