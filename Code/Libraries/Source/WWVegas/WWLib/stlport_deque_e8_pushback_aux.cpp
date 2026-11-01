// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 54B456: eight-byte integer/float records, sixteen elements per node.
// Use the shared STLport declarations while preserving the existing external
// reserve and construction providers; their visibility determines native code.
// The byte allocator already owns the former vectorSmallAllocate alias target.
#include <deque>
struct BfmeE8 { int a; float b; };
namespace _STL {
template<> void deque<BfmeE8,allocator<BfmeE8> >::_M_reserve_map_at_back(unsigned int);
template<> void _Construct<BfmeE8,BfmeE8>(BfmeE8 *,const BfmeE8 &);
}

// Preserve the existing local node-update helper without emitting an unused
// out-of-line copy of the header's iterator member under this TU's profile.
static __forceinline void setDequeNode(
    _STL::_Deque_iterator_base<BfmeE8> &iterator, BfmeE8 **newNode)
{
    iterator._M_node = newNode;
    iterator._M_first = *newNode;
    iterator._M_last = iterator._M_first + 16;
}

template<> void _STL::deque<BfmeE8,_STL::allocator<BfmeE8> >::_M_push_back_aux_v(const BfmeE8 &value)
{
 BfmeE8 copy;
 copy.a = value.a;
 copy.b = value.b;
 this->_M_reserve_map_at_back(1);
 *(this->_M_finish._M_node + 1) = (BfmeE8 *)_STL::allocator<char>::allocate(0x80,0);
 _STL::_Construct(this->_M_finish._M_cur, copy);
 setDequeNode(this->_M_finish, this->_M_finish._M_node + 1);
 this->_M_finish._M_cur = this->_M_finish._M_first;
}
