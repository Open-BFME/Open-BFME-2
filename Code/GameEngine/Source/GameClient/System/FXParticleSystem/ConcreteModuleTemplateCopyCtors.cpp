// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Concrete module template copy constructors (retail 0x003AEB9C cluster).
// Each 45-byte wrapper delegates to its module's 91-byte template copy
// (rowed through the ledger) and installs its own four vftables. All vftable
// dwords are DIR32 sites the gate takes from the target; the call resolves
// through the ledger.

class Rva003AEBC9
{
public:
	Rva003AEBC9(const Rva003AEBC9 &other);
};

extern "C" char Rva003AEB9C_v0;
extern "C" char Rva003AEB9C_v14;
extern "C" char Rva003AEB9C_v18;
extern "C" char Rva003AEB9C_v1c;

class Rva003AEB9C
{
public:
	__declspec(noinline) Rva003AEB9C(const Rva003AEB9C &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the template copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
};

// ??0Rva003AEB9C@@QAE@ABV0@@Z
Rva003AEB9C::Rva003AEB9C(const Rva003AEB9C &that)
{
	const void *src = &that;
	((Rva003AEBC9 *)this)->Rva003AEBC9::Rva003AEBC9(*(const Rva003AEBC9 *)src);
	*(void **)this = &Rva003AEB9C_v0;
	*(void **)((char *)this + 0x14) = &Rva003AEB9C_v14;
	*(void **)((char *)this + 0x18) = &Rva003AEB9C_v18;
	*(void **)((char *)this + 0x1C) = &Rva003AEB9C_v1c;
}
