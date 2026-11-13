// cl: /MD /Oa
// stlport
#include <map>
// bfme link decl-only begin
namespace _STL { template <> void _Construct<_STL::pair<int const,int>,_STL::pair<int const,int> >(_STL::pair<int const,int> *,_STL::pair<int const,int> const &); }
namespace _STL { template <> pair<int const,int>::pair(int const &,int const &); }
namespace _STL { template <> pair<int const,int>::pair(_STL::pair<int const,int> const &); }
namespace _STL { template <> pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool>::pair(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > const &,bool const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator++(); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator--(); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::_M_create_node(_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::_M_insert(_STL::_Rb_tree_node_base *,_STL::_Rb_tree_node_base *,_STL::pair<int const,int> const &,_STL::_Rb_tree_node_base *); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,int> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,int> > *,unsigned int) const; }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool> _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::pair<int const,int> const &); }
namespace _STL { template <> int & map<int,int,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::operator[](int const &); }
// bfme link decl-only end

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

enum WeaponSetType
{
	WST_0 = 0
};

#include "../object.h"

#include "../../../../Include/GameLogic/Module/Rva00469294.h"

#include "../../../../Include/Common/BfmeObject872Header.h"

struct HordeContainSlot
{
	int m_key;
	char m_pad[0x18];
};

class HordeContain
{
public:
	// Slot 32 of HordeContain's vftable 0x00C45050 (inherited unchanged by
	// HorseHordeContain and AODHordeContain): virtual, with the vptr at +0.
	virtual void rva00472CA9(Object *obj);
private:
	Rva00469294 *m_4;
	unsigned char m_pad2[0x17C - 0x8];
	_STL::map<int, int> m_map;
	HordeContainSlot *m_slots;
};

void HordeContain::rva00472CA9(Object *obj)
{
	int id = obj->m_id;
	int v = m_map[id];
	int key = *(int *)((char *)m_slots + v * 0x1C);
	void *e = m_4->rva00469294(key);
	if (!e)
		return;
	if (*(unsigned char *)((char *)e + 0x34) == 0)
		return;
	BfmeObject872Header h1(*(BfmeObject872Header *)((char *)e + 0x14));
	BfmeObject872Header h2(*(BfmeObject872Header *)((char *)e + 0x24));
	for (int i = 0; i < 0x68; ++i) {
		unsigned int bit = 1u << (i & 31);
		unsigned int word = ((unsigned int)i >> 5) * 4;
		if (*(unsigned int *)((char *)&h1 + word) & bit)
			obj->setWeaponSetFlag((WeaponSetType)i);
		else if (*(unsigned int *)((char *)&h2 + word) & bit)
			obj->clearWeaponSetFlag((WeaponSetType)i);
	}
}
