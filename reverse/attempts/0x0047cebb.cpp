// ?rva0047CEBB@HordeSiegeEngineContain@@UAEXP6AXPAVObject@@PAX@Z1H@Z
// partial score=0.97 date=2026-10-10
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /EHsc
// stlport
//
// ?rva0047CEBB@HordeSiegeEngineContain@@UAEXP6AXPAVObject@@PAX@Z1H@Z, retail
// 0x0047CEBB, 125 bytes. HordeSiegeEngineContain's override of the iterate
// slot SlaughterHordeContain::rva004635EC implements (slot 106): the base
// walks the squad list at +0x34; this override adds the rider list at +0x108.
// Flag bit 2 enables the rider walk and bit 3 selects the direction, as in the
// base (whose bit 0 / bit 3 gate its own list): reverse walks the riders
// before the base call, forward walks them after it. The name stays
// address-derived: the slot's method name is unproven beyond class and slot.
#include <list>

namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

class Object;
typedef void (__cdecl *ContainIterateFunc)(Object *obj, void *userData);

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1) SLOT16(s2) SLOT16(s3) SLOT16(s4) SLOT16(s5)
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69();
	virtual void rva004635EC(ContainIterateFunc func, void *userData, int flags);

private:
	char m_pad04[0x34 - 0x04];
	_STL::list<Object *> m_list34;
};

class HordeSiegeEngineContain : public SlaughterHordeContain
{
public:
	virtual void rva0047CEBB(ContainIterateFunc func, void *userData, int flags);

private:
	char m_pad38[0x108 - 0x38];
	_STL::list<Object *> m_riders;
};

void HordeSiegeEngineContain::rva0047CEBB(ContainIterateFunc func, void *userData, int flags)
{
	int allFlags = flags;
	flags &= 4;
	if (flags != 0 && (allFlags & 8) != 0) {
		for (_STL::list<Object *>::iterator it = m_riders.end(); it != m_riders.begin(); ) {
			--it;
			func(*it, userData);
		}
	}
	SlaughterHordeContain::rva004635EC(func, userData, allFlags);
	if (flags != 0 && (allFlags & 8) == 0) {
		for (_STL::list<Object *>::iterator it = m_riders.begin(); it != m_riders.end(); ) {
			Object *rider = *it;
			++it;
			func(rider, userData);
		}
	}
}
