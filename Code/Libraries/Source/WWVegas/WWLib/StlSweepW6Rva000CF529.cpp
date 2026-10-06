// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva000CF529Element {Rva000CF529Element();Rva000CF529Element(const Rva000CF529Element&);Rva000CF529Element&operator=(const Rva000CF529Element&);virtual void slot0();virtual ~Rva000CF529Element();char bytes[4]; bool operator==(const Rva000CF529Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva000CF529Element * _STL::__uninitialized_fill_n<Rva000CF529Element *, unsigned int, Rva000CF529Element>(Rva000CF529Element *, unsigned int, Rva000CF529Element const &, _STL::__false_type const &);
