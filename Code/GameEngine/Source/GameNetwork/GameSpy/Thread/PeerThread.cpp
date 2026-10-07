// cl: /DBFME_ASCII_KEEP_COPY_SET_BODY /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /O1 /G7 /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PeerThread.cpp //////////////////////////////////////////////////////
// GameSpy Peer (chat) thread
// This thread communicates with GameSpy's chat server
// and talks through a message queue with the rest of
// the game.
// Author: Matthew D. Campbell, June 2002

// Retail also calls _snprintf through msvcrt's import slot; stdio.h is read
// here under /D_CRTIMP= and only that one function is declared as the import.
#define _snprintf _snprintf_unimported
#include <stdio.h>
#undef _snprintf
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, size_t count, const char *format, ...);
// Retail imports character tests and string comparisons but uses game free
// for STL storage. Load those CRT declarations with imports before the local
// allocator headers inherit /D_CRTIMP=.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <ctype.h>
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#define atoi atoi_unimported
#include <stdlib.h>
#undef atoi
extern "C" __declspec(dllimport) int __cdecl atoi(const char *string);
// STLport frees through the C++-linkage free retail's containers call, which
// keeps the unwind-state stores around their inlined destructors.
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#undef free

#include "Common/Registry.h"
#include "Common/StackDump.h"
#include "Common/UserPreferences.h"
#include "Common/Version.h"
#include "GameNetwork/IPEnumeration.h"
// The GameSpy SDK is C: under /EHsc its callees are nothrow, which is what
// lets Thread_Function batch its stack pops inside the try. BFME 2's SDK
// header maps the string-taking calls to their ANSI entry points when
// GSI_UNICODE is off (rowed as peerXxxA in GameSpy/peer/*.c and qr2/qr2.c);
// the sweep Peer.h predates that block, so it is restated here.
#define peerConnect                     peerConnectA
#define peerCreateStagingRoomWithSocket peerCreateStagingRoomWithSocketA
#define peerGetPlayerFlags              peerGetPlayerFlagsA
#define peerGetPlayerInfoNoWait         peerGetPlayerInfoNoWaitA
#define peerJoinStagingRoom             peerJoinStagingRoomA
#define peerLeaveRoom                   peerLeaveRoomA
#define peerListGroupRooms              peerListGroupRoomsA
#define peerMessagePlayer               peerMessagePlayerA
#define peerMessageRoom                 peerMessageRoomA
#define peerSetRoomWatchKeys            peerSetRoomWatchKeysA
#define peerSetTitle                    peerSetTitleA
#define peerStartListingGames           peerStartListingGamesA
#define peerUTMPlayer                   peerUTMPlayerA
#define peerUTMRoom                     peerUTMRoomA
#define qr2_buffer_add                  qr2_buffer_addA
#define qr2_register_key                qr2_register_keyA
// These two keep the C++ spellings their addresses already carry:
// peerParseQuery is rowed so in PeerParseQueryThunk.cpp, and peerGetLocalIP's
// body is owned by the folded GadgetListBoxGetEnabledSelectedItemColor row.
#define peerGetLocalIP  peerGetLocalIP_sdkC
#define peerParseQuery  peerParseQuery_sdkC
extern "C" {
#include "GameSpy/Peer/Peer.h"
}
#undef peerGetLocalIP
#undef peerParseQuery
unsigned int peerGetLocalIP(PEER peer) throw();
PEERBool peerParseQuery(PEER peer, char *data, int len, struct sockaddr *from) throw();
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "PeerThreadRetail.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

#include "strtok_r.h"
#include "mutex.h"
#include "thread.h"

#include "Common/MiniLog.h"

// The retail58B append body is owned by StlportNarrowAppendCStr.cpp.
namespace _STL { template <> string &string::append(const char *); }
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *, const char *);

// Native callback uses the already recovered GameSpy C API entry.
extern "C" void peerGetPlayerProfileIDA(PEER, const char *, void *, void *, PEERBool);
#pragma comment(linker, "/alternatename:??0PeerResponse@@QAE@XZ=??0BfmeOpaqueOwnedRecord840@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1PeerResponse@@QAE@XZ=??1BfmeOpaqueOwnedRecord840@@QAE@XZ")

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// enable this for trying to track down why SBServers are losing their keyvals  -MDC 2/20/2003
#undef SERVER_DEBUGGING
#ifdef SERVER_DEBUGGING
void CheckServers(PEER peer);
#endif // SERVER_DEBUGGING

#ifdef DEBUG_LOGGING
//#define PING_TEST
static LogClass s_pingLog("Ping.txt");
#define PING_LOG(x) s_pingLog.log x
#else // DEBUG_LOGGING
#define PING_LOG(x) {}
#endif // DEBUG_LOGGING

#ifdef DEBUG_LOGGING
static LogClass s_stateChangedLog("StateChanged.txt");

#define STATECHANGED_LOG(x) s_stateChangedLog.log x

#else // DEBUG_LOGGING

#define STATECHANGED_LOG(x) {}

#endif // DEBUG_LOGGING

// we should always be using broadcast keys from now on.  Remove the old code sometime when
// we're not in a rush, ok?
// -MDC 2/14/2003
#define USE_BROADCAST_KEYS

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

int isThreadHosting = 0;
static UnsignedInt s_lastStateChangedHeartbeat = 0;
static Bool s_wantStateChangedHeartbeat = FALSE;
static UnsignedInt s_heartbeatInterval = 10000;

static SOCKET qr2Sock = INVALID_SOCKET;

enum
{
	EXECRC_KEY = NUM_RESERVED_KEYS + 1,
	INICRC_KEY,
	PW_KEY,
	OBS_KEY,
  USE_STATS_KEY,
	LADIP_KEY,
	LADPORT_KEY,
	PINGSTR_KEY,
	NUMPLAYER_KEY,
	MAXPLAYER_KEY,
	NUMOBS_KEY,
	NAME__KEY,
	FACTION__KEY,
	COLOR__KEY,
	WINS__KEY,
	LOSSES__KEY
};

#define EXECRC_STR		"exeCRC"
#define INICRC_STR		"iniCRC"
#define PW_STR				"pw"
#define OBS_STR				"obs"
#define USE_STATS_STR "stat"
#define LADIP_STR			"ladIP"
#define LADPORT_STR		"ladPort"
#define PINGSTR_STR		"pings"
#define NUMPLAYER_STR	"numRealPlayers"
#define MAXPLAYER_STR	"maxRealPlayers"
#define NUMOBS_STR		"numObservers"
#define NAME__STR			"name"
#define FACTION__STR	"faction"
#define COLOR__STR		"color"
#define WINS__STR			"wins"
#define LOSSES__STR		"losses"

//-------------------------------------------------------------------------

// Target vtable getters read PeerThreadClass connection bytes at +0x50/+0x51;
// the donor class puts the same Bool members at +0x58/+0x59. Keep the target
// offsets local to these queue getters instead of changing the class layout.
struct BfmePeerThreadStatusView {
	UnsignedByte unknown_00[0x50];
	Bool m_isConnecting;
	Bool m_isConnected;
	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }
};
struct Rva0009990D {
	void *pointer;
	Rva0009990D() : pointer(0) {}
	void clear();
	void set(void *pointer);
	~Rva0009990D() { clear(); }
};
struct Rva006105F0 { void stop(); };
struct Rva0038909EPeerThreadDtorView {
	virtual void *destroy(unsigned int flags);
};
// The vtable installed by target constructor 0x38AAEB has scalar deleting
// destructor at slot 0 and ThreadClass::Execute at slot +4. The object remains
// address-derived because the target-only tail/layout is not otherwise named.
struct Rva0038AAEBThreadObject {
	void *targetVtable;
	unsigned char opaqueTail[0x4ac];
	Rva0038AAEBThreadObject(MutexClass *queueMutex);
};
typedef char Rva0038AAEBThreadObject_size_check[
	sizeof(Rva0038AAEBThreadObject) == 0x4b0 ? 1 : -1];
struct Rva0038AAEBThreadExecuteVtable {
	virtual void scalarDeletingDtorSlot();
	virtual void executeSlot();
};

// Target's request queue advances in 0x1EC-byte steps. Its push_back body is
// already verified under this size-only record view. Target members and payload
// meanings remain unclaimed; PeerRequest is donor context for the queue role.
struct BfmeOpaqueOwnedRecord492 {
	union { unsigned int alignmentWitness; unsigned char bytes[492]; };
	BfmeOpaqueOwnedRecord492();
	BfmeOpaqueOwnedRecord492(const BfmeOpaqueOwnedRecord492 &);
	~BfmeOpaqueOwnedRecord492();
};
typedef char BfmeOpaqueOwnedRecord492_size_check[
	sizeof(BfmeOpaqueOwnedRecord492) == 492 ? 1 : -1];
typedef _STL::deque<BfmeOpaqueOwnedRecord492,
	_STL::allocator<BfmeOpaqueOwnedRecord492> > BfmeRequestDeque492;

// The vtable-selected response queue advances by 0x348 bytes. Keep its payload
// owner opaque; STLport queue stores its deque as the sole member `c`.
struct BfmeOpaqueOwnedRecord840 {
	union { unsigned int alignmentWitness; unsigned char bytes[840]; };
	BfmeOpaqueOwnedRecord840();
	BfmeOpaqueOwnedRecord840(const BfmeOpaqueOwnedRecord840 &);
	~BfmeOpaqueOwnedRecord840();
};
typedef char BfmeOpaqueOwnedRecord840_size_check[
	sizeof(BfmeOpaqueOwnedRecord840) == 840 ? 1 : -1];
typedef _STL::deque<BfmeOpaqueOwnedRecord840,
	_STL::allocator<BfmeOpaqueOwnedRecord840> > BfmeResponseDeque840;
typedef std::queue<BfmeOpaqueOwnedRecord492> RequestQueue;
typedef std::queue<BfmeOpaqueOwnedRecord840> ResponseQueue;

class PeerThreadClass;

class GameSpyPeerMessageQueue : public GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueue();
	GameSpyPeerMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );

	virtual void addRequest( const PeerRequest& req );
	virtual Bool getRequest( PeerRequest& req );

	virtual void addResponse( const PeerResponse& resp );
	virtual Bool getResponse( PeerResponse& resp );

	virtual SerialAuthResult getSerialAuthResult( void ) { return m_serialAuth; }
	void setSerialAuthResult( SerialAuthResult result ) { m_serialAuth = result; }

	PeerThreadClass* getThread( void );

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	PeerThreadClass *m_thread;

	SerialAuthResult m_serialAuth;

	// Target constructor 0x38E171 constructs this MutexClass at +0x6C and clears
	// +0x74. Target startThread stores an 8-byte heap owner there via 0x998EA;
	// endThread and this owner's destructor release it via 0x9990D. Its payload
	// identity remains opaque. Matched createNewMessageQueue allocates 0x78 bytes.
	MutexClass _bfme_hole_thirdMutex;
	Rva0009990D _bfme_hole_tailOwner;
};

GameSpyPeerMessageQueueInterface* GameSpyPeerMessageQueueInterface::createNewMessageQueue( void )
{
	return NEW GameSpyPeerMessageQueue;
}

GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
#define MESSAGE_QUEUE ((GameSpyPeerMessageQueue *)TheGameSpyPeerMessageQueue)

//-------------------------------------------------------------------------

// Native enum callback at 38B5DB stores the completion flag at +48C.
// Preserve this measured view without shifting the donor thread fields.
// Native player-left callback reads the quickmatch status at +294.
struct BfmePeerQMState { unsigned char unknown[0x294]; QMStatus status; };
struct BfmePeerEnumState { unsigned char unknown[0x48c]; Bool sawEnd; };

class PeerThreadClass : public ThreadClass
{

public:
	PeerThreadClass() : ThreadClass()
	{
		//Added By Sadullah Nader
		//Initializations inserted
		m_roomJoined = m_allowObservers = m_hasPassword = FALSE;
    m_useStats = TRUE;
		m_exeCRC = m_iniCRC = 0;
		m_gameVersion = 0;
		m_ladderPort = 0;
		m_localRoomID = 0;
		m_maxPlayers = 0;
		m_numObservers = 0;
		m_maxPlayers = 0;
		m_qmGroupRoom = 0;
		m_sawEndOfEnumPlayers = m_sawMatchbot = FALSE;
		m_sawCompleteGameList = FALSE;
		//
		m_isConnecting = m_isConnected = false; 
		m_groupRoomID = m_profileID = 0;
		m_nextStagingServer = 1; m_stagingServers.clear();
		m_pingStr = ""; m_mapName = ""; m_ladderIP = ""; m_isHosting = false;
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			m_playerNames[i] = "";
			
			//Added by Sadullah Nader
			//Initializations 
			m_playerColors[i] = 0;
			m_playerFactions[i] = 0;
			m_playerLosses[i] = 0;
			m_playerProfileID[i] = 0;
			m_playerWins[i] = 0;

			//
		}
	}

	void Thread_Function();

	void markAsDisconnected( void ) { m_isConnecting = m_isConnected = false; }

	void connectCallback( PEER peer, PEERBool success );
	void nickErrorCallback( PEER peer, Int type, const char *nick );

	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }

	Int addServerToMap( SBServer server );
	Int removeServerFromMap( SBServer server );
	void clearServers( void );
	SBServer findServerByID( Int id );
	Int findServer( SBServer server );

	// get info about the game we are hosting
	Bool isHosting( void ) { return m_isHosting; }
	void stopHostingAlready(PEER peer);
	Bool hasPassword( void ) { return m_hasPassword; }
	Bool allowObservers( void ) { return m_allowObservers; }
  Bool useStats(void) const { return m_useStats; }
	std::string getMapName( void ) { return m_mapName; }
	UnsignedInt exeCRC( void ) { return m_exeCRC; }
	UnsignedInt iniCRC( void ) { return m_iniCRC; }
	UnsignedInt gameVersion( void ) { return m_gameVersion; }
	std::wstring getLocalStagingServerName( void ) { return m_localStagingServerName; }
	Int getLocalRoomID( void ) { return m_localRoomID; }
	std::string ladderIP( void ) { return m_ladderIP; }
	UnsignedShort ladderPort( void ) { return m_ladderPort; }
	std::string pingStr( void ) { return m_pingStr; }
	std::string getPlayerName(Int idx) { return m_playerNames[idx]; }
	Int getPlayerWins(Int idx) { return m_playerWins[idx]; }
	Int getPlayerLosses(Int idx) { return m_playerLosses[idx]; }
	Int getPlayerProfileID(Int idx) { return m_playerProfileID[idx]; }
	Int getPlayerFaction(Int idx) { return m_playerFactions[idx]; }
	Int getPlayerColor(Int idx) { return m_playerColors[idx]; }
	Int getNumPlayers(void) { return m_numPlayers; }
	Int getMaxPlayers(void) { return m_maxPlayers; }
	Int getNumObservers(void) { return m_numObservers; }

	void roomJoined( Bool val ) { m_roomJoined = val; }
	void setQMGroupRoom( Int groupID ) { m_qmGroupRoom = groupID; }
	void sawEndOfEnumPlayers( void ) { reinterpret_cast<BfmePeerEnumState *>(this)->sawEnd = true; }
	void sawMatchbot(std::string bot); // Target body lives in PeerThreadMatchbot.cpp.
	QMStatus getQMStatus( void ) { return reinterpret_cast<BfmePeerQMState *>(this)->status; }
	void handleQMMatch(PEER peer, Int mapIndex, Int seed, char *playerName[MAX_SLOTS], char *playerIP[MAX_SLOTS], char *playerSide[MAX_SLOTS], char *playerColor[MAX_SLOTS], char *playerNAT[MAX_SLOTS]);
	std::string getQMBotName(void);
	Int getQMGroupRoom( void ) { return m_qmGroupRoom; }
	Int getQMLadder( void ) { return m_qmInfo.QM.ladderID; }

	Int getCurrentGroupRoom(void) { return m_groupRoomID; }

