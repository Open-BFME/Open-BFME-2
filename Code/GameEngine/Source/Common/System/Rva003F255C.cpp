// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F255C@Rva003F255C@@QAEXPBVModuleData@@@Z @0x003F255C 26B
// Null-checked push_back into vector at +0xfc. Retail cmp [esp+4] je then
// lea eax [esp+4] push eax add ecx 0xfc call push_back vector PBVModuleData.
// Evidence: unlock lane, callee rowed push_back 0x004DFCB0, caller 0x003F2576
// (LivingWorldRegion ModuleData INI string), prev LivingWorldRegionConnection
// dtor / next Rva003F26AAFinish give flags and stlport vector usage.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;

class Rva003F255C
{
public:
	void rva003F255C(const ModuleData *p);
private:
	char _pad[0xfc];
	_STL::vector<const ModuleData *> m_vec; // +0xfc
};

void Rva003F255C::rva003F255C(const ModuleData *p)
{
	if (p != 0)
		m_vec.push_back(p);
}
