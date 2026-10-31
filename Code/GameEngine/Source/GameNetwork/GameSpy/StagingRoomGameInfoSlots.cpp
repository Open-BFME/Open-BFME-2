// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// GameSpyStagingRoom::amIHost, retail 0x004FDBAA (75 bytes), and
// GameSpyStagingRoom::getLocalSlotNum, retail 0x004FDBF5 (126 bytes), and
// GameSpyStagingRoom::resetAccepted, retail 0x004FDA62 (16 bytes): slots 12,
// 13 and 14 of vtable 0x00C19440, whose unique slot-2 name getter returns
// "GameSpyStagingRoom"; in the GameInfo vtable the same slots hold the
// rowed GameInfo amIHost/getLocalSlotNum/resetAccepted bodies, which Zero Hour's
// GameSpyStagingRoom overrides. Ported verbatim from Zero Hour's
// GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference).
// Callees: the rowed GameInfo::getConstSlot and GameSlot::isPlayer (an
// AsciiString by value); TheGameSpyInfo's getLocalName is its vslot 29.
// The base GameInfo::resetAccepted (rowed 0x003FF9B4 under a non-virtual
// name) is slot 14 of the GameInfo vtable; it is pinned under its virtual
// name for the qualified base call.
// Layout: m_inGame +0x10, m_localName +0xFE8.
// Slot 6, retail 0x004FDC78 (105 bytes): the game-list column image. Column
// 2 is "AptLock" (literal 0x00C3E4F4, shared with the LANGameInfo override
// 0x00447BE0) while the byte at +0xFEC is set, read through an inline
// accessor (load-then-test); other columns go to the base GameInfo body
// 0x00401015. The names follow that base's address; the +0xFEC field's
// meaning is not established.
typedef bool Bool;
typedef int Int;
enum
{
	MAX_SLOTS = 8
};

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class VSlots<0>
{
};

template <class B, int N> class VPad : public VPad<B, N - 1>
{
public:
	virtual void pad(B *, char (*)[N]) = 0;
};

template <class B> class VPad<B, 0> : public B
{
};


class GameSpyStagingRoom;

class PlayerInfo
{
public:
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_clan;
	int m_wins;
	int m_losses;
	int m_profileID;
	int m_flags;
	int m_rankPoints;
	int m_side;
	int m_unk24;
	int m_dc;
	int m_desync;
	int m_preorder;
};

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class GameSpyInfoSlot22 : public VSlots<21>
{
public:
	virtual PlayerInfoMap *getPlayerInfoMap(void) = 0;		// slot 21 (+0x54)
	virtual PlayerInfo *rva00382CCE(const char *key) = 0;		// slot 22 (+0x58)
};

class GameSpyInfoSlot29 : public VPad<GameSpyInfoSlot22, 6>
{
public:
	virtual AsciiString getLocalName(void) = 0; // slot 29 (+0x74)
};

class GameSpyInfoSlot31 : public VPad<GameSpyInfoSlot29, 1>
{
public:
	virtual int getLocalProfileID(void) = 0;			// slot 31 (+0x7C)
};

class GameSpyInfoSlot47 : public VPad<GameSpyInfoSlot31, 15>
{
public:
	virtual void leaveStagingRoom(void) = 0;			// slot 47 (+0xBC)
};

class GameSpyInfoSlot53 : public VPad<GameSpyInfoSlot47, 5>
{
public:
	virtual GameSpyStagingRoom *getCurrentStagingRoom(void) = 0;	// slot 53 (+0xD4)
};

class GameSpyInfoSlot72 : public VPad<GameSpyInfoSlot53, 18>
{
public:
	virtual int _M_slot_120(const AsciiString &name); // slot 72 (+0x120)
};

class GameSpyInfoInterface : public VPad<GameSpyInfoSlot72, 17>
{
public:
	virtual bool didPlayerPreorder(int profileID) const = 0;	// slot 90 (+0x168)
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

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

class GameSpyGameSlot : public GameSlot
{
public:
	__declspec(dllimport) __forceinline int getProfileID(void) const { return m_profileID; }
	void setProfileID(int id) { m_profileID = id; }
	void setSlotRankPoints(int val) { m_rankPoints = val; }
	void setFavoriteSide(int val) { m_favoriteSide = val; }
private:
	int m_profileID;				// +0x1AC
	AsciiString m_gameSpyLogin;			// +0x1B0
	AsciiString m_gameSpyLocale;			// +0x1B4
	AsciiString m_pingStr;				// +0x1B8
	int m_pingInt;					// +0x1BC
	int m_wins;					// +0x1C0
	int m_losses;					// +0x1C4
	int m_rankPoints;				// +0x1C8
	int m_favoriteSide;				// +0x1CC
};

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

struct NAT;
class LivingWorldBattle;
class GameSpyGameSlot;

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

// GameSpyStagingRoom::getGameSpySlot, retail 0x004FDA3D (5 bytes): Zero Hour's
// body (its DEBUG_ASSERTCRASH compiles out), a tail jump to the rowed
// GameInfo::getSlot 0x003FF29F. Callers reach it as a direct call.
GameSpyGameSlot * GameSpyStagingRoom::getGameSpySlot( Int index )
{
	GameSlot *slot = getSlot(index);
	return (GameSpyGameSlot *)slot;
}

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

void GameSpyStagingRoom::resetAccepted( void )
{
	GameInfo::resetAccepted();

	if (amIHost())
	{
		/*
		peerStateChanged(TheGameSpyChat->getPeer());
		m_hasBeenQueried = false;
		DEBUG_LOG(("resetAccepted() called peerStateChange()\n"));
		*/
	}
}

const Image *GameSpyStagingRoom::rva00401015( Int column )
{
	switch (column)
	{
		case 2:
			if (getBfmeFEC())
				return TheMappedImageCollection->findImageByName(AsciiString("AptLock"));
			return NULL;
	}
	return GameInfo::rva00401015(column);
}