#ifdef USE_BROADCAST_KEYS
	void pushStatsToRoom(PEER peer);
	void getStatsFromRoom(PEER peer, RoomType roomType);
	void trackStatsForPlayer(RoomType roomType, const char *nick, const char *key, const char *val);
	int lookupStatForPlayer(RoomType roomType, const char *nick, const char *key);
	void clearPlayerStats(RoomType roomType);
#endif // USE_BROADCAST_KEYS

	void setSawCompleteGameList(Bool val) { m_sawCompleteGameList = val; }
	Bool getSawCompleteGameList() { return m_sawCompleteGameList; }

private:
	Bool m_isConnecting;
	Bool m_isConnected;
	std::string m_loginName, m_originalName, m_password, m_email;
	Int m_profileID;
	Int m_groupRoomID;
	Bool m_sawCompleteGameList;

#ifdef USE_BROADCAST_KEYS
	enum { NumKeys = 9, ValBufSize = 20 };
	static const char *s_keys[NumKeys];
	static char s_valueBuffers[NumKeys][ValBufSize];
	static const char *s_values[NumKeys];

	typedef std::map<std::string, int> PlayerStatMap;
	PlayerStatMap m_groupRoomStats;
	PlayerStatMap m_stagingRoomStats;
	std::string packStatKey(const char *nick, const char *key);
#endif // USE_BROADCAST_KEYS

	// game-hosting info for GOA callbacks
	Bool m_isHosting;
	Bool m_hasPassword;
	std::string m_mapName;
	std::string m_playerNames[MAX_SLOTS];
	UnsignedInt m_exeCRC;
	UnsignedInt m_iniCRC;
	UnsignedInt m_gameVersion;
	Bool m_allowObservers;
  Bool m_useStats;
	std::string m_pingStr;
	std::string m_ladderIP;
	UnsignedShort m_ladderPort;
	Int m_playerWins[MAX_SLOTS];
	Int m_playerLosses[MAX_SLOTS];
	Int m_playerProfileID[MAX_SLOTS];
	Int m_playerColors[MAX_SLOTS];
	Int m_playerFactions[MAX_SLOTS];
	Int m_numPlayers;
	Int m_maxPlayers;
	Int m_numObservers;

	Int m_nextStagingServer;
	std::map<Int, SBServer> m_stagingServers;
	std::wstring m_localStagingServerName;
	Int m_localRoomID;

	void doQuickMatch( PEER peer );
	QMStatus m_qmStatus;
	PeerRequest m_qmInfo;
	Bool m_roomJoined;
	Int m_qmGroupRoom;
	Bool m_sawEndOfEnumPlayers;
	Bool m_sawMatchbot;
	std::string m_matchbotName;
};

#ifdef USE_BROADCAST_KEYS
// Native data table DC0768 contains these nine literal pointers in this order.
const char* PeerThreadClass::s_keys[NumKeys] = { "b_locale", "b_wins", "b_losses", "b_points", "b_side", "b_pre", "b_BSide", "b_rank1v1", "b_rank2v2" };
char PeerThreadClass::s_valueBuffers[NumKeys][20] = { "", "", "", "", "", "" };
const char* PeerThreadClass::s_values[NumKeys] = { s_valueBuffers[0], s_valueBuffers[1], s_valueBuffers[2],
	s_valueBuffers[3], s_valueBuffers[4], s_valueBuffers[5]};

// Player-stat writes are recovered in PeerThreadStats.cpp.

// Stat-key concatenation is recovered in PeerThreadStats.cpp.

// Stat lookup is recovered in PeerThreadLookupStat.cpp.

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadClearPlayerStats.cpp
void PeerThreadClass::clearPlayerStats(RoomType roomType)
{
	switch (roomType)
	{
		case GroupRoom:
			m_groupRoomStats.clear();
			break;
		case StagingRoom:
			m_stagingRoomStats.clear();
			break;
	}
}

// ?pushStatsToRoom@PeerThreadClass@@ present-unmatched
void PeerThreadClass::pushStatsToRoom(PEER peer)
{
	DEBUG_LOG(("PeerThreadClass::pushStatsToRoom(): stats are %s=%s,%s=%s,%s=%s,%s=%s,%s=%s,%s=%s\n",
		s_keys[0], s_values[0],
		s_keys[1], s_values[1],
		s_keys[2], s_values[2],
		s_keys[3], s_values[3],
		s_keys[4], s_values[4],
		s_keys[5], s_values[5]));
	peerSetRoomKeys(peer, GroupRoom, m_loginName.c_str(), 6, s_keys, s_values);
	peerSetRoomKeys(peer, StagingRoom, m_loginName.c_str(), 6, s_keys, s_values);
}

void getRoomKeysCallback(PEER peer, PEERBool success, RoomType roomType, const char *nick, int num, char **keys, char **values, void *param);
extern "C" void peerGetRoomKeysA(PEER, RoomType, const char *, int, const char **, void *, void *, int);
void PeerThreadClass::getStatsFromRoom(PEER peer, RoomType roomType)
{
	peerGetRoomKeysA(peer, roomType, "*", NumKeys, s_keys, reinterpret_cast<void *>(getRoomKeysCallback), this, PEERFalse);
}
#endif // USE_BROADCAST_KEYS

// BFME keeps m_nextStagingServer at PeerThreadClass+0x208 and the staging map
// straight after it at +0x20c, where this tree lands them at +0x1f8 and
// +0x1fc. Per-site, so removeServerFromMap below keeps its own spelling.
#define BFME_PEER_NEXTSTAGING(p) (*(Int *)((char *)(p) + 0x208))
#define BFME_PEER_STAGINGMAP(p)  (*(std::map<Int, SBServer> *)((char *)(p) + 0x20c))
// ?addServerToMap@PeerThreadClass@@QAEHPAU_SBServer@@@Z present-unmatched
Int PeerThreadClass::addServerToMap( SBServer server )
{
	Int val = BFME_PEER_NEXTSTAGING(this)++;
	BFME_PEER_STAGINGMAP(this)[val] = server;
	return val;
}

// ?removeServerFromMap@PeerThreadClass@@ present-unmatched
Int PeerThreadClass::removeServerFromMap( SBServer server )
{
	for (std::map<Int, SBServer>::iterator it = m_stagingServers.begin(); it != m_stagingServers.end(); ++it)
	{
		if (it->second == server)
		{
			Int val = it->first;
			m_stagingServers.erase(it);
			return val;
		}
	}

	return 0;
}

// ?clearServers@PeerThreadClass@@ present-unmatched
void PeerThreadClass::clearServers( void )
{
	m_stagingServers.clear();
}

// ?findServerByID@PeerThreadClass@@ present-unmatched
SBServer PeerThreadClass::findServerByID( Int id )
{
	std::map<Int, SBServer>::iterator it = m_stagingServers.find(id);
	if (it != m_stagingServers.end())
	{
		SBServer server = it->second;
		if (server && !server->keyvals)
		{
			DEBUG_CRASH(("Referencing a missing server!"));
			return 0;
		}
		return it->second;
	}
	return 0;
}

// ?findServer@PeerThreadClass@@ present-unmatched
Int PeerThreadClass::findServer( SBServer server )
{
	char tmp[10] = "";
	const char *newName = SBServerGetStringValue(server, "gamename", tmp);
	UnsignedInt newPrivateIP = SBServerGetPrivateInetAddress(server);
	UnsignedShort newPrivatePort = SBServerGetPrivateQueryPort(server);
	UnsignedInt newPublicIP = SBServerGetPublicInetAddress(server);

	SBServer serverToRemove = NULL;

	for (std::map<Int, SBServer>::iterator it = m_stagingServers.begin(); it != m_stagingServers.end(); ++it)
	{
		if (it->second == server)
		{
			return it->first;
		}
		else
		{
			const char *oldName = SBServerGetStringValue(it->second, "gamename", tmp);
			UnsignedInt oldPrivateIP = SBServerGetPrivateInetAddress(it->second);
			UnsignedShort oldPrivatePort = SBServerGetPrivateQueryPort(it->second);
			UnsignedInt oldPublicIP = SBServerGetPublicInetAddress(it->second);
			if (!strcmp(oldName, newName) &&
				oldPrivateIP == newPrivateIP &&
				oldPublicIP == newPublicIP &&
				oldPrivatePort == newPrivatePort)
			{
				serverToRemove = it->second;
			}
		}
	}

	if (serverToRemove)
	{
		// this is the same as another game - it has just migrated to another port.  Remove the old and replace it.
		PeerResponse resp;
		resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
		resp.stagingRoom.id = removeServerFromMap( serverToRemove );
		resp.stagingRoom.action = PEER_REMOVE;
		resp.stagingRoom.isStaging = TRUE;
		resp.stagingRoom.percentComplete = -1;
		TheGameSpyPeerMessageQueue->addResponse(resp);
	}

	return addServerToMap(server);
}

static enum CallbackType
{
	CALLBACK_CONNECT,
	CALLBACK_ERROR,
	CALLBACK_RECVMESSAGE,
	CALLBACK_RECVREQUEST,
	CALLBACK_RECVSTATUS,
	CALLBACK_MAX
};

void connectCallbackWrapper( PEER peer, PEERBool success, void *param )
{
#ifdef SERVER_DEBUGGING
	DEBUG_LOG(("In connectCallbackWrapper()\n"));
	CheckServers(peer);
#endif // SERVER_DEBUGGING
	if (param != NULL)
	{
		((PeerThreadClass *)param)->connectCallback( peer, success );
	}
}

void nickErrorCallbackWrapper( PEER peer, Int type, const char *nick, void *param )
{
	if (param != NULL)
	{
		((PeerThreadClass *)param)->nickErrorCallback( peer, type, nick );
	}
}

static void joinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param);

//-------------------------------------------------------------------------

GameSpyPeerMessageQueue::GameSpyPeerMessageQueue()
{
	m_thread = NULL;
	m_serialAuth = SERIAL_OK;
}

GameSpyPeerMessageQueue::~GameSpyPeerMessageQueue()
{
	endThread();
}

void GameSpyPeerMessageQueue::startThread( void )
{
	if (m_thread)
		return;
	_bfme_hole_tailOwner.set(NEW MutexClass::LockClass(
		_bfme_hole_thirdMutex, -1));
	Rva0038AAEBThreadObject *thread =
		NEW Rva0038AAEBThreadObject(&_bfme_hole_thirdMutex);
	m_thread = (PeerThreadClass *)thread;
	((Rva0038AAEBThreadExecuteVtable *)thread)->executeSlot();
}

void GameSpyPeerMessageQueue::endThread( void )
{
	if (m_thread) {
		_bfme_hole_tailOwner.clear();
		((Rva006105F0 *)m_thread)->stop();
		void *threadToFree;
		if (m_thread)
			threadToFree = ((Rva0038909EPeerThreadDtorView *)m_thread)->destroy(0);
		else
			threadToFree = NULL;
		::operator delete(threadToFree);
	}
	m_thread = NULL;
}

Bool GameSpyPeerMessageQueue::isThreadRunning( void )
{
	return (m_thread) ? m_thread->Is_Running() : false;
}

Bool GameSpyPeerMessageQueue::isConnected( void )
{
	return (m_thread) ? ((BfmePeerThreadStatusView *)m_thread)->isConnected() : false;
}

Bool GameSpyPeerMessageQueue::isConnecting( void )
{
	return (m_thread) ? ((BfmePeerThreadStatusView *)m_thread)->isConnecting() : false;
}

void GameSpyPeerMessageQueue::addRequest( const PeerRequest& req )
{
	MutexClass::LockClass m(m_requestMutex);
	if (m.Failed())
		return;

	((BfmeRequestDeque492 *)&m_requests)->push_back(
		*(const BfmeOpaqueOwnedRecord492 *)&req);
}

//PeerRequest GameSpyPeerMessageQueue::getRequest( void )
Bool GameSpyPeerMessageQueue::getRequest( PeerRequest& req )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;

	if (m_requests.empty())
		return false;
	req = *(const PeerRequest *)&m_requests.front();
	((BfmeRequestDeque492 *)&m_requests)->pop_front();
	return true;
}

void GameSpyPeerMessageQueue::addResponse( const PeerResponse& resp )
{
	if (resp.nick == "(END)")
		return;

	MutexClass::LockClass m(m_responseMutex);
	if (m.Failed())
		return;

	((BfmeResponseDeque840 *)&m_responses)->push_back(
		*(const BfmeOpaqueOwnedRecord840 *)&resp);
}

//PeerResponse GameSpyPeerMessageQueue::getResponse( void )
Bool GameSpyPeerMessageQueue::getResponse( PeerResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;

	if (m_responses.empty())
		return false;
	resp = *(const PeerResponse *)&m_responses.front();
	((BfmeResponseDeque840 *)&m_responses)->pop_front();
	return true;
}

// ?getThread@GameSpyPeerMessageQueue@@QAEPAVPeerThreadClass@@XZ present-unmatched
PeerThreadClass* GameSpyPeerMessageQueue::getThread( void )
{
	return m_thread;
}

//-------------------------------------------------------------------------
static void disconnectedCallback(PEER peer, const char * reason, void * param);
static void roomMessageCallback(PEER peer, RoomType roomType, const char * nick, const char * message, MessageType messageType, void * param);
void playerMessageCallback(PEER peer, const char * nick, const char * message, MessageType messageType, void * param);
static void playerJoinedCallback(PEER peer, RoomType roomType, const char * nick, void * param);
static void playerLeftCallback(PEER peer, RoomType roomType, const char * nick, const char * reason, void * param);
static void playerChangedNickCallback(PEER peer, RoomType roomType, const char * oldNick, const char * newNick, void * param);
static void playerInfoCallback(PEER peer, RoomType roomType, const char * nick, unsigned int IP, int profileID, void * param);
static void playerFlagsChangedCallback(PEER peer, RoomType roomType, const char * nick, int oldFlags, int newFlags, void * param);
static void listingGamesCallback(PEER peer, PEERBool success, const char * name, SBServer server, PEERBool staging, int msg, Int percentListed, void * param);
void roomUTMCallback(PEER peer, RoomType roomType, const char * nick, const char * command, const char * parameters, PEERBool authenticated, void * param);
void playerUTMCallback(PEER peer, const char * nick, const char * command, const char * parameters, PEERBool authenticated, void * param);
static void gameStartedCallback(PEER peer, UnsignedInt IP, const char *message, void *param);
static void globalKeyChangedCallback(PEER peer, const char *nick, const char *key, const char *val, void *param);
static void roomKeyChangedCallback(PEER peer, RoomType roomType, const char *nick, const char *key, const char *val, void *param);

