// cl: /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE@ABV01@@Z,
// retail 0x00413EE6, 165 bytes. Dedicated TU.
//
// ModuleFactory::ModuleTemplateMap red-black tree copy ctor duplicate (chain
// lane: calls the just-landed _M_copy_00413E73 at 0x00413E73, the rowed
// _Rb_tree_base ctor at 0x0030087C and the rowed vector get_allocator fold
// at 0x0021983A). Same 165B shape as the unclaimed 0x004137C6 which calls
// the original copy 0x004136B4. Address-scoped _M_copy rename follows the
// fleet _M_copy_006008E6 precedent since the unsuffixed copy is claimed.
// No commas in notes. Evidence: EH_prolog with handler, empty-tree header
// init, leftmost/rightmost fixup and node-count copy.
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#define _M_copy _M_copy_00413E73
#include <map>

enum NameKeyType
{
	NAMEKEY_0 = 0
};

#include "../../../../GameEngine/Include/Common/ModuleFactoryClass.h"

typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryMapValueCopy00413EE6;
typedef _STL::_Select1st<ModuleFactoryMapValueCopy00413EE6> ModuleFactoryMapKeyOf00413EE6;
typedef _STL::less<NameKeyType> ModuleFactoryMapCompare00413EE6;
typedef _STL::allocator<ModuleFactoryMapValueCopy00413EE6> ModuleFactoryMapAlloc00413EE6;
typedef _STL::_Rb_tree<NameKeyType, ModuleFactoryMapValueCopy00413EE6, ModuleFactoryMapKeyOf00413EE6, ModuleFactoryMapCompare00413EE6, ModuleFactoryMapAlloc00413EE6> ModuleFactoryMapTreeCopy00413EE6;

template ModuleFactoryMapTreeCopy00413EE6::_Rb_tree(const ModuleFactoryMapTreeCopy00413EE6 &);

#undef _M_copy

// The outer map copy constructor at retail 0x00413FF7 (18 bytes): forwards to the tree
// member instantiated above and returns this.
template _STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType >, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > >::map(const _STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType >, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > &);
