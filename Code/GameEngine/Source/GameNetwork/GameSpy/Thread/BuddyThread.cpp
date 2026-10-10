// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/buddythread /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// GameSpyBuddyMessageQueue::GameSpyBuddyMessageQueue 0x00551A94 (110B),
// GameSpyBuddyMessageQueue::getRequest 0x0055106D (102B),
// GameSpyBuddyMessageQueue::getResponse 0x005510D3 (102B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

// FILE: BuddyThread.cpp //////////////////////////////////////////////////////
// GameSpy Presence & Messaging (Buddy) thread
// This thread communicates with GameSpy's buddy server
// and talks through a message queue with the rest of
// the game.
// Author: Matthew D. Campbell, June 2002

// BFME 2's WWLib thread base (as in PersistentStorageThread.cpp), not ZH's
// 0x58-byte one: BuddyThreadClass's members start at +0x50 in retail
// (errorCallback 0x005513E9 writes m_lastErrorCode at +0x58).
#define THREAD_H
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

#include "Common/StackDump.h"

#include "mutex.h"
#include "thread.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------

typedef std::queue<BuddyRequest> RequestQueue;
typedef std::queue<BuddyResponse> ResponseQueue;
// Native551988 calls the separately verified response deque cleanup.
// Declaration-only here preserves its exception boundary under home flags.
namespace _STL {template<> deque<BuddyResponse>::~deque();}
class BuddyThreadClass;
// Retail shutdown550B4C and cleanup9990D prove the owning lock at +70.
class Rva0009990D {public:MutexClass::LockClass *m_ptr;void clear();~Rva0009990D(){clear();}};
class Rva00550B4C {public:void rva00550B4C();};

class GameSpyBuddyMessageQueue : public GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueue();
	GameSpyBuddyMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );

	virtual void addRequest( const BuddyRequest& req );
	virtual Bool getRequest( BuddyRequest& req );

	virtual void addResponse( const BuddyResponse& resp );
	virtual Bool getResponse( BuddyResponse& resp );

	virtual GPProfile getLocalProfileID( void );

	BuddyThreadClass* getThread( void ) { return m_thread; }

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	BuddyThreadClass *m_thread;
	MutexClass m_bfme_rva0063e080_mutex68;
	Rva0009990D m_bfme_lock70;
};


extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
#define MESSAGE_QUEUE ((GameSpyBuddyMessageQueue *)TheGameSpyBuddyMessageQueue)

//-------------------------------------------------------------------------

class BuddyThreadClass : public ThreadClass
{

public:
	BuddyThreadClass() : ThreadClass(0) { m_isNewAccount = m_isdeleting = m_isConnecting = m_isConnected = false; m_profileID = 0; m_lastErrorCode = 0; }

	void Thread_Function();

	void errorCallback( GPConnection *con, GPErrorArg *arg );
	void messageCallback( GPConnection *con, GPRecvBuddyMessageArg *arg );
	void connectCallback( GPConnection *con, GPConnectResponseArg *arg );
	void requestCallback( GPConnection *con, GPRecvBuddyRequestArg *arg );
	void statusCallback( GPConnection *con, GPRecvBuddyStatusArg *arg );
	void rva00550720( GPConnection *con, GPRecvBuddyRequestArg *arg );

	Bool isConnecting( void ) { return m_isConnecting; }
	Bool isConnected( void ) { return m_isConnected; }

	GPProfile getLocalProfileID( void ) { return m_profileID; }

private:
	Bool m_isNewAccount;
	Bool m_isConnecting;
	Bool m_isConnected;
	GPProfile m_profileID;
	Int m_lastErrorCode;
	Bool m_isdeleting;
	std::string m_nick, m_email, m_pass;
};

static enum CallbackType
{
	CALLBACK_CONNECT,
	CALLBACK_ERROR,
	CALLBACK_RECVMESSAGE,
	CALLBACK_RECVREQUEST,
	CALLBACK_RECVSTATUS,
	CALLBACK_MAX
};

// Retail 0x00551FB3..0x00552027, 116B, immediately follows addResponse.
// BFME1 34f59164f BuddyThread.cpp supplies callbackWrapper's purpose and
// cases 0..4. Target calls identify those arms independently; case 5 calls
// the existing address-named rva00550720 callback, whose purpose is opaque.
// The target reads the queue's thread at +0x64, checks it once, then forwards
// con and arg through the six-way dispatcher; every arm ends in a cdecl ret.
void callbackWrapper( GPConnection *con, void *arg, void *param )
{
	BuddyThreadClass *thread = MESSAGE_QUEUE->getThread();
	if (!thread)
		return;
	switch ((Int)param)
	{
	case 0: thread->connectCallback(con, (GPConnectResponseArg *)arg); break;
	case 1: thread->errorCallback(con, (GPErrorArg *)arg); break;
	case 2: thread->messageCallback(con, (GPRecvBuddyMessageArg *)arg); break;
	case 3: thread->requestCallback(con, (GPRecvBuddyRequestArg *)arg); break;
	case 4: thread->statusCallback(con, (GPRecvBuddyStatusArg *)arg); break;
	case 5: thread->rva00550720(con, (GPRecvBuddyRequestArg *)arg); break;
	}
}