// convenience function to set buddy status
static void updateBuddyStatus( GameSpyBuddyStatus status, Int groupRoom = 0, std::string gameName = "" )
{
	if (!TheGameSpyBuddyMessageQueue)
		return;

	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	switch(status)
	{
		case BUDDY_OFFLINE:
			req.arg.status.status = GP_OFFLINE;
			strcpy(req.arg.status.statusString, "Offline");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_ONLINE:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Online");
			strcpy(req.arg.status.locationString, "");
			break;
		case BUDDY_LOBBY:
			req.arg.status.status = GP_CHATTING;
			strcpy(req.arg.status.statusString, "Chatting");
			sprintf(req.arg.status.locationString, "%d", groupRoom);
			break;
		case BUDDY_STAGING:
			req.arg.status.status = GP_STAGING;
			strcpy(req.arg.status.statusString, "Staging");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_LOADING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Loading");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_PLAYING:
			req.arg.status.status = GP_PLAYING;
			strcpy(req.arg.status.statusString, "Playing");
			sprintf(req.arg.status.locationString, "%s", gameName.c_str());
			break;
		case BUDDY_MATCHING:
			req.arg.status.status = GP_ONLINE;
			strcpy(req.arg.status.statusString, "Matching");
			strcpy(req.arg.status.locationString, "");
			break;
	}
	DEBUG_LOG(("updateBuddyStatus %d:%s\n", req.arg.status.status, req.arg.status.statusString));
	TheGameSpyBuddyMessageQueue->addRequest(req);
}

static void createRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param)
{
	Int *s = (Int *)param;
	if (s)
		*s = result;
}

static const char * KeyTypeToString(qr2_key_type type)
{
	switch(type)
	{
	case key_server:
		return "server";
	case key_player:
		return "player";
	case key_team:
		return "team";
	}

	return "Unkown key type";
}

static const char * ErrorTypeToString(qr2_error_t error)
{
	switch(error)
	{
	case e_qrnoerror:
		return "noerror";
	case e_qrwsockerror:
		return "wsockerror";
	case e_qrbinderror:
		return "rbinderror";
	case e_qrdnserror:
		return "dnserror";
	case e_qrconnerror:
		return "connerror";
	}

	return "Unknown error type";
}

static void QRServerKeyCallback
(
	PEER peer,
	int key,
	qr2_buffer_t buffer,
	void * param
)
{
	//DEBUG_LOG(("QR_SERVER_KEY | %d (%s)\n", key, qr2_registered_key_list[key]));
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("QRServerKeyCallback: bailing because of no thread info\n"));
		return;
	}

	if (!t->isHosting())
		t->stopHostingAlready(peer);

#ifdef DEBUG_LOGGING
	AsciiString val = "";
#define ADD(x) { qr2_buffer_add(buffer, x); val = x; }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); val.format("%d",x); }
#else
#define ADD(x) { qr2_buffer_add(buffer, x); }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); }
#endif

	switch(key)
	{
	case HOSTNAME_KEY:
		ADD(t->getPlayerName(0).c_str());
		break;
	case GAMEVER_KEY:
		ADDINT(t->gameVersion());
		break;
	case EXECRC_KEY:
		ADDINT(t->exeCRC());
		break;
	case INICRC_KEY:
		ADDINT(t->iniCRC());
		break;
	case GAMENAME_KEY:
		{
			std::string tmp = t->getPlayerName(0);
			tmp.append(" ");
			tmp.append(WideCharStringToMultiByte(t->getLocalStagingServerName().c_str()));
			ADD(tmp.c_str());
		}
		break;
	case MAPNAME_KEY:
		ADD(t->getMapName().c_str());
		break;
	case PW_KEY:
		ADDINT(t->hasPassword());
		break;
	case OBS_KEY:
		ADDINT(t->allowObservers());
		break;
  case USE_STATS_KEY:
    ADDINT(t->useStats());
    break;
	case LADIP_KEY:
		ADD(t->ladderIP().c_str());
		break;
	case LADPORT_KEY:
		ADDINT(t->ladderPort());
		break;
	case PINGSTR_KEY:
		ADD(t->pingStr().c_str());
		break;
	case NUMPLAYER_KEY:
		ADDINT(t->getNumPlayers());
		break;
	case MAXPLAYER_KEY:
		ADDINT(t->getMaxPlayers());
		break;
	case NUMOBS_KEY:
		ADDINT(t->getNumObservers());
		break;
	default:
		ADD("");
		//DEBUG_LOG(("QR_SERVER_KEY | %d (%s)\n", key, qr2_registered_key_list[key]));
		break;
	}

	DEBUG_LOG(("QR_SERVER_KEY | %d (%s) = [%s]\n", key, qr2_registered_key_list[key], val.str()));
}

static void QRPlayerKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void * param
)
{
	//DEBUG_LOG(("QR_PLAYER_KEY | %d | %d (%s)\n", key, index, qr2_registered_key_list[key]));
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("QRPlayerKeyCallback: bailing because of no thread info\n"));
		return;
	}

	if (!t->isHosting())
		t->stopHostingAlready(peer);

#undef ADD
#undef ADDINT
#ifdef DEBUG_LOGGING
	AsciiString val = "";
#define ADD(x) { qr2_buffer_add(buffer, x); val = x; }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); val.format("%d",x); }
#else
#define ADD(x) { qr2_buffer_add(buffer, x); }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); }
#endif

	switch(key)
	{
	case NAME__KEY:
		ADD(t->getPlayerName(index).c_str());
		break;
	case WINS__KEY:
		ADDINT(t->getPlayerWins(index));
		break;
	case LOSSES__KEY:
		ADDINT(t->getPlayerLosses(index));
		break;
	case PID__KEY:
		ADDINT(t->getPlayerProfileID(index));
		break;
	case FACTION__KEY:
		ADDINT(t->getPlayerLosses(index));
		break;
	case COLOR__KEY:
		ADDINT(t->getPlayerLosses(index));
		break;
	default:
		ADD("");
		//DEBUG_LOG(("QR_PLAYER_KEY | %d | %d (%s)\n", key, index, qr2_registered_key_list[key]));
		break;
	}

	DEBUG_LOG(("QR_PLAYER_KEY | %d | %d (%s) = [%s]\n", key, index, qr2_registered_key_list[key], val.str()));
}

static void QRTeamKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void * param
)
{
	//DEBUG_LOG(("QR_TEAM_KEY | %d | %d\n", key, index));

	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("QRTeamKeyCallback: bailing because of no thread info\n"));
		return;
	}
	if (!t->isHosting())
		t->stopHostingAlready(peer);

	// we don't report teams, so this shouldn't get called
	qr2_buffer_add(buffer, "");
}

static void QRKeyListCallback
(
	PEER peer,
	qr2_key_type type,
	qr2_keybuffer_t keyBuffer,
	void * param
)
{
	DEBUG_LOG(("QR_KEY_LIST | %s\n", KeyTypeToString(type)));

	/*
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("QRKeyListCallback: bailing because of no thread info\n"));
		return;
	}
	if (!t->isHosting())
		t->stopHostingAlready(peer);
		*/

	// register the keys we use
	switch(type)
	{
	case key_server:
		qr2_keybuffer_add(keyBuffer, HOSTNAME_KEY);
		qr2_keybuffer_add(keyBuffer, GAMEVER_KEY);
		//qr2_keybuffer_add(keyBuffer, GAMENAME_KEY);
		qr2_keybuffer_add(keyBuffer, MAPNAME_KEY);
		// BFME registers two more of the reserved keys than Zero Hour does, and
		// in this order: 0x0C then 0x0B, TEAMPLAY before GAMEMODE.
		qr2_keybuffer_add(keyBuffer, TEAMPLAY_KEY);
		qr2_keybuffer_add(keyBuffer, GAMEMODE_KEY);
		qr2_keybuffer_add(keyBuffer, EXECRC_KEY);
		qr2_keybuffer_add(keyBuffer, INICRC_KEY);
		qr2_keybuffer_add(keyBuffer, PW_KEY);
		qr2_keybuffer_add(keyBuffer, OBS_KEY);
    qr2_keybuffer_add(keyBuffer, USE_STATS_KEY);
		qr2_keybuffer_add(keyBuffer, LADIP_KEY);
		qr2_keybuffer_add(keyBuffer, LADPORT_KEY);
		qr2_keybuffer_add(keyBuffer, PINGSTR_KEY);
		qr2_keybuffer_add(keyBuffer, NUMPLAYER_KEY);
		qr2_keybuffer_add(keyBuffer, MAXPLAYER_KEY);
		qr2_keybuffer_add(keyBuffer, NUMOBS_KEY);
		break;
	case key_player:
		qr2_keybuffer_add(keyBuffer, NAME__KEY);
		qr2_keybuffer_add(keyBuffer, WINS__KEY);
		qr2_keybuffer_add(keyBuffer, LOSSES__KEY);
		qr2_keybuffer_add(keyBuffer, PID__KEY);
		qr2_keybuffer_add(keyBuffer, FACTION__KEY);
		qr2_keybuffer_add(keyBuffer, COLOR__KEY);
		break;
	case key_team:
		// no custom team keys
		break;
	}
}

static int QRCountCallback
(
	PEER peer,
	qr2_key_type type,
	void * param
)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("QRCountCallback: bailing because of no thread info\n"));
		return 0;
	}
	if (!t->isHosting())
		t->stopHostingAlready(peer);

	if(type == key_player)
	{
		DEBUG_LOG(("QR_COUNT | %s = %d\n", KeyTypeToString(type), t->getNumPlayers() + t->getNumObservers()));
		return t->getNumPlayers() + t->getNumObservers();
	}
	else if(type == key_team)
	{
		DEBUG_LOG(("QR_COUNT | %s = %d\n", KeyTypeToString(type), 0));
		return 0;
	}

	DEBUG_LOG(("QR_COUNT | %s = %d\n", KeyTypeToString(type), 0));
	return 0;
}

// Target call at 0x38DE7B enters this body at 0x38D526. The internal
// receiver method at 0x38BDEE has no established name or class identity.
class Rva0038BDEEReceiver { public: void invoke(PEER peer); void rva0038BD70(PEER peer); };
void PeerThreadClass::stopHostingAlready(PEER peer)
{
	isThreadHosting = 0; // debugging
	s_lastStateChangedHeartbeat = 0;
	s_wantStateChangedHeartbeat = FALSE;
	reinterpret_cast<Rva0038BDEEReceiver *>(this)->invoke(peer);
	if (qr2Sock != INVALID_SOCKET)
	{
		closesocket(qr2Sock);
		qr2Sock = INVALID_SOCKET;
	}
}

static void QRAddErrorCallback
(
	PEER peer,
	qr2_error_t error,
	char * errorString,
	void * param
)
{
	DEBUG_LOG(("QR_ADD_ERROR | %s | %s\n", ErrorTypeToString(error), errorString));
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_FAILEDTOHOST;
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

static void QRNatNegotiateCallback
(
	PEER peer,
	int cookie,
	void * param
)
{
	DEBUG_LOG(("QR_NAT_NEGOTIATE | 0x%08X\n", cookie));
}

static void KickedCallback
(
	PEER peer,
	RoomType roomType,
	const char * nick,
	const char * reason,
	void * param
)
{
	DEBUG_LOG(("Kicked from %d by %s: \"%s\"\n", roomType, nick, reason));
}

static void NewPlayerListCallback
(
	PEER peer,
	RoomType roomType,
	void * param
)
{
	DEBUG_LOG(("NewPlayerListCallback\n"));
}

static void AuthenticateCDKeyCallback
(
	PEER peer,
	int result,
	const char * message,
	void * param
)
{
	DEBUG_LOG(("CD Key Result: %s (%d) %X\n", message, result, param));
#ifdef SERVER_DEBUGGING
	CheckServers(peer);
#endif // SERVER_DEBUGGING
	SerialAuthResult *val = (SerialAuthResult *)param;
	if (val)
	{
		if (result >= 1)
		{
			*val = SERIAL_OK;
		}
		else
		{
			*val = SERIAL_AUTHFAILED;
		}
	}
#ifdef SERVER_DEBUGGING
	CheckServers(peer);
#endif // SERVER_DEBUGGING
}

static SerialAuthResult doCDKeyAuthentication( PEER peer )
{
	SerialAuthResult retval = SERIAL_NONEXISTENT;
	if (!peer)
		return retval;

	AsciiString s = "";
	if (GetStringFromRegistry("\\ergc", "", s) && s.isNotEmpty())
	{
#ifdef SERVER_DEBUGGING
		DEBUG_LOG(("Before peerAuthenticateCDKey()\n"));
		CheckServers(peer);
#endif // SERVER_DEBUGGING
		peerAuthenticateCDKey(peer, s.str(), AuthenticateCDKeyCallback, &retval, PEERTrue);
#ifdef SERVER_DEBUGGING
		DEBUG_LOG(("After peerAuthenticateCDKey()\n"));
		CheckServers(peer);
#endif // SERVER_DEBUGGING
	}
	
	if (retval == SERIAL_OK)
	{
		PSRequest req;
		req.requestType = PSRequest::PSREQUEST_READCDKEYSTATS;
		req.cdkey = s.str();
		TheGameSpyPSMessageQueue->addRequest(req);
	}

	return retval;
}

#define INBUF_LEN 256
void checkQR2Queries( PEER peer, SOCKET sock )
{
	static char indata[INBUF_LEN];
	struct sockaddr_in saddr;
	int saddrlen = sizeof(struct sockaddr_in);
	fd_set set;
	struct timeval timeout = {0,0};
	int error;

	FD_ZERO ( &set );
	FD_SET ( sock, &set );

	while (1)
	{
		error = select(FD_SETSIZE, &set, NULL, NULL, &timeout);
		if (SOCKET_ERROR == error || 0 == error)
			return;
		//else we have data
		error = recvfrom(sock, indata, INBUF_LEN - 1, 0, (struct sockaddr *)&saddr, &saddrlen);
		if (error != SOCKET_ERROR)
		{
			indata[error] = '\0';
			peerParseQuery( peer, indata, error, (sockaddr *)&saddr );
		}
	}
}

static UnsignedInt localIP = 0;

#undef payload

static void qmProfileIDCallback( PEER peer, PEERBool success, const char *nick, int profileID, void *param )
{
	Int *i = (Int *)param;
	if (!i || !success || !nick)
		return;

	*i = profileID;
}

static Int matchbotProfileID = 0;
void quickmatchEnumPlayersCallback( PEER peer, PEERBool success, RoomType roomType, int index, const char * nick, int flags, void * param )
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t || !success || nick == NULL || nick[0] == '\0')
	{
		t->sawEndOfEnumPlayers();
		return;
	}

	Int id = 0;
	peerGetPlayerProfileIDA(peer, nick, reinterpret_cast<void *>(qmProfileIDCallback), &id, PEERTrue);
	DEBUG_LOG(("Saw player %s with id %d (looking for %d)\n", nick, id, matchbotProfileID));
	if (id == matchbotProfileID)
	{
		t->sawMatchbot(nick);
	}

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERJOIN;
	resp.nick = nick;
	resp.player.roomType = roomType;
	resp.player.IP = 0;

	TheGameSpyPeerMessageQueue->addResponse(resp);
}

