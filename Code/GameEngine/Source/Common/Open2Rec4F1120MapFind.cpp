// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport46
//
// Retail 0x001EF5BD 164B:
// ??$_M_find@VAsciiString@@@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@3@UAsciiComparator@@V?$allocator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@1@ABVAsciiString@@@Z
// _Rb_tree _M_find worker for map<AsciiString PlayerInfo AsciiComparator>.
// Key at node+0x10 left at +8 right at +0xC header pointer at this+0
// comparator at this+8. By-value comparator needs EH (two StringBase copies
// per call destroyed by the callee at 0x0038233A). Caller 0x001EF90E copies
// PlayerInfo from node+0x14 proving the mapped type; GameSpyInfo::
// playerLeftGroupRoom (0x00384678) calls it on m_playerInfoMap.
//
#include <map>

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


#include "../../Include/Common/AsciiComparator.h"

#include "../../Include/GameNetwork/PlayerInfo.h"

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

// ?RecMapFind@@YA?AU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@U?$_Const_traits@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@2@@_STL@@ABV?$map@VAsciiString@@VPlayerInfo@@UAsciiComparator@@V?$allocator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@_STL@@@2@ABVAsciiString@@@Z present-unmatched
PlayerInfoMap::const_iterator RecMapFind(const PlayerInfoMap &playerInfoMap, const AsciiString &key)
{
	return playerInfoMap.find(key);
}
