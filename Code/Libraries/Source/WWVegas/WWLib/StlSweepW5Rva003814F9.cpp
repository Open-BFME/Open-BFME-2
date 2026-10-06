// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003814F9Element { char bytes[8]; bool operator<(const Rva003814F9Element&)const; bool operator==(const Rva003814F9Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva003814F9Element * _STL::__uninitialized_fill_n<Rva003814F9Element *, unsigned int, Rva003814F9Element>(Rva003814F9Element *, unsigned int, Rva003814F9Element const &, _STL::__false_type const &);
