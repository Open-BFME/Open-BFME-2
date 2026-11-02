// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@2@@Z,
// retail 0x00413740, 134 bytes. Dedicated TU.
//
// ModuleFactory::ModuleTemplateMap red-black tree no-hint insert_unique
// (pair<iterator,bool> shape: search with less, decrement on begin miss,
// then _M_insert or existing). Retail calls the rowed _M_insert 0x0041362C
// and the rowed _M_decrement. Same 134B shape as the int-pod16 precedent.
// Evidence: unlock lane makes 0x00414009 and 0x004138C7 ready; left-spine
// search with setl and begin fast path.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

enum NameKeyType
{
	NAMEKEY_0 = 0
};

#include "../../../../GameEngine/Include/Common/ModuleFactoryClass.h"

typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryInsertValue;
typedef _STL::_Rb_tree<NameKeyType, ModuleFactoryInsertValue, _STL::_Select1st<ModuleFactoryInsertValue>, _STL::less<NameKeyType>, _STL::allocator<ModuleFactoryInsertValue> > ModuleFactoryInsertTree;

// The native insertion calls the factory already owned by ModuleFactory.cpp.
template <> ModuleFactoryInsertTree::_Link_type
ModuleFactoryInsertTree::_M_create_node(const ModuleFactoryInsertValue &);

template _STL::pair<ModuleFactoryInsertTree::iterator, bool> ModuleFactoryInsertTree::insert_unique(const ModuleFactoryInsertTree::value_type &);

// The outer map::insert at retail 0x004138A1 (20 bytes): forwards the
// result slot and the argument to the tree/table member of this unit.
typedef _STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType >, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > MP_004138A1;
template _STL::pair<MP_004138A1::iterator, bool> MP_004138A1::insert(const MP_004138A1::value_type &);
