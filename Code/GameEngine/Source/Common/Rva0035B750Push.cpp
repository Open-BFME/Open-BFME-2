// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX-
// stlport
// ?rva0035B750@Rva0035B750@@QAEXPBVModuleData@@@Z retail 0x0035B750 45B
// Empty-or-first setter over ModuleData vector at +0xec storing to +0xfc.
// Evidence: unlock lane, callers 0x0031BE58 0x0053D355, rowed push_back 0x004DFCB0.
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

#include "ascii_string.h"

class ModuleData
{
};

class Rva0035B750
{
public:
	void rva0035B750(const ModuleData *arg);

private:
	char m_pad[0xec];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec;
	char m_pad2[0x4];
	int m_selected;
};

void Rva0035B750::rva0035B750(const ModuleData *arg)
{
	if (m_vec.empty()) {
		m_selected = 0;
		m_vec.push_back(arg);
	} else {
		m_vec[0] = arg;
	}
}
