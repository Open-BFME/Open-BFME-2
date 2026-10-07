// TU-scoped BFME2 GameSpy request/response views; BFME1 donor revision6583b3c1.
// Request ownership and extent1EC come from native389AAA/1EF661/1EF723 and
// player-left callback38C788. Assignment38B248 witnesses union copy order and
// extents; its largest alternative retains212 bytes with unnamed additions;
// unused donor payload fields do not establish target names or offsets.
// Target copy/dtor/default-ctor 389C14/38A063/389F77 establish string members
// through F4 plus vector100 and total extent348. Native callback38B5DB stores
// room type at118 and IP at120. Other payload names remain donor leads; the
// 572-byte unknown union alternative preserves the independently proven size.
// PeerResponseAssign.cpp independently witnesses these same owning offsets.
#include <vector>
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

// FILE: PeerThread.h //////////////////////////////////////////////////////
// Generals GameSpy Peer-to-peer chat thread class interface
// Author: Matthew D. Campbell, June 2002

#pragma once

// TU-scoped stand-in for GameNetwork/GameSpy/PeerThread.h -- see the note on
// PeerRequest::gameOptions below. Scoped through /Ireference/shims/nat.

#ifndef __PEERTHREAD_H__
#define __PEERTHREAD_H__

#include "GameSpy/Peer/Peer.h"
#include "GameNetwork/NetworkDefs.h"

enum SerialAuthResult
{
	SERIAL_NONEXISTENT,
	SERIAL_AUTHFAILED,
	SERIAL_BANNED,
	SERIAL_OK
};

// this class encapsulates a request for the peer thread
class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	enum
	{
		PEERREQUEST_LOGIN,				// attempt to login
		PEERREQUEST_LOGOUT,				// log out if connected
		PEERREQUEST_MESSAGEPLAYER,
		PEERREQUEST_MESSAGEROOM,
		PEERREQUEST_JOINGROUPROOM,
		PEERREQUEST_LEAVEGROUPROOM,
		// BFME 2 adds a leave-group-only request here: Thread_Function at
		// 0x0038EDD7 dispatches value 6 to it and STARTGAMELIST..LEAVESTAGINGROOM
		// to 7..12, which keeps UTMPLAYER at 13 as the NAT call sites store it.
		PEERREQUEST_LEAVEGROUPROOMONLY,
		PEERREQUEST_STARTGAMELIST,
		PEERREQUEST_STOPGAMELIST,
		PEERREQUEST_CREATESTAGINGROOM,
		PEERREQUEST_SETGAMEOPTIONS,
		PEERREQUEST_JOINSTAGINGROOM,
		PEERREQUEST_LEAVESTAGINGROOM,
		PEERREQUEST_UTMPLAYER,
		PEERREQUEST_UTMROOM,
		PEERREQUEST_STARTGAME,
		PEERREQUEST_STARTQUICKMATCH,
		PEERREQUEST_WIDENQUICKMATCHSEARCH,
		PEERREQUEST_STOPQUICKMATCH,
		PEERREQUEST_PUSHSTATS,
		PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO,
		// BFME 2 additions, numbered by Thread_Function's dispatch table.
		PEERREQUEST_MESSAGEROOMNOTICE,
		PEERREQUEST_REFRESHGAMELIST,
		PEERREQUEST_LISTGROUPROOMS,
		PEERREQUEST_UTMSTAGINGPN,
		PEERREQUEST_PUSHSTATSVALUES,
		PEERREQUEST_MAX
	} peerRequestType;

	std::string nick;	// only used by login, but must be outside the union b/c of copy constructor
	std::wstring text;  // can't be in a union
	std::string password;
	std::string email;
	std::string id;
	
	// gameopts
	std::string options; // full string for UTMs
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[MAX_SLOTS];

