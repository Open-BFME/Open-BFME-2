// ?ProcessGameSpyResponses@AptOnlineCustomMatch@@QAEXXZ
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// platformsdk
//
// ?ProcessGameSpyResponses@AptOnlineCustomMatch@@QAEXXZ
// retail 0x005A2DB7..0x005A51B9 (9218 bytes EH) thiscall.
//
// The online custom match screen's GameSpy response pump: WorldBuilder
// 0x014F0FA0 AptOnlineCustomMatch::ProcessGameSpyResponses
// (AptOnlineCustomMatch.cpp; a unit of its own here for its /G7 flags). It
// merges Zero Hour's WOLLobbyMenuUpdate and WOLGameSetupMenuUpdate response
// loops (semantic guide) onto the Apt screen: buddy and persistent-storage
// responses first, then up to getMaxMessagesPerUpdate peer responses, each
// also shown to the messenger (0x005AF12F), until an important one is seen.
// Evidence (target): the retail case bodies, labels and callees; field
// offsets and virtual slots are read from retail (they differ from the
// WorldBuilder build).
//
// The register shape (13 held in ESI from the switch head through the
// PLAYERJOIN kick, `this` in a frame home) follows the original's inline
// GameSlot accessors, which the WorldBuilder build shows as calls: the saved
// slot getters while restoring a save in PLAYERJOIN and the slot getters in
// PLAYERUTM. PLAYERCHANGEDFLAGS and response 22 are separate case bodies
// (distinct WorldBuilder jump-table targets), which retail's dispatch tail
// `jne default; jmp` keeps after cross-jumping merges them.

#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
// Retail calls MSVCR71 _mbscat here (thunk 0x0062988C), not strcat.
#include <mbstring.h>
#include <stdlib.h>
#include <stdio.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include <map>
#include <string>
#include <vector>
#undef free
// Character-buffer cleanup remains inline; the library supplies deallocate.
namespace _STL { template <> __declspec(dllimport) __forceinline void allocator<unsigned short>::deallocate(unsigned short *p, size_t) const { if (p != 0) _STL::free(p); } }

// Retail calls the STLport library's string operator= (0x0001B790);
// declaring the specialization keeps this /O1 unit from emitting its own
// divergent copy and the helpers it pulls in.
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::operator=(const char *s);
}

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Color;

enum { MAX_SLOTS = 8 };
enum { PLAYERTEMPLATE_OBSERVER = -2 };
enum SlotState { SLOT_OPEN = 0, SLOT_PLAYER = 6 };
enum GameSpyColors { GSCOLOR_DEFAULT = 0 };

// strncpy, sscanf, atoi and _strcmpi go through msvcr71's import table while
// the inlined STLport string destructors free through the game's direct
// _free; /D_CRTIMP= gives the direct forms and the IAT forms live in their own
// scope (as GameInfoPlayerCounts.cpp).
namespace CrtIAT
{
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dest, const char *src, size_t count);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *s, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
}

#define NOMINMAX
#include <WinSock2.h>
#include <windows.h>
#include <mmsystem.h>

extern Color GameSpyColor[];

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *movie, const char *path, const char *function);

void HandleBuddyResponses();
void HandlePersistentStorageResponses();
// AptMessengerOnline::ProcessGameSpyResponse in WorldBuilder.
class AptMessengerOnline
{
public:
	static bool ProcessGameSpyResponse(void *response);
};
// Zero Hour's GameSpyCloseAllOverlays.
void Rva00548C1ACleanup();
void GSMessageBoxOk(UnicodeString title, UnicodeString body, void (*okFunc)() = 0);
void Rva0059FF9DDo();
void TearDownGameSpy();
std::wstring MultiByteToWideCharSingleLine(const char *orig);

// An IP and port pair, copied as one 8-byte block.
struct IPPort
{
	IPPort(UnsignedInt ip, UnsignedShort port) : m_ip(ip), m_port(port) {}
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
	virtual void slot16();
	virtual UnicodeString *fetchPtr(const char *label, bool *exists = 0); // vslot 17
};
extern GameTextInterface *TheGameText;

class Shell
{
public:
	void pop();
};
extern Shell *TheShell;

class MultiplayerSettings
{
public:
	Int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}

private:
	UnsignedByte m_pre38[0x38];
	Int m_colorCount; // +0x38
	UnsignedByte m_pre3c[0x40 - 0x3C];
	Int m_numColors; // +0x40
};
extern MultiplayerSettings *TheMultiplayerSettings;

class PlayerTemplate
{
	UnsignedByte m_data[0x1DC];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const { return m_end - m_begin; }

private:
	UnsignedByte m_pre0c[0x0C];
	PlayerTemplate *m_begin; // +0x0C
	PlayerTemplate *m_end;   // +0x10
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(bool full);

	UnicodeString m_displayName; // +0x00
	UnsignedByte m_pad04[0x20 - 0x04];
	Int m_numPlayers;			 // +0x20
	UnsignedByte m_pad24[0x26 - 0x24];
	Bool m_isOfficial;		   // +0x26
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

class GameState
{
public:
	AsciiString getMapLeafName(const AsciiString &in) const;
};
extern GameState *TheGameState;

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : nat(0), port(0) {}
	unsigned int nat;
	unsigned short port;
};

class GameSlot
{
public:
	GameSlot();
	GameSlot(const GameSlot &that);
	virtual ~GameSlot();

