// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@URva003F610FElement@@U1@@_STL@@YAXPAURva003F610FElement@@ABU1@@Z @ 0x003F5822 45B
// True _STL::_Construct for the 48-byte Rva003F610FElement: placement copy via the pinned copy ctor at 0x003F54DC.
// Evidence: called by 4 matched rows (uninitialized_copy/fill_n/insert_overflow/push_back); BfmePod48 pin at same address is the size-view twin.
#include <vector>

struct Rva003F610FElement {
	char opaque[48];
	Rva003F610FElement(const Rva003F610FElement &);
	Rva003F610FElement &operator=(const Rva003F610FElement &);
	~Rva003F610FElement();
};

namespace _STL {
template <> void _Construct<Rva003F610FElement, Rva003F610FElement>(
	Rva003F610FElement *p, const Rva003F610FElement &val)
{
	new ((void *)p) Rva003F610FElement(val);
}
}
