// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
// m_ladderIP (+0xFFC) and the 16-bit m_ladderPort (+0x1008). The byte at
// +0xFF4 is Zero Hour's m_isQM (startGame below picks its quick-match branch
// on it); the other trailing fields are BFME 2's, their meanings not
// established. The slot class keeps its address name (unproven as
// GameSpyGameSlot).
//
// PopBackToLobby @ 0x004FDA72 (85 bytes): Zero Hour's PopBackToLobby (there
// in WOLGameSetupMenu.cpp; BFME 2 places it in this unit, between the rowed
// cleanUpSlotPointers and resetAccepted). Target evidence: it is the bail-out
// both failure paths of 0x004FDEFF call after their GSMessageBoxOk, as Zero
// Hour's launchGame calls PopBackToLobby after GUI:CouldNotTransferMap. As in
// Zero Hour it deletes the global in TheNAT's place (0x00E063F8, kept under
// its address name) and nulls it, then, while TheGameSpyInfo exists, resets
// its current staging room (TheGameSpyInfo vslot 53, room vslot 10, the
// GameInfo reset slot) and leaves it (vslot 47). Zero Hour's shell pop has no
// counterpart; BFME 2 instead clears the object at 0x00E063EC through the
// rowed 0x0059EE7F (a tail jump).
//
// GameSpyStagingRoom::rva004FDEFF @ 0x004FDEFF (551 bytes), named by
// address: the GameSpy twin of the rowed LANAPI::rva00249B08, called only from
// 0x002B8A67 on TheGameSpyGame. Like Zero Hour's launchGame: the map is
// maps\<name>\<name>.map for the battle holder's name, then the game is set
// in progress (+0x11) and every human slot whose profile (+0x1AC) preordered
// (TheGameSpyInfo vslot 90) is marked. BFME 2's hero transfer check
// (0x0044C3D4) and the map transfer (DoAnyMapTransfers, updateCache,
// findMap) each fail with GUI:Error and GUI:CouldNotTransferHero or
// GUI:CouldNotTransferMap after ::deleting TheNetwork, then PopBackToLobby;
// retail tail-merges the two GSMessageBoxOk calls. Otherwise every slot gets
// its battle data as in the LAN twin, TheGameSpyGame's map becomes
// TheWritableGlobalData's pending file and the logic random is seeded from
// the seed at +0x50.
//
// GameSpyStagingRoom::launchWOTRMPGame @ 0x004FE126 (569 bytes), named by
// address: the GameSpy twin of the rowed LANAPI::OnWOTRGameStart (its only caller
// is 0x005A63E3) and shaped like Zero Hour's GameSpyStagingRoom::launchGame.
// Carried from Zero Hour: game in progress and preorder marks, a new network
// whose local address is the room's (+0x38) with, while the global in TheNAT's
// place exists, its port replaced by that object's slot port for the local
// slot (GameInfo vslot 13; 0x005A684F reads the slot's node +0x90C and its
// 16-bit port, else 0) and its transport attached (0x005801F2, a folded +4
// getter, into TheNetwork vslot 19) instead of initTransport, then
// parseUserList, the buddy status 4 with the room name (the rowed 0x0022C4DF
// on TheGameSpyGame) and the global ::deleted and nulled last. BFME 2 adds the
// call 0x005A6A4C (copies each slot address to +0x38/+0x3C) before attaching,
// and, as in the LAN twin, TheGameLogic's 0x00376E92 twice, the hero transfer
// check (failing with GUI:Error/GUI:CouldNotTransferHero and PopBackToLobby),
// the living-world reset, 0x00DFEF18 vslot 10 and message 0x1F carrying +0x58
// and 2. The callee methods keep address names on the object's address class.
//
// GameSpyStagingRoom::reset @ 0x004FDC73 (5 bytes): vtable 0x00C19440 slot 10,
// a tail jump to the rowed GameInfo::reset, as Zero Hour's override (which
// only adds a debug-build NAT check).
//
// GameSpyStagingRoom::startGame @ 0x004FF09F (360 bytes): vtable 0x00C19440
// slot 11, Zero Hour's slot loop without the NAT setup. For each human slot
// it counts the human, sets the login name from the translated slot name
// (+0x30) and looks the player up by that name (TheGameSpyInfo vslot 22).
// In quick match (+0xFF4) only the local slot gets its profile ID (vslot 31),
// and BFME 2 clears two further slot strings. Otherwise the player-info map
// (vslot 21) entry found through the looked-up info gives the profile ID,
// the clan string (Zero Hour's locale setter in that place), rank points and
// favorite side. Zero Hour's numHumans < 2 branch keeps only its launchGame
// call (0x004FED35).
//
// GameSpyStagingRoom::launchGame @ 0x004FED35 (874 bytes). Identity from target
// evidence: startGame calls it where Zero Hour's startGame calls launchGame,
// and the NAT code at 0x005A63ED calls it where Zero Hour's NAT calls
// launchGame once connections are established. launchWOTRMPGame is called instead
// at 0x005A63E3 when the room's +0x5C is 1.
// The body is Zero Hour's launchGame in BFME 2's form: preorder marks, the
// network as in launchWOTRMPGame, the hero transfer check and the map transfer
// (both failing as in rva004FDEFF), the pending file, then MSG_NEW_GAME
// (0x1E) carrying GAME_INTERNET (5), 1, 0 and +0x1018, TheGameLogic's byte
// +0x9D set as in LANAPI::OnGameStart, the logic random seed, buddy status 4
// with the room name and the global in TheNAT's place deleted. BFME 2 adds a
// quick-match tail: when +0xFF4 is set, persistent-storage request type 7
// (only if +0x101C is set; no queue null check) and then type 5 (with a
// null check) go to TheGameSpyPSMessageQueue.
#include <string>
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
enum
{
	MAX_SLOTS = 8
};

