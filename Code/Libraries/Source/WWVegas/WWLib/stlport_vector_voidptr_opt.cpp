// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// vector<void *> again, optimised. The instantiation appears in game.dat from
// more than one unit and only one definition of each COMDAT survives the link,
// so the flags that produced the surviving copy are not the same for every
// body. erase is the clear case: the /Od unit compiles it to 84 bytes with an
// ebp frame, and the image holds a 34-byte version with no frame at all that
// keeps the vector in esi. That is the definition clear and _M_fill_assign
// call, so it has to be built here rather than there.

#include <vector>

template class _STL::vector<void *, _STL::allocator<void *> >;
