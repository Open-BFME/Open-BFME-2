// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002ABFA0@Rva002ABFA0@@QAEXPAX@Z, RVA 0x002ABFA0, size 35.
// Evidence: caller 0x003BD062 passes Player as this and void* from Rva002D06CAGet;
// this+0x700 is _STL::list<short> and arg+0x5d8 is short; calls rowed list<short>::remove.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


struct Rva002ABFA0Arg
{
	char m_pad[0x5d8];
	unsigned short m_val;
};

class Rva002ABFA0
{
public:
	void rva002ABFA0(void *p);
	void rva002ACEDF(void *p);
private:
	char m_pad[0x700];
	_STL::list<short, _STL::allocator<short> > m_list;
};

void Rva002ABFA0::rva002ABFA0(void *p)
{
	unsigned short key = *(unsigned short *)((char *)p + 0x5d8);
	m_list.remove((short)key);
}

void Rva002ABFA0::rva002ACEDF(void *p)
{
	unsigned short key = *(unsigned short *)((char *)p + 0x5d8);
	m_list.push_back((short)key);
}
