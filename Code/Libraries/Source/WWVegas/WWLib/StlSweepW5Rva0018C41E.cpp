// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0018C41EElement { char bytes[2]; bool operator<(const Rva0018C41EElement&)const; bool operator==(const Rva0018C41EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva0018C41EElement, _STL::allocator<Rva0018C41EElement> >::_M_insert_overflow(Rva0018C41EElement *, Rva0018C41EElement const &, _STL::__true_type const &, unsigned int, bool);