// Six-array retail handler lives in PeerThreadQMMatch.cpp.

// PeerThreadClass::doQuickMatch, retail 0x0038E684 (1875 bytes). Zero Hour /
// Open-BFME-1 donor body on BFME 2's thread layout, which the class above (Zero
// Hour's) does not have; the view below carries the offsets this body reads,
// like BfmePeerQMState/BfmePeerEnumState. Kept in this unit: matchbotProfileID
// is the file-static above, and only a store to it schedules retail's prologue.
// Target facts: request types LOGOUT 1, LEAVEGROUPROOM 5, UTMPLAYER 13, WIDEN 17,
// STOP 18; the EXE field is ComputeCRC of the 16-byte hash at +0x400.
struct BfmeQuickMatchPreferences
{
	Int minPointPercentage;
	Int maxPointPercentage;
	Int points;
	Int widenTime;
	Int ladderID;
	UnsignedInt ladderPassCRC;
	Int maxPing;
	Int maxDiscons;
	Int discons;
	char pings[20];
	Int numPlayers;
	Int botID;
	Int roomID;
	Int side;
	Int color;
	Int NAT;
	unsigned char exeHash[16];
	UnsignedInt iniCRC;
	UnsignedInt cmdCRC;
};

struct BfmeQuickMatchThread
{
	unsigned char unknown000[0x88];
	Int groupRoomID;
	unsigned char unknown08C[0xB0 - 0x8C];
	Bool isHosting;
	unsigned char unknown0B1[0x290 - 0xB1];
	Int localRoomID;
	QMStatus qmStatus;
	unsigned char unknown298[0x39C - 0x298];
	std::vector<bool> qmMaps;
	BfmeQuickMatchPreferences QM;
	unsigned char unknown418[0x484 - 0x418];
	Bool roomJoined;
	unsigned char unknown485[3];
	Int qmGroupRoom;
	Bool sawEndOfEnumPlayers;
	Bool sawMatchbot;
	unsigned char unknown48E[2];
	std::string matchbotName;
	unsigned char unknown49C[0x4AC - 0x49C];
	MutexClass *lock;
};

UnsignedInt ComputeCRC(const unsigned char *buffer, UnsignedInt length, UnsignedInt crc);