// Native owning copy389AAA and cleanup1EF723 witness raw wordsD0 and stringF8.
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> qmMaps;

	union
	{
		struct
		{
			Int profileID;
		} login;

		struct
		{
			Int id;
		} groupRoom;

		// Native assignment copies another four-byte union alternative here.
		struct { unsigned int unknown; } unknown_scalar;
		
		struct
		{
			Bool restrictGameList;
		} gameList;

		struct
		{
			Bool isAction;
		} message;

		struct
		{
			Int id;
		} stagingRoom;

		struct
		{
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt gameVersion;
			Bool allowObservers;
      Bool useStats;
			UnsignedShort ladPort;
			UnsignedInt ladPassCRC;
			Bool restrictGameList;
			// Native assignment copies this union member as 60 bytes.
			unsigned int unknown_creation_tail[9];
		} stagingRoomCreation;

		struct
		{
			// Donor field names and eight-entry arrays remain leads. Native only
			// proves this union alternative spans212 bytes; the extra40 are opaque.
			Int wins[MAX_SLOTS], losses[MAX_SLOTS], profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS], color[MAX_SLOTS];
			Int numPlayers, maxPlayers, numObservers;
			unsigned int unknown_game_options_tail[10];
		} gameOptions;

		struct
		{
			Bool isStagingRoom;
		} UTM;

		struct
		{
			Int minPointPercentage, maxPointPercentage, points;
			Int widenTime;
			Int ladderID;
			UnsignedInt ladderPassCRC;
			Int maxPing;
			Int maxDiscons, discons;
			char pings[17]; // 8 servers (0-ff), 1 NULL
			Int numPlayers;
			Int botID;
			Int roomID;
			Int side;
			Int color;
			Int NAT;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			// Native assignment copies 104 bytes; these final words are unnamed.
			unsigned int unknown_qm_tail[4];
		} QM;

		struct
		{
			Int locale;
			Int wins;
			Int losses;
			Int rankPoints;
			Int side;
			Bool preorder;
			// Native assignment copies 28 bytes; the seventh field is unnamed.
			unsigned int unknown_stats_tail;
		} statsToPush;

		// Native assignment ends with a distinct eight-byte alternative.
		struct { unsigned int unknown[2]; } unknown_pair;

	};
};

//-------------------------------------------------------------------------

enum DisconnectReason
{
	DISCONNECT_NICKTAKEN = 1,
	DISCONNECT_BADNICK,
	DISCONNECT_LOSTCON,
	DISCONNECT_COULDNOTCONNECT,
	DISCONNECT_GP_LOGIN_TIMEOUT,
	DISCONNECT_GP_LOGIN_BAD_NICK,
	DISCONNECT_GP_LOGIN_BAD_EMAIL,
	DISCONNECT_GP_LOGIN_BAD_PASSWORD,
	DISCONNECT_GP_LOGIN_BAD_PROFILE,
	DISCONNECT_GP_LOGIN_PROFILE_DELETED,
	DISCONNECT_GP_LOGIN_CONNECTION_FAILED,
	DISCONNECT_GP_LOGIN_SERVER_AUTH_FAILED,
	DISCONNECT_SERIAL_INVALID,
	DISCONNECT_SERIAL_NOT_PRESENT,
	DISCONNECT_SERIAL_BANNED,
	DISCONNECT_GP_NEWUSER_BAD_NICK,
	DISCONNECT_GP_NEWUSER_BAD_PASSWORD,
	DISCONNECT_GP_NEWPROFILE_BAD_NICK,
	DISCONNECT_GP_NEWPROFILE_BAD_OLD_NICK,
	DISCONNECT_MAX,
};

enum QMStatus
{
	QM_IDLE,
	QM_JOININGQMCHANNEL,
	QM_LOOKINGFORBOT,
	QM_SENTINFO,
	QM_WORKING,
	QM_POOLSIZE,
	QM_WIDENINGSEARCH,
	QM_MATCHED,
	QM_INCHANNEL,
	QM_NEGOTIATINGFIREWALLS,
	QM_STARTINGGAME,
	QM_COULDNOTFINDBOT,
	QM_COULDNOTFINDCHANNEL,
	QM_COULDNOTNEGOTIATEFIREWALLS,
	QM_STOPPED,
};

// BFME 2's "exeCRC" staging key: four dotted values, parsed by
// BfmeStagingCreationCRCs::parse (retail 0x003892DF) in PeerThread.cpp.
struct BfmeStagingCreationCRCs
{
	UnsignedInt value[4];
	Bool parse(AsciiString text);
	__forceinline Bool isZero() const
	{
		for (Int i = 0; i < 4; ++i)
		{
			if (value[i])
				return FALSE;
		}
		return TRUE;
	}
};

