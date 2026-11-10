// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <algorithm>
#include <memory>



// The element is Rva003B02F4Entry with comparator Rva003B02F4Greater: this __push_heap_aux's
// only call (0x003AFFE5) goes to the rowed __push_heap<Rva003B02F4Entry *, int,
// Rva003B02F4Entry, Rva003B02F4Greater> at 0x003AFE48 (stlport_priority_queue_rva003b02f4.cpp),
// declared only here. Only the rowed __push_heap_aux is instantiated.
#include "Rva003B02F4Entry.h"
struct Rva003B02F4Greater
{
	bool operator()(const Rva003B02F4Entry &x, const Rva003B02F4Entry &y) const
	{
		return x.key > y.key;
	}
};
namespace _STL { template <> void __push_heap<Rva003B02F4Entry *, int, Rva003B02F4Entry, Rva003B02F4Greater>(Rva003B02F4Entry *, int, int, Rva003B02F4Entry, Rva003B02F4Greater); }
template void _STL::__push_heap_aux<Rva003B02F4Entry *, Rva003B02F4Greater, int, Rva003B02F4Entry>(Rva003B02F4Entry *, Rva003B02F4Entry *, Rva003B02F4Greater, int *, Rva003B02F4Entry *);
