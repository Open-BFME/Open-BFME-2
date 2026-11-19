// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__lower_bound@PAUBfmePod40@@U1@U?$less@UBfmePod40@@@_STL@@H@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@U?$less@UBfmePod40@@@0@PAH@Z @0x00540253 (66B):
// __lower_bound over BfmePod40 pointers with default less<> on a[0]; idiv
// stride count plus halving loop. Caller 0x00540319.
// Evidence: unlock lane, all callees rowed, unblocks 0x00540301.
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

#include <vector>
#include <algorithm>
// This vector's 40-byte element is the one whose copy and construct are
// rowed as Rva0054000B's: _M_allocate_and_copy 0x0054016A calls the
// uninitialized copy 0x005400B4, which constructs through 0x00540070.
struct BfmePod40;
class Rva0054000B;
namespace _STL {
template <> void _Construct<Rva0054000B, Rva0054000B>(Rva0054000B *, const Rva0054000B &) throw();
template <> Rva0054000B *__uninitialized_copy<const Rva0054000B *, Rva0054000B *>(const Rva0054000B *, const Rva0054000B *, Rva0054000B *, const __false_type &) throw();
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod40, BfmePod40>(BfmePod40 *p, const BfmePod40 &v) throw()
{ _Construct((Rva0054000B *)p, (const Rva0054000B &)v); }
template <> __declspec(dllimport) __forceinline BfmePod40 *__uninitialized_copy<BfmePod40 *, BfmePod40 *>(BfmePod40 *first, BfmePod40 *last, BfmePod40 *result, const __false_type &)
{ __false_type tag; return (BfmePod40 *)__uninitialized_copy((const Rva0054000B *)first, (const Rva0054000B *)last, (Rva0054000B *)result, tag); }
}
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod40@@V?$allocator@UBfmePod40@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> vector<BfmePod40,allocator<BfmePod40> >::vector(vector<BfmePod40,allocator<BfmePod40> > const &); }
struct BfmePod40 { int a[10]; __forceinline bool operator<(const BfmePod40 &o) const { return a[0] < o.a[0]; } };
// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *, BfmePod40 *); }
// reserve inlines this cleanup; its out-of-line copy belongs to the retail provider.
namespace _STL {
template <> __declspec(dllimport) __forceinline void vector<BfmePod40>::_M_clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_end_of_storage.deallocate(this->_M_start,
        this->_M_end_of_storage._M_data - this->_M_start);
}
}
template _STL::_Vector_base<BfmePod40, _STL::allocator<BfmePod40> >::_Vector_base(unsigned int, const _STL::allocator<BfmePod40> &);
template void _STL::vector<BfmePod40>::reserve(unsigned int);
template BfmePod40 *_STL::__lower_bound<BfmePod40 *, BfmePod40, _STL::less<BfmePod40>, int>(BfmePod40 *, BfmePod40 *, const BfmePod40 &, _STL::less<BfmePod40>, int *);
