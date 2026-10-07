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
// GameSpyStagingRoom::rva004FE126 @ 0x004FE126 (569 bytes), named by
// address: the GameSpy twin of the rowed LANAPI::rva0024900D (its only caller
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
// favorite side. Zero Hour's numHumans < 2 launch becomes one call to
// 0x004FED35 on the room.
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

	UnsignedByte m_pre30[0x30 - 4];
	UnicodeString m_name;				// +0x30
	UnsignedByte m_pre4C[0x4C - 0x34];
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

// The slot's out-of-line AsciiString setters, rowed on address classes:
// +0x1B0 (Zero Hour's setLoginName), +0x1B4 (setLocale), +0x1D8 and +0x1DC.
class Rva004FDCE1AsciiField
{
public:
	void rva004FDCFF(AsciiString value);
};
class Rva004FDD36AsciiField
{
public:
	void rva004FDD36(AsciiString value);
};
class Rva004CFB6DAsciiField
{
public:
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
	char m_pad5C[0xDC - 0x5C];
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
	void rva004FED35(void);
	void rva004FDEFF(LivingWorldBattle *battle);
	void rva004FE126(void);
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

void GameSpyStagingRoom::rva004FE126(void)
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

// Retail's str() falls back to its function-local TheNullChr, which the
// linker folded with the "" literal at 0x00BBAC1C. This TU's shim str()
// returns "" itself, so the empty quick-match strings below name the pinned
// g_bfmeEmptyF9 there to keep the two constants distinct, as in retail.
extern char g_bfmeEmptyF9[];

// ?startGame@GameSpyStagingRoom@@UAEXH@Z present-unmatched
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
		rva004FED35();
}
