// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
//
// BFME2's online custom match screen Apt callbacks, 0x0059EC65 onward,
// bound by these names ("AptOnline::CustomMatch::PlayGame" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is AptOnlineCustomMatch (retail string
// "AptOnlineCustomMatch::InitGadgets"; the "AptOnline::CustomMatch::" names
// are Apt binding strings, not the C++ scope). +0x488 is the screen's state.

#include "ascii_string.h"
#include "unicode_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <functional>
// Retail's out-of-line less<int>::operator() is the speed-form copy other units emit;
// this /O1 unit inlines it but, imported, emits no copy of its own.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &x, const int &y) const { return x < y; }
}
#include <map>
#include <string>
#include <vector>
#include <windows.h>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null(unsigned short *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null_aux(unsigned short *, __true_type const &); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void __char_traits_base<unsigned short, unsigned short>::assign(unsigned short &, unsigned short const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > & basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::assign(unsigned short const *, unsigned short const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::copy(unsigned short *, unsigned short const *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::erase(unsigned short *, unsigned short *); }
namespace _STL { template <> unsigned int __char_traits_base<unsigned short, unsigned short>::length(unsigned short const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::move(unsigned short *, unsigned short const *, unsigned int); }
// bfme link decl-only end

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
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
struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : nat(0), port(0) {}
	unsigned int nat;
	unsigned short port;
};
struct NAT { void processPlayerLeave(int); };

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
	// Slots 8 and 9 (+0x20, +0x24): the room list enables joining while
	// they differ (Zero Hour's player counts; address-derived names).
	virtual int v08(); virtual int v09(); virtual void v10(); virtual void v11();
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

	unsigned char m_pad04[0x11 - 0x04];
	bool m_11;						   // +0x11, tested before a state-14 launch
	unsigned char m_pad12[0x14 - 0x12];
	unsigned int m_14;				   // +0x14, the buddy invite's second field
	unsigned char m_pad18[0x38 - 0x18];
	// +0x38: an 8-byte address pair the custom match fills from
	// TheGameSpyInfo vslots 85 and 86 when it creates the NAT (retail copies
	// it through an 8-byte local whose first dword it forwards).
	struct Address38 { int ip; unsigned short port; } m_38;
	unsigned char m_pad40[0x5C - 0x40];
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
	void launchWOTRMPGame(); // rowed 0x004FE126
	void launchGame();		 // rowed 0x004FED35
	// RequestJoinGame copies this WORD between complete staging-room objects.
	unsigned char m_pad88[0xFED - 0x88];
	bool m_fed; // +0xFED, set when the host creates the room
	unsigned char m_padfee[0x1008 - 0xFEE];
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

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;

// Unrowed 0x0044C0A8 (pinned; as AptLanLobby::MpOwnerPrintMessage uses it)
// and the flag it is skipped under.
void MessageBoxOk(UnicodeString title, UnicodeString text, void (*callback)());
extern int g_Va00E046B8;

// TheWritableGlobalData's version block at +0xB08 copies itself into a
// creation request (rowed 0x00237E28).
class Rva00237E28
{
public:
	void rva00237E28(Rva00237E28 *out);
	unsigned char m_data[0x10];
};

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
	union
	{
		bool isStagingRoom;
		int gameID;
		// Type 9, staging-room creation (Zero Hour's stagingRoomCreation
		// plus BFME fields; names after the donor where it has them).
		struct
		{
			Rva00237E28 version;		  // +0x118, TheWritableGlobalData +0xB08
			unsigned int exeCRC;		  // +0x128
			unsigned int iniCRC;		  // +0x12C
			unsigned char ladderKey[16];  // +0x130
			int gameVersion;			  // +0x140, TheGameSpyInfo vslot 85
			bool allowObservers;		  // +0x144
			unsigned short ladPort;	   // +0x146
			unsigned char m_148[4];
			bool restrictGameList;		// +0x14C
			int mapValue;				 // +0x150, the map cache entry's +0x20
			unsigned char m_154[0x1E4 - 0x154];
			int localSlot;				// +0x1E4
		} creation;
		unsigned char m_raw[0x1EC - 0x118];
	};
};