//-------------------------------------------------------------------------

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameSpyBuddyMessageQueueCtorThunk.cpp
GameSpyBuddyMessageQueue::GameSpyBuddyMessageQueue()
{
	m_bfme_lock70.m_ptr = 0;
	m_thread = NULL;
}


Bool GameSpyBuddyMessageQueue::getRequest( BuddyRequest& req )
{
	MutexClass::LockClass m(m_requestMutex, 0);
	if (m.Failed())
		return false;

	if (m_requests.empty())
		return false;
	req = m_requests.front();
	m_requests.pop();
	return true;
}

void GameSpyBuddyMessageQueue::addRequest( const BuddyRequest& req )
{
	MutexClass::LockClass m(m_requestMutex);
	if (m.Failed())
		return;

	m_requests.push(req);
}


// Retail 0x00551BA7, 77 bytes: vtable 0x00C6B020 slot 5, between addRequest
// (slot 3) and getResponse (slot 6); the response mutex and queue push.
void GameSpyBuddyMessageQueue::addResponse( const BuddyResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex);
	if (m.Failed())
		return;

	m_responses.push(resp);
}

Bool GameSpyBuddyMessageQueue::getResponse( BuddyResponse& resp )
{
	MutexClass::LockClass m(m_responseMutex, 0);
	if (m.Failed())
		return false;

	if (m_responses.empty())
		return false;
	resp = m_responses.front();
	m_responses.pop();
	return true;
}


//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

// Zero Hour's BuddyThreadClass::errorCallback; native [5513E9,55182E),1093B
// (callbackWrapper case 1). The GameSpy SDK's GPErrorArg and BFME2's error
// response are read through local views: the sweep shim's GP.h orders
// GPErrorArg differently, and BFME2's BuddyResponse error arm keeps the
// GPResult Zero Hour commented out, putting errorCode at +0x10. The error
// codes are the SDK's values (GP.h's enum here is not). BFME2 also skips the
// bad-nick/bad-email login errors, reports a forced disconnect as response
// type 6, and copies the error code's name over the SDK error string.
struct GPErrorArgSDK
{
	GPResult result;
	GPErrorCode errorCode;
	char *errorString;
	GPEnum fatal;
};
struct BuddyErrorResponseArm
{
	GPResult result;
	GPErrorCode errorCode;
	char errorString[MAX_BUDDY_CHAT_LEN];
	GPEnum fatal;
};
struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	Int peerRequestType;
	unsigned char m_04[492 - 4];
};

