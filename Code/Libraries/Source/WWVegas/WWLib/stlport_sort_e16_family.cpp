// cl: /GX-
// stlport
// STLport sort<Rva005B2FDCItem*, Rva005B26CEItemCmp> family over the 16-byte
// record of stlport_sort_e16_partition.cpp, 0x005B28BD-0x005B4653: sort
// 0x005B4610 and the helpers it instantiates, plus the out-of-line
// copy_backward 0x005B3644 its __linear_insert calls. The median 0x005B282E
// and partition 0x005B2FDC were already rowed there as hand-written free
// functions; the template bodies below compile byte-identical at both, so the
// template names are pinned there as aliases rather than rowed twice.
//
// The comparator is called as a thiscall functor on record references. Its
// only body is the rowed stdcall Rva005B26CELess at 0x005B26CE; a const
// operator() with that statement over references compiles byte-identical
// there, so it is pinned as a twin (the existing Rva005B26CECmp pin is the
// void-pointer spelling the partition uses). swap folds onto the rowed 16-byte
// swap at 0x005B2893 and __copy_backward_ptrs onto the BfmeE16 row at
// 0x005B2B1E, both byte-identical under these flags. /GX- (the Keyframe and
// StringLookUp sort units' flags) is what keeps copy_backward calling its
// pointer helper out of line as retail does.
#include <algorithm>

struct Rva005B2FDCItem
{
	unsigned int w[4];
};

struct Rva005B26CEItemCmp
{
	bool operator()(const Rva005B2FDCItem &a, const Rva005B2FDCItem &b) const;
};

// ??$sort@PAURva005B2FDCItem@@URva005B26CEItemCmp@@@_STL@@YAXPAURva005B2FDCItem@@0URva005B26CEItemCmp@@@Z @0x005B4610 and its callees
template void _STL::sort<Rva005B2FDCItem *, Rva005B26CEItemCmp>(Rva005B2FDCItem *, Rva005B2FDCItem *, Rva005B26CEItemCmp);
