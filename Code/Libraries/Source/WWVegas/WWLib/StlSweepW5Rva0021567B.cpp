// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <deque>






struct Rva0021567BElement { _STL::list<short> values[1]; bool operator==(const Rva0021567BElement&) const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva0021567BElement ** _STL::__copy_backward_aux<Rva0021567BElement **, Rva0021567BElement **>(Rva0021567BElement **, Rva0021567BElement **, Rva0021567BElement **, _STL::__true_type const &);
