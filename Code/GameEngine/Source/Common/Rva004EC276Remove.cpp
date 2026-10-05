// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004EC276@Rva004EC276@@QAEXPAX@Z @ 0x004EC276, 94 bytes.
// Removes value from vector<void*> at +0x130 and list<int> at +0x13C.
// Evidence: callees are rowed vector<void*>::erase 0x001FF51F and
// list<int>::erase 0x00438539; caller 0x0055ADBA passes its this as value;
// vector loop with cmp [eax] ebx erase-or-add-4 and list loop with cmp
// [eax+8] ebx struct-return erase reusing param slot; Rva honest-address name
// since caller class is UNCLAIMED.
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
#include <list>

class ModuleData;

class Rva004EC276
{
public:
	void rva004EC276(void *value);
	void rva004EC83F(void *p);
	char m_pad[0x130];
	_STL::vector<void *, _STL::allocator<void *> > m_vec;
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva004EC276::rva004EC276(void *value)
{
	_STL::vector<void *>::iterator it = m_vec.begin();
	while (it != m_vec.end()) {
		if (*it == value)
			it = m_vec.erase(it);
		else
			++it;
	}
	_STL::list<int>::iterator jt = m_list.begin();
	while (jt != m_list.end()) {
		if (*jt == (int)value)
			jt = m_list.erase(jt);
		else
			++jt;
	}
}

// ?rva004EC83F@Rva004EC276@@QAEXPAX@Z @ 0x004EC83F, 42 bytes.
// Pushes p onto vector at +0x130 when p->+0x10==0 else onto list at +0x13C.
// Evidence: rowed vector<ModuleData*>::push_back 0x004DFCB0 and rowed
// list<int>::push_back 0x0005548F share one lea-push of &p; cmp [eax+0x10],0
// matches Rva004ECDC8 m_unk10 and caller 0x0055AD91 and-ing [esi+0x10]; same
// Rva004EC276 class as rva004EC276 (same +0x130/+0x13C).
void Rva004EC276::rva004EC83F(void *p)
{
	if (*(int *)((char *)p + 0x10) == 0)
		((_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > &)m_vec).push_back((const ModuleData *&)p);
	else
		m_list.push_back((int &)p);
}
