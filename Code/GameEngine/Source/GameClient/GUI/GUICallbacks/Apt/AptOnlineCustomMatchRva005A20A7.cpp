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
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
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
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

#include <string.h>

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

#include "../../../../../Include/GameClient/Shell.h"

extern Shell *TheShell;

#include "../../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

// The options file (0x14 bytes; its destructor is the pinned ~OptionPreferences).
#include "../../../../../Include/Common/OptionPreferences.h"

enum SlotState { SLOT_OPEN = 0 };

// Retail passes a zero DWORD and zero port WORD to GameSlot::setState.
#include "../../../../../Include/GameNetwork/GameSlotConnectInfo.h"

#include "../../../../../Include/GameNetwork/GameInfo.h"

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


#include "../../../../../Include/GameNetwork/GameSpyStagingRoom.h"

extern GameSpyStagingRoom *TheGameSpyGame;

#include "../../../../../Include/GameClient/MapMetaData.h"

bool operator<(const AsciiString &left, const AsciiString &right);

#include "../../../../../Include/GameClient/MapCache.h"

extern MapCache *TheMapCache;

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

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

// Descriptive names for the players' ladder ranks sent to the host.
extern int BfmeOnlineLadderRank1v1;
extern int BfmeOnlineLadderRank2v2;

#include "../../../../../Include/Common/GameModePreferences.h"

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

// Bind the existing NAT datum; retain this unit's access view at use sites.
struct NAT;
extern NAT *TheNAT;

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
			TheShell->popImmediate();
			return;
		}

		if (TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->isConnected())
		{
			rva005A1EEE();
			return;
		}
		TheShell->popImmediate();
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
				game->m_field58 = m_prefs.getStrategicScenario();
			int rules[10];
			m_prefs.rva0044DB54(rules);
			memcpy(game->m_field60, rules, sizeof(rules));
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
		hostSlot->m_field40 = natPref.getFirewallBehavior();
		((Rva004FDB04 *)hostSlot)->rva004FDB04(TheGameSpyInfo->getPingString());
		hostSlot->m_1ac = TheGameSpyInfo->getLocalProfileID();
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
			m_heroSlotValue = heroSlot.m_field5C;
		}
		options.format("NAT=%d", natPref.getFirewallBehavior());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Ping=%s", TheGameSpyInfo->getPingString().str());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("LadderRank1v1=%d", BfmeOnlineLadderRank1v1);
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("LadderRank2v2=%d", BfmeOnlineLadderRank2v2);
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
	if (TheNAT)
	{
		::operator delete(((Rva005A6D47 *)TheNAT)->deleteInstance(0));
		TheNAT = 0;
	}
}
