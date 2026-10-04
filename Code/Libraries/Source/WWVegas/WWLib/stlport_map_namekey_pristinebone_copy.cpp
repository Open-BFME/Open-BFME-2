// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport

// ?_M_copy@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@2@PAU32@0@Z
// retail 0x000BC2DE, 115 bytes. _Rb_tree<NameKeyType,pair<const NameKeyType,
// PristineBoneInfo>>::_M_copy beside stlport_map_namekey_pristinebone.cpp.
// Evidence: pinned name; rowed _M_clone_node 0x000BBC89 plus self-recursion;
// callers 0x000BC388 and 0x000BD111 in the same tree; same 115B shape as the
// rowed NameKeyType->ModuleTemplate 0x004136B4 and int-int 0x002CF6CF copies.
#include <map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

struct PristineBoneInfo
{
	unsigned char m_data[52];
};

typedef _STL::_Rb_tree<NameKeyType, _STL::pair<const NameKeyType, PristineBoneInfo>, _STL::_Select1st<_STL::pair<const NameKeyType, PristineBoneInfo> >, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, PristineBoneInfo> > > PristineBoneTree;
template PristineBoneTree::_Link_type PristineBoneTree::_M_copy(PristineBoneTree::_Link_type, PristineBoneTree::_Link_type);