// The peer thread response (PeerThreadRetail.h layout): type +0x00, the
// disconnect reason at +0x10C, 0x348 bytes; rowed ctor 0x00389F77, dtor
// 0x0038A063.
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	enum { PEERRESPONSE_LOGIN, PEERRESPONSE_DISCONNECT };
	int peerResponseType;
	unsigned char m_pad004[0x10C - 0x04];
	union
	{
		unsigned int unknown_payload[143];
		struct { int reason; } discon;
	};
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
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual bool getResponse(PeerResponse &response) = 0; // slot 9 (+0x24)
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// The screen's owner at +0x58 keeps its Apt movie at +0x274.
struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
	unsigned char m_pad278[0x2B0 - 0x278];
	int m_2b0; // +0x2B0, nonzero while its pending reset (0x005170CD) is due
};

// The screen's game-mode preferences (GameModePreferences.cpp; vslot 3 is
// write, as in AptLanLobby).
#include "../../../../../Include/Common/GameModePreferences.h"

// Address-named views the buddy invite uses: the screen's state test
// (0x0059EF33, state 6 or 12), the room's +0xFDC string (0x0059F340) and
// the invite record's five-field setter (0x0059EF62).
class Rva0059ECAD
{
public:
	unsigned char rva0059EF33() const;
	void rva0059ECAD(int password); // rowed 0x0059ECAD, the join request
};

UnicodeString GadgetTextEntryGetText(GameWindow *window); // rowed 0x00320AAB

// The +0x70 panel's rowed 0x0043DBCA test and the screen's state-2 action
// 0x005A5B38 (address-named views).
class Rva005A5B38Box
{
public:
	bool Run();
	void DoRefresh(int ladder, void *password); // pinned 0x005A51B9
};

void GadgetComboBoxGetSelectedPos(GameWindow *window, int *pos);	   // rowed 0x003228EB
void *GadgetComboBoxGetItemData(GameWindow *window, int pos);		  // rowed 0x00322981
void *GadgetListBoxGetItemData(GameWindow *window, int row, int column); // rowed 0x003253BE
void Rva003B3371Call(int value);									   // rowed 0x003B3371

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
	int m_7c; // +0x7C (+0xEC of the screen), the local slot a created room records
	char m_lead80[0x2B0 - 0x80];
	// +0x2B0 (+0x320 of the screen): the selected ladder, whose 16-byte key
	// at +0xDAC a created room carries; state 0 waits for it.
	struct Ladder { unsigned char m_pad[0xDAC]; unsigned char m_key[16]; } *m_ladder;
	char m_lead2b4[0x2B9 - 0x2B4];
	unsigned char m_a;
	unsigned char m_b;
};

#include "../../../../../Include/GameClient/AptMpGameSetup.h"

// The NAT negotiator at 0x00A063F8 keeps its port negotiation at +0x28.
struct Elem005DB98E;

// The screen's +0x6C observer base and the NAT's observer list (rowed
// append 0x005A0B4C).
struct Rva002BA8F1Listener
{
	void *m_vptr;
};

#include "../../../../../Include/Common/Rva005A0B4CList.h"

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
	int m_10;					   // +0x10, zero when idle
	unsigned char m_pad14[0x28 - 0x14];
	PortNegotiationSchema m_schema; // +0x28
	unsigned char m_pad29[0x2C - 0x29];
	Rva005A0B4CList m_observers; // +0x2C (WB Observable<PortNegotiationSchemaObserver>)
	int rva005A8F57(); // rowed 0x005A8F57, the per-frame negotiation step
};

// The NAT the custom match creates in state 12 (0x974 bytes, rowed ctor
// 0x005A721C); it is stored into TheNAT.
// TheNAT 0x00A063F8, read through the Rva005A6D47 view.
extern NAT *TheNAT;