class NAT;
class Transport;

// An address as BFME 2's NetworkInterface::setLocalAddress takes it.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// Vtable gaps: VSlots<N> declares slots 0..N-1 and VPad<B, N> the N slots
// after B's.
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

class GameSlot
{
public:
	virtual ~GameSlot();
	Bool isHuman(void) const;
	Bool isAI(void) const;
	Bool disconnected(void) const;
	Int getTeamNumber(void) const { return m_teamNumber; }

	UnsignedByte m_pre1C[0x1C - 4];
	Int m_teamNumber;				// +0x1C
	UnsignedByte m_pre30[0x30 - 0x20];
	UnicodeString m_name;				// +0x30
	AsciiString m_bfme34;				// +0x34, the player's name-key string
	UnsignedByte m_pre4C[0x4C - 0x38];
	Int m_bfme4C;					// +0x4C, the living-world battle's index
	UnsignedByte m_pre1A4[0x1A4 - 0x50];
	Bool m_bfme1A4;					// +0x1A4
	UnsignedByte m_pre1AC[0x1AC - 0x1A5];
};

class GameSpyGameSlot : public GameSlot
{
public:
	Int getProfileID(void) const { return m_profileID; }
	void setProfileID(Int id) { m_profileID = id; }
	void setSlotRankPoints(Int val) { m_rankPoints = val; }
	void setFavoriteSide(Int val) { m_favoriteSide = val; }
private:
	Int m_profileID;				// +0x1AC
	AsciiString m_gameSpyLogin;			// +0x1B0
	AsciiString m_gameSpyLocale;			// +0x1B4
	AsciiString m_pingStr;				// +0x1B8
	Int m_pingInt;					// +0x1BC
	Int m_wins;					// +0x1C0
	Int m_losses;					// +0x1C4
	Int m_rankPoints;				// +0x1C8
	Int m_favoriteSide;				// +0x1CC
};

