// ?setGameOptions@GameSpyInfo@@UAEXXZ
// cl: /O1 /arch:SSE /G7 /GF- /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport

// GameSpyInfo::setGameOptions semantic spine: committed ZH PeerDefs.cpp.
// BFME2 [0x386501,0x386B7B) and vtable C19500 slot55 establish identity.
// Access offsets and the four request publications below are target evidence;
// donor field names describe their purpose, rather than proving original names.
// Target slot55 C19500 and native386501..386B7B verify the complete interface.
// Inline initStatsAndGetSlot preserves native argument/store scheduling.
// /GF- is required: pooling empty strings retains EDI through the slot loop.
// This TU isolates that setting; /GF- regresses two existing PeerDefs bodies.

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
typedef _STL::map<Int, GameSpyStagingRoom *> StagingRoomMap;
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
typedef _STL::map<AsciiString, AsciiString> PreferenceMap;

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

class GameSpyGroupRoom;
typedef _STL::map<Int,GameSpyGroupRoom> GroupRoomMap;
class GameSpyInfoInterface {
public:
	virtual ~GameSpyInfoInterface();
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
	virtual void markAsStagingRoomJoiner(Int id);
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
	virtual void rva003871F6(Int id);
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

};
class GameSpyInfo : public GameSpyInfoInterface {
public:
 virtual void setGameOptions();
 unsigned char pad04[0x4c-4];
 PlayerInfoMap m_playerInfoMap;
 unsigned char pad58[0x5e0-0x58];
 bool m_isHosting;
 unsigned char pad5e1[3];
 unsigned char m_localStagingRoom[0x1020];
};
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
static __forceinline void appendMapCharacter(AsciiString &dst, char c)
{
 reinterpret_cast<StringBase<char> *>(&dst)->concat(&c, 1);
}
#define LOCAL_GAME (reinterpret_cast<const GameInfo *>(m_localStagingRoom))
#pragma function(memcpy)
// ?setGameOptions@GameSpyInfo@@UAEXXZ @0x00386501 1658B
static __forceinline GameSpyGameSlot*initStatsAndGetSlot(GameSpyStagingRoom*game,Int i,Int&wins,Int&losses,Int&profileID){(volatile Int&)wins=0;(volatile Int&)losses=0;(volatile Int&)profileID=0;return game->getGameSpySlot(i);}
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
		if(c != '\\') appendMapCharacter(newMapName, c);
		else appendMapCharacter(newMapName, '/');
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
		Int wins, losses, profileID;
		GameSpyGameSlot*slot=initStatsAndGetSlot(TheGameSpyGame,i,wins,losses,profileID);
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
	for (i=0; (UnsignedInt)i<MAX_SLOTS; ++i)
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

