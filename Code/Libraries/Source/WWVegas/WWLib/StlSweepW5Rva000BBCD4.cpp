// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <deque>






struct Rva000BBCD4Element { _STL::list<short> values[1]; bool operator==(const Rva000BBCD4Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva000BBCD4Element ** _STL::__copy_backward_aux<Rva000BBCD4Element **, Rva000BBCD4Element **>(Rva000BBCD4Element **, Rva000BBCD4Element **, Rva000BBCD4Element **, _STL::__true_type const &);
