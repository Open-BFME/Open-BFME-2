// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<Rva004EBE74Item**, Rva004EBE74Cmp> family, 0x004EABEA-0x004EBEB7:
// sort 0x004EBE74 (sole caller 0x004EBEDE) and the 19 helpers it instantiates.
// The element is a pointer; every comparison in retail loads the pointee's
// unsigned dword at +0x50 and compares unsigned (jae/jb), which is an inline
// functor over that field; pointee and functor keep address-derived names.
// Evidence: all 20 bodies place uniquely by masked search in 0x4EA800-0x4EC000
// from one explicit sort instantiation of the vendored header (the 23B
// forwarders split by callee) and reach one another by REL32. The functor's
// out-of-line operator() also matches 21 bytes at 0x004EAB8A, but nothing
// calls that address and no function starts there, so it is not rowed.
#include <algorithm>

struct Rva004EBE74Item
{
	char m_pad[0x50];
	unsigned int m_50;
};

struct Rva004EBE74Cmp
{
	bool operator()(const Rva004EBE74Item *a, const Rva004EBE74Item *b) const { return a->m_50 < b->m_50; }
};

// ??$sort@PAPAURva004EBE74Item@@URva004EBE74Cmp@@@_STL@@YAXPAPAURva004EBE74Item@@0URva004EBE74Cmp@@@Z @0x004EBE74 and its callees
template void _STL::sort<Rva004EBE74Item **, Rva004EBE74Cmp>(Rva004EBE74Item **, Rva004EBE74Item **, Rva004EBE74Cmp);