	bool isOccupied() const;
	bool isHuman() const;
	bool isOpen() const;
	bool isPlayer(AsciiString name) const;
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *info);
	void setPlayerTemplate(int playerTemplate);
	void unAccept();
	void setMapAvailability(bool available);
	bool decodeHero(UnsignedByte hero);
	void rva003FF5F2(const AsciiString &clanID);

	const UnicodeString &getName() const { return m_name; }
	Int getColor() const { return m_color; }
	void setColor(Int v) { m_color = v; }
	Int getStartPos() const { return m_startPos; }
	void setStartPos(Int v) { m_startPos = v; }
	void setStartPos14(Int v) { m_startPos14 = v; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
	void setTeamNumber(Int v) { m_teamNumber = v; }
	Int getHandicap() const { return m_handicap; }
	void setHandicap(Int v) { m_handicap = v; }
	void setNATBehavior(Int v) { m_natBehavior = v; }
	Int getHero0() const { return m_hero[0]; }
	Int getHero1() const { return m_hero[1]; }
	Int getHero2() const { return m_hero[2]; }
	Int getHero3() const { return m_hero[3]; }

	void setIP(UnsignedInt ip)
	{
		IPPort ipPort = m_ipPort;
		ipPort.m_ip = ip;
		m_ipPort = ipPort;
	}

	Int m_state;			 // +0x04
	Bool m_isAccepted;	   // +0x08
	Bool m_hasMap;		   // +0x09
	UnsignedByte m_pad0a[0x0C - 0x0A];
	Int m_color;			 // +0x0C
	Int m_startPos;		  // +0x10
	Int m_startPos14;		// +0x14
	Int m_playerTemplate;	// +0x18
	Int m_teamNumber;		// +0x1C
	Int m_handicap;		  // +0x20
	UnsignedByte m_pad24[0x30 - 0x24];
	UnicodeString m_name;	// +0x30
	UnsignedByte m_pad34[0x38 - 0x34];
	IPPort m_ipPort;		 // +0x38
	Int m_natBehavior;	   // +0x40
	UnsignedByte m_pad44[0x50 - 0x44];
	Int m_hero[4];		   // +0x50
	UnsignedByte m_pad60[0x1AC - 0x60];
};

// Rowed setter of the slot's last hero word (+0x5C).
class Rva003FF0E7DwordSlot
{
public:
	void set(int value);
};

// AsciiString view whose text compare is declared nonthrowing, so a
// temporary compared through it needs no unwind state (retail registers none
// for the clan id); the spelling resolves to the rowed
// StringBase<char>::compare(const char *) at 0x000069B1 (as INIAsciiIndexParse.cpp).
class Rva004DBFF1Name : public AsciiString
{
public:
	int compareText(const char *text) const throw();
};

// Rowed getter of the slot's clan id.
class Rva003821B9AsciiField
{
public:
	AsciiString get() const;
};

// The GameSpy slot's ping string setter (address-named row).
class Rva004FDB04
{
public:
	void rva004FDB04(AsciiString ping);
};

class GameSpyGameSlot : public GameSlot
{
public:
	Int m_profileID;		 // +0x1AC
	UnsignedByte m_pad1b0[0x1D0 - 0x1B0];
	Int m_ladderRank1v1;	 // +0x1D0
	Int m_ladderRank2v2;	 // +0x1D4
};

// A saved game's slot records (+0x4C of the record the room keeps at +0xC8).
struct SavedSlot
{
	UnsignedByte m_pad00[0x0C];
	Int m_color;			 // +0x0C
	UnsignedByte m_pad10[0x14 - 0x10];
	Int m_startPos;		  // +0x14
	Int m_playerTemplate;	// +0x18
	Int m_teamNumber;		// +0x1C
	Int m_handicap;		  // +0x20
	UnsignedByte m_pad24[0x50 - 0x24];
	Int m_hero[4];		   // +0x50
	UnsignedByte m_pad60[0x1AC - 0x60];
	Int getColor() const { return m_color; }
	Int getStartPos() const { return m_startPos; }
	Int getPlayerTemplate() const { return m_playerTemplate; }
	Int getTeamNumber() const { return m_teamNumber; }
	Int getHandicap() const { return m_handicap; }
	Int getHero0() const { return m_hero[0]; }
	Int getHero1() const { return m_hero[1]; }
	Int getHero2() const { return m_hero[2]; }
	Int getHero3() const { return m_hero[3]; }
};

struct SavedGameSlots
{
	UnsignedByte m_pad00[0x4C];
	SavedSlot m_slots[MAX_SLOTS]; // +0x4C
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void reset();					  // slot 10
	virtual void startGame(Int gameID);		// slot 11
	virtual bool v12();						// slot 12
	virtual Int getLocalSlotNum() const;	   // slot 13
	virtual void resetAccepted();			  // slot 14

	GameSlot *getSlot(Int index);
	const GameSlot *getConstSlot(Int index) const;
	Int getSlotNum(AsciiString name) const;
	AsciiString getMap() const;
	void setSlot(Int index, GameSlot slot);
	void rva003FF1A7(Int mode);

	Bool isInGame() const { return m_inGame; }
	UnsignedInt getMapCRC() const { return m_mapCRC; }

	UnsignedByte m_pad04[0x10 - 0x04];
	Bool m_inGame;			   // +0x10
	Bool m_inProgress;		   // +0x11
	UnsignedByte m_pad12[0x38 - 0x12];
	IPPort m_localIPPort;		// +0x38
	UnsignedByte m_pad40[0x44 - 0x40];
	UnsignedInt m_mapCRC;		// +0x44
	UnsignedByte m_pad48[0x60 - 0x48];
	Int m_rules[10];			 // +0x60
	UnsignedByte m_pad88[0x8C - 0x88];
	Bool m_restoringSave;		// +0x8C
	UnsignedByte m_pad8d[0xC8 - 0x8D];
	SavedGameSlots *m_savedSlots; // +0xC8
};

Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool flag = false);
bool Rva00300E42Check(GameInfo *game);
void SendStatsToOtherPlayers(GameInfo *game);

// GameSpyStagingRoom assignment (rowed under an address name).
class Rva00382E73
{
public:
	Rva00382E73 &operator=(const Rva00382E73 &that);
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyGameSlot *getGameSpySlot(Int index);

	UnsignedByte m_pad0cc[0xFDC - 0xCC];
	AsciiString m_ladderIP;	  // +0xFDC
	UnsignedByte m_padfe0[0xFF4 - 0xFE0];
	Bool m_ff4;				  // +0xFF4
	UnsignedByte m_padff5[0xFF8 - 0xFF5];
	Int m_ff8;				   // +0xFF8
	UnsignedByte m_padffc[0x1018 - 0xFFC];
	Int m_seed;				  // +0x1018
};
extern GameSpyStagingRoom *TheGameSpyGame;

class PlayerInfo
{
public:
	AsciiString m_00;
	AsciiString m_name; // +0x04
};

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

