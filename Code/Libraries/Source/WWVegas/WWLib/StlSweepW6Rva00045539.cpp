// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <memory>
#include <utility>

// Reuse the verified unsigned max body at 0x00013740; this unit
// must not supply a conflicting out-of-line copy.
namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}

struct Rva00045539Element { unsigned char words[1];bool operator<(const Rva00045539Element&)const;bool operator==(const Rva00045539Element&)const; };
template class _STL::deque<Rva00045539Element>;
