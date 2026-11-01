// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /MD /EHsc
// ?getMap@GameInfo@@QBE?AVAsciiString@@XZ @0x23E943 (27B):
// GameInfo::getMap, out-of-line AsciiString copy of m_map at +0x40 via the
// rowed StringBase copy-ctor at 0x365F0 into the hidden return pointer.
// Called once from GameLogic::bfmePopulateGameReport at 0x2473E9 for the
// Session-Map line. Leaf, no new pins.
#include "ascii_string.h"

#include "../../Include/GameNetwork/GameInfo.h"

// ?getMap@GameInfo@@QBE?AVAsciiString@@XZ
inline AsciiString GameInfo::getMap() const
{
	return m_mapName;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeGameInfoInlineAnchor@@YAXPAVGameInfo@@@Z absent-from-retail
void _bfmeGameInfoInlineAnchor(GameInfo *gameInfo)
{
    gameInfo->getMap();
}
#pragma inline_depth()
