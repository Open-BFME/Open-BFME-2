// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva00526103Element {Rva00526103Element();Rva00526103Element(const Rva00526103Element&);Rva00526103Element&operator=(const Rva00526103Element&);virtual void slot0();virtual ~Rva00526103Element();char bytes[4]; bool operator<(const Rva00526103Element&)const; bool operator==(const Rva00526103Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva00526103Element, _STL::allocator<Rva00526103Element> >::push_back(Rva00526103Element const &);
