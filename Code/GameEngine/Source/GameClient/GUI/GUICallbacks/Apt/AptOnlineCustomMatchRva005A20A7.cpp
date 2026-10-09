// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005A20A7@AptOnlineCustomMatch@@QAEXXZ
// retail 0x005A20A7..0x005A2899 (2034 bytes) thiscall.
//
// The online custom match screen's staging-room entry: Zero Hour's
// WOLGameSetupMenuInit (WOLGameSetupMenu.cpp) moved onto the Apt screen.
// Called directly from 0x005A34BE and 0x005A3731; the WorldBuilder twin
// 0x014EDFC0 has the same body (strings "GUI:GSDisconReason%d"
// "PlayerTemplate=%d" "LadderRank1v1=%d"). Returning from a game it pops
// back (after the disconnect message box when the peer reports a
// disconnect; through the rowed 0x005A1EEE while still connected).
// Otherwise it saves and clears the group room and refreshes the map cache;
// the host fills its own slot and the game from the screen's
// GameModePreferences (+0x46C) unless the +0x70 game setup loaded a saved
// game; a client sends its preferences to the host as PeerRequest options.
// Then the +0x70 setup runs Init and the Apt movie moves on from the
// "create" (5) or "join" (11) states. The NAT negotiator (0x00A063F8) and
// the connection grid (+0x4D4) are released last.

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>
#include <vector>

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int size);

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *movie, const char *path, const char *function);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *t, void *movie, const char *path, const char *function, const char *arg);

// Zero Hour's GameSpyCloseAllOverlays and GSMessageBoxOk.
void Rva00548C1ACleanup();
void GSMessageBoxOk(UnicodeString title, UnicodeString body, void (*okFunc)() = 0);
// The rowed record dispatch run before the staging room is set up.
void Rva0059FF9DDo();
// ChatSystem::ClearHistory in WorldBuilder.
void Rva00381C2DClear(unsigned int which);

class Shell
{
public:
	void rva0035BF0E(); // Zero Hour's popImmediate
};

extern Shell *TheShell;

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
};

extern GameTextInterface *TheGameText;

// The options file (0x14 bytes; its destructor is the pinned ~OptionPreferences).
class OptionPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	int getFirewallBehavior();

private:
	unsigned char m_rest[0x14 - 0x04];
};

enum SlotState { SLOT_OPEN = 0 };

// Retail passes a zero DWORD and zero port WORD to GameSlot::setState.
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
	virtual ~GameSlot();
	unsigned char encodeHero() const;
	void setMapAvailability(bool available);
	void setPlayerTemplate(int playerTemplate);
	void setState(SlotState, UnicodeString, const GameSlotConnectInfo *);

	int m_state;				// +0x04
	bool m_isAccepted;		  // +0x08
	unsigned char m_pad09[0x0C - 0x09];
	int m_color;				// +0x0C
	unsigned char m_pad10[0x30 - 0x10];
	UnicodeString m_name;	   // +0x30
	unsigned char m_pad34[0x40 - 0x34];
	int m_natBehavior;		  // +0x40
	unsigned char m_pad44[0x5C - 0x44];
	int m_5c;				   // +0x5C
	unsigned char m_pad60[0x1AC - 0x60];
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
	int m_1ac; // +0x1AC
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void adjustSlotsForMap(); // slot 16

	void setMap(AsciiString mapName);
	void setMapCRC(unsigned int crc);
	void setMapSize(unsigned int size);

	unsigned char m_pad04[0x11 - 0x04];
	bool m_inProgress;				   // +0x11
	unsigned char m_pad12[0x44 - 0x12];
	unsigned int m_mapCRC;			   // +0x44
	unsigned int m_mapSize;			  // +0x48
	unsigned char m_pad4c[0x58 - 0x4C];
	int m_strategicScenario;			 // +0x58
	unsigned char m_pad5c[0x60 - 0x5C];
	int m_rules[10];					 // +0x60
};

class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyGameSlot *getGameSpySlot(int index);
};

extern GameSpyStagingRoom *TheGameSpyGame;

