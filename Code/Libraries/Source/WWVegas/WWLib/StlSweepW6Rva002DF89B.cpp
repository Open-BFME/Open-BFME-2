// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva002DF89BElement { unsigned word0;unsigned word1;unsigned word2;Rva002DF89BElement& operator=(const Rva002DF89BElement&b){if(this!=&b){word0=b.word0;word1=b.word1;word2=b.word2;}return *this;}bool operator<(const Rva002DF89BElement&)const;bool operator==(const Rva002DF89BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva002DF89BElement, _STL::allocator<Rva002DF89BElement> >::push_back(Rva002DF89BElement const &);
