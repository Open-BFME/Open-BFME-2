// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00331B6AElement {Rva00331B6AElement();Rva00331B6AElement(const Rva00331B6AElement&);Rva00331B6AElement&operator=(const Rva00331B6AElement&);~Rva00331B6AElement(){}char bytes[12]; bool operator==(const Rva00331B6AElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00331B6AElement * _STL::__uninitialized_fill_n<Rva00331B6AElement *, unsigned int, Rva00331B6AElement>(Rva00331B6AElement *, unsigned int, Rva00331B6AElement const &, _STL::__false_type const &);
