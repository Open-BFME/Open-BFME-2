// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??0?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@@_STL@@QAE@ABU?$less@W4NameKeyType@@@1@ABV?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@1@@Z
// retail 0x00425FEC, 42 bytes. Empty _Rb_tree ctor for the
// PristineBoneInfoMap (map<NameKeyType, PristineBoneInfo>): calls the rowed
// _Rb_tree_base ctor at 0x00382A4A, zeroes the node count, marks the header
// red and links it to itself. Evidence: unlock lane (unblocks 0x004260FD);
// caller 0x0042610C passes (comp, allocator); callee rowed 0x00382A4A;
// same 42B shape as the rowed NameKeyType->ModuleTemplate 0x00603AE0 and
// long->LadderPref 0x0046AB53 tree ctors.
//
// ??0?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@QAE@XZ
// retail 0x004260FD, 25 bytes. Default map ctor for PristineBoneInfoMap:
// forwards empty comp and allocator temporaries to the rowed _Rb_tree ctor
// 0x00425FEC. Evidence: chain lane (calls 0x00425FEC just landed); same
// explicit anchor as _bfmePristineBoneAnchor's map() call in
// W3DModelDrawO1Inlines.cpp; unblocks 0x004261B8, 0x000C6A4D, 0x00385FE1.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
// Native tree teardownBB65C frees through C++ allocator30830.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseBoneNode(void *storage)
{
	_STL::free(storage);
}
#include <map>
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; struct PristineBoneInfo;
namespace _STL { template <> _Rb_tree_node<pair<NameKeyType const ,PristineBoneInfo> > * _Rb_tree<NameKeyType,pair<NameKeyType const ,PristineBoneInfo>,_Select1st<pair<NameKeyType const ,PristineBoneInfo> >,less<NameKeyType>,allocator<pair<NameKeyType const ,PristineBoneInfo> > >::_M_create_node(pair<NameKeyType const ,PristineBoneInfo> const &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; struct PristineBoneInfo;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<NameKeyType const ,PristineBoneInfo>,_Nonconst_traits<pair<NameKeyType const ,PristineBoneInfo> > >,bool> _Rb_tree<NameKeyType,pair<NameKeyType const ,PristineBoneInfo>,_Select1st<pair<NameKeyType const ,PristineBoneInfo> >,less<NameKeyType>,allocator<pair<NameKeyType const ,PristineBoneInfo> > >::insert_unique(pair<NameKeyType const ,PristineBoneInfo> const &); }
// Keep the genuine STLport _M_erase emission: its complete 45-byte body,
// recursive call and allocator binding fold onto native 0x000B646B.
// The rowed neutral owner remains; this is an independently verified template fold.
// Suppress this TU's non-retail copy of ??A?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$p:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; struct PristineBoneInfo;
namespace _STL { template <> PristineBoneInfo &map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::operator[](const NameKeyType &); }

namespace _STL {
template<> inline void allocator<_Rb_tree_node<pair<const NameKeyType, PristineBoneInfo> > >::deallocate(_Rb_tree_node<pair<const NameKeyType, PristineBoneInfo> > *__p, size_type) const
{
	if (__p != 0) releaseBoneNode((void *)__p);
}
}
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

struct PristineBoneInfo
{
	unsigned char m_data[52];
};

typedef _STL::map<NameKeyType, PristineBoneInfo> PristineBoneMap;
typedef _STL::_Rb_tree<NameKeyType, PristineBoneMap::value_type, _STL::_Select1st<PristineBoneMap::value_type>, _STL::less<NameKeyType>, PristineBoneMap::allocator_type> PristineBoneTree;
// Use the rowed placement helper and leave unused searches uninstantiated.
namespace _STL {
template <> void _Construct<PristineBoneMap::value_type, PristineBoneMap::value_type>(PristineBoneMap::value_type *, const PristineBoneMap::value_type &);
template <> PristineBoneMap::iterator PristineBoneMap::find(const NameKeyType &);
template <> PristineBoneMap::const_iterator PristineBoneMap::find(const NameKeyType &) const;
template <> PristineBoneMap::size_type PristineBoneMap::count(const NameKeyType &) const;
}
// Retail's _M_copy is the no-EH copy (rowed 0x000BC2DE in
// stlport_map_namekey_pristinebone_copy.cpp) that the copy constructor and
// assignment here call; suppress this /EHsc unit's own instantiation and keep
// the rowed _M_clone_node (0x000BBC89) it used to pull in.
extern template PristineBoneTree::_Link_type PristineBoneTree::_M_copy(PristineBoneTree::_Link_type, PristineBoneTree::_Link_type);
template PristineBoneTree::_Link_type PristineBoneTree::_M_clone_node(PristineBoneTree::_Link_type);
// Preserve the existing instantiated map operations and emit native destruction.
template class _STL::map<NameKeyType, PristineBoneInfo>;
template PristineBoneTree::~_Rb_tree();
// Instantiate the normal map range teardown so MSVC emits its implicit destructor.
template void _STL::_Destroy<PristineBoneMap *>(PristineBoneMap *, PristineBoneMap *);
