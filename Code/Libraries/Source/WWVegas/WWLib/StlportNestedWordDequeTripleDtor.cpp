// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3; BFME1 reference headers 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Complete retail destructor 0x425756/87 destroys the proven three-level deque
// through the rowed iterator Destroy 0x4256EE, then frees storage via
// 0x54FAAC. The existing nested word-deque copy chain establishes 4-byte
// inner values and 40-byte nested deque objects; original word type is unknown.
// Declare Destroy out of line to preserve retail's EH cleanup and use /EHs
// as the matched outer push-back sibling does (retail writes unwind state).
// Storage base destructor and node cleanup independently verify all bytes.
#include <deque>
struct BfmeWordValue4 { unsigned bits; BfmeWordValue4(); ~BfmeWordValue4() {} };
typedef _STL::deque<BfmeWordValue4,_STL::allocator<BfmeWordValue4> > InnerDeque;
typedef _STL::deque<InnerDeque,_STL::allocator<InnerDeque> > OuterDeque;
namespace _STL { template<> OuterDeque::~deque(); }
typedef _STL::deque<OuterDeque,_STL::allocator<OuterDeque> > TripleDeque;
namespace _STL {
template<> void _Destroy<TripleDeque::iterator>(TripleDeque::iterator,TripleDeque::iterator);
}
template TripleDeque::~deque();

