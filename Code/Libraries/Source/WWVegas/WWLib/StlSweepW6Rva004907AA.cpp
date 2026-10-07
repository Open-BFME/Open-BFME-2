// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>
#include <utility>

struct Rva004907AAElement { unsigned char words[1];bool operator<(const Rva004907AAElement&)const;bool operator==(const Rva004907AAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva004907AAElement, _STL::allocator<Rva004907AAElement> >::pop_front(void);
