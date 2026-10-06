// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva004D751DElement { short words[1]; bool operator<(const Rva004D751DElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva004D751DElement&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<Rva004D751DElement, _STL::pair<Rva004D751DElement const, int>, _STL::_Select1st<_STL::pair<Rva004D751DElement const, int> >, _STL::less<Rva004D751DElement>, _STL::allocator<_STL::pair<Rva004D751DElement const, int> > >::clear(void);
