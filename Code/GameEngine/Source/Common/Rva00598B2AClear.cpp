// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00598B2A@Rva00598B2A@@QAEXXZ @0x00598B2A 78B via tree-list-vector clear with virtual delete
// Evidence: thiscall ret0; tree clear 0x00598120 at +8; list walk with virtual slot0 int0 plus rowed delete 0x0002FD60; rowed List_base<int> clear 0x0023DAA5 at +0x14; rowed vector<AsciiString> erase 0x0002CCFC at +0x4C; caller unclaimed 0x00598CFD
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <vector>
#include "ascii_string.h"
void __cdecl operator delete(void *p);
class Rva005980F3
{
public:
	void rva00598120();
private:
	void *m_head;
	int m_flag;
};
class RvaObj00598B2A
{
public:
	virtual void *get(int x);
};
class Rva00598B2A
{
public:
	void rva00598B2A();
private:
	char m_pad00[8];
	Rva005980F3 m_tree;
	char m_pad10[4];
	_STL::list<int> m_list;
	char m_padAfterList[0x4C - 0x14 - sizeof(_STL::list<int>)];
	_STL::vector<AsciiString> m_vec;
};
void Rva00598B2A::rva00598B2A()
{
	m_tree.rva00598120();
	for (_STL::list<int>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		RvaObj00598B2A *o = (RvaObj00598B2A *)(int)*it;
		::operator delete(o ? o->get(0) : 0);
	}
	m_list.clear();
	_STL::vector<AsciiString> &v = m_vec;
	v.erase(v.begin(), v.end());
}
