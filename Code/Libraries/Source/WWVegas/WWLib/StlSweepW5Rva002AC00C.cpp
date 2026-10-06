// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva002AC00CElement {Rva002AC00CElement();Rva002AC00CElement(const Rva002AC00CElement&);Rva002AC00CElement&operator=(const Rva002AC00CElement&);virtual void slot0();virtual ~Rva002AC00CElement();char bytes[4]; bool operator<(const Rva002AC00CElement&)const; bool operator==(const Rva002AC00CElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva002AC00CElement, _STL::allocator<Rva002AC00CElement> >::push_back(Rva002AC00CElement const &);
