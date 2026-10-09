// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
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

template <typename T>
struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

class PlayerInfo
{
public:
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1c;
	int m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
};

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

// ?RecMapFind@@YA?AU?$_Rb_tree_iterator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@U?$_Const_traits@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@2@@_STL@@ABV?$map@VAsciiString@@VPlayerInfo@@UAsciiComparator@@V?$allocator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@_STL@@@2@ABVAsciiString@@@Z present-unmatched
PlayerInfoMap::const_iterator RecMapFind(const PlayerInfoMap &m, const AsciiString &key)
{
	return m.find(key);
}
