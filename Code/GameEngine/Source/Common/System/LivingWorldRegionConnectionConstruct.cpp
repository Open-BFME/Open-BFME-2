// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct for LivingWorldRegionConnection elements.
//
// ??$_Construct@VLivingWorldRegionConnection@@V1@@_STL@@YAXPAVLivingWorldRegionConnection@@ABV1@@Z
// (retail 0x003F2980, 45 bytes): the null-guarded placement-new copy over
// a single element; the copy delegates out-of-line to the rowed element
// copy ctor at 0x003F247D, and __EH_prolog resolves via its matched row.
// Serves the push_back fast path at 0x003F309A plus the copy/fill loops
// at 0x003F29D2/0x003F29AD below.

#include <memory>

class LivingWorldRegionConnection
{
public:
	LivingWorldRegionConnection(const LivingWorldRegionConnection &other);
};

template void _STL::_Construct<LivingWorldRegionConnection, LivingWorldRegionConnection>(LivingWorldRegionConnection *, const LivingWorldRegionConnection &);
