// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc
// stlport
// ?setMapCRC@GameInfo@@QAEXI@Z @0x00400E9F (187B):
// GameInfo::setMapCRC. BFME1 GameInfo.cpp donor verbatim (DEBUG_LOG compiled
// out) with BFME2 deltas proven by retail: SLOT_PLAYER 6 check inlined via
// isHuman plus direct m_hasMap store at +0x09 (no setMapAvailability call),
// MapMetaData CRC at +0x2C within value (node+0x40) for the m_mapCRC compare,
// m_map at +0x40 and m_mapCRC at +0x44 via GameInfoGetMap precedent, m_inGame
// at +0x10, getLocalSlotNum at vtable +0x34 slot 13. TheMapCache global at
// 0x00DFF12C via MapCacheFindMap precedent; AsciiString copy/toLower/release
// via pinned 0x365F0 and rowed 0x36A70/0x36410; getSlot rowed 0x3FF29F.
// Callers at 0x401EC4 0x444F9C etc. No new pins.
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

#include "unicode_string.h"
#include "../../Include/GameClient/MapMetaData.h"

#include "../../Include/GameClient/MapCache.h"

extern MapCache *TheMapCache;

#include "../../Include/GameNetwork/GameInfo.h"

void GameInfo::setMapCRC(UnsignedInt mapCRC)
{
	m_mapCRC = mapCRC;
	if (!TheMapCache)
		return;
	if (m_inGame && getLocalSlotNum() >= 0) {
		AsciiString lowerMap = m_mapName;
		((StringBase<char> &)(lowerMap)).toLower();
		_STL::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it == TheMapCache->end()) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->getState() == 6)
				slot->m_hasMap = false;
		} else if (m_mapCRC != it->second.m_CRC) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->getState() == 6)
				slot->m_hasMap = false;
		} else {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->getState() == 6)
				slot->m_hasMap = true;
		}
	}
}

// Native folded setter at33F898 writes GameInfo map-mask +4C.
// Complete deserializer448423 passes its parsed mask here; donor semantic
// purpose is setMapContentsMask but its original target spelling is unproven.
void GameInfo::rva0033F898(Int mask) { m_mapMask=mask; }
