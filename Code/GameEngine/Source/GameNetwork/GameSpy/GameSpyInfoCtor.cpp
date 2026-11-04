// ??0GameSpyInfo@@QAE@XZ
// partial score=0.95 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
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
#include <vector>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"
#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree<unsigned char, pair<unsigned char const, int>, _Select1st<pair<unsigned char const, int> >, less<unsigned char>, allocator<pair<unsigned char const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::~_Rb_tree(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$allocator@H@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<int,int,_Identity<int>,less<int>,allocator<int> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBEH@_STL@@V?$allocator@U?$pair@$$CBEH@_STL@@@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<unsigned char const ,int>,allocator<pair<unsigned char const ,int> > >::~_Rb_tree_base(); }

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

class PSPlayerAllStats {
public:
    PSPlayerAllStats(int id);
    ~PSPlayerAllStats();
    void rva00552CB8(void);
private:
    unsigned int m_words[0x548 / 4];
};
// The member at +0x58 is the one-pointer list base constructed by 0x38295A.
// This existing opaque specialization names storage, not a target message type.
struct BfmePod24 { int a[6]; };

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
struct BfmeOpaqueOwnedRecord492
{
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[492];
	};
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
};

// 0x1020-byte staging-room record (GameInfo base at +0; ctor 0x004FDE4D,
// copy ctor 0x003835F4, dtor 0x00382C4A).
#include "../../../Include/GameNetwork/GameSpyStagingRoom.h"

// GameInfo assignment (0x00382E73), rowed under its address name.
struct TreeHintOpaque0043671B;
extern "C" void MD5Print(unsigned char digest[16], char output[33]);
TreeHintOpaque0043671B *Rva004360B3(AsciiString key);

#include "../../../Include/GameNetwork/PlayerInfo.h"

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

typedef _STL::set<AsciiString> IgnoreList;
typedef _STL::map<Int, AsciiString> SavedIgnoreMap;
// ICF twin respells: the GameSpy container default ctors are unrowed and fold
// onto the rowed same-address instantiations below (25B each).
struct Rva001DDBC6Record { char m_pad[1]; };	// one byte, as StlSweepR3Rva001DDBC6.cpp defines it
typedef _STL::map<Int, Rva001DDBC6Record> GroupRoomMap;			// ctor 0x001DDBC6
typedef _STL::map<unsigned char, int> StagingRoomMap;			// ctor 0x0033C432
class DetailedArchivedDirectoryInfo { public: ~DetailedArchivedDirectoryInfo(); char m_pad[8]; };
typedef _STL::map<AsciiString, DetailedArchivedDirectoryInfo> BuddyInfoMap;	// ctor 0x005B400A
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;	// ctor folds onto 0x004260FD
// Suppress this TU's non-retail copy of the PlayerInfoMap _M_erase; the copy
// rowed in PeerDefs.cpp (0x00383ACA) serves the link. Declaration-only form.
namespace _STL { template <> void _Rb_tree<AsciiString,pair<AsciiString const ,PlayerInfo>,_Select1st<pair<AsciiString const ,PlayerInfo> >,AsciiComparator,allocator<pair<AsciiString const ,PlayerInfo> > >::_M_erase(_Rb_tree_node<pair<AsciiString const ,PlayerInfo> > *); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBHVAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@2@@_STL@@QAE@ABV?$al:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<int const, AsciiString>, allocator<pair<int const, AsciiString> > >::_Rb_tree_base(allocator<pair<int const, AsciiString> > const &); }
typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

extern Int GetAdditionalDisconnectsFromUserFile(Int playerID);

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread(void);
	virtual void endThread(void);
	virtual void s03(void);
	virtual void s04(void);
	virtual void s05(void);
	virtual void addRequest(const BfmeOpaqueOwnedRecord492 &req);

	static GameSpyPeerMessageQueueInterface *createNewMessageQueue(void);
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

#include "../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

#include "../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

#include "../../../Include/GameNetwork/GameSpyConfigInterface.h"

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

#include "../../../Include/Common/GameModePreferences.h"

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
	virtual void startThread(void);
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
	virtual void startThread(void);
	virtual void endThread(void);
};

class PingerInterface
{
public:
	virtual ~PingerInterface();
	virtual void startThreads(void);
	virtual void endThreads(void);

