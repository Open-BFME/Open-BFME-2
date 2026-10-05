// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch K. As in VslotSmallBodiesA-J, each class and method
// is address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the .rdata slot address(es)
// that reference it. Meanings are not recovered.

#include "ascii_string.h"

// slots at VA 0x00BC82BC and 0x00BC82F8: copies the global string at VA
// 0x00E01CF0 over the one at VA 0x00E01CF4 (inline AsciiString assignment,
// the rowed StringBase<char>::set).
extern AsciiString g_rva00318A95Source;
extern AsciiString g_rva00318A95Target;
class Rva00318A95
{
public:
	void rva00318A95();
};
void Rva00318A95::rva00318A95()
{
	g_rva00318A95Target = g_rva00318A95Source;
}

// slot at VA 0x00C548F4: returns a copy of the global value at VA
// 0x00E030D0 (rowed copy constructor 0x002CF0F0).
class BfmeFixedStorage002CF0F0
{
public:
	BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);
private:
	int m_00;
};
extern BfmeFixedStorage002CF0F0 g_rva004AB9D5Value;
class Rva004AB9D5
{
public:
	BfmeFixedStorage002CF0F0 rva004AB9D5();
};
BfmeFixedStorage002CF0F0 Rva004AB9D5::rva004AB9D5()
{
	return g_rva004AB9D5Value;
}
