// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A1EEE@AptOnlineCustomMatch@@QAE_NXZ
// Retail 0x005A1EEE..0x005A20A7 (441 bytes); called from 0x005A21F7
// 0x005A3691 0x005A3867 0x005A3DA0 0x005A4B3B 0x005A627A and 0x005A645A.
// Leaves the current staging room and returns the custom match screen to
// its lobby: only when both +0x48C and +0x490 are set; notifies
// TheGameSpyInfo (vslot 47), resets the +0x70 game setup panel, closes the
// connection screen, lets the window manager drop the owner's windows and
// the owner (AptOnline 0x00516F08) reset, tells TheGameSpyInfo (vslot 40),
// queues peer request 7 (staging-room flag from TheGameSpyConfig vslot 13),
// clears the info's room name (vslot 13 with ""), repopulates the lobby combo
// box and the games list, drives the Apt movie ("ClosePassword",
// "GotoAndPlay" "_lobby", "EnableButtonCreateGame", "DisableButtonJoinGame"),
// clears +0x4C0, enters state 1 and calls 0x00437421. Returns true.
// Evidence (target): the five literals; rowed callees
// AptMpGameSetup::rva0043DC0F 0x0043DC0F OpenConnectionScreen 0x0059F37C
// AptOnline::rva00516F08 0x00516F08 PeerRequest ctor 0x001EF661 / dtor
// 0x001EF723 basic_string::operator=(const char *) 0x0001B790 AsciiString
// ctor 0x00037BA0 PopulateLobbyComboBox 0x0059FD3A Rva00524EF4AptCall
// 0x00524EF4 Rva005FB5E6AptCall 0x005FB5E6; pinned GameWindowManager
// 0x002C5761 PopulateGamesListBox (pin spelling Rva005A0D61::rva005A061B)
// and 0x00437421. Views and offsets follow
// AptOnlineCustomMatchCallbacks.cpp. WorldBuilder 0x014EDC70 has the same
// calls (it names PopulateGamesListBox). The method name is address-derived.
// The two guards are separate early returns: a combined || test moves the
// false return to the end instead of retail's inline block.
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string>
#include <vector>

class GameWindow;

class GameWindowManager
{
public:
	void rva002C5761(GameWindow *window);
};
extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3, const char *a4);
void Rva00437421();

class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12)
	virtual void setRoomName(AsciiString name) = 0;  // slot 13 (+0x34)
	V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void leaveRoom() = 0;                    // slot 40 (+0xA0)
	V(41) V(42) V(43) V(44) V(45) V(46)
	virtual void leaveStagingRoom() = 0;             // slot 47 (+0xBC)
#undef V
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyConfigInterface
{
public:
#define V(n) virtual void cf##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12)
#undef V
	virtual bool stagingRoomFlag() = 0;              // slot 13 (+0x34)
};
extern GameSpyConfigInterface *TheGameSpyConfig;

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
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
};

class AptOnline
{
public:
	void rva00516F08();
};

class AptMpGameSetup
{
public:
	void rva0043DC0F();
};

class Rva005A0D61
{
public:
	void rva005A061B();
};

class CustomMatchScreen
{
public:
	virtual void v00(); virtual void v01(); virtual void InitGadgets(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual bool rva0059EF49();
	virtual bool rva005A6697();
	virtual const char *v10();

protected:
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x70 - 0x5C];
};

class AptOnlineCustomMatch : public CustomMatchScreen
{
public:
	bool rva005A1EEE();
	void OpenConnectionScreen(bool open);
	void PopulateLobbyComboBox();

private:
	unsigned char m_70[0x488 - 0x70]; // +0x70 game setup panel
	int m_state;    // +0x488
	int m_48c;      // +0x48C
	int m_490;      // +0x490
	unsigned char m_pad494[0x4A0 - 0x494];
	bool m_popUp;   // +0x4A0
	unsigned char m_pad4a1[0x4C0 - 0x4A1];
	bool m_4c0;     // +0x4C0
};

bool AptOnlineCustomMatch::rva005A1EEE()
{
	if (!m_48c)
		return false;
	if (!m_490)
		return false;
	if (TheGameSpyInfo)
		TheGameSpyInfo->leaveStagingRoom();
	((AptMpGameSetup *)m_70)->rva0043DC0F();
	OpenConnectionScreen(false);
	TheWindowManager->rva002C5761((GameWindow *)m_owner);
	m_popUp = false;
	((AptOnline *)m_owner)->rva00516F08();
	TheGameSpyInfo->leaveRoom();
	PeerRequest req;
	req.peerRequestType = 7;
	req.unknown_f8 = "";
	req.isStagingRoom = TheGameSpyConfig->stagingRoomFlag();
	TheGameSpyPeerMessageQueue->addRequest(req);
	TheGameSpyInfo->setRoomName("");
	PopulateLobbyComboBox();
	((Rva005A0D61 *)this)->rva005A061B();
	void *movie = m_owner->m_movie;
	Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "ClosePassword");
	movie = m_owner->m_movie;
	Rva005FB5E6AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "GotoAndPlay", "_lobby");
	movie = m_owner->m_movie;
	Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "EnableButtonCreateGame");
	movie = m_owner->m_movie;
	Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "DisableButtonJoinGame");
	m_4c0 = false;
	m_state = 1;
	Rva00437421();
	return true;
}
