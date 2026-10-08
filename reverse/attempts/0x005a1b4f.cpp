// ?rva005A1B4F@AptOnlineCustomMatch@@UAEX_NH@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's online custom match screen Apt callbacks, 0x0059EC65 onward,
// bound by these names ("AptOnline::CustomMatch::PlayGame" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The scope and class are named for the strings. +0x488 is the
// screen's state.

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>
#include <vector>

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

// The connecting pop-up's per-slot name and status lines (rowed 0x0059F20B
// and 0x0059F296).
void Rva0059F20BSet(int slot, const UnicodeString &text);
void Rva0059F296Set(int slot, const UnicodeString &text);
void __cdecl Rva00434160Init(int a, int b, bool c);

// The game slot the owner menus edit. Target facts: Team writes +0x1C;
// the host's name (slot 0) is the UnicodeString at +0x30 that
// AsciiString::translate 0x00038220 reads. encodeHero is the rowed
// 0x003FF16F.
struct GameSpySlotView
{
	unsigned char m_pad000[0x1BC];
	int m_ping; // +0x1BC
};

class GameSlot
{
public:
	virtual void reset();
	unsigned char encodeHero() const;
	bool isPlayer(AsciiString name) const;        // rowed 0x003FFEF5
	void rva003FF5F2(const AsciiString &clanID); // rowed 0x003FF5F2
	void setMapAvailability(bool available);      // rowed 0x003FF8A0
	void setPlayerTemplate(int playerTemplate);   // rowed 0x00400E33
	bool isHuman() const;                         // rowed 0x003FF0F1
	// Slot 6 (+0x18): the GameSpy view of the slot; its +0x1BC is the local
	// player's own ping.
	virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual GameSpySlotView *gameSpySlot();

	int m_state;                // +0x04
	unsigned char m_pad08[0x0C - 0x08];
	int m_color;                // +0x0C

	int m_startPos;             // +0x10, StartPos sends this one
	int m_startPos14;           // +0x14, written with it
	unsigned char m_pad18[0x1C - 0x18];
	int m_teamNumber;           // +0x1C
	int m_handicap;             // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	UnicodeString m_name;       // +0x30
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
	virtual void v08(); virtual void v09(); virtual void v10();
	// Slot 11 (+0x2C): slot 18 of the owner interface calls it with 0 after
	// copying a room into TheGameSpyGame.
	virtual void v11(int value);
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
	void setMap(AsciiString mapName);    // rowed 0x00400126

	unsigned char m_pad04[0x14 - 0x04];
	unsigned int m_14;                   // +0x14, the buddy invite's second field
	unsigned char m_pad18[0x5C - 0x18];
	unsigned int m_5c;                   // +0x5C, the buddy invite's last field
	int m_rules[10];                     // +0x60, saved as "Rules"
	unsigned char m_pad88[0xFF4 - 0x88];
	bool m_ff4;                          // +0xFF4
	int m_ff8;                           // +0xFF8
	void setMapCRC(unsigned int crc);    // rowed 0x00400E9F
	void setMapSize(unsigned int size);  // rowed 0x00400F5A
};

class GameSpyGameSlot : public GameSlot
{
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyGameSlot *getGameSpySlot(int index); // rowed 0x004FDA3D
};

// TheGameSpyGame 0x00A02324.
extern GameSpyStagingRoom *TheGameSpyGame;

// The map cache: the AsciiString-keyed map whose find worker is the pinned
// _M_find 0x001F8437; size at +0x28 and CRC at +0x2C of the value (as
// AptLanLobby::bfmeMapChanged reads them).
class MapMetaData
{
public:
	unsigned char m_pad00[0x28];
	unsigned int m_filesize; // +0x28
	unsigned int m_CRC;      // +0x2C
};

bool operator<(const AsciiString &left, const AsciiString &right);

class MapCache : public std::map<AsciiString, MapMetaData>
{
};

