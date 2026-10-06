// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0026068AElement {Rva0026068AElement();Rva0026068AElement(const Rva0026068AElement&);Rva0026068AElement&operator=(const Rva0026068AElement&);virtual void slot0();virtual ~Rva0026068AElement();char bytes[4]; bool operator==(const Rva0026068AElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0026068AElement * _STL::__uninitialized_fill_n<Rva0026068AElement *, unsigned int, Rva0026068AElement>(Rva0026068AElement *, unsigned int, Rva0026068AElement const &, _STL::__false_type const &);