// The slot's out-of-line AsciiString setters and getters, rowed on address
// classes: +0x1B0 (Zero Hour's setLoginName/getLoginName), +0x1B4
// (setLocale), +0x1D8, +0x1DC and +0x1A8.
class Rva004FDCE1AsciiField
{
public:
	AsciiString get(void) const;
	void rva004FDCFF(AsciiString value);
};
class Rva004FDD6DAsciiField
{
public:
	AsciiString get(void) const;
};
class Rva003821B9AsciiField
{
public:
	AsciiString get(void) const;
};
class Rva004FDD36AsciiField
{
public:
	void rva004FDD36(AsciiString value);
};
class Rva004CFB6DAsciiField
{
public:
	AsciiString get(void) const;
	void rva004CFB8B(AsciiString value);
};
class Rva004CFBC2AsciiField
{
public:
	void rva004CFBC2(AsciiString value);
};

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void v1() = 0; virtual void v2() = 0; virtual void v3() = 0;
	virtual void v4() = 0; virtual void v5() = 0; virtual void v6() = 0;
	virtual void v7() = 0; virtual void v8() = 0; virtual void v9() = 0;
	virtual void reset(void);			// slot 10 (+0x28)
	virtual void startGame(Int gameID) = 0;		// slot 11
	virtual Bool amIHost(void) const = 0;		// slot 12
	virtual Int getLocalSlotNum(void) const = 0;	// slot 13 (+0x34)
	void setSlotPointer(Int index, GameSlot *slot);
	GameSlot *getSlot(Int slotNum);
	void setMap(AsciiString mapName);
	AsciiString getMap(void) const;
	void markPlayerAsPreorder(Int index);
	void setGameInProgress(Bool inProgress) { m_inProgress = inProgress; }
	UnsignedInt getSeed(void) const { return m_seed; }
private:
	char m_pad04[0x11 - 4];
	Bool m_inProgress;				// +0x11
	char m_pad12[0x38 - 0x12];
protected:
	BfmeNetAddress m_localAddress;			// +0x38
private:
	char m_pad40[0x50 - 0x40];
	UnsignedInt m_seed;				// +0x50
	char m_pad54[0x58 - 0x54];
protected:
	Int m_bfme58;					// +0x58
private:
	char m_pad5C[0x60 - 0x5C];
public:
	Int m_bfme60;					// +0x60, zero when heroes are allowed
private:
	char m_pad64[0x6C - 0x64];
public:
	// Inline reads: retail 0x4FE5CA loads both into registers before pushing
	// them, where a plain member access is pushed from memory.
	Int getCmdPointFactor(void) const { return m_bfme6C; }
	Int getIniResource(void) const { return m_bfme70; }
	Int m_bfme6C;					// +0x6C, the command point factor
	Int m_bfme70;					// +0x70, the initial resources
private:
	char m_pad74[0xDC - 0x74];
};

class Rva00382398
{
public:
	Rva00382398();
	virtual ~Rva00382398();
private:
	char m_pad[0x1E0 - 4];
};

struct Rva003EFDDBOut;

class Rva003EFDDBHolder
{
public:
	void rva003EFDDB(Int index, Rva003EFDDBOut *out);

	UnsignedByte m_pre18[0x18];
	AsciiString m_mapName;			// +0x18
};

class LivingWorldBattle
{
public:
	Bool rva003F486C(Int index);

