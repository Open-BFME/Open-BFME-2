// cl: /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00414093@@QAE@ABV0@@Z, retail 0x00414093, 61 bytes. Dedicated TU.
//
// Honest copy ctor for a holder with vector<unsigned> at +0 and the
// ModuleFactory ModuleTemplateMap _Rb_tree at +0xC: copies the vector
// through the rowed 0x002CFAB9 then the tree through the just-landed
// 0x00413EE6. Evidence: chain lane calls both rowed bodies; add edi 0xC
// plus lea ecx [esi+0xC] pins the +0xC tree offset; ret 4 copy-ctor shape
// with EH_prolog.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <vector>
#include <map>

enum NameKeyType
{
	NAMEKEY_0 = 0
};

#include "../../Include/Common/ModuleFactoryClass.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree<NameKeyType,pair<NameKeyType const ,ModuleFactory::ModuleTemplate>,_Select1st<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> >,less<NameKeyType>,allocator<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> > >::_Rb_tree(_Rb_tree<NameKeyType,pair<NameKeyType const ,ModuleFactory::ModuleTemplate>,_Select1st<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> >,less<NameKeyType>,allocator<pair<NameKeyType const ,ModuleFactory::ModuleTemplate> > > const &); }

typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryMapValue14093;
typedef _STL::_Select1st<ModuleFactoryMapValue14093> ModuleFactoryMapKeyOf14093;
typedef _STL::less<NameKeyType> ModuleFactoryMapCompare14093;
typedef _STL::allocator<ModuleFactoryMapValue14093> ModuleFactoryMapAlloc14093;
typedef _STL::_Rb_tree<NameKeyType, ModuleFactoryMapValue14093, ModuleFactoryMapKeyOf14093, ModuleFactoryMapCompare14093, ModuleFactoryMapAlloc14093> ModuleFactoryMapTree14093;

namespace _STL {
template <> ModuleFactoryMapTree14093::_Rb_tree(const ModuleFactoryMapTree14093 &);
}

class Rva00414093
{
public:
	Rva00414093(const Rva00414093 &src);
private:
	_STL::vector<unsigned int> m_vec;
	ModuleFactoryMapTree14093 m_tree;
};

Rva00414093::Rva00414093(const Rva00414093 &src) : m_vec(src.m_vec), m_tree(src.m_tree)
{
}
