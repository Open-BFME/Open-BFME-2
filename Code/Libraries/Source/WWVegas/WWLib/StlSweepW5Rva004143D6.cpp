// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva004143D6Element { char bytes[9];Rva004143D6Element();Rva004143D6Element(const Rva004143D6Element&);~Rva004143D6Element();Rva004143D6Element&operator=(const Rva004143D6Element&); bool operator<(const Rva004143D6Element&)const; bool operator==(const Rva004143D6Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva004143D6Element * _STL::vector<Rva004143D6Element, _STL::allocator<Rva004143D6Element> >::_M_allocate_and_copy<Rva004143D6Element const *>(unsigned int, Rva004143D6Element const *, Rva004143D6Element const *);