	static PingerInterface *createNewPingerInterface(void);
};

// LadderList (0xC bytes): ctor 0x0054E546, non-virtual dtor rowed at 0x0054D974.
class Rva0054D974
{
public:
	Rva0054D974();
	~Rva0054D974();
private:
	void *m_lists[3];
};

// The three thread factories SetUpGameSpy calls are rowed under names that
// disagree with the globals retail stores their results in: 0x00551B28
// (allocates 0x74 for TheGameSpyBuddyMessageQueue) is rowed as
// GameResultsInterface's, 0x005590FC (TheGameSpyPSMessageQueue) as
// PingerInterface's, and the pinger factory 0x005503B1 by address.
class GameResultsInterface
{
public:
	static GameResultsInterface *createNewGameResultsInterface(void);
};
class Rva0055011A;
// GlobalData's user-data path getter and FileSystem::createDirectory, both
// rowed by address.
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
class FileSystem;
extern FileSystem *TheFileSystem;
// Rva0054F508 is CustomMatchPreferences; its getters are rowed by name.
#include "../../../Include/Common/CustomMatchPreferencesClass.h"

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;	// 0x00E05FC8
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;	// 0x00E05FBC
extern PingerInterface *ThePinger;		// 0x00E05FB8
extern Rva0054D974 *TheLadderList;		// 0x00E05FB0

// 0x00556FB8 (rowed in GameSpy/Thread/PersistentStorageThread.cpp): writes
// the stats into GameSpyMiscPreferences' cached stats as two hex strings (ZH
// inlines a key/value version of this in TearDownGameSpy).
void Rva00556FB8(const PSPlayerStats &stats);
void Rva003B3371Call(Int hook);		// SignalUIInteraction
void Rva00415EF8Close(void);		// deleteNotificationBox

