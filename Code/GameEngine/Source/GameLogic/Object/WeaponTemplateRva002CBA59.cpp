// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002CBA59@WeaponTemplate@@QAEXPAX@Z @0x002CBA59 35B: nugget-append member
// every Weapon-block nugget callback calls last. Copies byte +0x160 to
// nugget +0x124 then pushes the nugget pointer bits as int into list at
// +0x17c via rowed list<int>::push_back 0x0005548F. Evidence: 19 callers in
// WeaponNuggetParse.cpp, pin notes, no donor.
#include <list>

// LINK: single-node insert binds the verified native STLport owner at RVA
// 0x005925E2; keep the out-of-line call without emitting a competing copy.
namespace _STL {
template <> list<int>::iterator list<int>::insert(iterator position, const int &x);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

#include "../../../Include/GameLogic/WeaponTemplate.h"

void WeaponTemplate::rva002CBA59(void *nugget)
{
	((unsigned char *)nugget)[0x124] = m_field160;
	((_STL::list<int, _STL::allocator<int> > *)&m_field17C)->push_back((int &)nugget);
}
