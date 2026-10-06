// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00426612@Rva00426612@@QAEXPAVCreateAHeroData@@@Z, retail 0x00426612, 76 bytes.
// Move-one registry shuffle: null arg returns; rowed _STL::find 0x0020E873
// over the +0x0C/+0x10 pointer range; miss (== end) returns; hit goes through
// rowed vector<void*>::erase 0x001FF51F, sets byte +0x18C on the item, then
// rowed vector<ModuleData>::push_back 0x004DFCB0 into the +0x18 vector.
// Evidence: callees rowed; caller 0x004DCB6F unclaimed; layout from pushes
// (begin +0x0C, end +0x10, second vector +0x18); precedent
// GateOpenBehaviorListRva004E908C.cpp for the void-pointer erase cast.
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
#include <algorithm>

class CreateAHeroData
{
public:
	char m_pad[0x18C];
	unsigned char m_18C;
};

class ModuleData;

class Rva00426612
{
public:
	void rva00426612(CreateAHeroData *item);
private:
	char m_pad00[0x0C];
	CreateAHeroData **m_begin0C;
	CreateAHeroData **m_end10;
	void *m_cap14;
	const ModuleData **m_beg18;
	const ModuleData **m_end1C;
	const ModuleData **m_cap20;
};

void Rva00426612::rva00426612(CreateAHeroData *item)
{
	if (item == 0)
		return;
	CreateAHeroData **found = _STL::find(m_begin0C, m_end10, item);
	if (found == m_end10)
		return;
	((_STL::vector<void *, _STL::allocator<void *> > *)&m_begin0C)->erase((void **)found);
	item->m_18C = 1;
	((_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *)&m_beg18)->push_back(*(const ModuleData * const *)&item);
}