class AptConnectionScreen
{
public:
	void RedrawGrid(const char *);
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
	// Slot 3 of vftable 0x00871414: the per-frame update (WB unnamed).
	virtual void Update();
	virtual void v04();
	// Slot 5: the screen's window-message handler (msg, mData1, mData2 as in
	// Zero Hour's WOLLobbyMenuSystem; the window argument is unused).
	virtual int GameWindowSystem(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
	virtual void v06(); virtual void v07();
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
	virtual void MpOwnerUpdatePlayerTooltip() = 0;							// 19
	virtual void *v20() = 0;												  // 20
	virtual int v21() = 0;													// 21
	virtual bool rva0059EC50() = 0;										   // 22

private:
	unsigned char m_pad04[0x0C - 0x04];
};

template <class T> static inline volatile T &__vref(T &x){return (volatile T &)x;}
class AptOnlineCustomMatch : public CustomMatchScreen, public MpOwner
{
public:
	void PlayGame(const char *unused);
	void rva005A5BAF();	// 0x005A5BAF (Rva005A5BAFCheck.cpp)
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
	// UpdatePings 0x0059ED8B is defined below.

	// Rowed 0x005A0DC2 (339 bytes; ret 4), named by WorldBuilder.
	void FillGameNameTextEntry(bool flag);

	// Unrowed 0x005A0D61 (97 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0D61(bool force);

