// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AptOnlineCustomMatch::MpOwnerUpdatePlayerTooltip (MpOwner vtable slot 19)
// Retail 0x005A00E6..0x005A061B (1333 bytes) RET4. Builds the staging-room
// player tooltip: locale label (WOL:Locale%2.2d) and favourite side
// (APT:Men or SIDE:%s) from the PlayerInfo record, ladder rank from the
// mode threshold tables, the two rank labels, the ping (own slot or the NAT
// schema peek), then the Local/Buddy/Profiled/Generic player prefix and
// TheMouse tooltip; a non-human slot clears the tooltip.
// Evidence: WorldBuilder twin 0x014EB8C0 names the full staging tooltip;
// BFME1 donor 9cbfb551 chat tooltip (Rva005307B0ChatPlayerTooltip.cpp) as
// semantic guide; target offsets and callees read from retail. The class
// view below is this screen's layout from the home unit
// AptOnlineCustomMatchCallbacks.cpp (which rows the other members).
// Shape note: the wins/losses pair is read through const int references
// for the games total, which keeps retail's reload of both fields after
// the favourite-side constructor and its store of the total; the redundant
// inner if(info) is WB's and gives the retail EH state numbering.

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>
#include <vector>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

// The connecting pop-up's per-slot name and status lines (rowed 0x0059F20B
// and 0x0059F296).
void Rva0059F20BSet(int slot, const UnicodeString &text);
void Rva0059F296Set(int slot, const UnicodeString &text);
// The game slot the owner menus edit. Target facts: Team writes +0x1C;
// the host's name (slot 0) is the UnicodeString at +0x30 that
// AsciiString::translate 0x00038220 reads. encodeHero is the rowed
// 0x003FF16F.
struct GameSpySlotView
{
	unsigned char m_pad000[0x1BC];
	int m_ping; // +0x1BC
};

enum SlotState { SLOT_PLAYER = 6 };
// Retail passes a zero DWORD and zero port WORD to GameSlot::setState.
#include "../../../../../Include/GameNetwork/GameSlotConnectInfo.h"
#include "../../../../../Include/GameNetwork/NATClass.h"

class GameSlot
{
public:
	virtual void reset();
	unsigned char encodeHero() const;
	bool isPlayer(AsciiString name) const;		// rowed 0x003FFEF5
	void rva003FF5F2(const AsciiString &clanID); // rowed 0x003FF5F2
	void setMapAvailability(bool available);	  // rowed 0x003FF8A0
	void setPlayerTemplate(int playerTemplate);   // rowed 0x00400E33
	bool isAI() const;
	void setState(SlotState, UnicodeString, const GameSlotConnectInfo *);
	bool isHuman() const;						 // rowed 0x003FF0F1
	// Slot 6 (+0x18): the GameSpy view of the slot; its +0x1BC is the local
	// player's own ping.
	virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual GameSpySlotView *gameSpySlot();

	int m_state;				// +0x04
	unsigned char m_pad08[0x0C - 0x08];
	int m_color;				// +0x0C

	int m_startPos;			 // +0x10, StartPos sends this one
	int m_startPos14;		   // +0x14, written with it
	unsigned char m_pad18[0x1C - 0x18];
	int m_teamNumber;		   // +0x1C
	int m_handicap;			 // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	UnicodeString m_name;	   // +0x30
};

// The current staging room's game info. Target facts: getSlot (rowed
// 0x003FF29F) takes the room pointer itself, so the vtable is GameInfo's;
// every owner menu calls virtual slot 14 (+0x38) before asking whether this
// player hosts, where the BFME1 donor (OnlineCustomMatchApplySlotTeam.cpp)
// calls resetAccepted.
class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	// Slot 12 (+0x30): StartPosition asks the room this where the other
	// owner menus ask TheGameSpyInfo's amIHost.
	virtual bool amIHost();
	// Slot 13 (+0x34): the local player's slot index, negative when absent.
	virtual int getLocalSlotNum();
	virtual void resetAccepted();
	// Slots 15 and 16 as AptLanLobby::bfmeMapChanged names them (LANGameInfo
	// vtable 0x00C3E518).
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();

	GameSlot *getSlot(int index);
	int getSlotNum(AsciiString) const;
	void setMap(AsciiString mapName);	// rowed 0x00400126

	unsigned char m_pad04[0x14 - 0x04];
	unsigned int m_14;				   // +0x14, the buddy invite's second field
	unsigned char m_pad18[0x5C - 0x18];
	unsigned int m_5c;				   // +0x5C, the buddy invite's last field
	int m_rules[10];					 // +0x60, saved as "Rules"
	void rva003FF1A7(int);
	void setMapCRC(unsigned int crc);	// rowed 0x00400E9F
	void setMapSize(unsigned int size);  // rowed 0x00400F5A
};

