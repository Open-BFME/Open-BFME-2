// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva00057C80Element { unsigned word0;unsigned word1;Rva00057C80Element& operator=(const Rva00057C80Element&b){if(this!=&b){word0=b.word0;word1=b.word1;}return *this;}bool operator<(const Rva00057C80Element&)const;bool operator==(const Rva00057C80Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00057C80Element, _STL::allocator<Rva00057C80Element> >::_M_insert_overflow(Rva00057C80Element *, Rva00057C80Element const &, _STL::__false_type const &, unsigned int, bool);
