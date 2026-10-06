// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0020572FElement {Rva0020572FElement();Rva0020572FElement(const Rva0020572FElement&);Rva0020572FElement&operator=(const Rva0020572FElement&);virtual void slot0();virtual ~Rva0020572FElement();char bytes[4]; bool operator==(const Rva0020572FElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0020572FElement * _STL::__uninitialized_fill_n<Rva0020572FElement *, unsigned int, Rva0020572FElement>(Rva0020572FElement *, unsigned int, Rva0020572FElement const &, _STL::__false_type const &);
