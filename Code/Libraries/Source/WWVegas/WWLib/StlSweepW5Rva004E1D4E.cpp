// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// Reuse the verified unsigned max body at 0x00013740; this unit
// must not supply a conflicting out-of-line copy.
namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}

struct Rva004E1D4EElement
{
public:
	bool operator<(const Rva004E1D4EElement&)const;
	bool operator==(const Rva004E1D4EElement&)const;
	char bytes[12]; // +0x00
};
template class _STL::vector<Rva004E1D4EElement>;
