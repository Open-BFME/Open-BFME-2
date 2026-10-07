// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// GameSpyStagingRoom::cleanUpSlotPointers, retail 0x004FDA17 (38 bytes):
// slot-pointer init loop over eight 0x1E0-byte slots at +0xDC via rowed
// GameInfo::setSlotPointer 0x003FF332. Identity: the GameSpyStagingRoom
// default constructor 0x004FDE4D (GameSpyStagingRoomCtor.cpp) calls it on
// this first, as Zero Hour's constructor calls cleanUpSlotPointers
// (GameSpy/StagingRoomGameInfo.cpp); the +0xDC/8x0x1E0 shape matches the
// GameSpyStagingRoom layout of the Dtor/Copy TUs and the loop matches the
// LANGameInfo ctor's setSlotPointer(i/&m_LANSlot[i]) in LANGameInfoCtor.cpp.
typedef int Int;

class GameSlot;

class GameInfo
{
public:
	void setSlotPointer(Int index, GameSlot *slot);
private:
	char m_pad[0xDC];
};

struct GameSpyGameSlotBytes
{
	unsigned char m_bytes[0x1E0];
};

class GameSpyStagingRoom : public GameInfo
{
public:
	void cleanUpSlotPointers(void);
private:
	GameSpyGameSlotBytes m_slots[8];
};

void GameSpyStagingRoom::cleanUpSlotPointers(void)
{
	for (Int i = 0; i < 8; ++i)
		setSlotPointer(i, (GameSlot *)&m_slots[i]);
}
