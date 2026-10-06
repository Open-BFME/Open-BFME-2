// ?rva002B8AC0@Rva002B8AC0@@QAEXPBVModuleData@@@Z
// recovered 2026-10-05 from the 0.93 bank; exact 42/42
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8AC0@Rva002B8AC0@@QAEXPBVModuleData@@@Z @0x002B8AC0 42B.
// Push ModuleData* into vector at +0xCC or +0xD8 based on byte at [p+8]
// via rowed push_back 0x004DFCB0. Callers in 0x00211396 0x00565148 etc.
// Retail spills the argument back to its own slot before taking its address,
// so each arm binds its own named copy of the pointer; a single hoisted copy
// drops the redundant store and emits 39B.
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

class ModuleData
{
public:
	unsigned char m_pad[8];
	unsigned char m_flag8;
};

class Rva002B8AC0
{
public:
	void rva002B8AC0(const ModuleData *p);
private:
	char m_pad[0xCC];
	_STL::vector<const ModuleData *> m_cc;
	_STL::vector<const ModuleData *> m_d8;
};

void Rva002B8AC0::rva002B8AC0(const ModuleData *p)
{
	if (p->m_flag8)
	{
		const ModuleData *slot = p;
		m_d8.push_back(slot);
	}
	else
	{
		const ModuleData *slot = p;
		m_cc.push_back(slot);
	}
}