	UnsignedByte m_pre24[0x24];
	Rva003EFDDBHolder *m_holder;		// +0x24
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	virtual ~GameSpyStagingRoom();
	virtual void reset(void);
	virtual void startGame(Int gameID);
	void cleanUpSlotPointers(void);
	void launchGame(void);
	void rva004FDEFF(LivingWorldBattle *battle);
	void launchWOTRMPGame(void);
	AsciiString generateGameSpyGameResultsPacket(Bool sawCRCMismatch, Bool playerQuit);
	Bool isQMGame(void) { return m_isQM; }
private:
	Rva00382398 m_GameSpySlot[MAX_SLOTS]; // +0xDC
	AsciiString m_gameName;     // +0xFDC
	Int m_id;                   // +0xFE0
	NAT *m_transport;           // +0xFE4
	AsciiString m_localName;    // +0xFE8
	Bool m_bfmeFEC;             // +0xFEC
	Bool m_bfmeFED;             // +0xFED
	UnsignedInt m_bfmeFF0;      // +0xFF0
	Bool m_isQM;                // +0xFF4
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

void GameSpyStagingRoom::reset(void)
{
	GameInfo::reset();
}

class GameSpyStagingRoom;

// BFME 2's PlayerInfo as PeerDefs.cpp lays it out (0x34 bytes).
class PlayerInfo
{
public:
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_clan;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_side;
	Int m_unk24;
	Int m_dc;
	Int m_desync;
	Int m_preorder;
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
class GameSpyInfoSlot31 : public VPad<GameSpyInfoSlot22, 8>
{
public:
	virtual Int getLocalProfileID(void) = 0;			// slot 31 (+0x7C)
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
class GameSpyInfoInterface : public VPad<GameSpyInfoSlot53, 36>
{
public:
	virtual Bool didPlayerPreorder(Int profileID) const = 0;	// slot 90 (+0x168)
};
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyStagingRoom *TheGameSpyGame;

// The global in Zero Hour's TheNAT position (0x00E063F8).
class Rva005A6D47
{
public:
	virtual ~Rva005A6D47();
	UnsignedShort rva005A684F(Int slot);
	void rva005A6A4C(void);
	Transport *rva005801F2(void);
};
extern Rva005A6D47 *g_Va00E063F8;

// The object at 0x00E063EC, cleared through the rowed 0x0059EE7F.
class Rva0059EE7FDwordClearer
{
public:
	void clear();
};
extern int g_Va00E063EC;

void PopBackToLobby(void)
{
	if (g_Va00E063F8)
	{
		::delete g_Va00E063F8;
		g_Va00E063F8 = 0;
	}

	if (TheGameSpyInfo)
	{
		TheGameSpyInfo->getCurrentStagingRoom()->reset();
		TheGameSpyInfo->leaveStagingRoom();
	}

	if (g_Va00E063EC)
		((Rva0059EE7FDwordClearer *)g_Va00E063EC)->clear();
}

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);	// slot 15 (+0x3C)
};
extern GameTextInterface *TheGameText;

class MapMetaData;

class MapCache
{
public:
	void updateCache(void);
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

class GlobalData
{
public:
	UnsignedByte m_preAC0[0xAC0];
	AsciiString m_pendingFile;			// +0xAC0
};
extern GlobalData *TheWritableGlobalData;

class NetworkInterface
{
public:
	virtual ~NetworkInterface();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void parseUserList(const GameInfo *game);		// slot 17 (+0x44)
	virtual void setLocalAddress(const BfmeNetAddress *address);	// slot 18 (+0x48)
	virtual void attachTransport(Transport *transport);		// slot 19 (+0x4C)
	virtual void initTransport(void);				// slot 20 (+0x50)
};
extern NetworkInterface *TheNetwork;

Bool Rva0044C3D4(void);
Bool DoAnyMapTransfers(GameInfo *game);
void InitGameLogicRandom(UnsignedInt seed);
void GSMessageBoxOk(UnicodeString titleString, UnicodeString bodyString, void (*okFunc)(void));

void GameSpyStagingRoom::rva004FDEFF(LivingWorldBattle *battle)
{
	if (!battle)
		return;

	Rva003EFDDBHolder *battleHolder = battle->m_holder;
	const char *name = battleHolder->m_mapName.str();
	AsciiString mapName;
	mapName.format("maps\\%s\\%s.map", name, name);
	setMap(mapName);

	setGameInProgress(true);
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = (GameSpyGameSlot *)getSlot(i);
		if (slot->isHuman())
		{
			if (TheGameSpyInfo->didPlayerPreorder(slot->getProfileID()))
				markPlayerAsPreorder(i);
		}
	}

