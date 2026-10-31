// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva00568A20@@QAE@ABV0@@Z @0x00568A20 33B: copy ctor over BfmePoolRef10 base plus int at +4 and byte at +8. Base copy is rowed at 0x00051950. Caller at 0x00568C8F passes dest in ecx with null check.

#include <new.h>

struct BfmePoolHolder88;
class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
};
class HostClass005C8E0A;
class Rva00568A20
{
public:
	Rva00568A20(const Rva00568A20 &o);
	BfmePoolRef10 m_ref;
	HostClass005C8E0A *m_host;
	unsigned char m_byte;
	char m_pad[3];
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00568A20::Rva00568A20(const Rva00568A20 &o) : m_ref(o.m_ref), m_host(o.m_host), m_byte(o.m_byte)
{
}

// ?bfmeAnchorRva00568A20 absent-from-retail
void *bfmeAnchorRva00568A20(void *where, const Rva00568A20 *src)
{
	return new (where) Rva00568A20(*src);
}
