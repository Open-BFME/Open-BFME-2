// ?setGameOptions@GameSpyInfo@@UAEXXZ
// partial score=0.85 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: GameSpyInfo methods in PeerDefs.cpp (reconciled from Zero Hour's
// GameNetwork/GameSpy/PeerDefs.cpp and PeerDefsImplementation.h).

#include <utility>
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(T) T()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>
#include <string>
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"
#include "unicode_string.h"

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva0038404A { public: void rva00384E8E(void); };
class Rva00383AFF { public: void rva00383AFF(void); };
class Rva00383A28 { public: void rva00383A28(void); };
class Rva00072FE6 { public: void rva00072FE6(void); };
class PSPlayerAllStats { public: void rva00552CB8(void); };

class GameWindow;

// Retail spells the 0x20-byte group-room record's out-of-line copy ctor
// (0x00382444) and dtor (0x0038240F) as AsciiUnicodePair; ZH's
// GameSpyGroupRoom fields plus BFME 2's trailing room type.
struct AsciiUnicodePair
{
	AsciiString m_name;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
	Int m_roomType;
	AsciiUnicodePair(const AsciiUnicodePair &other);
};

class GameSpyGroupRoom : public AsciiUnicodePair
{
public:
	GameSpyGroupRoom();		// 0x0038226B
	GameSpyGroupRoom &operator=(const GameSpyGroupRoom &other);	// 0x00381E56
};
class BuddyInfo {};

// ZH's PeerRequest (PeerThread.h) as BFME 2 lays it out: 492 bytes, its
// ctor 0x001EF661 and dtor 0x001EF723 rowed under this name. BFME 2 adds ten
// words at +0xD0 and a string at +0xF8 ahead of qmMaps; setGameOptions fills
// six per-slot arrays and two trailing words of gameOptions.
struct BfmeOpaqueOwnedRecord492
{
	enum
	{
		PEERREQUEST_JOINGROUPROOM = 4,
		PEERREQUEST_LEAVEGROUPROOM = 5,
		PEERREQUEST_LEAVEGROUPROOMONLY = 6,
		PEERREQUEST_SETGAMEOPTIONS = 10,
		PEERREQUEST_LEAVESTAGINGROOM = 12,
		PEERREQUEST_UTMROOM = 14,
		PEERREQUEST_UTMSTAGINGPN = 24
	};
	Int peerRequestType;					// +0x00
	_STL::string nick;						// +0x04
	_STL::wstring text;						// +0x10
	_STL::string password;					// +0x1C
	_STL::string email;						// +0x28
	_STL::string id;						// +0x34
	_STL::string options;					// +0x40
	_STL::string ladderIP;					// +0x4C
	_STL::string hostPingStr;				// +0x58
	_STL::string gameOptsMapName;			// +0x64
	_STL::string gameOptsPlayerNames[8];	// +0x70
	UnsignedInt gameOptsUnknownD0[10];		// +0xD0: the staging room's +0x60 words
	_STL::string unknownF8;					// +0xF8
	_STL::vector<Bool> qmMaps;				// +0x104
	union									// +0x118
	{
		struct
		{
			Int id;
		} groupRoom;

		struct
		{
			Bool isStagingRoom;
		} UTM;

		// Per slot index: wins, losses, profile ID (the AI state for AI
		// slots), player template, color and the slot's +0x20 word.
		struct
		{
			Int wins[8];
			Int losses[8];
			Int profileID[8];
			Int faction[8];
			Int color[8];
			Int slotValue20[8];
			Int numPlayers;
			Int maxPlayers;
			Int numObservers;
			Int valueCC;			// the staging room's +0x5C
			Int valueD0;			// the staging room's +0x58
		} gameOptions;
	};
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
};
typedef BfmeOpaqueOwnedRecord492 PeerRequest;
typedef char PeerRequestSizeCheck[sizeof(PeerRequest) == 492 ? 1 : -1];
typedef char PeerRequestUnionCheck[offsetof(PeerRequest, gameOptions) == 0x118 ? 1 : -1];

// BFME 2's slot states add a fourth AI difficulty ahead of SLOT_PLAYER.
enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_AI_5,
	SLOT_PLAYER
};

enum { PLAYERTEMPLATE_OBSERVER = -2 };
enum { MAX_SLOTS = 8 };

// GameSlot (0x1AC bytes) as setGameOptions reads it; the state predicates
// are rowed out of line.
class GameSlot
{
public:
	Bool isHuman(void) const;
	Bool isOccupied(void) const;
	Bool isAI(void) const;
	Bool isOpen(void) const;
	SlotState getState(void) const { return (SlotState)m_state; }
	Int getColor(void) const { return m_color; }
	Int getPlayerTemplate(void) const { return m_playerTemplate; }
	const UnicodeString &getName(void) const { return m_name; }

	unsigned char m_pad00[0x04];
	Int m_state;						// +0x04
	unsigned char m_pad08[0x04];
	Int m_color;						// +0x0C
	unsigned char m_pad10[0x08];
	Int m_playerTemplate;				// +0x18
	Int m_teamNumber;					// +0x1C
	Int m_20;							// +0x20
	unsigned char m_pad24[0x0C];
	UnicodeString m_name;				// +0x30
	unsigned char m_pad34[0x1A8 - 0x34];
	AsciiString m_1A8;					// +0x1A8
};

// GameSpyGameSlot extends GameSlot with ZH's profile ID, login, locale and
// ping string (+0x1B8).
class GameSpyGameSlot : public GameSlot
{
public:
	Int getProfileID(void) const { return m_profileID; }

	Int m_profileID;					// +0x1AC
};

// The slot's +0x1A8 and +0x1B8 (ZH getPingString) getters, rowed as
// AsciiString RVO getters under address names.
class Rva003821B9AsciiField
{
public:
	AsciiString get() const;
};
class Rva00382216AsciiField
{
public:
	AsciiString get() const;
};

// GameInfo, the staging room's base, as setGameOptions reads it.
class GameInfo
{
public:
	AsciiString getMap(void) const;
	const GameSlot *getConstSlot(Int index) const;

	unsigned char m_pad00[0x58];
	Int m_58;							// +0x58
	Int m_5c;							// +0x5C
	UnsignedInt m_60[10];				// +0x60
};

AsciiString GameInfoToAsciiString(const GameInfo *game, Bool flag);
_STL::string WideCharStringToMultiByte(const unsigned short *orig);

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
};

extern GameState *TheGameState;

