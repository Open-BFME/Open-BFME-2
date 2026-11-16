// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>

// 40-byte element, itself a deque: retail's deque destroy 0x00423EB0 steps by 0x28 and
// calls the rowed inner deque destructor 0x00422D48, reached here by a qualified call.
#include "../../../../GameEngine/Include/Common/BfmeWordValue4.h"
typedef _STL::deque<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > Rva004244C1InnerDeque;
// The inner destructor is owned by StlportNestedWordDeque.cpp; declaration-only here.
namespace _STL { template <> Rva004244C1InnerDeque::~deque(); }
struct Rva004244C1Element
{
	__forceinline ~Rva004244C1Element() { ((Rva004244C1InnerDeque *)this)->Rva004244C1InnerDeque::~deque(); }
	char bytes[40];
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy<_STL::_Deque_iterator<Rva004244C1Element, _STL::_Nonconst_traits<Rva004244C1Element> >, Rva004244C1Element>(_STL::_Deque_iterator<Rva004244C1Element, _STL::_Nonconst_traits<Rva004244C1Element> >, _STL::_Deque_iterator<Rva004244C1Element, _STL::_Nonconst_traits<Rva004244C1Element> >, Rva004244C1Element *);
