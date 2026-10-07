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
#include <map>

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

template class _STL::map<NameKeyType, PristineBoneInfo>;