extern MapCache *TheMapCache;

// TheGameSpyInfo 0x00A02320: slot 29 (+0x74) returns an AsciiString as the
// BFME1 donor's getLocalName; slots 51 (+0xCC), 53 (+0xD4) and 55 (+0xDC)
// as the BFME1 donor's amIHost / getCurrentStagingRoom / setGameOptions.
class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28)
	virtual AsciiString getLocalName() = 0; // slot 29 (+0x74)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50)
	virtual bool amIHost() = 0;
	V(52)
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
	V(54)
	virtual void setGameOptions() = 0;
	V(56) V(57) V(58) V(59) V(60)
	// Slot 61 (+0xF4): text with a color (PrintMessage kinds 0 and 1).
	virtual void v61(UnicodeString text, int color) = 0;
	V(62) V(63) V(64)
	// Slot 65 (+0x104): text alone (PrintMessage kind 2).
	virtual void v65(UnicodeString text) = 0;
#undef V
};

extern GameSpyInfoInterface *TheGameSpyInfo;

// The online chat colors: 0x009B9198 and, inside the 148-byte table
// 0x009B91B4, the dword at +0x44 (0x009B91F8).
extern int g_00DB9198;
extern unsigned int g_00DB91B4;

// Unrowed 0x0044C0A8 (pinned; as AptLanLobby::MpOwnerPrintMessage uses it)
// and the flag it is skipped under.
void Rva0044C0A8(UnicodeString title, UnicodeString text, void *callback);
extern int g_Va00E046B8;

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
	union
	{
		bool isStagingRoom; // +0x118
		int payloadWord;    // +0x118, the word form request 0xF sets to -1
	};
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
class GameModePreferences
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	void rva0044DDFB(int *rules); // rowed 0x0044DDFB, "Rules"

private:
	unsigned char m_pad04[0x1C - 0x04];
};

// Address-named views the buddy invite uses: the screen's state test
// (0x0059EF33, state 6 or 12), the room's +0xFDC string (0x0059F340) and
// the invite record's five-field setter (0x0059EF62).
class Rva0059ECAD
{
public:
	unsigned char rva0059EF33() const;
};

class Rva0059F340AsciiField
{
public:
	AsciiString get() const;
};

class Rva0059EF62
{
public:
	void rva0059EF62(unsigned int a, unsigned int b, const AsciiString &password, const AsciiString &text, unsigned int c);
};

UnicodeString GadgetTextEntryGetText(GameWindow *window); // rowed 0x00320AAB

// The +0x70 panel's rowed 0x0043DBCA test and the screen's state-2 action
// 0x005A5B38 (address-named views).
class Rva0043DFE0
{
public:
	bool rva0043DBCA();
};

class Rva005A5B38Box
{
public:
	bool Run();
};

// InitGadgets' helpers: the +0x450 preferences loader (rowed 0x00580316),
// the +0x70 panel's reset (AptMpGameSetup 0x0043DE19), the screen closer
// (0x0041149A) and the full object's 0x0052493F.
class Rva00580316
{
public:
	void rva00580316(void *prefs);
};

void _bfme_closeAptScreen(const AsciiString &name);

class Rva0052493F
{
public:
	void rva0052493F();
};

// Slot 18's helpers: the unrowed 0x00387288 (pinned; WorldBuilder places
// it in PeerDefs.cpp) takes the room, and the placeholder-named staging
// room assignment 0x00382E73 copies it into TheGameSpyGame.
void Rva00387288(GameSpyStagingRoom *room);

class Rva00382E73
{
public:
	Rva00382E73 &operator=(const Rva00382E73 &o);
};

// The +0x70 panel viewed by its first two virtual slots.
class Rva005A1B4FPanel
{
public:
	virtual void v00();
	virtual void v01();
};

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

	char m_lead[0x2B9];
	unsigned char m_a;
	unsigned char m_b;
};

