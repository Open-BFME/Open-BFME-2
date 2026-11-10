// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x005C856D, 183B; Ghidra boundary, ret14 ABI and 72-byte
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
struct Rva005C8624Element;
struct Rva005C84D3Element;
namespace _STL { template<> void vector<Rva005C84D3Element>::_M_clear(); }
namespace _STL { template<> void _Construct<Rva005C8624Element,Rva005C8624Element>(Rva005C8624Element*,const Rva005C8624Element&); }

struct Rva005C856DClearOwner : _STL::vector<Rva005C84D3Element > {
    using _STL::vector<Rva005C84D3Element >::_M_clear;
};

struct Rva005C856DRecord { Rva005C856DRecord(); Rva005C856DRecord(const Rva005C856DRecord&); ~Rva005C856DRecord(); Rva005C856DRecord&operator=(const Rva005C856DRecord&); private: char bytes[72]; };
namespace _STL {
template<> __declspec(dllimport) __forceinline void vector<Rva005C856DRecord>::_M_clear()
{ reinterpret_cast<Rva005C856DClearOwner*>(this)->_M_clear(); }
template<> __declspec(dllimport) __forceinline void _Construct<Rva005C856DRecord,Rva005C856DRecord>(Rva005C856DRecord*p,const Rva005C856DRecord&v)
{ _Construct(reinterpret_cast<Rva005C8624Element*>(p),reinterpret_cast<const Rva005C8624Element&>(v)); }
}
template void _STL::vector<Rva005C856DRecord>::_M_insert_overflow(Rva005C856DRecord*,const Rva005C856DRecord&,const _STL::__false_type&,unsigned int,bool);
template void _STL::vector<Rva005C856DRecord>::push_back(const Rva005C856DRecord&);
