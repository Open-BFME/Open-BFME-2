// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 12-byte BfmeStringRecord002CF5B1 vector allocation/copy helper at RVA 0x2CFAFC.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeStringRecord002CF5B1.h"
#include <memory>
template void _STL::_Construct<BfmeStringRecord002CF5B1,BfmeStringRecord002CF5B1>(BfmeStringRecord002CF5B1*,const BfmeStringRecord002CF5B1&);
#include <vector>
namespace _STL { template<> vector<BfmeStringRecord002CF5B1> &vector<BfmeStringRecord002CF5B1>::operator=(const vector<BfmeStringRecord002CF5B1> &); }
template BfmeStringRecord002CF5B1* _STL::vector<BfmeStringRecord002CF5B1,_STL::allocator<BfmeStringRecord002CF5B1> >::_M_allocate_and_copy<const BfmeStringRecord002CF5B1*>(unsigned int,const BfmeStringRecord002CF5B1*,const BfmeStringRecord002CF5B1*);
// ?bfmeEmitstlport_vector_2cf5b1_uninitialized_fill_n@@YAXPAUBfmeStringRecord002CF5B1@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf5b1_uninitialized_fill_n(const BfmeStringRecord002CF5B1 *p)
{
	_STL::__uninitialized_fill_n((BfmeStringRecord002CF5B1 *)0, 0u, *p, _STL::__false_type());
}
