// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// The insert path of PlayerInfoMap (map<AsciiString, PlayerInfo,
// AsciiComparator>), the map whose _M_find is rowed in
// Open2Rec4F1120MapFind.cpp. PlayerInfoMap::operator[] (0x00385F29, called by
// GameSpyInfo::updatePlayerInfo 0x00386EF8) calls the hinted insert 0x00385D03
// with a pair built from the PlayerInfo default constructor (0x003822C4) and
// destroys that value through ??1PlayerInfo@@QAE@XZ (0x001EF50E), naming the
// mapped type. Target evidence: the
// node constructor at 0x00383D4F allocates 0x48 bytes (a 0x10-byte tree header
// plus the 0x38-byte pair) and places the pair through 0x0038353A, which calls
// the pair copy at 0x00382BF0: an AsciiString key copy, then the out-of-line
// PlayerInfo copy constructor (0x001EF485) on the value at +4. The inserts
// compare keys through the rowed AsciiComparator::operator() (0x0038233A). The
// flags and the retail tree-insert layout are LanguageFilterMapInsert.cpp's,
// which reproduce the same STLport insert bodies for its UnicodeString map.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

#include "ascii_string.h"

#include "../../Include/Common/AsciiComparator.h"

#include "../../Include/GameNetwork/PlayerInfo.h"

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

template PlayerInfoMap::iterator PlayerInfoMap::insert(PlayerInfoMap::iterator, const PlayerInfoMap::value_type &);
