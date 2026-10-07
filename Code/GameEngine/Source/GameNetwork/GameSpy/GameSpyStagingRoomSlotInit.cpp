// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// GameSpyStagingRoom::cleanUpSlotPointers @ 0x004FDA17 (38 bytes), from Zero
// Hour's GameNetwork/GameSpy/StagingRoomGameInfo.cpp (GeneralsMD tree under
// reference/open-bfme-1/inputs/reference): setSlotPointer(i, &slot[i]) over
// the eight 0x1E0-byte slots at +0xDC via the rowed GameInfo::setSlotPointer
// 0x003FF332. The default constructor 0x004FDE4D (GameSpyStagingRoomCtor.cpp)
// calls it first, as Zero Hour's constructor calls cleanUpSlotPointers.
//
// Layout evidence from that constructor: the rowed ??0GameInfo 0x00400A07,
// vtable 0x00C19440, eight slots built through the EH vector constructor with
// the rowed Rva00382398 ctor/dtor, and the four strings the rowed
// ~GameSpyStagingRoom 0x00382C4A releases (+0xFDC/+0xFE8/+0xFFC/+0x1000).
// Carried from Zero Hour: m_transport (+0xFE4), m_localName (+0xFE8),
// m_ladderIP (+0xFFC) and the 16-bit m_ladderPort (+0x1008). The other
// trailing fields are BFME 2's, their meanings not established. The slot
// class keeps its address name (unproven as GameSpyGameSlot).
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
enum
{
	MAX_SLOTS = 8
};

class GameSlot;
class NAT;

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	void setSlotPointer(Int index, GameSlot *slot);
private:
	char m_pad04[0xDC - 4];
};

class Rva00382398
{
public:
	Rva00382398();
	virtual ~Rva00382398();
private:
	char m_pad[0x1E0 - 4];
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	virtual ~GameSpyStagingRoom();
	void cleanUpSlotPointers(void);
private:
	Rva00382398 m_GameSpySlot[MAX_SLOTS]; // +0xDC
	AsciiString m_gameName;     // +0xFDC
	Int m_id;                   // +0xFE0
	NAT *m_transport;           // +0xFE4
	AsciiString m_localName;    // +0xFE8
	Bool m_bfmeFEC;             // +0xFEC
	Bool m_bfmeFED;             // +0xFED
	UnsignedInt m_bfmeFF0;      // +0xFF0
	Bool m_bfmeFF4;             // +0xFF4
	Int m_bfmeFF8;              // +0xFF8
	AsciiString m_ladderIP;     // +0xFFC
	AsciiString m_bfme1000;     // +0x1000
	Int m_bfme1004;             // +0x1004
	UnsignedShort m_ladderPort; // +0x1008
	Int m_bfme100C;             // +0x100C
	Int m_bfme1010;             // +0x1010
	Int m_bfme1014;             // +0x1014
	Int m_bfme1018;             // +0x1018
	Int m_bfme101C;             // +0x101C
};

void GameSpyStagingRoom::cleanUpSlotPointers(void)
{
	for (Int i = 0; i < MAX_SLOTS; ++i)
		setSlotPointer(i, (GameSlot *)&m_GameSpySlot[i]);
}
