// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001F070CElement {Rva001F070CElement();Rva001F070CElement(const Rva001F070CElement&);Rva001F070CElement&operator=(const Rva001F070CElement&);~Rva001F070CElement(){}char bytes[12]; bool operator==(const Rva001F070CElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva001F070CElement * _STL::__uninitialized_fill_n<Rva001F070CElement *, unsigned int, Rva001F070CElement>(Rva001F070CElement *, unsigned int, Rva001F070CElement const &, _STL::__false_type const &);