class GameSpyGameSlot : public GameSlot
{
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyGameSlot *getGameSpySlot(int index); // rowed 0x004FDA3D
	// RequestJoinGame copies this WORD between complete staging-room objects.
	unsigned char m_pad88[0x1008 - 0x88];
	unsigned short m_1008; // purpose remains unknown
};

// TheGameSpyGame 0x00A02324.
extern GameSpyStagingRoom *TheGameSpyGame;

// The map cache: the AsciiString-keyed map whose find worker is the pinned
// _M_find 0x001F8437; size at +0x28 and CRC at +0x2C of the value (as
// AptLanLobby::bfmeMapChanged reads them).
#include "../../../../../Include/GameClient/MapMetaData.h"

bool operator<(const AsciiString &left, const AsciiString &right);

#include "../../../../../Include/GameClient/MapCache.h"

extern MapCache *TheMapCache;

// TheGameSpyInfo 0x00A02320: slot 29 (+0x74) returns an AsciiString as the
// BFME1 donor's getLocalName; slots 51 (+0xCC), 53 (+0xD4) and 55 (+0xDC)
// as the BFME1 donor's amIHost / getCurrentStagingRoom / setGameOptions.

// Use the shared retail PlayerInfo layout for the staging tooltip.
#include "../../../../../Include/GameNetwork/PlayerInfo.h"
// PeerDefs.h at BFME1 donor revision 9cbfb551 supplies this map value.
// The tooltip only searches its integer profile key, never its payload.
class BuddyInfo
{
public:
    int m_id;
    AsciiString m_name;
    AsciiString m_email;
    AsciiString m_countryCode;
    int m_status;
    UnicodeString m_statusString;
    UnicodeString m_locationString;
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

// Unrowed 0x0044C0A8 (pinned; as AptLanLobby::MpOwnerPrintMessage uses it)
// and the flag it is skipped under.
void Rva0044C0A8(UnicodeString title, UnicodeString text, void *callback);
// The peer thread request (layout of Rva005A8666BoxNat.cpp): type +0x00,
// nick +0x04, id +0x34, options +0x40, the staging-room flag +0x118.
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
	// Request type 11 uses the DWORD; kick and option requests use its flag.
	union { bool isStagingRoom; int gameID; }; // +0x118
	unsigned char m_tail[0x1EC - 0x11C];
};

// TheGameSpyPeerMessageQueue 0x00A02340: addRequest is virtual slot 6.
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
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// The screen's owner at +0x58 keeps its Apt movie at +0x274.
struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
};

// The screen's game-mode preferences (GameModePreferences.cpp; vslot 3 is
// write, as in AptLanLobby).
#include "../../../../../Include/Common/GameModePreferences.h"

// Address-named views the buddy invite uses: the screen's state test
// (0x0059EF33, state 6 or 12), the room's +0xFDC string (0x0059F340) and
// the invite record's five-field setter (0x0059EF62).
UnicodeString GadgetTextEntryGetText(GameWindow *window); // rowed 0x00320AAB

// The +0x70 panel's rowed 0x0043DBCA test and the screen's state-2 action
// 0x005A5B38 (address-named views).
// InitGadgets' helpers: the +0x450 preferences loader (rowed 0x00580316),
// the +0x70 panel's reset (AptMpGameSetup 0x0043DE19), the screen closer
// (0x0041149A) and the full object's 0x0052493F.
class Rva00580316
{
public:
	void rva00580316(void *prefs);
};

void _bfme_closeAptScreen(const AsciiString &name);

// The screen's full object, as the placeholder row 0x0059F950 names it.
class Rva0059F950
{
public:
	void rva0059F950();
};

// The +0x70 game setup panel: PlayerTemplate enables it after a host
// change (rowed 0x0043DB47: bytes +0x2B9 and +0x2BA) and UpdatePings sets
// each slot's connection icon through AptMpGameSetup 0x0043E5C1.
class Rva0043DB47DoubleSetter
{
public:
	void enable();