// this class encapsulates an action the peer thread wants from the UI
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	enum
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE,
		PEERRESPONSE_GROUPROOM,
		PEERRESPONSE_STAGINGROOM,
		PEERRESPONSE_STAGINGROOMLISTCOMPLETE,
		PEERRESPONSE_STAGINGROOMPLAYERINFO,
		PEERRESPONSE_JOINGROUPROOM,
		PEERRESPONSE_CREATESTAGINGROOM,
		PEERRESPONSE_JOINSTAGINGROOM,
		PEERRESPONSE_PLAYERJOIN,
		PEERRESPONSE_PLAYERLEFT,
		PEERRESPONSE_PLAYERCHANGEDNICK,
		PEERRESPONSE_PLAYERINFO,
		PEERRESPONSE_PLAYERCHANGEDFLAGS,
		PEERRESPONSE_ROOMUTM,
		PEERRESPONSE_PLAYERUTM,
		PEERRESPONSE_QUICKMATCHSTATUS,
		PEERRESPONSE_GAMESTART,
		PEERRESPONSE_FAILEDTOHOST,
		// BFME 2: a room NoticeMessage's text alone (roomMessageCallback
		// 0x0038BE17 stores 0x14); the name is descriptive.
		PEERRESPONSE_ROOMNOTICE,
		PEERRESPONSE_MAX
	} peerResponseType;

	std::string groupRoomName; // can't be in union

	std::string nick;   // can't be in a union
	std::string oldNick;   // can't be in a union
	std::wstring text;  // can't be in a union
	std::string locale; // can't be in a union

	std::string stagingServerGameOptions; // full string from UTMs

	// game opts sent with PEERRESPONSE_STAGINGROOM
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;
	std::string unknown_7c;

	// game opts sent with PEERRESPONSE_STAGINGROOMPLAYERINFO
	std::string stagingRoomPlayerNames[MAX_SLOTS];

	std::string command;
	std::string commandOptions;
	std::vector<AsciiString> unknown_100;

	union
	{
		unsigned int unknown_payload[143];
		struct
		{
			DisconnectReason reason;
		} discon;

		struct
		{
			Int id;
			Int numWaiting;
			Int maxWaiting;
			Int numGames;
			Int numPlaying;
		} groupRoom;

		struct
		{
			Int id;
			Bool ok;
		} joinGroupRoom;
		
		struct
		{
			Int result;
		} createStagingRoom;
		
		struct
		{
			Int id;
			Bool ok;
			Bool isHostPresent;
			Int result; // for failures
		} joinStagingRoom;
		
		struct
		{
			Bool isPrivate;
			Bool isAction;
			Int profileID;
		} message;

		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			RoomType roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			UnsignedInt internalIP; // for us, on connection
			UnsignedInt externalIP; // for us, on connection
			// connectCallback38B9F8 copies two 256-byte global buffers to +0x138
			// and +0x238 and sets +0x338 (cleared on the failure path).
			char loginTextA[256];
			char loginTextB[256];
			Bool loginComplete;
		} player;

		// BFME 2's layout, as listingGamesCallback (retail 0x0038CBBA) fills
		// it: the four-value exeCRC, cmdCRC, a 16-byte ladder hash, handicaps,
		// the game type, ten ladder-port values and the scenario.
		struct
		{
			Int id;
			Int action;
			Bool isStaging;
			Bool requiresPassword;
			Bool allowObservers;
			Bool useStats;
			UnsignedInt version;
			BfmeStagingCreationCRCs exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt cmdCRC;
			unsigned char ladderHash[16];
			UnsignedShort ladderPort;
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int handicap[MAX_SLOTS];
			Int numPlayers;
			Int numObservers;
			Int maxPlayers;
			Int percentComplete;
			Int gameType;
			Int ladPortValues[10];
			Int scenario;
		} stagingRoom;

		struct
		{
			QMStatus status;
			Int poolSize;
			Int mapIdx; // when matched
			Int seed; // when matched
			UnsignedInt IP[MAX_SLOTS]; // when matched
			// Native handleQMMatch38B6C1 witnesses port13C and the final array1AC.
			UnsignedShort port[MAX_SLOTS];
			Int side[MAX_SLOTS]; // when matched
			Int color[MAX_SLOTS]; // when matched
			Int nat[MAX_SLOTS];
			Int extra[MAX_SLOTS]; // sixth token purpose remains unknown
		} qmStatus;
	};
};

//-------------------------------------------------------------------------

// this is the actual message queue used to pass messages between threads
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual Bool isConnected( void ) = 0;
	virtual Bool isConnecting( void ) = 0;

	virtual void addRequest( const PeerRequest& req ) = 0;
	virtual Bool getRequest( PeerRequest& req ) = 0;

	virtual void addResponse( const PeerResponse& resp ) = 0;
	virtual Bool getResponse( PeerResponse& resp ) = 0;

	virtual SerialAuthResult getSerialAuthResult( void ) = 0;

	static GameSpyPeerMessageQueueInterface* createNewMessageQueue( void );
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

#endif // __PEERTHREAD_H__
