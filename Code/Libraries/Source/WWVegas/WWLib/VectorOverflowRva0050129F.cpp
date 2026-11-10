// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x0050129F, 183B; Ghidra boundary, ret14 ABI and 12-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

// Native placement-copy and range-destruction calls identify these existing
// helper owners. The opaque element spelling stays local; no new identity
// or layout is claimed for the record. Bind its helper calls to those owners.
struct BfmePod88;
namespace _STL { template<> void vector<vector<BfmePod88> >::_M_clear(); }
namespace _STL { template<> void _Construct<_STL::vector<BfmePod88>,_STL::vector<BfmePod88> >(_STL::vector<BfmePod88>*,const _STL::vector<BfmePod88>&); }

struct Rva0050129FClearOwner : _STL::vector<_STL::vector<BfmePod88> > {
    using _STL::vector<_STL::vector<BfmePod88> >::_M_clear;
};

struct Rva0050129FRecord { Rva0050129FRecord(); Rva0050129FRecord(const Rva0050129FRecord&); ~Rva0050129FRecord(); Rva0050129FRecord&operator=(const Rva0050129FRecord&); private: char bytes[12]; };
namespace _STL {
template<> __declspec(dllimport) __forceinline void vector<Rva0050129FRecord>::_M_clear()
{ reinterpret_cast<Rva0050129FClearOwner*>(this)->_M_clear(); }
template<> __declspec(dllimport) __forceinline void _Construct<Rva0050129FRecord,Rva0050129FRecord>(Rva0050129FRecord*p,const Rva0050129FRecord&v)
{ _Construct(reinterpret_cast<_STL::vector<BfmePod88>*>(p),reinterpret_cast<const _STL::vector<BfmePod88>&>(v)); }
}
template void _STL::vector<Rva0050129FRecord>::_M_insert_overflow(Rva0050129FRecord*,const Rva0050129FRecord&,const _STL::__false_type&,unsigned int,bool);