	char m_lead[0x7C];
    int m_7c; // full screen +0xEC, MpOwner-relative +0x8C
    char m_middle[0x2B9 - 0x80];
	unsigned char m_a;
	unsigned char m_b;
};

#include "../../../../../Include/GameClient/AptMpGameSetup.h"

// The NAT negotiator at 0x00A063F8 keeps its port negotiation at +0x28.
struct Elem005DB98E { float rva005DB95B(); };

#include "../../../../../Include/GameClient/PortNegotiationSchema.h"

class Rva005A6D47
{
public:
	unsigned char m_pad00[0x10];
	int m_10;					   // +0x10, zero when idle
	unsigned char m_pad14[0x28 - 0x14];
	PortNegotiationSchema m_schema; // +0x28
};

// Bind the existing NAT datum; retain this unit's access view at use sites.
struct NAT;
extern NAT *TheNAT;

#include "../../../../../Include/GameClient/AptConnectionScreen.h"

int Rva005DB335Get(int ping); // rowed 0x005DB335

// The screen's primary base: the vtable whose slot 10 gives the Apt path,
// and the owner at +0x58.
class CustomMatchScreen
{
public:
	virtual void v00(); virtual void v01();
	// Slot 2 of vftable 0x00871414 (WorldBuilder and the retail string
	// "AptOnlineCustomMatch::InitGadgets").
	virtual void InitGadgets();
	virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	// Slots 8 and 9 of vftable 0x00871414 (unnamed in WorldBuilder).
	virtual bool rva0059EF49();
	virtual bool rva005A6697();
	// vslot 10: the screen's Apt path for its callbacks.
	virtual const char *v10();

protected:
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x60 - 0x5C];
};

// The multiplayer owner interface at +0x60. Target facts: vftable
// 0x008713B8 (slot 0 is a sub-ecx-0x60 deleting thunk; the same bodies fill
// 0x00873CD8 and 0x00873D70), and its bodies reach the screen at this-0x60.
// Slot names are WorldBuilder's where it names the body.
class MpOwner
{
public:
	virtual ~MpOwner();													   // 0
	virtual bool rva0059EBDE() = 0;										   // 1
	virtual void rva0059EBFE() = 0;										   // 2
	virtual bool MpOwnerOnReadyChecked(bool ready) = 0;					   // 3
	virtual bool MpOwnerSelectColor(GameSlot *slot, int color) = 0;		   // 4
	virtual bool MpOwnerSelectHandicap(GameSlot *slot, int handicap) = 0;	 // 5
	virtual bool MpOwnerSelectHero(GameSlot *slot) = 0;					   // 6
	virtual bool MpOwnerSelectMap(const AsciiString &mapName) = 0;			// 7
	virtual void MpOwnerSelectStrategicScenario() = 0;						// 8
	virtual bool MpOwnerSelectPlayer(GameSlot *slot, int state, int unused) = 0; // 9
	virtual bool MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate) = 0; // 10
	virtual bool MpOwnerSelectStartPosition(GameSlot *slot, int startPos) = 0; // 11
	virtual bool MpOwnerSelectTeam(GameSlot *slot, int team) = 0;			 // 12
	virtual bool MpOwnerSetClanID(GameSlot *slot, const UnicodeString &clanID) = 0; // 13
	virtual void MpOwnerGetLocalPlayerName(UnicodeString &name) = 0;		  // 14
	virtual void rva005A1D32() = 0;										   // 15
	virtual void rva005A1C87(bool open) = 0;								  // 16
	virtual void MpOwnerPrintMessage(const UnicodeString &text, int kind) = 0; // 17
	virtual void v18() = 0;												   // 18
	virtual void MpOwnerUpdatePlayerTooltip(GameSlot *slot) = 0;							// 19
	virtual void *v20() = 0;												  // 20
	virtual int v21() = 0;													// 21
	virtual bool rva0059EC50() = 0;										   // 22

private:
	unsigned char m_pad04[0x0C - 0x04];
};

class AptOnlineCustomMatch : public CustomMatchScreen, public MpOwner
{
public:
	void PlayGame(const char *unused);
	void LoadGame(const char *unused);
	void CancelPopUpCreate(const char *unused);
	void CancelPopUpHost(const char *unused);
	void OnOpenConnectionsScreen(const char *unused);
	void OnClosingConnectionsScreen(const char *unused);
	void Refresh(const char *unused);
	// Bound as "AptOnline::OnOpenCreateDialog" on this screen.
	void OnOpenCreateDialog(const char *unused);

