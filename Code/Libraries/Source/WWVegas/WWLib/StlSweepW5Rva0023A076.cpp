// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>






struct Rva0023A076Element { _STL::list<short> values[1]; bool operator==(const Rva0023A076Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0023A076Element, _STL::allocator<Rva0023A076Element> >::_M_insert_overflow(Rva0023A076Element *, Rva0023A076Element const &, _STL::__false_type const &, unsigned int, bool);
