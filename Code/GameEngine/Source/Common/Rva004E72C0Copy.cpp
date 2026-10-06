// cl: /EHsc /DNDEBUG /MD
//
// ??0Rva004E72C0@@QAE@ABV0@@Z @0x004E72C0 11B: copy constructor of a
// state-free polymorphic base; it only installs vtable 0x00BFCFF8. Its one
// caller is the derived copy constructor 0x004E7392 (Rva004E7392Copy.cpp),
// which then installs the derived vtable 0x00BFD010. Identity is
// address-derived.

struct Rva004E72C0
{
	Rva004E72C0(const Rva004E72C0 &other);
	virtual ~Rva004E72C0();
};

Rva004E72C0::Rva004E72C0(const Rva004E72C0 &)
{
}
