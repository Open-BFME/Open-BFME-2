// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva005F22D2@Rva005F22D2@@QAEXXZ, retail 0x005F22D2, 60 bytes.
// List at +0x00 with map<int void*> at +0x10; clears map notifying via forEach 0x005F224E.
// Evidence: callees rowed forEach 0x005F224E erase 0x005530A8 forwarder 0x005CC208; callers unclaimed.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,_STL::_Rb_tree_node<_STL::pair<int const,void *> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,void *> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<int const,void *> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,void *> > *,unsigned int) const; }
namespace _STL { template <> void _Rb_tree<int,_STL::pair<int const,void *>,_STL::_Select1st<_STL::pair<int const,void *> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,void *> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const,void *>,_STL::_Nonconst_traits<_STL::pair<int const,void *> > >); }
// bfme link decl-only end

#include "../../Include/Common/Rva005F224EListener.h"

class Rva005F224EList
{
public:
	void forEach(void (Rva005F224EListener::*notify)(void *, int), void *arg, int value);
private:
	Rva005F224EListener **m_begin;
	Rva005F224EListener **m_end;
	Rva005F224EListener **m_capacity;
	unsigned int m_index;
};

class Rva005CC208
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void rva005CC208();
};

class Rva005F22D2
{
public:
	void rva005F22D2();
private:
	Rva005F224EList m_list00;
	_STL::map<int, void *> m_map10;
};

void Rva005F22D2::rva005F22D2()
{
	while (!m_map10.empty()) {
		int key = m_map10.begin()->first;
		m_list00.forEach((void (Rva005F224EListener::*)(void *, int))&Rva005CC208::rva005CC208, this, key);
		m_map10.erase(m_map10.begin());
	}
}
