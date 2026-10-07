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
#include "ascii_string.h"
#include "unicode_string.h"

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

	UnsignedByte m_pre4C[0x4C - 4];
	Int m_bfme4C;					// +0x4C, the living-world battle's index
	UnsignedByte m_pre1A4[0x1A4 - 0x50];
	Bool m_bfme1A4;					// +0x1A4
	UnsignedByte m_pre1AC[0x1AC - 0x1A5];
};

class GameSpyGameSlot : public GameSlot
{
public:
	Int getProfileID(void) const { return m_profileID; }
private:
	Int m_profileID;				// +0x1AC
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
	char m_pad12[0x50 - 0x12];
	UnsignedInt m_seed;				// +0x50
	char m_pad54[0xDC - 0x54];
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
	void cleanUpSlotPointers(void);
	void rva004FDEFF(LivingWorldBattle *battle);
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

class GameSpyStagingRoom;

class GameSpyInfoSlot47 : public VSlots<47>
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
