// ?_M_erase@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?_M_erase@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@Z, retail 0x0032B4ED 53B:
// map<pair<AsciiString AsciiString> int>::_M_erase recursing right, destroying the value at
// node+0x10 through 0x002046BB then freeing via 0x00030830, walking left. Called by the
// pair-keyed map clear 0x0032BEBF (TeamsInfoRec +0x00, SidesListTeamsInfoRecClear.cpp).
//
// Evidence: LINK BONUS pin name; callers clear 0x0032BECD and self 0x0032B4FF; callees value
// dtor 0x002046BB (pin ??1Rva002046BBValue) and free 0x00030830; layout as
// SidesListTeamsInfoRecClear.cpp (TeamKey pair at +0x00, int mapped).
#include <map>
#include "ascii_string.h"
typedef _STL::pair<AsciiString, AsciiString> TeamKey;
typedef _STL::pair<const TeamKey, int> TeamKeyIntValue;
typedef _STL::_Rb_tree<TeamKey, TeamKeyIntValue, _STL::_Select1st<TeamKeyIntValue>, _STL::less<TeamKey>, _STL::allocator<TeamKeyIntValue> > TeamKeyIntTree;
template void TeamKeyIntTree::_M_erase(TeamKeyIntTree::_Link_type);
