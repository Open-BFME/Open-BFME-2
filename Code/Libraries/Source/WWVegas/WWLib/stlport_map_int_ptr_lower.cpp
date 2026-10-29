// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// Dedicated TU for map<unsigned,void*>::_M_lower_bound. Reloc named this
// address as the signed-int tree but retail uses jb not jl.

#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>

// Inline unsigned comparison belongs to the caller; the retail owner supplies
// the external less<unsigned> body without a competing local COMDAT.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int& a, const unsigned int& b) const
{ return a < b; }
}

// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned int const, void *>, _Nonconst_traits<pair<unsigned int const, void *> > >, bool> _Rb_tree<unsigned int, pair<unsigned int const, void *>, _Select1st<pair<unsigned int const, void *> >, less<unsigned int>, allocator<pair<unsigned int const, void *> > >::insert_unique(pair<unsigned int const, void *> const &); }
// bfme link decl-only end

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

typedef _STL::pair<const unsigned, void *> PairIntPtrLower;
typedef _STL::_Rb_tree<unsigned, PairIntPtrLower, _STL::_Select1st<PairIntPtrLower>, _STL::less<unsigned>, _STL::allocator<PairIntPtrLower> > TreeIntPtrLower;
typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<PairIntPtrLower> > MapIntPtrLower;

// Retail's two clone calls in _M_copy reach the existing ModuleFactory tree
// owner at 0x00413E55. Preserve that provider's full value type instead of
// emitting a pointer-pair clone under the legacy caller's template name.
enum NameKeyType { NAMEKEY_0 = 0 };
class ModuleFactory
{
public:
    class ModuleTemplate
    {
    public:
        void *m_createProc;
        void *m_createDataProc;
        int m_whichInterfaces;
    };
};
typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleCloneValue;
typedef _STL::_Rb_tree<NameKeyType, ModuleCloneValue,
    _STL::_Select1st<ModuleCloneValue>, _STL::less<NameKeyType>,
    _STL::allocator<ModuleCloneValue> > ModuleCloneTree;
namespace _STL {
template <> ModuleCloneTree::_Link_type ModuleCloneTree::_M_clone_node(ModuleCloneTree::_Link_type);
}
struct ModuleCloneAccess : ModuleCloneTree
{
    using ModuleCloneTree::_M_clone_node;
};
namespace _STL {
// ?_M_copy@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBIPAX@_STL@@@2@PAU32@0@Z
template <> inline TreeIntPtrLower::_Link_type
TreeIntPtrLower::_M_copy(TreeIntPtrLower::_Link_type node, TreeIntPtrLower::_Link_type parent)
{
    _Link_type top = (_Link_type)((ModuleCloneAccess *)this)->_M_clone_node(
        (ModuleCloneTree::_Link_type)node);
    top->_M_parent = parent;
    if (node->_M_right)
        top->_M_right = _M_copy((_Link_type)node->_M_right, top);
    parent = top;
    node = (_Link_type)node->_M_left;
    while (node != 0) {
        _Link_type next = (_Link_type)((ModuleCloneAccess *)this)->_M_clone_node(
            (ModuleCloneTree::_Link_type)node);
        parent->_M_left = next;
        next->_M_parent = parent;
        if (node->_M_right)
            next->_M_right = _M_copy((_Link_type)node->_M_right, next);
        parent = next;
        node = (_Link_type)node->_M_left;
    }
    return top;
}
}

// Explicit single-member instantiations for the 7 rows this TU owns.
// Replaces the former whole-class instantiation, which emitted 140 COMDAT
// copies including 7 that differ from retail (link lane). Each line emits
// exactly one owned body; calls to shared helpers reach the retail copy
// another TU provides.
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_lower_bound(const unsigned &) const;
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_upper_bound(const unsigned &) const;
template TreeIntPtrLower::_Link_type TreeIntPtrLower::_M_find<unsigned>(const unsigned &) const;
template TreeIntPtrLower::iterator TreeIntPtrLower::insert_unique(TreeIntPtrLower::iterator, const TreeIntPtrLower::value_type &);
template TreeIntPtrLower::_Rb_tree(const TreeIntPtrLower &);
template bool MapIntPtrLower::value_compare::operator()(const MapIntPtrLower::value_type &, const MapIntPtrLower::value_type &) const;

