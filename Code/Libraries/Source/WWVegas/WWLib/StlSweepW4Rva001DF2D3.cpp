// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001DF2D3Element { Rva001DF2D3Element();Rva001DF2D3Element(const Rva001DF2D3Element&);~Rva001DF2D3Element();Rva001DF2D3Element&operator=(const Rva001DF2D3Element&);char bytes[48]; bool operator<(const Rva001DF2D3Element&)const; bool operator==(const Rva001DF2D3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001DF2D3Element, _STL::allocator<Rva001DF2D3Element> >::_M_fill_insert(Rva001DF2D3Element *, unsigned int, Rva001DF2D3Element const &);
