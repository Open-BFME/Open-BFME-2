// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F6477Element {Rva003F6477Element();Rva003F6477Element(const Rva003F6477Element&);Rva003F6477Element&operator=(const Rva003F6477Element&);~Rva003F6477Element(){}char bytes[28]; bool operator==(const Rva003F6477Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva003F6477Element * _STL::__copy<Rva003F6477Element *, Rva003F6477Element *, int>(Rva003F6477Element *, Rva003F6477Element *, Rva003F6477Element *, _STL::random_access_iterator_tag const &, int *);
