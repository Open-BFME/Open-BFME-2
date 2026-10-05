// cl: /O1 /G7 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?_M_push_back_aux_v@?$deque@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@V?$allocator@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@@2@@_STL@@IAEXABV?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@2@@Z
// retail 0x004235CD, 123 bytes. Outer-deque (deque<deque<BfmeWordValue4>>)
// _M_push_back_aux_v: temp copy of the inner deque, _M_reserve_map_at_back,
// 0x78-byte node allocate, _Construct at finish, set_node. Same stock
// STLport 4.5.3 header body as the rowed POD sibling 0x00423558; the
// non-POD temp needs EH and the retail `or [ebp-4],-1` state store needs
// /EHs (the /EHsc sibling TU StlportNestedWordDeque.cpp emits 119 B
// without it). Evidence: callees rowed 0x00422825 0x0042305C 0x000307F0
// 0x0042301D 0x00422D48; caller 0x00423C4A in 0x00423BD8.
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
typedef _STL::deque<InnerDeque, _STL::allocator<InnerDeque> > OuterDeque;
typedef char InnerDequeSize[sizeof(InnerDeque) == 40 ? 1 : -1];

template void OuterDeque::_M_push_back_aux_v(const InnerDeque &);
