// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001D9B62Element {Rva001D9B62Element();Rva001D9B62Element(const Rva001D9B62Element&);Rva001D9B62Element&operator=(const Rva001D9B62Element&);virtual void slot0();virtual ~Rva001D9B62Element();char bytes[4]; bool operator==(const Rva001D9B62Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva001D9B62Element * _STL::__uninitialized_fill_n<Rva001D9B62Element *, unsigned int, Rva001D9B62Element>(Rva001D9B62Element *, unsigned int, Rva001D9B62Element const &, _STL::__false_type const &);
