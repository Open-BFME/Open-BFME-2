// cl: /O1 /G7 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target word copies and iterator cleanup have no element teardown side effects.
// This view preserves the observed loop; the original element type is unknown.
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

typedef _STL::deque<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > InnerDeque;
// Retail outer destructor is owned by StlportNestedWordDequeOuterDtor.cpp.
// Avoid emitting this TU's shorter incompatible copy.
typedef _STL::deque<InnerDeque, _STL::allocator<InnerDeque> > OuterDeque;
namespace _STL {
template<> OuterDeque::~deque();
}

typedef char WordSize[sizeof(BfmeWordValue4) == 4 ? 1 : -1];
typedef char InnerDequeSize[sizeof(InnerDeque) == 40 ? 1 : -1];

template class _STL::deque<BfmeWordValue4, _STL::allocator<BfmeWordValue4> >;
template class _STL::deque<InnerDeque, _STL::allocator<InnerDeque> >;
