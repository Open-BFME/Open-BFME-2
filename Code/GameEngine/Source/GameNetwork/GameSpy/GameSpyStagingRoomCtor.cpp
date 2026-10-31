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
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class Image;
class GameSlot;
class AsciiString;

struct BfmeNetAddress
{
	unsigned int m_ip;
	unsigned short m_port;
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void v1() = 0; virtual void v2() = 0; virtual void v3() = 0;
	virtual void v4() = 0; virtual void v5() = 0;
	virtual const Image *rva00401015(int column);
	virtual void v7() = 0; virtual void v8() = 0; virtual void v9() = 0;
	virtual void reset(void);			// slot 10 (+0x28)
	virtual void startGame(int gameID) = 0;		// slot 11
	virtual bool amIHost(void) const = 0;		// slot 12
	virtual int getLocalSlotNum(void) const = 0;	// slot 13 (+0x34)
	virtual void resetAccepted(void);
	void init();
	const GameSlot *getConstSlot(int slotNum) const;
	void setSlotPointer(int index, GameSlot *slot);
	GameSlot *getSlot(int slotNum);
	void setMap(AsciiString mapName);
	AsciiString getMap(void) const;
	void markPlayerAsPreorder(int index);
	void setGameInProgress(bool inProgress) { m_inProgress = inProgress; }
	unsigned int getSeed(void) const { return m_seed; }
private:
	char m_pad04[0x10 - 4];
protected:
	bool m_inGame; // +0x10
private:
	bool m_inProgress;				// +0x11
	char m_pad12[0x38 - 0x12];
protected:
	BfmeNetAddress m_localAddress;			// +0x38
private:
	char m_pad40[0x50 - 0x40];
	unsigned int m_seed;				// +0x50
	char m_pad54[0x58 - 0x54];
protected:
	int m_bfme58;					// +0x58
private:
	char m_pad5C[0x60 - 0x5C];
public:
	int m_bfme60;					// +0x60, zero when heroes are allowed
private:
	char m_pad64[0x6C - 0x64];
public:
	// Inline reads: retail 0x4FE5CA loads both into registers before pushing
	// them, where a plain member access is pushed from memory.
	int getCmdPointFactor(void) const { return m_bfme6C; }
	int getIniResource(void) const { return m_bfme70; }
	int m_bfme6C;					// +0x6C, the command point factor
	int m_bfme70;					// +0x70, the initial resources
private:
	char m_pad74[0xDC - 0x74];
};

class GameSlot
{
public:
	GameSlot();
	virtual ~GameSlot();
	bool isPlayer(AsciiString userName) const;
	bool isHuman(void) const;
	bool isAI(void) const;
	bool disconnected(void) const;
	int getTeamNumber(void) const { return m_teamNumber; }

	unsigned char m_pre1C[0x1C - 4];
	int m_teamNumber;				// +0x1C
	unsigned char m_pre30[0x30 - 0x20];
	UnicodeString m_name;				// +0x30
	AsciiString m_bfme34;				// +0x34, the player's name-key string
	unsigned char m_pre4C[0x4C - 0x38];
	int m_bfme4C;					// +0x4C, the living-world battle's index
	unsigned char m_pre1A4[0x1A4 - 0x50];
	bool m_bfme1A4;					// +0x1A4
	unsigned char m_pre1AC[0x1AC - 0x1A5];
};

// Zero Hour's GameSpyGameSlot; the ledger names its constructor and
// destructor after the destructor's address.
class Rva00382398 : public GameSlot
{
public:
	virtual ~Rva00382398();
	int m_1AC;
	AsciiString m_1B0;
	AsciiString m_1B4;
	AsciiString m_1B8;
	int m_1BC;
	int m_1C0;
	int m_1C4;
	int m_1C8;
	int m_1CC;
	int m_1D0;
	int m_1D4;
	AsciiString m_1D8;
	AsciiString m_1DC;
	Rva00382398();
};

struct NAT;
class LivingWorldBattle;
class GameSpyGameSlot;

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	virtual ~GameSpyStagingRoom();
	virtual void reset(void);
	virtual void startGame(int gameID);
	virtual bool amIHost(void) const;
	virtual int getLocalSlotNum(void) const;
	virtual void resetAccepted(void);
	virtual const Image *rva00401015(int column);
	GameSpyGameSlot *getGameSpySlot(int index);
	bool getBfmeFEC(void) const { return m_bfmeFEC; }
	void cleanUpSlotPointers(void);
	void launchGame(void);
	void rva004FDEFF(LivingWorldBattle *battle);
	void launchWOTRMPGame(void);
	AsciiString generateGameSpyGameResultsPacket(bool sawCRCMismatch, bool playerQuit);
	bool isQMGame(void) { return m_isQM; }
private:
	Rva00382398 m_GameSpySlot[8]; // +0xDC
	AsciiString m_gameName;     // +0xFDC
	int m_id;                   // +0xFE0
	NAT *m_transport;           // +0xFE4
	AsciiString m_localName;    // +0xFE8
	bool m_bfmeFEC;             // +0xFEC
	bool m_bfmeFED;             // +0xFED
	unsigned int m_bfmeFF0;      // +0xFF0
	bool m_isQM;                // +0xFF4
	int m_qmLadderType;         // +0xFF8
	AsciiString m_ladderIP;     // +0xFFC
	AsciiString m_pingStr;     // +0x1000
	int m_pingInt;             // +0x1004
	unsigned short m_ladderPort; // +0x1008
	int m_bfme100C;             // +0x100C
	int m_bfme1010;             // +0x1010
	int m_bfme1014;             // +0x1014
	int m_reportedMaxPlayers;   // +0x1018
	int m_reportedNumObservers; // +0x101C
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
