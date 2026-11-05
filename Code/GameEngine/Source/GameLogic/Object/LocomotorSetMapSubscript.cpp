// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??A?$map@W4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@1@ABW4LocomotorSetType@@@Z
// retail 0x001EA05B (153 bytes).
//
// LocomotorSetType to template-vector map subscript (AIUpdate parse
// cluster). Miss path builds a default vector temp through the rowed
// _Vector_base 0x211E58, pairs it with the key through 0x796CB, and
// hint-inserts through the rowed wrapper 0x1E9066. /EHs (not /EHsc)
// keeps the post-insert EH state stores; the explicit-spec rvalue pair
// keeps the pair address in eax (no re-lea) and homes the hidden
// insert-result temp at [ebp-0x10].

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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_copy(_Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *, _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_create_node(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Nonconst_traits<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >, bool> _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::insert_unique(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
// bfme link decl-only end
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
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVLocomotorTemplate@@@_STL@@QBEPAPBVLocomotorTemplate@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LocomotorTemplate;
namespace _STL { template <> LocomotorTemplate const * * allocator<LocomotorTemplate const *>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum LocomotorSetType; class LocomotorTemplate;
namespace _STL { template <> _Rb_tree_node<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > * allocator<_Rb_tree_node<pair<LocomotorSetType const ,vector<LocomotorTemplate const *,allocator<LocomotorTemplate const *> > > > >::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@IU?$pair@$$CBIV?$vector@IV?$allocator@I@_STL@@@_STL@@@_STL@@U?$_Select1st@U?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<unsigned int,pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > >,_Select1st<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > >,less<unsigned int>,allocator<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > > >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBIV?$vector@IV?$allocator@I@_STL@@@_STL@@@_STL@@V?$allocator:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > >,allocator<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > > >::_Rb_tree_base(allocator<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > > const &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBIV?$vector@IV?$allocator@I@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > > * allocator<_Rb_tree_node<pair<unsigned int const ,vector<unsigned int,allocator<unsigned int> > > > >::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHV?$vector@IV?$allocator@I@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<int const ,vector<unsigned int,allocator<unsigned int> > > > * allocator<_Rb_tree_node<pair<int const ,vector<unsigned int,allocator<unsigned int> > > > >::allocate(unsigned int,void const *) const; }

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

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
template <> BfmeRetailLocomotorTree::_Link_type BfmeRetailLocomotorTree::_M_copy(
    BfmeRetailLocomotorTree::_Link_type, BfmeRetailLocomotorTree::_Link_type);
template <> BfmeRetailLocomotorTree& BfmeRetailLocomotorTree::operator=(const BfmeRetailLocomotorTree&);
}

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;

template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType& __k)
{
	BfmeLocomotorSetMap::iterator __i = lower_bound(__k);
	if (__i == end() || key_comp()(__k, (*__i).first)) {
		BfmeLocomotorTemplateVector __tmp;
		__i = insert(__i, BfmeLocomotorSetMap::value_type(__k, __tmp));
	}
	return (*__i).second;
}

template class _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > >;

// Native 0x0021E063 has the same scoped-vector expression as 0x001EA05B.
// Its insertion goes to the independently rowed int/vector<unsigned> map
// wrapper 0x0021DB74. The lower-bound walk, empty vector header and pair
// constructor are folded helpers; no Locomotor application identity is claimed
// for this integer-keyed specialization.
typedef _STL::vector<unsigned int> BfmeIntegerMapVector;
// The native pair constructors call the complete copy provider at 0x002CFAB9.
// Reuse it rather than emitting this unit's incompatible allocator variant.
namespace _STL {
template <> BfmeIntegerMapVector::vector(const BfmeIntegerMapVector &);
}
typedef _STL::map<int, BfmeIntegerMapVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmeIntegerMapVector> > > BfmeIntegerVectorMap;

template<> BfmeIntegerMapVector &BfmeIntegerVectorMap::operator[](const int &key)
{
 BfmeIntegerVectorMap::iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  BfmeIntegerMapVector value;
  it = insert(it, BfmeIntegerVectorMap::value_type(key, value));
 }
 return (*it).second;
}

template class _STL::map<int, BfmeIntegerMapVector, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmeIntegerMapVector> > >;

// Native 0x0007A26E orders keys unsigned and uses the same twelve-byte
// vector header and four-byte trivial element copy. Unsigned storage names
// those observed bits; the application's element identity remains unknown.
// The formerly missing 0x00079ED4 forwarder is now independently rowed under
// its opaque-record view. Reuse that established iterator/pair ABI without
// adding a second pin or asserting its inferred signed key as a target fact.
typedef _STL::map<unsigned int, BfmeIntegerMapVector, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, BfmeIntegerMapVector> > > BfmeUnsignedVectorMap;
struct Rva00079ED4Record { char bytes[1]; };
typedef _STL::map<int, Rva00079ED4Record, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00079ED4Record> > > Rva0007A26EInsertMap;
namespace _STL {
template <> Rva0007A26EInsertMap::iterator Rva0007A26EInsertMap::insert(Rva0007A26EInsertMap::iterator, const Rva0007A26EInsertMap::value_type &);
}

template<> BfmeIntegerMapVector &BfmeUnsignedVectorMap::operator[](const unsigned int &key)
{
 BfmeUnsignedVectorMap::iterator it = lower_bound(key);
 if (it == end() || key_comp()(key, (*it).first)) {
  BfmeIntegerMapVector value;
  it = BfmeUnsignedVectorMap::iterator(reinterpret_cast<BfmeUnsignedVectorMap::iterator::_Link_type>(
    reinterpret_cast<Rva0007A26EInsertMap *>(this)->insert(
     Rva0007A26EInsertMap::iterator(reinterpret_cast<Rva0007A26EInsertMap::iterator::_Link_type>(it._M_node)),
     reinterpret_cast<const Rva0007A26EInsertMap::value_type &>(BfmeUnsignedVectorMap::value_type(key, value)))._M_node));
 }
 return (*it).second;
}

template class _STL::map<unsigned int, BfmeIntegerMapVector, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, BfmeIntegerMapVector> > >;
