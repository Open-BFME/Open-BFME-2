// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?append@Rva005A0B4CList@@QAEXPAURva002BA8F1Listener@@@Z retail 0x005A0B4C 22B
// Append listener as ModuleData to vector. Evidence: named pin plus rowed
// vector push_back 0x004DFCB0; 40+ callers.
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
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	_STL::vector<const ModuleData *> m_vec;
};
void Rva005A0B4CList::append(Rva002BA8F1Listener *p)
{
	const ModuleData *q = (const ModuleData *)(void *)p;
	m_vec.push_back(q);
}
