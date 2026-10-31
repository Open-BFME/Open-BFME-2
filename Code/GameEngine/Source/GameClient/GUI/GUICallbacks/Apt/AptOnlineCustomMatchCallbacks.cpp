// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport46
//
// BFME2's online custom match screen Apt callbacks, 0x0059EC65 onward,
// bound by these names ("AptOnline::CustomMatch::PlayGame" ...) as member
// pointers by the screen's registration; that binding is their only
// reference. The class is AptOnlineCustomMatch (retail string
// "AptOnlineCustomMatch::InitGadgets"; the "AptOnline::CustomMatch::" names
// are Apt binding strings, not the C++ scope). +0x488 is the screen's state.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
#include <map>
#include <string>
#include <vector>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null(unsigned short *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null_aux(unsigned short *, __true_type const &); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *); }
namespace _STL { template <> void __char_traits_base<unsigned short, unsigned short>::assign(unsigned short &, unsigned short const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > & basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::assign(unsigned short const *, unsigned short const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::copy(unsigned short *, unsigned short const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::erase(unsigned short *, unsigned short *); }
namespace _STL { template <> unsigned int __char_traits_base<unsigned short, unsigned short>::length(unsigned short const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::move(unsigned short *, unsigned short const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

class GameWindow { public: int winEnable(bool); };

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
class AptSaveLoad
{
public:
	static void OpenScreen(int a, int b, bool c);
};

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

class Rva0022C4DF { public: UnicodeString rva0022C4DF() const; };
class Rva003821E2 { public: void assign(UnicodeString); };
class Rva0059F322AsciiField { public: AsciiString get() const; };
class Rva0059F2EB { public: void rva0059F2EB(AsciiString); };

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
	unsigned char m_padfee[0xFF4 - 0xFEE];
	bool m_ff4; // +0xFF4
	unsigned char m_padff5[0xFF8 - 0xFF5];
	int m_ff8; // +0xFF8
	unsigned char m_padffc[0x1008 - 0xFFC];
	unsigned short m_1008; // purpose remains unknown
};

// TheGameSpyGame 0x00A02324.
extern GameSpyStagingRoom *TheGameSpyGame;

// The map cache: the AsciiString-keyed map whose find worker is the pinned
// _M_find 0x001F8437; size at +0x28 and CRC at +0x2C of the value (as
// AptLanLobby::bfmeMapChanged reads them).
class MapMetaData
{
public:
	unsigned char m_pad00[0x20];
	int m_20;				// +0x20, sent with a created room
	unsigned char m_pad24[0x28 - 0x24];
	unsigned int m_filesize; // +0x28
	unsigned int m_CRC;	  // +0x2C
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
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48)
	// RequestJoinGame passes the selected room ID through slot 49 (+0xC4).
	virtual void gs49(int);
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
	V(66) V(67) V(68) V(69)
	V(70)
	virtual const AsciiString &v71() = 0; // +0x11C, the host ping string
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84)
	// Slots 85/86 (+0x154/+0x158) seed the room's +0x38/+0x3C when state 12
	// creates the NAT; 88 (+0x160), 89 (+0x164) and 93 (+0x174) serve
	// state 14's disconnect drain (address-derived names).
	virtual int v85() = 0;
	virtual unsigned short v86() = 0;
	V(87)
	virtual bool v88(bool) = 0;
	virtual void v89(int reason) = 0;
	V(90) V(91) V(92)
	virtual int v93() = 0;
#undef V
};

extern GameSpyInfoInterface *TheGameSpyInfo;

// The online chat colors: 0x009B9198 and, inside the 148-byte table
// 0x009B91B4, the dword at +0x44 (0x009B91F8).
// Chat.cpp owns the colour array at VA 0x00DB9198; index/addend unchanged.
extern int GameSpyColor[];
extern unsigned int g_00DB91B4;

// Unrowed 0x0044C0A8 (pinned; as AptLanLobby::MpOwnerPrintMessage uses it)
// and the flag it is skipped under.
void MessageBoxOk(UnicodeString title, UnicodeString text, void (*callback)());
class AptMessenger { public: static AptMessenger *s_instance; };

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
		int payloadWord; // request 0xF sets the word to -1
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
class GameModePreferences
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	AsciiString rva0044DAA8(const AsciiString &);
	AsciiString rva0044DBA5();
	void rva0044DE5A(const AsciiString &name);	// rowed 0x0044DE5A
	void rva0044DEC1(const AsciiString &password); // rowed 0x0044DEC1
	AsciiString rva0044D986();					  // rowed 0x0044D986, the map
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

class AptMpGameSetup
{
public:
	void rva0043E5C1(int slot, int kind, int value);
	void InitGadgets();
	bool OnHostStartGame(bool host); // rowed 0x00440BDF (WB OnHostStartGame)
	bool WaitStartGame();		 // rowed 0x0044127C
	bool OnUpdate();			 // rowed 0x00443EA8
};

// The NAT negotiator at 0x00A063F8 keeps its port negotiation at +0x28.
struct Elem005DB98E;

// The screen's +0x6C observer base and the NAT's observer list (rowed
// append 0x005A0B4C).
struct Rva002BA8F1Listener
{
	void *m_vptr;
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

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
class Rva005A734B
{
public:
	Rva005A734B();
	unsigned char m_data[0x974];
};

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
	// Slot 4 of vftable 0x00871414: the screen's key handler (WB unnamed).
	virtual int rva005A6582(int window, int msg, unsigned char key, int flags);
	virtual void v05(); virtual void v06(); virtual void v07();
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

// Slot 18's helpers: the rowed SendStatsToOtherPlayers 0x00387288 takes the
// room, and the staging room assignment 0x00382E73 copies it into TheGameSpyGame.
void SendStatsToOtherPlayers(GameInfo *game);

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
	virtual void rva005A1B4F(bool accepted, int unused) = 0;			  // 18
	virtual void MpOwnerUpdatePlayerTooltip() = 0;							// 19
	virtual void *v20() = 0;												  // 20
	virtual int v21() = 0;													// 21
	virtual bool rva0059EC50() = 0;										   // 22

private:
	unsigned char m_pad04[0x0C - 0x04];
};

int __cdecl Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class AptOnlineCustomMatch : public CustomMatchScreen, public MpOwner
{
public:
	void PlayGame(const char *unused);
	void rva005A5BAF();	// 0x005A5BAF (Rva005A5BAFCheck.cpp)
	void rva0059ECD2(int unused);	// 0x0059ECD2 and 0x0059EC72 (Rva0059ECD2.cpp)
	void rva0059EC72(int unused);
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
	virtual bool MpOwnerSelectColor(GameSlot *slot, int color);
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
	virtual void rva005A1B4F(bool accepted, int unused);

	virtual void rva005A1C87(bool open);
	virtual void rva0059EBFE();
	virtual bool rva0059EC50();
	virtual void InitGadgets();
	virtual int rva005A6582(int window, int msg, unsigned char key, int flags);
	virtual bool rva0059EF49();
	virtual bool rva005A6697();

	void OnBttnCancel(int unused);
	void AcceptJoinGame(const char *unused);

	GameSpyStagingRoom *GetGameToJoin();
	bool RequestJoinGame(const char *password);
	void OpenConnectionScreen(bool open);
	bool FillBuddyInviteGameInfo(Rva0059EF62 *info);
	// UpdatePings 0x0059ED8B is banked: reverse/attempts/0x0059ed8b.cpp.

	// Rowed 0x005A0DC2 (339 bytes; ret 4), named by WorldBuilder.
	void FillGameNameTextEntry(bool flag);

	// Unrowed 0x005A0D61 (97 bytes; ret 4, a byte flag), pinned by address.
	void rva005A0D61(bool force);

	virtual void Update();
	void UpdatePings();					 // banked 0x0059ED8B, pinned
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
	unsigned char m_pad4c0[2];
	bool m_4c2; // +0x4C2
	unsigned char m_pad4c3[0x4D4 - 0x4C3];
	AptConnectionScreen *m_connectionGrid; // +0x4D4
	bool m_connectionsScreen; // +0x4D8
	unsigned char m_pad4d9[0x4DC - 0x4D9];
	unsigned int m_inviteTime; // +0x4DC, timeGetTime when the buddy invite went out
};

// Retail 0x0059EC65, 13 bytes: "AptOnline::CustomMatch::PlayGame".
void AptOnlineCustomMatch::PlayGame(const char *unused)
{
	m_state = 7;
}

// Retail 0x0059ECC1, 17 bytes: "AptOnline::CustomMatch::LoadGame".
void AptOnlineCustomMatch::LoadGame(const char *unused)
{
	AptSaveLoad::OpenScreen(2, 16, false);
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
	FillGameNameTextEntry(true);
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
		TheGameSpyInfo->v61(text, GameSpyColor[0]);
		break;
	case 1:
		if (!AptMessenger::s_instance)
			MessageBoxOk(UnicodeString(L""), text, 0);
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

// Retail 0x005A0F4B, 399 bytes (WorldBuilder name; wb-name-unverified):
// "Color=%d"; the host applies the color and publishes the options, a guest
// must own the slot and sends the request to the host.
// Codegen: the failure return is ONE block hosted after the isPlayer test in
// retail (the null-info and null-room tests jump forward to it): the first two
// failures are gotos to the label inside the isPlayer arm. The always-true
// color test carries the slot into its register role; the barrier keeps the
// staging room load ahead of its test.
bool AptOnlineCustomMatch::MpOwnerSelectColor(GameSlot *slot, int color)
{
	if ((slot->m_color != 0 || slot->m_color == 0)) {
		if (!TheGameSpyInfo)
			goto fail;
		GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
		_ReadWriteBarrier();
		if (!room)
			goto fail;

		slot->m_color = color;
		if (TheGameSpyInfo->amIHost())
		{
			TheGameSpyInfo->setGameOptions();
		}
		else
		{
			if (!slot->isPlayer(TheGameSpyInfo->getLocalName()))
			{
fail:
				return false;
			}

			AsciiString options;
			options.format("Color=%d", color);
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
	if (TheNAT && ((Rva005A6D47 *)TheNAT)->m_10 == 0)
		return true;
	return false;
}

// Retail 0x0059EF49, 14 bytes, vftable 0x00871414 slot 8 (unnamed in
// WorldBuilder): the negation of the +0x70 panel's 0x0043DBCA test.
bool AptOnlineCustomMatch::rva0059EF49()
{
	return !((Rva0043DFE0 *)&m_70)->rva0043DBCA();
}

// Retail 0x005A6582, 277 bytes, vftable 0x00871414 slot 4 (unnamed in WorldBuilder):
// the screen's key handler. For message 0x15 with the key-down bit set, Escape
// (1) cancels or closes whatever the current state shows and Enter (0x1C) accepts
// it, unless a connecting pop-up is open; both report the key handled.
int AptOnlineCustomMatch::rva005A6582(int window, int msg, unsigned char key, int flags)
{
	if (msg == 0x15)
	{
		switch (key)
		{
		case 1:
		{
			if (flags & 1)
			{
				if (m_connectingCount > 0)
					return 1;
				switch (m_state)
				{
				case 2:
					return 0;
				case 3:
				{
					void *movie = m_owner->m_movie;
					Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "EscapeKeyPressed");
					m_state = 1;
					m_popUp = false;
					return 1;
				}
				case 6:
				case 12:
					if (!m_connectionsScreen)
						OnBttnCancel(0);
					else
						Rva0043DB23((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_owner->m_movie, "CloseConnectionsScreen");
					return 1;
				case 10:
					rva0059ECD2(0);
					return 1;
				default:
					return 1;
				}
			}
			break;
		}
		case 0x1C:
		{
			if (flags & 1)
			{
				if (m_connectingCount > 0)
					return 1;
				switch (m_state)
				{
				case 3:
					rva0059EC72(0);
					return 1;
				case 10:
					AcceptJoinGame(0);
					return 1;
				default:
					return 1;
				}
			}
			break;
		}
		}
	}
	return 0;
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
	((AptMpGameSetup *)&m_70)->InitGadgets();
	m_4b0 = 0;
	if (TheWindowManager)
		TheWindowManager->pad45();
	_bfme_closeAptScreen(AsciiString("AptOnlineCustomMatch::InitGadgets"));
	m_48c = 0;
	m_490 = 0;
	m_494 = 0;
	m_textentryGameName = 0;
	m_createDialog = 0;
	((Rva0052493F *)this)->rva0052493F();
}

// Retail 0x005A168D..0x005A186B, 478 bytes, MpOwner vftable slot 9.
// WorldBuilder 0x014EA540 names this callback and asserts GameSpy state at
// AptOnlineCustomMatch.cpp:1134/1136. Retail supplies the slot state at +4,
// name at +0x30 and the connection grid at MpOwner-relative +0x474.
// A human slot is kicked before resetting its connection information;
// changing whether a nonhuman slot is AI invalidates the room's acceptance.
// Retail redraws the grid inside the kick branch and again on success.
bool AptOnlineCustomMatch::MpOwnerSelectPlayer(GameSlot *slot, int state, int)
{
	if (!TheGameSpyInfo)
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;
	if (slot->m_state == SLOT_PLAYER)
	{
		PeerRequest req;
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		AsciiString name;
		name.translate(slot->m_name);
		req.nick = name.str();
		req.id = "KICK/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
		if (TheNAT)
		{
			int index = room->getSlotNum(name);
			if (index >= 0)
				TheNAT->processPlayerLeave(index);
		}
		slot->setState((SlotState)state, UnicodeString::TheEmptyString,
			&GameSlotConnectInfo());
		room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
		if (m_connectionGrid)
			m_connectionGrid->RedrawGrid(0);
	}
	else if (slot->m_state != state)
	{
		bool oldAI = slot->isAI();
		slot->setState((SlotState)state, UnicodeString::TheEmptyString,
			&GameSlotConnectInfo());
		if (oldAI ^ slot->isAI())
			room->resetAccepted();
		TheGameSpyInfo->setGameOptions();
	}
	else
		return false;
	if (m_connectionGrid)
		m_connectionGrid->RedrawGrid(0);
	return true;
}

// Retail 0x005A2C77..0x005A2DB7, 320 bytes, ret 4. WorldBuilder
// 0x014F0720 names RequestJoinGame and asserts roomToJoin at line 2647.
// The existing matched getters and setters prove the string-by-value ABI;
// their address-derived owner names retain uncertainty about those fields.
// Native bytes prove the selected ID at +0x4B8, copied room WORD at +0x1008,
// peer request type 11, and the transition to state 11 with pending marker -1.
bool AptOnlineCustomMatch::RequestJoinGame(const char *password)
{
	GameSpyStagingRoom *room = GetGameToJoin();
	if (!room)
		return false;
	TheGameSpyInfo->gs49(m_gameToJoinID);
	((Rva003821E2 *)TheGameSpyGame)->assign(
		((Rva0022C4DF *)room)->rva0022C4DF());
	((Rva0059F2EB *)TheGameSpyGame)->rva0059F2EB(
		((Rva0059F322AsciiField *)room)->get());
	TheGameSpyGame->m_1008 = room->m_1008;
	TheGameSpyGame->rva003FF1A7(room->m_5c);
	PeerRequest req;
	req.peerRequestType = 11;
	req.unknown_10 = ((Rva0022C4DF *)room)->rva0022C4DF().str();
	req.gameID = m_gameToJoinID;
	req.unknown_1c = password;
	TheGameSpyPeerMessageQueue->addRequest(req);
	m_state = 11;
	m_4a8 = -1;
	m_popUp = true;
	return true;
}

class GameTextInterface
{
public:
#define T(n) virtual void t##n();
	T(0) T(1) T(2) T(3) T(4) T(5) T(6) T(7) T(8) T(9) T(10) T(11) T(12) T(13) T(14)
#undef T
	virtual UnicodeString fetch(const char *, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

// Retail 0x0059F12A..0x0059F1B8, 142 bytes. WorldBuilder's unnamed
// 0x014EC750 counterpart returns a UnicodeString by value. Native tooltip
// callers pass a signed ladder rank: negatives fetch the unavailable label;
// other values use the UTF-16 "%d" literal at 0x00BC9260. Name remains unknown.
UnicodeString Rva0059F12A(int rank)
{
	UnicodeString text;
	if (rank < 0)
		text = TheGameText->fetch("TOOLTIP:LadderRankUnavailable");
	else
		text.format((const unsigned short *)L"%d", rank);
	return text;
}

void GadgetTextEntrySetText(GameWindow *, UnicodeString);
// Retail RVA 0x005A0DC2, 339 bytes, RET4; named WB014F84A0 and assert4214.
// The complete native body establishes the +8 target field delta and
// both string lifetimes. The flag at4C2 retains an address-derived label.
void AptOnlineCustomMatch::FillGameNameTextEntry(bool flag)
{
 if (!m_textentryGameName)
  return;
 UnicodeString secondText;
 UnicodeString firstText;
 if (flag) {
  firstText.translate(m_prefs.rva0044DAA8(TheGameSpyInfo->getLocalName()));
  secondText.translate(m_prefs.rva0044DBA5());
 } else {
  GameSpyStagingRoom *room = GetGameToJoin();
  if (room)
   firstText = ((Rva0022C4DF *)room)->rva0022C4DF();
 }
 m_4c2 = true;
 GadgetTextEntrySetText(m_textentryGameName, firstText);
 m_textentryGameName->winEnable(flag);
 m_createDialog->winEnable(true);
 GadgetTextEntrySetText(m_createDialog, secondText);
}

int g_Va00E063F0;	// retail RVA 0x00A063F0 (.bss), defined here
#include <windows.h>
void __cdecl Rva00381C2DClear(unsigned int value);
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
class Rva005170CD { public: void rva005170CD(); };
class Rva0059FC9F { public: int rva0059FC9F(); };

// Retail 0x005A61C6, 956 bytes: slot 3 of vftable 0x00871414, the screen's
// per-frame step over its +0x488 state (WorldBuilder twin 0x014E76B0, a
// later revision with extra calls, unnamed; strings "OnStartLobby",
// "GUI:GSBuddyInviteFailed", "GUI:GSDisconReason%d"). Every state ends in
// the +0x70 panel's OnUpdate and, when that reports a change, UpdatePings,
// except the state-14 launch which returns at once.
void AptOnlineCustomMatch::Update()
{
	switch (m_state)
	{
	case 0:
		if (g_Va00E063F0 == 1 && rva005A1EEE() && m_70.m_ladder != 0)
			m_state = 4;
		break;
	case 1:
	{
		void *movie = m_owner->m_movie;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "OnStartLobby");
		m_state = 2;
	}
		// fall through
	case 2:
		rva005A0D61(false);
		break;
	case 4:
		rva005A2899();
		break;
	case 6:
		if (TheNAT)
			((Rva005A6D47 *)TheNAT)->rva005A8F57();
		UpdateHostStartGameButton();
		break;
	case 7:
		if (((AptMpGameSetup *)&m_70)->OnHostStartGame(true))
		{
			m_state = 8;
		}
		else
		{
			m_state = 6;
			rva0059EE96(1, 1);
			Rva00381C2DClear(1);
		}
		break;
	case 8:
		if (!((AptMpGameSetup *)&m_70)->WaitStartGame())
		{
			m_state = 6;
			rva0059EE96(1, 1);
		}
		break;
	case 9:
		rva005A57BA(false);
		break;
	case 13:
		if (timeGetTime() - m_inviteTime > 15000)
		{
			((Rva005170CD *)m_owner)->rva005170CD();
			m_inviteTime = 0;
			GSMessageBoxOk(TheGameText->fetch("GUI:GSBuddyInviteFailedTitle"),
				TheGameText->fetch("GUI:GSBuddyInviteFailed"), 0);
			rva005A1EEE();
		}
		else if (((Rva0059FC9F *)this)->rva0059FC9F() >= 0)
		{
			rva005A5BAF();
		}
		break;
	case 12:
		if (!TheNAT && TheGameSpyGame->getLocalSlotNum() >= 0)
		{
			TheNAT = (NAT *)new Rva005A734B;
			GameInfo::Address38 address;
			address.ip = TheGameSpyInfo->v85();
			address.port = TheGameSpyInfo->v86();
			TheGameSpyGame->m_38 = address;
			((Rva005A6D47 *)TheNAT)->m_observers.append(&m_observer);
		}
		if (TheNAT)
			((Rva005A6D47 *)TheNAT)->rva005A8F57();
		if (m_owner->m_2b0)
			((Rva005170CD *)m_owner)->rva005170CD();
		break;
	case 14:
		if (TheGameSpyGame && TheGameSpyGame->m_11)
		{
			if (!TheGameSpyInfo->v88(false))
			{
				int count = TheGameSpyInfo->v93();
				bool done = false;
				PeerResponse resp;
				while (count--)
				{
					if (done || !TheGameSpyPeerMessageQueue->getResponse(resp))
						break;
					switch (resp.peerResponseType)
					{
					case PeerResponse::PEERRESPONSE_DISCONNECT:
					{
						done = true;
						AsciiString reason;
						reason.format("GUI:GSDisconReason%d", resp.discon.reason);
						TheGameSpyInfo->v89(resp.discon.reason);
						break;
					}
					}
				}
			}
		}
		else
		{
			if (TheGameSpyGame->m_5c == 1)
				TheGameSpyGame->launchWOTRMPGame();
			else
				TheGameSpyGame->launchGame();
			return;
		}
		break;
	}
	if (((AptMpGameSetup *)&m_70)->OnUpdate())
		UpdatePings();
}

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
void AptOnlineCustomMatch::rva005A2899()
{
	PeerRequest req;
	if (m_70.m_ladder)
	{
		if (m_textentryGameName)
		{
			UnicodeString name;
			name.translate(m_prefs.rva0044DAA8(TheGameSpyInfo->getLocalName()));
			GadgetTextEntrySetText(m_textentryGameName, name);
		}
		if (m_createDialog)
		{
			UnicodeString password;
			password.translate(m_prefs.rva0044DBA5());
			GadgetTextEntrySetText(m_createDialog, password);
		}
	}
	UnicodeString gameName = GadgetTextEntryGetText(m_textentryGameName);
	if (TheLanguageFilter)
		TheLanguageFilter->filterLine(gameName);
	AsciiString asciiName(gameName);
	m_prefs.rva0044DE5A(asciiName);
	req.peerRequestType = 9;
	req.unknown_10 = gameName.str();
	((Rva003821E2 *)TheGameSpyGame)->assign(gameName);
	AsciiString passwd;
	passwd.translate(GadgetTextEntryGetText(m_createDialog));
	req.unknown_1c = passwd.str();
	m_prefs.rva0044DEC1(passwd);
	req.creation.allowObservers = true;
	TheGameSpyGame->m_fed = true;
	((Rva005A2899GlobalView *)TheWritableGlobalData)->m_version.rva00237E28(&req.creation.version);
	req.creation.exeCRC = ((Rva005A2899GlobalView *)TheWritableGlobalData)->m_exeCRC;
	req.creation.iniCRC = ((Rva005A2899GlobalView *)TheWritableGlobalData)->m_iniCRC;
	req.creation.gameVersion = TheGameSpyInfo->v85();
	req.creation.restrictGameList = TheGameSpyConfig->v13();
	req.unknown_4c = "localhost";
	req.creation.ladPort = 0;
	((Rva0059F2EB *)TheGameSpyGame)->rva0059F2EB(AsciiString(req.unknown_4c.c_str()));
	TheGameSpyGame->m_1008 = req.creation.ladPort;
	req.unknown_58 = TheGameSpyInfo->v71().str();
	int slot = m_70.m_7c;
	TheGameSpyGame->rva003FF1A7(slot);
	req.creation.localSlot = slot;
	if (m_70.m_ladder)
	{
		memcpy(req.creation.ladderKey, m_70.m_ladder->m_key, sizeof(req.creation.ladderKey));
		req.unknown_1c = "";
	}
	else
	{
		memset(req.creation.ladderKey, 0, sizeof(req.creation.ladderKey));
	}
	req.creation.mapValue = 2;
	if (TheMapCache)
	{
		AsciiString map = m_prefs.rva0044D986();
		map.toLower();
		MapCache::iterator it = TheMapCache->find(map);
		if (it != TheMapCache->end())
			req.creation.mapValue = it->second.m_20;
	}
	TheGameSpyPeerMessageQueue->addRequest(req);
	m_state = 5;
}

// Retail 0x0059FB4F, 246 bytes (WorldBuilder name, AptOnlineCustomMatch.cpp
// lines 4577..4588; wb-name-unverified): while hosting in state 6 or 12,
// fills the buddy invite from the create dialog's password and the room.
// Plain 'return false' early exits with no result variable alive let cl keep
// the constant 0 in ebx for every compare and the EH store (found by W7-U1);
// the room fields are read into locals before the call.
bool AptOnlineCustomMatch::FillBuddyInviteGameInfo(Rva0059EF62 *info)
{
	if (!((Rva0059ECAD *)this)->rva0059EF33())
		return false;
	if (!TheGameSpyInfo)
		return false;
	if (!TheGameSpyInfo->getCurrentStagingRoom()->amIHost())
		return false;
	GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
	if (!room)
		return false;
	AsciiString password(GadgetTextEntryGetText(m_createDialog));
	AsciiString text = ((Rva0059F340AsciiField *)room)->get();
	bool filled = false;
	if (text.getLength() != 0)
	{
		int f5c = room->m_5c;
		int f14 = room->m_14;
		info->rva0059EF62(m_4a4, f14, password, text, f5c);
		filled = true;
	}
	return filled;
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
		if (((room->m_rules[1]) ? (room->m_rules[1]) : (room->m_rules[1])))
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
		SendStatsToOtherPlayers(room);
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
