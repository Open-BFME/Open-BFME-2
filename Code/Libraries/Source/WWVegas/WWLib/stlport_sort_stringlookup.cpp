// cl: /GX-
// stlport
// STLport sort<StringLookUp*, Rva002E5678Cmp> family, 0x002E5B66-0x002E68EB:
// the GameText label table sort (StringLookUp is the 8-byte {label, info}
// record of the landed GameTextStringLookUpLess.cpp). sort 0x002E68A9 and the
// 19 helpers it instantiates all place uniquely by masked search in
// 0x2E5600-0x2E6A00 from one explicit sort instantiation of the vendored
// header (the 23B forwarders split by callee) and reach one another by
// REL32. The comparator is called as a thiscall functor on the two records'
// addresses; its only body is the rowed stdcall compareStringLookUpLess at
// 0x002E5678, which a thiscall operator() with the same statement compiles to
// byte for byte (the this pointer is unused), so the functor is pinned there
// under an address-derived name. swap and copy_backward fold onto the rowed
// 8-byte bodies at 0x005A9125 and 0x004C72FE; under these flags (the same as
// the Keyframe sort family's) both compile byte-identical to them and are
// pinned as aliases. Under /EHsc the vendored copy_backward inlines its
// pointer helper instead, which is why the unit keeps /GX-.
#include <algorithm>

class AsciiString;

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

struct Rva002E5678Cmp
{
	bool operator()(const StringLookUp &a, const StringLookUp &b) const;
};

// ??$sort@PAUStringLookUp@@URva002E5678Cmp@@@_STL@@YAXPAUStringLookUp@@0URva002E5678Cmp@@@Z @0x002E68A9 and its callees
template void _STL::sort<StringLookUp *, Rva002E5678Cmp>(StringLookUp *, StringLookUp *, Rva002E5678Cmp);