void PeerThreadClass::doQuickMatch( PEER peer )
{
	BfmeQuickMatchThread *self = reinterpret_cast<BfmeQuickMatchThread *>(this);
	matchbotProfileID = self->QM.botID;
	self->qmGroupRoom = self->QM.roomID;
	self->qmStatus = QM_JOININGQMCHANNEL;
	Bool done = false;
	self->sawMatchbot = false;
	updateBuddyStatus( BUDDY_MATCHING );
	while (!done)
	{
		MutexClass::LockClass lock(*self->lock, 1);
		if (!lock.Failed()) break;
		if (!peerIsConnected( peer ))
		{
			done = true;
		}
		else
		{
			// update the network
			peerThink( peer );

			// end our timeslice
			Switch_Thread();

			PeerRequest incomingRequest;
			if (TheGameSpyPeerMessageQueue->getRequest(incomingRequest))
			{
				switch (incomingRequest.peerRequestType)
				{
				case PeerRequest::PEERREQUEST_WIDENQUICKMATCHSEARCH:
					{
						if (self->qmStatus != QM_IDLE && self->qmStatus != QM_STOPPED && self->sawMatchbot)
						{
							peerMessagePlayer( peer, self->matchbotName.c_str(), "\\WIDEN", NormalMessage );
						}
					}
					break;
				case PeerRequest::PEERREQUEST_STOPQUICKMATCH:
					{
						self->qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_LOGOUT:
					{
						self->qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_LEAVEGROUPROOM:
					{
						self->qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				case PeerRequest::PEERREQUEST_UTMPLAYER:
					{
						peerUTMPlayer( peer, incomingRequest.nick.c_str(), incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
					}
					break;
				}
			}

			if (!done)
			{
				// do the next bit of QM
				switch (self->qmStatus)
				{
				case QM_JOININGQMCHANNEL:
					{
						PeerResponse resp;
						resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
						resp.qmStatus.status = QM_JOININGQMCHANNEL;
						TheGameSpyPeerMessageQueue->addResponse(resp);

						self->groupRoomID = self->qmGroupRoom;
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL ); self->isHosting = false;
						self->localRoomID = self->groupRoomID;
						self->roomJoined = false;
						peerJoinGroupRoom( peer, self->localRoomID, joinRoomCallback, (void *)this, PEERTrue );
						if (self->roomJoined)
						{
							resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
							resp.qmStatus.status = QM_LOOKINGFORBOT;
							TheGameSpyPeerMessageQueue->addResponse(resp);

							self->qmStatus = QM_LOOKINGFORBOT;
							self->sawMatchbot = false;
							self->sawEndOfEnumPlayers = false;
							peerEnumPlayers( peer, GroupRoom, quickmatchEnumPlayersCallback, this );
						}
						else
						{
							resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
							resp.qmStatus.status = QM_COULDNOTFINDBOT;
							TheGameSpyPeerMessageQueue->addResponse(resp);
							done = true;
							self->qmStatus = QM_STOPPED;
						}
					}
					break;
				case QM_LOOKINGFORBOT:
					{
						if (self->sawEndOfEnumPlayers)
						{
							if (self->sawMatchbot)
							{
								char buf[64];
								buf[63] = '\0';
								std::string msg = "\\CINFO";
								_snprintf(buf, 63, "\\Widen\\%d", self->QM.widenTime);
								msg.append(buf);
								_snprintf(buf, 63, "\\LadID\\%d", self->QM.ladderID);
								msg.append(buf);
								_snprintf(buf, 63, "\\LadPass\\%d", self->QM.ladderPassCRC);
								msg.append(buf);
								_snprintf(buf, 63, "\\PointsMin\\%d", self->QM.minPointPercentage);
								msg.append(buf);
								_snprintf(buf, 63, "\\PointsMax\\%d", self->QM.maxPointPercentage);
								msg.append(buf);
								_snprintf(buf, 63, "\\Points\\%d", self->QM.points);
								msg.append(buf);
								_snprintf(buf, 63, "\\Discons\\%d", self->QM.discons);
								msg.append(buf);
								_snprintf(buf, 63, "\\DisconMax\\%d", self->QM.maxDiscons);
								msg.append(buf);
								_snprintf(buf, 63, "\\NumPlayers\\%d", self->QM.numPlayers);
								msg.append(buf);
								_snprintf(buf, 63, "\\PingMax\\%d", self->QM.maxPing);
								msg.append(buf);
								_snprintf(buf, 63, "\\Pings\\%s", self->QM.pings);
								msg.append(buf);
								_snprintf(buf, 63, "\\IP\\%d", htonl(peerGetLocalIP(peer)));// not of localIP, as we need EXTERNAL address for proper NAT negotiation! (retail imports htonl here)
								msg.append(buf);
								_snprintf(buf, 63, "\\Side\\%d", self->QM.side);
								msg.append(buf);
								_snprintf(buf, 63, "\\Color\\%d", self->QM.color);
								msg.append(buf);
								_snprintf(buf, 63, "\\NAT\\%d", self->QM.NAT);
								msg.append(buf);
								_snprintf(buf, 63, "\\EXE\\%d", ComputeCRC(self->QM.exeHash, 16, 0));
								msg.append(buf);
								_snprintf(buf, 63, "\\INI\\%d", self->QM.iniCRC);
								msg.append(buf);
								_snprintf(buf, 63, "\\CMD\\%d", self->QM.cmdCRC);
								msg.append(buf);
								buf[0] = 0;
								msg.append("\\Maps\\");
								for (Int i=0; i<self->qmMaps.size(); ++i)
								{
									if (self->qmMaps[i])
										msg.append("1");
									else
										msg.append("0");
								}
								peerMessagePlayer( peer, self->matchbotName.c_str(), msg.c_str(), NormalMessage );
								self->qmStatus = QM_WORKING;
								PeerResponse resp;
								resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
								resp.qmStatus.status = QM_SENTINFO;
								TheGameSpyPeerMessageQueue->addResponse(resp);
							}
							else
							{
								// no QM bot.  Bail.
								PeerResponse resp;
								resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
								resp.qmStatus.status = QM_COULDNOTFINDBOT;
								TheGameSpyPeerMessageQueue->addResponse(resp);

								self->qmStatus = QM_STOPPED;
								peerLeaveRoom(peer, GroupRoom, "");
								done = true;
							}
						}
					}
					break;
				case QM_MATCHED:
					{
						// leave QM channel, and clean up.  Our work here is done.
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL ); self->isHosting = false;

						self->qmStatus = QM_STOPPED;
						peerLeaveRoom(peer, GroupRoom, "");
						done = true;
					}
					break;
				}
			}
		}
	}
	updateBuddyStatus( BUDDY_ONLINE );
}

// PeerThreadClass::Thread_Function, retail 0x0038EDD7 (4723 bytes). The Zero
// Hour body as BFME 2 ships it: the GameSpy availability check and title
// "lotrbme2r" up front, BFME's own query keys, a server browser beside the
// peer object, a thread lock per pass instead of the running flag, and the
// BFME request handlers (see PeerThreadRetail.h for the request numbering).
// BFME 2 offsets are read through the views below; the class above keeps
// Zero Hour's layout.
struct BfmeStagingCreationCRCs
{
	UnsignedInt value[4];
};

struct BfmeRequestPayload
{
	union
	{
		Int id;
		Bool flag;
		struct
		{
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int slotValue60[MAX_SLOTS];
			Int slotValue80[MAX_SLOTS];
			Int slotValueA0[MAX_SLOTS];
			Int numPlayers;
			Int maxPlayers;
			Int numObservers;
			Int valueCC;
			Int valueD0;
		} gameOptions;
		struct
		{
			BfmeStagingCreationCRCs crcs;
			UnsignedInt value10;
			UnsignedInt value14;
			unsigned char hash18[16];
			UnsignedInt value28;
			Bool allowObservers;
			unsigned char pad2D;
			UnsignedShort ladPort;
			unsigned char pad30[4];
			Bool restrictGameList;
			unsigned char pad35[3];
			Int maxPlayers;
		} creation;
		struct
		{
			Int value0;
			Int value4;
		} statsPair;
	};
};

struct BfmeStagingResponseView
{
	unsigned char head[0x10C];
	Int id;
	Int action;
	Bool isStaging;
	unsigned char pad115[0x214 - 0x115];
	Int percentComplete;
};

class GameModePreferences
{
public:
	virtual ~GameModePreferences();
	AsciiString rva0044D986();
private:
	unsigned char m_unrecovered[0x18];
};

// The mode-keyed preferences object built here is the matched derived class at
// 0x0054F508 (Rva0044D56ADerived.cpp); its map name comes from the base.
class Rva0054F508 : public GameModePreferences
{
public:
	Rva0054F508(Int mode);
	virtual ~Rva0054F508();
};

class Rva00388EAE
{
public:
	void rva00389129();
};

class DualIndexedDispatchThunk
{
public:
	void dispatch(PEER peer);
};

struct BfmePeerThreadView
{
	unsigned char unknown000[0x50];
	Bool isConnecting;
	Bool isConnected;
	unsigned char unknown052[2];
	std::string loginName;
	std::string originalName;
	std::string password;
	std::string email;
	Int profileID;
	Int groupRoomID;
	Bool sawCompleteGameList;
	unsigned char unknown08D[3];
	Int startGameValue;
	Bool pushStatsEachPass;
	unsigned char unknown095[0xB0 - 0x95];
	Bool isHosting;
	Bool hasPassword;
	unsigned char unknown0B2[2];
	std::string mapName;
	Int valueC0;
	unsigned char unknown0C4[0xD0 - 0xC4];
	std::string playerNames[MAX_SLOTS];
	BfmeStagingCreationCRCs crcs;
	UnsignedInt value140;
	UnsignedInt value144;
	unsigned char hash148[16];
	UnsignedInt value158;
	Bool allowObservers;
	unsigned char unknown15D[3];
	std::string pingStr;
	std::string ladderIP;
	UnsignedShort ladderPort;
	unsigned char unknown17A[2];
	Int playerWins[MAX_SLOTS];
	Int playerLosses[MAX_SLOTS];
	Int playerProfileID[MAX_SLOTS];
	Int playerValue1DC[MAX_SLOTS];
	Int playerValue1FC[MAX_SLOTS];
	Int playerValue21C[MAX_SLOTS];
	Int numPlayers;
	Int maxPlayers;
	Int numObservers;
	unsigned int value248[10];
	Int value270;
	unsigned char unknown274[4];
	Rva00388EAE stagingServers;
	unsigned char unknown279[0x284 - 0x279];
	std::wstring localStagingServerName;
	Int localRoomID;
	QMStatus qmStatus;
	PeerRequest qmInfo;
	Bool roomJoined;
	unsigned char unknown485[3];
	Int qmGroupRoom;
	unsigned char unknown48C[0x49C - 0x48C];
	Bool suspendStateChanged;
	unsigned char unknown49D[3];
	Int value4A0;
	Int value4A4;
	Bool listGroupRooms;
	unsigned char unknown4A9[3];
	MutexClass *lock;
};

// The global after TheGameSpyInfo (0x00E02324); its +0x5C word gates the
// per-pass stats push.
struct BfmeGameSpyGameView
{
	unsigned char unknown00[0x5C];
	Int localPlayerProfile;
};

// TheGameSpyInfo (0x00E02320) maps a nick through its +0x58 slot.
class BfmeGameSpyPlayerLookup
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual const AsciiString *lookupPlayerName(const char *nick);
};

// BFME 2's EnumeratedIP keeps the address at +4 and the link at +8.
struct BfmeEnumeratedIPView
{
	void *unknown00;
	UnsignedInt m_IP;
	BfmeEnumeratedIPView *m_next;
	UnsignedInt getIP( void ) { return m_IP; }
	BfmeEnumeratedIPView *getNext( void ) { return m_next; }
};

struct BfmeSerialAuthQueueView
{
	unsigned char unknown00[0x68];
	SerialAuthResult serialAuthResult;
};

// BFME 2's SDK join results, as this body compares and stores them: success
// 0, already-in-room 5, failed 10 (the sweep header numbers them differently).
static const Int BfmePEERJoinSuccess = 0;
static const Int BfmePEERJoinFailed = 10;
static const Int BfmePEERAlreadyInRoom = 5;

typedef enum { GSIACWaiting, GSIACAvailable, GSIACUnavailable, GSIACTemporarilyUnavailable } GSIACResult;
extern "C" void GSIStartAvailableCheckA(const char *gamename);
extern "C" GSIACResult GSIAvailableCheckThink(void);
typedef void *ServerBrowser;
extern "C" ServerBrowser ServerBrowserNewA(const char *queryForGamename, const char *queryFromGamename, const char *queryFromKey, int queryFromVersion, int maxConcUpdates, int queryVersion, void *callback, void *instance);
extern "C" void ServerBrowserClear(ServerBrowser sb);
extern "C" int ServerBrowserUpdateA(ServerBrowser sb, int async, int disconnectOnComplete, const unsigned char *fields, int numFields, const char *serverFilter);
extern "C" void peerSetQuietMode(PEER peer, PEERBool quiet);
extern "C" const char *peerGetRoomNameA(PEER peer, RoomType roomType);
static void serverBrowserCallback(void) {}
static void listGroupRoomsCallback(PEER peer, PEERBool success,
							int groupID, SBServer server,
							const char * name, int numWaiting,
							int maxWaiting, int numGames,
							int numPlaying, void * param);

void PeerThreadClass::Thread_Function()
{
	try {
	BfmePeerThreadView *self = reinterpret_cast<BfmePeerThreadView *>(this);
	PEER peer;

	char gameName[12];
	char secretKey[7];
	gameName[0]='l';gameName[1]='o';gameName[2]='t';gameName[3]='r';
	gameName[4]='b';gameName[5]='m';gameName[6]='e';gameName[7]='2';
	gameName[8]='r';gameName[9]='\0';
	secretKey[0]='g';secretKey[1]='3';secretKey[2]='F';secretKey[3]='d';
	secretKey[4]='9';secretKey[5]='z';secretKey[6]='\0';

	GSIStartAvailableCheckA(gameName);
	GSIACResult available;
	while ((available = GSIAvailableCheckThink()) == GSIACWaiting)
		Sleep(10);
	if (available != GSIACAvailable)
		return;

	// Setup the callbacks.
	///////////////////////
	PEERCallbacks callbacks;
	memset(&callbacks, 0, sizeof(PEERCallbacks));
	callbacks.disconnected = disconnectedCallback;
	callbacks.roomMessage = roomMessageCallback;
	callbacks.playerMessage = playerMessageCallback;
	callbacks.gameStarted = gameStartedCallback;
	callbacks.playerJoined = playerJoinedCallback;
	callbacks.playerLeft = playerLeftCallback;
	callbacks.playerChangedNick = playerChangedNickCallback;
	callbacks.playerFlagsChanged = playerFlagsChangedCallback;
	callbacks.playerInfo = playerInfoCallback;
	callbacks.roomUTM = roomUTMCallback;
	callbacks.playerUTM = playerUTMCallback;
	callbacks.globalKeyChanged = globalKeyChangedCallback;
	callbacks.roomKeyChanged = roomKeyChangedCallback;

	callbacks.qrServerKey = QRServerKeyCallback;
	callbacks.qrPlayerKey = QRPlayerKeyCallback;
	callbacks.qrTeamKey = QRTeamKeyCallback;
	callbacks.qrKeyList = QRKeyListCallback;
	callbacks.qrCount = QRCountCallback;
	callbacks.qrAddError = QRAddErrorCallback;
	callbacks.qrNatNegotiateCallback = QRNatNegotiateCallback;

	callbacks.kicked = KickedCallback;
	callbacks.newPlayerList = NewPlayerListCallback;

	callbacks.param = this;

	self->qmGroupRoom = 0;

	peer = peerInitialize( &callbacks );
	self->isConnected = self->isConnecting = false;

	qr2_register_key(0x33, "exeCRC");
	qr2_register_key(0x34, "iniCRC");
	qr2_register_key(0x35, "cmdCRC");
	qr2_register_key(0x36, "pw");
	qr2_register_key(0x37, "obs");
	qr2_register_key(0x38, "ladIP");
	qr2_register_key(0x39, "ladPort");
	qr2_register_key(0x3a, "pings");
	qr2_register_key(0x3d, "numObservers");
	qr2_register_key(0x3b, "numRealPlayers");
	qr2_register_key(0x3c, "maxRealPlayers");
	qr2_register_key(0x3e, "name_");
	qr2_register_key(0x42, "wins_");
	qr2_register_key(0x43, "losses_");
	qr2_register_key(0x3f, "faction_");
	qr2_register_key(0x40, "color_");
	qr2_register_key(0x41, "handicap_");
	qr2_register_key(0x44, "rules");
	qr2_register_key(0x45, "gCRC");
	qr2_register_key(0x46, "scen");

	const Int NumKeys = 20;
	unsigned char allKeysArray[NumKeys] = {
		5, 6, 0xb, 3, 2, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x38, 0x39, 0x3a, 0x3d, 0x3b, 0x3c, 1, 0x44, 0x45, 0x46
	};

	const char * key = "username";
	peerSetRoomWatchKeys(peer, StagingRoom, 1, &key, PEERTrue);
	peerSetRoomWatchKeys(peer, GroupRoom, 1, &key, PEERTrue);

	self->localRoomID = 0;
	self->localStagingServerName = L"";

	self->qmStatus = QM_IDLE;

	// Setup which rooms to do pings and cross-pings in.
	////////////////////////////////////////////////////
	PEERBool pingRooms[NumRooms];
	PEERBool crossPingRooms[NumRooms];
	pingRooms[TitleRoom] = PEERFalse;
	pingRooms[GroupRoom] = PEERFalse;
	pingRooms[StagingRoom] = PEERFalse;
	crossPingRooms[TitleRoom] = PEERFalse;
	crossPingRooms[GroupRoom] = PEERFalse;
	crossPingRooms[StagingRoom] = PEERFalse;

	// Set the title.
	/////////////////
	if(!peerSetTitle( peer , gameName, secretKey, gameName, secretKey, GetRegistryVersion(), 30, PEERTrue, pingRooms, crossPingRooms))
	{
		peerShutdown( peer );
		return;
	}

	ServerBrowser serverBrowser = ServerBrowserNewA(gameName, gameName, secretKey, 0, 30, 1, serverBrowserCallback, this);

	OptionPreferences pref;
	UnsignedInt preferredIP = INADDR_ANY;
	UnsignedInt selectedIP = pref.getOnlineIPAddress();
	IPEnumeration IPs;
	BfmeEnumeratedIPView *IPlist = reinterpret_cast<BfmeEnumeratedIPView *>(IPs.getAddresses());
	while (IPlist)
	{
		if (selectedIP == IPlist->getIP())
		{
			preferredIP = IPlist->getIP();
			break;
		}
		IPlist = IPlist->getNext();
	}
	chatSetLocalIP(preferredIP);

	UnsignedInt preferredQRPort = 0;
	AsciiString selectedQRPort = pref["GameSpyQRPort"];
	if (!selectedQRPort.isEmpty())
	{
		preferredQRPort = atoi(selectedQRPort.str());
	}

	PeerRequest incomingRequest;
#define payload (*reinterpret_cast<BfmeRequestPayload *>(reinterpret_cast<char *>(&incomingRequest) + 0x118))
	for (;;)
	{
		MutexClass::LockClass lock(*self->lock, 1);
		if (!lock.Failed())
			break;

		if (self->pushStatsEachPass && reinterpret_cast<BfmeGameSpyGameView *>(TheGameSpyGame)->localPlayerProfile != -1)
			pushStatsToRoom(peer);

		// deal with requests
		if (TheGameSpyPeerMessageQueue->getRequest(incomingRequest))
		{
			switch (incomingRequest.peerRequestType)
			{
			case PeerRequest::PEERREQUEST_LOGIN:
				{
				self->isConnecting = true;
				self->originalName = incomingRequest.nick;
				self->loginName = incomingRequest.nick;
				self->profileID = payload.id;
				self->password = incomingRequest.password;
				self->email = incomingRequest.email;
				peerConnect( peer, incomingRequest.nick.c_str(), payload.id, nickErrorCallbackWrapper, connectCallbackWrapper, this, PEERTrue );
				if (self->isConnected)
				{
					SerialAuthResult ret = doCDKeyAuthentication( peer );
					if (ret != SERIAL_OK)
					{
						self->isConnecting = self->isConnected = false;
						reinterpret_cast<BfmeSerialAuthQueueView *>(TheGameSpyPeerMessageQueue)->serialAuthResult = ret;
						peerDisconnect( peer );
					}
				}
				self->isConnecting = false;
				}
				break;

			case PeerRequest::PEERREQUEST_LOGOUT:
				self->isConnecting = self->isConnected = false;
				peerDisconnect( peer );
				break;

			case PeerRequest::PEERREQUEST_JOINGROUPROOM:
				self->groupRoomID = payload.id;
				isThreadHosting = 0; // debugging
				s_lastStateChangedHeartbeat = 0;
				s_wantStateChangedHeartbeat = FALSE;
				reinterpret_cast<Rva0038BDEEReceiver *>(this)->invoke( peer );
				peerSetQuietMode( peer, PEERFalse );
				peerLeaveRoom( peer, GroupRoom, NULL );
				peerLeaveRoom( peer, StagingRoom, NULL );
				if (qr2Sock != INVALID_SOCKET)
				{
					closesocket(qr2Sock);
					qr2Sock = INVALID_SOCKET;
				}
				self->isHosting = false;
				self->localRoomID = self->groupRoomID;
				peerJoinGroupRoom( peer, payload.id, joinRoomCallback, (void *)this, PEERTrue );
				break;

			case PeerRequest::PEERREQUEST_LEAVEGROUPROOM:
				if (self->groupRoomID == payload.id)
				{
					self->groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					peerLeaveRoom( peer, GroupRoom, NULL );
					peerLeaveRoom( peer, StagingRoom, NULL ); self->isHosting = false;
				}
				break;

			case PeerRequest::PEERREQUEST_LEAVEGROUPROOMONLY:
				if (self->groupRoomID == payload.id)
				{
					self->groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					peerLeaveRoom( peer, GroupRoom, NULL );
				}
				break;

			case PeerRequest::PEERREQUEST_JOINSTAGINGROOM:
				{
					self->groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					peerLeaveRoom( peer, GroupRoom, NULL );
					peerLeaveRoom( peer, StagingRoom, NULL ); self->isHosting = false;
					SBServer server = findServerByID(payload.id);
					self->localStagingServerName = incomingRequest.text;
					self->localRoomID = payload.id;
					if (server)
					{
						peerJoinStagingRoom( peer, server, incomingRequest.password.c_str(), joinRoomCallback, (void *)this, PEERTrue );
					}
					else
					{
						PeerResponse resp;
						resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINSTAGINGROOM;
						resp.joinStagingRoom.id = payload.id;
						resp.joinStagingRoom.ok = FALSE;
						resp.joinStagingRoom.result = BfmePEERJoinFailed;
						TheGameSpyPeerMessageQueue->addResponse(resp);
					}
				}
				break;

			case PeerRequest::PEERREQUEST_LEAVESTAGINGROOM:
				self->groupRoomID = 0;
				updateBuddyStatus( BUDDY_ONLINE );
				peerLeaveRoom( peer, GroupRoom, NULL );
				peerLeaveRoom( peer, StagingRoom, NULL );
				isThreadHosting = 0; // debugging
				s_lastStateChangedHeartbeat = 0;
				s_wantStateChangedHeartbeat = FALSE;
				if (self->isHosting)
				{
					self->numPlayers = 1;
					self->numObservers = 0;
					self->maxPlayers = MAX_SLOTS;
					reinterpret_cast<Rva0038BDEEReceiver *>(this)->invoke( peer );
					if (qr2Sock != INVALID_SOCKET)
					{
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
					}
					self->isHosting = false;
				}
				break;

			case PeerRequest::PEERREQUEST_MESSAGEPLAYER:
				{
					std::string s = WideCharStringToMultiByte(incomingRequest.text.c_str());
					peerMessagePlayer( peer, incomingRequest.nick.c_str(), s.c_str(), (payload.flag)?ActionMessage:NormalMessage );
				}
				break;

			case PeerRequest::PEERREQUEST_MESSAGEROOM:
				{
					std::string s = WideCharStringToMultiByte(incomingRequest.text.c_str());
					peerMessageRoom( peer, (self->groupRoomID)?GroupRoom:StagingRoom, s.c_str(), (payload.flag)?ActionMessage:NormalMessage );
				}
				break;

			case PeerRequest::PEERREQUEST_MESSAGEROOMNOTICE:
				{
					std::string s = WideCharStringToMultiByte(incomingRequest.text.c_str());
					peerMessageRoom( peer, (self->groupRoomID)?GroupRoom:StagingRoom, s.c_str(), (MessageType)2 );
				}
				break;

			case PeerRequest::PEERREQUEST_PUSHSTATS:
				pushStatsToRoom(peer);
				break;

			case PeerRequest::PEERREQUEST_PUSHSTATSVALUES:
				_snprintf(s_valueBuffers[0], 20, "%d", payload.statsPair.value0);
				_snprintf(s_valueBuffers[1], 20, "%d", payload.statsPair.value4);
				reinterpret_cast<DualIndexedDispatchThunk *>(this)->dispatch( peer );
				break;

			case PeerRequest::PEERREQUEST_SETGAMEOPTIONS:
				{
					self->mapName = incomingRequest.gameOptsMapName;
					self->valueC0 = payload.gameOptions.valueCC;
					self->numPlayers = payload.gameOptions.numPlayers;
					self->numObservers = payload.gameOptions.numObservers;
					self->maxPlayers = payload.gameOptions.maxPlayers;
					memcpy(self->value248, incomingRequest.unknown_d0, sizeof(self->value248));
					self->value270 = payload.gameOptions.valueD0;
					for (Int i=0; i<MAX_SLOTS; ++i)
					{
						self->playerNames[i] = incomingRequest.gameOptsPlayerNames[i];
						self->playerWins[i] = payload.gameOptions.wins[i];
						self->playerLosses[i] = payload.gameOptions.losses[i];
						self->playerProfileID[i] = payload.gameOptions.profileID[i];
						self->playerValue21C[i] = payload.gameOptions.slotValue60[i];
						self->playerValue1DC[i] = payload.gameOptions.slotValue80[i];
						self->playerValue1FC[i] = payload.gameOptions.slotValueA0[i];
					}

					s_wantStateChangedHeartbeat = TRUE;

					peerUTMRoom( peer, StagingRoom, "SL/", incomingRequest.options.c_str(), PEERFalse ); // send the full string to people in the room
				}
				break;

			case PeerRequest::PEERREQUEST_UTMSTAGINGPN:
				peerUTMRoom( peer, StagingRoom, "PN/", incomingRequest.options.c_str(), PEERFalse );
				break;

			case PeerRequest::PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO:
				{
					SBServer server = findServerByID( payload.id );
					if (server)
					{
						peerUpdateGame( peer, server, PEERTrue );
					}
				}
				break;

			case PeerRequest::PEERREQUEST_CREATESTAGINGROOM:
				{
					Int oldGroupID = self->groupRoomID;
					self->groupRoomID = 0;
					updateBuddyStatus( BUDDY_ONLINE );
					if (!payload.creation.restrictGameList)
					{
						peerLeaveRoom( peer, GroupRoom, NULL );
						peerLeaveRoom( peer, StagingRoom, NULL );
					}
					self->isHosting = TRUE;

					Int res = BfmePEERJoinFailed;
					if (qr2Sock == INVALID_SOCKET)
					{
						// allocate a port
						if (preferredQRPort < 1024)
						{
							preferredQRPort = 6500 + (htonl(localIP) & 0xff);
						}
					}
					else
					{
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
					}
					qr2Sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
					struct sockaddr_in saddr;
					saddr.sin_port=htons(preferredQRPort);
					saddr.sin_addr.s_addr=localIP;
					saddr.sin_family=AF_INET;
					if (bind(qr2Sock, (sockaddr *)&saddr, sizeof(saddr)) != 0)
					{
						closesocket(qr2Sock);
						qr2Sock = INVALID_SOCKET;
						preferredQRPort = 0;
					}
					std::string compositeGame = self->loginName;
					compositeGame.append(" ");
					compositeGame.append(WideCharStringToMultiByte(incomingRequest.text.c_str()));
					self->localStagingServerName = incomingRequest.text;
					self->playerNames[0] = self->loginName;
					for (Int i=0; i<MAX_SLOTS; ++i)
					{
						self->playerNames[i] = "";
						self->playerWins[i] = 0;
						self->playerLosses[i] = 0;
						self->playerProfileID[i] = 0;
						self->playerValue21C[i] = 0;
						self->playerValue1DC[i] = 0;
						self->playerValue1FC[i] = 0;
					}
					self->hasPassword = incomingRequest.password.length() != 0;
					self->playerNames[0] = self->loginName;
					self->crcs = payload.creation.crcs;
					self->value140 = payload.creation.value10;
					self->value144 = payload.creation.value14;
					memcpy(self->hash148, payload.creation.hash18, sizeof(self->hash148));
					self->value158 = payload.creation.value28;
					self->maxPlayers = payload.creation.maxPlayers;
					self->localStagingServerName = incomingRequest.text;
					self->ladderIP = incomingRequest.ladderIP;
					self->pingStr = incomingRequest.hostPingStr;
					self->ladderPort = payload.creation.ladPort;
					self->valueC0 = payload.gameOptions.valueCC;

					Rva0054F508 modePrefs(0);
					self->mapName = modePrefs.rva0044D986().str();

					peerCreateStagingRoomWithSocket(peer, compositeGame.c_str(), MAX_SLOTS, incomingRequest.password.c_str(), qr2Sock, preferredQRPort, createRoomCallback, (void *)&res, PEERTrue);

					PeerResponse resp;
					resp.peerResponseType = PeerResponse::PEERRESPONSE_CREATESTAGINGROOM;
					resp.createStagingRoom.result = res;
					if (res == BfmePEERJoinSuccess || res == BfmePEERAlreadyInRoom)
						resp.unknown_7c = peerGetRoomNameA( peer, StagingRoom );
					TheGameSpyPeerMessageQueue->addResponse(resp);

					if (res != BfmePEERJoinSuccess && res != BfmePEERAlreadyInRoom)
					{
						self->localRoomID = oldGroupID;
						if (payload.creation.restrictGameList)
						{
							peerLeaveRoom( peer, StagingRoom, NULL );
						}
						else
						{
							peerJoinGroupRoom( peer, oldGroupID, joinRoomCallback, (void *)this, PEERTrue );
						}
						self->isHosting = FALSE;
						self->localStagingServerName = L"";
						self->playerNames[0] = "";
					}
					else
					{
						if (payload.creation.restrictGameList)
						{
							peerLeaveRoom( peer, GroupRoom, NULL );
						}
						isThreadHosting = 1; // debugging
						s_lastStateChangedHeartbeat = timeGetTime(); // wait the full interval before updating state
						s_wantStateChangedHeartbeat = FALSE;
						self->isHosting = TRUE;
						self->allowObservers = payload.creation.allowObservers;
						self->mapName = "";
						pushStatsToRoom(peer);
						updateBuddyStatus( BUDDY_STAGING, 0, WideCharStringToMultiByte(self->localStagingServerName.c_str()) );
					}
				}
				break;

			case PeerRequest::PEERREQUEST_STARTGAMELIST:
				{
					self->sawCompleteGameList = FALSE;
					PeerResponse resp;
					BfmeStagingResponseView &staging = reinterpret_cast<BfmeStagingResponseView &>(resp);
					resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
					staging.action = PEER_CLEAR;
					staging.isStaging = TRUE;
					staging.percentComplete = 0;
					self->stagingServers.rva00389129();
					TheGameSpyPeerMessageQueue->addResponse(resp);
					AsciiString filter = "gamemode != 'closedplaying'";
					if (incomingRequest.unknown_f8.length() != 0)
					{
						filter.concat(" and hostname='");
						filter.concat(incomingRequest.unknown_f8.c_str());
						filter.concat("'");
					}
					peerStartListingGames( peer, allKeysArray, NumKeys, filter.str(), listingGamesCallback, this );
				}
				break;

			case PeerRequest::PEERREQUEST_STOPGAMELIST:
				{
					peerStopListingGames( peer );
				}
				break;

			case PeerRequest::PEERREQUEST_REFRESHGAMELIST:
				{
					self->sawCompleteGameList = FALSE;
					PeerResponse resp;
					BfmeStagingResponseView &staging = reinterpret_cast<BfmeStagingResponseView &>(resp);
					resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
					staging.action = PEER_CLEAR;
					staging.isStaging = TRUE;
					staging.percentComplete = 0;
					self->stagingServers.rva00389129();
					TheGameSpyPeerMessageQueue->addResponse(resp);
					ServerBrowserClear(serverBrowser);
					ServerBrowserUpdateA(serverBrowser, 0, 1, allKeysArray, NumKeys, NULL);
				}
				break;

			case PeerRequest::PEERREQUEST_STARTGAME:
				{
					self->startGameValue = payload.id;
					peerSetQuietMode( peer, PEERTrue );
					peerStopListingGames( peer );
					reinterpret_cast<Rva0038BDEEReceiver *>(this)->rva0038BD70( peer );
				}
				break;

			case PeerRequest::PEERREQUEST_UTMPLAYER:
				{
					if (incomingRequest.nick.length() > 0)
					{
						const AsciiString *name = reinterpret_cast<BfmeGameSpyPlayerLookup *>(TheGameSpyInfo)->lookupPlayerName(incomingRequest.nick.c_str());
						if (name)
							peerUTMPlayer( peer, name->str(), incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
						else
							peerUTMPlayer( peer, incomingRequest.nick.c_str(), incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
					}
				}
				break;

			case PeerRequest::PEERREQUEST_UTMROOM:
				{
					peerUTMRoom( peer, (payload.flag)?StagingRoom:GroupRoom, incomingRequest.id.c_str(), incomingRequest.options.c_str(), PEERFalse );
				}
				break;

			case PeerRequest::PEERREQUEST_STARTQUICKMATCH:
				{
					self->qmInfo = incomingRequest;
					doQuickMatch( peer );
				}
				break;

			case PeerRequest::PEERREQUEST_LISTGROUPROOMS:
				self->value4A4 = 0;
				self->value4A0 = 0;
				if (self->listGroupRooms)
					peerListGroupRooms( peer, "\\roomType", listGroupRoomsCallback, this, PEERTrue );
				break;
			}
		}

		if (isThreadHosting && s_wantStateChangedHeartbeat && !self->suspendStateChanged)
		{
			UnsignedInt now = timeGetTime();
			if (now > s_lastStateChangedHeartbeat + s_heartbeatInterval)
			{
				s_lastStateChangedHeartbeat = now;
				s_wantStateChangedHeartbeat = FALSE;
				peerStateChanged( peer );
			}
		}

		// update the network
		PEERBool isConnected = PEERTrue;
		isConnected = peerIsConnected( peer );
		if ( isConnected == PEERTrue )
		{
			if (qr2Sock != INVALID_SOCKET)
			{
				// check hosting activity
				checkQR2Queries( peer, qr2Sock );
			}
			peerThink( peer );
		}
	}

	peerShutdown( peer );

	} catch ( ... ) {
		try {
			PeerResponse resp;
			resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
			resp.discon.reason = DISCONNECT_LOSTCON;
			TheGameSpyPeerMessageQueue->addResponse(resp);
		}
		catch (...)
		{
		}
	}
}

static void getPlayerProfileIDCallback(PEER peer,  PEERBool success,  const char * nick,  int profileID,  void * param)
{
	if (success && param != NULL)
	{
		*((Int *)param) = profileID;
	}
}

static void stagingRoomPlayerEnum( PEER peer, PEERBool success, RoomType roomType, int index, const char * nick, int flags, void * param )
{
	DEBUG_LOG(("Enum: success=%d, index=%d, nick=%s, flags=%d\n", success, index, nick, flags));
	if (!nick || !success)
		return;

	Int id = 0;
	peerGetPlayerProfileID(peer, nick, getPlayerProfileIDCallback, &id, PEERTrue);
	DEBUG_ASSERTCRASH(id != 0, ("Failed to fetch player ID!"));

	PeerResponse *resp = (PeerResponse *)param;
	if (flags & PEER_FLAG_OP)
	{
		resp->joinStagingRoom.isHostPresent = TRUE;
	}
	if (index < MAX_SLOTS)
	{
		resp->stagingRoomPlayerNames[index] = nick;
	}

	if (id)
	{
		PSRequest req;
		req.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
		req.player.id = id;
		TheGameSpyPSMessageQueue->addRequest(req);
	}
}

// ?Rva0038B8B7Enum@@YAXPAXHW4RoomType@@HPBDH0@Z @0x0038B8B7 104B evidence: REF callback pushed for peerEnumPlayers in joinRoomCallback 0x0038E5A0; nick success guards; peerGetPlayerProfileIDA 0x69A540 with getPlayerProfileIDCallback 0x00388BE4; flag 0x20 host 0x111; index LT 8 names 0x88 string assign 0x1B790; TheGameSpyInfo slot 0x7c
void Rva0038B8B7Enum(PEER peer, PEERBool success, RoomType roomType, int index, const char *nick, int flags, void *param)
{
	if (!nick || !success)
		return;
	Int id = 0;
	peerGetPlayerProfileIDA(peer, nick, (void *)getPlayerProfileIDCallback, &id, PEERTrue);
	PeerResponse *resp = (PeerResponse *)param;
	if (flags & 0x20)
		resp->joinStagingRoom.isHostPresent = TRUE;
	if (index < MAX_SLOTS)
		resp->stagingRoomPlayerNames[index] = nick;
	if (TheGameSpyInfo)
		TheGameSpyInfo->getStagingRoomList();
}

// ?Rva0038B91FList@@YAXPAXHHPAU_SBServer@@PBDHHHH0@Z @0x0038B91F 217B evidence: REF callback for peerListGroupRooms 0x0038BBAE; 10-param group-room enum; SBServerGetIntValue roomType 0x69BA20; string assign 0x1B790; PeerMessageQueue slot 0x20; flag 0x4A8 on groupID 0
extern "C" int SBServerGetIntValueA(SBServer server, const char *key, int idefault);
void Rva0038B91FList(PEER peer, PEERBool success, int groupID, SBServer server, const char *name, int numWaiting, int maxWaiting, int numGames, int numPlaying, void *param)
{
	if (!param || !success)
		return;
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_GROUPROOM;
	resp.groupRoom.id = groupID;
	resp.groupRoom.numWaiting = numWaiting;
	resp.groupRoom.maxWaiting = maxWaiting;
	resp.groupRoom.numGames = numGames;
	resp.groupRoom.numPlaying = numPlaying;
	if (server)
		resp.unknown_payload[5] = SBServerGetIntValueA(server, "roomType", 1);
	if (name)
		resp.groupRoomName = name;
	TheGameSpyPeerMessageQueue->addResponse(resp);
	if (groupID == 0)
		((unsigned char *)param)[0x4A8] = 1;
}

static void joinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result, RoomType roomType, void *param)
{
	DEBUG_LOG(("JoinRoomCallback: success==%d, result==%d\n", success, result));
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
		return;
	DEBUG_LOG(("Room id was %d from thread %X\n", t->getLocalRoomID(), t));
	DEBUG_LOG(("Current staging server name is [%ls]\n", t->getLocalStagingServerName().c_str()));
	DEBUG_LOG(("Room type is %d (GroupRoom=%d, StagingRoom=%d, TitleRoom=%d)\n", roomType, GroupRoom, StagingRoom, TitleRoom));

#ifdef USE_BROADCAST_KEYS
	if (success)
	{
		t->pushStatsToRoom(peer);
		t->getStatsFromRoom(peer, roomType);
	}
#endif // USE_BROADCAST_KEYS

	switch (roomType)
	{
		case GroupRoom:
			{
#ifdef USE_BROADCAST_KEYS
				t->clearPlayerStats(GroupRoom);
#endif // USE_BROADCAST_KEYS
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINGROUPROOM;
				resp.joinGroupRoom.id = t->getLocalRoomID();
				resp.joinGroupRoom.ok = success;
				TheGameSpyPeerMessageQueue->addResponse(resp);
				t->roomJoined(success == PEERTrue);
				DEBUG_LOG(("Entered group room %d, qm is %d\n", t->getLocalRoomID(), t->getQMGroupRoom()));
				if ((!t->getQMGroupRoom()) || (t->getQMGroupRoom() != t->getLocalRoomID()))
				{
					DEBUG_LOG(("Updating buddy status\n"));
					updateBuddyStatus( BUDDY_LOBBY, t->getLocalRoomID() );
				}
			}
			break;
		case StagingRoom:
			{
#ifdef USE_BROADCAST_KEYS
				t->clearPlayerStats(StagingRoom);
#endif // USE_BROADCAST_KEYS
				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_JOINSTAGINGROOM;
				resp.joinStagingRoom.id = t->getLocalRoomID();
				resp.joinStagingRoom.ok = success;
				resp.joinStagingRoom.result = result;
				if (success)
				{
					DEBUG_LOG(("joinRoomCallback() - game name is now '%ls'\n", t->getLocalStagingServerName().c_str()));
					updateBuddyStatus( BUDDY_STAGING, 0, WideCharStringToMultiByte(t->getLocalStagingServerName().c_str()) );
				}

				resp.joinStagingRoom.isHostPresent = FALSE;
				DEBUG_LOG(("Enum of staging room players\n"));
				peerEnumPlayers(peer, StagingRoom, stagingRoomPlayerEnum, &resp);
				DEBUG_LOG(("Host %s present\n", (resp.joinStagingRoom.isHostPresent)?"is":"is not"));

				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
			break;
	}
}

// Gets called once for each group room when listing group rooms.
// After this has been called for each group room, it will be
// called one more time with groupID==0 and name==NULL.
/////////////////////////////////////////////////////////////////
static void listGroupRoomsCallback(PEER peer, PEERBool success,
														int groupID, SBServer server,
														const char * name, int numWaiting,
														int maxWaiting, int numGames,
														int numPlaying, void * param)
{
	DEBUG_LOG(("listGroupRoomsCallback, success=%d, server=%X, groupID=%d\n", success, server, groupID));
#ifdef SERVER_DEBUGGING
	CheckServers(peer);
#endif // SERVER_DEBUGGING
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		DEBUG_LOG(("No thread!  Bailing!\n"));
		return;
	}

	if (success)
	{
		DEBUG_LOG(("Saw group room of %d (%s) at address %X %X\n", groupID, name, server, (server)?server->keyvals:0));
		PeerResponse resp;
		resp.peerResponseType = PeerResponse::PEERRESPONSE_GROUPROOM;
		resp.groupRoom.id = groupID;
		resp.groupRoom.numWaiting = numWaiting;
		resp.groupRoom.maxWaiting = maxWaiting;
		resp.groupRoom.numGames = numGames;
		resp.groupRoom.numPlaying = numPlaying;
		if (name)
		{
			resp.groupRoomName = name;
			//t->setQMGroupRoom(groupID);
		}
		else
		{
			resp.groupRoomName.empty();
		}
		TheGameSpyPeerMessageQueue->addResponse(resp);
#ifdef SERVER_DEBUGGING
		CheckServers(peer);
		DEBUG_LOG(("\n"));
#endif // SERVER_DEBUGGING
	}
	else
	{
		DEBUG_LOG(("Failure!\n"));
	}
}

// ?connectCallback@PeerThreadClass@@ present-unmatched
void PeerThreadClass::connectCallback( PEER peer, PEERBool success )
{
	PeerResponse resp;
	if(!success)
	{
		//updateBuddyStatus( BUDDY_OFFLINE );
		resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
		resp.discon.reason = DISCONNECT_COULDNOTCONNECT;
		TheGameSpyPeerMessageQueue->addResponse(resp);
		return;
	}

	updateBuddyStatus( BUDDY_ONLINE );

	m_isConnected = true;
	DEBUG_LOG(("Connected as profile %d (%s)\n", m_profileID, m_loginName.c_str()));
	resp.peerResponseType = PeerResponse::PEERRESPONSE_LOGIN;
	resp.player.profileID = m_profileID;
	resp.nick = m_loginName;
	GetLocalChatConnectionAddress("peerchat.gamespy.com", 6667, localIP);
	chatSetLocalIP(localIP);
	resp.player.internalIP = ntohl(localIP);
	resp.player.externalIP = ntohl(peerGetLocalIP(peer));
	TheGameSpyPeerMessageQueue->addResponse(resp);

	PSRequest psReq;
	psReq.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
	psReq.player.id = m_profileID;
	psReq.nick = m_originalName;
	psReq.email = m_email;
	psReq.password = m_password;
	TheGameSpyPSMessageQueue->addRequest(psReq);

#ifdef SERVER_DEBUGGING
	DEBUG_LOG(("Before peerListGroupRooms()\n"));
	CheckServers(peer);
#endif // SERVER_DEBUGGING
	peerListGroupRooms( peer, NULL, listGroupRoomsCallback, this, PEERTrue );
#ifdef SERVER_DEBUGGING
	DEBUG_LOG(("After peerListGroupRooms()\n"));
	CheckServers(peer);
#endif // SERVER_DEBUGGING
}

// Nickname retry callback is recovered in PeerThreadNickError.cpp.

void disconnectedCallback(PEER peer, const char * reason, void * param)
{
	DEBUG_LOG(("disconnectedCallback(): reason was '%s'\n", reason));
	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (t)
		t->markAsDisconnected();
	//updateBuddyStatus( BUDDY_OFFLINE );
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_DISCONNECT;
	resp.discon.reason = DISCONNECT_LOSTCON;
	SerialAuthResult res = TheGameSpyPeerMessageQueue->getSerialAuthResult();
	switch (res)
	{
		case SERIAL_NONEXISTENT:
			resp.discon.reason = DISCONNECT_SERIAL_NOT_PRESENT;
			break;
		case SERIAL_AUTHFAILED:
			resp.discon.reason = DISCONNECT_SERIAL_INVALID;
			break;
		case SERIAL_BANNED:
			resp.discon.reason = DISCONNECT_SERIAL_BANNED;
			break;
	}
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

void roomMessageCallback(PEER peer, RoomType roomType, const char * nick, const char * message, MessageType messageType, void * param)
{
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_MESSAGE;
	resp.nick = nick;
	resp.text = MultiByteToWideCharSingleLine(message);
	resp.message.isPrivate = FALSE;
	resp.message.isAction = (messageType == ActionMessage);
	TheGameSpyPeerMessageQueue->addResponse(resp);
	DEBUG_LOG(("Saw text [%hs] (%ls) %d chars Orig was %s (%d chars)\n", nick, resp.text.c_str(), resp.text.length(), message, strlen(message)));

	UnsignedInt IP;
	peerGetPlayerInfoNoWait(peer, nick, &IP, &resp.message.profileID);
	
	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (t && (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED))
	{
		if (resp.message.profileID == matchbotProfileID)
		{
			char *lastStr = NULL;
			char *cmd = strtok_r((char *)message, " ", &lastStr);
			if ( cmd && strcmp(cmd, "MBOT:POOLSIZE") == 0 )
			{
				Int poolSize = 0;

				while (1)
				{
					char *poolStr = strtok_r(NULL, " ", &lastStr);
					char *sizeStr = strtok_r(NULL, " ", &lastStr);
					if (poolStr && sizeStr)
					{
						Int pool = atoi(poolStr);
						Int size = atoi(sizeStr);
						if (pool == t->getQMLadder())
						{
							poolSize = size;
							break;
						}
					}
					else
						break;
				}

				PeerResponse resp;
				resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
				resp.qmStatus.status = QM_POOLSIZE;
				resp.qmStatus.poolSize = poolSize;
				TheGameSpyPeerMessageQueue->addResponse(resp);
			}
		}
	}
}

void gameStartedCallback( PEER peer, UnsignedInt IP, const char *message, void *param )
{
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_GAMESTART;
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

// Retail callback lives in PeerThreadPlayerMessage.cpp.






static void getPlayerInfo(PeerThreadClass *t, PEER peer, const char *nick, Int& id, UnsignedInt& IP,
													std::string& locale, Int& wins, Int& losses, Int& rankPoints, Int& side, Int& preorder,
													RoomType roomType, Int& flags, Int& rank1v1, Int& rank2v2, Int& bSide)
{
	if (!t || !nick)
		return;
	peerGetPlayerInfoNoWait(peer, nick, &IP, &id);
#ifdef USE_BROADCAST_KEYS
	//locale.printf
	Int localeIndex = t->lookupStatForPlayer(roomType, nick, "b_locale");
	AsciiString tmp;
	tmp.format("%d", localeIndex);
	locale = tmp.str();

	wins = t->lookupStatForPlayer(roomType, nick, "b_wins");
	losses = t->lookupStatForPlayer(roomType, nick, "b_losses");
	rankPoints = t->lookupStatForPlayer(roomType, nick, "b_points");
	side = t->lookupStatForPlayer(roomType, nick, "b_side");
	preorder = t->lookupStatForPlayer(roomType, nick, "b_pre");
	flags = 0;
	rank1v1 = t->lookupStatForPlayer(roomType, nick, "b_rank1v1");
	rank2v2 = t->lookupStatForPlayer(roomType, nick, "b_rank2v2");
	bSide = t->lookupStatForPlayer(roomType, nick, "b_BSide");
	peerGetPlayerFlags(peer, nick, roomType, &flags);
#else // USE_BROADCAST_KEYS
	const char *s;
	s = peerGetGlobalWatchKey(peer, nick, "locale");
	locale = (s)?s:"";
	s = peerGetGlobalWatchKey(peer, nick, "wins");
	wins = atoi((s)?s:"");
	s = peerGetGlobalWatchKey(peer, nick, "losses");
	losses = atoi((s)?s:"");
	s = peerGetGlobalWatchKey(peer, nick, "points");
	rankPoints = atoi((s)?s:"");
	s = peerGetGlobalWatchKey(peer, nick, "side");
	side = atoi((s)?s:"");
	s = peerGetGlobalWatchKey(peer, nick, "pre");
	preorder = atoi((s)?s:"");
	flags = 0;
	peerGetPlayerFlags(peer, nick, roomType, &flags);
#endif // USE_BROADCAST_KEYS
	DEBUG_LOG(("getPlayerInfo(%d) - %s has locale %s, wins:%d, losses:%d, rankPoints:%d, side:%d, preorder:%d\n",
		id, nick, locale.c_str(), wins, losses, rankPoints, side, preorder));
}

static __forceinline void getPlayerInfo(PeerThreadClass *t, PEER peer, const char *nick, Int& id, UnsignedInt& IP,
													std::string& locale, Int& wins, Int& losses, Int& rankPoints, Int& side, Int& preorder,
													RoomType roomType, Int& flags)
{
	Int rank1v1 = 0, rank2v2 = 0, bSide = 0;
	getPlayerInfo(t, peer, nick, id, IP, locale, wins, losses, rankPoints, side, preorder, roomType, flags, rank1v1, rank2v2, bSide);
}

// ?setPeerResponseCode absent-from-retail
template <class Code> static __forceinline void setPeerResponseCode(Code &code, Int value) { code = static_cast<Code>(value); }

static void roomKeyChangedCallback(PEER peer, RoomType roomType, const char *nick, const char *key, const char *val, void *param)
{
#ifdef USE_BROADCAST_KEYS
	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t || !nick || !key || !val)
	{
		// Retail retains this comparison when the callback arguments are invalid.
		(void)strcmp(nick, "(END)");
		return;
	}

	if (strcmp(key, "username") && strcmp(key, "b_flags"))
	{
		DEBUG_LOG(("roomKeyChangedCallback() - %s set %s=%s\n", nick, key, val));
	}

	t->trackStatsForPlayer(roomType, nick, key, val);

	PeerResponse resp;
	// Retail queues code22 here; its original enumerator spelling is unknown.
	setPeerResponseCode(resp.peerResponseType, 22);
	resp.nick = nick;
	resp.player.roomType = roomType;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		resp.player.roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);
#endif // USE_BROADCAST_KEYS
}

#ifdef USE_BROADCAST_KEYS
void getRoomKeysCallback(PEER peer, PEERBool success, RoomType roomType, const char *nick, int num, char **keys, char **values, void *param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t || !nick || !num || !success || !keys || !values)
	{
		DEBUG_ASSERTCRASH(!nick || strcmp(nick,"(END)")==0, ("getRoomKeysCallback bad key/value %X/%X, nick=%s", keys, values, nick));
		return;
	}

	for (Int i=0; i<num; ++i)
	{
		t->trackStatsForPlayer(roomType, nick, keys[i], values[i]);
	}

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERINFO;
	resp.nick = nick;
	resp.player.roomType = roomType;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		resp.player.roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);
}
#endif // USE_BROADCAST_KEYS

