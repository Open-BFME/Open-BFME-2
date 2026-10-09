// ??A?$map@VAsciiString@@VPlayerInfo@@UAsciiComparator@@V?$allocator@U?$pair@$$CBVAsciiString@@VPlayerInfo@@@_STL@@@_STL@@@_STL@@QAEAAVPlayerInfo@@ABVAsciiString@@@Z
// partial score=0.98 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Ob2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// PlayerInfoMap::operator[] (map<AsciiString, PlayerInfo, AsciiComparator>),
// retail 0x00385F29..0x00385FE1 (184 bytes, RET 4). GameSpyInfo::
// updatePlayerInfo (0x00386EF8) stores through m_playerInfoMap[pi.m_name].
// Retail calls the PeerDefs.cpp lower_bound (0x00382AB7), the rowed
// AsciiComparator (0x0038233A) on by-value key copies, the out-of-line
// 0x34-byte PlayerInfo default constructor (0x003822C4), the EH-framed pair
// constructor (0x003829AC), the hinted map insert (0x00385D03), then the
// pair (0x00382881) and PlayerInfo (0x001EF50E) destructors. The flags and
// tree layout are LanguageFilterMapInsert.cpp's, which reproduce the same
// STLport operator[] shape for its UnicodeString map. The comparator body
// is visible in-class (retail's own copy at 0x0038233A, which this TU's
// COMDAT reproduces exactly) so its empty temporary needs no frame slot,
// as in the PeerDefs.cpp instantiation; without /D_CRTIMP= _strcmpi keeps
// retail's import call.

#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

#include "ascii_string.h"

typedef int Int;

class PlayerInfo
{
public:
	PlayerInfo();
	PlayerInfo(const PlayerInfo &other);
	~PlayerInfo();
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_clan;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_side;
	Int m_unk24;
	Int m_dc;
	Int m_desync;
	Int m_preorder;
};

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const
	{
		return _strcmpi(s1.str(), s2.str()) < 0;
	}
};

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

template PlayerInfo &PlayerInfoMap::operator[](const AsciiString &);