extern "C" const void *const __identifier("??_7Rva00381D78@@6B@")[];
class Rva00386374Base
{
public:
    virtual ~Rva00386374Base() { *(const void **)this = __identifier("??_7Rva00381D78@@6B@"); }
};
class GameSpyInfo : public Rva00386374Base
{
public:
	GameSpyInfo();			// 0x00385FE1
	// Virtual slots follow the retail vtable at 0x00C1DD90 so that virtual
	// self-calls encode the right slot offsets; unnamed slots are placeholders.
	virtual ~GameSpyInfo();
	virtual void reset(void);
	virtual void clearGroupRoomList(void) = 0;
	virtual GroupRoomMap *getGroupRoomList(void) = 0;
	virtual void addGroupRoom(GameSpyGroupRoom room);
	virtual void slot05(void) = 0;
	virtual void joinGroupRoom(Int groupID);
	virtual void leaveGroupRoom(void);
	virtual void rva003854C5(void);
	virtual void joinBestGroupRoom(Int roomType);
	virtual void joinPreferredGroupRoom(Bool unusedFlag, Int roomType);
	virtual void setCurrentGroupRoom(Int groupID);
	virtual Int getCurrentGroupRoom(void) = 0;
	virtual void rva00386139(AsciiString value);
	virtual AsciiString rva0038616D(void);
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void rva003674FE(Int value);
	virtual void slot18(void) = 0;
	virtual void updatePlayerInfo(PlayerInfo pi, AsciiString oldNick);
	virtual void playerLeftGroupRoom(AsciiString nick);
	virtual void slot21(void) = 0;
	virtual PlayerInfo *rva00382CCE(const char *key);
	virtual PlayerInfo *rva00382D0A(Int profileID);
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual Bool isBuddy(Int id);
	virtual void setLocalName(AsciiString name);
	virtual AsciiString getLocalName(void);
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual AsciiString getLocalEmail(void);
	virtual void setLocalEmail(AsciiString email);
	virtual AsciiString getLocalPassword(void);
	virtual void setLocalPassword(AsciiString passwd);
	virtual void setLocalBaseName(AsciiString name);
	virtual AsciiString getLocalBaseName(void);
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void clearStagingRoomList(void);
	virtual void slot41(void) = 0;
	virtual GameSpyStagingRoom *findStagingRoomByID(Int id);
	virtual void addStagingRoom(GameSpyStagingRoom room);
	virtual void updateStagingRoom(GameSpyStagingRoom room) = 0;
	virtual void removeStagingRoom(GameSpyStagingRoom room);
	virtual Bool hasStagingRoomListChanged(void);
	virtual void leaveStagingRoom(void);
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual Bool rva00381DC4(void);
	virtual GameSpyStagingRoom *getCurrentStagingRoom(void);
	virtual Bool validateStagingRoom(GameSpyStagingRoom *room);
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void slot57(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot59(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot61(void) = 0;
	virtual void slot62(void) = 0;
	virtual void slot63(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot65(void) = 0;
	virtual void setMOTD(const AsciiString &motd);
	virtual void slot67(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot69(void) = 0;
	virtual void setPingString(const AsciiString &ping);
	virtual void slot71(void) = 0;
	virtual void slot72(void) = 0;
	virtual void slot73(void) = 0;
	virtual void slot74(void) = 0;
	virtual void addToSavedIgnoreList(Int profileID, AsciiString nick);
	virtual void removeFromSavedIgnoreList(Int profileID);
	virtual Bool isSavedIgnored(Int profileID);
	virtual void slot78(void) = 0;
	virtual void loadSavedIgnoreList(void) = 0;
	virtual IgnoreList returnIgnoreList(void);
	virtual void addToIgnoreList(AsciiString nick);
	virtual void removeFromIgnoreList(AsciiString nick);
	virtual Bool isIgnored(AsciiString nick);
	virtual void setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP);
	virtual void slot85(void) = 0;
	virtual unsigned short rva003860FF(void);
	virtual void slot87(void) = 0;
	virtual Bool isDisconnectedAfterGameStart(Int *reason) const;
	virtual void markAsDisconnectedAfterGameStart(Int reason);
	virtual Bool didPlayerPreorder(Int profileID) const;
	virtual void markPlayerAsPreorder(Int profileID);
	virtual void slot92(void) = 0;
	virtual void slot93(void) = 0;
	virtual void slot94(void) = 0;
	virtual void slot95(void) = 0;
	virtual void readAdditionalDisconnects(void);
	virtual void slot97(void) = 0;
	virtual void slot98(void) = 0;

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
	_STL::list<BfmePod24, _STL::allocator<BfmePod24> > m_buddyMessages;				// +0x58
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
	PSPlayerAllStats m_cachedLocalPlayerStats; // +0x84..+0x5CB
	Bool m_disallowAsainText;			// +0x5CC
	Bool m_disallowNonAsianText;		// +0x5CD
	unsigned char m_pad05CE[2];			// +0x5CE..+0x5CF
	UnsignedInt m_internalIP;			// +0x5D0
	UnsignedInt m_externalIP;			// +0x5D4
	Int m_maxMessagesPerUpdate;			// +0x5D8
	Int m_joinedStagingRoom;			// +0x5DC
	Bool m_isHosting;					// +0x5E0
	unsigned char m_pad05E1[3];			// +0x5E1..+0x5E3
	GameSpyStagingRoom m_localStagingRoom; // +0x5E4..+0x1603
	Int m_localStagingRoomID;			// +0x1604
	IgnoreList m_ignoreList;			// +0x1608..+0x1613
	SavedIgnoreMap m_savedIgnoreMap;	// +0x1614..+0x161F
	_STL::set<AsciiString> m_textWindows; // +0x1620..+0x162B (set ctor 0x000D3A71)
	_STL::set<Int> m_preorderPlayers;	// +0x162C..+0x1637
	Int m_additionalDisconnects;		// +0x1638
	Bool m_unk163C;						// +0x163C
};

extern GameSpyStagingRoom *TheGameSpyGame;
class GameInfo;
extern GameInfo *TheGameInfo;

// ??0GameSpyInfo@@QAE@XZ @0x00385FE1, extent270 through RET at0x003860EE.
// ZH PeerDefs.cpp ctor is the semantic lead. Retail's factory0x3864CC,
// vtable0xC19500, reset0x385D25 and dtor0x386374 establish identity and layout.
// The native member call sequence supplies each constructor and EH lifetime.
GameSpyInfo::GameSpyInfo()
    : m_cachedLocalPlayerStats(0)
{
    reset();
    TheGameInfo = (GameInfo *)(TheGameSpyGame = &m_localStagingRoom);
    m_isDisconAfterGameStart = false;
}
