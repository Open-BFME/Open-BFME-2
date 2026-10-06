// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0048C872Element {Rva0048C872Element();Rva0048C872Element(const Rva0048C872Element&);Rva0048C872Element&operator=(const Rva0048C872Element&);virtual void slot0();virtual ~Rva0048C872Element();char bytes[4]; bool operator==(const Rva0048C872Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0048C872Element * _STL::__uninitialized_fill_n<Rva0048C872Element *, unsigned int, Rva0048C872Element>(Rva0048C872Element *, unsigned int, Rva0048C872Element const &, _STL::__false_type const &);
