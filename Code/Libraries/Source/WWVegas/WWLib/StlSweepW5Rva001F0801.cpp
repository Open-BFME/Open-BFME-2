// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>






struct Rva001F0801Element { _STL::list<short> values[3]; bool operator==(const Rva001F0801Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva001F0801Element *>(Rva001F0801Element *, Rva001F0801Element *, _STL::__false_type const &);
