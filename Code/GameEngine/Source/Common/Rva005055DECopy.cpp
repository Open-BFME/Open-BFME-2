// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva005055DE@Rva005055DE@@QAEXXZ, retail 0x005055DE, 40 bytes.
// Evidence: copies ModuleData ptr range from global g_00E0311C vec at +0xc via rowed push_back 0x004DFCB0 into vec at +0x14; caller jmp 0x0050590C.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;

struct Rva005055DESrc
{
	char m_00[0xc];
	_STL::vector<const ModuleData *> m_0C;
};

// g_00E0311C: matched references place it at VA 0xe0311c (retail .data initial value 0).
Rva005055DESrc * g_00E0311C = 0;

class Rva005055DE
{
	char m_00[0x14];
	_STL::vector<const ModuleData *> m_14;
public:
	void rva005055DE();
};

void Rva005055DE::rva005055DE()
{
	_STL::vector<const ModuleData *> &src = g_00E0311C->m_0C;
	for (_STL::vector<const ModuleData *>::iterator it = src.begin(); it != src.end(); ++it)
		m_14.push_back(*it);
}