	virtual void Update();
	virtual int GameWindowSystem(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
	void UpdatePings();					 // 0x0059ED8B
	void PopulateGamesListBox();		 // rowed 0x005A061B
	void rva005A2899();					 // unrowed 0x005A2899 (990 bytes), pinned
	bool rva005A1EEE();					 // rowed 0x005A1EEE
	void UpdateHostStartGameButton();	   // rowed 0x0059EEE2
	void rva0059EE96(unsigned char a, unsigned char b); // rowed 0x0059EE96
	bool rva005A57BA(bool flag);			// rowed 0x005A57BA

private:
	// Everything after the screen's own state that the full object refreshes
	// when the local slot changes (placeholder row 0x0059F950).
	void RefreshScreen() { ((Rva0059F950 *)this)->rva0059F950(); }

	Rva002BA8F1Listener m_observer; // +0x6C
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
	bool m_joinEnabled; // +0x4C0, the join button's last Apt state
	unsigned char m_pad4c1;
	bool m_4c2; // +0x4C2
	unsigned char m_pad4c3[0x4D4 - 0x4C3];
	AptConnectionScreen *m_connectionGrid; // +0x4D4
	bool m_connectionsScreen; // +0x4D8
	unsigned char m_pad4d9[0x4DC - 0x4D9];
	unsigned int m_inviteTime; // +0x4DC, timeGetTime when the buddy invite went out
};

// Retail 0x0059EC65, 13 bytes: "AptOnline::CustomMatch::PlayGame".
// AptOnlineCustomMatch::PlayGame is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059ECC1, 17 bytes: "AptOnline::CustomMatch::LoadGame".
// AptOnlineCustomMatch::LoadGame is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059ED18, 20 bytes: "AptOnline::CustomMatch::CancelPopUpCreate".
// AptOnlineCustomMatch::CancelPopUpCreate is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059ED2C, 61 bytes: "AptOnline::CustomMatch::CancelPopUpHost"
// also tells the movie "ClosePassword".
// AptOnlineCustomMatch::CancelPopUpHost is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059ED69, 17 bytes: "AptOnline::CustomMatch::OnOpenConnectionsScreen".
// AptOnlineCustomMatch::OnOpenConnectionsScreen is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059ED7A, 17 bytes: "AptOnline::CustomMatch::OnClosingConnectionsScreen".
// AptOnlineCustomMatch::OnClosingConnectionsScreen is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A0F15, 10 bytes: "AptOnline::CustomMatch::Refresh".
// AptOnlineCustomMatch::Refresh is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A0F1F, 44 bytes: bound as "AptOnline::OnOpenCreateDialog";
// focuses the +0x49C window and moves to state 3.
// AptOnlineCustomMatch::OnOpenCreateDialog is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A1281, 343 bytes (WorldBuilder name, AptOnlineCustomMatch.cpp
// line 1004; wb-name-unverified): asks the host for the slot's hero, as the
// BFME1 donor's applySlotTeam shape with "Hero=%d" of GameSlot::encodeHero.
// AptOnlineCustomMatch::MpOwnerSelectHero is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A13D8, 343 bytes (WorldBuilder name; wb-name-unverified): the
// BFME1 donor applySlotTeam (0x0053D170) with "Team=%d".
// AptOnlineCustomMatch::MpOwnerSelectTeam is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A152F, 350 bytes (WorldBuilder name; wb-name-unverified):
// "Handicap=%d" for the slot's +0x20; the host resets acceptance again
// before publishing the options.
// AptOnlineCustomMatch::MpOwnerSelectHandicap is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A186B, 341 bytes (WorldBuilder name; wb-name-unverified):
// "StartPos=%d"; the BFME1 donor is applySlotStartPos.
// AptOnlineCustomMatch::MpOwnerSelectStartPosition is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A19C0, 399 bytes (WorldBuilder name; wb-name-unverified):
// stores the translated clan ID through GameSlot 0x003FF5F2, then, when not
// hosting, asks the host "clanID=<id>" only for the local player's slot.
// AptOnlineCustomMatch::MpOwnerSetClanID is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A1DCE, 288 bytes (WorldBuilder name; wb-name-unverified): a
// joined player tells the host "READY" / "UNREADY" (options "true").
// AptOnlineCustomMatch::MpOwnerOnReadyChecked is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059F043, 180 bytes (WorldBuilder name; wb-name-unverified): the
// staging room counterpart of AptLanLobby::MpOwnerPrintMessage 0x004448E5.
// AptOnlineCustomMatch::MpOwnerPrintMessage is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A0B7E, 240 bytes (WorldBuilder name; wb-name-unverified): the
// host's map change, the staging room counterpart of
// AptLanLobby::bfmeMapChanged 0x00444F9C.
// AptOnlineCustomMatch::MpOwnerSelectMap is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059EBDE, 32 bytes, vftable 0x008713B8 slot 1 (unnamed in
// WorldBuilder): whether the current staging room says this player hosts.
// AptOnlineCustomMatch::rva0059EBDE is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A1D32, 156 bytes, vftable 0x008713B8 slot 15 (unnamed in
// WorldBuilder): the host posts request 0xE "EUI/" with options "true".
// AptOnlineCustomMatch::rva005A1D32 is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A10DA, 423 bytes (WorldBuilder name; wb-name-unverified):
// "PlayerTemplate=%d"; the host also enables the +0x70 member.
// AptOnlineCustomMatch::MpOwnerSelectPlayerTemplate is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059F37C, 253 bytes (WorldBuilder name; wb-name-unverified):
// counts open requests of the connecting pop-up; the first clears the eight
// slot lines and opens it, the last close closes it.
// AptOnlineCustomMatch::OpenConnectionScreen is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A1C87, 171 bytes, vftable 0x008713B8 slot 16 (unnamed in
// WorldBuilder): opens or closes the connecting pop-up; a host opening it
// also posts request 0xE "DUI/" with options "true".
// AptOnlineCustomMatch::rva005A1C87 is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059EBFE, 82 bytes, vftable 0x008713B8 slot 2 (unnamed in
// WorldBuilder): publishes the game options and, on the host, saves the
// room's ten rule ints through GameModePreferences "Rules" -- the staging
// room counterpart of AptLanLobby's slot 2 (0x00444279).
// AptOnlineCustomMatch::rva0059EBFE is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059EC50, 21 bytes, vftable 0x008713B8 slot 22 (unnamed in
// WorldBuilder): whether the NAT negotiator 0x00A063F8 exists and is idle.
// AptOnlineCustomMatch::rva0059EC50 is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059EF49, 14 bytes, vftable 0x00871414 slot 8 (unnamed in
// WorldBuilder): the negation of the +0x70 panel's 0x0043DBCA test.
// AptOnlineCustomMatch::rva0059EF49 is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A6697, 33 bytes, vftable 0x00871414 slot 9 (unnamed in
// WorldBuilder): in state 2 runs 0x005A5B38; states 0 and 1 stay; any other
// state falls back to 1.
// AptOnlineCustomMatch::rva005A6697 is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x0059EFA0, 163 bytes: AptOnlineCustomMatch::InitGadgets (the
// retail string names it), vftable 0x00871414 slot 2.
// AptOnlineCustomMatch::InitGadgets is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A168D..0x005A186B, 478 bytes, MpOwner vftable slot 9.
// WorldBuilder 0x014EA540 names this callback and asserts GameSpy state at
// AptOnlineCustomMatch.cpp:1134/1136. Retail supplies the slot state at +4,
// name at +0x30 and the connection grid at MpOwner-relative +0x474.
// A human slot is kicked before resetting its connection information;
// changing whether a nonhuman slot is AI invalidates the room's acceptance.
// Retail redraws the grid inside the kick branch and again on success.
// AptOnlineCustomMatch::MpOwnerSelectPlayer is rowed in its home unit; this copy was a duplicate definition.

// Retail 0x005A2C77..0x005A2DB7, 320 bytes, ret 4. WorldBuilder
// 0x014F0720 names RequestJoinGame and asserts roomToJoin at line 2647.
// The existing matched getters and setters prove the string-by-value ABI;
// their address-derived owner names retain uncertainty about those fields.
// Native bytes prove the selected ID at +0x4B8, copied room WORD at +0x1008,
// peer request type 11, and the transition to state 11 with pending marker -1.
// AptOnlineCustomMatch::RequestJoinGame is rowed in its home unit; this copy was a duplicate definition.

#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

// Retail 0x0059F12A..0x0059F1B8, 142 bytes. WorldBuilder's unnamed
// 0x014EC750 counterpart returns a UnicodeString by value. Native tooltip
// callers pass a signed ladder rank: negatives fetch the unavailable label;
// other values use the UTF-16 "%d" literal at 0x00BC9260. Name remains unknown.
UnicodeString Rva0059F12A(int rank); // rowed in AptOnlineCustomMatchCallbacks.cpp

void GadgetTextEntrySetText(GameWindow *, UnicodeString);
// Retail RVA 0x005A0DC2, 339 bytes, RET4; named WB014F84A0 and assert4214.
// The complete native body establishes the +8 target field delta and
// both string lifetimes. The flag at4C2 retains an address-derived label.
// AptOnlineCustomMatch::FillGameNameTextEntry is rowed in its home unit; this copy was a duplicate definition.

extern int g_Va00E063F0;
void __cdecl Rva00381C2DClear(unsigned int value);
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
// Retail 0x005A61C6, 956 bytes: slot 3 of vftable 0x00871414, the screen's
// per-frame step over its +0x488 state (WorldBuilder twin 0x014E76B0, a
// later revision with extra calls, unnamed; strings "OnStartLobby",
// "GUI:GSBuddyInviteFailed", "GUI:GSDisconReason%d"). Every state ends in
// the +0x70 panel's OnUpdate and, when that reports a change, UpdatePings,
// except the state-14 launch which returns at once.
// AptOnlineCustomMatch::Update is rowed in its home unit; this copy was a duplicate definition.

class LanguageFilter { public: void filterLine(UnicodeString &line); }; // rowed 0x00388102
extern LanguageFilter *TheLanguageFilter;
class GameSpyConfigInterface
{
public:
#define G(n) virtual void g##n();
	G(0) G(1) G(2) G(3) G(4) G(5) G(6) G(7) G(8) G(9) G(10) G(11) G(12)
#undef G
	virtual bool v13(); // +0x34, Zero Hour's restrictGamesToLobby slot
};
extern GameSpyConfigInterface *TheGameSpyConfig;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva005A2899GlobalView
{
	unsigned char m_pad000[0xB04];
	unsigned int m_exeCRC;	 // +0xB04
	Rva00237E28 m_version;	 // +0xB08
	unsigned char m_padb18[0xB38 - 0xB18];
	unsigned int m_iniCRC;	 // +0xB38
};

// Retail 0x005A2899, 990 bytes: state 4 of the per-frame step, the host's
// staging-room creation (Zero Hour's PopupHostGame createGame, adapted):
// with a ladder (+0x70 panel +0x2B0) it first refills the name and password
// entries from the saved game-mode preferences, then sends a type-9 peer
// request carrying the filtered game name, the password, TheWritableGlobalData's
// version block and CRCs, TheGameSpyInfo's vslot-85 value, TheGameSpyConfig's
// vslot-13 flag, the "localhost" ladder address, the ping string, the ladder's
// 16-byte key (else zeros) and the map's +0x34 cache value, and moves to
// state 5.
// AptOnlineCustomMatch::rva005A2899 is rowed in its home unit; this copy was a duplicate definition.

// The UnicodeString buffer header as retail's inlined emptiness test reads
// it: the length word at +4.
struct Rva005A52FEWideData
{
	int m_refCount;
	unsigned short m_length; // +0x04
};
static inline bool Rva005A52FEIsEmptyA(const UnicodeString &text)
{
	const Rva005A52FEWideData *data = *(const Rva005A52FEWideData *const *)&text;
	if (data == 0)
		return true;
	return data->m_length == 0;
}
static inline bool Rva005A52FEIsEmptyB(const UnicodeString &text)
{
	const Rva005A52FEWideData *data = *(const Rva005A52FEWideData *const *)&text;
	return data == 0 || data->m_length == 0;
}
static inline int EmpI(const UnicodeString &text){const Rva005A52FEWideData *data = *(const Rva005A52FEWideData *const *)&text; return data == 0 || data->m_length == 0;}
static inline int Rva005A52FELength(const UnicodeString &text)
{
	const Rva005A52FEWideData *data = *(const Rva005A52FEWideData *const *)&text;
	return data ? data->m_length : 0;
}
static inline bool Rva005A52FEIsEmptyC(const UnicodeString &text)
{
	return Rva005A52FELength(text) == 0;
}

// Retail 0x005A52FE, 820 bytes (RET 0x10): slot 5 of vftable 0x00871414.
// Every message goes to the +0x70 panel (0x00442CB3) first, whose result
// is returned for messages the screen does not handle. The screen keeps
// the create button in step with the game-name entry, applies a ladder
// picked in the +0x490 combo box, sends a join for a double-clicked room
// and, for a selected room in the +0x48C list, shows it on the panel,
// enables joining while the room's slots 8 and 9 differ and asks for its
// extended info at most once a second per room (Zero Hour's
// WOLLobbyMenuSystem GLM_SELECTED throttle, by timeGetTime).
static inline void *Rva5A52FEAddr(const AsciiString &asciiString) { return (void *)&asciiString; }
int AptOnlineCustomMatch::GameWindowSystem(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
	int result = ((AptMpGameSetup *)&m_70)->rva00442CB3(msg, mData1, mData2);
	switch (msg)
	{
	case 1:
		Rva003B3371Call(0x1A);
		break;
	case 2:
		Rva003B3371Call(0x1B);
		break;
	case 0x4032:
		if (mData1 && (GameWindow *)mData1 == m_textentryGameName)
		{
			UnicodeString text = GadgetTextEntryGetText(m_textentryGameName);
			int empty = EmpI(text); bool enable = !(char)empty;
			if (m_4c2 != enable)
			{
				m_4c2 = enable;
				const char *function = enable ? "EnableButtonCreatePopup" : "DisableButtonCreatePopup";
				void *movie = m_owner->m_movie;
				Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), function);
			}
		}
		break;
	case 0x4026:
		if ((int)mData1 == m_490 && !m_popUp)
		{
			int pos = -1;
			GadgetComboBoxGetSelectedPos((GameWindow *)m_490, &pos);
			if (pos >= 0)
			{
				void *ladder = GadgetComboBoxGetItemData((GameWindow *)m_490, pos);
				((Rva005A5B38Box *)this)->DoRefresh((int)ladder, Rva5A52FEAddr(AsciiString("")));
			}
		}
		break;
	case 0x4015:
		if ((int)mData1 == m_48c && (int)mData2 >= 0)
			((Rva0059ECAD *)this)->rva0059ECAD((int)"");
		break;
	case 0x4014:
		if ((int)mData1 == m_48c && !m_70.m_ladder)
		{
			struct Locals { int id; GameSpyStagingRoom *room; } L;
			L.room = 0;
			if ((int)mData2 >= 0)
			{
				std::map<int, GameSpyStagingRoom *> *rooms = TheGameSpyInfo->getStagingRoomList();
				L.id = (int)GadgetListBoxGetItemData((GameWindow *)mData1, mData2, 3);
				std::map<int, GameSpyStagingRoom *>::iterator it = rooms->find(L.id);
				if (it != rooms->end())
				{
					L.room = it->second;
					((AptMpGameSetup *)&m_70)->rva0043FA68(L.room);
				}
				else
				{
					((AptMpGameSetup *)&m_70)->rva0043FA68(0);
				}
				if (L.room && L.room->v08() != L.room->v09())
				{
					if (!m_joinEnabled)
					{
						m_joinEnabled = true;
						void *movie = m_owner->m_movie;
						Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "EnableButtonJoinGame");
					}
				}
				else if (m_joinEnabled)
				{
					m_joinEnabled = false;
					void *movie = m_owner->m_movie;
					Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "DisableButtonJoinGame");
				}
				static unsigned int lastTime = 0;
				static int lastID = -1;
				unsigned int now = timeGetTime();
				PeerRequest req;
				req.peerRequestType = 0x14;
				req.gameID = (int)GadgetListBoxGetItemData((GameWindow *)mData1, mData2, 3);
				if (lastID != req.gameID || now > lastTime + 1000)
					TheGameSpyPeerMessageQueue->addRequest(req);
				lastID = req.gameID;
				lastTime = now;
			}
			else if (m_joinEnabled)
			{
				m_joinEnabled = false;
				void *movie = m_owner->m_movie;
				Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "DisableButtonJoinGame");
			}
		}
		break;
	default:
		return result;
	}
	return 1;
}

