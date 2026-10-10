// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element name remains address-derived. Native ArrowStorm 49083C reads a
// four-byte ID from node+8 before GameLogic::findObjectByID; width is target evidence.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>
#include <utility>

struct Rva004907AAElement { unsigned int id;bool operator<(const Rva004907AAElement&)const;bool operator==(const Rva004907AAElement&)const; };

// Native uses the owned pooled erase specialization at2ABB20, not generic
// allocator deallocation. Suppress the generic body and bind the real provider.
template<> _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::iterator _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::erase(iterator);

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva004907AAElement, _STL::allocator<Rva004907AAElement> >::pop_front(void);
