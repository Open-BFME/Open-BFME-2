// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>






struct Rva005EF3FEElement { _STL::list<short> values[1]; bool operator==(const Rva005EF3FEElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva005EF3FEElement * _STL::__uninitialized_copy<Rva005EF3FEElement const *, Rva005EF3FEElement *>(Rva005EF3FEElement const *, Rva005EF3FEElement const *, Rva005EF3FEElement *, _STL::__false_type const &);
