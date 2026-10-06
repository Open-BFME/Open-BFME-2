// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Triple-deque (deque<deque<deque<BfmeWordValue4>>>>) push_back fast path @0x00424CEA 45B.
// Same stock STLport 4.5.3 header body as the rowed double-nested sibling 0x00423C26 (45B);
// fast path constructs via rowed _Construct 0x00423D65 else rowed _M_push_back_aux_v 0x00424A65.
// Evidence: callees rowed 0x00423D65 0x00424A65; caller 0x004251C4; chain lane calls just-landed 0x00424A65.
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

#include <deque>
struct BfmeWordValue4
{
    unsigned int bits;
    BfmeWordValue4();
    ~BfmeWordValue4() {}
};
typedef _STL::deque<BfmeWordValue4,_STL::allocator<BfmeWordValue4> > InnerDeque;
typedef _STL::deque<InnerDeque,_STL::allocator<InnerDeque> > OuterDeque;
typedef _STL::deque<OuterDeque,_STL::allocator<OuterDeque> > TripleDeque;
typedef char InnerDequeSize[sizeof(InnerDeque) == 40 ? 1 : -1];
typedef char OuterDequeSize[sizeof(OuterDeque) == 40 ? 1 : -1];
typedef char TripleDequeSize[sizeof(TripleDeque) == 40 ? 1 : -1];
template void TripleDeque::push_back(const OuterDeque &);