	if (!Rva0044C3D4())
	{
		if (TheNetwork)
		{
			::delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferHero"), 0);
		PopBackToLobby();
		return;
	}

	Bool filesOk = DoAnyMapTransfers(this);
	TheMapCache->updateCache();
	if (!filesOk || TheMapCache->findMap(getMap()) == 0)
	{
		if (TheNetwork)
		{
			::delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferMap"), 0);
		PopBackToLobby();
		return;
	}

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = getSlot(i);
		Int index = slot->m_bfme4C;
		Rva003EFDDBHolder *holder = battle->m_holder;
		holder->rva003EFDDB(index, (Rva003EFDDBOut *)slot);
		slot->m_bfme1A4 = battle->rva003F486C(index);
	}

	TheWritableGlobalData->m_pendingFile = TheGameSpyGame->getMap();
	InitGameLogicRandom(getSeed());
}

void CreateTheNetwork(void);

extern GameLogic *TheGameLogic;

class LivingWorldManager
{
public:
	void rva0021427A(void);
};
extern LivingWorldManager *TheLivingWorldManager;

class LivingWorldLogic
{
public:
	UnsignedByte m_preEC[0xEC];
	Int m_bfmeEC;					// +0xEC
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002D3627Host
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9();
	virtual void rva10(Int value);			// slot 10 (+0x28)
};
extern Rva002D3627Host *g_00DFEF18;

class GameMessage
{
public:
	void appendIntegerArgument(Int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(Int type);	// slot 18 (+0x48)
};
extern MessageStream *MessageStreamSubsystem;

enum GameSpyBuddyStatus
{
	GAMESPY_BUDDY_STATUS_4 = 4
};
_STL::string WideCharStringToMultiByte(const unsigned short *orig);
void updateBuddyStatus(GameSpyBuddyStatus status, int sleepTime, _STL::string mapName);

// The rowed name getter 0x0022C4DF, called on TheGameSpyGame.
class Rva0022C4DF
{
public:
	UnicodeString rva0022C4DF(void) const;
};

void GameSpyStagingRoom::launchWOTRMPGame(void)
{
	setGameInProgress(true);
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = (GameSpyGameSlot *)getSlot(i);
		if (slot->isHuman())
		{
			if (TheGameSpyInfo->didPlayerPreorder(slot->getProfileID()))
				markPlayerAsPreorder(i);
		}
	}

	CreateTheNetwork();
	BfmeNetAddress localAddress = m_localAddress;
	if (g_Va00E063F8)
		localAddress.m_port = g_Va00E063F8->rva005A684F(getLocalSlotNum());
	TheNetwork->setLocalAddress(&localAddress);
	if (g_Va00E063F8)
	{
		g_Va00E063F8->rva005A6A4C();
		TheNetwork->attachTransport(g_Va00E063F8->rva005801F2());
	}
	else
	{
		TheNetwork->initTransport();
	}
	TheNetwork->parseUserList(this);
	TheGameLogic->rva00376E92(false, false);

	Bool heroesOk = Rva0044C3D4();
	if (!heroesOk)
	{
		if (TheNetwork)
		{
			::delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferHero"), 0);
		PopBackToLobby();
		return;
	}

	if (TheLivingWorldManager)
		TheLivingWorldManager->rva0021427A();
	TheLivingWorldLogic->m_bfmeEC = 0;
	TheGameLogic->rva00376E92(false, false);
	g_00DFEF18->rva10(1);

	GameMessage *msg = MessageStreamSubsystem->appendMessage(0x1F);
	if (msg)
	{
		msg->appendIntegerArgument(m_bfme58);
		msg->appendIntegerArgument(2);
	}

	InitGameLogicRandom(getSeed());
	updateBuddyStatus(GAMESPY_BUDDY_STATUS_4, 0,
		WideCharStringToMultiByte(((Rva0022C4DF *)TheGameSpyGame)->rva0022C4DF().str()));

	if (g_Va00E063F8)
	{
		::delete g_Va00E063F8;
		g_Va00E063F8 = 0;
	}
}

// TheGameLogic's byte +0x9D, which the shared GameLogic view does not lay
// out; LANAPI::OnGameStart sets it the same way after MSG_NEW_GAME.
struct GameLogicStartView
{
	UnsignedByte m_pre9D[0x9D];
	Bool m_bfme9D;					// +0x9D
};

// BFME 2's 0x598-byte persistent-storage request (the rowed ctor 0x00556523
// and dtor 0x0038A1F2), queued through TheGameSpyPSMessageQueue vslot 4.
struct BfmeOpaqueOwnedRecord1432
{
	BfmeOpaqueOwnedRecord1432();
	~BfmeOpaqueOwnedRecord1432();
	Int requestType;
	UnsignedByte m_pad04[0x598 - 4];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread(void);
	virtual void endThread(void);
	virtual Bool isThreadRunning(void);
	virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &req);	// slot 4 (+0x10)
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

void GameSpyStagingRoom::launchGame(void)
{
	setGameInProgress(true);
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = (GameSpyGameSlot *)getSlot(i);
		if (slot->isHuman())
		{
			if (TheGameSpyInfo->didPlayerPreorder(slot->getProfileID()))
				markPlayerAsPreorder(i);
		}
	}