class MapMetaData
{
public:
	unsigned char m_pad00[0x28];
	unsigned int m_filesize; // +0x28
	unsigned int m_CRC;	  // +0x2C
};

bool operator<(const AsciiString &left, const AsciiString &right);

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	void updateCache();
};

extern MapCache *TheMapCache;

class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0)
	virtual void reset() = 0;								// slot 1
	V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
	virtual void setCurrentGroupRoom(int groupID) = 0;	   // slot 11
	virtual int getCurrentGroupRoom() = 0;				   // slot 12
	V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
	virtual int gs31() = 0;								  // slot 31
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50)
	virtual bool amIHost() = 0;							  // slot 51
	V(52)
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0; // slot 53
	V(54)
	virtual void setGameOptions() = 0;					   // slot 55
	V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70)
	virtual AsciiString &getPingString() = 0;				// slot 71
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	virtual bool isDisconnectedAfterGameStart(int *reason) = 0; // slot 88
#undef V
};

extern GameSpyInfoInterface *TheGameSpyInfo;

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
	union { bool isStagingRoom; int gameID; }; // +0x118
	unsigned char m_tail[0x1EC - 0x11C];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual bool isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest(const PeerRequest &request) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

// The players' ladder ranks sent to the host (no ledger names).
extern int g_Va00E02548;
extern int g_Va00E0254C;

class GameModePreferences
{
public:
	int rva0044D836();					// preferred color
	int rva0044D88C();					// preferred faction
	bool rva0044D774(GameSlot *slot);	 // preferred hero
	int getStrategicScenario();
	bool rva0044DB54(int *rules);
	AsciiString rva0044D986();			// preferred map

private:
	unsigned char m_pad[0x1C];
};

class AptMpGameSetup
{
public:
	bool InitGameInfoFromSaveGame(GameInfo *game);
	bool Init(GameInfo *game, int mode);
};

// The NAT negotiator at 0x00A063F8 and the connection grid, both deleted
// through vslot 0 and a separate operator delete.
class Rva005A6D47
{
public:
	virtual void *deleteInstance(int flags);
};

extern Rva005A6D47 *g_Va00E063F8;

class AptConnectionScreen
{
public:
	virtual void *deleteInstance(int flags);
};

struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
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
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x70 - 0x5C];
};

class AptOnlineCustomMatch : public CustomMatchScreen
{
public:
	void rva005A20A7();
	bool rva005A1EEE();
	void rva0059EE96(unsigned char a, unsigned char b);

private:
	AptMpGameSetup m_setup; // +0x70
	unsigned char m_pad071[0xEC - 0x71];
	int m_gameMode; // +0xEC
	unsigned char m_pad0f0[0x324 - 0xF0];
	int m_heroSlotValue; // +0x324
	unsigned char m_pad328[0x46C - 0x328];
	GameModePreferences m_prefs; // +0x46C
	int m_state; // +0x488
	unsigned char m_pad48c[0x4A4 - 0x48C];
	int m_groupRoom; // +0x4A4
	unsigned char m_pad4a8[0x4D4 - 0x4A8];
	AptConnectionScreen *m_connectionGrid; // +0x4D4
};