// The peer response (layout of PeerThreadRetail.h; 0x348 bytes).
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();

	enum
	{
		PEERRESPONSE_DISCONNECT = 1,
		PEERRESPONSE_STAGINGROOMLISTCOMPLETE = 5,
		PEERRESPONSE_JOINGROUPROOM = 7,
		PEERRESPONSE_CREATESTAGINGROOM = 8,
		PEERRESPONSE_JOINSTAGINGROOM = 9,
		PEERRESPONSE_PLAYERJOIN = 10,
		PEERRESPONSE_PLAYERLEFT = 11,
		PEERRESPONSE_PLAYERINFO = 13,
		PEERRESPONSE_PLAYERCHANGEDFLAGS = 14,
		PEERRESPONSE_ROOMUTM = 15,
		PEERRESPONSE_PLAYERUTM = 16,
		PEERRESPONSE_GAMESTART = 18,
		PEERRESPONSE_FAILEDTOHOST = 19,
		PEERRESPONSE_22 = 22
	};

	Int peerResponseType;					   // +0x00
	std::string groupRoomName;				  // +0x04
	std::string nick;						   // +0x10
	std::string oldNick;						// +0x1C
	std::wstring text;						  // +0x28
	std::string locale;						 // +0x34
	std::string stagingServerGameOptions;	   // +0x40
	std::wstring stagingServerName;			 // +0x4C
	std::string stagingServerPingString;		// +0x58
	std::string stagingServerLadderIP;		  // +0x64
	std::string stagingRoomMapName;			 // +0x70
	std::string unknown_7c;					 // +0x7C
	std::string stagingRoomPlayerNames[MAX_SLOTS]; // +0x88
	std::string command;						// +0xE8
	std::string commandOptions;				 // +0xF4
	std::vector<AsciiString> unknown_100;	   // +0x100

	union
	{
		UnsignedInt unknown_payload[143];
		struct { Int reason; } discon;
		struct { Int id; Bool ok; } joinGroupRoom;
		struct { Int result; } createStagingRoom;
		struct { Int id; Bool ok; Bool isHostPresent; Int result; } joinStagingRoom;
		struct { Int seed; } gameStart;
		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			Int roomType;
			Int flags;
			UnsignedInt IP;
		} player;
	};
};

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	std::string nick;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string id;
	std::string options;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	bool isStagingRoom; // +0x118
	unsigned char m_tail[0x1EC - 0x119];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest(const PeerRequest &request) = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual bool getResponse(PeerResponse &response) = 0; // slot 9
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class PSPlayerAllStats
{
public:
	PSPlayerAllStats(Int id);
	PSPlayerAllStats(const PSPlayerAllStats &that);
	~PSPlayerAllStats();
	Int getID() const { return m_id; }

private:
	Int m_id;
	UnsignedByte m_rest[0x548 - 0x04];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual bool isThreadRunning() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void trackPlayerStats(PSPlayerAllStats stats) = 0;	// slot 8
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual PSPlayerAllStats findPlayerStatsByID(Int id) = 0;	 // slot 12
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0)
	virtual void reset() = 0;											// slot 1
	V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	virtual void playerLeftGroupRoom(AsciiString nick) = 0;			  // slot 20
	virtual PlayerInfoMap *getPlayerInfoMap() = 0;					   // slot 21
	V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46)
	virtual void leaveStagingRoom() = 0;								 // slot 47
	virtual void markAsStagingRoomHost() = 0;							// slot 48
	V(49) V(50)
	virtual bool amIHost() = 0;										  // slot 51
	V(52)
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;			 // slot 53
	V(54)
	virtual void setGameOptions() = 0;								   // slot 55
	V(56) V(57) V(58) V(59)
	V(60)
	virtual void addText(UnicodeString message, Color color) = 0;		// slot 61
	V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84)
	virtual UnsignedInt getInternalIP() = 0;							 // slot 85
	virtual UnsignedShort getInternalPort() = 0;						 // slot 86
	V(87) V(88) V(89)
	V(90) V(91) V(92)
	virtual Int getMaxMessagesPerUpdate() = 0;						   // slot 93
#undef V
};
extern GameSpyInfoInterface *TheGameSpyInfo;

// Zero Hour's GameSpyInfo::updatePlayerInfo path for a joining player.
struct Rva00382D39Input;
class GameSpyInfo
{
public:
	void rva00382D39(Rva00382D39Input *source, AsciiString oldNick);
};

// The NAT negotiator's listener list (+0x2C) and the screen's listener base.
struct Rva002BA8F1Listener
{
	virtual void v00();
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

// The NAT negotiator object (0x974 bytes; its constructor is rowed under an
// address name).
class Rva005A734B
{
public:
	Rva005A734B();
	UnsignedByte m_data[0x974];
};

struct NAT
{
	void attachSlotList(GameInfo *game, Int localSlot, UnsignedInt localIP, UnsignedInt unused, bool flag);
	void processPlayerJoin(Int slot);
	void processPlayerLeave(Int slot);
	void processGlobalMessage(Int slot, const char *options);

	UnsignedByte m_pad00[0x2C];
	Rva005A0B4CList m_listeners; // +0x2C
};
extern NAT *TheNAT;

class AptConnectionScreen
{
public:
	AptConnectionScreen(void *movie);
	UnsignedByte m_data[0x60];
};

class Rva005170CD
{
public:
	void rva005170CD();
};

struct AptOnlineCustomMatchOwner
{
	UnsignedByte m_pad000[0x274];
	void *m_movie; // +0x274
	UnsignedByte m_pad278[0x2B0 - 0x278];
	Int m_2b0;	 // +0x2B0
};

// The +0x70 game setup panel and its rowed helpers.
class Rva0043DB47DoubleSetter
{
public:
	void enable();
};

class Rva0043DB5EByteOneSetter
{
public:
	void enable();
};

class Rva0043DFE0
{
public:
	void rva0043DBA3();
};

class AptMpGameSetup
{
public:
	virtual void v00();
	virtual void v01();

	void rva0043DC0F();
	bool rva0043DCFA(Int startPos);

