// cl: /O1 /G7 /EHsc /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport sort<Rva00588195Elem*> (default less) family, 0x00587490-0x005881DA:
// sort 0x00588195 and the 19 helpers it instantiates. The element is a
// 12-byte record ordered by the float at +0 (every comparison is a single
// comiss on that slot); record and fields keep address-derived names.
// Evidence: all 20 bodies place uniquely by masked search in
// 0x587000-0x588400 from one explicit instantiation of the two-argument sort
// of the vendored header and reach one another by REL32. The two-argument
// form is what retail's sort is: it pushes a dword it already holds for the
// empty less<> temporary and keeps an ebp frame, which the comparator-taking
// overload does not reproduce. swap and copy_backward fold onto the rowed
// 12-byte bodies at 0x004219CD and 0x0051C94D; compiled with those rows' own
// flags they are byte-identical there and are pinned as aliases. The
// record's operator< also matches 19 bytes at 0x0058722A, but nothing calls
// that address, so it is not rowed.
#include <algorithm>

struct Rva00588195Elem
{
	float m_key;
	unsigned int m_04;
	unsigned int m_08;
	bool operator<(const Rva00588195Elem &other) const { return m_key < other.m_key; }
};

// ??$sort@PAURva00588195Elem@@@_STL@@YAXPAURva00588195Elem@@0@Z @0x00588195 and its callees
template void _STL::sort<Rva00588195Elem *>(Rva00588195Elem *, Rva00588195Elem *);
