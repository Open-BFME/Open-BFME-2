// cl: /O1 /EHsc /arch:SSE /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Integer-to-float map element access (shared subscript helper). The insert
// folds to the rowed integer-pair spelling (twin pin).

#include <map>

template float &_STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > >::operator[](const int &);
