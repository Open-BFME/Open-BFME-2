// cl: /Od /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 vector<unsigned int, _STL::allocator<unsigned int> >, vendored instantiation. /Od /Ob1 is the shape the
// vector<void *> unit established for these containers: an unoptimised frame
// with inline expansion still on.

// Native range erase at 0x27400 calls the rowed __copy_trivial (0x179B0).
// Keep the header's implementation under a local spelling so it cannot emit
// an /Od copy of that provider, then bind unsigned-pointer copies to the
// existing declaration. The vendor's copy/destroy tag temporaries remain.
#define __copy_trivial uintInlineCopyTrivial
#include <vector>
#undef __copy_trivial

namespace _STL
{
void *__copy_trivial(const void *, const void *, void *);
template <> inline unsigned int *__copy_ptrs<unsigned int *, unsigned int *>(
	unsigned int *first, unsigned int *last, unsigned int *result, const __true_type &)
{
	return (unsigned int *)__copy_trivial(first, last, result);
}
}

// The complete scalar copy is rowed in stlport_vector_scalar_copy.cpp at
// 2CFAB9. This /Od unit owns other members and must not emit a competing copy.
namespace _STL {
template <> vector<unsigned int>::vector(const vector<unsigned int> &);
}
template class _STL::vector<unsigned int, _STL::allocator<unsigned int> >;
