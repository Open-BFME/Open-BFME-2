// cl: /O1 /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/campaignmanagerascii /Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ??A?$map@JVLadderPref@@...@QAEAAVLadderPref@@ABJ@Z retail 0x005E017A, 135 bytes.
// Ported from the Open-BFME-1 donor game/Libraries/Source/WWVegas/WWLib/
// stlport_map_long_ladderpref_operator.cpp (reference/open-bfme-1 @ 6583b3c1) with
// BFME 2 include paths. At /O1 it is a unique masked placement on unclaimed .text.
// The callees are this map's rowed pair constructor 0x005DFB7F and LadderPref
// destructor 0x005BA3C0, plus the pinned _M_lower_bound 0x00382A92 and insert
// 0x005DFFB6. Kept apart from stlport_map_long_ladderpref.cpp because
// retail's subscript builds its default LadderPref inline, and that unit's
// out-of-line constructor declaration would change the other bodies.

// The retail map subscript at 0x000ACC40 belongs to LadderPreferences' recent
// ladder map.  The callers pass a signed time_t key and use the returned
// LadderPref reference to fill a newly inserted record.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

class LadderPref
{
public:
	UnicodeString name;
	AsciiString address;
	unsigned short port;
	long lastPlayDate;
};

typedef std::map<long, LadderPref> LadderPrefMap;

template LadderPref &LadderPrefMap::operator[](const long &key);
