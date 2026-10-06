// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_push_back_aux_v@?$deque@V?$deque@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@V?$allocator@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@@2@@_STL@@V?$allocator@V?$deque@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@V?$allocator@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@@2@@_STL@@@2@@_STL@@IAEXABV?$deque@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@V?$allocator@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_STL@@@2@@Z @0x00424A65 123B. Triple-deque (deque<deque<deque<BfmeWordValue4>>>>) _M_push_back_aux_v: temp copy of the OuterDeque value, _M_reserve_map_at_back, 0x78-byte node allocate, _Construct at finish, set_node. Same stock STLport 4.5.3 header body as the rowed double-nested sibling 0x004235CD; non-POD temp needs EH and retail or [ebp-4],-1 needs /EHs. Evidence: callees rowed 0x00423675 0x000307F0 0x00423D65 0x00424A0E and reserve 0x0042305C folded (pin TripleDeque reserve there); caller 0x00424CEA push_back fast path; unblocks 0x00424CEA.
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
template void TripleDeque::_M_push_back_aux_v(const OuterDeque &);