	void enable() { ((Rva0043DB47DoubleSetter *)this)->enable(); }
	void enableByte() { ((Rva0043DB5EByteOneSetter *)this)->enable(); }
	void rva0043DBA3() { ((Rva0043DFE0 *)this)->rva0043DBA3(); }
};

extern Int g_Va00E0333C;

class GameModePreferences
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual bool write(); // slot 3
	void rva0054F7C0(Int groupRoom);
};

class CustomMatchScreen
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	// vslot 10: the screen's Apt path for its callbacks.
	virtual const char *v10();

protected:
	UnsignedByte m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	UnsignedByte m_pad05c[0x6C - 0x5C];
};

// The games list refresh (pinned spelling).
class Rva005A0D61
{
public:
	void rva005A061B();
};

class AptOnlineCustomMatch : public CustomMatchScreen, public Rva002BA8F1Listener
{
public:
	void ProcessGameSpyResponses();
	void PopulateLobbyComboBox();
	void rva005A20A7();
	bool rva005A1EEE();

	void PopulateGamesListBox();

private:
	AptMpGameSetup m_setup;			 // +0x70
	UnsignedByte m_pad074[0xEC - 0x74];
	Int m_gameMode;					 // +0xEC
	UnsignedByte m_pad0f0[0x46C - 0xF0];
	GameModePreferences m_prefs;		// +0x46C
	UnsignedByte m_pad470[0x488 - 0x470];
	Int m_state;						// +0x488
	UnsignedByte m_pad48c[0x4A0 - 0x48C];
	Bool m_popUp;					   // +0x4A0
	UnsignedByte m_pad4a1[0x4A8 - 0x4A1];
	Int m_localSlot;					// +0x4A8
	UnsignedByte m_pad4ac[0x4B0 - 0x4AC];
	UnsignedInt m_lastSlotlistTime;	 // +0x4B0
	Bool m_initialAcceptEnable;		 // +0x4B4
	UnsignedByte m_pad4b5[0x4D4 - 0x4B5];
	AptConnectionScreen *m_connectionGrid; // +0x4D4
};


