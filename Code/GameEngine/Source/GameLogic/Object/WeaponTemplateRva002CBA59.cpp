// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX- /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002CBA59@WeaponTemplate@@QAEXPAX@Z @0x002CBA59 35B: nugget-append member
// every Weapon-block nugget callback calls last. Copies byte +0x160 to
// nugget +0x124 then pushes the nugget pointer bits as int into list at
// +0x17c via rowed list<int>::push_back 0x0005548F. Evidence: 19 callers in
// WeaponNuggetParse.cpp, pin notes, no donor.
#include <list>

class WeaponTemplate
{
public:
	void rva002CBA59(void *nugget);
private:
	char m_pad00[0x160];
	unsigned char m_160;
	char m_pad161[0x17c - 0x161];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void WeaponTemplate::rva002CBA59(void *nugget)
{
	((unsigned char *)nugget)[0x124] = m_160;
	m_list.push_back((int &)nugget);
}