void AptOnlineCustomMatch::rva005A20A7()
{
	if (TheGameSpyGame && TheGameSpyGame->m_inProgress)
	{
		TheGameSpyGame->m_inProgress = false;

		int disconReason;
		if (TheGameSpyInfo->isDisconnectedAfterGameStart(&disconReason))
		{
			AsciiString disconMunkee;
			disconMunkee.format("GUI:GSDisconReason%d", disconReason);
			UnicodeString title, body;
			title = TheGameText->fetch("GUI:GSErrorTitle");
			body = TheGameText->fetch(disconMunkee);
			Rva00548C1ACleanup();
			GSMessageBoxOk(title, body);
			TheGameSpyInfo->reset();
			TheShell->rva0035BF0E();
			return;
		}

		if (TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->isConnected())
		{
			rva005A1EEE();
			return;
		}
		TheShell->rva0035BF0E();
		return;
	}

	Rva0059FF9DDo();
	m_groupRoom = TheGameSpyInfo->getCurrentGroupRoom();
	TheGameSpyInfo->setCurrentGroupRoom(0);
	TheMapCache->updateCache();
	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	GameSpyGameSlot *hostSlot = game->getGameSpySlot(0);
	hostSlot->m_isAccepted = true;
	if (TheGameSpyInfo->amIHost())
	{
		OptionPreferences natPref;
		bool loaded = m_setup.InitGameInfoFromSaveGame(game);
		if (!loaded)
		{
			hostSlot->m_color = m_prefs.rva0044D836();
			hostSlot->setPlayerTemplate(m_prefs.rva0044D88C());
			m_prefs.rva0044D774(hostSlot);
			for (int i = 1; i < 8; ++i)
			{
				GameSpyGameSlot *slot = game->getGameSpySlot(i);
				slot->setState(SLOT_OPEN, UnicodeString::TheEmptyString, &GameSlotConnectInfo());
			}
			if (m_gameMode == 1)
				game->m_strategicScenario = m_prefs.getStrategicScenario();
			int rules[10];
			m_prefs.rva0044DB54(rules);
			memcpy(game->m_rules, rules, sizeof(rules));
		}

		AsciiString mapName;
		if (m_gameMode == 1)
			mapName = "maps\\map wor mirkwood\\map wor mirkwood.map";
		else
			mapName = m_prefs.rva0044D986();
		game->setMap(mapName);
		mapName.toLower();
		MapCache::iterator it = TheMapCache->find(mapName);
		if (it != TheMapCache->end())
		{
			hostSlot->setMapAvailability(true);
			game->setMapCRC(it->second.m_CRC);
			game->setMapSize(it->second.m_filesize);
			if (!loaded)
				game->adjustSlotsForMap();
		}
		hostSlot->m_natBehavior = natPref.getFirewallBehavior();
		((Rva004FDB04 *)hostSlot)->rva004FDB04(TheGameSpyInfo->getPingString());
		hostSlot->m_1ac = TheGameSpyInfo->gs31();
	}
	else
	{
		bool loaded = m_setup.InitGameInfoFromSaveGame(game);
		OptionPreferences natPref;
		AsciiString options;
		PeerRequest req;
		UnicodeString uName = hostSlot->m_name;
		AsciiString aName;
		aName.translate(uName);
		req.peerRequestType = 0xD;
		req.isStagingRoom = true;
		req.id = "REQ/";
		req.nick = aName.str();
		if (!loaded)
		{
			options.format("PlayerTemplate=%d", m_prefs.rva0044D88C());
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
			options.format("Color=%d", m_prefs.rva0044D836());
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
			GameSlot heroSlot;
			m_prefs.rva0044D774(&heroSlot);
			options.format("Hero=%d", heroSlot.encodeHero());
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
			m_heroSlotValue = heroSlot.m_5c;
		}
		options.format("NAT=%d", natPref.getFirewallBehavior());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Ping=%s", TheGameSpyInfo->getPingString().str());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("LadderRank1v1=%d", g_Va00E02548);
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("LadderRank2v2=%d", g_Va00E0254C);
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		game->setMapCRC(game->m_mapCRC);
		game->setMapSize(game->m_mapSize);
	}

	m_setup.Init(game, 0);
	TheGameSpyInfo->setGameOptions();
	if (m_state == 5)
	{
		void *movie = m_owner->m_movie;
		Rva005FB5E6AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "GotoAndPlay", "_host");
		rva0059EE96(0, 1);
		m_state = 6;
	}
	else if (m_state == 11)
	{
		void *movie = m_owner->m_movie;
		Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "ClosePassword");
		movie = m_owner->m_movie;
		Rva005FB5E6AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, movie, v10(), "GotoAndPlay", "_join");
		m_state = 12;
		Rva00381C2DClear(1);
	}

	if (m_connectionGrid)
	{
		::operator delete(m_connectionGrid->deleteInstance(0));
		m_connectionGrid = 0;
	}
	if (g_Va00E063F8)
	{
		::operator delete(g_Va00E063F8->deleteInstance(0));
		g_Va00E063F8 = 0;
	}
}