class AptMpGameSetup
{
public:
	void rva0043E5C1(int slot, int kind, int value);
	void rva0043DE19();
};

// The NAT negotiator at 0x00A063F8 keeps its port negotiation at +0x28.
struct Elem005DB98E;

class PortNegotiationSchema
{
public:
	int GetConnectionState(unsigned short localSlot, unsigned short slot); // rowed 0x005DB9BC
	void *peekPing(unsigned short localSlot, unsigned short slot); // rowed 0x005DB98E
};

class Rva005A6D47
{
public:
	unsigned char m_pad00[0x10];
	int m_10;                       // +0x10, zero when idle
	unsigned char m_pad14[0x28 - 0x14];
	PortNegotiationSchema m_schema; // +0x28
};

extern Rva005A6D47 *g_Va00E063F8;

class AptConnectionScreen
{
public:
	static int GetPingImageEnum(Elem005DB98E *ping); // rowed 0x005DB37C
};

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
	virtual ~MpOwner();                                                       // 0
	virtual bool rva0059EBDE() = 0;                                           // 1
	virtual void rva0059EBFE() = 0;                                           // 2
	virtual bool MpOwnerOnReadyChecked(bool ready) = 0;                       // 3
	virtual bool MpOwnerSelectColor(GameSlot *slot, int color) = 0;           // 4
	virtual bool MpOwnerSelectHandicap(GameSlot *slot, int handicap) = 0;     // 5
	virtual bool MpOwnerSelectHero(GameSlot *slot) = 0;                       // 6
	virtual bool MpOwnerSelectMap(const AsciiString &mapName) = 0;            // 7
	virtual void MpOwnerSelectStrategicScenario() = 0;                        // 8
	virtual bool MpOwnerSelectPlayer(GameSlot *slot, int state, int unused) = 0; // 9
	virtual bool MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate) = 0; // 10
	virtual bool MpOwnerSelectStartPosition(GameSlot *slot, int startPos) = 0; // 11
	virtual bool MpOwnerSelectTeam(GameSlot *slot, int team) = 0;             // 12
	virtual bool MpOwnerSetClanID(GameSlot *slot, const UnicodeString &clanID) = 0; // 13
	virtual void MpOwnerGetLocalPlayerName(UnicodeString &name) = 0;          // 14
	virtual void rva005A1D32() = 0;                                           // 15
	virtual void rva005A1C87(bool open) = 0;                                  // 16
	virtual void MpOwnerPrintMessage(const UnicodeString &text, int kind) = 0; // 17
	virtual void rva005A1B4F(bool accepted, int unused) = 0;                  // 18
	virtual void MpOwnerUpdatePlayerTooltip() = 0;                            // 19
	virtual void *v20() = 0;                                                  // 20
	virtual int v21() = 0;                                                    // 21
	virtual bool rva0059EC50() = 0;                                           // 22

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
	virtual bool MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate);
	virtual bool MpOwnerSelectStartPosition(GameSlot *slot, int startPos);
	virtual bool MpOwnerSelectTeam(GameSlot *slot, int team);
	virtual bool MpOwnerSetClanID(GameSlot *slot, const UnicodeString &clanID);
	virtual void rva005A1D32();
	virtual void MpOwnerPrintMessage(const UnicodeString &text, int kind);

	virtual void rva005A1C87(bool open);
	virtual void rva0059EBFE();
	virtual bool rva0059EC50();
	virtual void rva005A1B4F(bool accepted, int unused);
	virtual void InitGadgets();
	virtual bool rva0059EF49();
	virtual bool rva005A6697();

	void OpenConnectionScreen(bool open);
	// FillBuddyInviteGameInfo 0x0059FB4F is banked: reverse/attempts/0x0059fb4f.cpp.
	// UpdatePings 0x0059ED8B is banked: reverse/attempts/0x0059ed8b.cpp.

	// Unrowed 0x005A0DC2 (339 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0DC2(bool flag);

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
	int m_498; // +0x498
	GameWindow *m_createDialog; // +0x49C
	bool m_popUp; // +0x4A0
	unsigned char m_pad4a1[0x4A4 - 0x4A1];
	unsigned int m_4a4; // +0x4A4, passed first to the invite record
	unsigned char m_pad4a8[0x4B0 - 0x4A8];
	int m_4b0; // +0x4B0
	unsigned char m_pad4b4[0x4BC - 0x4B4];
	int m_connectingCount; // +0x4BC, open requests of the connecting pop-up
	unsigned char m_pad4c0[0x4D8 - 0x4C0];
	bool m_connectionsScreen; // +0x4D8
};