void BuddyThreadClass::errorCallback( GPConnection *con, GPErrorArg *errorArg )
{
	const GPErrorArgSDK *arg = (const GPErrorArgSDK *)errorArg;
	m_lastErrorCode = arg->errorCode;

	char errorCodeString[256];
	char resultString[256];

	switch((Int)arg->result)
	{
	case 0: strcpy(resultString, "GP_NO_ERROR"); break;
	case 1: strcpy(resultString, "GP_MEMORY_ERROR"); break;
	case 2: strcpy(resultString, "GP_PARAMETER_ERROR"); break;
	case 3: strcpy(resultString, "GP_NETWORK_ERROR"); break;
	case 4: strcpy(resultString, "GP_SERVER_ERROR"); break;
	default:
		strcpy(resultString, "Unknown result!");
	}

	switch((Int)arg->errorCode)
	{
	case 0x0000: strcpy(errorCodeString, "GP_GENERAL"); break;
	case 0x0001: strcpy(errorCodeString, "GP_PARSE"); break;
	case 0x0002: strcpy(errorCodeString, "GP_NOT_LOGGED_IN"); break;
	case 0x0003: strcpy(errorCodeString, "GP_BAD_SESSKEY"); break;
	case 0x0004: strcpy(errorCodeString, "GP_DATABASE"); break;
	case 0x0005: strcpy(errorCodeString, "GP_NETWORK"); break;
	case 0x0006: strcpy(errorCodeString, "GP_FORCED_DISCONNECT"); break;
	case 0x0007: strcpy(errorCodeString, "GP_CONNECTION_CLOSED"); break;
	case 0x0100: strcpy(errorCodeString, "GP_LOGIN"); break;
	case 0x0101: strcpy(errorCodeString, "GP_LOGIN_TIMEOUT"); break;
	case 0x0102: strcpy(errorCodeString, "GP_LOGIN_BAD_NICK"); break;
	case 0x0103: strcpy(errorCodeString, "GP_LOGIN_BAD_EMAIL"); break;
	case 0x0104: strcpy(errorCodeString, "GP_LOGIN_BAD_PASSWORD"); break;
	case 0x0105: strcpy(errorCodeString, "GP_LOGIN_BAD_PROFILE"); break;
	case 0x0106: strcpy(errorCodeString, "GP_LOGIN_PROFILE_DELETED"); break;
	case 0x0107: strcpy(errorCodeString, "GP_LOGIN_CONNECTION_FAILED"); break;
	case 0x0108: strcpy(errorCodeString, "GP_LOGIN_SERVER_AUTH_FAILED"); break;
	case 0x0200: strcpy(errorCodeString, "GP_NEWUSER"); break;
	case 0x0201: strcpy(errorCodeString, "GP_NEWUSER_BAD_NICK"); break;
	case 0x0202: strcpy(errorCodeString, "GP_NEWUSER_BAD_PASSWORD"); break;
	case 0x0204: strcpy(errorCodeString, "GP_NEWUSER_UNIQUENICK_INUSE"); break;
	case 0x0300: strcpy(errorCodeString, "GP_UPDATEUI"); break;
	case 0x0301: strcpy(errorCodeString, "GP_UPDATEUI_BAD_EMAIL"); break;
	case 0x0400: strcpy(errorCodeString, "GP_NEWPROFILE"); break;
	case 0x0401: strcpy(errorCodeString, "GP_NEWPROFILE_BAD_NICK"); break;
	case 0x0402: strcpy(errorCodeString, "GP_NEWPROFILE_BAD_OLD_NICK"); break;
	case 0x0500: strcpy(errorCodeString, "GP_UPDATEPRO"); break;
	case 0x0501: strcpy(errorCodeString, "GP_UPDATEPRO_BAD_NICK"); break;
	case 0x0600: strcpy(errorCodeString, "GP_ADDBUDDY"); break;
	case 0x0601: strcpy(errorCodeString, "GP_ADDBUDDY_BAD_FROM"); break;
	case 0x0602: strcpy(errorCodeString, "GP_ADDBUDDY_BAD_NEW"); break;
	case 0x0603: strcpy(errorCodeString, "GP_ADDBUDDY_ALREADY_BUDDY"); break;
	case 0x0700: strcpy(errorCodeString, "GP_AUTHADD"); break;
	case 0x0701: strcpy(errorCodeString, "GP_AUTHADD_BAD_FROM"); break;
	case 0x0702: strcpy(errorCodeString, "GP_AUTHADD_BAD_SIG"); break;
	case 0x0800: strcpy(errorCodeString, "GP_STATUS"); break;
	case 0x0900: strcpy(errorCodeString, "GP_BM"); break;
	case 0x0901: strcpy(errorCodeString, "GP_BM_NOT_BUDDY"); break;
	case 0x0A00: strcpy(errorCodeString, "GP_GETPROFILE"); break;
	case 0x0A01: strcpy(errorCodeString, "GP_GETPROFILE_BAD_PROFILE"); break;
	case 0x0B00: strcpy(errorCodeString, "GP_DELBUDDY"); break;
	case 0x0B01: strcpy(errorCodeString, "GP_DELBUDDY_NOT_BUDDY"); break;
	case 0x0C00: strcpy(errorCodeString, "GP_DELPROFILE"); break;
	case 0x0C01: strcpy(errorCodeString, "GP_DELPROFILE_LAST_PROFILE"); break;
	case 0x0D00: strcpy(errorCodeString, "GP_SEARCH"); break;
	case 0x0D01: strcpy(errorCodeString, "GP_SEARCH_CONNECTION_FAILED"); break;
	default:
		strcpy(errorCodeString, "Unknown error code!");
	}

	if (arg->fatal == 1 && arg->errorCode != 0x0102 && arg->errorCode != 0x0103)
	{
		BuddyResponse errorResponse;
		BuddyErrorResponseArm &error = *(BuddyErrorResponseArm *)&errorResponse.arg;
		*(Int *)&errorResponse.buddyResponseType = (arg->errorCode == 0x0006) ? 6 : BuddyResponse::BUDDYRESPONSE_DISCONNECT;
		errorResponse.result = arg->result;
		error.errorCode = arg->errorCode;
		error.fatal = arg->fatal;
		strncpy(error.errorString, arg->errorString, MAX_BUDDY_CHAT_LEN);
		error.errorString[MAX_BUDDY_CHAT_LEN-1] = 0;
		strncpy(error.errorString, errorCodeString, MAX_BUDDY_CHAT_LEN-1);
		m_isConnecting = m_isConnected = false;
		TheGameSpyBuddyMessageQueue->addResponse( errorResponse );

		if (m_isdeleting)
		{
			BfmeOpaqueOwnedRecord492 req;
			req.peerRequestType = PeerRequest::PEERREQUEST_LOGOUT;
			TheGameSpyPeerMessageQueue->addRequest( *(const PeerRequest *)&req );
			m_isdeleting = false;
		}
	}
}

// Native551988..551A06 follows PeerThread cleanup order; target member
// offsets and the already recovered shutdown distinguish the Buddy owner.
GameSpyBuddyMessageQueue::~GameSpyBuddyMessageQueue(){
 ((Rva00550B4C*)this)->rva00550B4C();
}
