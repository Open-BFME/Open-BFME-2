// cl: /EHsc /DNDEBUG /MD
//
// ??0Rva004E7392@@QAE@ABV0@@Z @0x004E7392 39B: copy constructor (caller
// 0x004E74C1). It copies the state-free polymorphic base through its
// out-of-line copy 0x004E72C0 (Rva004E72C0Copy.cpp), installs vtable
// 0x00BFD010 and copies the two plain fields at +4 and +8. Identities are
// address-derived.

struct Rva004E72C0
{
	Rva004E72C0(const Rva004E72C0 &other);
	Rva004E72C0();
	virtual ~Rva004E72C0();
};
// ??0Rva004E72C0@@QAE@XZ @0x0029B1E1 9B: the default constructor, storing the
// class's own vtable (VA 0x00BFCFF8) and returning this.
Rva004E72C0::Rva004E72C0()
{
}

struct Rva004E7392 : Rva004E72C0
{
	Rva004E7392(const Rva004E7392 &other);
	virtual ~Rva004E7392();

	int m_04;
	int m_08;
};

Rva004E7392::Rva004E7392(const Rva004E7392 &other) :
	Rva004E72C0(other),
	m_04(other.m_04),
	m_08(other.m_08)
{
}