// Retail 0x0059ED8B, 244 bytes: refreshes the connection icons of the host
// panel for each of the room's eight slots (the local ping, or the NAT's
// negotiation state with each human peer).
void AptOnlineCustomMatch::UpdatePings()
{
	if (!TheGameSpyInfo)
		return;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return;

	unsigned short localSlot = room->getLocalSlotNum();
	PortNegotiationSchema *schema = &((Rva005A6D47 *)TheNAT)->m_schema;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = room->getSlot(i);
		if (!slot)
			continue;
		GameSpySlotView *gsSlot = slot->gameSpySlot();
		int value = 0;
		int kind = 0;
		if (i == localSlot)
		{
			kind = 4;
			value = Rva005DB335Get(gsSlot->m_ping);
		}
		else if (slot->isHuman())
		{
			Elem005DB98E *ping = 0;
			if (TheNAT)
			{
				switch (schema->GetConnectionState(localSlot, i))
				{
				case 1:
					kind = 2;
					break;
				case 2:
					kind = 3;
					break;
				case 3:
					ping = (Elem005DB98E *)schema->peekPing(localSlot, i);
					if (ping)
					{
						kind = 4;
						value = AptConnectionScreen::GetPingImageEnum(ping);
					}
					else
						kind = 0;
					break;
				case 4:
					kind = 1;
					break;
				default:
					kind = 0;
					break;
				}
			}
			else
				kind = 0;
		}
		((AptMpGameSetup *)&m_70)->rva0043E5C1(i, kind, value);
	}
}

