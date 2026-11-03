// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfmealloc -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// stlport
//
// ??0?$_Vector_base@UBfmeStringRecord000B9534@@V?$allocator@UBfmeStringRecord000B9534@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmeStringRecord000B9534@@@1@@Z,
// retail 0x000B63B2, 60 bytes. _Vector_base ctor for the 24-byte StringRecord
// vector: proxy ctor 0x0014F3C4 then allocate 0x00395944 with imul 0x18.
// Needs /G7: home-TU /O1 strength-reduces the imul (allocator-row note).
// Callers 0x000BCE65 0x000BCEC5 0x00425471 0x0052D524 0x005DE88A.
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

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BfmeStringRecord000B9534 {
    AsciiString text;
    unsigned char flag;
    unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534();
    // The allocation/copy unit already owns the shared cleanup COMDAT.
    // Keep calls to it without emitting a different AsciiString forwarding copy.
    ~BfmeStringRecord000B9534();
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &other)
      : text(other.text), flag(other.flag), word0(other.word0), word1(other.word1), word2(other.word2), word3(other.word3) {}
};
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> BfmeStringRecord000B9534 * __copy<BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,int>(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> BfmeStringRecord000B9534 * __copy<BfmeStringRecord000B9534 const *,BfmeStringRecord000B9534 *,int>(BfmeStringRecord000B9534 const *,BfmeStringRecord000B9534 const *,BfmeStringRecord000B9534 *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> BfmeStringRecord000B9534 * __copy_backward<BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,int>(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,_STL::random_access_iterator_tag const &,int *); }
namespace _STL { template <> void fill<BfmeStringRecord000B9534 *,BfmeStringRecord000B9534>(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 const &); }
namespace _STL { template <> BfmeStringRecord000B9534 * fill_n<BfmeStringRecord000B9534 *,unsigned int,BfmeStringRecord000B9534>(BfmeStringRecord000B9534 *,unsigned int,BfmeStringRecord000B9534 const &); }
namespace _STL { template <> BfmeStringRecord000B9534 * vector<BfmeStringRecord000B9534,_STL::allocator<BfmeStringRecord000B9534> >::erase(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 *); }
namespace _STL { template <> BfmeStringRecord000B9534 * vector<BfmeStringRecord000B9534,_STL::allocator<BfmeStringRecord000B9534> >::insert(BfmeStringRecord000B9534 *,BfmeStringRecord000B9534 const &); }
// bfme link decl-only end
template class _STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >;

// /OPT:ICF folds vector<LightSubPoint>'s base constructor onto this body: the
// element is 24 bytes too, and the fill constructor 0x0042545A calls 0x000B63B2.
#include "../WW3D2/LightSubPoint.h"
template _STL::_Vector_base<LightSubPoint, _STL::allocator<LightSubPoint> >::_Vector_base(size_t, const _STL::allocator<LightSubPoint> &);
