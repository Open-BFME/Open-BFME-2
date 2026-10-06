// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// RVA 0x00569543 dedup push into vector<ModuleData*> at +0x58 via rowed push_back @0x004DFCB0.
class ModuleData;
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
namespace _STL
{
template <class ForwardIter, class T>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T &val);
}
class Rva00569543 {
	char m_pad[0x4C];
	_STL::vector<const ModuleData *> m_sorted;
	_STL::vector<const ModuleData *> m_mods;
public:
	void rva00569543(const ModuleData *m);
	void rva005695F2(const ModuleData *m);
};
void Rva00569543::rva00569543(const ModuleData *m)
{
	for (_STL::vector<const ModuleData *>::iterator it = m_mods.begin(); it != m_mods.end(); ++it) {
		if (*it == m)
			return;
	}
	m_mods.push_back(m);
}
// ?rva005695F2@Rva00569543@@QAEXPBVModuleData@@@Z @0x005695F2 54B sorted dedup insert
// into vector at +0x4C via rowed lower_bound @0x00568F5B and rowed insert @0x003B67B3.
// Caller family at 0x0056970A 0x00569723 0x005697E3 0x005698F2 0x0056A696 proves role.
void Rva00569543::rva005695F2(const ModuleData *m)
{
	typedef _STL::vector<const ModuleData *> Vec;
	struct VecHack
	{
		const unsigned *m_start;
		const unsigned *m_finish;
		const unsigned *m_end;
	};
	const unsigned *last = *(const unsigned *const *)((const char *)this + 0x50);
	Vec *v = (Vec *)((char *)this + 0x4C);
	const unsigned &val = reinterpret_cast<const unsigned &>(m);
	const unsigned *pos = _STL::lower_bound(((const VecHack *)v)->m_start, last, val);
	if (pos == last || *reinterpret_cast<const ModuleData *const *>(pos) != m)
		v->insert(reinterpret_cast<Vec::iterator>(const_cast<unsigned *>(pos)), m);
}