	CreateTheNetwork();
	BfmeNetAddress localAddress = m_localAddress;
	if (g_Va00E063F8)
		localAddress.m_port = g_Va00E063F8->rva005A684F(getLocalSlotNum());
	TheNetwork->setLocalAddress(&localAddress);
	if (g_Va00E063F8)
	{
		g_Va00E063F8->rva005A6A4C();
		TheNetwork->attachTransport(g_Va00E063F8->rva005801F2());
	}
	else
	{
		TheNetwork->initTransport();
	}
	TheNetwork->parseUserList(this);
	TheGameLogic->rva00376E92(false, false);

	Bool heroesOk = Rva0044C3D4();
	if (!heroesOk)
	{
		if (TheNetwork)
		{
			::delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferHero"), 0);
		PopBackToLobby();
		return;
	}

	Bool filesOk = DoAnyMapTransfers(this);
	TheMapCache->updateCache();
	if (!filesOk || TheMapCache->findMap(getMap()) == 0)
	{
		if (TheNetwork)
		{
			::delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferMap"), 0);
		PopBackToLobby();
		return;
	}

	TheWritableGlobalData->m_pendingFile = TheGameSpyGame->getMap();

	GameMessage *msg = MessageStreamSubsystem->appendMessage(0x1E);
	msg->appendIntegerArgument(5);
	msg->appendIntegerArgument(1);
	msg->appendIntegerArgument(0);
	msg->appendIntegerArgument(m_bfme1018);
	((GameLogicStartView *)TheGameLogic)->m_bfme9D = true;

	InitGameLogicRandom(getSeed());
	updateBuddyStatus(GAMESPY_BUDDY_STATUS_4, 0,
		WideCharStringToMultiByte(((Rva0022C4DF *)TheGameSpyGame)->rva0022C4DF().str()));

	if (g_Va00E063F8)
	{
		::delete g_Va00E063F8;
		g_Va00E063F8 = 0;
	}

	if (m_isQM)
	{
		if (m_bfme101C)
		{
			BfmeOpaqueOwnedRecord1432 req;
			req.requestType = 7;
			TheGameSpyPSMessageQueue->addRequest(req);
		}
		BfmeOpaqueOwnedRecord1432 req;
		req.requestType = 5;
		if (TheGameSpyPSMessageQueue)
			TheGameSpyPSMessageQueue->addRequest(req);
	}
}

// Retail's str() falls back to its function-local TheNullChr, which the
// linker folded with the "" literal at 0x00BBAC1C. This TU's shim str()
// returns "" itself, so the empty quick-match strings below name the pinned
// g_bfmeEmptyF9 there to keep the two constants distinct, as in retail.
extern char g_bfmeEmptyF9[];

void GameSpyStagingRoom::startGame(Int gameID)
{
	Int numHumans = 0;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = (GameSpyGameSlot *)&m_GameSpySlot[i];
		if (slot->isHuman())
		{
			++numHumans;
			AsciiString gsName;
			gsName.translate(slot->m_name);
			((Rva004FDCE1AsciiField *)slot)->rva004FDCFF(gsName);
			PlayerInfo *info = TheGameSpyInfo->rva00382CCE(gsName.str());

			if (m_isQM)
			{
				if (getLocalSlotNum() == i)
					slot->setProfileID(TheGameSpyInfo->getLocalProfileID());
				((Rva004CFB6DAsciiField *)slot)->rva004CFB8B(g_bfmeEmptyF9);
				((Rva004CFBC2AsciiField *)slot)->rva004CFBC2(g_bfmeEmptyF9);
			}
			else
			{
				PlayerInfoMap *pInfoMap = TheGameSpyInfo->getPlayerInfoMap();
				PlayerInfoMap::iterator it = pInfoMap->end();
				if (info)
					it = pInfoMap->find(info->m_name);
				if (it != pInfoMap->end())
				{
					slot->setProfileID(it->second.m_profileID);
					((Rva004FDD36AsciiField *)slot)->rva004FDD36(it->second.m_clan);
					slot->setSlotRankPoints(it->second.m_rankPoints);
					slot->setFavoriteSide(it->second.m_desync);
				}
			}
		}
	}

	if (numHumans < 2)
		launchGame();
}

class PlayerTemplate
{
public:
	const AsciiString &getSide(void) const { return m_side; }
private:
	UnsignedByte m_pre18[0x18];
	AsciiString m_side;				// +0x18
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate(void) const { return m_playerTemplate; }
private:
	UnsignedByte m_pre34[0x34];
	const PlayerTemplate *m_playerTemplate;		// +0x34
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};
extern PlayerList *ThePlayerList;

extern GameInfo *TheGameInfo;

// The victory conditions at 0x00E03138, kept under its address name: slot 14
// as Zero Hour's hasAchievedVictory, 16 as hasSinglePlayerBeenDefeated and 22
// as getEndFrame (Zero Hour's six-slot gap between the first and the last).
class Rva00E03138Slot14 : public VSlots<14>
{
public:
	virtual Bool hasAchievedVictory(Player *player) = 0;		// slot 14 (+0x38)
};
class Rva00E03138Slot16 : public VPad<Rva00E03138Slot14, 1>
{
public:
	virtual Bool hasSinglePlayerBeenDefeated(Player *player) = 0;	// slot 16 (+0x40)
};
class Rva00E03138 : public VPad<Rva00E03138Slot16, 5>
{
public:
	virtual UnsignedInt getEndFrame(void) = 0;			// slot 22 (+0x58)
};
extern Rva00E03138 *g_00E03138;

// The donor's StringBase<char>::concat(char) form (as GameInfoSetMap.cpp): the
// character goes through its own one-byte slot into concat(text, 1).
static inline void concatChar(AsciiString &s, char c)
{
	((StringBase<char> *)&s)->concat(&c, 1);
}

AsciiString GameSpyStagingRoom::generateGameSpyGameResultsPacket(Bool sawCRCMismatch, Bool playerQuit)
{
	Int i;
	Int endFrame = g_00E03138->getEndFrame();
	Int localSlotNum = getLocalSlotNum();
	Int winningTeam = -1;
	Int numHumans = 0;
	Int numPlayers = 0;
	Int numAIs = 0;
	Int numTeamsAtGameEnd = 0;
	Int lastTeamAtGameEnd = -1;
	for (i = 0; i < MAX_SLOTS; ++i)
	{
		AsciiString playerName;
		playerName = TheGameInfo->getSlot(i)->m_bfme34;
		Player *p;
		if (!playerName.isEmpty() &&
			(p = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName))) != 0)
		{
			++numHumans;
			if (g_00E03138->hasAchievedVictory(p))
				winningTeam = getSlot(i)->getTeamNumber();

			// check if he lasted
			GameSlot *slot = getSlot(i);
			if (!slot->disconnected())
			{
				if (slot->getTeamNumber() != lastTeamAtGameEnd || numTeamsAtGameEnd == 0)
				{
					lastTeamAtGameEnd = slot->getTeamNumber();
					++numTeamsAtGameEnd;
				}
			}
		}
		else if (((GameSlot *)&m_GameSpySlot[i])->isAI())
		{
			++numAIs;
		}
	}
	numPlayers = numHumans + numAIs;

