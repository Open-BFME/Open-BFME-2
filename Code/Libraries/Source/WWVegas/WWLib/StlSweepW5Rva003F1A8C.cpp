// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F1A8CElement {Rva003F1A8CElement();Rva003F1A8CElement(const Rva003F1A8CElement&);Rva003F1A8CElement&operator=(const Rva003F1A8CElement&);~Rva003F1A8CElement(){}char bytes[12]; bool operator==(const Rva003F1A8CElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva003F1A8CElement * _STL::__uninitialized_fill_n<Rva003F1A8CElement *, unsigned int, Rva003F1A8CElement>(Rva003F1A8CElement *, unsigned int, Rva003F1A8CElement const &, _STL::__false_type const &);
