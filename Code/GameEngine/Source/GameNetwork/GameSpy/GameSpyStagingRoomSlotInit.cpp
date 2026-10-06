// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ?rva004FDA17@Rva004FDA17@@QAEXXZ @ 0x004FDA17 (38 bytes): slot-pointer init
// loop over eight 0x1E0-byte slots at +0xDC via rowed GameInfo::setSlotPointer
// 0x003FF332. Evidence: +0xDC/8x0x1E0 shape matches GameSpyStagingRoom layout
// (Rva00382FA7 base 0xDC plus 8x0x1E0 Rva00382398 array landing on +0xFDC per
// GameSpyStagingRoomDtor/Copy TUs); loop shape matches LANGameInfo ctor's
// setSlotPointer(i/&m_LANSlot[i]) in LANGameInfoCtor.cpp; callers are four
// unclaimed GameSpy bodies so class is unproven and the honest Rva name is used.
typedef int Int;

class GameSlot;

class GameInfo
{
public:
	void setSlotPointer(Int index, GameSlot *slot);
private:
	char m_pad[0xDC];
};

struct Rva004FDA17Slot
{
	unsigned char m_bytes[0x1E0];
};

class Rva004FDA17 : public GameInfo
{
public:
	void rva004FDA17();
private:
	Rva004FDA17Slot m_slots[8];
};

void Rva004FDA17::rva004FDA17()
{
	for (Int i = 0; i < 8; ++i)
		setSlotPointer(i, (GameSlot *)&m_slots[i]);
}
