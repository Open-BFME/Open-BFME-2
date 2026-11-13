// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::push_back for five element types whose _Construct
// and _M_insert_overflow rows already exist: retail 0x001ED285, 0x002B14EB,
// 0x004F93E7, 0x005ECC19 and 0x00337CEA, 55 bytes each.
// Evidence: each body is the unowned retail caller of its element's matched
// _Construct (fast path) and _M_insert_overflow (growth path), byte-identical
// with relocations masked to the rowed push_back siblings in
// StlportVectorGrowthFootprints.cpp, whose flags and footprint recipe this TU
// mirrors: out-of-line copy ctor and dtor, and _Construct declared as an
// explicit specialization so the fast path calls the element's _Construct row.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 36-byte element; layout owner StringContainerRecordCopyBFME2.cpp.
#include "../../../../GameEngine/Include/Common/Rva001EC349.h"
struct BfmeRecord001ECAF9 { char m_pad[36]; public: BfmeRecord001ECAF9(const BfmeRecord001ECAF9 &); // Destruction is the rowed ??1Rva001EC349, reached by a qualified call.
__declspec(dllimport) __forceinline ~BfmeRecord001ECAF9() { ((Rva001EC349 *)this)->Rva001EC349::~Rva001EC349(); } };
// 36-byte element; layout as in StlportVectorGrowthFootprints.cpp.
struct BfmeVectorRecord002AF478 { char m_pad[36]; public: BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &); ~BfmeVectorRecord002AF478(); };
// 24-byte element; layout owner StringRecordInlineCopyBFME2.cpp.
#include "BfmeStringRecord005EC43C.h"
// 12-byte element; layout as in StlportVectorGrowthFootprints.cpp.
struct Rva004F6352 { char m_pad[12]; public: Rva004F6352(const Rva004F6352 &); ~Rva004F6352(); };

// 20-byte element; layout owner Rva003371B1Copy.cpp.
class Rva003371B1 { char m_pad[20]; public: Rva003371B1(const Rva003371B1 &); ~Rva003371B1(); };

// Bind the incidental cleanup to the rowed _M_clear in
// StlportVectorGrowthFootprints.cpp instead of emitting a second copy.
namespace _STL { template <> void vector<BfmeVectorRecord002AF478>::_M_clear(); }

namespace _STL
{
template <> void _Construct<BfmeRecord001ECAF9, BfmeRecord001ECAF9>(BfmeRecord001ECAF9 *, const BfmeRecord001ECAF9 &);
template <> void _Construct<BfmeVectorRecord002AF478, BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478 *, const BfmeVectorRecord002AF478 &);
template <> void _Construct<Rva004F6352, Rva004F6352>(Rva004F6352 *, const Rva004F6352 &);
template <> void _Construct<BfmeStringRecord005EC43C, BfmeStringRecord005EC43C>(BfmeStringRecord005EC43C *, const BfmeStringRecord005EC43C &);
template <> void _Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &);
}

template void _STL::vector<BfmeRecord001ECAF9>::push_back(const BfmeRecord001ECAF9 &);
template void _STL::vector<BfmeVectorRecord002AF478>::push_back(const BfmeVectorRecord002AF478 &);
template void _STL::vector<Rva004F6352>::push_back(const Rva004F6352 &);
template void _STL::vector<BfmeStringRecord005EC43C>::push_back(const BfmeStringRecord005EC43C &);
template void _STL::vector<Rva003371B1>::push_back(const Rva003371B1 &);

// The sixth sibling, vector<Object *>::push_back at 0x001F211B (58 bytes), calls the unrowed growth
// body at 0x001F2155, pinned as the _M_insert_overflow specialization; its fast path stores the
// four-byte slot directly.
class Object;
template <> void _STL::vector<Object *>::_M_insert_overflow(Object **, Object * const &, const _STL::__true_type &, unsigned, bool);
template void _STL::vector<Object *>::push_back(Object * const &);