// Retail 0x0059EC65, 13 bytes: "AptOnline::CustomMatch::PlayGame".
void AptOnlineCustomMatch::PlayGame(const char *unused)
{
	m_state = 7;
}

// Retail 0x0059ECC1, 17 bytes: "AptOnline::CustomMatch::LoadGame".
void AptOnlineCustomMatch::LoadGame(const char *unused)
{
	Rva00434160Init(2, 16, false);
}

// Retail 0x0059ED18, 20 bytes: "AptOnline::CustomMatch::CancelPopUpCreate".
void AptOnlineCustomMatch::CancelPopUpCreate(const char *unused)
{
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED2C, 61 bytes: "AptOnline::CustomMatch::CancelPopUpHost"
// also tells the movie "ClosePassword".
void AptOnlineCustomMatch::CancelPopUpHost(const char *unused)
{
	void *movie = m_owner->m_movie;
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "ClosePassword");
	m_state = 1;
	m_popUp = false;
}

// Retail 0x0059ED69, 17 bytes: "AptOnline::CustomMatch::OnOpenConnectionsScreen".
void AptOnlineCustomMatch::OnOpenConnectionsScreen(const char *unused)
{
	if (!m_connectionsScreen)
		m_connectionsScreen = true;
}

// Retail 0x0059ED7A, 17 bytes: "AptOnline::CustomMatch::OnClosingConnectionsScreen".
void AptOnlineCustomMatch::OnClosingConnectionsScreen(const char *unused)
{
	if (m_connectionsScreen)
		m_connectionsScreen = false;
}

// Retail 0x005A0F15, 10 bytes: "AptOnline::CustomMatch::Refresh".
void AptOnlineCustomMatch::Refresh(const char *unused)
{
	rva005A0D61(true);
}

// Retail 0x005A0F1F, 44 bytes: bound as "AptOnline::OnOpenCreateDialog";
// focuses the +0x49C window and moves to state 3.
void AptOnlineCustomMatch::OnOpenCreateDialog(const char *unused)
{
	rva005A0DC2(true);
	TheWindowManager->winSetFocus(m_createDialog);
	m_state = 3;
}

// Retail 0x005A1281, 343 bytes (WorldBuilder name, AptOnlineCustomMatch.cpp
// line 1004; wb-name-unverified): asks the host for the slot's hero, as the
// BFME1 donor's applySlotTeam shape with "Hero=%d" of GameSlot::encodeHero.
bool AptOnlineCustomMatch::MpOwnerSelectHero(GameSlot *slot)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	room->resetAccepted();
	if (TheGameSpyInfo->amIHost())
	{
		TheGameSpyInfo->setGameOptions();
	}
	else
	{
		AsciiString options;
		options.format("Hero=%d", slot->encodeHero());
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	return true;
}

// Retail 0x005A13D8, 343 bytes (WorldBuilder name; wb-name-unverified): the
// BFME1 donor applySlotTeam (0x0053D170) with "Team=%d".
bool AptOnlineCustomMatch::MpOwnerSelectTeam(GameSlot *slot, int team)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	slot->m_teamNumber = team;
	room->resetAccepted();
	if (TheGameSpyInfo->amIHost())
	{
		TheGameSpyInfo->setGameOptions();
	}
	else
	{
		AsciiString options;
		options.format("Team=%d", team);
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	return true;
}

