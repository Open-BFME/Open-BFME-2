// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 view of the target iterator stride; original element name and
// fields are unknown. Verified operations cover iteration, growth and cleanup.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmeOpaque2148 { unsigned char bytes[0x864]; };
template class _STL::deque<BfmeOpaque2148, _STL::allocator<BfmeOpaque2148> >;
template _STL::_Deque_iterator<BfmeOpaque2148, _STL::_Nonconst_traits<BfmeOpaque2148> > &
_STL::_Deque_iterator<BfmeOpaque2148, _STL::_Nonconst_traits<BfmeOpaque2148> >::operator++();