// Retail 0x005A51B9, 325 bytes: the custom match screen's room refresh for a
// ladder/group room id and name. When the room differs from TheGameSpyInfo's
// (vslot 12) or its name (vslot 14) differs, the info leaves its room
// (vslots 7, 6 and, once TheGameSpyConfig allows it, 40), the games list
// repopulates (rowed 0x005A061B) and a type-7 peer request carrying the name
// is queued before the info is handed the name again (vslot 13).
void Rva005A5B38Box::DoRefresh(int ladder, void *password)
{
	AsciiString &name = *(AsciiString *)password;
	bool differs;
	if (ladder && (ladder != TheGameSpyInfo->getCurrentGroupRoom() || name.compare(TheGameSpyInfo->rva0038616D()) != 0))
		differs = true;
	else
		differs = false;
	if (differs)
	{
		TheGameSpyInfo->leaveGroupRoom();
		TheGameSpyInfo->joinGroupRoom(ladder);
		if (TheGameSpyConfig->v13())
		{
			TheGameSpyInfo->clearStagingRoomList();
			((AptOnlineCustomMatch *)this)->PopulateGamesListBox();
			PeerRequest req;
			req.peerRequestType = 7;
			req.isStagingRoom = true;
			req.unknown_f8 = name.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
			TheGameSpyInfo->rva00386139(AsciiString(name.str()));
		}
	}
}
