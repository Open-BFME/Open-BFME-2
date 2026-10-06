// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>
#include <vector>

struct Rva004F8C16Element { char bytes[4];Rva004F8C16Element();Rva004F8C16Element(const Rva004F8C16Element&);~Rva004F8C16Element();Rva004F8C16Element&operator=(const Rva004F8C16Element&); bool operator<(const Rva004F8C16Element&)const; bool operator==(const Rva004F8C16Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__inplace_merge_aux<Rva004F8C16Element *, Rva004F8C16Element, int, _STL::less<Rva004F8C16Element> >(Rva004F8C16Element *, Rva004F8C16Element *, Rva004F8C16Element *, Rva004F8C16Element *, int *, _STL::less<Rva004F8C16Element>);
