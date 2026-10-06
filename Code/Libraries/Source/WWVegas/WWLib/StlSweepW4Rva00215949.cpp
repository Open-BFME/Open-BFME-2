// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00215949Element { Rva00215949Element();Rva00215949Element(const Rva00215949Element&);~Rva00215949Element();Rva00215949Element&operator=(const Rva00215949Element&);char bytes[16]; bool operator<(const Rva00215949Element&)const; bool operator==(const Rva00215949Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva00215949Element, _STL::allocator<Rva00215949Element> >::_M_fill_insert(Rva00215949Element *, unsigned int, Rva00215949Element const &);