// Retail 0x005A152F, 350 bytes (WorldBuilder name; wb-name-unverified):
// "Handicap=%d" for the slot's +0x20; the host resets acceptance again
// before publishing the options.
bool AptOnlineCustomMatch::MpOwnerSelectHandicap(GameSlot *slot, int handicap)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	slot->m_handicap = handicap;
	room->resetAccepted();
	if (TheGameSpyInfo->amIHost())
	{
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
	}
	else
	{
		AsciiString options;
		options.format("Handicap=%d", handicap);
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	return true;
}

// Retail 0x005A186B, 341 bytes (WorldBuilder name; wb-name-unverified):
// "StartPos=%d"; the BFME1 donor is applySlotStartPos.
bool AptOnlineCustomMatch::MpOwnerSelectStartPosition(GameSlot *slot, int startPos)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	slot->m_startPos = startPos;
	slot->m_startPos14 = startPos;
	if (room->amIHost())
	{
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
	}
	else
	{
		AsciiString options;
		options.format("StartPos=%d", slot->m_startPos);
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	return true;
}

// Retail 0x005A19C0, 399 bytes (WorldBuilder name; wb-name-unverified):
// stores the translated clan ID through GameSlot 0x003FF5F2, then, when not
// hosting, asks the host "clanID=<id>" only for the local player's slot.
bool AptOnlineCustomMatch::MpOwnerSetClanID(GameSlot *slot, const UnicodeString &clanID)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	AsciiString clan;
	clan.translate(clanID);
	slot->rva003FF5F2(clan);
	room->resetAccepted();
	if (TheGameSpyInfo->amIHost())
	{
		TheGameSpyInfo->setGameOptions();
	}
	else
	{
		if (!slot->isPlayer(TheGameSpyInfo->getLocalName()))
			return false;

		AsciiString options("clanID=");
		options += clan;
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	return true;
}

// Retail 0x005A1DCE, 288 bytes (WorldBuilder name; wb-name-unverified): a
// joined player tells the host "READY" / "UNREADY" (options "true").
bool AptOnlineCustomMatch::MpOwnerOnReadyChecked(bool ready)
{
	if (TheGameSpyInfo->amIHost())
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;

	UnicodeString hostName(room->getSlot(0)->m_name);
	AsciiString asciiName;
	asciiName.translate(hostName);

	PeerRequest req;
	req.peerRequestType = 0xD;
	req.isStagingRoom = true;
	req.options = "true";
	req.id = ready ? "READY" : "UNREADY";
	req.nick = asciiName.str();
	TheGameSpyPeerMessageQueue->addRequest(req);
	return true;
}

// Retail 0x0059F043, 180 bytes (WorldBuilder name; wb-name-unverified): the
// staging room counterpart of AptLanLobby::MpOwnerPrintMessage 0x004448E5.
void AptOnlineCustomMatch::MpOwnerPrintMessage(const UnicodeString &text, int kind)
{
	if (!TheGameSpyInfo)
		return;

	switch (kind)
	{
	case 0:
		TheGameSpyInfo->v61(text, g_00DB9198);
		break;
	case 1:
		if (!g_Va00E046B8)
			Rva0044C0A8(UnicodeString(L""), text, 0);
		TheGameSpyInfo->v61(text, (&g_00DB91B4)[17]);
		break;
	case 2:
		TheGameSpyInfo->v65(text);
		break;
	}
}

