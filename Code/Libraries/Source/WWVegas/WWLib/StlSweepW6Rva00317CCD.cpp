// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00317CCDElement {Rva00317CCDElement();Rva00317CCDElement(const Rva00317CCDElement&);Rva00317CCDElement&operator=(const Rva00317CCDElement&);virtual void slot0();virtual ~Rva00317CCDElement();char bytes[4]; bool operator==(const Rva00317CCDElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00317CCDElement * _STL::__uninitialized_fill_n<Rva00317CCDElement *, unsigned int, Rva00317CCDElement>(Rva00317CCDElement *, unsigned int, Rva00317CCDElement const &, _STL::__false_type const &);
