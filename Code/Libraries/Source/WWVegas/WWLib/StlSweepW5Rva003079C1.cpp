// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003079C1Element { char bytes[9];Rva003079C1Element();Rva003079C1Element(const Rva003079C1Element&);~Rva003079C1Element();Rva003079C1Element&operator=(const Rva003079C1Element&); bool operator<(const Rva003079C1Element&)const; bool operator==(const Rva003079C1Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva003079C1Element, _STL::allocator<Rva003079C1Element> >::swap(_STL::vector<Rva003079C1Element, _STL::allocator<Rva003079C1Element> > &);
