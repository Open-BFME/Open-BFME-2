// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva005348AD@@QAE@XZ
// retail 0x005348AD 58B: honest-address ctor constructing list<BfmePod8> at +0
// via the rowed _List_base 0x0035C9A6 and map<NameKeyType ModuleTemplate> at +4
// via the rowed map ctor 0x00413727 then bool at +0x10 = false.
// Called once from unclaimed 0x002F364A. Evidence: callee rows plus retail
// member layout list(4) map(12) bool.
#include <list>
#include <map>

struct BfmePod8
{
	int a[2];
};

enum NameKeyType
{
	NAMEKEY_FIRST = 0
};

#include "../../Include/Common/ModuleFactoryClass.h"

class Rva005348AD
{
public:
	Rva005348AD();

private:
	_STL::list<BfmePod8> m_list;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate> m_map;
	bool m_flag;
};

// bfme link decl-only begin
namespace _STL { template <> _List_base<BfmePod8,_STL::allocator<BfmePod8> >::_List_base(_STL::allocator<BfmePod8> const &); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::_Rb_tree_base(_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > const &); }
namespace _STL { template <> _List_base<BfmePod8,_STL::allocator<BfmePod8> >::~_List_base(); }
namespace _STL { template <> _Rb_tree<NameKeyType,_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::_Select1st<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> >,_STL::less<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::~_Rb_tree_base(); }
namespace _STL { template <> void _Rb_tree<NameKeyType,_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate>,_STL::_Select1st<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> >,_STL::less<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > *); }
namespace _STL { template <> _STL::_List_node<BfmePod8> * _STLP_alloc_proxy<_STL::_List_node<BfmePod8> *,_STL::_List_node<BfmePod8>,_STL::allocator<_STL::_List_node<BfmePod8> > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > *,_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_List_node<BfmePod8> * allocator<_STL::_List_node<BfmePod8> >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > * allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _List_base<BfmePod8,_STL::allocator<BfmePod8> >::clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_List_node<BfmePod8> *,_STL::_List_node<BfmePod8>,_STL::allocator<_STL::_List_node<BfmePod8> > >::deallocate(_STL::_List_node<BfmePod8> *,unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > *,_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_List_node<BfmePod8> >::deallocate(_STL::_List_node<BfmePod8> *,unsigned int) const; }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<NameKeyType const,ModuleFactory::ModuleTemplate> > *,unsigned int) const; }
// bfme link decl-only end
Rva005348AD::Rva005348AD()
	: m_flag(false)
{
}
