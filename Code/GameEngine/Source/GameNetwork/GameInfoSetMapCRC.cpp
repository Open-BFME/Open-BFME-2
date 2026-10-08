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

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

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

class MapMetaData
{
public:
	char m_pad[0x2C];
	UnsignedInt m_CRC;
};

class MapCache : public _STL::map<AsciiString, MapMetaData>
{
};

extern MapCache *TheMapCache;

class GameSlot
{
public:
	Bool isHuman() const { return m_state == 6; }
	void *m_vtable;
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
};

class GameInfo
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual Int getLocalSlotNum() const = 0;
	GameSlot *getSlot(Int slotNum);
	void setMapCRC(UnsignedInt mapCRC);
	void rva0033F898(Int mask);
private:
	char m_pad0C[0x0C];
	Bool m_inGame;
	char m_pad11[0x2F];
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
	Int m_mapMask;
};

void GameInfo::setMapCRC(UnsignedInt mapCRC)
{
	m_mapCRC = mapCRC;
	if (!TheMapCache)
		return;
	if (m_inGame && getLocalSlotNum() >= 0) {
		AsciiString lowerMap = m_mapName;
		lowerMap.toLower();
		_STL::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it == TheMapCache->end()) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = false;
		} else if (m_mapCRC != it->second.m_CRC) {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = false;
		} else {
			GameSlot *slot = getSlot(getLocalSlotNum());
			if (slot->isHuman())
				slot->m_hasMap = true;
		}
	}
}

// Native folded setter at33F898 writes GameInfo map-mask +4C.
// Complete deserializer448423 passes its parsed mask here; donor semantic
// purpose is setMapContentsMask but its original target spelling is unproven.
void GameInfo::rva0033F898(Int mask) { m_mapMask=mask; }
