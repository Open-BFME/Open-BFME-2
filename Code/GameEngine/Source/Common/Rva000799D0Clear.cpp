// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva000799D0@Rva000799D0@@QAEXXZ @0x000799D0 23B via list clear plus sentinel free
// Evidence: thiscall ret0; rowed List_base<string> clear at +0 then rowed _free 0x00030830 of node ptr; callers 0x0007A52E 0x004251A8 plus thunk 0x00424A09
#include <list>
#include <string>

extern "C" void __cdecl free(void *);

class Rva000799D0
{
public:
	void rva000799D0();
private:
	_STL::list<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > m_list;
};

void Rva000799D0::rva000799D0()
{
	m_list.clear();
	void *p = *(void **)&m_list;
	if (p != 0)
		free(p);
}
