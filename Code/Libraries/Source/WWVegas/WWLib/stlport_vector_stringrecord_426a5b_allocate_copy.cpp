// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 8-byte BfmeStringRecord00426A5B vector allocation/copy helper at RVA 0x426B46.
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

#include "ascii_string.h"
struct BfmeStringRecord00426A5B {
    AsciiString text;
    unsigned char flag0, flag1, flag2;
    BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o);
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord00426A5B,BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B*,const BfmeStringRecord00426A5B&);
namespace _STL {
template <>
inline __declspec(noinline) void _Destroy<BfmeStringRecord00426A5B *>(BfmeStringRecord00426A5B *__first, BfmeStringRecord00426A5B *__last)
{
    for (; __first != __last; ++__first)
        __first->text.~AsciiString();
}
}
#include <vector>
template BfmeStringRecord00426A5B *_STL::__uninitialized_copy<const BfmeStringRecord00426A5B *, BfmeStringRecord00426A5B *>(const BfmeStringRecord00426A5B *, const BfmeStringRecord00426A5B *, BfmeStringRecord00426A5B *, const _STL::__false_type &);
template BfmeStringRecord00426A5B *_STL::__uninitialized_fill_n<BfmeStringRecord00426A5B *, unsigned int, BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B *, unsigned int, const BfmeStringRecord00426A5B &, const _STL::__false_type &);
template BfmeStringRecord00426A5B *_STL::__copy_ptrs(BfmeStringRecord00426A5B *, BfmeStringRecord00426A5B *, BfmeStringRecord00426A5B *, _STL::__false_type);
template BfmeStringRecord00426A5B *_STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::_M_allocate_and_copy<const BfmeStringRecord00426A5B *>(unsigned int, const BfmeStringRecord00426A5B *, const BfmeStringRecord00426A5B *);
template void _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::push_back(const BfmeStringRecord00426A5B &);
template void _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::_M_insert_overflow(BfmeStringRecord00426A5B *, const BfmeStringRecord00426A5B &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::_M_clear();
template void _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::reserve(unsigned int);
