// cl: /O1 /G7 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_push_back_aux_v@?$deque@UBfmeNarrowRecord0054FEF1@@V?$allocator@UBfmeNarrowRecord0054FEF1@@@_STL@@@_STL@@IAEXABUBfmeNarrowRecord0054FEF1@@@Z @0x00550098 130B.
// deque<BfmeNarrowRecord0054FEF1> auxiliary push-back: temp copy via rowed 0x0054FEF1, reserve via folded 0x0042305C, 0x78 node via 0x000307F0, Construct via rowed 0x0054FF6E, set_node, string cleanup via 0x00030830.
// Evidence: callees rowed 0x0054FEF1 0x0042305C(fold) 0x000307F0 0x0054FF6E 0x00030830; caller 0x005503A8 in 0x00550384; same stock STLport 4.5.3 shape as rowed OuterDeque 0x004235CD.
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
#include <string>

struct BfmeNarrowRecord0054FEF1
{
	_STL::basic_string<char> text;
	unsigned int word0;
	unsigned int word1;
	BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &o);
};

typedef _STL::deque<BfmeNarrowRecord0054FEF1, _STL::allocator<BfmeNarrowRecord0054FEF1> > NarrowRecord0054FEF1Deque;
typedef char NarrowRecord0054FEF1DequeSize[sizeof(NarrowRecord0054FEF1Deque) == 40 ? 1 : -1];

template void NarrowRecord0054FEF1Deque::_M_push_back_aux_v(const BfmeNarrowRecord0054FEF1 &);
template void NarrowRecord0054FEF1Deque::push_back(const BfmeNarrowRecord0054FEF1 &);
