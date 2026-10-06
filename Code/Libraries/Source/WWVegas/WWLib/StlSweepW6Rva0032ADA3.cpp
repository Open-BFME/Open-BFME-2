// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva0032ADA3Element {Rva0032ADA3Element();Rva0032ADA3Element(const Rva0032ADA3Element&);Rva0032ADA3Element&operator=(const Rva0032ADA3Element&);virtual void slot0();virtual ~Rva0032ADA3Element();char bytes[4]; bool operator==(const Rva0032ADA3Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva0032ADA3Element * _STL::__uninitialized_fill_n<Rva0032ADA3Element *, unsigned int, Rva0032ADA3Element>(Rva0032ADA3Element *, unsigned int, Rva0032ADA3Element const &, _STL::__false_type const &);
