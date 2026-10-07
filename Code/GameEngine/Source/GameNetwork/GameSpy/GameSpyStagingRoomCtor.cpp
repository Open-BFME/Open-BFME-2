// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// GameSpyStagingRoom::GameSpyStagingRoom, retail 0x004FDE4D (178 bytes): the
// default constructor addStagingRoom 0x003857EB runs after operator new(0x1020)
// (pinned there). It runs the rowed GameInfo constructor 0x00400A07, installs
// the vtable 0x00C19440 (slot 2's name getter returns "GameSpyStagingRoom"),
// builds the 8 x 0x1E0 slots at +0xDC through the EH vector constructor with
// the rowed Rva00382398 constructor 0x004FDD8B and destructor 0x00382398, and
// constructs the AsciiStrings at +0xFDC/+0xFE8/+0xFFC/+0x1000 (the destructor
// 0x00382C4A tears down the same four).
//
// Body: Zero Hour's (GameSpy/StagingRoomGameInfo.cpp in the GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference) and BFME 1's port
// (reference/open-bfme-1/game/.../GameSpyStagingRoom_ctor.cpp). Retail calls
// cleanUpSlotPointers (0x004FDA17) out of line, has no setLocalIP(0) store,
// sets m_localName through StringBase<char>::set(const char *) and clears
// +0xFFC; of BFME 1's trailing stores it keeps +0x1008 (word), +0x1018, +0xFF4
// (byte), +0xFF8 and +0x101C in that order and has no CRC/version stores.
// m_id, m_transport and m_localName follow Zero Hour's member order (amIHost
// reads m_localName at +0xFE8, addStagingRoom keys rooms by m_id at +0xFE0);
// the other names are BFME 1's, carried by offset and store order, not
// established from BFME 2 uses.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();

private:
	unsigned char m_pad04[0xDC - 0x04];
};

// Zero Hour's GameSpyGameSlot; the ledger names its constructor and
// destructor after the destructor's address.
class Rva00382398
{
public:
	Rva00382398();
	virtual ~Rva00382398();

private:
	unsigned char m_pad04[0x1E0 - 0x04];
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	virtual ~GameSpyStagingRoom();
	void cleanUpSlotPointers(void);

private:
	Rva00382398 m_GameSpySlot[8];     // +0xDC
	AsciiString m_bfmeFDC;            // +0xFDC
	Int m_id;                         // +0xFE0
	void *m_transport;                // +0xFE4
	AsciiString m_localName;          // +0xFE8
	Bool m_bfmeFEC;                   // +0xFEC
	Int m_bfmeFF0;                    // +0xFF0
	Bool m_isQM;                      // +0xFF4
	Int m_qmLadderType;               // +0xFF8
	AsciiString m_ladderIP;           // +0xFFC
	AsciiString m_pingStr;            // +0x1000
	Int m_pingInt;                    // +0x1004
	UnsignedShort m_ladderPort;       // +0x1008
	Int m_bfme100C[3];                // +0x100C
	Int m_reportedMaxPlayers;         // +0x1018
	Int m_reportedNumObservers;       // +0x101C
};

GameSpyStagingRoom::GameSpyStagingRoom()
{
	cleanUpSlotPointers();

	m_transport = NULL;

	m_localName = "localhost";

	m_ladderIP.clear();
	m_ladderPort = 0;
	m_reportedMaxPlayers = 0;
	m_isQM = false;
	m_qmLadderType = 0;
	m_reportedNumObservers = 0;
}
