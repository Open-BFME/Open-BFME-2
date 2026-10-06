// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>






struct Rva005DE4BAElement { _STL::list<short> values[2]; bool operator==(const Rva005DE4BAElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva005DE4BAElement, _STL::allocator<Rva005DE4BAElement> >::_M_insert_overflow(Rva005DE4BAElement *, Rva005DE4BAElement const &, _STL::__false_type const &, unsigned int, bool);
