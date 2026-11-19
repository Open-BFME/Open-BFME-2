// cl: /MD /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// Native9292B copies GeometryInfo's +2C vector through64289/63C8F.
// That target chain establishes this36-byte owning record view, including
// AsciiString at1C and two tail bytes20/21. The original application class
// is not newly asserted. The old160C70/5EA9xx private GeometryShape families
// remain separate; only the actual copying member is reconciled here.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// The rowed vector destructor supplies the shared out-of-line body.
struct BfmeStringRecord00063BE4;
namespace _STL { template <> vector<BfmeStringRecord00063BE4, allocator<BfmeStringRecord00063BE4> >::~vector(); }
#include "ascii_string.h"

typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmeStringRecord00063BE4@@V?$allocator@UBfmeStringRecord00063BE4@@@_STL@@@_STL@@QAEXABUGeom:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmeStringRecord00063BE4,allocator<BfmeStringRecord00063BE4> >::push_back(BfmeStringRecord00063BE4 const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmeStringRecord00063BE4@@V?$allocator@UBfmeStringRecord00063BE4@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmeStringRecord00063BE4,allocator<BfmeStringRecord00063BE4> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UBfmeStringRecord00063BE4@@V?$allocator@UBfmeStringRecord00063BE4@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmeStringRecord00063BE4,allocator<BfmeStringRecord00063BE4> >::_M_insert_overflow(BfmeStringRecord00063BE4 *,BfmeStringRecord00063BE4 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$_Construct@UBfmeStringRecord00063BE4@@U1@@_STL@@YAXPAUBfmeStringRecord00063BE4@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Construct<BfmeStringRecord00063BE4,BfmeStringRecord00063BE4>(BfmeStringRecord00063BE4 *,BfmeStringRecord00063BE4 const &); }
// The native count-base and its inline allocator path are emitted here.
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UBfmeStringRecord00063BE4@@V?$allocator@UBfmeStringRecord00063BE4@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Vector_base<BfmeStringRecord00063BE4,allocator<BfmeStringRecord00063BE4> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeStringRecord00063BE4@@@_STL@@QBEXPAUBfmeStringRecord00063BE4@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<BfmeStringRecord00063BE4>::deallocate(BfmeStringRecord00063BE4 *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &);
    ~BfmeStringRecord00063BE4();
    BfmeStringRecord00063BE4 &operator=(const BfmeStringRecord00063BE4 &);
};

template _STL::vector<BfmeStringRecord00063BE4>::vector(const _STL::vector<BfmeStringRecord00063BE4> &);

// The unrelated erase/copy_ptrs bodies formerly instantiated here are
// already owned and verified by GeometryInfoRva002B0E55.cpp.
