// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F63B3Element {Rva003F63B3Element();Rva003F63B3Element(const Rva003F63B3Element&);Rva003F63B3Element&operator=(const Rva003F63B3Element&);~Rva003F63B3Element(){}char bytes[28]; bool operator==(const Rva003F63B3Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva003F63B3Element * _STL::__copy_backward<Rva003F63B3Element *, Rva003F63B3Element *, int>(Rva003F63B3Element *, Rva003F63B3Element *, Rva003F63B3Element *, _STL::random_access_iterator_tag const &, int *);
