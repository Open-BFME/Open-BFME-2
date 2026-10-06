// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00239FE4@Rva00239FE4@@QAEXPBVModuleData@@@Z @0x00239FE4 48B: vector dedup at this+0xE8 via push_back 0x004DFCB0. Evidence: caller at 0x00362E00 same vector shape as 0x00423A68.
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
class Rva00239FE4
{
	char m_pad[0xE8];
	_STL::vector<const ModuleData *> m_vec;
public:
	void rva00239FE4(const ModuleData *p);
};
void Rva00239FE4::rva00239FE4(const ModuleData *p)
{
	for (_STL::vector<const ModuleData *>::iterator it = m_vec.begin(); it != m_vec.end(); ++it) {
		if (*it == p)
			return;
	}
	m_vec.push_back(p);
}
