// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004EB794@Rva004EB794@@QAE_NPBVModuleData@@@Z @0x004EB794 56B
// Evidence: unlock thiscall ret 4 1 arg; vector at +8 begin/end via +8 +0xC; loops items comparing +0x50 key to arg +0x50; duplicate returns false else push_back rowed 0x004DFCB0 returns true; caller 0x004E9D24.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
class ModuleData
{
public:
	char m_pad[0x50];
	int m_50;
};
class Rva004EB794
{
public:
	bool rva004EB794(const ModuleData *d);
private:
	char m_pad[8];
	_STL::vector<const ModuleData *> m_vec08;
};

bool Rva004EB794::rva004EB794(const ModuleData *d)
{
	const ModuleData **end = m_vec08.end();
	const ModuleData **p = m_vec08.begin();
	for (; p != end; ++p)
	{
		if ((*p)->m_50 == d->m_50)
			return false;
	}
	m_vec08.push_back(d);
	return true;
}
