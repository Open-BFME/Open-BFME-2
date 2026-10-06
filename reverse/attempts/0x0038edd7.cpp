// ?Thread_Function@PeerThreadClass@@UAEXXZ
// partial score=0.9995 date=2026-10-06
// Banked PeerThreadClass::Thread_Function (retail 0x0038EDD7, 4723-byte main body;
// catch funclets 0x0039004A..0x003900A0 and the 26-entry jump table follow).
// Replaces the Zero Hour Thread_Function in PeerThread.cpp (lines of the old body).
// In scratch this body matches 4721/4723 bytes and leaves the unit's other 48
// rows byte-exact, given these unit changes (all tested together):
//  - cl line: add /G7 (retail's imul for i*12 in the slot loops);
//  - wrap the sweep Peer.h in extern "C" { } before BuddyThread.h (SDK calls
//    nothrow, so retail's batched stack cleanup inside the try);
//  - atoi as the msvcr71 import like _snprintf: #define atoi atoi_unimported
//    around the existing early <stdlib.h>, then declare it dllimport;
//  - Rva0038BDEEReceiver gains void rva0038BD70(PEER);
//  - PeerThreadRetail.h request enum: LEAVEGROUPROOMONLY at 6 (STARTGAMELIST..
//    LEAVESTAGINGROOM become 7..12, UTMPLAYER stays 13), and MESSAGEROOMNOTICE,
//    REFRESHGAMELIST, LISTGROUPROOMS, UTMSTAGINGPN, PUSHSTATSVALUES as 21..25.
// Remaining 2 bytes, +0x121A: heartbeat test. Retail loads s_lastStateChanged-
// Heartbeat into ecx, then s_heartbeatInterval into edx, add edx,ecx; ours loads
// interval first (add ecx,edx). Not changed by operand order, </<=/> forms,
// temporaries, helper inlining, static declaration order, initializer, DWORD/Int
// types, non-static linkage, volatile, renaming, /G5-/G7, /Ob1.
// Pins still needed to land: C names of the SDK calls (_peerConnect,
// _peerSetTitle, _qr2_register_key, _peerLeaveRoom, ...) to their A-suffixed /
// pi* rows, findServerByID 0x003896BD, doCDKeyAuthentication 0x0038B4D7,
// OptionPreferences getOnlineIPAddress 0x002E514A and dtor 0x002E4272,
// GameModePreferences ctor/dtor 0x0054F52F/0x0054F508, chatSetLocalIP
// 0x0069BD40, _Rb_tree clear (stagingServers) 0x00389129, basic_string
// append(const&) 0x0002B250. The 6-byte row ?Rva0039009BGet@@YAHXZ at
// 0x0039009B is this function's inner catch(...) funclet, not a getter.
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
	GameModePreferences(Int mode);
	virtual ~GameModePreferences();
	AsciiString rva0044D986();
private:
	unsigned char m_unrecovered[0x18];
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

					GameModePreferences modePrefs(0);
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
#undef payload
