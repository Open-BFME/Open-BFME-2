// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F9004@Rva003F9004@@QAEXPBVModuleData@@@Z @0x003F9004 23B null-checked vector push_back.
// Evidence: calls rowed ?push_back@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEXABQBVModuleData@@@Z 0x004DFCB0 with vector at this+0xC; callers 0x003F90B9 0x003F9162 in 0x003F907B; same lea-push-add-call shape as stlport_moduledatavector_push and Rva002129A1PushBack.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;

class Rva003F9004
{
public:
	void rva003F9004(const ModuleData *p);
private:
	unsigned char m_pad[0xC];
	_STL::vector<const ModuleData *> m_vec;
};

void Rva003F9004::rva003F9004(const ModuleData *p)
{
	if (p != 0)
		m_vec.push_back(p);
}
