// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004635EC@SlaughterHordeContain@@UAEXP6AXPAVObject@@PAX@Z1H@Z, retail 0x004635EC, 83 bytes.
// Virtual slot 106 (offset 0x1A8) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Iterates the list at this+0x34 with a
// ContainIterateFunc callback: bit0 of the int flags enables iteration,
// bit3 selects reverse (prev links) vs forward (next links), data at node+8.
// No direct callees (callback via param); honest address name since method
// identity is unproven beyond class plus slot.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
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

void SlaughterHordeContain::rva004635EC(ContainIterateFunc func, void *userData, int flags)
{
	if ((flags & 1) == 0)
		return;
	if ((flags & 8) != 0) {
		for (_STL::list<Object *>::iterator it = m_list34.end(); it != m_list34.begin(); ) {
			--it;
			func(*it, userData);
		}
	} else {
		for (_STL::list<Object *>::iterator it = m_list34.begin(); it != m_list34.end(); ) {
			Object *rider = *it;
			++it;
			func(rider, userData);
		}
	}
}
