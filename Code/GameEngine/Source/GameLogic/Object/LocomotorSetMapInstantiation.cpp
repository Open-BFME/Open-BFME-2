// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// LocomotorSetType to template-vector map instantiation (AIUpdate parse cluster).

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
// Suppress this TU's non-retail copy of ?find@?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorT:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> _Rb_tree_iterator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > >,_Const_traits<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > > map<LocomotorSetType,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> >,less<LocomotorSetType>,allocator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::find(LocomotorSetType const &) const; }
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@P:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> _Rb_tree_node<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > * _Rb_tree<LocomotorSetType,pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > >,_Select1st<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > >,less<LocomotorSetType>,allocator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::_M_create_node(pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > const &); }
// Suppress this TU's non-retail copy of ??0?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemp:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> map<LocomotorSetType,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> >,less<LocomotorSetType>,allocator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::map(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> _Rb_tree_base<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > >,allocator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::_Rb_tree_base(allocator<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > const &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> _Rb_tree_node<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > * allocator<_Rb_tree_node<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::allocate(unsigned int,void const *) const; }

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/LocomotorSetType.h"















typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

// The retail map helpers are provided out of line. Avoid competing tree copies.
typedef _STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> BfmeRetailLocomotorValue;
typedef _STL::_Rb_tree<LocomotorSetType, BfmeRetailLocomotorValue,
    _STL::_Select1st<BfmeRetailLocomotorValue>, _STL::less<LocomotorSetType>,
    _STL::allocator<BfmeRetailLocomotorValue> > BfmeRetailLocomotorTree;
namespace _STL {
// Inline the vendor iterator wrapper without emitting a second external copy.
template <> template <> __declspec(dllimport) __forceinline
BfmeRetailLocomotorTree::const_iterator BfmeRetailLocomotorTree::find<LocomotorSetType>(const LocomotorSetType &key) const
{ return const_iterator(_M_find(key)); }
// The complete tree destructor is emitted by LocomotorSetMapSubscript.cpp.
template <> BfmeRetailLocomotorTree::~_Rb_tree();
template <> BfmeRetailLocomotorTree::_Link_type BfmeRetailLocomotorTree::_M_copy(
    BfmeRetailLocomotorTree::_Link_type, BfmeRetailLocomotorTree::_Link_type);
}

// Native assignment 0x004FFDA5 calls the clear owner at 0x004FF49F.
// The similarly named clear row in this unit owns 0x0026DEE4 instead.
class Rva004FF3DB
{
public:
    void rva004FF3DB(void *node);
    void rva004FF49F();
private:
    void *m_00Head;
    int m_04Flag;
};

namespace _STL {
// ??4?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV01@ABV01@@Z
template <> inline BfmeRetailLocomotorTree&
BfmeRetailLocomotorTree::operator=(const BfmeRetailLocomotorTree& other)
{
    if (this != &other) {
        reinterpret_cast<Rva004FF3DB *>(this)->rva004FF49F();
        _M_node_count = 0;
        _M_key_compare = other._M_key_compare;
        if (other._M_root() == 0) {
            _M_root() = 0;
            _M_leftmost() = this->_M_header._M_data;
            _M_rightmost() = this->_M_header._M_data;
        } else {
            _M_root() = _M_copy(other._M_root(), this->_M_header._M_data);
            _M_leftmost() = _S_minimum(_M_root());
            _M_rightmost() = _S_maximum(_M_root());
            _M_node_count = other._M_node_count;
        }
    }
    return *this;
}
}

// Reuse the verified retail container providers. Native callers use the
// out-of-line map subscript and folded pointer-vector erase/append bodies;
// suppress local default copies that the census proves differ from them.
typedef _STL::vector<const LocomotorTemplate *> BfmeRetailLocomotorVector;
typedef _STL::map<LocomotorSetType, BfmeRetailLocomotorVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeRetailLocomotorVector> > > BfmeRetailLocomotorMap;
namespace _STL { template<> BfmeRetailLocomotorVector& BfmeRetailLocomotorMap::operator[](const LocomotorSetType&); }

template class _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > >;
