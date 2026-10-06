// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva002CA82CElement { short words[4]; bool operator<(const Rva002CA82CElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002CA82CElement&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Construct<_STL::pair<Rva002CA82CElement const, int>, _STL::pair<Rva002CA82CElement const, int> >(_STL::pair<Rva002CA82CElement const, int> *, _STL::pair<Rva002CA82CElement const, int> const &);
