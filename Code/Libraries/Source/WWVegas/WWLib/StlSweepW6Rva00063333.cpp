// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <memory>
#include <utility>

struct Rva00063333Element { unsigned char words[1];bool operator<(const Rva00063333Element&)const;bool operator==(const Rva00063333Element&)const; };
template class _STL::deque<Rva00063333Element>;
