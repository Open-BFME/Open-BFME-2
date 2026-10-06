// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 vector<T>::erase(first, last) for two more
// placeholder POD elements, in the _STLP_USE_MALLOC configuration of
// stlport_pod_vector_malloc_bodies.cpp (whose rowed erase bodies show the
// same [ebp+0xb] slot for the empty __false_type temporary). The element
// size of each site is carried by its callee chain: erase 0x001DDC2C calls
// __copy_ptrs 0x001DD339, which calls the rowed 52-byte __copy 0x001DD14F;
// erase 0x00587C1A calls __copy_ptrs 0x0058757C, which calls the rowed
// 60-byte __copy 0x005873DE. __copy_ptrs takes the tag by const reference
// (retail pushes the temporary's address), so the Pod52 one is pinned under
// that spelling next to its by-value row; the Pod60 one is rowed here.
#include <vector>
struct BfmePod52 { int a[13]; };
struct BfmePod60 { int a[15]; };
template BfmePod52 *_STL::vector<BfmePod52, _STL::allocator<BfmePod52> >::erase(BfmePod52 *, BfmePod52 *);
template BfmePod60 *_STL::vector<BfmePod60, _STL::allocator<BfmePod60> >::erase(BfmePod60 *, BfmePod60 *);
