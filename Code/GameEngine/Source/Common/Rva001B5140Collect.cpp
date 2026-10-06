// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001B5140@Rva001B5140@@QAE_NXZ
// ?rva001B5140@Rva001B5140@@QAE_NXZ @0x001B5140 128B. Filter over two arrays
// into the vector at +0x18: clears it via rowed vector<void*> erase, then
// scans the 8-byte-entry array ([this+0]=begin, [this+4]=end) and the
// pointer array ([this+0xC]=begin, [this+0x10]=end), keeping entries whose
// object passes virtual slot 0x14 and collecting them via rowed
// vector<ModuleData*> push_back; returns whether anything was kept.
// Evidence: chain packet (calls 0x31BD55 erase and 0x4DFCB0 push_back, both
// rowed); ret with no N proves __thiscall with no stack args; ecx read
// before write proves thiscall; al return proves bool; neighbours share
// // cl: /Ireference/shims/bfme2_ascii /O1 /MD.
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

class ModuleData;

struct Rva001B5140Entry8
{
	void *m_obj; // +0 dereferenced for the slot 0x14 call
	int m_pad; // +4 keeps the 8-byte stride retail steps
};

class Rva001B5140Pred
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual bool vf5();
};

class Rva001B5140
{
public:
	bool rva001B5140();

private:
	Rva001B5140Entry8 *m_firstBegin; // +0
	Rva001B5140Entry8 *m_firstEnd; // +4
	void *m_pad8; // +8 capacity of the first array, untouched
	const ModuleData **m_secondBegin; // +0xC
	const ModuleData **m_secondEnd; // +0x10
	void *m_pad14; // +0x14 capacity of the second array, untouched
	_STL::vector<const ModuleData *> m_vec; // +0x18
};

bool Rva001B5140::rva001B5140()
{
	bool found = false;
	_STL::vector<void *> &clearVec = (_STL::vector<void *> &)m_vec;
	clearVec.erase(clearVec.begin(), clearVec.end());
	for (Rva001B5140Entry8 *p = m_firstBegin; p != m_firstEnd; ++p) {
		const ModuleData *obj = (const ModuleData *)p->m_obj;
		if (obj == 0)
			continue;
		if (!((Rva001B5140Pred *)obj)->vf5())
			continue;
		found = true;
		m_vec.push_back(obj);
	}
	for (const ModuleData **q = m_secondBegin; q != m_secondEnd; ++q) {
		const ModuleData *obj = *q;
		if (obj == 0)
			continue;
		if (!((Rva001B5140Pred *)obj)->vf5())
			continue;
		found = true;
		m_vec.push_back(obj);
	}
	return found;
}
