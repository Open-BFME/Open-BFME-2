// cl: /Od /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 vector<void *>. The reloc sweep names _M_fill_insert and
// reserve out of this instantiation from byte-true call sites, so the
// instantiation is known to exist in the image; this is the same vendored
// route the int and pair vectors here already use.

#include <vector>

template class _STL::vector<void *, _STL::allocator<void *> >;