static void globalKeyChangedCallback(PEER peer, const char *nick, const char *key, const char *val, void *param)
{
	if (!nick)
		return;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERINFO;
	resp.nick = nick;
	resp.player.roomType = t->getCurrentGroupRoom()?GroupRoom:StagingRoom;

	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		resp.player.roomType, resp.player.flags);
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

void playerJoinedCallback(PEER peer, RoomType roomType, const char * nick, void * param)
{
	if (!nick)
		return;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERJOIN;
	resp.nick = nick;
	resp.player.roomType = roomType;

	// Native passes these three outputs at response offsets 33C/340/344.
	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

void playerLeftCallback(PEER peer, RoomType roomType, const char * nick, const char * reason, void * param)
{
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERLEFT;
	resp.nick = nick;
	resp.player.roomType = roomType;
	resp.player.profileID = 0;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	// Native passes these three outputs at response offsets 33C/340/344.
	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);

//	PeerThreadClass *t = (PeerThreadClass *)param;
//	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (t->getQMStatus() != QM_IDLE && t->getQMStatus() != QM_STOPPED)
	{
		if (!_strcmpi(t->getQMBotName().c_str(), nick))
		{
			// matchbot left - bail
			PeerResponse resp;
			resp.peerResponseType = PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS;
			resp.qmStatus.status = QM_COULDNOTFINDBOT;
			TheGameSpyPeerMessageQueue->addResponse(resp);

			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_STOPQUICKMATCH;
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

void playerChangedNickCallback(PEER peer, RoomType roomType, const char * oldNick, const char * newNick, void * param)
{
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERCHANGEDNICK;
	resp.nick = newNick;
	resp.oldNick = oldNick;
	resp.player.roomType = roomType;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	// Native passes these three outputs at response offsets 33C/340/344.
	getPlayerInfo(t, peer, newNick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

static void playerInfoCallback(PEER peer, RoomType roomType, const char * nick, unsigned int IP, int profileID, void * param)
{
	if (!nick)
		return;
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERINFO;
	resp.nick = nick;
	resp.player.roomType = roomType;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	// Native outputs at response33C/340/344 occupy the top frame slots.
	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
DEBUG_LOG(("**GS playerInfoCallback name=%s, local=%s\n", nick, resp.locale.c_str() ));
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

static void playerFlagsChangedCallback(PEER peer, RoomType roomType, const char * nick, int oldFlags, int newFlags, void * param)
{
	if (!nick)
		return;
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_PLAYERCHANGEDFLAGS;
	resp.nick = nick;
	resp.player.roomType = roomType;

	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(t, ("No Peer thread!"));
	if (!t)
		return;

	// Native passes these three outputs at response offsets 33C/340/344.
	getPlayerInfo(t, peer, nick, resp.player.profileID, resp.player.IP,
		resp.locale, resp.player.wins, resp.player.losses,
		resp.player.rankPoints, resp.player.side, resp.player.preorder,
		roomType, resp.player.flags,
		reinterpret_cast<Int &>(resp.unknown_payload[140]),
		reinterpret_cast<Int &>(resp.unknown_payload[141]),
		reinterpret_cast<Int &>(resp.unknown_payload[142]));
	TheGameSpyPeerMessageQueue->addResponse(resp);
}

#ifdef DEBUG_LOGGING
/*
static void enumFunc(char *key, char *val, void *param)
{
	DEBUG_LOG(("  [%s] = [%s]\n", key, val));
}
*/
#endif

static void listingGamesCallback(PEER peer, PEERBool success, const char * name, SBServer server, PEERBool staging, int msg, Int percentListed, void * param)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t || !success)
		return;

#ifdef DEBUG_LOGGING
	AsciiString cmdStr = "<Unknown>";
	switch(msg)
	{
		case PEER_ADD:
			cmdStr = "PEER_ADD";
			break;
		case PEER_UPDATE:
			cmdStr = "PEER_UPDATE";
			break;
		case PEER_REMOVE:
			cmdStr = "PEER_REMOVE";
			break;
		case PEER_CLEAR:
			cmdStr = "PEER_CLEAR";
			break;
		case PEER_COMPLETE:
			cmdStr = "PEER_COMPLETE";
			break;
	}
	DEBUG_LOG(("listingGamesCallback() - doing command %s on server %X\n", cmdStr.str(), server));
#endif // DEBUG_LOGGING

//	PeerThreadClass *t = (PeerThreadClass *)param;
	DEBUG_ASSERTCRASH(name || msg==PEER_CLEAR || msg==PEER_COMPLETE, ("Game has no name!\n"));
	if (!t || !success || (!name && (msg == PEER_ADD || msg == PEER_UPDATE)))
	{
		DEBUG_LOG(("Bailing from listingGamesCallback() - success=%d, name=%X, server=%X, msg=%X\n", success, name, server, msg));
		return;
	}
	if (!name)
		name = "bogus";

	if (server && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		DEBUG_ASSERTCRASH(server->keyvals, ("Looking at an already-freed server for msg type %d!", msg));
		if (!server->keyvals)
		{
			msg = PEER_REMOVE;
		}
	}

	if (server && success && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		DEBUG_LOG(("Game name is '%s'\n", name));
		const char *newname = SBServerGetStringValue(server, "gamename", (char *)name);
		if (strcmp(newname, "ccgenzh"))
			name = newname;
		DEBUG_LOG(("Game name is now '%s'\n", name));
	}

	DEBUG_LOG(("listingGamesCallback - got percent complete %d\n", percentListed));
	if (percentListed == 100)
	{
		if (!t->getSawCompleteGameList())
		{
			t->setSawCompleteGameList(TRUE);
			PeerResponse completeResp;
			completeResp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOMLISTCOMPLETE;
			TheGameSpyPeerMessageQueue->addResponse(completeResp);
		}
	}

	AsciiString gameName = name;
	AsciiString tmp = gameName;
	AsciiString hostName;
	tmp.nextToken(&hostName, " ");
	const char *firstSpace = gameName.find(' ');
	if(firstSpace)
	{
		gameName.set(firstSpace + 1);
		//gameName.trim();
		DEBUG_LOG(("Hostname/Gamename split leaves '%s' hosting '%s'\n", hostName.str(), gameName.str()));
	}
	PeerResponse resp;
	resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
	resp.stagingRoom.action = msg;
	resp.stagingRoom.isStaging = staging;
	resp.stagingRoom.percentComplete = percentListed;

	if (server && (msg == PEER_ADD || msg == PEER_UPDATE))
	{
		Bool hasPassword = (Bool)SBServerGetIntValue(server, PW_STR, FALSE);
		Bool allowObservers = (Bool)SBServerGetIntValue(server, OBS_STR, FALSE);
    Bool usesStats = (Bool)SBServerGetIntValue(server, USE_STATS_STR, TRUE);
		const char *verStr = SBServerGetStringValue(server, "gamever", "000000");
		const char *exeStr = SBServerGetStringValue(server, EXECRC_STR, "000000");
		const char *iniStr = SBServerGetStringValue(server, INICRC_STR, "000000");
		const char *ladIPStr = SBServerGetStringValue(server, LADIP_STR, "000000");
		const char *pingStr = SBServerGetStringValue(server, PINGSTR_STR, "FFFFFFFFFFFFFFFF");
		UnsignedShort ladPort = (UnsignedShort)SBServerGetIntValue(server, LADPORT_STR, 0);
		UnsignedInt verVal = strtoul(verStr, NULL, 10);
		UnsignedInt exeVal = strtoul(exeStr, NULL, 10);
		UnsignedInt iniVal = strtoul(iniStr, NULL, 10);
		resp.stagingRoom.requiresPassword = hasPassword;
		resp.stagingRoom.allowObservers = allowObservers;
    resp.stagingRoom.useStats = usesStats;
		resp.stagingRoom.version = verVal;
		resp.stagingRoom.exeCRC = exeVal;
		resp.stagingRoom.iniCRC = iniVal;
		resp.stagingServerLadderIP = ladIPStr;
		resp.stagingServerPingString = pingStr;
		resp.stagingRoom.ladderPort = ladPort;
		resp.stagingRoom.numPlayers = SBServerGetIntValue(server, NUMPLAYER_STR, 0);
		resp.stagingRoom.numObservers = SBServerGetIntValue(server, NUMOBS_STR, 0);
		resp.stagingRoom.maxPlayers = SBServerGetIntValue(server, MAXPLAYER_STR, 8);
		resp.stagingRoomMapName = SBServerGetStringValue(server, "mapname", "");
		for (Int i=0; i<MAX_SLOTS; ++i)
		{
			resp.stagingRoomPlayerNames[i] = SBServerGetPlayerStringValue(server, i, NAME__STR, "");
			resp.stagingRoom.wins[i] = SBServerGetPlayerIntValue(server, i, WINS__STR, 0);
			resp.stagingRoom.losses[i] = SBServerGetPlayerIntValue(server, i, LOSSES__STR, 0);
			resp.stagingRoom.profileID[i] = SBServerGetPlayerIntValue(server, i, "pid", 0);
			resp.stagingRoom.color[i] = SBServerGetPlayerIntValue(server, i, COLOR__STR, 0);
			resp.stagingRoom.faction[i] = SBServerGetPlayerIntValue(server, i, FACTION__STR, 0);
#ifdef DEBUG_LOGGING
			if (resp.stagingRoomPlayerNames[i].length())
			{
				DEBUG_LOG(("Player %d raw stuff: [%s] [%d] [%d] [%d]\n", i, resp.stagingRoomPlayerNames[i].c_str(), resp.stagingRoom.wins[i], resp.stagingRoom.losses[i], resp.stagingRoom.profileID[i]));
			}
#endif
		}
		if (resp.stagingRoomPlayerNames[0].empty())
		{
			resp.stagingRoomPlayerNames[0] = hostName.str();
		}
		DEBUG_ASSERTCRASH(resp.stagingRoomPlayerNames[0].empty() == false, ("No host!"));
		DEBUG_LOG(("Raw stuff: [%s] [%s] [%s] [%d] [%d] [%d]\n", verStr, exeStr, iniStr, hasPassword, allowObservers, usesStats));
		DEBUG_LOG(("Raw stuff: [%s] [%s] [%d]\n", pingStr, ladIPStr, ladPort));
		DEBUG_LOG(("Saw game with stuff %s %d %X %X %X %s\n", resp.stagingRoomMapName.c_str(), hasPassword, verVal, exeVal, iniVal, SBServerGetStringValue(server, "password", "missing")));
#ifdef PING_TEST
	PING_LOG(("%s\n", pingStr));
#endif
	}

	if (msg == PEER_ADD || msg == PEER_UPDATE)
	{
		if (!resp.stagingRoom.exeCRC || !resp.stagingRoom.iniCRC)
		{
			if (SBServerHasBasicKeys(server))
			{
				DEBUG_LOG(("Server %x does not have basic keys\n", server));
				return;
			}
			else
			{
				DEBUG_LOG(("Server %x has basic keys, yet has no info\n", server));
			}
			if (msg == PEER_UPDATE)
			{
				PeerRequest req;
				req.peerRequestType = PeerRequest::PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO;
				req.stagingRoom.id = t->findServer( server );
				DEBUG_LOG(("Add/update a 0/0 server %X (%d, %s) - requesting full update to see if that helps.\n",
					server, resp.stagingRoom.id, gameName.str()));
				TheGameSpyPeerMessageQueue->addRequest(req);
			}
			return; // don't actually try to list it.
		}
	}

	switch (msg)
	{
		case PEER_CLEAR:
			t->clearServers();
			break;
		case PEER_ADD:
		case PEER_UPDATE:
			resp.stagingRoom.id = t->findServer( server );
			DEBUG_LOG(("Add/update on server %X (%d, %s)\n", server, resp.stagingRoom.id, gameName.str()));
			resp.stagingServerName = MultiByteToWideCharSingleLine( gameName.str() );
			DEBUG_LOG(("Server had basic=%d, full=%d\n", SBServerHasBasicKeys(server), SBServerHasFullKeys(server)));
#ifdef DEBUG_LOGGING
			//SBServerEnumKeys(server, enumFunc, NULL);
#endif
			break;
		case PEER_REMOVE:
			DEBUG_LOG(("Removing server %X (%d)\n", server, resp.stagingRoom.id));
			resp.stagingRoom.id = t->removeServerFromMap( server );
			break;
	}

	TheGameSpyPeerMessageQueue->addResponse(resp);
}

//-------------------------------------------------------------------------

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")

// Address-derived callees read directly from the retail body at 0x00517EA2.
// Their bodies and semantic names are outside this recovered response pump.
extern void __cdecl rva00416C69(void);
extern void __cdecl rva005BDAC1(void);
extern void __cdecl rva005AF12F(void *response);

// The native call uses GameSpyInfo vtable slot 0x5D. Earlier slots have no
// identity claim in this TU; this view exists only to express that call.
#define RVA00517EA2_INFO_SLOT(N) virtual void slot##N(void);
class Rva00517EA2InfoView
{
public:
	RVA00517EA2_INFO_SLOT(00)
	RVA00517EA2_INFO_SLOT(01)
	RVA00517EA2_INFO_SLOT(02)
	RVA00517EA2_INFO_SLOT(03)
	RVA00517EA2_INFO_SLOT(04)
	RVA00517EA2_INFO_SLOT(05)
	RVA00517EA2_INFO_SLOT(06)
	RVA00517EA2_INFO_SLOT(07)
	RVA00517EA2_INFO_SLOT(08)
	RVA00517EA2_INFO_SLOT(09)
	RVA00517EA2_INFO_SLOT(10)
	RVA00517EA2_INFO_SLOT(11)
	RVA00517EA2_INFO_SLOT(12)
	RVA00517EA2_INFO_SLOT(13)
	RVA00517EA2_INFO_SLOT(14)
	RVA00517EA2_INFO_SLOT(15)
	RVA00517EA2_INFO_SLOT(16)
	RVA00517EA2_INFO_SLOT(17)
	RVA00517EA2_INFO_SLOT(18)
	RVA00517EA2_INFO_SLOT(19)
	RVA00517EA2_INFO_SLOT(20)
	RVA00517EA2_INFO_SLOT(21)
	RVA00517EA2_INFO_SLOT(22)
	RVA00517EA2_INFO_SLOT(23)
	RVA00517EA2_INFO_SLOT(24)
	RVA00517EA2_INFO_SLOT(25)
	RVA00517EA2_INFO_SLOT(26)
	RVA00517EA2_INFO_SLOT(27)
	RVA00517EA2_INFO_SLOT(28)
	RVA00517EA2_INFO_SLOT(29)
	RVA00517EA2_INFO_SLOT(30)
	RVA00517EA2_INFO_SLOT(31)
	RVA00517EA2_INFO_SLOT(32)
	RVA00517EA2_INFO_SLOT(33)
	RVA00517EA2_INFO_SLOT(34)
	RVA00517EA2_INFO_SLOT(35)
	RVA00517EA2_INFO_SLOT(36)
	RVA00517EA2_INFO_SLOT(37)
	RVA00517EA2_INFO_SLOT(38)
	RVA00517EA2_INFO_SLOT(39)
	RVA00517EA2_INFO_SLOT(40)
	RVA00517EA2_INFO_SLOT(41)
	RVA00517EA2_INFO_SLOT(42)
	RVA00517EA2_INFO_SLOT(43)
	RVA00517EA2_INFO_SLOT(44)
	RVA00517EA2_INFO_SLOT(45)
	RVA00517EA2_INFO_SLOT(46)
	RVA00517EA2_INFO_SLOT(47)
	RVA00517EA2_INFO_SLOT(48)
	RVA00517EA2_INFO_SLOT(49)
	RVA00517EA2_INFO_SLOT(50)
	RVA00517EA2_INFO_SLOT(51)
	RVA00517EA2_INFO_SLOT(52)
	RVA00517EA2_INFO_SLOT(53)
	RVA00517EA2_INFO_SLOT(54)
	RVA00517EA2_INFO_SLOT(55)
	RVA00517EA2_INFO_SLOT(56)
	RVA00517EA2_INFO_SLOT(57)
	RVA00517EA2_INFO_SLOT(58)
	RVA00517EA2_INFO_SLOT(59)
	RVA00517EA2_INFO_SLOT(60)
	RVA00517EA2_INFO_SLOT(61)
	RVA00517EA2_INFO_SLOT(62)
	RVA00517EA2_INFO_SLOT(63)
	RVA00517EA2_INFO_SLOT(64)
	RVA00517EA2_INFO_SLOT(65)
	RVA00517EA2_INFO_SLOT(66)
	RVA00517EA2_INFO_SLOT(67)
	RVA00517EA2_INFO_SLOT(68)
	RVA00517EA2_INFO_SLOT(69)
	RVA00517EA2_INFO_SLOT(70)
	RVA00517EA2_INFO_SLOT(71)
	RVA00517EA2_INFO_SLOT(72)
	RVA00517EA2_INFO_SLOT(73)
	RVA00517EA2_INFO_SLOT(74)
	RVA00517EA2_INFO_SLOT(75)
	RVA00517EA2_INFO_SLOT(76)
	RVA00517EA2_INFO_SLOT(77)
	RVA00517EA2_INFO_SLOT(78)
	RVA00517EA2_INFO_SLOT(79)
	RVA00517EA2_INFO_SLOT(80)
	RVA00517EA2_INFO_SLOT(81)
	RVA00517EA2_INFO_SLOT(82)
	RVA00517EA2_INFO_SLOT(83)
	RVA00517EA2_INFO_SLOT(84)
	RVA00517EA2_INFO_SLOT(85)
	RVA00517EA2_INFO_SLOT(86)
	RVA00517EA2_INFO_SLOT(87)
	RVA00517EA2_INFO_SLOT(88)
	RVA00517EA2_INFO_SLOT(89)
	RVA00517EA2_INFO_SLOT(90)
	RVA00517EA2_INFO_SLOT(91)
	RVA00517EA2_INFO_SLOT(92)
	virtual Int responseLimit(void);
};
#undef RVA00517EA2_INFO_SLOT

class Rva00517EA2
{
public:
	void rva00517EA2();
};

void Rva00517EA2::rva00517EA2()
{
	if (TheGameSpyPeerMessageQueue)
	{
		rva00416C69();
		rva005BDAC1();
		Int responsesLeft = reinterpret_cast<Rva00517EA2InfoView *>(TheGameSpyInfo)->responseLimit();
		PeerResponse response;
		while (responsesLeft)
		{
			--responsesLeft;
			if (!TheGameSpyPeerMessageQueue->getResponse(response))
				break;
			rva005AF12F(&response);
		}
	}
}

#pragma comment(linker, "/alternatename:??0PeerRequest@@QAE@XZ=??0BfmeOpaqueOwnedRecord492@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1PeerRequest@@QAE@XZ=??1BfmeOpaqueOwnedRecord492@@QAE@XZ")
#pragma comment(linker, "/alternatename:?getQMBotName@PeerThreadClass@@QAE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ=?get@Rva00389F2CNarrowField@@QBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@XZ")