	virtual bool rva0059EBDE();
	virtual bool MpOwnerOnReadyChecked(bool ready);
	// MpOwnerSelectColor 0x005A0F4B (slot 4) is banked:
	// reverse/attempts/0x005a0f4b.cpp.
	virtual bool MpOwnerSelectHandicap(GameSlot *slot, int handicap);
	virtual bool MpOwnerSelectHero(GameSlot *slot);
	virtual bool MpOwnerSelectMap(const AsciiString &mapName);
	virtual bool MpOwnerSelectPlayer(GameSlot *slot, int state, int unused);
	virtual bool MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate);
	virtual bool MpOwnerSelectStartPosition(GameSlot *slot, int startPos);
	virtual bool MpOwnerSelectTeam(GameSlot *slot, int team);
	virtual bool MpOwnerSetClanID(GameSlot *slot, const UnicodeString &clanID);
	virtual void rva005A1D32();
	virtual void MpOwnerPrintMessage(const UnicodeString &text, int kind);
    virtual void MpOwnerUpdatePlayerTooltip(GameSlot *slot);

	virtual void rva005A1C87(bool open);
	virtual void rva0059EBFE();
	virtual bool rva0059EC50();
	virtual void InitGadgets();
	virtual bool rva0059EF49();
	virtual bool rva005A6697();

	GameSpyStagingRoom *GetGameToJoin();
	bool RequestJoinGame(const char *password);
	void OpenConnectionScreen(bool open);
	// FillBuddyInviteGameInfo 0x0059FB4F is banked: reverse/attempts/0x0059fb4f.cpp.
	// UpdatePings 0x0059ED8B is banked: reverse/attempts/0x0059ed8b.cpp.

	// Rowed 0x005A0DC2 (339 bytes; ret 4), named by WorldBuilder.
	void FillGameNameTextEntry(bool flag);

	// Unrowed 0x005A0D61 (97 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0D61(bool force);

private:
	// Everything after the screen's own state that the full object refreshes
	// when the local slot changes (placeholder row 0x0059F950).
	void RefreshScreen() { ((Rva0059F950 *)this)->rva0059F950(); }

	unsigned char m_pad06c[0x70 - 0x6C];
	Rva0043DB47DoubleSetter m_70; // +0x70
	unsigned char m_pad32b[0x450 - (0x70 + sizeof(Rva0043DB47DoubleSetter))];
	Rva00580316 m_prefsLoader; // +0x450
	unsigned char m_pad451[0x46C - 0x451];
	GameModePreferences m_prefs; // +0x46C
	int m_state; // +0x488
	int m_48c; // +0x48C
	int m_490; // +0x490
	int m_494; // +0x494
	GameWindow *m_textentryGameName; // +0x498; WB +0x490 assert names this field
	GameWindow *m_createDialog; // +0x49C
	bool m_popUp; // +0x4A0
	unsigned char m_pad4a1[0x4A4 - 0x4A1];
	unsigned int m_4a4; // +0x4A4, passed first to the invite record
	int m_4a8;
	unsigned char m_pad4ac[0x4B0 - 0x4AC];
	int m_4b0; // +0x4B0
	unsigned char m_pad4b4[0x4B8 - 0x4B4];
	int m_gameToJoinID;
	int m_connectingCount; // +0x4BC, open requests of the connecting pop-up
	unsigned char m_pad4c0[2];
	bool m_4c2; // +0x4C2
	unsigned char m_pad4c3[0x4D4 - 0x4C3];
	AptConnectionScreen *m_connectionGrid; // +0x4D4
	bool m_connectionsScreen; // +0x4D8
};

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

UnicodeString Rva0059F12A(int rank);

void GadgetTextEntrySetText(GameWindow *, UnicodeString);
struct RGBColor;
#include "../../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
// Existing 52-byte rank-table globals defined by Rva005B8116Stats.cpp.
class Rva00559D0CRankWeights;
extern Rva00559D0CRankWeights g_00E05FCC;
extern Rva00559D0CRankWeights g_00E06000;
extern const char *g_rva0033A3F4Table[7];
UnicodeString Rva00559CE5(int side, int rank);