// 0x1020-byte staging-room record (GameInfo base at +0; ctor 0x004FDE4D,
// copy ctor 0x003835F4, dtor 0x00382C4A).
class GameSpyStagingRoom
{
public:
	GameSpyStagingRoom();
	GameSpyStagingRoom(const GameSpyStagingRoom &other);
	virtual ~GameSpyStagingRoom();
	virtual void s01(void);
	virtual void s02(void);
	virtual void s03(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void s06(void);
	virtual void s07(void);
	virtual void s08(void);
	virtual void s09(void);
	virtual void reset(void);
	static void operator delete(void *p) { ::operator delete(p); }
	void cleanUpSlotPointers(void);
	Int getID(void) const { return m_id; }
	GameSpyGameSlot *getGameSpySlot(Int index);
	unsigned char m_pad0004[0xC8];		// +0x04..+0xCB
	unsigned char m_digest[16];			// +0xCC..+0xDB
	unsigned char m_pad00DC[0xF04];		// +0xDC..+0xFDF
	Int m_id;							// +0xFE0
	unsigned char m_pad0FE4[0x3C];		// +0xFE4..+0x101F
};

extern GameSpyStagingRoom *TheGameSpyGame;

// GameInfo assignment (0x00382E73) and cleanUpSlotPointers (0x004FDA17),
// rowed under their address names.
class Rva00382E73 { public: Rva00382E73 &operator=(const Rva00382E73 &other); };

struct TreeHintOpaque0043671B;
extern "C" void MD5Print(unsigned char digest[16], char output[33]);
TreeHintOpaque0043671B *Rva004360B3(AsciiString key);

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
	Int m_preorder;		// +0x30: updatePlayerInfo marks the profile when set
	~PlayerInfo();
	Bool isIgnored(void);
};

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

typedef _STL::set<AsciiString> IgnoreList;
typedef _STL::map<Int, AsciiString> SavedIgnoreMap;
typedef _STL::map<Int, GameSpyGroupRoom> GroupRoomMap;
typedef _STL::map<Int, GameSpyStagingRoom *> StagingRoomMap;
typedef _STL::map<Int, BuddyInfo> BuddyInfoMap;
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();
	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);
	void rva003B2322(const AsciiString &val, Int num, Bool flag);
protected:
	UnicodeString m_filename;
};

class IgnorePreferences : public UserPreferences
{
public:
	IgnorePreferences();
	virtual ~IgnorePreferences();
	SavedIgnoreMap getIgnores(void);
};

