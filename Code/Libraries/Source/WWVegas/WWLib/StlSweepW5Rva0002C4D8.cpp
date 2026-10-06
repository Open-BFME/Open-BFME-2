// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>






struct Rva0002C4D8Element { _STL::list<short> values[1]; bool operator==(const Rva0002C4D8Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0002C4D8Element * _STL::__uninitialized_fill_n<Rva0002C4D8Element *, unsigned int, Rva0002C4D8Element>(Rva0002C4D8Element *, unsigned int, Rva0002C4D8Element const &, _STL::__false_type const &);
