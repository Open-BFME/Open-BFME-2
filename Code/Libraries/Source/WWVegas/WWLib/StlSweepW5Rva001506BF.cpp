// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <memory>

struct Rva001506BFElement { unsigned words[2];Rva001506BFElement();Rva001506BFElement(const Rva001506BFElement&b){words[0]=b.words[0];words[1]=b.words[1];}bool operator<(const Rva001506BFElement&)const;bool operator==(const Rva001506BFElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001506BFElement, _STL::allocator<Rva001506BFElement> >::_M_fill_insert(Rva001506BFElement *, unsigned int, Rva001506BFElement const &);
