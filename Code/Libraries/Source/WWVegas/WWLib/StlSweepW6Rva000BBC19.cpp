// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva000BBC19Element {Rva000BBC19Element();Rva000BBC19Element(const Rva000BBC19Element&);Rva000BBC19Element&operator=(const Rva000BBC19Element&);virtual void slot0();virtual ~Rva000BBC19Element();char bytes[4]; bool operator==(const Rva000BBC19Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva000BBC19Element * _STL::__uninitialized_fill_n<Rva000BBC19Element *, unsigned int, Rva000BBC19Element>(Rva000BBC19Element *, unsigned int, Rva000BBC19Element const &, _STL::__false_type const &);
