// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport sort<Rva003C3AB0Item**, Rva003C3AB0Cmp> family around 0x003BD4C3-0x003C6973.
// Masked twin of the rowed stlport_sort_rva004ebe74.cpp family: every retail
// comparison loads the pointee's dword at +0x20 and compares signed (jl/jge),
// an inline functor over that field. The 23B forwarder 0x003C3AB0
// (__unguarded_insertion_sort) is called from __final_insertion_sort
// 0x003C6973, and 0x003BD4C3 (__unguarded_linear_insert) from both
// 0x003BE532 and __linear_insert 0x003C4B2D. Pointee and functor keep
// address-derived names; only the +0x20 int key is claimed.
#include <algorithm>

struct Rva003C3AB0Item
{
	char m_pad[0x20];
	int m_20;
};

struct Rva003C3AB0Cmp
{
	bool operator()(const Rva003C3AB0Item *a, const Rva003C3AB0Item *b) const { return a->m_20 < b->m_20; }
};

template void _STL::sort<Rva003C3AB0Item **, Rva003C3AB0Cmp>(Rva003C3AB0Item **, Rva003C3AB0Item **, Rva003C3AB0Cmp);
