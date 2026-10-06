// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F643DElement { char bytes[9];Rva003F643DElement();Rva003F643DElement(const Rva003F643DElement&);~Rva003F643DElement();Rva003F643DElement&operator=(const Rva003F643DElement&); bool operator<(const Rva003F643DElement&)const; bool operator==(const Rva003F643DElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003F643DElement * _STL::__copy_backward_ptrs<Rva003F643DElement *, Rva003F643DElement *>(Rva003F643DElement *, Rva003F643DElement *, Rva003F643DElement *, _STL::__false_type const &);
