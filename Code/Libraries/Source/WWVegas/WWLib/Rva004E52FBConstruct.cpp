// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@VRva004E5012@@V1@@_STL@@YAXPAVRva004E5012@@ABV1@@Z @0x004E52FB (45B)
// True _STL::_Construct for the Rva004E5012 element: placement copy via the rowed copy ctor at 0x004E5012.
// Evidence: chain lane caller 0x004E54A1 (_M_create_node list Pod60 site); BfmePod60 pin at same address is the size-view twin.
#include <vector>

class Rva004E5012 {
public:
	Rva004E5012(const Rva004E5012 &);
	Rva004E5012 &operator=(const Rva004E5012 &);
	~Rva004E5012();
};

namespace _STL {
template <> void _Construct<Rva004E5012, Rva004E5012>(
	Rva004E5012 *p, const Rva004E5012 &val)
{
	new ((void *)p) Rva004E5012(val);
}
}