extern Int GetAdditionalDisconnectsFromUserFile(Int playerID);

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void s01(void);
	virtual void endThread(void);
	virtual void s03(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void addRequest(const PeerRequest &req);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class GameSpyInfoInterface
{
public:
	virtual ~GameSpyInfoInterface();
	virtual void s01(void);
	virtual void s02(void);
	virtual GroupRoomMap *getGroupRoomList(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void s06(void);
	virtual void s07(void);
	virtual void s08(void);
	virtual void s09(void);
	virtual void s0A(void);
	virtual void s0B(void);
	virtual void s0C(void);
	virtual void s0D(void);
	virtual void s0E(void);
	virtual void s0F(void);
	virtual void s10(void);
	virtual void s11(void);
	virtual void s12(void);
	virtual void s13(void);
	virtual void s14(void);
	virtual void s15(void);
	virtual void s16(void);
	virtual void s17(void);
	virtual void s18(void);
	virtual void s19(void);
	virtual void s1A(void);
	virtual void s1B(void);
	virtual void s1C(void);
	virtual void s1D(void);
	virtual void s1E(void);
	virtual Int getLocalProfileID(void);
	virtual void s20(void);
	virtual void s21(void);
	virtual void s22(void);
	virtual void s23(void);
	virtual void s24(void);
	virtual void s25(void);
	virtual void s26(void);
	virtual void s27(void);
	virtual void s28(void);
	virtual void s29(void);
	virtual void s2A(void);
	virtual void s2B(void);
	virtual void s2C(void);
	virtual void s2D(void);
	virtual void s2E(void);
	virtual void s2F(void);
	virtual void s30(void);
	virtual void s31(void);
	virtual void s32(void);
	virtual void s33(void);
	virtual void s34(void);
	virtual void s35(void);
	virtual void s36(void);
	virtual void s37(void);
	virtual void s38(void);
	virtual void s39(void);
	virtual void s3A(void);
	virtual void s3B(void);
	virtual void s3C(void);
	virtual void s3D(void);
	virtual void s3E(void);
	virtual void s3F(void);
	virtual void s40(void);
	virtual void s41(void);
	virtual void s42(void);
	virtual void s43(void);
	virtual void s44(void);
	virtual void s45(void);
	virtual void s46(void);
	virtual void s47(void);
	virtual void s48(void);
	virtual void s49(void);
	virtual void s4A(void);
	virtual void s4B(void);
	virtual void s4C(void);
	virtual Bool isSavedIgnored(Int profileID);
	virtual void s4E(void);
	virtual void s4F(void);
	virtual void s50(void);
	virtual void s51(void);
	virtual void s52(void);
	virtual Bool isIgnored(AsciiString nick);
	virtual void setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP);
	virtual UnsignedInt getInternalIP(void);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class GameTextInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	// MSVC assigns same-name virtual overloads in reverse declaration order:
	// fetch(const AsciiString &) lands at 0x38, fetch(const char *) at 0x3C.
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface();
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual Int getQMChannel(void) = 0;
	virtual void setQMChannel(Int channel) = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

// CustomPref<id>.ini preferences for a game mode (0 Rts, 1 Strat); the lobby
// room getter is spelled on its GameModePreferences base.
class Rva0054F508
{
public:
	Rva0054F508(Int mode);
	virtual ~Rva0054F508();
private:
	unsigned char m_body[0x18];
};

class GameModePreferences
{
public:
	Int rva0054F5A4(void);
};

// Retail calls _strcmpi through its msvcr71 import slot (0x00BBA518); the
// CRT headers here declare it without dllimport.
extern "C" int (__cdecl * const _imp___strcmpi)(const char *, const char *);

// Lobby room IDs recorded by addGroupRoom from the GUI:LobbyRoom<n> labels.
extern Int g_lobbyRoom2ID;		// 0x00E02328
extern Int g_lobbyRoom9ID;		// 0x00E0232C
extern Int g_lobbyRoom1ID;		// 0x00E02330
extern Int g_lobbyRoom6ID;		// 0x00E02334
extern Int g_lobbyRoom1IDAlt;	// 0x00E02338

typedef void (*GameWinMsgBoxFunc)(void);
void GSMessageBoxOk(UnicodeString title, UnicodeString message, GameWinMsgBoxFunc okFunc = 0);

// PSPlayerStats (0x548 bytes, profile id first); its dtor 0x00385371 is rowed
// under the address name.
struct Gen_uw_00385371
{
	Int id;
	unsigned char m_body[0x544];
	~Gen_uw_00385371();
};
typedef Gen_uw_00385371 PSPlayerStats;

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void s01(void);
	virtual void endThread(void);
	virtual void s03(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void s06(void);
	virtual void s07(void);
	virtual void s08(void);
	virtual void s09(void);
	virtual void s0A(void);
	virtual void s0B(void);
	virtual PSPlayerStats findPlayerStatsByID(Int id);
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void s01(void);
	virtual void endThread(void);
};

class PingerInterface
{
public:
	virtual ~PingerInterface();
	virtual void s01(void);
	virtual void endThreads(void);
};

// LadderList: non-virtual dtor rowed at 0x0054D974.
class Rva0054D974 { public: ~Rva0054D974(); };

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;	// 0x00E05FC8
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;	// 0x00E05FBC
extern PingerInterface *ThePinger;		// 0x00E05FB8
extern Rva0054D974 *TheLadderList;		// 0x00E05FB0

// Unrowed 0x00556FB8: writes the stats' key/value pairs into
// GameSpyMiscPreferences' cached stats (ZH inlines this in TearDownGameSpy).
void Rva00556FB8(const PSPlayerStats &stats);
void Rva003B3371Call(Int hook);		// SignalUIInteraction
void Rva00415EF8Close(void);		// deleteNotificationBox

class GameSpyInfo
{
public:
	// Virtual slots follow the retail vtable at 0x00C1DD90 so that virtual
	// self-calls encode the right slot offsets; unnamed slots are placeholders.
	virtual ~GameSpyInfo();
	virtual void reset(void);
	virtual void clearGroupRoomList(void);
	virtual GroupRoomMap *getGroupRoomList(void);
	virtual void addGroupRoom(GameSpyGroupRoom room);
	virtual void slot05(void);
	virtual void joinGroupRoom(Int groupID);
	virtual void leaveGroupRoom(void);
	virtual void rva003854C5(void);
	virtual void joinBestGroupRoom(Int roomType);
	virtual void joinPreferredGroupRoom(Bool unusedFlag, Int roomType);
	virtual void setCurrentGroupRoom(Int groupID);
	virtual Int getCurrentGroupRoom(void);
	virtual void rva00386139(AsciiString value);
	virtual AsciiString rva0038616D(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void rva003674FE(Int value);
	virtual void slot18(void);
	virtual void updatePlayerInfo(PlayerInfo pi, AsciiString oldNick);
	virtual void playerLeftGroupRoom(AsciiString nick);
	virtual void slot21(void);
	virtual PlayerInfo *rva00382CCE(const char *key);
	virtual PlayerInfo *rva00382D0A(Int profileID);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual Bool isBuddy(Int id);
	virtual void setLocalName(AsciiString name);
	virtual AsciiString getLocalName(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual AsciiString getLocalEmail(void);
	virtual void setLocalEmail(AsciiString email);
	virtual AsciiString getLocalPassword(void);
	virtual void setLocalPassword(AsciiString passwd);
	virtual void setLocalBaseName(AsciiString name);
	virtual AsciiString getLocalBaseName(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void clearStagingRoomList(void);
	virtual void slot41(void);
	virtual GameSpyStagingRoom *findStagingRoomByID(Int id);
	virtual void addStagingRoom(GameSpyStagingRoom room);
	virtual void updateStagingRoom(GameSpyStagingRoom room);
	virtual void removeStagingRoom(GameSpyStagingRoom room);
	virtual Bool hasStagingRoomListChanged(void);
	virtual void leaveStagingRoom(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual Bool rva00381DC4(void);
	virtual GameSpyStagingRoom *getCurrentStagingRoom(void);
	virtual Bool validateStagingRoom(GameSpyStagingRoom *room);
	virtual void setGameOptions(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual void slot65(void);
	virtual void setMOTD(const AsciiString &motd);
	virtual void slot67(void);
	virtual void slot68(void);
	virtual void slot69(void);
	virtual void setPingString(const AsciiString &ping);
	virtual void slot71(void);
	virtual void slot72(void);
	virtual void slot73(void);
	virtual void slot74(void);
	virtual void addToSavedIgnoreList(Int profileID, AsciiString nick);
	virtual void removeFromSavedIgnoreList(Int profileID);
	virtual Bool isSavedIgnored(Int profileID);
	virtual void slot78(void);
	virtual void loadSavedIgnoreList(void);
	virtual IgnoreList returnIgnoreList(void);
	virtual void addToIgnoreList(AsciiString nick);
	virtual void removeFromIgnoreList(AsciiString nick);
	virtual Bool isIgnored(AsciiString nick);
	virtual void setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP);
	virtual void slot85(void);
	virtual unsigned short rva003860FF(void);
	virtual void slot87(void);
	virtual Bool isDisconnectedAfterGameStart(Int *reason) const;
	virtual void markAsDisconnectedAfterGameStart(Int reason);
	virtual Bool didPlayerPreorder(Int profileID) const;
	virtual void markPlayerAsPreorder(Int profileID);
	virtual void slot92(void);
	virtual void slot93(void);
	virtual void slot94(void);
	virtual void slot95(void);
	virtual void readAdditionalDisconnects(void);
	virtual void slot97(void);
	virtual void slot98(void);

private:
	Bool m_sawFullGameList;				// +0x04
	Bool m_isDisconAfterGameStart;		// +0x05
	unsigned char m_pad0006[2];			// +0x06..+0x07
	Int m_disconReason;					// +0x08
	AsciiString m_rawMotd;				// +0x0C
	AsciiString m_rawConfig;			// +0x10
	AsciiString m_pingString;			// +0x14
	GroupRoomMap m_groupRooms;			// +0x18..+0x23
	StagingRoomMap m_stagingRooms;		// +0x24..+0x2F
	Bool m_stagingRoomsDirty;			// +0x30
	unsigned char m_pad0031[3];			// +0x31..+0x33
	BuddyInfoMap m_buddyMap;			// +0x34..+0x3F
	BuddyInfoMap m_buddyRequestMap;		// +0x40..+0x4B
	PlayerInfoMap m_playerInfoMap;		// +0x4C..+0x57
	void *m_buddyMessages;				// +0x58
	Int m_currentGroupRoomID;			// +0x5C
	AsciiString m_unk0060;				// +0x60
	Int m_unk0064;						// +0x64
	Int m_unk0068;						// +0x68
	Bool m_gotGroupRoomList;			// +0x6C
	unsigned char m_pad006D[3];			// +0x6D..+0x6F
	AsciiString m_localName;			// +0x70
	Int m_localProfileID;				// +0x74
	AsciiString m_localPasswd;			// +0x78
	AsciiString m_localEmail;			// +0x7C
	AsciiString m_localBaseName;		// +0x80
	unsigned char m_cachedLocalPlayerStats[0x548]; // +0x84..+0x5CB
	Bool m_disallowAsainText;			// +0x5CC
	Bool m_disallowNonAsianText;		// +0x5CD
	unsigned char m_pad05CE[2];			// +0x5CE..+0x5CF
	UnsignedInt m_internalIP;			// +0x5D0
	UnsignedInt m_externalIP;			// +0x5D4
	Int m_maxMessagesPerUpdate;			// +0x5D8
	Int m_joinedStagingRoom;			// +0x5DC
	Bool m_isHosting;					// +0x5E0
	unsigned char m_pad05E1[3];			// +0x5E1..+0x5E3
	unsigned char m_localStagingRoom[0x1020]; // +0x5E4..+0x1603
	Int m_localStagingRoomID;			// +0x1604
	IgnoreList m_ignoreList;			// +0x1608..+0x1613
	SavedIgnoreMap m_savedIgnoreMap;	// +0x1614..+0x161F
	_STL::set<GameWindow *> m_textWindows; // +0x1620..+0x162B
	_STL::set<Int> m_preorderPlayers;	// +0x162C..+0x1637
	Int m_additionalDisconnects;		// +0x1638
	Bool m_unk163C;						// +0x163C
};

// ?didPlayerPreorder@GameSpyInfo@@UBE_NH@Z @0x00383580 32B
Bool GameSpyInfo::didPlayerPreorder(Int profileID) const
{
	_STL::set<Int>::const_iterator it = m_preorderPlayers.find(profileID);
	return (it != m_preorderPlayers.end());
}

// ?markPlayerAsPreorder@GameSpyInfo@@UAEXH@Z @0x00383E80 28B
void GameSpyInfo::markPlayerAsPreorder(Int profileID)
{
	m_preorderPlayers.insert(profileID);
}

// ?setLocalIPs@GameSpyInfo@@UAEXII@Z @0x00381D9E 23B
void GameSpyInfo::setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP)
{
	m_internalIP = internalIP;
	m_externalIP = externalIP;
}

// ?rva00381DC4@GameSpyInfo@@UAE_NXZ @0x00381DC4 22B
Bool GameSpyInfo::rva00381DC4(void)
{
	return m_isHosting || m_joinedStagingRoom;
}

// ?hasStagingRoomListChanged@GameSpyInfo@@UAE_NXZ @0x00381DDA 8B
Bool GameSpyInfo::hasStagingRoomListChanged(void)
{
	Bool val = m_stagingRoomsDirty;
	m_stagingRoomsDirty = false;
	return val;
}

// ?setMOTD@GameSpyInfo@@UAEXABVAsciiString@@@Z @0x0038200D 8B
void GameSpyInfo::setMOTD(const AsciiString &motd)
{
	m_rawMotd = motd;
}

// ?addToIgnoreList@GameSpyInfo@@UAEXVAsciiString@@@Z @0x003846A8 61B
void GameSpyInfo::addToIgnoreList(AsciiString nick)
{
	m_ignoreList.insert(nick);
}

// ?removeFromIgnoreList@GameSpyInfo@@UAEXVAsciiString@@@Z @0x003871BF 55B
void GameSpyInfo::removeFromIgnoreList(AsciiString nick)
{
	m_ignoreList.erase(nick);
}

// ?isIgnored@GameSpyInfo@@UAE_NVAsciiString@@@Z @0x003846E5 41B
Bool GameSpyInfo::isIgnored(AsciiString nick)
{
	return m_ignoreList.find(nick) != m_ignoreList.end();
}

// ?returnIgnoreList@GameSpyInfo@@UAE?AV?$set@VAsciiString@@U?$less@VAsciiString@@@_STL@@V?$allocator@VAsciiString@@@3@@_STL@@XZ @0x00385AFE 30B
IgnoreList GameSpyInfo::returnIgnoreList(void)
{
	return m_ignoreList;
}

// ?isDisconnectedAfterGameStart@GameSpyInfo@@UBE_NPAH@Z @0x00386104 19B
Bool GameSpyInfo::isDisconnectedAfterGameStart(Int *reason) const
{
	if (reason != 0)
		*reason = m_disconReason;
	return m_isDisconAfterGameStart;
}

// ?markAsDisconnectedAfterGameStart@GameSpyInfo@@UAEXH@Z @0x00386117 14B
void GameSpyInfo::markAsDisconnectedAfterGameStart(Int reason)
{
	m_isDisconAfterGameStart = true;
	m_disconReason = reason;
}

// ?setLocalName@GameSpyInfo@@UAEXVAsciiString@@@Z @0x00386188 52B
void GameSpyInfo::setLocalName(AsciiString name)
{
	m_localName = name;
}

// ?getLocalName@GameSpyInfo@@UAE?AVAsciiString@@XZ @0x003861BC 27B
AsciiString GameSpyInfo::getLocalName(void)
{
	return m_localName;
}

// ?getLocalEmail@GameSpyInfo@@UAE?AVAsciiString@@XZ @0x003861D7 27B
AsciiString GameSpyInfo::getLocalEmail(void)
{
	return m_localEmail;
}

// ?setLocalEmail@GameSpyInfo@@UAEXVAsciiString@@@Z @0x003861F2 52B
void GameSpyInfo::setLocalEmail(AsciiString email)
{
	m_localEmail = email;
}

// ?getLocalPassword@GameSpyInfo@@UAE?AVAsciiString@@XZ @0x00386226 27B
AsciiString GameSpyInfo::getLocalPassword(void)
{
	return m_localPasswd;
}

// ?setLocalPassword@GameSpyInfo@@UAEXVAsciiString@@@Z @0x00386241 52B
void GameSpyInfo::setLocalPassword(AsciiString passwd)
{
	m_localPasswd = passwd;
}

// ?setLocalBaseName@GameSpyInfo@@UAEXVAsciiString@@@Z @0x00386275 55B
void GameSpyInfo::setLocalBaseName(AsciiString name)
{
	m_localBaseName = name;
}

// ?getLocalBaseName@GameSpyInfo@@UAE?AVAsciiString@@XZ @0x003862AC 30B
AsciiString GameSpyInfo::getLocalBaseName(void)
{
	return m_localBaseName;
}

// ?readAdditionalDisconnects@GameSpyInfo@@UAEXXZ @0x003853C6 20B
void GameSpyInfo::readAdditionalDisconnects(void)
{
	m_additionalDisconnects = GetAdditionalDisconnectsFromUserFile(m_localProfileID);
}

// ?isBuddy@GameSpyInfo@@UAE_NH@Z @0x003835D7 29B
Bool GameSpyInfo::isBuddy(Int id)
{
	return m_buddyMap.find(id) != m_buddyMap.end();
}

// ?findStagingRoomByID@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@H@Z @0x00383846 31B
GameSpyStagingRoom *GameSpyInfo::findStagingRoomByID(Int id)
{
	StagingRoomMap::iterator it = m_stagingRooms.find(id);
	if (it != m_stagingRooms.end())
		return it->second;
	return 0;
}

// ?getCurrentStagingRoom@GameSpyInfo@@UAEPAVGameSpyStagingRoom@@XZ @0x003835A0 48B
GameSpyStagingRoom *GameSpyInfo::getCurrentStagingRoom(void)
{
	if (m_isHosting || m_joinedStagingRoom)
		return reinterpret_cast<GameSpyStagingRoom *>(&m_localStagingRoom);

	StagingRoomMap::iterator it = m_stagingRooms.find(m_localStagingRoomID);
	if (it != m_stagingRooms.end())
		return it->second;
	return 0;
}

// ?clearStagingRoomList@GameSpyInfo@@UAEXXZ @0x00382E2F 68B
void GameSpyInfo::clearStagingRoomList(void)
{
	Int numRoomsRemoved = 0;
	m_sawFullGameList = false;
	m_stagingRoomsDirty = false;

	StagingRoomMap::iterator it = m_stagingRooms.begin();
	while (it != m_stagingRooms.end())
	{
		++numRoomsRemoved;

		::delete it->second;
		m_stagingRooms.erase(it);
		it = m_stagingRooms.begin();
	}
	if (numRoomsRemoved > 0)
	{
	}
}

// ?addGroupRoom@GameSpyInfo@@UAEXVGameSpyGroupRoom@@@Z @0x00386B7B 893B
// ZH's addGroupRoom. BFME 2 falls back to the translated raw room name when a
// GUI:<name> label is missing and records the lobby room IDs by label.
void GameSpyInfo::addGroupRoom(GameSpyGroupRoom room)
{
	if (room.m_groupID == 0)
	{
		m_gotGroupRoomList = true;

		GroupRoomMap::iterator iter;

		// figure out how many good strings we've got
		_STL::vector<UnicodeString> names;
		Int numRooms = 0;
		for (iter = getGroupRoomList()->begin(); iter != getGroupRoomList()->end(); ++iter)
		{
			GameSpyGroupRoom room = iter->second;
			if (room.m_groupID != TheGameSpyConfig->getQMChannel())
			{
				++numRooms;

				AsciiString groupLabel;
				groupLabel.format("GUI:%s", room.m_name.str());

				Bool exists = false;
				UnicodeString groupName = TheGameText->fetch(groupLabel, &exists);
				if (exists)
				{
					names.push_back(groupName);
					if (groupLabel.compare("GUI:LobbyRoom1") == 0)
					{
						g_lobbyRoom1ID = room.m_groupID;
						g_lobbyRoom1IDAlt = room.m_groupID;
					}
					else if (groupLabel.compare("GUI:LobbyRoom2") == 0)
					{
						g_lobbyRoom2ID = room.m_groupID;
					}
					else if (groupLabel.compare("GUI:LobbyRoom6") == 0)
					{
						g_lobbyRoom6ID = room.m_groupID;
					}
					else if (groupLabel.compare("GUI:LobbyRoom9") == 0)
					{
						g_lobbyRoom9ID = room.m_groupID;
					}
				}
				else
				{
					UnicodeString rawName;
					rawName.translate(room.m_name);
					names.push_back(rawName);
				}
			}
		}

		if (!names.empty() && names.size() != numRooms)
		{
			// didn't get all names.  fix up
			Int nameIndex = 0;
			Int timesThrough = 1; // start with USA Lobby 1
			for (iter = TheGameSpyInfo->getGroupRoomList()->begin(); iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter)
			{
				GameSpyGroupRoom room = iter->second;
				if (room.m_groupID != TheGameSpyConfig->getQMChannel())
				{
					room.m_translatedName.format(L"%ls %d", names[nameIndex].str(), timesThrough);
					nameIndex = (nameIndex+1)%names.size();
					m_groupRooms[room.m_groupID] = room;
					if (!nameIndex)
					{
						// we've looped through the name list already.  increment the timesThrough counter
						++timesThrough;
					}
				}
			}
		}
	}
	else
	{
		AsciiString groupLabel;
		groupLabel.format("GUI:%s", room.m_name.str());
		Bool exists = false;
		room.m_translatedName = TheGameText->fetch(groupLabel, &exists);
		if (!exists)
			room.m_translatedName.translate(room.m_name);
		m_groupRooms[room.m_groupID] = room;
		if ( !_imp___strcmpi("quickmatch", room.m_name.str()) )
		{
			TheGameSpyConfig->setQMChannel(room.m_groupID);
		}
	}
}

// ?setCurrentGroupRoom@GameSpyInfo@@UAEXH@Z @0x003862DB 18B
void GameSpyInfo::setCurrentGroupRoom(Int groupID)
{
	m_currentGroupRoomID = groupID;
	m_playerInfoMap.clear();
}

// ?updatePlayerInfo@GameSpyInfo@@UAEXVPlayerInfo@@VAsciiString@@@Z @0x00386EF8 135B
void GameSpyInfo::updatePlayerInfo(PlayerInfo pi, AsciiString oldNick)
{
	if (!oldNick.isEmpty())
		playerLeftGroupRoom(oldNick);

	m_playerInfoMap[pi.m_name] = pi;
	if (pi.m_preorder)
		markPlayerAsPreorder(pi.m_profileID);
}

// ?playerLeftGroupRoom@GameSpyInfo@@UAEXVAsciiString@@@Z @0x00384660 72B
void GameSpyInfo::playerLeftGroupRoom(AsciiString nick)
{
	PlayerInfoMap::iterator it = m_playerInfoMap.find(nick);
	if (it != m_playerInfoMap.end())
	{
		m_playerInfoMap.erase(it);
	}
}

// ?addToSavedIgnoreList@GameSpyInfo@@UAEXHVAsciiString@@@Z @0x00385E2A 118B
void GameSpyInfo::addToSavedIgnoreList(Int profileID, AsciiString nick)
{
	m_savedIgnoreMap[profileID] = nick;
	IgnorePreferences pref;
	pref.rva003B2322(nick, profileID, true);
	pref.write();
}

// ?removeFromSavedIgnoreList@GameSpyInfo@@UAEXH@Z @0x00385B1C 92B
void GameSpyInfo::removeFromSavedIgnoreList(Int profileID)
{
	m_savedIgnoreMap.erase(profileID);
	IgnorePreferences pref;
	pref.rva003B2322(AsciiString::TheEmptyString, profileID, false);
	pref.write();
}

// ?isSavedIgnored@GameSpyInfo@@UAE_NH@Z @0x003839B9 32B
Bool GameSpyInfo::isSavedIgnored(Int profileID)
{
	return m_savedIgnoreMap.find(profileID) != m_savedIgnoreMap.end();
}

// ?isIgnored@PlayerInfo@@QAE_NXZ @0x00382841 56B
Bool PlayerInfo::isIgnored(void)
{
	return (m_profileID) ? TheGameSpyInfo->isSavedIgnored(m_profileID) : TheGameSpyInfo->isIgnored(m_name);
}

// ?validateStagingRoom@GameSpyInfo@@UAE_NPAVGameSpyStagingRoom@@@Z @0x00383207 55B
Bool GameSpyInfo::validateStagingRoom(GameSpyStagingRoom *room)
{
	StagingRoomMap::iterator it = m_stagingRooms.begin();
	while (it != m_stagingRooms.end())
	{
		if (it->second == room)
			return true;
		++it;
	}
	Bool r = (&m_localStagingRoom == (void *)room);
	return r;
}

// ?setPingString@GameSpyInfo@@UAEXABVAsciiString@@@Z @0x0030D420 8B
void GameSpyInfo::setPingString(const AsciiString &ping)
{
	m_pingString = ping;
}

// ?rva003860FF@GameSpyInfo@@UAEGXZ @0x003860FF 5B
unsigned short GameSpyInfo::rva003860FF(void)
{
	return 0x1F98;
}

// ?rva003674FE@GameSpyInfo@@UAEXH@Z @0x003674FE 10B
void GameSpyInfo::rva003674FE(Int value)
{
	m_unk0068 = value;
}

// ?rva00386139@GameSpyInfo@@UAEXVAsciiString@@@Z @0x00386139
void GameSpyInfo::rva00386139(AsciiString value)
{
	m_unk0060 = value;
}

// ?rva0038616D@GameSpyInfo@@UAE?AVAsciiString@@XZ @0x0038616D
AsciiString GameSpyInfo::rva0038616D(void)
{
	return m_unk0060;
}

// ?rva00382CCE@GameSpyInfo@@UAEPAVPlayerInfo@@PBD@Z @0x00382CCE
PlayerInfo *GameSpyInfo::rva00382CCE(const char *key)
{
	PlayerInfoMap::iterator it = m_playerInfoMap.begin();
	while (it != m_playerInfoMap.end())
	{
		PlayerInfo *info = &it->second;
		if (info->m_locale.compare(key) == 0)
			return info;
		++it;
	}
	return 0;
}

// ?rva00382D0A@GameSpyInfo@@UAEPAVPlayerInfo@@H@Z @0x00382D0A
PlayerInfo *GameSpyInfo::rva00382D0A(Int profileID)
{
	PlayerInfoMap::iterator it = m_playerInfoMap.begin();
	while (it != m_playerInfoMap.end())
	{
		PlayerInfo *info = &it->second;
		if (info->m_profileID == profileID)
			return info;
		++it;
	}
	return 0;
}

// ?joinGroupRoom@GameSpyInfo@@UAEXH@Z @0x003853DA
void GameSpyInfo::joinGroupRoom(Int groupID)
{
	if (groupID > 0)
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_JOINGROUPROOM;
		req.groupRoom.id = groupID;
		TheGameSpyPeerMessageQueue->addRequest(req);
		m_playerInfoMap.clear();
	}
}

// ?leaveGroupRoom@GameSpyInfo@@UAEXXZ @0x0038544D 120B
void GameSpyInfo::leaveGroupRoom(void)
{
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_LEAVEGROUPROOM;
	req.groupRoom.id = getCurrentGroupRoom();
	TheGameSpyPeerMessageQueue->addRequest(req);
	setCurrentGroupRoom(0);
	m_playerInfoMap.clear();
}

// ?rva003854C5@GameSpyInfo@@UAEXXZ @0x003854C5 120B
void GameSpyInfo::rva003854C5(void)
{
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_LEAVEGROUPROOMONLY;
	req.groupRoom.id = getCurrentGroupRoom();
	TheGameSpyPeerMessageQueue->addRequest(req);
	setCurrentGroupRoom(0);
	m_playerInfoMap.clear();
}

// ?joinPreferredGroupRoom@GameSpyInfo@@UAEX_NH@Z @0x0038553D 315B
// Joins the lobby room for a room type: types 1 and 2 use the room saved in
// that mode's custom-match preferences, falling back to a GUI:LobbyRoom ID.
// The flag (1 from the caller at 0x00516F08) is never read.
void GameSpyInfo::joinPreferredGroupRoom(Bool unusedFlag, Int roomType)
{
	Int groupID;
	switch (roomType)
	{
	case 1:
		{
			Rva0054F508 pref(0);
			groupID = ((GameModePreferences *)&pref)->rva0054F5A4();
			if (groupID <= 0)
				groupID = g_lobbyRoom2ID;
		}
		break;
	case 2:
		{
			Rva0054F508 pref(1);
			groupID = ((GameModePreferences *)&pref)->rva0054F5A4();
			if (groupID <= 0)
				groupID = g_lobbyRoom9ID;
		}
		break;
	case 3:
		groupID = g_lobbyRoom6ID;
		break;
	case 4:
		groupID = g_lobbyRoom1ID;
		break;
	case 5:
		groupID = g_lobbyRoom1IDAlt;
		break;
	default:
		return;
	}

	if (groupID > 0)
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_JOINGROUPROOM;
		req.groupRoom.id = groupID;
		TheGameSpyPeerMessageQueue->addRequest(req);
		m_playerInfoMap.clear();
	}
	else
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSGroupRoomJoinFail"), 0);
	}
}

// ?joinBestGroupRoom@GameSpyInfo@@UAEXH@Z @0x00385678 371B
// ZH's joinBestGroupRoom, filtered to rooms of the requested type; the bail-out
// tests the per-type current room (+0x64 for type 2, else +0x68).
void GameSpyInfo::joinBestGroupRoom(Int roomType)
{
	if ((roomType == 2 ? m_unk0064 : m_unk0068) != 0)
	{
		m_currentGroupRoomID = 0;
		return;
	}

	if (m_groupRooms.size())
	{
		Int minID = -1;
		Int minPlayers = 1000;
		GroupRoomMap::iterator iter = m_groupRooms.begin();
		while (iter != m_groupRooms.end())
		{
			AsciiUnicodePair room = iter->second;
			if (TheGameSpyConfig->getQMChannel() != room.m_groupID && minPlayers > 25
				&& room.m_numWaiting < minPlayers && room.m_roomType == roomType)
			{
				minID = room.m_groupID;
				minPlayers = room.m_numWaiting;
			}
			++iter;
		}

		if (minID > 0)
		{
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_JOINGROUPROOM;
			req.groupRoom.id = minID;
			TheGameSpyPeerMessageQueue->addRequest(req);
			m_playerInfoMap.clear();
		}
		else
		{
			GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSGroupRoomJoinFail"), 0);
		}
	}
	else
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:GSGroupRoomJoinFail"), 0);
	}
}

// ?addStagingRoom@GameSpyInfo@@UAEXVGameSpyStagingRoom@@@Z @0x003857EB 244B
// ZH's addStagingRoom, but a room advertising a non-zero map digest is only
// listed when that digest names a known map.
void GameSpyInfo::addStagingRoom(GameSpyStagingRoom room)
{
	removeStagingRoom(room);
	unsigned char digest[16];
	memcpy(digest, room.m_digest, 16);
	char printedDigest[33];
	MD5Print(digest, printedDigest);
	if (strcmp("00000000000000000000000000000000", printedDigest) != 0 &&
		!Rva004360B3(AsciiString(printedDigest)))
		return;
	GameSpyStagingRoom *newRoom = new GameSpyStagingRoom;
	*(Rva00382E73 *)newRoom = *(Rva00382E73 *)&room;
	newRoom->cleanUpSlotPointers();
	// Retail calls the identical-code-folded map<int,int>::operator[] (0x0028932C).
	((_STL::map<Int, Int> &)m_stagingRooms)[room.getID()] = (Int)newRoom;
	m_stagingRoomsDirty = m_sawFullGameList;
}

// ?removeStagingRoom@GameSpyInfo@@UAEXVGameSpyStagingRoom@@@Z @0x003837D3 115B
void GameSpyInfo::removeStagingRoom(GameSpyStagingRoom room)
{
	StagingRoomMap::iterator it = m_stagingRooms.find(room.getID());
	if (it != m_stagingRooms.end())
	{
		::delete it->second;
		m_stagingRooms.erase(it);
		m_stagingRoomsDirty = m_sawFullGameList;
	}
}

// ?leaveStagingRoom@GameSpyInfo@@UAEXXZ @0x003858DF 119B
void GameSpyInfo::leaveStagingRoom(void)
{
	m_localStagingRoomID = 0;
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_LEAVESTAGINGROOM;
	TheGameSpyPeerMessageQueue->addRequest(req);
	m_playerInfoMap.clear();
	m_joinedStagingRoom = 0;
	m_isHosting = false;
}

// ZH's setGameOptions with BFME 2's per-slot-index arrays, a fourth AI name,
// the staging room's +0x58/+0x5C/+0x60 values, and two more UTMs: the human
// player names by slot (UTMSTAGINGPN) and "PIDS/" profile IDs with each
// slot's +0x1A8 string. The 40-byte copy is an out-of-line memcpy call.
// AsciiString::getCharAt and concat(char) expanded inline, as retail emits
// them here.
static inline char peerCharAt(const AsciiString &s, Int i)
{
	const BfmeStringData<char> *data = *reinterpret_cast<BfmeStringData<char> * const *>(&s);
	return data ? data->text[i] : 0;
}
#define LOCAL_GAME (reinterpret_cast<const GameInfo *>(m_localStagingRoom))
#pragma function(memcpy)
// ?setGameOptions@GameSpyInfo@@UAEXXZ @0x00386501 1658B
void GameSpyInfo::setGameOptions(void)
{
	if (!m_isHosting)
		return;

	// set options for game lists, and UTM players in-game
	PeerRequest req;
	req.peerRequestType = PeerRequest::PEERREQUEST_SETGAMEOPTIONS;
	req.options = GameInfoToAsciiString(LOCAL_GAME, false).str();

	Int i;
	AsciiString mapName = TheGameState->realMapPathToPortableMapPath(LOCAL_GAME->getMap());
	AsciiString newMapName;
	for (i=0; i<mapName.getLength(); ++i)
	{
		char c = peerCharAt(mapName, i);
		if (c == '\\')
			c = '/';
		reinterpret_cast<StringBase<char> *>(&newMapName)->concat(&c, 1);
	}
	req.gameOptsMapName = newMapName.str();
	memcpy(req.gameOptsUnknownD0, LOCAL_GAME->m_60, sizeof(req.gameOptsUnknownD0));
	req.gameOptions.valueCC = LOCAL_GAME->m_5c;

	req.gameOptions.numPlayers = 0;
	req.gameOptions.numObservers = 0;
	Int numOpenSlots = 0;
	AsciiString playerInfo = "";
	for (i=0; i<MAX_SLOTS; ++i)
	{
		Int wins = 0, losses = 0, profileID = 0;
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
		req.gameOptsPlayerNames[i] = "";
		req.gameOptions.wins[i] = 0;
		req.gameOptions.losses[i] = 0;
		req.gameOptions.profileID[i] = slot->getState();
		req.gameOptions.faction[i] = slot->getPlayerTemplate();
		req.gameOptions.color[i] = slot->getColor();
		req.gameOptions.slotValue20[i] = slot->m_20;
		if (!slot->isOccupied())
		{
			if (slot->isOpen())
				++numOpenSlots;
		}
		else
		{
			AsciiString playerName;
			if (slot->isHuman())
			{
				playerName.translate(slot->getName());
				req.gameOptsPlayerNames[i] = playerName.str();
				PlayerInfoMap::iterator it = m_playerInfoMap.find(playerName);
				if (it != m_playerInfoMap.end())
				{
					wins = it->second.m_wins;
					losses = it->second.m_losses;
					profileID = it->second.m_profileID;
				}
				req.gameOptions.wins[i] = wins;
				req.gameOptions.losses[i] = losses;
				req.gameOptions.profileID[i] = profileID;
				req.gameOptions.faction[i] = slot->getPlayerTemplate();
				req.gameOptions.color[i] = slot->getColor();
				req.gameOptions.slotValue20[i] = slot->m_20;
				if (slot->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER)
				{
					++req.gameOptions.numObservers;
				}
				else
				{
					++req.gameOptions.numPlayers;
				}
			}
			else if (slot->isAI())
			{
				// add in AI players
				switch (slot->getState())
				{
				case SLOT_EASY_AI:
					playerName = "CE";
					break;
				case SLOT_MED_AI:
					playerName = "CM";
					break;
				case SLOT_BRUTAL_AI:
					playerName = "CH";
					break;
				case SLOT_AI_5:
					playerName = "CB";
					break;
				}
				req.gameOptsPlayerNames[i] = playerName.str(); // name is unused - we go off of the profileID
				req.gameOptions.wins[i] = 0;
				req.gameOptions.losses[i] = 0;
				req.gameOptions.profileID[i] = slot->getState();
				req.gameOptions.faction[i] = slot->getPlayerTemplate();
				req.gameOptions.color[i] = slot->getColor();
				req.gameOptions.slotValue20[i] = slot->m_20;
				++req.gameOptions.numPlayers;
			}
		}
	}
	req.gameOptions.maxPlayers = numOpenSlots + req.gameOptions.numObservers + req.gameOptions.numPlayers;
	req.gameOptions.valueD0 = LOCAL_GAME->m_58;
	TheGameSpyPeerMessageQueue->addRequest(req);

	AsciiString playerNames;
	for (i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = LOCAL_GAME->getConstSlot(i);
		if (slot->isHuman())
		{
			if (i != 0)
				playerNames.concat(",");
			AsciiString entry;
			entry.format("%d=%s", i, WideCharStringToMultiByte(slot->getName().str()).c_str());
			playerNames.concat(entry);
		}
	}
	PeerRequest namesReq;
	namesReq.peerRequestType = PeerRequest::PEERREQUEST_UTMSTAGINGPN;
	namesReq.options = playerNames.str();
	TheGameSpyPeerMessageQueue->addRequest(namesReq);

	req.peerRequestType = PeerRequest::PEERREQUEST_UTMROOM;
	req.UTM.isStagingRoom = true;
	req.id = "Pings/";
	AsciiString pings;
	for (i=0; i<MAX_SLOTS; ++i)
	{
		if (i!=0)
			pings.concat(",");

		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
		if (slot && slot->isHuman())
		{
			pings.concat(((const Rva00382216AsciiField *)slot)->get());
		}
		else
		{
			pings.concat("0");
		}
	}
	req.options = pings.str();
	TheGameSpyPeerMessageQueue->addRequest(req);

	req.peerRequestType = PeerRequest::PEERREQUEST_UTMROOM;
	req.UTM.isStagingRoom = true;
	req.id = "PIDS/";
	AsciiString pids;
	for (i=0; i<MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
		if (slot && slot->isHuman())
		{
			AsciiString entry;
			AsciiString tag = ((const Rva003821B9AsciiField *)slot)->get();
			entry.format("%x,%s", slot->getProfileID(), tag.isEmpty() ? " " : tag.str());
			pids.concat(entry);
		}
		else
		{
			pids.concat(" , ");
		}
		pids.concat(",");
	}
	req.options = pids.str();
	TheGameSpyPeerMessageQueue->addRequest(req);
}
#undef LOCAL_GAME
#pragma intrinsic(memcpy)

// ?TearDownGameSpy@@YAXXZ @0x00385956 424B
// ZH's TearDownGameSpy without the rank-point table; BFME 2 also ends and
// frees ThePinger and moves the cached-stats write into 0x00556FB8.
void TearDownGameSpy(void)
{
	if (TheGameSpyInfo && TheGameSpyInfo->getLocalProfileID())
	{
		PSPlayerStats localPSStats = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
		if (localPSStats.id != 0)
			Rva00556FB8(localPSStats);
	}

	if (TheGameSpyPSMessageQueue)
		TheGameSpyPSMessageQueue->endThread();
	if (TheGameSpyBuddyMessageQueue)
		TheGameSpyBuddyMessageQueue->endThread();
	if (TheGameSpyPeerMessageQueue)
		TheGameSpyPeerMessageQueue->endThread();
	if (ThePinger)
		ThePinger->endThreads();

	if (TheGameSpyPSMessageQueue)
	{
		::delete TheGameSpyPSMessageQueue;
		TheGameSpyPSMessageQueue = NULL;
	}
	if (TheGameSpyBuddyMessageQueue)
	{
		::delete TheGameSpyBuddyMessageQueue;
		TheGameSpyBuddyMessageQueue = NULL;
	}
	if (TheGameSpyPeerMessageQueue)
	{
		::delete TheGameSpyPeerMessageQueue;
		TheGameSpyPeerMessageQueue = NULL;
	}
	if (TheGameSpyInfo)
	{
		if (TheGameSpyInfo->getInternalIP())
			Rva003B3371Call(0x13);
		::delete TheGameSpyInfo;
		TheGameSpyInfo = NULL;
	}
	if (ThePinger)
	{
		::delete ThePinger;
		ThePinger = NULL;
	}
	if (TheLadderList)
	{
		delete TheLadderList;
		TheLadderList = NULL;
	}
	if (TheGameSpyConfig)
	{
		::delete TheGameSpyConfig;
		TheGameSpyConfig = NULL;
	}

	Rva00415EF8Close();
}

// ?reset@GameSpyInfo@@UAEXXZ @0x00385D25 261B
void GameSpyInfo::reset(void)
{
	m_sawFullGameList = false;
	m_isDisconAfterGameStart = false;
	m_currentGroupRoomID = 0;
	m_unk0060.clear();
	m_unk0064 = 0;
	m_unk0068 = 0;
	clearGroupRoomList();
	clearStagingRoomList();
	m_localStagingRoomID = 0;
	((Rva0038404A *)&m_buddyRequestMap)->rva00384E8E();
	((Rva0038404A *)&m_buddyMap)->rva00384E8E();
	((Rva00383AFF *)&m_buddyMessages)->rva00383AFF();
	m_joinedStagingRoom = 0;
	m_isHosting = false;
	m_localStagingRoomID = 0;
	((GameSpyStagingRoom *)m_localStagingRoom)->reset();
	m_gotGroupRoomList = false;
	m_localName = "";
	m_localProfileID = 0;
	m_maxMessagesPerUpdate = 100;
	m_disallowAsainText = false;
	m_disallowNonAsianText = false;
	m_disconReason = 0;
	m_localBaseName.clear();
	m_localEmail.clear();
	m_localPasswd.clear();
	m_pingString.clear();
	m_rawConfig.clear();
	m_rawMotd.clear();
	m_internalIP = m_externalIP = 0;
	((Rva00383A28 *)&m_savedIgnoreMap)->rva00383A28();
	((Rva00072FE6 *)&m_preorderPlayers)->rva00072FE6();
	((PSPlayerAllStats *)m_cachedLocalPlayerStats)->rva00552CB8();
	m_additionalDisconnects = -1;
	m_unk163C = false;
}

class Rva00382077 { public: ~Rva00382077(); };
class Rva0038201D { public: ~Rva0038201D(); };
class Rva0038204A { public: ~Rva0038204A(); };
class Rva003820A4 { public: ~Rva003820A4(); };
class Rva003820D1 { public: ~Rva003820D1(); };

class Rva00383567
{
public:
	void rva00383567();
};

void Rva00383567::rva00383567()
{
	((Rva00382077 *)this)->~Rva00382077();
}

class Rva0038356C
{
public:
	void rva0038356C();
};

void Rva0038356C::rva0038356C()
{
	((Rva0038201D *)this)->~Rva0038201D();
}

class Rva00383571
{
public:
	void rva00383571();
};

void Rva00383571::rva00383571()
{
	((Rva0038204A *)this)->~Rva0038204A();
}

class Rva00383576
{
public:
	void rva00383576();
};

void Rva00383576::rva00383576()
{
	((Rva003820A4 *)this)->~Rva003820A4();
}

class Rva0038357B
{
public:
	void rva0038357B();
};

void Rva0038357B::rva0038357B()
{
	((Rva003820D1 *)this)->~Rva003820D1();
}

