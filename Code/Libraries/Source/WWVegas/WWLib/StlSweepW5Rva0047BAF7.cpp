// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

struct Rva0047BAF7Element { unsigned opaque;bool operator<(const Rva0047BAF7Element&)const;bool operator==(const Rva0047BAF7Element&)const; };


// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0047BAF7Element *, _STL::allocator<Rva0047BAF7Element *> >::remove(Rva0047BAF7Element *const &);
