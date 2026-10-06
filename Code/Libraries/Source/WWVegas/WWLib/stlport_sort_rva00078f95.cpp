// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<Rva00078F95Item**, Rva00078F95Cmp> family: sort 0x0007A3BE and
// every helper it instantiates, 0x0007921F-0x0007A400. The element is a
// pointer (4-byte stride, compared by value through the thiscall comparator
// whose 380B body at 0x00078F95 orders the pointees by the dword at +4, then
// by further fields); comparator and pointee keep address-derived names, the
// comparator is pinned, not rowed. Evidence: all 20 bodies place uniquely by
// masked search in 0x78F00-0x7A500 from one explicit sort instantiation of
// the vendored header (the two 23B forwarders split by their callees), each
// reaches the next by REL32, and the comparator's 12 call sites are exactly
// the ones inside these bodies. Sole caller of sort: 0x0007A43F.
#include <algorithm>

struct Rva00078F95Item;

struct Rva00078F95Cmp
{
	bool operator()(const Rva00078F95Item *a, const Rva00078F95Item *b) const;
};

// ??$sort@PAPAURva00078F95Item@@URva00078F95Cmp@@@_STL@@YAXPAPAURva00078F95Item@@0URva00078F95Cmp@@@Z @0x0007A3BE and its callees
template void _STL::sort<Rva00078F95Item **, Rva00078F95Cmp>(Rva00078F95Item **, Rva00078F95Item **, Rva00078F95Cmp);
