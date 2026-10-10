// cl: /DNDEBUG /MD
//
// Small vtable-slot body with no ledger owner and no Ghidra entry (sized from
// its bytes), batch N. As in VslotSmallBodiesA-M, the class and method are
// address-derived unless the ledger already names them, and model only what
// the body touches. Meanings are not recovered.

// slot 1 of the vtable at VA 0x00BD3A6C (referenced at 0x00BD3A70): stores a
// newly constructed 0x28-byte object (rowed constructor 0x00151866) at +0x14,
// or NULL when the allocation fails. Retail has no unwind frame around the
// construction, so the constructor is declared nothrow here.
class Rva001517DE
{
public:
	Rva001517DE() throw();
private:
	char m_data[0x28];
};
class Rva001518B2
{
public:
	void rva001518B2();
private:
	char m_pad00[0x14];
	Rva001517DE *m_14;
};
void Rva001518B2::rva001518B2()
{
	m_14 = new Rva001517DE;
}

// Installed-vtable pointer-backed predicate. Only the observed accesses
// and native ABI are known; original owner and field meanings are unknown.
struct Rva005CEA3DWord {char prefix[0x18]; int word;};
class Rva005CEA3D {public: bool rva005CEA3D(int value); private: char prefix[8]; Rva005CEA3DWord *entry;};
bool Rva005CEA3D::rva005CEA3D(int value) {return entry->word == value;}


// Native CMP EDX,[EAX+18]: EAX comes from this8 and EDX from the
// stack word. Original owner and field meanings remain unknown.
struct Rva005E574AField {char prefix[0x18]; int word;};
class Rva005E574A {public: bool rva005E574A(int value); private: char prefix[8]; Rva005E574AField *entry;};
bool Rva005E574A::rva005E574A(int value) {return value!=entry->word;}
