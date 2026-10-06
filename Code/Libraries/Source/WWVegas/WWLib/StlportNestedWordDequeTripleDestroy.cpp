// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 reference headers, BFME1 revision 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Retail 0x425400/33 destroys 40-byte outer word-deques via the independently
// recovered destructor 0x424A0E, and increments a deque iterator through
// 0x42198C (stride40, three elements per buffer). That destructor's own
// Destroy424709 chain and recovered inner copy422825 establish nesting;
// footprint alone does not. Original innermost four-byte type is unknown.
// Both full33B body and complete36B iterator dependency verify strictly.
#include <deque>
struct BfmeWordValue4 { unsigned bits; BfmeWordValue4(); ~BfmeWordValue4() {} };
typedef _STL::deque<BfmeWordValue4,_STL::allocator<BfmeWordValue4> > InnerDeque;
typedef _STL::deque<InnerDeque,_STL::allocator<InnerDeque> > OuterDeque;
namespace _STL { template<> OuterDeque::~deque(); }
typedef _STL::_Deque_iterator<OuterDeque,_STL::_Nonconst_traits<OuterDeque> > OuterDequeIterator;
template void _STL::__destroy_aux(OuterDequeIterator,OuterDequeIterator,const _STL::__false_type &);
template void _STL::_Destroy(OuterDequeIterator,OuterDequeIterator);
