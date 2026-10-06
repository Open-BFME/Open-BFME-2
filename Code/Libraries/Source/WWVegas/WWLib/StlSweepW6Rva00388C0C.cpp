// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct Rva00388C0CElement { _STL::auto_ptr<unsigned> value;unsigned word0;Rva00388C0CElement(const Rva00388C0CElement&b);Rva00388C0CElement& operator=(const Rva00388C0CElement&b);bool operator<(const Rva00388C0CElement&)const;bool operator==(const Rva00388C0CElement&)const; };
template class _STL::set<Rva00388C0CElement>;
