// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva004390F7Element {Rva004390F7Element();Rva004390F7Element(const Rva004390F7Element&);Rva004390F7Element&operator=(const Rva004390F7Element&);virtual void slot0();virtual ~Rva004390F7Element();char bytes[4]; bool operator<(const Rva004390F7Element&)const; bool operator==(const Rva004390F7Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva004390F7Element, _STL::allocator<Rva004390F7Element> >::push_back(Rva004390F7Element const &);