void AptOnlineCustomMatch::ProcessGameSpyResponses()
{
	HandleBuddyResponses();
	HandlePersistentStorageResponses();

	Int allowedMessages = TheGameSpyInfo->getMaxMessagesPerUpdate();
	PeerResponse resp;
	Bool sawImportantMessage = FALSE;

	while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse(resp))
	{
		AptMessengerOnline::ProcessGameSpyResponse(&resp);
		switch (resp.peerResponseType)
		{
		case PeerResponse::PEERRESPONSE_CREATESTAGINGROOM:
			{
				if (resp.createStagingRoom.result == 0)
				{
					TheGameSpyInfo->markAsStagingRoomHost();
					TheGameSpyGame->rva003FF1A7(m_gameMode);
					TheGameSpyInfo->setGameOptions();
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game)
					{
						game->m_ladderIP = AsciiString(resp.unknown_7c.c_str());
						rva005A20A7();
						if (TheNAT == NULL && TheGameSpyGame->getLocalSlotNum() >= 0)
						{
							TheNAT = (NAT *)new Rva005A734B;
							UnsignedInt localIP = TheGameSpyInfo->getInternalIP();
							UnsignedShort localPort = TheGameSpyInfo->getInternalPort();
							TheGameSpyGame->m_localIPPort = IPPort(localIP, localPort);
							TheNAT->attachSlotList(TheGameSpyGame, TheGameSpyGame->getLocalSlotNum(),
								TheGameSpyGame->m_localIPPort.m_ip, 0, true);
							m_connectionGrid = new AptConnectionScreen(m_owner->m_movie);
							TheNAT->m_listeners.append(this);
						}
					}
				}
				else
				{
					GSMessageBoxOk(TheGameText->fetch("APT:CreateGame"), TheGameText->fetch("GUI:GSFailedToHost"));
					rva005A1EEE();
				}
			}
			break;

		case PeerResponse::PEERRESPONSE_JOINGROUPROOM:
			{
				sawImportantMessage = TRUE;
				PopulateLobbyComboBox();
				if (resp.joinGroupRoom.ok)
				{
					m_prefs.rva0054F7C0(resp.joinGroupRoom.id);
					m_prefs.write();
				}
			}
			break;

		case PeerResponse::PEERRESPONSE_STAGINGROOMLISTCOMPLETE:
			{
				PopulateGamesListBox();
			}
			break;

		case PeerResponse::PEERRESPONSE_JOINSTAGINGROOM:
			{
				sawImportantMessage = TRUE;
				if (m_popUp)
				{
					m_popUp = false;
					void *movie = m_owner->m_movie;
					Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "ClosePassword");
				}
				Bool isHostPresent = TRUE;
				if (resp.joinStagingRoom.ok == TRUE)
				{
					GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
					if (!room)
					{
						isHostPresent = FALSE;
					}
					else
					{
						isHostPresent = FALSE;
						for (Int i = 0; i < MAX_SLOTS; ++i)
						{
							AsciiString hostName;
							hostName.translate(room->getConstSlot(0)->m_name);
							const char *playerName = resp.stagingRoomPlayerNames[i].c_str();
							char name[256] = "";
							CrtIAT::strncpy(name, playerName, 255);
							if (strcmp(hostName.str(), name) == 0)
							{
								isHostPresent = TRUE;
							}
						}
					}
				}
				if (resp.joinStagingRoom.ok == TRUE && isHostPresent)
				{
					GameSpyStagingRoom *joined = TheGameSpyInfo->getCurrentStagingRoom();
					if (joined)
					{
						rva005A20A7();
					}
				}
				else
				{
					UnicodeString s;
					switch (resp.joinStagingRoom.result)
					{
					case 1:
						s = TheGameText->fetch("GUI:JoinFailedRoomFull");
						break;
					case 2:
						s = TheGameText->fetch("GUI:JoinFailedInviteOnly");
						break;
					case 3:
						s = TheGameText->fetch("GUI:JoinFailedBannedFromRoom");
						break;
					case 4:
						s = TheGameText->fetch("GUI:JoinFailedBadPassword");
						break;
					case 5:
						s = TheGameText->fetch("GUI:JoinFailedAlreadyInRoom");
						break;
					case 7:
						s = TheGameText->fetch("GUI:JoinFailedNoConnection");
						break;
					case 9:
						s = TheGameText->fetch("GUI:JoinFailedGameInPlay");
						break;
					default:
						s.format(TheGameText->fetchPtr("GUI:JoinFailedGeneralError"), resp.joinStagingRoom.result);
						break;
					}
					if (m_owner->m_2b0)
						((Rva005170CD *)m_owner)->rva005170CD();
					GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), s);
					rva005A1EEE();
				}
			}
			break;

		case PeerResponse::PEERRESPONSE_FAILEDTOHOST:
			{
				GSMessageBoxOk(TheGameText->fetch("APT:CreateGame"), TheGameText->fetch("GUI:GSFailedToHost"));
				rva005A1EEE();
			}
			break;

		case PeerResponse::PEERRESPONSE_GAMESTART:
			{
				sawImportantMessage = TRUE;
				GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
				if (!myGame || !myGame->isInGame())
					break;
				if (!TheGameSpyGame)
					break;
				SendStatsToOtherPlayers(TheGameSpyGame);
				m_setup.v01();
				myGame->m_seed = resp.gameStart.seed;
				*(Rva00382E73 *)TheGameSpyGame = *(Rva00382E73 *)myGame;
				TheGameSpyGame->startGame(0);
				if (TheGameSpyGame->m_rules[1])
				{
					GameSpyStagingRoom *game = TheGameSpyGame;
					game->m_ff4 = true;
					game->m_ff8 = 3;
				}
				else
				{
					myGame->m_ff4 = false;
					myGame->m_ff8 = 0;
				}
				m_state = 14;
			}
			break;


		case PeerResponse::PEERRESPONSE_PLAYERINFO:
			{
				m_setup.enable();
				TheGameSpyInfo->setGameOptions();
			}
			break;


		case PeerResponse::PEERRESPONSE_PLAYERJOIN:
			{
				if (resp.player.roomType == 1)
					break;
				if (resp.player.roomType != 2)
					break;
				sawImportantMessage = TRUE;
				((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)&resp, AsciiString::TheEmptyString);

				GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
				Bool kicked = FALSE;
				if (TheGameSpyInfo->amIHost() && game)
				{
					if (m_state == 7 || m_state == 8)
					{
						PeerRequest req;
						req.peerRequestType = 13;
						req.isStagingRoom = TRUE;
						req.id = "KICK/";
						req.nick = resp.nick.c_str();
						req.options = "GameStarted";
						TheGameSpyPeerMessageQueue->addRequest(req);
						kicked = TRUE;
					}
					else
					{
						Int numPlayers = 0;
						for (Int player = 0; player < MAX_SLOTS; ++player)
						{
							if (game->getSlot(player)->isOccupied() &&
								game->getSlot(player)->m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
							{
								++numPlayers;
							}
						}

						Int numStartingSpots = MAX_SLOTS;
						const MapMetaData *md = TheMapCache->findMap(game->getMap());
						if (md != NULL)
						{
							numStartingSpots = md->m_numPlayers;
						}

						Int openSlotIndex = -1;
						for (Int i = 0; i < MAX_SLOTS; ++i)
						{
							const GameSlot *slot = game->getConstSlot(i);
							if (slot && slot->isOpen())
							{
								openSlotIndex = i;
								break;
							}
						}

						if (openSlotIndex >= 0)
						{
							GameSlot newSlot;
							UnicodeString uName;
							uName.translate(resp.nick.c_str());
							newSlot.setState(SLOT_PLAYER, uName, &GameSlotConnectInfo());
							newSlot.m_ipPort = IPPort(htonl(resp.player.IP), 8088);
							if (game->m_restoringSave)
							{
								SavedGameSlots *saved = game->m_savedSlots;
								if (saved)
								{
									const SavedSlot *savedSlot = &saved->m_slots[openSlotIndex];
									newSlot.m_color = savedSlot->getColor();
									newSlot.m_startPos = savedSlot->getStartPos();
									newSlot.m_startPos14 = savedSlot->getStartPos();
									newSlot.setPlayerTemplate(savedSlot->getPlayerTemplate());
									newSlot.m_teamNumber = savedSlot->getTeamNumber();
									newSlot.m_handicap = savedSlot->getHandicap();
									newSlot.m_hero[0] = savedSlot->getHero0();
									newSlot.m_hero[1] = savedSlot->getHero1();
									newSlot.m_hero[2] = savedSlot->getHero2();
									((Rva003FF0E7DwordSlot *)&newSlot)->set(savedSlot->getHero3());
									newSlot.m_natBehavior = 1;
								}
							}
							game->setSlot(openSlotIndex, newSlot);
							GameSpyGameSlot *gsSlot = game->getGameSpySlot(openSlotIndex);
							if (gsSlot)
							{
								gsSlot->m_profileID = resp.player.profileID;
							}
							game->resetAccepted();
							TheGameSpyInfo->setGameOptions();
							if (TheNAT)
							{
								TheNAT->processPlayerJoin(openSlotIndex);
							}
						}
						else
						{
							PeerRequest req;
							req.peerRequestType = 13;
							req.isStagingRoom = TRUE;
							req.id = "KICK/";
							req.nick = resp.nick.c_str();
							req.options = "GameFull";
							TheGameSpyPeerMessageQueue->addRequest(req);
							kicked = TRUE;
							TheGameSpyInfo->setGameOptions();
						}
					}
				}
				if (!kicked)
					Rva0059FF9DDo();
			}
		case PeerResponse::PEERRESPONSE_PLAYERCHANGEDFLAGS:
			{
				m_setup.enable();
			}
			break;

		case PeerResponse::PEERRESPONSE_22:
			{
				m_setup.enable();
			}
			break;

		case PeerResponse::PEERRESPONSE_PLAYERLEFT:
			{
				sawImportantMessage = TRUE;
				TheGameSpyInfo->playerLeftGroupRoom(resp.nick.c_str());

				if (TheGameSpyGame && TheGameSpyGame->m_inProgress)
					break;

				if (m_state != 8)
				{
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game)
					{
						Int idx = game->getSlotNum(resp.nick.c_str());
						if (idx >= 0)
						{
							if (TheGameSpyInfo->amIHost())
							{
								game->getSlot(idx)->setState(SLOT_OPEN, UnicodeString::TheEmptyString, &GameSlotConnectInfo());
								game->resetAccepted();
							}
							if (TheNAT)
							{
								TheNAT->processPlayerLeave(idx);
							}
						}
					}

					TheGameSpyInfo->setGameOptions();
					m_setup.enable();

					if (game && !TheGameSpyInfo->amIHost())
					{
						Int idx = game->getSlotNum(resp.nick.c_str());
						if (idx == 0)
						{
							game->reset();
							TheGameSpyInfo->leaveStagingRoom();
							m_setup.v01();
							GSMessageBoxOk(TheGameText->fetch("GUI:HostLeftTitle"), TheGameText->fetch("GUI:HostLeft"));
							rva005A1EEE();
						}
					}
				}
			}
			break;

		case PeerResponse::PEERRESPONSE_DISCONNECT:
			{
				sawImportantMessage = TRUE;
				UnicodeString title, body;
				AsciiString disconMunkee;
				disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
				title = TheGameText->fetch("GUI:GSErrorTitle");
				body = TheGameText->fetch(disconMunkee);
				Rva00548C1ACleanup();
				GSMessageBoxOk(title, body);
				TheGameSpyInfo->reset();
				TheShell->pop();
				TearDownGameSpy();
			}
			break;

		case PeerResponse::PEERRESPONSE_ROOMUTM:
			{
				if (m_state == 14)
					break;
				sawImportantMessage = TRUE;
				if (!strcmp(resp.command.c_str(), "SL"))
				{
					// slotlist
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->find(AsciiString(resp.nick.c_str()));
					AsciiString senderName;
					if (it != TheGameSpyInfo->getPlayerInfoMap()->end())
						senderName = it->second.m_name;
					else
						senderName.set(resp.nick.c_str());
					Bool isValidSlotList = game && game->getSlot(0) && game->getSlot(0)->isPlayer(senderName) && !TheGameSpyInfo->amIHost();
					if (!isValidSlotList)
					{
						if (!game)
						{
						}
						else
						{
							if (!game->getSlot(0))
							{
							}
							else
							{
								if (TheGameSpyInfo->amIHost())
								{
								}
							}
						}
					}
					else
					{
						AsciiString oldMap = game->getMap();
						UnsignedInt oldMapCRC, newMapCRC;
						oldMapCRC = game->getMapCRC();

						AsciiString options = resp.commandOptions.c_str();
						options.trim();
						UnicodeString names[MAX_SLOTS];
						UnsignedShort ports[MAX_SLOTS];
						UnsignedInt ips[MAX_SLOTS];
						Int i;
						for (i = 0; i < MAX_SLOTS; ++i)
						{
							if (game->getConstSlot(i) && game->getConstSlot(i)->isHuman() && game->getConstSlot(i)->getName().getLength() > 0)
							{
								ips[i] = game->getConstSlot(i)->m_ipPort.m_ip;
								ports[i] = game->getConstSlot(i)->m_ipPort.m_port;
								names[i] = game->getConstSlot(i)->m_name;
							}
							else
							{
								ips[i] = 0;
								ports[i] = 0;
							}
						}
						Bool optionsOK = ParseAsciiStringToGameInfo(game, options.str());
						Bool wasInGame = m_localSlot >= 0;
						Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
						m_localSlot = newLocalSlotNum;
						Bool isInGame = newLocalSlotNum >= 0;
						if (!optionsOK)
						{
							break;
						}
						for (i = 0; i < MAX_SLOTS; ++i)
						{
							if (ips[i])
							{
								GameSlot *slot = game->getSlot(i);
								if (slot && slot->isHuman() && slot->m_name.compare(names[i]) == 0)
								{
									slot->m_ipPort = IPPort(ips[i], ports[i]);
								}
							}
						}
						if (!isInGame)
						{
							for (Int i = 0; i < MAX_SLOTS; ++i)
							{
								const GameSpyGameSlot *slot = game->getGameSpySlot(i);
								if (slot && slot->isHuman())
								{
									UnicodeString munkee;
									munkee.format(L"\t%d: %ls", i, slot->m_name.str());
								}
							}
						}
						m_setup.enable();

						// if I changed map availability, send it across
						newMapCRC = game->getMapCRC();
						if (isInGame)
						{
							m_lastSlotlistTime = timeGetTime();
							if ((oldMapCRC ^ newMapCRC) || !wasInGame)
							{
								// it changed.  send it
								UnicodeString hostName = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(0)->m_name;
								AsciiString asciiName;
								asciiName.translate(hostName);
								PeerRequest req;
								req.peerRequestType = 13;
								req.isStagingRoom = TRUE;
								req.id = "MAP";
								req.nick = asciiName.str();
								req.options = (game->getSlot(m_localSlot)->m_hasMap) ? "1" : "0";
								TheGameSpyPeerMessageQueue->addRequest(req);
								if (!game->getSlot(m_localSlot)->m_hasMap)
								{
									UnicodeString text;
									UnicodeString mapDisplayName;
									const MapMetaData *mapData = TheMapCache->findMap(game->getMap());
									Bool willTransfer = TRUE;
									if (mapData)
									{
										mapDisplayName.format(L"%ls", mapData->m_displayName.str());
										willTransfer = !mapData->m_isOfficial;
									}
									else
									{
										mapDisplayName.format(L"%hs", TheGameState->getMapLeafName(game->getMap()).str());
										willTransfer = Rva00300E42Check(game);
									}
									if (willTransfer)
										text.format(TheGameText->fetchPtr("GUI:LocalPlayerNoMapWillTransfer"), mapDisplayName.str());
									else
										text.format(TheGameText->fetchPtr("GUI:LocalPlayerNoMap"), mapDisplayName.str());
									TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT]);
								}
							}
							if (!m_initialAcceptEnable)
							{
								m_initialAcceptEnable = TRUE;
							}
						}
						else
						{
							if (m_lastSlotlistTime && m_lastSlotlistTime < timeGetTime() - 10000)
							{
								// can't see ourselves
								GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
								if (room)
									room->reset();
								TheGameSpyInfo->leaveStagingRoom();
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSKicked"));
								m_setup.v01();
								rva005A1EEE();
							}
						}
					}
				}
				else if (!strcmp(resp.command.c_str(), "PN"))
				{
					// player names
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					AsciiString senderName;
					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->find(AsciiString(resp.nick.c_str()));
					if (it != TheGameSpyInfo->getPlayerInfoMap()->end())
						senderName = it->second.m_name;
					else
						senderName.set(resp.nick.c_str());
					Bool valid = game && game->getSlot(0) && game->getSlot(0)->isPlayer(senderName) && !TheGameSpyInfo->amIHost();
					if (!valid)
						break;
					Int slotNum = -1;
					AsciiString options = resp.commandOptions.c_str();
					AsciiString token;
					AsciiString name;
					while (options.nextToken(&token, ",=") && options.nextToken(&name, ",="))
					{
						if (CrtIAT::sscanf(token.str(), "%d", &slotNum) != 1)
							break;
						if (slotNum >= 0 && slotNum < MAX_SLOTS)
						{
							GameSlot *slot = game->getSlot(slotNum);
							if (slot && !name.isEmpty())
							{
								UnicodeString uName(MultiByteToWideCharSingleLine(name.str()).c_str());
								slot->m_name = uName;
							}
						}
					}
				}
				else if (!strcmp(resp.command.c_str(), "HWS"))
				{
					// host wants to start
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game && game->isInGame() && game->getSlot(0) && game->getSlot(0)->isPlayer(resp.nick.c_str()))
					{
						GameSlot *slot = game->getSlot(game->getLocalSlotNum());
						if (slot && !slot->m_isAccepted)
						{
							TheGameSpyInfo->addText(TheGameText->fetch("GUI:HostWantsToStart"), GameSpyColor[GSCOLOR_DEFAULT]);
						}
					}
				}
				else if (!strcmp(resp.command.c_str(), "DUI"))
				{
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game && game->isInGame() && !game->v12() && game->getSlot(0) && game->getSlot(0)->isPlayer(resp.nick.c_str()))
					{
						m_setup.rva0043DBA3();
					}
				}
				else if (!strcmp(resp.command.c_str(), "EUI"))
				{
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game && game->isInGame() && !game->v12() && game->getSlot(0) && game->getSlot(0)->isPlayer(resp.nick.c_str()))
					{
						m_setup.rva0043DC0F();
					}
				}
				else if (!CrtIAT::_strcmpi(resp.command.c_str(), "NAT"))
				{
					if (TheNAT != NULL)
					{
						TheNAT->processGlobalMessage(-1, resp.commandOptions.c_str());
					}
				}
				else if (!CrtIAT::_strcmpi(resp.command.c_str(), "Pings"))
				{
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game && !TheGameSpyInfo->amIHost())
					{
						AsciiString pings = resp.commandOptions.c_str();
						AsciiString token;
						for (Int i = 0; i < MAX_SLOTS; ++i)
						{
							GameSpyGameSlot *slot = game->getGameSpySlot(i);
							if (pings.nextToken(&token, ","))
							{
								token.trim();
								((Rva004FDB04 *)slot)->rva004FDB04(token);
							}
							else
							{
								((Rva004FDB04 *)slot)->rva004FDB04("");
							}
						}
					}
				}
				else if (!CrtIAT::_strcmpi(resp.command.c_str(), "PIDS"))
				{
					GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
					if (game)
					{
						if (!TheGameSpyInfo->amIHost())
						{
							AsciiString pids = resp.commandOptions.c_str();
							AsciiString token;
							for (Int i = 0; i < MAX_SLOTS; ++i)
							{
								GameSpyGameSlot *slot = game->getGameSpySlot(i);
								if (pids.nextToken(&token, ","))
								{
									token.trim();
									char buf[32] = "0x";
									_mbscat((unsigned char *)buf, (const unsigned char *)token.str());
									Int profileID = 0;
									CrtIAT::sscanf(buf, "%x", &profileID);
									slot->m_profileID = profileID;
								}
								else
								{
									slot->m_profileID = 0;
								}
								if (pids.nextToken(&token, ","))
								{
									token.trim();
									slot->rva003FF5F2(token);
								}
								else
								{
									slot->rva003FF5F2(AsciiString::TheEmptyString);
								}
							}
						}
						m_setup.enableByte();
					}
				}
			}
			break;

		case PeerResponse::PEERRESPONSE_PLAYERUTM:
			{
				sawImportantMessage = TRUE;
				if (!strcmp(resp.command.c_str(), "STATS"))
				{
					PSPlayerAllStats stats(0);
					if (stats.getID() && TheGameSpyPSMessageQueue->findPlayerStatsByID(stats.getID()).getID() == 0)
						TheGameSpyPSMessageQueue->trackPlayerStats(stats);
					break;
				}
				GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
				if (game)
				{
					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->find(AsciiString(resp.nick.c_str()));
					AsciiString senderName;
					if (it != TheGameSpyInfo->getPlayerInfoMap()->end())
						senderName = it->second.m_name;
					else
						senderName.set(resp.nick.c_str());
					Int slotNum = game->getSlotNum(senderName);
					if ((slotNum >= 0) && (slotNum < MAX_SLOTS) && (!CrtIAT::_strcmpi(resp.command.c_str(), "NAT")))
					{
						// this is a command for NAT negotiations, pass if off to TheNAT
						if (TheNAT != NULL)
						{
							TheNAT->processGlobalMessage(slotNum, resp.commandOptions.c_str());
						}
					}
					if (slotNum <= 0 && !TheGameSpyInfo->amIHost())
					{
						if (!strcmp(resp.command.c_str(), "KICK"))
						{
							// oops - we've been kicked.  bail.
							GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
							if (room)
								room->reset();
							TheGameSpyInfo->leaveStagingRoom();
							UnicodeString message = TheGameText->fetch("GUI:GSKicked");
							AsciiString commandMessage = resp.commandOptions.c_str();
							commandMessage.trim();
							if (commandMessage.compare("GameStarted") == 0)
							{
								message = TheGameText->fetch("GUI:GSKickedGameStarted");
							}
							else if (commandMessage.compare("GameFull") == 0)
							{
								message = TheGameText->fetch("GUI:GSKickedGameFull");
							}
							GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), message);
							m_setup.v01();
							rva005A1EEE();
						}
					}
					else if (slotNum > 0 && TheGameSpyInfo->amIHost())
					{
						if (!strcmp(resp.command.c_str(), "READY"))
						{
							game->getSlot(slotNum)->m_isAccepted = true;
							TheGameSpyInfo->setGameOptions();
							m_setup.enable();
						}
						else if (!strcmp(resp.command.c_str(), "UNREADY"))
						{
							game->getSlot(slotNum)->unAccept();
							TheGameSpyInfo->setGameOptions();
							m_setup.enable();
						}
						else if (!strcmp(resp.command.c_str(), "MAP"))
						{
							Bool hasMap = CrtIAT::atoi(resp.commandOptions.c_str()) != 0;
							game->getSlot(slotNum)->setMapAvailability(hasMap);
							if (!hasMap)
							{
								// tell the host the user doesn't have the map
								UnicodeString mapDisplayName;
								const MapMetaData *mapData = TheMapCache->findMap(game->getMap());
								Bool willTransfer = Rva00300E42Check(game);
								if (mapData)
								{
									mapDisplayName.format(L"%ls", const_cast<MapMetaData *>(mapData)->bfme_getDisplayName(true).str());
								}
								else
								{
									mapDisplayName.format(L"%hs", game->getMap().str());
								}
								UnicodeString text;
								if (willTransfer)
									text.format(TheGameText->fetchPtr("GUI:PlayerNoMapWillTransfer"), game->getSlot(slotNum)->getName().str(), mapDisplayName.str());
								else
									text.format(TheGameText->fetchPtr("GUI:PlayerNoMap"), game->getSlot(slotNum)->getName().str(), mapDisplayName.str());
								TheGameSpyInfo->addText(text, GameSpyColor[GSCOLOR_DEFAULT]);
							}
							m_setup.enable();
						}
						else if (!strcmp(resp.command.c_str(), "REQ"))
						{
							AsciiString options = resp.commandOptions.c_str();
							options.trim();

							Bool change = false;
							Bool shouldUnaccept = false;
							AsciiString key;
							options.nextToken(&key, "=");
							Int val = CrtIAT::atoi(options.str() + 1);
							UnsignedInt uVal = CrtIAT::atoi(options.str() + 1);

							GameSpyGameSlot *slot = game->getGameSpySlot(slotNum);
							if (!slot)
								break;

							if (key.compare("Color") == 0)
							{
								if (val >= -1 && val < TheMultiplayerSettings->getNumColors() && val != slot->getColor() && slot->m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
								{
									slot->m_color = val;
									change = true;
								}
							}
							else if (key.compare("PlayerTemplate") == 0)
							{
								if (val >= PLAYERTEMPLATE_OBSERVER && val < ThePlayerTemplateStore->getPlayerTemplateCount() && val != slot->m_playerTemplate)
								{
									slot->setPlayerTemplate(val);
									if (val == PLAYERTEMPLATE_OBSERVER)
									{
										slot->m_color = -1;
										slot->m_handicap = 0;
										slot->m_startPos = -1;
										slot->m_startPos14 = -1;
										slot->m_teamNumber = -1;
									}
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("StartPos") == 0)
							{
								if (val >= -1 && val != slot->getStartPos() && slot->m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
								{
									Bool startPosAvailable = TRUE;
									if (val != -1)
									{
										for (Int i = 0; i < MAX_SLOTS; i++)
										{
											GameSlot *checkSlot = game->getSlot(i);
											if (val == checkSlot->getStartPos() && slot != checkSlot)
											{
												startPosAvailable = FALSE;
												break;
											}
										}
										if (startPosAvailable && g_Va00E0333C)
											startPosAvailable = ((AptMpGameSetup *)g_Va00E0333C)->rva0043DCFA(val);
									}
									if (startPosAvailable)
									{
										slot->m_startPos = val;
										slot->m_startPos14 = val;
									}
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("Team") == 0)
							{
								if (val >= -1 && val < MAX_SLOTS / 2 && val != slot->getTeamNumber() && slot->m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
								{
									slot->m_teamNumber = val;
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("clanID") == 0)
							{
								if (((const Rva003821B9AsciiField *)slot)->get().compare(options.str() + 1) != 0 && slot->m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
								{
									slot->rva003FF5F2(AsciiString(options.str() + 1));
									m_setup.enableByte();
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("Hero") == 0)
							{
								if (slot->m_playerTemplate == PLAYERTEMPLATE_OBSERVER && val != 0)
									val = 0;
								Int hero0 = slot->m_hero[0];
								Int hero1 = slot->m_hero[1];
								Int hero2 = slot->m_hero[2];
								Int hero3 = slot->m_hero[3];
								slot->decodeHero(val);
								if (hero0 != slot->m_hero[0] || hero1 != slot->m_hero[1] || hero2 != slot->m_hero[2] || hero3 != slot->m_hero[3])
								{
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("Handicap") == 0)
							{
								if (val <= 0 && val >= -100 && val % 5 == 0)
								{
									slot->m_handicap = val;
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("IP") == 0)
							{
								if (uVal != slot->m_ipPort.m_ip)
								{
									slot->setIP(uVal);
									change = true;
									shouldUnaccept = true;
								}
							}
							else if (key.compare("NAT") == 0)
							{
								if (val >= 0 && val <= 0x100)
								{
									slot->m_natBehavior = val;
									change = true;
								}
							}
							else if (key.compare("Ping") == 0)
							{
								((Rva004FDB04 *)slot)->rva004FDB04(options.str() + 1);
								TheGameSpyInfo->setGameOptions();
							}
							else if (key.compare("LadderRank_1v1") == 0)
							{
								slot->m_ladderRank1v1 = CrtIAT::atoi(options.str());
								TheGameSpyInfo->setGameOptions();
							}
							else if (key.compare("LadderRank_2v2") == 0)
							{
								slot->m_ladderRank2v2 = CrtIAT::atoi(options.str());
								TheGameSpyInfo->setGameOptions();
							}

							if (change)
							{
								if (shouldUnaccept)
									game->resetAccepted();
								TheGameSpyInfo->setGameOptions();
								m_setup.enable();
							}
						}
					}
				}
			}
			break;
		}
	}
}
