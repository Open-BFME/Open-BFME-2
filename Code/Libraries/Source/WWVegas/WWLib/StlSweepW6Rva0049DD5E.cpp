// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0049DD5EElement {Rva0049DD5EElement();Rva0049DD5EElement(const Rva0049DD5EElement&);Rva0049DD5EElement&operator=(const Rva0049DD5EElement&);virtual void slot0();virtual ~Rva0049DD5EElement();char bytes[4]; bool operator==(const Rva0049DD5EElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0049DD5EElement * _STL::__uninitialized_fill_n<Rva0049DD5EElement *, unsigned int, Rva0049DD5EElement>(Rva0049DD5EElement *, unsigned int, Rva0049DD5EElement const &, _STL::__false_type const &);
