// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
#include <memory>

struct Rva0007E394Element { unsigned opaque;bool operator<(const Rva0007E394Element&)const;bool operator==(const Rva0007E394Element&)const; };
template class _STL::hash_map<unsigned,Rva0007E394Element*>;

