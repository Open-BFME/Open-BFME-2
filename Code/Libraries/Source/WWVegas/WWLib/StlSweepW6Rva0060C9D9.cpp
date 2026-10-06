// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>
#include <utility>

struct Rva0060C9D9Element { double words[1];bool operator<(const Rva0060C9D9Element&)const;bool operator==(const Rva0060C9D9Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Construct<Rva0060C9D9Element, Rva0060C9D9Element>(Rva0060C9D9Element *, Rva0060C9D9Element const &);
