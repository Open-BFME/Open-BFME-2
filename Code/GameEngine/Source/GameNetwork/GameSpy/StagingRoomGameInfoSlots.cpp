// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// GameSpyStagingRoom::amIHost, retail 0x004FDBAA (75 bytes), and
// GameSpyStagingRoom::getLocalSlotNum, retail 0x004FDBF5 (126 bytes): slots
// 12 and 13 of vtable 0x00C19440, whose unique slot-2 name getter returns
// "GameSpyStagingRoom"; in the GameInfo vtable the same slots hold the
// rowed GameInfo amIHost/getLocalSlotNum bodies, which Zero Hour's
// GameSpyStagingRoom overrides. Ported verbatim from Zero Hour's
// GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference).
// Callees: the rowed GameInfo::getConstSlot and GameSlot::isPlayer (an
// AsciiString by value); TheGameSpyInfo's getLocalName is its vslot 29.
// Layout: m_inGame +0x10, m_localName +0xFE8.
typedef bool Bool;
typedef int Int;
enum
{
	MAX_SLOTS = 8
};

#include "ascii_string.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class GameSpyInfoInterface : public VSlots<29>
{
public:
	virtual AsciiString getLocalName(void) = 0;
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSlot
{
public:
	Bool isPlayer(AsciiString userName) const;
};

class GameInfo
{
public:
	virtual Bool amIHost(void) const;
	virtual Int getLocalSlotNum(void) const;
	const GameSlot *getConstSlot(Int slotNum) const;
protected:
	unsigned char m_pad04[0x10 - 0x04];
	Bool m_inGame; // +0x10
};

class GameSpyStagingRoom : public GameInfo
{
public:
	virtual Bool amIHost(void) const;
	virtual Int getLocalSlotNum(void) const;
private:
	unsigned char m_pad14[0xFE8 - 0x14];
	AsciiString m_localName; // +0xFE8
};

Bool GameSpyStagingRoom::amIHost( void ) const
{
	if (!m_inGame)
		return false;

	return getConstSlot(0)->isPlayer(m_localName);
}

Int GameSpyStagingRoom::getLocalSlotNum( void ) const
{
	if (!m_inGame)
		return -1;

	AsciiString localName = TheGameSpyInfo->getLocalName();

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot == NULL) {
			continue;
		}
		if (slot->isPlayer(localName))
			return i;
	}
	return -1;
}
