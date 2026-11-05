// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8A9F@Rva002B8A9F@@QAEXPAVModuleData@@@Z @0x002B8A9F 33B.
// Push-once ModuleData* into vector at +0x118 if byte at [p+0x75] clear
// then set it, via rowed push_back 0x004DFCB0. Callers in 0x002BA3DA etc.
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

#include "../../../../GameEngine/Include/Common/ModuleData.h"

// Opaque record offsets; keep the canonical ModuleData pointer in the ABI.
struct Rva002B8A9FRecordView
{
	char m_pad[0x75];
	unsigned char m_flag75;
};

class Rva002B8A9F
{
public:
	void rva002B8A9F(ModuleData *p);
private:
	char m_pad[0x118];
	_STL::vector<const ModuleData *> m_118;
};

void Rva002B8A9F::rva002B8A9F(ModuleData *moduleData)
{
	if (reinterpret_cast<Rva002B8A9FRecordView *>(moduleData)->m_flag75)
		return;
	reinterpret_cast<Rva002B8A9FRecordView *>(moduleData)->m_flag75 = 1;
	m_118.push_back(moduleData);
}
