// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <vector>

struct Rva002B0CE7Element { _STL::vector<char> values[3]; bool operator==(const Rva002B0CE7Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva002B0CE7Element *>(Rva002B0CE7Element *, Rva002B0CE7Element *, _STL::__false_type const &);
