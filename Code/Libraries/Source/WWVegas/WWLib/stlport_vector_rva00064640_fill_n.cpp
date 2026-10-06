// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAVRva00064640Record@@IV1@@_STL@@YAPAVRva00064640Record@@PAV1@IABV1@ABU__false_type@0@@Z 0x00469CC8 37B evidence: 0x1c-stride fill via rowed _Construct 0x469C73 caller 0x4701B6 record layout from copy ctor 0x50403D
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class Rva00064640Record {
public:
	Rva00064640Record();
	Rva00064640Record(const Rva00064640Record &other);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};
namespace _STL {
template <> void _Construct<Rva00064640Record, Rva00064640Record>(Rva00064640Record *, const Rva00064640Record &);
template Rva00064640Record *__uninitialized_fill_n<Rva00064640Record *, unsigned int, Rva00064640Record>(Rva00064640Record *, unsigned int, const Rva00064640Record &, const __false_type &);
// ??$__uninitialized_copy@PBVRva00064640Record@@PAV1@@_STL@@YAPAVRva00064640Record@@PBV1@0PAV1@ABU__false_type@0@@Z 0x00469CA2 38B evidence: 0x1c-stride range copy via rowed _Construct 0x469C73 callers 0x469D0B 0x470189 0x4701D4
template Rva00064640Record *__uninitialized_copy<const Rva00064640Record *, Rva00064640Record *>(const Rva00064640Record *, const Rva00064640Record *, Rva00064640Record *, const __false_type &);
// ??$_M_allocate_and_copy@PBVRva00064640Record@@@?$vector@VRva00064640Record@@V?$allocator@VRva00064640Record@@@_STL@@@_STL@@IAEPAVRva00064640Record@@IPBV2@0@Z 0x00469CED 45B evidence: allocate via ICF twin pin allocator Rva00064640Record at 0xB40EA then rowed copy 0x469CA2 caller 0x46EE72
template Rva00064640Record *vector<Rva00064640Record, allocator<Rva00064640Record> >::_M_allocate_and_copy<const Rva00064640Record *>(unsigned int, const Rva00064640Record *, const Rva00064640Record *);
// ?_M_insert_overflow@?$vector@VRva00064640Record@@V?$allocator@VRva00064640Record@@@_STL@@@_STL@@IAEXPAVRva00064640Record@@ABV3@ABU__false_type@2@I_N@Z 0x00470148 189B evidence: growth path whose calls read rowed _Construct 0x469C73, fill_n 0x469CC8 and copy 0x469CA2 (twice), ICF allocate 0xB40EA and _free
template void vector<Rva00064640Record, allocator<Rva00064640Record> >::_M_insert_overflow(Rva00064640Record *, const Rva00064640Record &, const __false_type &, unsigned int, bool);
// ?push_back@?$vector@VRva00064640Record@@V?$allocator@VRva00064640Record@@@_STL@@@_STL@@QAEXABVRva00064640Record@@@Z 0x00473F4A 55B evidence: calls rowed _Construct 0x469C73 and _M_insert_overflow 0x470148
template void vector<Rva00064640Record, allocator<Rva00064640Record> >::push_back(const Rva00064640Record &);
}