// Retail 0x005A0B7E, 240 bytes (WorldBuilder name; wb-name-unverified): the
// host's map change, the staging room counterpart of
// AptLanLobby::bfmeMapChanged 0x00444F9C.
bool AptOnlineCustomMatch::MpOwnerSelectMap(const AsciiString &mapName)
{
	if (!TheGameSpyInfo)
		return false;
	if (!TheGameSpyGame)
		return false;

	AsciiString lowerMap = mapName;
	lowerMap.toLower();
	TheGameSpyGame->setMap(lowerMap);
	MapCache::iterator it = TheMapCache->find(lowerMap);
	if (it != TheMapCache->end())
	{
		TheGameSpyGame->getGameSpySlot(0)->setMapAvailability(true);
		TheGameSpyGame->setMapCRC(it->second.m_CRC);
		TheGameSpyGame->setMapSize(it->second.m_filesize);
	}
	TheGameSpyGame->adjustSlotsForMap();
	TheGameSpyGame->resetAccepted();
	TheGameSpyGame->resetStartSpots();
	TheGameSpyInfo->setGameOptions();
	return true;
}

// Retail 0x0059EBDE, 32 bytes, vftable 0x008713B8 slot 1 (unnamed in
// WorldBuilder): whether the current staging room says this player hosts.
bool AptOnlineCustomMatch::rva0059EBDE()
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;
	return room->amIHost();
}

// Retail 0x005A1D32, 156 bytes, vftable 0x008713B8 slot 15 (unnamed in
// WorldBuilder): the host posts request 0xE "EUI/" with options "true".
void AptOnlineCustomMatch::rva005A1D32()
{
	if (TheGameSpyPeerMessageQueue && TheGameSpyInfo && TheGameSpyInfo->amIHost())
	{
		PeerRequest req;
		req.peerRequestType = 0xE;
		req.isStagingRoom = true;
		req.id = "EUI/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
}

// Retail 0x005A10DA, 423 bytes (WorldBuilder name; wb-name-unverified):
// "PlayerTemplate=%d"; the host also enables the +0x70 member.
bool AptOnlineCustomMatch::MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;
	if (room->getLocalSlotNum() < 0)
		return false;

	slot->setPlayerTemplate(playerTemplate);
	room->resetAccepted();
	if (TheGameSpyInfo->amIHost())
	{
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
		m_70.enable();
	}
	else
	{
		AsciiString options;
		options.format("PlayerTemplate=%d", playerTemplate);
		AsciiString hostName;
		hostName.translate(room->getSlot(0)->m_name);

		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = hostName.str();
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
	if (slot->m_name.compare(room->getSlot(room->getLocalSlotNum())->m_name) == 0)
		RefreshScreen();
	return true;
}

// Retail 0x0059F37C, 253 bytes (WorldBuilder name; wb-name-unverified):
// counts open requests of the connecting pop-up; the first clears the eight
// slot lines and opens it, the last close closes it.
void AptOnlineCustomMatch::OpenConnectionScreen(bool open)
{
	if (!g_bfmeAptWindowManager)
		return;

	if (open)
	{
		if (m_connectingCount == 0)
		{
			for (int i = 0; i < 8; ++i)
			{
				Rva0059F20BSet(i, UnicodeString((const unsigned short *)L" "));
				Rva0059F296Set(i, UnicodeString((const unsigned short *)L" "));
			}
			void *movie = m_owner->m_movie;
			Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "PopUpConnectingOpen");
		}
		++m_connectingCount;
	}
	else if (m_connectingCount != 0)
	{
		if (--m_connectingCount == 0)
		{
			void *movie = m_owner->m_movie;
			Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "PopUpConnectingClose");
		}
	}
}

