// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEXPAUBfmePod36@@IABU3@@Z @0x000B0478 232B. vector<BfmePod36> fill-insert false_type path.
// Evidence: rowed Pod36 helpers 0x000ADEA8 0x000ADEEB plus overflow 0x000AFF6B; StringRecord helpers 0x000ADECE 0x000AD806 share 0x24 stride; /Ob0 keeps copy-backward wrapper and /G7 fixes registers vs O1 sibling.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
#include <vector>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod36@@V?$allocator@UBfmePod36@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod36;
namespace _STL { template <> void vector<BfmePod36,allocator<BfmePod36> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::deallocate(BfmePod36 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod36@@U1@V?$allocator@UBfmePod36@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod36 * _STLP_alloc_proxy<BfmePod36 *,BfmePod36,allocator<BfmePod36> >::allocate(unsigned int); }

struct BfmePod36 { int a[9]; };

// Bind element construction to its rowed retail body (stlport_pod_vector_bodies.cpp).
namespace _STL { template <> void _Construct<BfmePod36,BfmePod36>(BfmePod36 *,const BfmePod36 &); }
// The growth path: retail's copy (0x000AFF6B, StlportVectorInsertOverflowRva000AFF6B.cpp)
// is an /O1 body with size, max, the allocator proxy, the old storage's release and
// _M_set expanded inline. This /Ob0 unit expands nothing, so spell the STLport 4.5.3
// algorithm out with those steps written in place; the TU's copy is then retail's.
namespace _STL {
template <> void vector<BfmePod36>::_M_insert_overflow(BfmePod36 *position, const BfmePod36 &value,
    const __false_type &, unsigned int fillLength, bool atEnd)
{
    unsigned int oldSize = this->_M_finish - this->_M_start;
    const unsigned int length = oldSize + *(oldSize < fillLength ? &fillLength : &oldSize);
    allocator<BfmePod36> &storage = this->_M_end_of_storage;
    BfmePod36 *start = storage.allocate(length, 0);
    BfmePod36 *finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    if (this->_M_start != 0)
        free(this->_M_start);
    this->_M_start = start;
    this->_M_finish = finish;
    this->_M_end_of_storage._M_data = start + length;
}
}

template void _STL::vector<BfmePod36>::_M_fill_insert(
	BfmePod36 *, unsigned int, const BfmePod36 &);
