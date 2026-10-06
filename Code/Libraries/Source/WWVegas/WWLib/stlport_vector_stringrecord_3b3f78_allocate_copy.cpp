// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /G7
// stlport
// BFME2's 20-byte BfmeStringRecord003B3F78 vector allocation/copy helper at RVA 0x3B469A.
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

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord003B3F78 {
    unsigned int word0, word1;
    AsciiString text;
    unsigned char flag;
    unsigned short short0;
    unsigned int word2;
    BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &o);
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord003B3F78,BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78*,const BfmeStringRecord003B3F78&);
#include <vector>
template BfmeStringRecord003B3F78 *_STL::__uninitialized_copy<const BfmeStringRecord003B3F78 *, BfmeStringRecord003B3F78 *>(const BfmeStringRecord003B3F78 *, const BfmeStringRecord003B3F78 *, BfmeStringRecord003B3F78 *, const _STL::__false_type &);
template BfmeStringRecord003B3F78 *_STL::__uninitialized_fill_n<BfmeStringRecord003B3F78 *, unsigned int, BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78 *, unsigned int, const BfmeStringRecord003B3F78 &, const _STL::__false_type &);
template BfmeStringRecord003B3F78 *_STL::vector<BfmeStringRecord003B3F78, _STL::allocator<BfmeStringRecord003B3F78> >::_M_allocate_and_copy<const BfmeStringRecord003B3F78 *>(unsigned int, const BfmeStringRecord003B3F78 *, const BfmeStringRecord003B3F78 *);
template void _STL::vector<BfmeStringRecord003B3F78, _STL::allocator<BfmeStringRecord003B3F78> >::push_back(const BfmeStringRecord003B3F78 &);
template void _STL::vector<BfmeStringRecord003B3F78, _STL::allocator<BfmeStringRecord003B3F78> >::reserve(unsigned int);
