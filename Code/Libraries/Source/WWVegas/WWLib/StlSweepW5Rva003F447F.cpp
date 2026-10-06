// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F447FElement { char bytes[9];Rva003F447FElement();Rva003F447FElement(const Rva003F447FElement&);~Rva003F447FElement();Rva003F447FElement&operator=(const Rva003F447FElement&); bool operator<(const Rva003F447FElement&)const; bool operator==(const Rva003F447FElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003F447FElement * _STL::__copy_backward_ptrs<Rva003F447FElement *, Rva003F447FElement *>(Rva003F447FElement *, Rva003F447FElement *, Rva003F447FElement *, _STL::__false_type const &);