// Retail 0x005A1C87, 171 bytes, vftable 0x008713B8 slot 16 (unnamed in
// WorldBuilder): opens or closes the connecting pop-up; a host opening it
// also posts request 0xE "DUI/" with options "true".
void AptOnlineCustomMatch::rva005A1C87(bool open)
{
	OpenConnectionScreen(open);
	if (open && TheGameSpyInfo->amIHost() && TheGameSpyPeerMessageQueue)
	{
		PeerRequest req;
		req.peerRequestType = 0xE;
		req.isStagingRoom = true;
		req.id = "DUI/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
}

// Retail 0x0059EBFE, 82 bytes, vftable 0x008713B8 slot 2 (unnamed in
// WorldBuilder): publishes the game options and, on the host, saves the
// room's ten rule ints through GameModePreferences "Rules" -- the staging
// room counterpart of AptLanLobby's slot 2 (0x00444279).
void AptOnlineCustomMatch::rva0059EBFE()
{
	if (!TheGameSpyInfo)
		return;
	TheGameSpyInfo->setGameOptions();
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (room && room->amIHost())
	{
		m_prefs.rva0044DDFB(room->m_rules);
		m_prefs.write();
	}
}

// Retail 0x0059EC50, 21 bytes, vftable 0x008713B8 slot 22 (unnamed in
// WorldBuilder): whether the NAT negotiator 0x00A063F8 exists and is idle.
bool AptOnlineCustomMatch::rva0059EC50()
{
	if (g_Va00E063F8 && g_Va00E063F8->m_10 == 0)
		return true;
	return false;
}

// Retail 0x0059EF49, 14 bytes, vftable 0x00871414 slot 8 (unnamed in
// WorldBuilder): the negation of the +0x70 panel's 0x0043DBCA test.
bool AptOnlineCustomMatch::rva0059EF49()
{
	return !((Rva0043DFE0 *)&m_70)->rva0043DBCA();
}

// Retail 0x005A6697, 33 bytes, vftable 0x00871414 slot 9 (unnamed in
// WorldBuilder): in state 2 runs 0x005A5B38; states 0 and 1 stay; any other
// state falls back to 1.
bool AptOnlineCustomMatch::rva005A6697()
{
	switch (m_state)
	{
	case 0:
		return false;
	case 1:
		return false;
	case 2:
		return ((Rva005A5B38Box *)this)->Run();
	default:
		m_state = 1;
		return false;
	}
}

// Retail 0x0059EFA0, 163 bytes: AptOnlineCustomMatch::InitGadgets (the
// retail string names it), vftable 0x00871414 slot 2.
void AptOnlineCustomMatch::InitGadgets()
{
	m_prefsLoader.rva00580316(&m_prefs);
	m_prefs.write();
	((AptMpGameSetup *)&m_70)->rva0043DE19();
	m_4b0 = 0;
	if (TheWindowManager)
		TheWindowManager->pad45();
	_bfme_closeAptScreen(AsciiString("AptOnlineCustomMatch::InitGadgets"));
	m_48c = 0;
	m_490 = 0;
	m_494 = 0;
	m_498 = 0;
	m_createDialog = 0;
	((Rva0052493F *)this)->rva0052493F();
}

// Retail 0x005A1B4F, 312 bytes, vftable 0x008713B8 slot 18 (unnamed in
// WorldBuilder): moves to state 14; when accepted, sets the room's +0xFF4 /
// +0xFF8 from its rule word +0x64, refreshes the panel and screen, posts
// request 0xF and adopts the room as TheGameSpyGame; otherwise posts
// request 0xE "HWS/" with options "true".
void AptOnlineCustomMatch::rva005A1B4F(bool accepted, int unused)
{
	m_state = 14;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (accepted)
	{
		if (room->m_rules[1])
		{
			room->m_ff4 = true;
			room->m_ff8 = 3;
		}
		else
		{
			room->m_ff4 = false;
			room->m_ff8 = 0;
		}
		((Rva005A1B4FPanel *)&m_70)->v01();
		RefreshScreen();

		PeerRequest req;
		req.peerRequestType = 0xF;
		req.payloadWord = -1;
		TheGameSpyPeerMessageQueue->addRequest(req);
		Rva00387288(room);
		*(Rva00382E73 *)TheGameSpyGame = *(Rva00382E73 *)room;
		TheGameSpyGame->v11(0);
	}
	else
	{
		PeerRequest req;
		req.peerRequestType = 0xE;
		req.isStagingRoom = true;
		req.id = "HWS/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
	}
}