	AsciiString mapName;
	for (i = 0; i < getMap().getLength(); ++i)
	{
		char c = getMap().getCharAt(i);
		if (c == '\\')
			c = '/';
		concatChar(mapName, c);
	}

	AsciiString ladder;
	if (isQMGame())
	{
		if (m_bfmeFF8 == 1)
			ladder = "1v1";
		else if (m_bfmeFF8 == 2)
			ladder = "2v2";
		else if (m_bfmeFF8 == 3)
			ladder = "clan";
	}
	else
	{
		ladder = "none";
	}

	AsciiString results;
	results.format("\\hostname\\%s\\mapname\\%s\\numplayers\\%d\\duration\\%d\\localplayer\\%d\\ladder\\%s",
		((Rva004FDCE1AsciiField *)&m_GameSpySlot[0])->get().str(), mapName.str(), numPlayers, endFrame,
		localSlotNum, ladder.str());

	if (ladder.compare("clan") == 0 && TheGameInfo)
	{
		AsciiString clanRule;
		clanRule.format("\\clanRule\\allowHero=%s:cmdPointFactor=%d:iniResource=%d",
			TheGameInfo->m_bfme60 == 0 ? "yes" : "no", TheGameInfo->getCmdPointFactor(), TheGameInfo->getIniResource());
		results += clanRule;
	}