void AptOnlineCustomMatch::MpOwnerUpdatePlayerTooltip(GameSlot *slot)
{
    if (!TheGameSpyInfo)
        return;
    GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
    if (!room || !slot->gameSpySlot())
        return;
    if (!slot->isHuman()) {
        TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
        return;
    }
    UnicodeString uName(slot->m_name);
    AsciiString name;
    name.translate(uName);
    PlayerInfo *info = TheGameSpyInfo->rva00382CCE(name.str());
    if (info) {
        int profileID = info->m_at14;
        bool isLocal = slot == room->getGameSpySlot(room->getLocalSlotNum());
        AsciiString localeIdentifier;
        localeIdentifier.format("WOL:Locale%2.2d", atoi(info->m_at08.str()));
        UnicodeString playerInfo;
        int wins = 0;
        int losses = 0;
        int ping = 0;
        const int &w = info->m_at0c;
        const int &l = info->m_at10;
        wins = info->m_at0c;
        losses = info->m_at10;
        UnicodeString favoriteSide;
        int totalGames = 0;
        int side = 0;
        totalGames = w + l;
        side = info->m_at2c;
        if (!totalGames)
            favoriteSide = TheGameText->fetch("APT:Men");
        else {
            AsciiString sideKey;
            sideKey.format("SIDE:%s", g_rva0033A3F4Table[side]);
            favoriteSide = TheGameText->fetch(sideKey);
        }
        bool firstMode = m_70.m_7c == 1;
        const int *thresholds = firstMode ? (const int *)&g_00E05FCC : (const int *)&g_00E06000;
        int rankSide = info->m_at28;
        int points = info->m_at1c;
        int rank;
        for (rank = 1; rank < 11; ++rank)
            if (points < thresholds[rank])
                break;
        UnicodeString rankText = Rva00559CE5(rankSide, rank - 1);
        UnicodeString rank20;
        UnicodeString rank24;
        // WB has this inner check even though the enclosing arm proved info.
        if (info) {
            rank20 = Rva0059F12A(info->m_at20);
            rank24 = Rva0059F12A(info->m_at24);
        } else {
            rank20 = Rva0059F12A(-1);
            rank24 = Rva0059F12A(-1);
        }
        if (isLocal)
            ping = slot->gameSpySlot()->m_ping;
        else {
            unsigned short slotIndex = 0;
            for (int i = 0; i < 8; ++i) {
                if (slot == room->getGameSpySlot(i)) {
                    slotIndex = (unsigned short)i;
                    break;
                }
            }
            if (slotIndex >= 8 || !TheNAT)
                return;
            PortNegotiationSchema &schema = ((Rva005A6D47 *)TheNAT)->m_schema;
            if (schema.GetConnectionState((unsigned short)room->getLocalSlotNum(), slotIndex) == 3)
                ping = (int)((Elem005DB98E *)schema.peekPing((unsigned short)room->getLocalSlotNum(), slotIndex))->rva005DB95B();
            else
                ping = -1;
        }
        UnicodeString pingString;
        if (ping <= 0)
            pingString.set((const unsigned short *)L"-");
        else
            pingString.format((const unsigned short *)L"%d", ping);
        playerInfo.format(TheGameText->fetchPtr("TOOLTIP:StagingPlayerInfo"),
            TheGameText->fetch(localeIdentifier).str(), rankText.str(), pingString.str(),
            wins, losses, favoriteSide.str(), rank20.str(), rank24.str());
        UnicodeString tooltip = UnicodeString::TheEmptyString;
        if (isLocal)
            tooltip.format(TheGameText->fetchPtr("TOOLTIP:LocalPlayer"), uName.str());
        else if (TheGameSpyInfo->getBuddyMap()->find(profileID) != TheGameSpyInfo->getBuddyMap()->end())
            tooltip.format(TheGameText->fetchPtr("TOOLTIP:BuddyPlayer"), uName.str());
        else if (profileID)
            tooltip.format(TheGameText->fetchPtr("TOOLTIP:ProfiledPlayer"), uName.str());
        else
            tooltip.format(TheGameText->fetchPtr("TOOLTIP:GenericPlayer"), uName.str());
        tooltip.concat(playerInfo);
        TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
        return;
    }
    TheMouse->rva001EEA6D(uName, -1, 0, 1.5f);
}