	Int playerID = 0;
	for (i = 0; i < MAX_SLOTS; ++i)
	{
		AsciiString playerName;
		playerName = TheGameInfo->getSlot(i)->m_bfme34;
		Player *p;
		if (!playerName.isEmpty() &&
			(p = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(playerName))) != 0)
		{
			GameSpyGameSlot *slot = (GameSpyGameSlot *)&m_GameSpySlot[i];
			AsciiString authName = ((Rva004CFB6DAsciiField *)slot)->get();
			AsciiString authToken = ((Rva004FDD6DAsciiField *)slot)->get();
			AsciiString clanID = (m_isQM && m_bfmeFF8 == 3) ?
				((Rva003821B9AsciiField *)slot)->get() : AsciiString::TheEmptyString;
			clanID.trim();
			AsciiString playerName = (slot->isHuman()) ? ((Rva004FDCE1AsciiField *)slot)->get() : "AIPlayer";
			Int gsPlayerID = slot->getProfileID();
			Bool disconnected = slot->disconnected();

			AsciiString result, side = "unknown";
			if (sawCRCMismatch)
			{
				if (!g_00E03138->hasSinglePlayerBeenDefeated(p))
					result = "desync";
				else
					result = "quit";
			}
			else if (disconnected)
			{
				result = "discon";
			}
			else if (g_00E03138->hasSinglePlayerBeenDefeated(p) && playerQuit)
			{
				result = "quit";
			}
			else if (g_00E03138->hasAchievedVictory(p))
			{
				result = "win";
			}
			else
			{
				result = "loss";
			}

			side = p->getPlayerTemplate()->getSide();

			AsciiString playerStr;
			playerStr.format("\\player_%d\\%s\\pid_%d\\%d\\team_%d\\%d\\result_%d\\%s\\side_%d\\%s\\clanID_%d\\%s\\auth_%d\\%s\\authtoken_%d\\%s",
				playerID, playerName.str(), playerID, gsPlayerID, playerID, slot->getTeamNumber(),
				playerID, result.str(), playerID, side.str(), playerID, clanID.str(),
				playerID, authName.str(), playerID, authToken.str());
			results += playerStr;
			++playerID;
		}
	}

	return results;
}
